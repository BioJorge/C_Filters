#include "helpers.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE average[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            average[h][w].rgbtBlue = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed)/3);
            average[h][w].rgbtGreen = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed)/3);
            average[h][w].rgbtRed = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed)/3);

            image[h][w].rgbtBlue = average[h][w].rgbtBlue;
            image[h][w].rgbtGreen = average[h][w].rgbtGreen;
            image[h][w].rgbtRed = average[h][w].rgbtRed;
        }
    }
}

{
    int average[height - 1][width - 1];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // if all channels are 255, then is already white
            if (image[h][w].rgbtBlue == 0xff && image[h][w].rgbtGreen == 0xff && image[h][w].rgbtRed == 0xff)
            {
                image[h][w].rgbtBlue = 0xff;
                image[h][w].rgbtGreen = 0xff;
                image[h][w].rgbtRed = 0xff;
            }
            // if all channels are 0, then is already black
            else if (image[h][w].rgbtBlue == 0x00 && image[h][w].rgbtGreen == 0x00 && image[h][w].rgbtRed == 0x0)
            {
                image[h][w].rgbtBlue = 0x00;
                image[h][w].rgbtGreen = 0x00;
                image[h][w].rgbtRed = 0x00;
            }
            else
            {
                // if not white, nor black, seek out the average and assign this value to all channels
                average[h][w] = (image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed)/3;
                image[h][w].rgbtBlue = average[h][w];
                image[h][w].rgbtGreen = average[h][w];
                image[h][w].rgbtRed = average[h][w];
            }
        }
    }
    return;
}


{
    // creating another variable that holds sepia info
    // is sepia filter would apply while assigning the values, it would cascade the values, not resulting in the original sepia filter
    RGBTRIPLE sepia[height - 1][width - 1];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if ((.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue) > 255)
            {
                sepia[h][w].rgbtRed = 255;
            }
            else
            {
                sepia[h][w].rgbtRed = round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue);
            }

            if ((.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue) > 255)
            {
                 sepia[h][w].rgbtBlue = 255;
            }
            else
            {
                sepia[h][w].rgbtBlue = round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue);
            }

            if ((.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue) > 255)
            {
                sepia[h][w].rgbtGreen = 255;
            }
            else
            {
                sepia[h][w].rgbtGreen = round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue);
            }

           image[h][w].rgbtBlue = sepia[h][w].rgbtBlue;
           image[h][w].rgbtGreen = sepia[h][w].rgbtGreen;
           image[h][w].rgbtRed = sepia[h][w].rgbtRed;
        }
    }
    // sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
    // sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
    // sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE reflection[height -1][width - 1], temp[width - 1];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            reflection[h][w] = image[h][width - 1 - w];

            // true if num is perfectly divisible by 2 (even number)
           //if(width % 2 == 0)


        }

    }

    for (int i = 0; i < height; i++)
    {
        temp[i] = temp[w]

            temp[(h * width) + w + 1]
    }
    return;
}



// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blur[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if (h == 0 && w == 0)
            {
                blur[h][w].rgbtBlue = (image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue + image[h + 1][w].rgbtBlue + image[h + 1][w + 1].rgbtBlue)/4;
                blur[h][w].rgbtGreen = (image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen + image[h + 1][w].rgbtGreen + image[h + 1][w + 1].rgbtGreen)/4;
                blur[h][w].rgbtRed = (image[h][w].rgbtRed + image[h][w + 1].rgbtRed + image[h + 1][w].rgbtRed + image[h + 1][w + 1].rgbtRed)/4;

            }
            else if (h != 0 && w == 0)
            {
                blur[h][w].rgbtBlue = (image[h][w].rgbtBlue + image[h - 1][w].rgbtBlue + image[h - 1][w + 1].rgbtBlue + image[h][w + 1].rgbtBlue + image[h + 1][w + 1].rgbtBlue + image[h + 1][w].rgbtBlue)/6;
                blur[h][w].rgbtGreen = (image[h][w].rgbtGreen + image[h - 1][w].rgbtGreen + image[h - 1][w + 1].rgbtGreen + image[h][w + 1].rgbtGreen + image[h + 1][w + 1].rgbtGreen + image[h + 1][w].rgbtGreen)/6;
                blur[h][w].rgbtRed = (image[h][w].rgbtRed + image[h - 1][w].rgbtRed + image[h - 1][w + 1].rgbtRed + image[h][w + 1].rgbtRed + image[h + 1][w + 1].rgbtRed + image[h + 1][w].rgbtRed)/6;
            }
            else if (h == height - 1 && w == 0)
            {
                blur[h][w].rgbtBlue = (image[h][w].rgbtBlue + image[h - 1][w].rgbtBlue + image[h - 1][w + 1].rgbtBlue + image[h][w + 1].rgbtBlue)/4;
                blur[h][w].rgbtGreen = (image[h][w].rgbtGreen + image[h - 1][w].rgbtGreen + image[h - 1][w + 1].rgbtGreen + image[h][w + 1].rgbtGreen)/4;
                blur[h][w].rgbtRed = (image[h][w].rgbtRed + image[h - 1][w].rgbtRed + image[h - 1][w + 1].rgbtRed + image[h][w + 1].rgbtRed)/4;
            }
            else if (h == height - 1 && w != 0)
            {
                blur[h][w].rgbtBlue = (image[h - 1][w - 1].rgbtBlue + image[h - 1][w].rgbtBlue + image[h - 1][w + 1].rgbtBlue + image[h][w - 1].rgbtBlue + image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue)/6;
                blur[h][w].rgbtGreen = (image[h - 1][w - 1].rgbtGreen + image[h - 1][w].rgbtGreen + image[h - 1][w + 1].rgbtGreen + image[h][w - 1].rgbtGreen + image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen)/6;
                blur[h][w].rgbtRed = (image[h - 1][w - 1].rgbtRed + image[h - 1][w].rgbtRed + image[h - 1][w + 1].rgbtRed + image[h][w - 1].rgbtRed + image[h][w].rgbtRed + image[h][w + 1].rgbtRed)/6;
            }
            else if (h == height - 1 && w == width -1)
            {
                blur[h][w].rgbtBlue = (image[h -1][w - 1].rgbtBlue + image[h - 1][w].rgbtBlue + image[h][w].rgbtBlue + image[h][w - 1].rgbtBlue)/4;
                blur[h][w].rgbtGreen = (image[h -1][w - 1].rgbtGreen + image[h - 1][w].rgbtGreen + image[h][w].rgbtGreen + image[h][w - 1].rgbtGreen)/4;
                blur[h][w].rgbtRed = (image[h -1][w - 1].rgbtRed + image[h - 1][w].rgbtRed + image[h][w].rgbtRed + image[h][w - 1].rgbtRed)/4;
            }
            else if (h != 0 && w == width -1)
            {
                blur[h][w].rgbtBlue = (image[h - 1][w - 1].rgbtBlue + image[h -1][w].rgbtBlue + image[h][w].rgbtBlue + image[h][w - 1].rgbtBlue + image[h + 1][w].rgbtBlue + image[h + 1][w - 1].rgbtBlue)/6;
                blur[h][w].rgbtGreen = (image[h - 1][w - 1].rgbtGreen + image[h -1][w].rgbtGreen + image[h][w].rgbtGreen + image[h][w - 1].rgbtGreen + image[h + 1][w].rgbtGreen + image[h + 1][w - 1].rgbtGreen)/6;
                blur[h][w].rgbtRed = (image[h - 1][w - 1].rgbtRed + image[h -1][w].rgbtRed + image[h][w].rgbtRed + image[h][w - 1].rgbtRed + image[h + 1][w].rgbtRed + image[h + 1][w - 1].rgbtRed)/6;
            }
            else if (h == 0 && w == width -1)
            {
                blur[h][w].rgbtBlue = (image[h][w - 1].rgbtBlue + image[h][w].rgbtBlue + image[h + 1][w - 1].rgbtBlue + image[h + 1][w].rgbtBlue)/4;
                blur[h][w].rgbtGreen = (image[h][w - 1].rgbtGreen + image[h][w].rgbtGreen + image[h + 1][w - 1].rgbtGreen + image[h + 1][w].rgbtGreen)/4;
                blur[h][w].rgbtRed = (image[h][w - 1].rgbtRed + image[h][w].rgbtRed + image[h + 1][w - 1].rgbtRed + image[h + 1][w].rgbtRed)/4;
            }
            else if (h == 0 && w != 0)
            {
                blur[h][w].rgbtBlue = (image[h][w - 1].rgbtBlue + image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue + image[h + 1][w - 1].rgbtBlue + image[h + 1][w].rgbtBlue + image[h + 1][w + 1].rgbtBlue)/6;
                blur[h][w].rgbtGreen = (image[h][w - 1].rgbtGreen + image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen + image[h + 1][w - 1].rgbtGreen + image[h + 1][w].rgbtGreen + image[h + 1][w + 1].rgbtGreen)/6;
                blur[h][w].rgbtRed = (image[h][w - 1].rgbtRed + image[h][w].rgbtRed + image[h][w + 1].rgbtRed + image[h + 1][w - 1].rgbtRed + image[h + 1][w].rgbtRed + image[h + 1][w + 1].rgbtRed)/6;
            }
            else if (h != 0 && h != height - 1 && w != 0 && w != width -1)
            {
                blur[h][w].rgbtBlue = (image[h][w - 1].rgbtBlue + image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue + image[h + 1][w - 1].rgbtBlue + image[h + 1][w].rgbtBlue + image[h + 1][w + 1].rgbtBlue + image[h - 1][w - 1].rgbtBlue + image[h - 1][w].rgbtBlue + image[h -1][w + 1].rgbtBlue)/9;
                blur[h][w].rgbtGreen = (image[h][w - 1].rgbtGreen + image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen + image[h + 1][w - 1].rgbtGreen + image[h + 1][w].rgbtGreen + image[h + 1][w + 1].rgbtGreen + image[h - 1][w - 1].rgbtGreen + image[h - 1][w].rgbtGreen + image[h -1][w + 1].rgbtGreen)/9;
                blur[h][w].rgbtRed = (image[h][w - 1].rgbtRed + image[h][w].rgbtRed + image[h][w + 1].rgbtRed + image[h + 1][w - 1].rgbtRed + image[h + 1][w].rgbtRed + image[h + 1][w + 1].rgbtRed + image[h - 1][w - 1].rgbtRed + image[h - 1][w].rgbtRed + image[h -1][w + 1].rgbtRed)/9;
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = blur[i][j].rgbtBlue;
            image[i][j].rgbtGreen = blur[i][j].rgbtGreen;
            image[i][j].rgbtRed = blur[i][j].rgbtRed;
        }
    }

    return;
}
