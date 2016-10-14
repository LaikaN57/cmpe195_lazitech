// linux only
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

/* Name of input file.  May be "-".  */
static char const *infile;

int main(int argc, char *argv[]) {
  int c;
  int file_open_mode = O_RDONLY;

  while((c = getopt(argc, argv, "i:")) != -1) {
    switch(c) {
      case 'i':
        infile = optarg;
        break;
      case '?':
        if(optopt == 'i')
          fprintf(stderr, "Option -%c requires an argument.\n", optopt);
        else if(isprint(optopt))
          fprintf(stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
        return 1;
      default:
        abort();
        break;
    }
  }

  input_desc = open(infile, file_open_mode);
  if(input_desc < 0) {
    error(0, errno, "%s", quotef(infile));
    ok = false;
    return 1;
  }

  return 0;
}

