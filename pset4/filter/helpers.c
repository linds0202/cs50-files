#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //find average of rgb values
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;
            
            
            int average = round((blue + green + red)/3);
            
            //assign average to each red green & blue
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = average;
            
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //array similar to 1 row
    RGBTRIPLE reflect[width];
    
    //iterate through 1 row @ a time
    for (int i = 0; i < height; i++)
    {
        //iterate 1 pixel in each column
        for (int j = 0; j < width / 2; j++)
        {
            //make temp copy of pixel
            RGBTRIPLE image_copy = image[i][j];
            //swap info of opposite pixels
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = image_copy;
            
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //make copy of original image to preserve rgb values
    RGBTRIPLE image_copy[height][width];
    
    //create copy of original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //initialize variables to hold total of rgb from surrounding pixels and # of pixels
            float sumR;
            float sumG;
            float sumB;
            int counter;
            
            //set to 0
            sumR = sumG = sumB = counter = 0;
            
            //loops to check 9 surrounding pixels
            for (int k = -1; k < 2; k++)
            {
                for (int m = -1; m < 2; m++)
                {
                    //check to see if outside # of rows
                    if (i + k < 0 || i + k >= height)
                    {
                        //doesn't count this pixel
                        continue;
                    }
                    
                    //check to see if outside width
                    if (j + m < 0 || j + m >= width)
                    {
                        //doesn't count this pixel
                        continue;
                    }
                    //otherwise add r g & b value to appropriate sum
                    else
                    {
                        sumR += image_copy[i + k][j + m].rgbtRed;
                        sumG += image_copy[i + k][j + m].rgbtGreen;
                        sumB += image_copy[i + k][j + m].rgbtBlue;
                        
                        //count the pixel
                        counter++;
                    }
                }
            }
            
            //get average and return it to the original image
            image[i][j].rgbtRed = round(sumR / counter);
            image[i][j].rgbtGreen = round(sumG / counter);
            image[i][j].rgbtBlue = round(sumB / counter);
        }
    }
    
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //make a copy of original
    RGBTRIPLE image_copy[height][width];
    
    //fill copy w/nested loop
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }
    
    //initialize sobel arrays
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    
    //loop through each pixel & calculate Gx & Gy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //initialize gx & gy for red, green & blue & set to 0
            float gx_red;
            float gx_green;
            float gx_blue;
            float gy_red;
            float gy_green;
            float gy_blue;
            
            gx_red = gx_green = gx_blue = gy_red = gy_green = gy_blue = 0;
            
            //check to see if surrounding pixels exist, if they do, calcuclate sobel #
            for (int k = -1; k < 2; k++)
            {
                for (int m = -1; m < 2; m++)
                {
                    //check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    //check if pixel is outside of colums
                    if (j + m < 0 || j + m >= width)
                    {
                        continue;
                    }
                    //if pixel exists, calculate
                    gx_red += image_copy[i + k][j + m].rgbtRed * Gx[k + 1][m + 1];
                    gx_green += image_copy[i + k][j + m].rgbtGreen * Gx[k + 1][m + 1];
                    gx_blue += image_copy[i + k][j + m].rgbtBlue * Gx[k + 1][m + 1];
                    gy_red += image_copy[i + k][j + m].rgbtRed * Gy[k + 1][m + 1];
                    gy_green += image_copy[i + k][j + m].rgbtGreen * Gy[k + 1][m + 1];
                    gy_blue += image_copy[i + k][j + m].rgbtBlue * Gy[k + 1][m + 1];
                }
            }
            //square and sum each for rgb
            int red = round(sqrt(gx_red * gx_red + gy_red * gy_red));
            int green = round(sqrt(gx_green * gx_green + gy_green * gy_green));
            int blue = round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue));
                    
            //check for > 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            
            //assing new value to original picture
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}

