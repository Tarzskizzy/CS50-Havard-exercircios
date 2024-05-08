#include "helpers.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int media = 0;
    for (int hi = 0; hi < height; hi++){
        for (int wi = 0; wi < width; wi++){
            media = (image[hi][wi].rgbtRed + image[hi][wi].rgbtGreen + image[hi][wi].rgbtBlue)/3;
            image[hi][wi].rgbtRed = media;
            image[hi][wi].rgbtGreen = media;
            image[hi][wi].rgbtBlue = media;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tempRed;
    int tempGreen;
    int tempBlue;


    for (int hi = 0; hi < height; hi++){
        for (int wi = 0; wi < width/2; wi++){
            tempRed = image[hi][wi].rgbtRed;
            tempGreen = image[hi][wi].rgbtGreen;
            tempBlue = image[hi][wi].rgbtBlue;

            image[hi][wi].rgbtRed = image[hi][width-1-wi].rgbtRed;
            image[hi][wi].rgbtGreen = image[hi][width-1-wi].rgbtGreen;
            image[hi][wi].rgbtBlue = image[hi][width-1-wi].rgbtBlue;


            image[hi][width-1-wi].rgbtRed = tempRed;
            image[hi][width-1-wi].rgbtGreen = tempGreen;
            image[hi][width-1-wi].rgbtBlue = tempBlue;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurImage[height][width];

    //copiando as imagens
    for (int hi = 0; hi < height; hi++){
        for (int wi = 0; wi < width; wi++){
            blurImage[hi][wi].rgbtRed = image[hi][wi].rgbtRed;
            blurImage[hi][wi].rgbtGreen = image[hi][wi].rgbtGreen;
            blurImage[hi][wi].rgbtBlue = image[hi][wi].rgbtBlue;
        }
    }


    int mediaR = 0;
    int mediaG = 0;
    int mediaB = 0;
    int count = 0;

    //OBJETIVO coletar a média dos pixels que estão a 1 pixel de distáncia do pixel alvo
    for (int hi = 0; hi < height; hi++){
        for (int wi = 0; wi < width; wi++){
            //redefinição
            count = 0;
            int totalRed = 0;
            int totalGreen = 0;
            int totalBlue = 0;
            //cores do pixel atual
            for (int k = (hi-1); k <= (hi+1); k++){
                for (int l = (wi-1); l <= (wi+1); l++){
                    if ((k >= 0 && k <= (height - 1)) && (l >= 0 && l <= (width - 1)))
                    {
                        totalBlue += blurImage[k][l].rgbtBlue;
                        totalGreen += blurImage[k][l].rgbtGreen;
                        totalRed += blurImage[k][l].rgbtRed;
                        count++;
                    }
                }
            }

            mediaR = (int)round((double)totalRed/(double)count);
            mediaG = (int)round((double)totalGreen/(double)count);
            mediaB = (int)round((double)totalBlue/(double)count);

            image[hi][wi].rgbtRed = mediaR;
            image[hi][wi].rgbtGreen = mediaG;
            image[hi][wi].rgbtBlue = mediaB;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{//-e
    // RGBTRIPLE blurImage[height][width];
    // int Gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    // int Gy[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};

    // //copiando as imagens
    // for (int hi = 0; hi < height; hi++){
    //     for (int wi = 0; wi < width; wi++){
    //         blurImage[hi][wi].rgbtRed = image[hi][wi].rgbtRed;
    //         blurImage[hi][wi].rgbtGreen = image[hi][wi].rgbtGreen;
    //         blurImage[hi][wi].rgbtBlue = image[hi][wi].rgbtBlue;
    //     }
    // }

    // //OBJETIVO coletar a média dos pixels que estão a 1 pixel de distáncia do pixel alvo
    // for (int hi = 0; hi < height; hi++){
    //     for (int wi = 0; wi < width; wi++){
    //         //redefinição
    //         int countx = 0;
    //         int county = 0;
    //         //definindo as cores
    //         int totalRed = 0;
    //         int totalGreen = 0;
    //         int totalBlue = 0;
    //         //definindo os Kernels
    //         //X
    //         int totalGxR = 0;
    //         int totalGxG = 0;
    //         int totalGxB = 0;
    //         //Y
    //         int totalGyR = 0;
    //         int totalGyB = 0;
    //         int totalGyG = 0;
    //         //Cor final
    //         int MediaGR = 0;
    //         int MediaGG = 0;
    //         int MediaGB = 0;

    //         //cores do pixel atual
    //         for (int k = (hi-1); k <= (hi+1); k++){
    //             for (int l = (wi-1); l <= (wi+1); l++){
    //                 if ((k >= 0 && k <= (height - 1)) && (l >= 0 && l <= (width - 1)))
    //                 {
    //                     totalGxB += Gx[k][l]*(blurImage[k][l].rgbtBlue);
    //                     totalGxG += Gx[k][l]*(blurImage[k][l].rgbtGreen);
    //                     totalGxR += Gx[k][l]*(blurImage[k][l].rgbtRed);

    //                     totalGyB += Gy[k][l]*(blurImage[k][l].rgbtBlue);
    //                     totalGyG += Gy[k][l]*(blurImage[k][l].rgbtGreen);
    //                     totalGyR += Gy[k][l]*(blurImage[k][l].rgbtRed);
    //                 }
    //             }
    //         }

    //         MediaGR = (int)sqrt(pow(totalGxR,2.0)+pow(totalGyR,2.0));
    //         MediaGG = (int)sqrt(pow(totalGxG,2.0)+pow(totalGyG,2.0));
    //         MediaGB = (int)sqrt(pow(totalGxB,2.0)+pow(totalGyB,2.0));

    //         MediaGR = MediaGR > 255 ? 255 : MediaGR;
    //         MediaGB = MediaGB > 255 ? 255 : MediaGB;
    //         MediaGG = MediaGG > 255 ? 255 : MediaGG;

    //         image[hi][wi].rgbtRed = MediaGR;
    //         image[hi][wi].rgbtGreen = MediaGG;
    //         image[hi][wi].rgbtBlue = MediaGB;
    //     }
    // }

    //temp image
    RGBTRIPLE temp[height][width];

    //gx and gy kernels
    int gxarr[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int gyarr[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    //copying image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) //
        {
            temp[i][j] = image[i][j];
        }
    }

    //iterating through image
    for (int i = 0; i < height; i++)    //
    {
        for (int j = 0; j < width; j++)
        {
            //setting all gx and gy values to 0
            int gxred = 0;
            int gyred = 0;

            int gxblue = 0;
            int gyblue = 0;

            int gxgreen = 0;
            int gygreen = 0; //

            int countx = 0;
            int county = 0;

            //indexing through 3x3 grid surrounding pixel
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    //not counting pixels that arent in the boundary
                    if (k < 0 || l < 0 || k > height - 1 || l > width - 1)
                    {
                        countx++;
                        county++;
                        continue;
                    }

                    //updating gx and gy values according to  3x3 pixel
                    gxred += (gxarr[countx] * temp[k][l].rgbtRed);
                    gxblue += (gxarr[countx] * temp[k][l].rgbtBlue);
                    gxgreen += (gxarr[countx] * temp[k][l].rgbtGreen);

                    gyred += (gyarr[county] * temp[k][l].rgbtRed);
                    gyblue += (gyarr[county] * temp[k][l].rgbtBlue);        //
                    gygreen += (gyarr[county] * temp[k][l].rgbtGreen);

                    //index of gx gy kernel
                    countx++;
                    county++;

                }
            }

            //calculating gx and gy
            int gred = round(sqrt(pow(gxred, 2) + pow(gyred, 2)));
            int gblue = round(sqrt(pow(gxblue, 2) + pow(gyblue, 2)));   //
            int ggreen = round(sqrt(pow(gxgreen, 2) + pow(gygreen, 2)));

            //condition for gx or gy being above 255
            gred = gred > 255 ? 255 : gred;
            gblue = gblue > 255 ? 255 : gblue;
            ggreen = ggreen > 255 ? 255 : ggreen;

            //updating colour of pixel
            image[i][j].rgbtRed = gred;
            image[i][j].rgbtBlue = gblue;
            image[i][j].rgbtGreen = ggreen;

        }
    }

    return;
}
