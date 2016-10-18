#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define DEBUG 0
#define LIMIT 1000

int main() {
  int i;
  int limit;
  unsigned char bytes[9];
  unsigned char end[] = "endstream";

  limit = 0;

  while(limit < LIMIT) {
    /* Look for the start mark by finding the word "stream" */
    if(DEBUG) printf("\nScanning...\n");

    // readline (lame version)
    scanf("%6s", bytes);
    getchar();

    // cmpare to stream
    if(strncmp(bytes, "stream", 6) == 0) {
      /* Found start mark, so continue to save bytes lazily until you find the
         end marker "endstream" */
      if(DEBUG) printf("\nFound start marker.\n");

      // read 9 bytes
      for(i = 0; i < 9; i++) {
        bytes[i] = (unsigned char) getchar();
      }

      // reset index
      i--;

      while(1) {
        // check for end marker
        if(strncmp(bytes, end + (8 - i), i + 1) == 0 &&
           strncmp(bytes + (i + 1) % 9, end, 8 - i) == 0) {
          /* Found end maker so we can just close and proccess the file as all
             bytes needed have already been saved */
          if(DEBUG) printf("\nFound end marker.\n");
          // close file
          break;
        }

	// circ buffer
        i = (i + 1) % 9;

	// save byte and get a new one
        //fwrite(fd, bytes[i]);
        if(DEBUG) printf("%02x ", bytes[i]);
        if(!DEBUG) putchar(bytes[i]);
        bytes[i] = (unsigned char) getchar();
      }
    }

    if(DEBUG) sleep(1);
    limit++;
  }
}
