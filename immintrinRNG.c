#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <immintrin.h>

int32_t rand32() {
	uint32_t r32 = 0;
	for (int i = 0; i < 100; ++i) {
		if ( _rdseed32_step(&r32) ) return (int32_t)r32;   //cast to signed because we want positive and negative ints
	}
	return 0;
}

int64_t rand64() {
	uint64_t r64 = 0;
	for (int i = 0; i < 100; ++i) {
		if ( _rdseed64_step(&r64) ) return (int64_t)r64;
	}
	return 0;
}

void print_results()   //Results from rand32() and rand64()
{
	printf("%"PRId32"\n", rand32());
	printf("%"PRId64"\n", rand64());
}

int main(int argc, char* argv[])
{
	char promptmsg[] = "Press enter to generate random 64 and 32 bit numbers. Say \"spam\" to output results 200 times.\n";
	printf("%s", promptmsg);
	char input[11];
	char enterpressed[] = "\0";
	char spam[] = "spam";
	while (1) {
		if ( fgets(input, sizeof(input), stdin ) != NULL ) {
			input[strcspn(input, "\n")] = '\0';
			if ( strcmp(input, enterpressed) == 0 ) {
				print_results();
			}
			else if ( strcmp(input, spam) == 0 ) {
				for (int i = 0; i < 200; i++) {
					printf("\n");
					print_results();
				}
			}
			else {
				system("cls");
				printf("%s", promptmsg);
			}
		}
	}
	return 0;
}
