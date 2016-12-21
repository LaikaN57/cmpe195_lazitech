#include "tinfl.c"

int main() {
  void * in_next;
  void * out_start;
  void * out_next;
  int c, flags;
  size_t in, o;
  tinfl_decompressor decomp;
  tinfl_status status;

  tinfl_init(&decomp);

  flags = set/clear TINFL_FLAG_HAS_MORE_INPUT clear TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF

  // read 64 bytes
  // printf
  status = tinfl_decompress(&decomp, (const mz_uint8 *) in_next, &in, (mz_uint8 *) out_start, (mz_uint8 *) out_next, &o, flags);

}
