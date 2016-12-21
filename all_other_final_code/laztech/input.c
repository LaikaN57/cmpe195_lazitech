#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#define DEBUG 1
#define LIMIT 1000

/*
 * @param buf The ring buffer.
 * @param idx The index of the last character written to the ring buffer.
 * @param str The String to match.
 * @param len The length of str.
 *
 * @return Returns 1 on match, otherwise 0.
 *
 */
int ringncmp(char * buf, uint8_t idx, char * str, uint8_t len) {
  return strncmp(buf, str + ((len - 1) - idx), idx + 1) == 0 && strncmp(buf + (idx + 1) % len, str, (len - 1) - idx) == 0;
}

/*
 * @param str The string to search for in the stream.
 * @param len The length of str.
 * @param in A callback function used to get the next byte of input from the stream.
 * @param save A callback function used to save any bytes that do not match str.
 * 
 * @return Returns 0 on success, 1 on error.
 * 
 */
int streamsearch(char * str, uint8_t len, int (* in)(void), int (* save)(char)) {
  int i;
  int c;
  char * bytes;

  // create and pre-fill ring buffer
  bytes = (char *) malloc(sizeof(char) * len);
  for(i = 0; i < len; i++) {
    c = in(); // getchar();
    if(c == EOF) {
      free(bytes);
      return 1;
    }
    bytes[i] = (char) c;
  }

  // reset index
  i--;

  while(1) {
    // check match
    if(ringncmp(bytes, i, str, len)) {
      break;
    }
    
    // next idx out/in
    i = (i + 1) % len;

    // save non-matching characters, if save is defined
    if(save != NULL) {
      save(bytes[i]);
    }
    
    // get next byte
    c = in(); // getchar();
    if(c == EOF) {
      free(bytes);
      return 1;
    }
    bytes[i] = (char) c;
  }
  
  free(bytes);
  return 0;
}

// wapper for putchar
int out(char c) {
  // save to 512 buffer
  // if full, call zlib

  return printf("%02hhx ", c);
}

void flush() {
  // if not 0, call zlib with end option
}

int main() {
  int i;
  char bytes[16];

  int limit;
  limit = 0;

  while(limit < LIMIT) {
    // clear all buffers

    if(DEBUG) printf("Scanning for start marker...\n");
    streamsearch("stream\n", 7, &getchar, NULL);
    if(DEBUG) printf("Scanning for end marker...\n");
    streamsearch("endstream", 9, &getchar, &out);
    if(DEBUG) printf("Found end marker.\n");
    
    // flush();

    return 0;
  
  
  
  
  
  
  
  
  
  
  
  
  
    /* Look for the start mark by finding the word "stream\n" */
    if(DEBUG) printf("Scanning for start marker...\n");

    // pre-fill ring buffer
    for(i = 0; i < 7; i++) {
      bytes[i] = (char) getchar();
    }
    // reset index
    i--;
    while(1) {
      // check for start marker
      if(ringncmp(bytes, i, "stream\n", 7)) {
        break;
      }
      i = (i + 1) % 7;
      bytes[i] = (char) getchar();
    }

    if(DEBUG) printf("Found start marker.\n");

    /* Look for the end mark by finding the work "endstream" */
    if(DEBUG) printf("Scanning for end marker...\n");

    // pre-fill ring buffer
    for(i = 0; i < 9; i++) {
      bytes[i] = (char) getchar();
    }
    // reset index
    i--;
    while(1) {
      // check for end marker
      if(ringncmp(bytes, i, "endstream", 9)) {
        break;
      }
      i = (i + 1) % 9;
      //fwrite(fd, bytes[i]);
      if(DEBUG) printf("%02hhx ", bytes[i]);
      if(!DEBUG) putchar(bytes[i]);
      bytes[i] = (char) getchar();
    }

    if(DEBUG) printf("Found end marker.\n");

    // close lock and do something to it.
    return 0;

    if(DEBUG) sleep(1);
    limit++;
  }
}
