#include "helpers.h"
#include <stdlib.h>

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int blue = rand() % 256;
        int red = rand() % 256;
        int green = rand() % 256;
        for (int j = 0; j < width; j++)
        {
            if (image[i][j].rgbtRed == 0x00 && image[i][j].rgbtGreen == 0x00 && image[i][j].rgbtBlue == 0x00)
            {
                image[i][j].rgbtBlue = blue;
                image[i][j].rgbtRed = red;
                image[i][j].rgbtRed = green;
            }
        }
    }
}
