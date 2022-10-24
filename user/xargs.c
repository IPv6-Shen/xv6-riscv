#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAXN 1024

int main(int argc, char* argv[]){
    if(argc < 2){
        fprintf(2, "argv error\n");
        exit(1);
    }    
    char *argvs[MAXARG];    //存放子进程的参数
    for(int i = 1; i < argc; ++i){
        argvs[i - 1] = argv[i];
    }
    char buf[MAXN];
    int stat = 1;
    while(stat){
        char c = 0;
        int buf_cnt = 0;
        int arg_begin = 0;
        int argv_cnt = argc - 1;

        /*读取一行*/
        while(1){
            if((stat = read(0, &c, 1)) == 0){
                exit(0);
            }
            if(c == ' ' || c == '\n'){
                buf[buf_cnt++] = '\0';
                argvs[argv_cnt++] = &buf[arg_begin];
                arg_begin = buf_cnt;
                if(c == '\n'){
                    break;
                }
            }
            else{
                buf[buf_cnt++] = c;
            }
        }
        
        argvs[argv_cnt] = 0;
        if(fork() == 0){
            exec(argvs[0], argvs);
        }
        else{
            wait(0);
        }

    }

    exit(0);
}
