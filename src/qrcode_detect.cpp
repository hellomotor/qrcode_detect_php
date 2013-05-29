#include <stdio.h>
#include <stdlib.h>

//extern "C" const char *single_detect_file(const char *filename, int *hresult);
extern "C" const char *single_detect_file(const char *filename, bool pure_barcode, int *hresult);

int main(int argc, char **argv)
{
	if (argc < 3) {
		printf("usage: %s <image file> <purebarcode>\n", argv[0]);
		return 1;
	}
	int hresult = 1;
	bool pure_barcode = atoi(argv[2]);
	const char *result = single_detect_file(argv[1], pure_barcode, &hresult);
	if (result)
		fprintf(stdout, "%s\n", result);
	else
		fprintf(stderr, "%s decode failed, %d\n", argv[1], hresult);

	return 0;
}
