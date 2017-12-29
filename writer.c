#ifndef ___WRITER___
#define ___WRITER___

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define STANDARD_OUTPUT		"std"

int main(int argc, char* argv[]) {
    int c, fp, file_flag = 0;

    if (argc > 1 && (strcmp(argv[1], STANDARD_OUTPUT) != 0)) {

        fp = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);

        if (fp < 0) {
            fprintf(stderr, "Can't open output file");
            exit(1);
        }

		file_flag++;
        close(1);
        dup(fp);
    }

    while ((c = getchar()) != EOF)
    {
        printf("%c", c);
    }

    fflush(stdout);	//dump all chars left in buffer into output file

    if (file_flag) { //close opened file
        close(fp);
    }

    exit(0);

    /*int c;

//handle output to file
if (argc > 1 && (strcmp(argv[1], STANDARD_OUTPUT) != 0)) {
    FILE *f_out;

    f_out = fopen(argv[1], "w+");

    if (f_out < 0) {
        fprintf(stderr, "Can't open output file");
        exit(1);
    }

    while ((c = getchar()) != EOF) {
        fprintf(f_out,"%c", c);
    }

    fclose(f_out);
}
else { //handle output to sdt
    while ((c = getchar()) != EOF){
        printf("%c", c);
    }

    fflush(stdout);	//dump all chars left in buffer into output file
}

printf("writer exiting");*/
}

#endif // !___WRITER___
