#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

void find(char* dirName, char* fileName)
{    
    int fd;
    struct dirent de;
    struct stat st;

    char buf[512], *p;
    memset(buf, 0, sizeof buf);
    memmove(buf, dirName, strlen(dirName));
    p = buf+strlen(buf);
    *p++ = '/';
    
    if((fd = open(dirName, 0)) < 0){
        fprintf(2, "%s: cannot open\n", dirName);
        return;
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "%s: cannot stat\n", dirName);
        close(fd);
        return;
    }

    while(read(fd, &de, sizeof(de)) == sizeof(de)){
        if(de.inum == 0)    //目录下无文件
            continue;
        if(!strcmp(".", de.name) || !strcmp("..", de.name))   
            continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if(stat(buf, &st) < 0){
            printf("cannot stat %s\n", buf);
            continue;
        }
        if(st.type == T_FILE){
            if(!strcmp(de.name, fileName)){
                fprintf(1, "%s\n", buf);
            }
        }
        else if(st.type == T_DIR){
            find(buf, fileName);
        }

    }
    close(fd); 
    return;

}


int main(int argc, char* argv[])
{
    if(argc != 3){
        fprintf(2, "argv error\n");
        exit(1);
    }
    char* dirName = argv[1];
    char* fileName = argv[2];
    find(dirName, fileName);
    exit(0);

}
