/*
 * laztech.hpp
 *
 *  Created on: Nov 22, 2016
 *      Author: alex
 */

#ifndef L5_APPLICATION_LAZTECH_HPP_
#define L5_APPLICATION_LAZTECH_HPP_

// built-in libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// freertos libraries (things we are extending)
#include "utilities.h"
#include "singleton_template.hpp"
#include "command_handler.hpp"
#include "scheduler_task.hpp"

// freertos helper libraries (things we are using)
#include "gpio.hpp"
#include "uart2.hpp"

// laztech libraries
// "include tinfl.c"
#define TINFL_HEADER_FILE_ONLY
#include "tinfl.c"
// "include scanner.l"
#ifdef __cplusplus
extern "C" {
#endif
extern FILE * yyin;
int yylex(void);
#ifdef __cplusplus
}
#endif

// constants
#define LAZTECH_MAX_JOBS 10
#define LAZTECH_STEP_DELAY 100

// enums
enum {
	LAZTECH_DIR_NEG,
	LAZTECH_DIR_POS,
};

// global vars
enum {
	shared_spool, // This is a queue so that the laztech thread is notified when the spooler has finished spooling data.
	shared_mem, // This is a semaphore to protect over allocation of memory from two threads.
};

/**
 * This class contains all of the hardware abstraction. The x and y values may unsync.
 * If this happens you should call calibrate() while the laser is off.
 */
class Laztech: public SingletonTemplate<Laztech> {
public:
	void calibrate() {
		this->setXDir(-1);
		this->setYDir(-1);

		while(!this->isXHome()) {
			this->stepX();
		}

		while(!this->isYHome()) {
			this->stepY();
		}

		this->x = 0;
		this->y = 0;
	}

	bool isXHome() {
		return this->pin_xhome->read();
	}

	bool isYHome() {
		return this->pin_yhome->read();
	}

	int getXDir() {
		return this->pin_xdir->read() ? LAZTECH_DIR_POS : LAZTECH_DIR_NEG;
	}

	int getYDir() {
		return this->pin_ydir->read() ? LAZTECH_DIR_POS : LAZTECH_DIR_NEG;
	}

	void setXDir(int dir) {
		if (dir == LAZTECH_DIR_NEG) {
			this->pin_xdir->setLow();
		} else {
			this->pin_xdir->setHigh();
		}
	}

	void setYDir(int dir) {
		if (dir == LAZTECH_DIR_NEG) {
			this->pin_ydir->setLow();
		} else {
			this->pin_ydir->setHigh();
		}

	}

	int getX() {
		return this->x;
	}

	int getY() {
		return this->y;
	}

	void stepX() {
		printf("[I] Stepped x.\n");
		this->pin_xstep->setHigh();
		delay_ms(LAZTECH_STEP_DELAY);
		this->pin_xstep->setLow();
		delay_ms(LAZTECH_STEP_DELAY);

		if(this->getXDir() == LAZTECH_DIR_NEG) {
			this->x--;
		} else {
			this->x++;
		}
	}

	void stepY() {
		printf("[I] Stepped y.\n");
		this->pin_ystep->setHigh();
		delay_ms(LAZTECH_STEP_DELAY);
		this->pin_ystep->setLow();
		delay_ms(LAZTECH_STEP_DELAY);

		if(this->getYDir() == LAZTECH_DIR_NEG) {
			this->y--;
		} else {
			this->y++;
		}
	}

	void setLaserOn() {
		/* REMOVED FOR SAFETY */
	}

	void setLaserOff() {
		/* REMOVED FOR SAFETY */
	}

	bool getLaser() {
		/* REMOVED FOR SAFETY */
		return false;
	}

	/*
	 void stepXY() {
	 mpOurGpio->FIOSET = (3 << mPinNum);
	 mpOurGpio->FIOCLR = (3 << mPinNum);
	 }
	 */

private:
	GPIO *pin_xhome;
	GPIO *pin_yhome;
	GPIO *pin_xdir;
	GPIO *pin_ydir;
	GPIO *pin_xstep;
	GPIO *pin_ystep;

	int x;
	int y;

	Laztech() {
		this->pin_xhome = new GPIO(P2_0);
		this->pin_yhome = new GPIO(P2_1);

		this->pin_xdir = new GPIO(P2_2);
		this->pin_ydir = new GPIO(P2_3);
		this->pin_xstep = new GPIO(P2_4);
		this->pin_ystep = new GPIO(P2_5);

		this->pin_xhome->setAsInput();
		this->pin_yhome->setAsInput();

		this->pin_xdir->setAsOutput();
		this->pin_ydir->setAsOutput();
		this->pin_xstep->setAsOutput();
		this->pin_ystep->setAsOutput();

		this->pin_xdir->setLow();
		this->pin_ydir->setLow();
		this->pin_xstep->setLow();
		this->pin_ystep->setLow();

		// Dummy sets for compiler warning. These will be overwritten in calibrate().
		this->x = 0;
		this->y = 0;

		// calibrate
		//this->calibrate();

		return;
	}
	friend class SingletonTemplate<Laztech>;
};

