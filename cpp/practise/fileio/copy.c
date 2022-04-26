#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[]) {

	int inputFD;
	int outputFD;
	int openFlags;

	mode_t filePerms;
	ssize_t numRead;
	char buf[BUF_SIZE];

	if (argc != 3 || strcmp(argv[1], "--help") == 0)
		printf("%s Old-file New-file\n", argv[0]);

	/* OPEN INPUT & OUTPUT FILEs */
       inputFD = open(argv[1], O_RDONLY);
       if(inputFD == -1)
	       printf("Error opening file: %s\n", argv[1]);
	
	openFlags = O_CREAT | O_WRONLY | O_TRUNC;

	/* rw-rw-rw- */
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	
	outputFD = open(argv[2], openFlags, filePerms);
	if(outputFD == -1)
		printf("Error opening file: %s\n", argv[2]);

	/* TRANSFER DATA UNTIL WE ENCOUNTER END OF THE INPUT FILE OR ERROR */
	while((numRead = read(inputFD, buf, BUF_SIZE)) > 0)
		if(write(outputFD, buf, numRead) != numRead)
			printf("Could not write the whole buffer!\n");

	if(numRead == -1)
		printf("Error Reading\n");

	if(close(inputFD) == -1)
		printf("Error Closing Input File.\n");

	if(close(outputFD) == -1)
		printf("Error Closing Output File.\n");
	printf("\n");
	exit(EXIT_SUCCESS);
}
