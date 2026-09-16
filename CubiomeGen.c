#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <immintrin.h>

static int64_t rand64() {
	uint64_t r64 = 0;
	for (int i = 0; i < 100; ++i) {
		if ( _rdseed64_step(&r64) ) return (int64_t)r64;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int OutputCount = 100000;
	char input[10];
	char yes[2] = "y";
	char yesUpper[2] = "Y";
	printf("Write RNG results to text file in this directory? y/n\n");
	if ( fgets(input, sizeof(input), stdin) != NULL ) {
		input[strcspn(input, "\n")] = '\0';
		if ( strcmp(input, yes) == 0 || strcmp(input, yesUpper) == 0 ) 
		{
			FILE *outfile = fopen("out.txt", "w");
			if (outfile == NULL) {
				fprintf(stderr, "File not found.\n");
				return 1;
			}
			printf("Please wait......\n");
				for (int i = 0; i < OutputCount; ++i) {
					fprintf(outfile, "%" PRId64 "\n", rand64());
				}
			fclose(outfile);
		    printf("Operation completed.\n");
		}
		system("pause"); // I know don't say it.
	}

	return 0;
}
