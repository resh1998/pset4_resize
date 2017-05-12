
#include <stdio.h>

#include <stdlib.h>



#include "bmp.h"



int main(int argc, char* argv[])

{

    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: resize size infile outfile\n");
        return 1;
    }

    // remember the scale to resize the image
    int size = atoi(argv[1]);

    // ensure scale is a positive number lass than 100
    if (size > 100 || size < 1)
    {
        printf("Scale must be a positive int less than or equal to 100\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");

    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");

    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 

        bi.biBitCount != 24 || bi.biCompression != 0)
    {

        fclose(outptr);

        fclose(inptr);

        fprintf(stderr, "Unsupported file format.\n");

        return 4;

    } 

    
}