/**
 * This task will listen on the UART for an incoming PDF. When found it will start to queue the jobs.
 */
class laztech_spoolerTask: public scheduler_task {
public:
	laztech_spoolerTask(uint8_t priority) :
			scheduler_task("laztech_spooler", 2048, priority) {
		Uart2 &uart2 = Uart2::getInstance();

		// setup uart
		uart2.init(9600);
		uart2.setReady(true);

		// setup queue
		QueueHandle_t spool = xQueueCreate(LAZTECH_MAX_JOBS, sizeof(uint16_t));

		if (spool == NULL) {
			printf("[E] Spooler: Could not create queue.\n");
			return;
		}

		addSharedObject(shared_spool, spool);
	}

	bool run(void *p) {
		static uint16_t job_id = 0;
		char filename[16];
		FILE * fd;

		// open next file
		snprintf(filename, 16, "1:%04d.job.gz", job_id);
		fd = fopen(filename, "w");

		if (fd == NULL) {
			return true; // FIXME
		}

		// search for start
		streamsearch("stream\n", 7);
		// search for end
		streamsearch("endstream", 9, fd);

		fclose(fd);

		// notify other thread to print
		QueueHandle_t spool = getSharedObject(shared_spool);
		xQueueSend(spool, &job_id, portMAX_DELAY);

		job_id++;

		return true;
	}
private:

	/*
	 * @param buf The ring buffer.
	 * @param idx The index of the last character written to the ring buffer.
	 * @param str The String to match.
	 * @param len The length of str.
	 *
	 * @return Returns 1 on match, otherwise 0.
	 *
	 */
	int ringncmp(char * buf, uint8_t idx, const char * str, uint8_t len) {
		return strncmp(buf, str + ((len - 1) - idx), idx + 1) == 0
				&& strncmp(buf + (idx + 1) % len, str, (len - 1) - idx) == 0;
	}

	/*
	 * @param str The string to search for in the stream.
	 * @param len The length of str.
	 * @param fd A save any bytes that do not match str.
	 *
	 * @return Returns 0 on success, 1 on error.
	 *
	 */
	int streamsearch(const char * str, uint8_t len, FILE * fd=NULL) {
		int i;
		char * bytes;

		// get input
		Uart2 &uart2 = Uart2::getInstance();

		// create and pre-fill ring buffer
		bytes = (char *) malloc(sizeof(char) * len);
		for (i = 0; i < len; i++) {
			uart2.getChar(&(bytes[i]), portMAX_DELAY);
		}

		// reset index
		i--;

		while (1) {
			// check match
			if (ringncmp(bytes, i, str, len)) {
				break;
			}

			// next idx out/in
			i = (i + 1) % len;

			// save non-matching characters, if save is defined
			if (fd != NULL) {
				fwrite(&(bytes[i]), sizeof(char), 1, fd);
			}

			// get next byte
			uart2.getChar(&(bytes[i]), portMAX_DELAY);
		}

		free(bytes);
		return 0;
	}
};

/**
 * This task will unzip the data and laser the product.
 */
class laztech_laserTask: public scheduler_task {
public:
	laztech_laserTask(uint8_t priority) :
			scheduler_task("laztech_laser", 2048, priority) {
		Laztech &lazer = Laztech::getInstance();
		lazer.calibrate();
	}

	bool run(void *p) {
		uint16_t job_id;
		QueueHandle_t spool = getSharedObject(shared_spool);

		printf("Lazer: Waiting for job...\n");
		if (xQueueReceive(spool, &job_id, portMAX_DELAY)) {
			printf("Lazer: Processing job #%d.\n", job_id);

			// unzip data
			this->inflate(job_id);

			// point scanner
			char filename[16];
			snprintf(filename, 16, "1:%04d.job", job_id);
			yyin = fopen(filename, "r");

			if (yyin == NULL) {
				printf("[E] Lazer: Could not open yyin.\n");
				return true; // FIXME
			}

			printf("Lazer: Scanning...\n");
			yylex();

			printf("Lazer: Finished job #%d.\n", job_id);
		}

		return true;
	}
private:
	int inflate(uint16_t job_id) {
		FILE * in;
		FILE * out;
		char filename[16];

		// open input file
		snprintf(filename, 16, "1:%04d.job.gz", job_id);
		in = fopen(filename, "r");
		if(in == NULL) {
			return 0;
		}

		// open output file
		snprintf(filename, 16, "1:%04d.job", job_id);
		out = fopen(filename, "w");
		if(out == NULL) {
			fclose(in);
			return 0;
		}

		// FIXME
		/*
		 * while() { // more in bytes
		 *   // get min 512 or left
		 *   // decomp
		 *   // write output
		 *
		 * }
		 *
		 *
		 */

		fclose(in);
		fclose(out);

		return 1;
	}
};

#endif /* L5_APPLICATION_LAZTECH_HPP_ */
