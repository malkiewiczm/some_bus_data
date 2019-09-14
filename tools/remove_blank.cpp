#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Statistics {
	int total;
	int success;
	int skipped_ok;
	int skipped_fopen;
};

static inline void do_single_file(const char *const fname, Statistics *stat)
{
	++stat->total;
	FILE *f = fopen(fname, "r");
	if (f == nullptr) {
		++stat->skipped_fopen;
		return;
	}
	const size_t DIM = 1024;
	static char buf[DIM];
	size_t len = fread(buf, 1, DIM, f);
	size_t count = 0;
	for (size_t i = 0; i < len; ++i) {
		if (buf[i] == '\n')
			++count;
		if (count == 2) {
			break;
		}
	}
	fclose(f);
	if (count < 2) {
		unlink(fname);
		++stat->success;
	} else {
		++stat->skipped_ok;
	}
}

int main(int argc, char **argv)
{
	if (argc <= 1) {
		puts("needs at least one file as argument");
		return 1;
	}
	Statistics stat;
	bzero(&stat, sizeof(stat));
	for (int i = 1; i < argc; ++i) {
		do_single_file(argv[i], &stat);
	}
	printf("total %d\n", stat.total);
	printf("success %d\n", stat.success);
	if (stat.skipped_ok)
		printf("skipped %d\n", stat.skipped_ok);
	if (stat.skipped_fopen)
		printf("skipped (fopen error)%d\n", stat.skipped_fopen);
	return 0;
}
