/**
 * Takes in a pdf path from the command line then spits out the raw commands and breaks.
 * http://zlib.net/zlib-1.2.8.tar.gz
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {

  if(argc < 2) {
    printf("Usage: %s <pdf>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /*
   * This shared buffer.
   */
  char* shared_buf;
  uint16_t in_partition;
  uint16_t in_index;

  FILE* fd = fopen(argv[1], "r");

  while(fgets(temp, 512, fp) != NULL) {
    if((strstr(temp, str)) != NULL) {
      printf("\n%s\n", temp);
    }
  }

// search pdf for content objects
// if found one
//   determine encoding
//   decode and output

  fclose(fd);

  return 0;
}
