#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bitmap.h"

void print_ascii(int grayscale);
void read_file(FILE *bitmap);

int read_bitmap(char *file_name) 
{
    FILE *bitmap = fopen(file_name, "rb");
    if(bitmap == NULL) {
        printf("No file of that name exists\n");
        return 1;
    }

    char image_type[2];

    fread(&image_type, sizeof(image_type), 1, bitmap);

    //should exit if BM is not found
    if(image_type[0] == 'B' && image_type[1] == 'M') {
        read_file(bitmap);
    } else {
        printf("File is not a bitmap\n");
        return 1;
    }
    fclose(bitmap);
    return 0;
}

void read_file(FILE *bitmap) {
    fseek(bitmap, sizeof(int) * 4, SEEK_CUR);
        int width, height;

    fread(&width, sizeof(int), 1, bitmap);
    fread(&height, sizeof(int), 1, bitmap);

    int byte_width = width * 3;
    int padding_width = get_padding_width(byte_width);
    int bitmap_size = get_bitmap_size(height, byte_width, padding_width);

    fseek(bitmap, 54, SEEK_SET);
    
    uint8_t *bitmap_array = malloc(bitmap_size);

    if(bitmap_array != NULL) {
        fread(bitmap_array, bitmap_size, 1, bitmap);
        
        for(int i = 0; i < height; i++) {
            printf(" ");
            for(int j = 0; j<byte_width; j+=3) {
                int indx = (i*(byte_width+padding_width)) + j;
                uint8_t blue = bitmap_array[indx];
                uint8_t green = bitmap_array[indx+1];
                uint8_t red = bitmap_array[indx+2];

                //since ascii is made from black images on a white background need to convert colors to grayscal first
                //This is the pixel instensity of gray values
                int grayscale = 0.2989 * red + 0.5870 * green + 0.1140 *blue; 
                print_ascii(grayscale);
            }
            printf(" \n");
        }
        free(bitmap_array);
    } else {
        printf("Unable to allocate memory!\n");
    }
}

void print_ascii(int grayscale) {

    if(grayscale >= 0 && grayscale <= 25) printf("#");
    else if(grayscale > 25 && grayscale <= 50) printf("$");
    else if(grayscale > 50 && grayscale <= 75) printf("O");
    else if(grayscale > 75 && grayscale <= 100) printf("=");
    else if(grayscale > 100 && grayscale <= 125) printf("+");
    else if(grayscale > 125 && grayscale <= 150) printf("|");
    else if(grayscale > 150 && grayscale <= 175) printf("-");
    else if(grayscale > 175 && grayscale <= 200) printf("^");
    else if(grayscale > 200 && grayscale <= 225) printf(".");
    else if(grayscale > 225 && grayscale <= 250) printf("@");
    else printf(" ");
}
