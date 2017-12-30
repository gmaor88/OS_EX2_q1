#ifndef ___WRITER___
#define ___WRITER___

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define STANDARD_OUTPUT		"std"
#define STDOUT				1
#define TRUE				1
#define	BUFF_SIZE			256

int main(int argc, char* argv[]) {
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
	char buff[BUFF_SIZE];
	int fp, byte_count;

    if (argc > 1 && (strcmp(argv[1], STANDARD_OUTPUT) != 0)) {

        fp = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);

        if (fp < 0) {
            perror("ERROR: Can't open output file.\n");
            exit(1);
        }
		
        close(STDOUT);
        dup(fp);
    }

	while(TRUE)
	{
		byte_count = read(0, buff, BUFF_SIZE);
		if(byte_count == 0)
		{
			exit(0);
		}
		
		if(byte_count < 0)
		{
			perror("ERROR: Failure in read.\n");  // illegal value 
			exit(1);	
		}
			
		if(write(1, buff, byte_count) != byte_count)
		{
			perror("ERROR: Failure in write.\n");
			exit(1);	
		}	
	}
    exit(0);
}

#endif // !___WRITER___
