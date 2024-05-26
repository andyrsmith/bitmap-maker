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

int get_padding_width(int byte_width);
int get_bitmap_size(int length, int padding_width, int byte_width);
