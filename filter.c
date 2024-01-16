#include "helpers.h"
#include <math.h>
#include <stdio.h>
int min(i, j)
{
    if (i < j)
    {
        return i;
    }
    return j;
}
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int shade = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = shade;
            image[i][j].rgbtGreen = shade;
            image[i][j].rgbtRed = shade;
        }
    }
    return;
}

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);

            image[i][j].rgbtBlue = min(sepiaBlue, 255);
            image[i][j].rgbtGreen = min(sepiaGreen, 255);
            image[i][j].rgbtRed = min(sepiaRed, 255);
        }
    }
    return;
}
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp[height][width];
            temp[i][j] = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_blur[height][width];
    double avgRed, avgGreen, avgBlue;
    float counter;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            counter = 0;
            avgRed = 0;
            avgGreen = 0;
            avgBlue = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    int a = i + k;
                    int b = j + l;

                    if (a < height && b < width && a >= 0 && b >= 0)
                    {
                        avgRed = avgRed + image[a][b].rgbtRed;
                        avgGreen = avgGreen + image[a][b].rgbtGreen;
                        avgBlue = avgBlue + image[a][b].rgbtBlue;

                        counter++;
                    }
                }
            }
            avgRed = round(avgRed / counter);
            avgGreen = round(avgGreen / counter);
            avgBlue = round(avgBlue / counter);

            image_blur[i][j].rgbtRed = avgRed;
            image_blur[i][j].rgbtGreen = avgGreen;
            image_blur[i][j].rgbtBlue = avgBlue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_blur[i][j];
        }
    }
    return;
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxBlue = 0, gyBlue = 0, gxGreen = 0, gyGreen = 0, gxRed = 0, gyRed = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k < 0 || i + k > height - 1 || j + l < 0 || j + l > width - 1)
                    {
                        continue;
                    }
                    gxBlue += image[i + k][j + l].rgbtBlue * gx[k + 1][l + 1];
                    gyBlue += image[i + k][j + l].rgbtBlue * gy[k + 1][l + 1];
                    gxGreen += image[i + k][j + l].rgbtGreen * gx[k + 1][l + 1];
                    gyGreen += image[i + k][j + l].rgbtGreen * gy[k + 1][l + 1];
                    gxRed += image[i + k][j + l].rgbtRed * gx[k + 1][l + 1];
                    gyRed += image[i + k][j + l].rgbtRed * gy[k + 1][l + 1];
                }
            }
            int blue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));
            int green = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int red = round(sqrt(gxRed * gxRed + gyRed * gyRed));
            temp[i][j].rgbtBlue = min(blue, 255);
            temp[i][j].rgbtGreen = min(green, 255);
            temp[i][j].rgbtRed = min(red, 255);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}
