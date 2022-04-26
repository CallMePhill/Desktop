//#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>



int main()
{
	int fd;
	fd = open("u-boot.bin", O_RDONLY);
	if (fd == -1){
		std::cout << "could not read"<< std::endl;
		return 1;
	}
	else
	{
		std::cout << " OK " << std::endl;
	}
	return 0;
}
