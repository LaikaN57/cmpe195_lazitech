/*
 * laztech.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: alex
 */

#include "laztech.hpp"

CMD_HANDLER_FUNC(laztech_testHandler) {
    cmdParams.trimStart(" ");
    cmdParams.trimEnd(" ");

    Laztech &laser = Laztech::getInstance();

	if(cmdParams.beginsWithIgnoreCase("x")) {
		cmdParams.eraseFirstWords(1, ' ');
	    cmdParams.trimStart(" ");

	    int steps = str::toInt(cmdParams);
	    if(steps < 0) {
	    	laser.setXDir(LAZTECH_DIR_NEG);
	    } else {
	    	laser.setXDir(LAZTECH_DIR_POS);

	    }
	    for(int i = 0; i < str::toInt(cmdParams); i++) {
		    laser.stepX();
	    }
	} else if(cmdParams.beginsWithIgnoreCase("y")) {
		cmdParams.eraseFirstWords(1, ' ');
	    cmdParams.trimStart(" ");

	    int steps = str::toInt(cmdParams);
	    if(steps < 0) {
	    	laser.setYDir(LAZTECH_DIR_NEG);
	    } else {
	    	laser.setYDir(LAZTECH_DIR_POS);

	    }
	    for(int i = 0; i < str::toInt(cmdParams); i++) {
		    laser.stepY();
	    }
	}

	return 0;
}


/*
size_t tinfl_decompress_mem_to_mem_test(void *pOut_buf, size_t out_buf_len, const void *pSrc_buf, size_t src_buf_len, int flags)
{
  tinfl_decompressor decomp;
  tinfl_status status;
  tinfl_init(&decomp);
  status = tinfl_decompress(&decomp, (const mz_uint8*)pSrc_buf, &src_buf_len, (mz_uint8*)pOut_buf, (mz_uint8*)pOut_buf, &out_buf_len, (flags & ~TINFL_FLAG_HAS_MORE_INPUT) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
  return (status != TINFL_STATUS_DONE) ? TINFL_DECOMPRESS_MEM_TO_MEM_FAILED : out_buf_len;
}
*/



// 500 mm/s
// 1 step per pixel
// 100 dpi
// 20.32 mm/s





//int inflate(FILE * fd, char * out, int len);




		/*
		// setup semaphore
		SemaphoreHandle_t mem = xSemaphoreCreateBinary();

		if (mem == NULL) {
			printf("[E] Spooler: Could not create binary semaphore.\n");
			return;
		}

		// FIXME: check if object is already shared.
		addSharedObject(shared_mem, mem);
		*/
