// example4.c - Uses tinfl.c to decompress a zlib stream in memory to an output file
// Public domain, May 15 2011, Rich Geldreich, richgel99@gmail.com. See "unlicense" statement at the end of tinfl.c.
#include "tinfl.c"
#include <stdio.h>
#include <limits.h>

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint;

#define my_max(a,b) (((a) > (b)) ? (a) : (b))
#define my_min(a,b) (((a) < (b)) ? (a) : (b))

static int tinfl_put_buf_func(const void* pBuf, int len, void *pUser)
{
  return len == (int)fwrite(pBuf, 1, len, (FILE*)pUser);
}

int main(int argc, char *argv[])
{
  int status;
  FILE *pInfile, *pOutfile;
  uint infile_size;
  size_t in_buf_size;
  uint8 *pCmp_data;
  long file_loc;

  // Open input file.
  if (!(pInfile = fopen(filename, "rb"))) {
    printf("Failed opening input file!\n");
    return EXIT_FAILURE;
  }

  // Determine input file's size.
  fseek(pInfile, 0, SEEK_END);
  file_loc = ftell(pInfile);
  fseek(pInfile, 0, SEEK_SET);

  if ((file_loc < 0) || (file_loc > INT_MAX)) {
    printf("File is too large to be processed by this example.\n");

    fclose(pInfile);

    return EXIT_FAILURE;
  }

  infile_size = (uint)file_loc;

  // Allocate and input file buffer.
  if (!(pCmp_data = (uint8 *)malloc(infile_size))) {
    printf("Out of memory!\n");

    fclose(pInfile);

    return EXIT_FAILURE;
  }

  // Read input file.
  if (fread(pCmp_data, 1, infile_size, pInfile) != infile_size) {
    printf("Failed reading input file!\n");
    
    free(pCmp_data);
    fclose(pInfile);

    return EXIT_FAILURE;
  }

  // Open output file.
  if (!(pOutfile = fopen(filename, "wb"))) {
    printf("Failed opening output file!\n");
    
    free(pCmp_data);
    fclose(pInfile);

    return EXIT_FAILURE;
  }

  // Decompress
  in_buf_size = infile_size;
  if (!(status = tinfl_decompress_mem_to_callback(pCmp_data, &in_buf_size, tinfl_put_buf_func, pOutfile, 0))) {
    printf("tinfl_decompress_mem_to_callback() failed with status %i!\n", status);
    
    free(pCmp_data);
    fclose(pInfile);
    fclose(pOutfile);
  
    return EXIT_FAILURE;
  }

  // Close
  free(pCmp_data);
  fclose(pInfile);
  fclose(pOutfile);

  printf("Success.\n");
  return EXIT_SUCCESS;
}
