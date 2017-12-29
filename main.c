/**************************************************/
///					Include						///
/**************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/***************************************************/

/**************************************************/
///					Define						///
/**************************************************/
#define STD_IN               0
#define STD_OUT              1
#define STD_ERR              2
#define MAX_OUT_FILE_NAME   11

/***************************************************/

/**************************************************/
///					Prototyps					///
/**************************************************/
void do_parent(void);
void do_writer(char*);

/***************************************************/

/**************************************************/
///						Globals					///
/**************************************************/
int writer_pipe[2];

/***************************************************/

/**************************************************/
///						Main					///
/**************************************************/
int main(){
    int pid;
    char out_file[MAX_OUT_FILE_NAME];

    scanf("%s", out_file);
	fflush(NULL);
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

}

/***************************************************/

/**************************************************/
///				Implementations					///
/**************************************************/
void do_writer(char* out_file){
    close(writer_pipe[1]);
    close(STD_IN);
    dup(writer_pipe[0]);
    close(writer_pipe[0]);
    execl("writer.exe", "writer.exe", out_file, (char*) NULL);
    printf("error!!!! fail to exec");
    exit(1); //for exec failure
}

void do_parent(){
    int fd_stdout = dup(STD_OUT); //save for later

    close(writer_pipe[0]);
    close(STD_OUT);
    dup(writer_pipe[1]);
    close(writer_pipe[1]);

    //debug
    int c;
    c = getchar();
    while (c != EOF)
    {
        printf("%c", c);
        c = getchar();
    }

    //return output to prompt
    dup2(STD_OUT, fd_stdout);
    close(fd_stdout);
}

/***************************************************/