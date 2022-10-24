#include "kernel/types.h"
#include "user.h"

int main(int argc, char* argv[])
{
    int p[2];
    if(pipe(p) < 0){
        exit(1);
    }
    if(fork() == 0){
        //child write
        char buf;
        if(read(p[0], &buf, 1) == -1){
            exit(1);
        }
        fprintf(1, "%d: received ping\n", getpid());
        write(p[1], &buf, 1);
        close(p[0]);
        close(p[1]);
        exit(0);
    }
    else{
        //parent read
        char buf = 'a';
        write(p[1], &buf, 1);
        wait(0);
        read(p[0], &buf, 1);
        fprintf(1, "%d: received pong\n", getpid());
        close(p[0]);
        close(p[1]);
        exit(0);
    }

}
