//
//  main.cpp
//  compress
//
//  Created by Robin on 10/11/14.
//  Copyright (c) 2014 FRAD. All rights reserved.
//
// main.c

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include "Header.h"

#define SIZE 196662

#pragma pack(push, 1)
struct BMPHeader
{
    uint16_t signature;		// 0x4D42
    uint32_t size;				// unreliable
    uint16_t res0;				// reserved 0
    uint16_t res1;				// reserved 0
    uint32_t offset;			// to start of image
    uint32_t hdrsize;			// 40
    uint32_t width;
    uint32_t height;
    uint16_t planes;			// 1
    uint16_t bpp;					// 1, 4, 8 or 24
    uint32_t compress;		// 0 = none, 1 = rle-8, 2=rle-4
    uint32_t total;				// size in bytes incl padding
    uint32_t h_res;
    uint32_t v_res;
    uint32_t num_color;
    uint32_t imp_color;
};
#pragma pack(pop)

struct pixelstack
{
    int pixelnum;
    char R,G,B;
};

int main()
{
    FILE* file;
    struct BMPHeader header;
    
    file = fopen("/Users/robin/Documents/spelprogrammering/Compress_FRAD/compress/image.bmp", "rb");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, 0);

    char buffer[size], *pixels;
    fread(buffer, 1, size, file);
    fclose(file);
    
    memcpy(&header, buffer, sizeof(struct BMPHeader));
    pixels = buffer + header.offset;
    
    FILE* newfile;
    newfile = fopen("/Users/robin/Documents/spelprogrammering/Compress_FRAD/compress/image.FRAD", "wb");
    fwrite(&header, 1, sizeof(struct BMPHeader), newfile);
    struct pixelstack stack{1,pixels[0], pixels[1], pixels[2]};
    
    for (int i=3; i < size; i+=3)
    {
        if(pixels[i] != pixels[i-3] || pixels[i+1] != pixels[i-2] || pixels[i+2] != pixels[i-1])
        {
            fwrite(&stack, 1, sizeof(struct pixelstack), newfile);
            stack.R = pixels[i];
            stack.G = pixels[i+1];
            stack.B = pixels[i+2];
            stack.pixelnum = 1;
        }
        else
        {
            stack.pixelnum++;
        }
    }
    
    fwrite(&stack, 1, sizeof(struct pixelstack), newfile);
    fclose(newfile);
    
    struct BMPHeader headerd;
    
    FILE* decompfile;
    newfile = fopen("/Users/robin/Documents/spelprogrammering/Compress_FRAD/compress/image.FRAD", "rb");
    fseek(newfile, 0, SEEK_END);
    long newsize = ftell(file);
    fseek(newfile, 0, SEEK_SET);
    decompfile = fopen("/Users/robin/Documents/spelprogrammering/Compress_FRAD/compress/imagedecomp.bmp", "wb");
    
    
    
    fread(&headerd, 1, sizeof(struct BMPHeader), newfile);
    //memcpy(&headerd, bufferd, sizeof(struct BMPHeader));
    
    struct pixelstack stackd;
    
    fwrite(&headerd, 1, sizeof(struct BMPHeader),decompfile);
    
    
    for (int i = headerd.offset; i < newsize; i += sizeof(struct pixelstack))
    {
        fread(&stackd, 1, sizeof(struct pixelstack), newfile);
        char bufferd[stackd.pixelnum*3];
        for (int j=0; j < stackd.pixelnum*3; j++)
        {
            switch(j%3)
            {
                case 0:
                    bufferd[j] = stackd.R;
                    break;
                case 1:
                    bufferd[j] = stackd.G;
                    break;
                case 2:
                    bufferd[j] = stackd.B;
                    break;
                    
            }
        }
        fwrite(&bufferd, 1, sizeof(bufferd), decompfile);
    }
    fclose(newfile);
    fclose(decompfile);
    
    
    
    std::cin.get();
    return 0;
}