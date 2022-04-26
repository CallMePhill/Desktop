#include <signal.h>
#include "../lib/tlpi_hdr.h"

static void sigHandler(int sig) {
	printf("\nOuch!\n%d\n", sig); /* UNSAFE (see Section 21.1.2) */
}

int main(int argc, char *argv[]) { system("clear");
	int j;
	if (signal(SIGINT, sigHandler) == SIG_ERR)
		printf("signal");
	for (j = 0; ; j++) {
		printf("%d\n", j);
		sleep(3); /* Loop slowly... */
	}
	return 0;
}

