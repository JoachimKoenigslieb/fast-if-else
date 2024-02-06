#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	u_int32_t test_case = atoi(argv[1]);
	u_int32_t max_check = atoi(argv[2]);

	int isOdd = 0;
	int isEven = 0;

	for (u_int32_t i = 1; i<max_check; i=i+2) {
		if (i == test_case) {
			isOdd += 1;
		}
	}

	// the max value we can have in whatever bit-width is 2**n - 1, this means we WILL skip over this
	for (u_int32_t i = 0; i<(max_check-1); i=i+2) {
		if (i == test_case) {
			// checking all the even numbers...
			isEven += 1;
		}
	}


	if (test_case == max_check) {
		isOdd += 1;
	}


	if (test_case == max_check - 1) {
		isEven += 1;
	}

	if (isEven) {
		printf("%d is even!\n", test_case);
	}

	if (isOdd) {
		printf("%d is odd!\n", test_case);
	}

    return 0;
}