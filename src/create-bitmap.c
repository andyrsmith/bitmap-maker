#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "create-bitmap.h"

typedef struct BITMAP_HEADER {
    int file_size;
    int reserved;
    int file_offset;
} bitmap_header;

typedef struct INFO_HEADER {
    int header_size;
    int width;
    int height;
    short int color_plane;
    short int bit_count;
    int compression;
    int image_size;
    int horizontal_resolution;
    int vertical_resolution;
    int color_palette;
    int important_color;
} info_header;

void make_bitmap(char *file_name, int length, int width, char *color) 
{
    
    bitmap_header bmp_header;
    info_header info_h;

    char image_type[2] = {
        'B',
        'M'
    };
    bmp_header.reserved = 0x00; // 4 bytes
    bmp_header.file_offset = 0x36; // 4 bytes
    info_h.header_size = 0x28;
    info_h.width = width;
    info_h.height = length;
    info_h.color_plane = 1;
    info_h.bit_count = 24;
    info_h.compression = 0x00;
    info_h.image_size = 0x00;
    info_h.horizontal_resolution = 0x002e23;
    info_h.vertical_resolution = 0x002e23;
    //gimp had value of 10
    info_h.color_palette = 0x00;
    info_h.important_color = 0x00;

    char bm_color[3];
    get_hex_color(color, bm_color);

    int byte_width = width * 3;
    // determine how much padding is needed. Needs to be a multiple of 4 or 24 bytes
    int padding_width = byte_width % 4 == 0 ? 0 : (4 - byte_width % 4);
    int bitmap_size = length * (byte_width+padding_width);
    //true calloc might not need line 131
    char *color_arr = malloc(bitmap_size * sizeof(char));

    int bm_counter = 0;
    for(int i = 0; i < length * (byte_width+padding_width); i++) color_arr[i] = 0;
    for(int i = 0; i < length; i++) {
        //interate through the width but not the padding
        for(int j = 0; j < byte_width; j++) {
           color_arr[(i * (byte_width+ padding_width)) + j] = bm_color[bm_counter];
           if(bm_counter >= 2) {
              bm_counter = 0;
            } else {
               bm_counter++;
            }
        }
    }
    bmp_header.file_size = sizeof(image_type) + sizeof(bmp_header) + sizeof(info_h) + bitmap_size;
    FILE *bitmap = fopen(file_name, "w+");
    fwrite(&image_type , sizeof(image_type), 1, bitmap);
    fwrite(&bmp_header, sizeof(bitmap_header), 1, bitmap);
    fwrite(&info_h, sizeof(info_header), 1, bitmap);
    // why can't I do &color_arr
    fwrite(color_arr, bitmap_size * sizeof(char), 1, bitmap);
    fclose(bitmap);
    free(color_arr);

}

void get_hex_color(char *color, char *hex_color){
    // red ff0000
    // blue 0000ff
    // black 000000
    // green 00ff00
    // orange ffA500
    // white ffffff
    // purple 800080
    // pink ffc0cb
    // yellow ffff00
    if(strcmp(color, "red") == 0) {
        printf("in here");
        hex_color[2] = 0xff;
    } else if(strcmp(color, "blue") == 0) {
        hex_color[0] = 0xff;
    } else if(strcmp(color, "green") ==0) {
        hex_color[1] = 0xff;
    } else if(strcmp(color, "orange") ==0) {
        hex_color[1] = 0xa5;
        hex_color[2] = 0xff;
    } else if(strcmp(color, "white") == 0) {
        hex_color[0] = 0xff;
        hex_color[1] = 0xff;
        hex_color[2] = 0xff;
    } else if(strcmp(color, "purple") == 0) {
        hex_color[0] = 0x80;
        hex_color[2] = 0x80;
    } else if(strcmp(color, "pink") == 0) {
        hex_color[0] = 0xcb;
        hex_color[1] = 0xc0;
        hex_color[2] = 0xff;
    } else if(strcmp(color, "yellow") ==0) {
        hex_color[1] = 0xff;
        hex_color[2] = 0xff;
    } else {
        printf("Color not found, black selected\n");
    }
}
