#include <stdio.h>
#include "tinfl.c"

int main(int argc, char ** argv) {
	if(argc < 3) {
		printf("fuck.\n");
		return 0;
	}

	FILE * a;
	FILE * b;

	a = fopen(argv[1], "r");
	b = fopen(argv[2], "w");

	tinfl_decompressor decomp;
	tinfl_status status;
	tinfl_init(&decomp);

	int c_in;
	char c, d;
	size_t one = 1;
	void *pOut_buf[32*1024];
	size_t out_buf_len = 32*1024;
	int flags = 0;

	// prime
	c_in = fgetc(a);
	if(c_in != EOF) {
		c = (char) c_in;
		do {
			// get a character
			d = c;
			c_in = fgetc(a);
			if(c_in != EOF) {
				c = c_in;
			}

			do {
				if(c_in != EOF) {
					flags = 0 | TINFL_FLAG_HAS_MORE_INPUT;
				} else {
					flags = 0 & ~(TINFL_FLAG_HAS_MORE_INPUT);
				}

				// attempt to decompress
				printf("pre:  %p %i %p %i\n", &d, one, pOut_buf, out_buf_len);
				status = tinfl_decompress(
						&decomp,
						(const mz_uint8*) &d,
						&one,
						(mz_uint8*) pOut_buf,
						(mz_uint8*) pOut_buf,
						&out_buf_len,
						flags & ~(TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)
				);
				printf("post: %p %i %p %i\n", &d, one, pOut_buf, out_buf_len);
				if(status | TINFL_STATUS_BAD_PARAM) { printf("bp "); }
				if(status | TINFL_STATUS_ADLER32_MISMATCH) { printf("am"); }
				if(status | TINFL_STATUS_FAILED) { printf("f "); }
				if(status | TINFL_STATUS_DONE) { printf("d "); }
				if(status | TINFL_STATUS_NEEDS_MORE_INPUT) { printf("nmi "); }
				if(status | TINFL_STATUS_HAS_MORE_OUTPUT) { printf("hmo "); }
				printf("\n");

			} while(0);
		} while(c_in != EOF);
	}

	fclose(a);
	fclose(b);

	return 0;
}
