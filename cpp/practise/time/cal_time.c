#include <locale.h>
#include <time.h>
#include <sys/time.h>
#include "../lib/tlpi_hdr.h"

int main(int argc, char *argv[]) { system("clear");

	time_t t;
	t = time(NULL);
	printf("%s", ctime(&t));
	return 0;
}
