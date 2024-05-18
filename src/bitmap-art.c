#include <stdio.h>
#include <stdbool.h>
//inlude for getopt
#include <unistd.h>
#include "create-bitmap.h"

//run -c create
// -w width
// -h height
// -c color
//-v view
//
//
int main(int argc, char *argv[])
{
    int length, width;
    char *color;
    int option;
    bool make_flag;
    char *file_name;
    
    // getopt is a gnu linux function and will return -1 once there is no more arguments
    while((option = getopt(argc, argv, "m:r:l:w:c:h")) != -1) {
        switch(option) {
            case 'm':
                make_flag = true; 
                file_name = optarg;
                break;
            case 'r':
                printf("reading bitmap of %s\n", optarg);
                break;
            case 'l':
                length = atoi(optarg);
                break;
            case 'w':
                width = atoi(optarg);
                break;
            case 'c':
                color = optarg;
                break;
            case 'h':
                printf("help menu\n");
                break;
            default:
                puts("nope");
            }
    }

    if(make_flag){
        make_bitmap(file_name, length, width, color);
    }

    printf("Bitmap created!\n");
    return 0;
}

