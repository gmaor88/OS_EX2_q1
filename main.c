/**************************************************/
///					Include						///
/**************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "polygon.h"

/***************************************************/

/**************************************************/
///					Define						///
/**************************************************/
#define MAX_OUT_FILE_NAME   11
#define STD_IN              0
#define STD_OUT             1
#define STD_ERR             2
#define READ                0
#define WRITE               1
#define TRUE                1
#define MSB_SHIFT           32
#define READER_32           32

/***************************************************/

/**************************************************/
///					Prototyps					///
/**************************************************/
void do_parent(void);
void do_writer(char*);
void do_reader64(void);
void do_reader32(void);
void handle_readers_creation_and_output_redirection(void);
void close_remaining_pipes(void);

/***************************************************/

/**************************************************/
///						Globals					///

/**************************************************/
int writer_pipe[2];
int poly_p[2], r_64_p[2], r_32_p[2];


/***************************************************/

/**************************************************/
///						Main					///
/**************************************************/
int main(){
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);

    int pid;
    char out_file[MAX_OUT_FILE_NAME];

    scanf("%s", out_file);
    pipe (writer_pipe);
    pid = fork();

    if(pid < 0){
        perror("fork failure");
        exit(1);
    }
    else if(pid == 0){
        do_writer(out_file);
    }
    else{
        do_parent();
    }

    return 0;
}

/***************************************************/

/**************************************************/
///				Implementations					///
/**************************************************/
void do_writer(char* out_file){
    close(writer_pipe[WRITE]);
    close(STD_IN);
    dup(writer_pipe[READ]);
    close(writer_pipe[READ]);
    execl("writer.exe", "writer.exe", out_file, (char*) NULL);
    printf("error!!!! fail to exec");
    exit(1); //for exec failure
}

void do_parent(){
    handle_readers_creation_and_output_redirection();

    int input_type, reader_to_call = r_64_p[WRITE];
    long long unsigned polygon;

    while (TRUE)
    {
        scanf("%d", &input_type);
        if(input_type == READER_32){
            reader_to_call = r_32_p[WRITE];
        }

        write(reader_to_call, &input_type, sizeof(input_type));
        read(poly_p[READ], &polygon, sizeof(polygon));
        analyze_and_exec(polygon);
        if (is_end_of_input(polygon)) {
            break;
        }
    }

    free_list();
    close_remaining_pipes();
    dup(STD_ERR);   //return output to prompt
    printf("main_process pid=%d is going to exit\n", getpid());
}

void handle_readers_creation_and_output_redirection(){
    close(writer_pipe[READ]);

    pipe(r_64_p);
    pipe(poly_p);
    int pid = fork();

    if(pid < 0){
        perror("fork failure");
        exit(1);
    }

    if(pid == 0){
        do_reader64();
    }

    close(r_64_p[READ]);
    pipe(r_32_p);
    pid = fork();
    if(pid < 0){
        perror("fork failure");
        exit(1);
    }

    if(pid == 0){
        do_reader32();
    }

    close(r_32_p[READ]);
    close(poly_p[WRITE]);
    close(STD_OUT);
    dup(writer_pipe[WRITE]);
    close(writer_pipe[WRITE]);
}

void do_reader64() {
    close(writer_pipe[WRITE]);
    close(poly_p[READ]);
    close(r_64_p[WRITE]);

    int sign;
    long long unsigned poly;

    while(TRUE){
        int byte_count = read(r_64_p[READ], &sign, sizeof(sign));

        if(byte_count <= 0){
            break;
        }

        scanf("%llx", &poly);
        write(poly_p[WRITE], &poly, sizeof(poly));
    }

    close(poly_p[WRITE]);
    close(r_64_p[READ]);
    fprintf(stderr, "reader64 pid=%d is going to exit\n", getpid());
    exit(0);
}

void do_reader32() {
    close(writer_pipe[WRITE]);
    close(poly_p[READ]);
    close(r_32_p[WRITE]);
    close(r_64_p[WRITE]);

    int sign;
    long long unsigned poly = 0, lsb = 0, msb = 0;

    while(TRUE){
        int byte_count = read(r_32_p[READ], &sign, sizeof(sign));

        if(byte_count <= 0){
            break;
        }

        scanf("%llx %llx", &lsb, &msb);
        poly = (msb << MSB_SHIFT) | lsb;
        write(poly_p[WRITE], &poly, sizeof(poly));
    }

    close(poly_p[WRITE]);
    close(r_32_p[READ]);
    fprintf(stderr, "reader32 pid=%d is going to exit\n", getpid());
    exit(0);
}

void close_remaining_pipes(){
    close(STD_OUT); //close last pointer to writer_pipe.
    wait(NULL); //writer
    close(r_64_p[WRITE]);
    close(poly_p[READ]);
    wait(NULL); //reader 64
    close(r_32_p[WRITE]);
    wait(NULL); //reader 32
}

/***************************************************/