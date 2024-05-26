#include <stdio.h>
#include <stdbool.h>
//inlude for getopt
#include <unistd.h>
#include "create-bitmap.h"
#include "read_bitmap.h"

//run -c create
// -w width
// -h height
// -c color
//-v view
//
//
//


int main(int argc, char *argv[])
{
    int length = 5;
    int width = 5;
    char *color = "red";
    int option;
    bool make_flag = false;
    bool read_flag = false;
    char *file_name;
    
    // getopt is a gnu linux function and will return -1 once there is no more arguments
    while((option = getopt(argc, argv, "m:r:l:w:c:h")) != -1) {
        switch(option) {
            case 'm':
                make_flag = true; 
                file_name = optarg;
                break;
            case 'r':
                read_flag = true;
                file_name = optarg;
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
                //TODO: Add help text
                printf("help menu\n");
                break;
            default:
            }
    }
    int return_code = 0;

    if(make_flag && read_flag) {
        printf("Please only either -r or -m, not both\n");
    } else if(make_flag && !read_flag){
        return_code = make_bitmap(file_name, length, width, color);
    } else if(read_flag && !make_flag) {
        return_code = read_bitmap(file_name);
    } else {
        printf("Please pass in either -r(read) or -m(make)\n");
    }

    return return_code;
}
