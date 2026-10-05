#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <immintrin.h>
#include <time.h>

static int64_t rand64() {
	uint64_t r64 = 0;
	if ( _rdrand64_step(&r64) ) return (int64_t)r64;
	else {
		printf("Error: rolling 0.\n");
		return 0;
	}
}

int main(int argc, char *argv[])
{
	int OutputCount = 100000000;
	char input[10];
	char yes[2] = "y";
	char yesbutloud[2] = "Y";
	printf("Write RNG results to text file in this directory? out.txt y/n\n");
	if ( fgets(input, sizeof(input), stdin) != NULL ) {
		input[strcspn(input, "\n")] = '\0';
		if ( strcmp(input, yes) == 0 || strcmp(input, yesbutloud) == 0 ) 
		{
			clock_t start, end;
			double time_elapsed;
			start = clock();
			FILE *outfile = fopen("out.txt", "w");
			if (outfile == NULL) return 1;
			size_t buffSize = 64 * 1024;
			char *buffer = malloc(buffSize);
			setvbuf(outfile, buffer, _IOFBF, buffSize);
			printf("Please wait . . . . . .\n");
			for (int i = 0; i < OutputCount; ++i) {
				fprintf(outfile, "%" PRId64 "\n", rand64());
			}
			fclose(outfile);
			free(buffer);
			end = clock();
			time_elapsed = (double) (end - start) / CLOCKS_PER_SEC;
			printf("Operation completed in %.3f seconds.\n", time_elapsed);
		}
		system("pause");
	}

	return 0;
}
