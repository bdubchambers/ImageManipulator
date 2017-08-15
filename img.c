/*
 * img.c
 *
 *  Created on: Apr 7, 2016
 *      Author: Brandon Chambers
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*CHANGE THIS TO YOUR PREFERRED TEST FILE*/
#define BMP_FILE "test.bmp"

/*function prototypes*/
//all in main acceptable this time
int main(void)
{
    //for eclipse console debug
    setvbuf(stdout, NULL, _IONBF, 0);

    //counter variable (row, col, etc...)
    unsigned int r, c, i;

    /*File pointers for input bitmaps.
     Change Constant @ #define BMP_FILE.
     */
    FILE *inbmp = fopen(BMP_FILE, "rb");
    FILE *inbmp2 = fopen(BMP_FILE, "rb");
    FILE *inbmp3 = fopen(BMP_FILE, "rb");
    FILE *inbmp4 = fopen(BMP_FILE, "rb");

    //File pointers for output of manipulated bitmaps
    FILE *quad = fopen("quad.bmp", "wb");
    FILE *reflect = fopen("reflect.bmp", "wb");
    FILE *warhol = fopen("warhol.bmp", "wb");

    /* first two junk bytes of header into header1,
     * filesize data into an int filesize
     * 12 more junk bytes into header2
     * 4 byte bmpWidth
     * 4 byte bmpHeight
     * and finally the last 28 junk bytes into header3
     */
    unsigned char header1[2];
    unsigned int filesize;
    unsigned char header2[12];
    unsigned int bmpWidth;
    unsigned int bmpHeight;
    unsigned char header3[28];
    //quad
    unsigned char header1_q[2];
    unsigned int filesize_q;
    unsigned char header2_q[12];
    unsigned int bmpWidth_q;
    unsigned int bmpHeight_q;
    unsigned char header3_q[28];
    //reflect
    unsigned char header1_ref[2];
    unsigned int filesize_ref;
    unsigned char header2_ref[12];
    unsigned int bmpWidth_ref;
    unsigned int bmpHeight_ref;
    unsigned char header3_ref[28];
    //warhol
    unsigned char header1_war[2];
    unsigned int filesize_war;
    unsigned char header2_war[12];
    unsigned int bmpWidth_war;
    unsigned int bmpHeight_war;
    unsigned char header3_war[28];

    //now read in the above header info from
    fread(header1, sizeof(char), 2, inbmp);
    fread(&filesize, sizeof(char), 4, inbmp);
    fread(header2, sizeof(char), 12, inbmp);
    fread(&bmpWidth, sizeof(char), 4, inbmp);
    fread(&bmpHeight, sizeof(char), 4, inbmp);
    fread(header3, sizeof(char), 28, inbmp);

    fread(header1_q, sizeof(char), 2, inbmp2);
    fread(&filesize_q, sizeof(char), 4, inbmp2);
    fread(header2_q, sizeof(char), 12, inbmp2);
    fread(&bmpWidth_q, sizeof(char), 4, inbmp2);
    fread(&bmpHeight_q, sizeof(char), 4, inbmp2);
    fread(header3_q, sizeof(char), 28, inbmp2);

    fread(header1_ref, sizeof(char), 2, inbmp3);
    fread(&filesize_ref, sizeof(char), 4, inbmp3);
    fread(header2_ref, sizeof(char), 12, inbmp3);
    fread(&bmpWidth_ref, sizeof(char), 4, inbmp3);
    fread(&bmpHeight_ref, sizeof(char), 4, inbmp3);
    fread(header3_ref, sizeof(char), 28, inbmp3);

    fread(header1_war, sizeof(char), 2, inbmp4);
    fread(&filesize_war, sizeof(char), 4, inbmp4);
    fread(header2_war, sizeof(char), 12, inbmp4);
    fread(&bmpWidth_war, sizeof(char), 4, inbmp4);
    fread(&bmpHeight_war, sizeof(char), 4, inbmp4);
    fread(header3_war, sizeof(char), 28, inbmp4);

    /*
     * Now that we have read in the pertinent header
     * info, like dimensions and size, we can create
     * our 2D char arrays that will hold the manipulated
     * bytes to output a new bitmap.
     */
    unsigned char bmpOriginal[bmpHeight][bmpWidth * 3];
    unsigned char bmpArrQuad[bmpHeight_q * 2][bmpWidth_q * 3 * 2];
    unsigned char bmpArrReflect[bmpHeight_ref][bmpWidth_ref * 3 * 2];

    fread(bmpOriginal, sizeof(char), filesize - 54, inbmp);
    fread(bmpArrQuad, sizeof(char), filesize_q - 54, inbmp2);
    fread(bmpArrReflect, sizeof(char), (filesize_ref - 54), inbmp);

    //-----------------------------------------------------------

    //quad logic
    for (r = 0; r < bmpHeight; r++)
    {
        i = 1;
        for (c = 0; c < ((bmpWidth * 2) * 3); c += 3, i += 3)
        {
            bmpArrQuad[r + bmpHeight_q][c] = bmpOriginal[r][c];
            bmpArrQuad[r + bmpHeight_q][c + 1] = bmpOriginal[r][c + 1];
            bmpArrQuad[r + bmpHeight_q][c + 2] = bmpOriginal[r][c + 2];

            bmpArrQuad[r][c] = bmpOriginal[r][c];
            bmpArrQuad[r][c + 1] = bmpOriginal[r][c + 1];
            bmpArrQuad[r][c + 2] = bmpOriginal[r][c + 2];
        }
    }

    filesize_q -= 54;
    filesize_q *= 4;
    bmpWidth_q *= 2;
    bmpHeight_q *= 2;
    fwrite(header1_q, sizeof(char), 2, quad);
    fwrite(&filesize_q, sizeof(char), 4, quad);
    fwrite(header2_q, sizeof(char), 12, quad);
    fwrite(&bmpWidth_q, sizeof(char), 4, quad);
    fwrite(&bmpHeight_q, sizeof(char), 4, quad);
    fwrite(header3_q, sizeof(char), 28, quad);
    fwrite(bmpArrQuad, sizeof(char), filesize_q, quad);

    //-----------------------------------------------------------

    //reflect logic
    for (r = 0; r < bmpHeight; r++)
    {
        i = 1;
        for (c = bmpWidth * 3; c < ((bmpWidth * 2) * 3); c += 3, i += 6)
        {
            bmpArrReflect[r][c] = bmpOriginal[r][c - (i + 2)];
            bmpArrReflect[r][c + 1] = bmpOriginal[r][c - (i + 1)];
            bmpArrReflect[r][c + 2] = bmpOriginal[r][c - (i)];

            bmpArrReflect[r][c - (bmpWidth * 3)] = bmpOriginal[r][c
                    - (bmpWidth * 3)];
            bmpArrReflect[r][c - (bmpWidth * 3) + 1] = bmpOriginal[r][c
                    - (bmpWidth * 3) + 1];
            bmpArrReflect[r][c - (bmpWidth * 3) + 2] = bmpOriginal[r][c
                    - (bmpWidth * 3) + 2];
        }
    }

    filesize_ref -= 54;
    filesize_ref *= 2;
    bmpWidth_ref *= 2;
    fwrite(header1_ref, sizeof(char), 2, reflect);
    fwrite(&filesize_ref, sizeof(char), 4, reflect);
    fwrite(header2_ref, sizeof(char), 12, reflect);
    fwrite(&bmpWidth_ref, sizeof(char), 4, reflect);
    fwrite(&bmpHeight_ref, sizeof(char), 4, reflect);
    fwrite(header3_ref, sizeof(char), 28, reflect);
    fwrite(bmpArrReflect, sizeof(char), filesize_ref, reflect);

    //-----------------------------------------------------------

    //warhol logic
    for (r = 0; r < bmpHeight; r++)
    {
        i = 1;
        for (c = 0; c < ((bmpWidth * 2) * 3); c += 3, i += 3)
        {
            //Lower Left Quadrant
            bmpArrQuad[r][c] = bmpOriginal[r][i + 2] + 64;
            bmpArrQuad[r][c + 1] = bmpOriginal[r][i + 1];
            bmpArrQuad[r][c + 2] = bmpOriginal[r][i + 1];

            if (c > bmpWidth * 3)
            {
                //Lower Right Quadrant
                bmpArrQuad[r][c] = bmpOriginal[r][i] - 50;
                bmpArrQuad[r][c + 1] = bmpOriginal[r][i] - 20;
                bmpArrQuad[r][c + 2] = bmpOriginal[r][i + 1] + 20;
            }
            //Upper Right Quadrant
            bmpArrQuad[r + bmpHeight][c] = bmpOriginal[r][i + 2];
            bmpArrQuad[r + bmpHeight][c + 1] = bmpOriginal[r][i + 2] + 84;
            bmpArrQuad[r + bmpHeight][c + 2] = bmpOriginal[r][i + 2];
        }
    }
    for (r = bmpHeight; r < bmpHeight * 2; r++)
    {
        i = 0;
        for (c = 0; c < ((bmpWidth) * 3); c += 3, i += 3)
        {
            //Upper left Quadrant
            bmpArrQuad[r][c] = bmpArrQuad[r][i + 1];
            bmpArrQuad[r][c + 1] = bmpArrQuad[r][i + 2];
            bmpArrQuad[r][c + 2] = bmpArrQuad[r][i];

        }
    }

    filesize_war -= 54;
    filesize_war *= 4;
    bmpWidth_war *= 2;
    bmpHeight_war *= 2;
    fwrite(header1_war, sizeof(char), 2, warhol);
    fwrite(&filesize_war, sizeof(char), 4, warhol);
    fwrite(header2_war, sizeof(char), 12, warhol);
    fwrite(&bmpWidth_war, sizeof(char), 4, warhol);
    fwrite(&bmpHeight_war, sizeof(char), 4, warhol);
    fwrite(header3_war, sizeof(char), 28, warhol);
    fwrite(bmpArrQuad, sizeof(char), filesize_war, warhol);

    //-----------------------------------------------------------
    fclose(inbmp);
    fclose(inbmp2);
    fclose(inbmp3);
    fclose(inbmp4);
    return 0;
}
