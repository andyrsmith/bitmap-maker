# Bitmap Art

CLI application to create and read Bitmap images.

Wanted to get a better understanding of how binary files worked so I created this program to create and read bitmap files.  Bitmap file format is one of the simpler file formats around.

## Compatibily

Should work on any Linux CLI, maybe Mac OS(haven't tested it), and will not probably not work in Windows CLI.

## Build

Run command

```
make all
```

To create the binary file.

## Usage

Can either create or read bitmap files.

### Create

To create pass in the -m with the name of the file to create.

-m: create
-l: number of pixels in length
-w: number of pixels wide
-c: color of image to create.  (color can be either red, orange, black, white, green, or yellow)

Example: bitmap-art -m new.bmp -l 50 -w 50 -c red

This will create a red bitmap image 50 pixels x 50 pixels

### Read

Coming soon

## Bitmap file format

Like most binary file format the bitmap file format consist of header to tell what kind of file it is and other information 

Header
Hex offset  | Number of bytes| Description                               |
OO          | 2 bytes        | file Identifier.  (BM for windows Bitmap) |
02          | 4 bytes        | Size of Bitmap  |
06          | 2 bytes        | reserved.  Can be 0 | 
08          | 2 bytes        | reserved.  Can be 0 |
0A          | 4 bytes        | Starting address where pixel array can be found.(where the image starts) |

Bitmap Info Header

Hex offset | Number of bytes | Description |
0E         | 4 bytes         | size of the header
12         | 4 bytes         | bitmap width
16         | 4 bytes         | bitmap height
1A         | 2 bytes         | number of color planes (always 1)
1C         | 2 bytes         | Number of bits per pixels.  Values could be 1, 4, 8, 16, 24, 32.  I used 24
1E         | 4 bytes         | Compression method used (didn't used this.  Just set to 0)
22         | 4 bytes         | image size.  Size of pixel data
26         | 4 bytes         | horizontal resolution
2A         | 4 bytes         | vertical resolution
2E         | 4 bytes         | number of colors in color palette
32         | 4 bytes         | number of import colors used

Pixel Data

Since I specified 24 bits for number of bits per pixel on address 1C 3 bytes were used to determine color of each pixel in RGB, since this is in little endian the bits are reversed.  Blue Green then red.

Red would be 00 00 FF.

Each row needs to end in a mutliple of 4, so if the row is 3 pixels long and each pixels is 3 bytes that would give us 9 bytes.  We need to add 3 bytes 00 bytes to get to 12. Otherwise the image would be appear mutli color.


