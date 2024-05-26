#include "bitmap.h"

// determine how much padding is needed. Needs to be a multiple of 4 or 24 bytes
int get_padding_width(int byte_width) {
    return byte_width % 4 == 0 ? 0 : (4 - byte_width % 4);
}

int get_bitmap_size(int length, int byte_width, int padding_width) {
    return length * (byte_width+padding_width);
}
