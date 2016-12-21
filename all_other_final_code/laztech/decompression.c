#include "tinfl.c"

int main() {
  int compressed_buffer[512];
  int uncompressed_buffer[512 * 5];
  int i;

  // search for "stream"
  do {
    for(i = 1; i < 6; i++) {
      compressed_buffer[i-1] = compressed_buffer[i];
    }

    compressed_buffer[5] = getchar();
  } while(strncmp(compressed_buffer, "stream", 6));

  // start zlib
  tinfl_init(&decomp);

  // save block until "endstream"
  do {
    // save 512 chars or until (timeout or "endstream")
    do {
      compressed_buffer[cb_len] = getchar();
      cb_len++;

      if(strncmp(compressed_buffer + (cb_len - 9), "endstream", 9)) {
        cb_len -= 9;
        end = 1;
      } else if(timeout) {
        cb_len--; // reduce bytes by 1 (for TIMEOUT signal "char") ???
        timeouts++;
      } else {
        timeouts = 0;
      }
    } while(cb_len < 512 && !end);

    if(cb_len > 0) {
      // flush out
      tinfl_decompress(&decomp,
          (const mz_uint8 *) compressed_buffer, &cb_len,
          (mz_uint8 *) uncompressed_buffer, (mz_uint8 *) uncompressed_buffer, &ub_len,
          (!end ? TINFL_FLAG_HAS_MORE_INPUT : 0) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);

      // write or scan
      yylex();
    } else {
      blanks++;
    }
  } while(!end);

  // end zlib
}
