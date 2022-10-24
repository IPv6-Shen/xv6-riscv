#include "kernel/types.h"
#include "user.h"

//0读 1写
void dfs(int fa[]){
    close(fa[1]);
    int st; //read the first prime
    if(read(fa[0], &st, 4) != 4){
        exit(0);
    }
    fprintf(1, "prime %d\n", st);
    int left[50];

    //process last number in the array
    int nxt, idx = 0;
    while(read(fa[0], &nxt, 4) == 4){
        if(nxt % st != 0){
            left[idx ++] = nxt;
        }
    }
    if(idx > 0){
        int p[2];    
        if(pipe(p) < 0){
            exit(1);
        }
        if(fork() == 0){
            dfs(p);
            exit(0);
        }
        close(p[0]);
        for(int i = 0; i < idx; ++i){
            write(p[1], &left[i], 4);
        }
        close(p[1]);
        wait(0);
    }
    close(fa[1]);
    exit(0);
}

int main(int argc, char* argv[])
{
    int n = 35;
    if(argc > 2){
        exit(1);
    }
    else if(argc == 2){
        n = atoi(argv[1]);
    }
    int p[2];
    if(pipe(p) < 0){
        exit(1);
    }
    int pid = fork();
    if(pid == 0){
        //child
        dfs(p);
        exit(0);
    }   
    //parent
    close(p[0]);

    for(int i = 2; i <= n; ++i){
        int ret = write(p[1], &i, 4);
        if(ret < 0){
            fprintf(2, "write erorr");
            exit(1);
        }
    }
    
    close(p[1]);
    wait(0);
    exit(0);
}
