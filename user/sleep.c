#include "kernel/types.h"
#include "user.h"


int main(int argc, char *argv[])
{
    if(argc < 2){
        fprintf(2, "argv error\n");
        exit(0);
    }
    sleep(atoi(argv[2]));
    exit(0);
}
