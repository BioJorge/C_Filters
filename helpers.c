#include "helpers.h"
#include "math.h"

// Convert image to grayscale
// to convert somenting to grayscale, each channel (R, G, and B) needs to have the same amount of intensity, per pixel
// this will result in an intensity of gray, ranging from black to white.
// just do an average intensity of each pixel, then apply this value to all 3 channels of that pixel.
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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // creating another variable that holds sepia info
    // is sepia filter would apply while assigning the values, it would cascade the values, not resulting in the original sepia filter
    RGBTRIPLE sepia[height][width];

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
    RGBTRIPLE reflection[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // basically the line below is mirroring each pixel location of the image, into another 2D array, called reflection
            // (e.g. w = 1919) ; reflected_w = 1920 (width) - 1 - 1919 (w) = 0; therefore, the last pixel will be moved to first place
            // (e.g. w = 2) reflected_w = 1920 (width) - 1 - 2 (w) = 1917; therefore, the third pixel would be moved to the third to last position
            reflection[h][w] = image[h][width - 1 - w];
        }

    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = reflection[i][j];
        }
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
            // there are 9 possibilites for the average pixel to be measured

            // possibility 1: top-left corner
            // here, only the pixels [h][w], [h][w + 1], [h +1][w] and [h+1][w+1] exist; therefore, an average can only include those pixels
            if (h == 0 && w == 0)
            {
                blur[h][w].rgbtBlue = (image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue + image[h + 1][w].rgbtBlue + image[h + 1][w + 1].rgbtBlue)/4;
                blur[h][w].rgbtGreen = (image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen + image[h + 1][w].rgbtGreen + image[h + 1][w + 1].rgbtGreen)/4;
                blur[h][w].rgbtRed = (image[h][w].rgbtRed + image[h][w + 1].rgbtRed + image[h + 1][w].rgbtRed + image[h + 1][w + 1].rgbtRed)/4;

            }
            //possibility 2: left corner, not in the top nor bottow extremity
            // here, only the pixels [h-1][w], [h-1][w+1], [h][w], [h][w+1], [h+1][w] and [h+1][w+1] exist; therefore, an average can only include those pixels
            else if (h != 0 && h != height - 1 && w == 0)
            {
                blur[h][w].rgbtBlue = (image[h][w].rgbtBlue + image[h - 1][w].rgbtBlue + image[h - 1][w + 1].rgbtBlue + image[h][w + 1].rgbtBlue + image[h + 1][w + 1].rgbtBlue + image[h + 1][w].rgbtBlue)/6;
                blur[h][w].rgbtGreen = (image[h][w].rgbtGreen + image[h - 1][w].rgbtGreen + image[h - 1][w + 1].rgbtGreen + image[h][w + 1].rgbtGreen + image[h + 1][w + 1].rgbtGreen + image[h + 1][w].rgbtGreen)/6;
                blur[h][w].rgbtRed = (image[h][w].rgbtRed + image[h - 1][w].rgbtRed + image[h - 1][w + 1].rgbtRed + image[h][w + 1].rgbtRed + image[h + 1][w + 1].rgbtRed + image[h + 1][w].rgbtRed)/6;
            }
            //possibility 3: bottow-left corner
            else if (h == height - 1 && w == 0)
            {
                blur[h][w].rgbtBlue = (image[h][w].rgbtBlue + image[h - 1][w].rgbtBlue + image[h - 1][w + 1].rgbtBlue + image[h][w + 1].rgbtBlue)/4;
                blur[h][w].rgbtGreen = (image[h][w].rgbtGreen + image[h - 1][w].rgbtGreen + image[h - 1][w + 1].rgbtGreen + image[h][w + 1].rgbtGreen)/4;
                blur[h][w].rgbtRed = (image[h][w].rgbtRed + image[h - 1][w].rgbtRed + image[h - 1][w + 1].rgbtRed + image[h][w + 1].rgbtRed)/4;
            }
            //possibility 4: bottow corner, not in the right nor left extremity
            else if (h == height - 1 && w != 0 && w != width - 1)
            {
                blur[h][w].rgbtBlue = (image[h - 1][w - 1].rgbtBlue + image[h - 1][w].rgbtBlue + image[h - 1][w + 1].rgbtBlue + image[h][w - 1].rgbtBlue + image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue)/6;
                blur[h][w].rgbtGreen = (image[h - 1][w - 1].rgbtGreen + image[h - 1][w].rgbtGreen + image[h - 1][w + 1].rgbtGreen + image[h][w - 1].rgbtGreen + image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen)/6;
                blur[h][w].rgbtRed = (image[h - 1][w - 1].rgbtRed + image[h - 1][w].rgbtRed + image[h - 1][w + 1].rgbtRed + image[h][w - 1].rgbtRed + image[h][w].rgbtRed + image[h][w + 1].rgbtRed)/6;
            }
            //possibility 5: bottow-right corner
            else if (h == height - 1 && w == width -1)
            {
                blur[h][w].rgbtBlue = (image[h -1][w - 1].rgbtBlue + image[h - 1][w].rgbtBlue + image[h][w].rgbtBlue + image[h][w - 1].rgbtBlue)/4;
                blur[h][w].rgbtGreen = (image[h -1][w - 1].rgbtGreen + image[h - 1][w].rgbtGreen + image[h][w].rgbtGreen + image[h][w - 1].rgbtGreen)/4;
                blur[h][w].rgbtRed = (image[h -1][w - 1].rgbtRed + image[h - 1][w].rgbtRed + image[h][w].rgbtRed + image[h][w - 1].rgbtRed)/4;
            }
            //possibility 6: right corner, not in the top nor bottow
            else if (h != 0 && h != height - 1 && w == width -1)
            {
                blur[h][w].rgbtBlue = (image[h - 1][w - 1].rgbtBlue + image[h -1][w].rgbtBlue + image[h][w].rgbtBlue + image[h][w - 1].rgbtBlue + image[h + 1][w].rgbtBlue + image[h + 1][w - 1].rgbtBlue)/6;
                blur[h][w].rgbtGreen = (image[h - 1][w - 1].rgbtGreen + image[h -1][w].rgbtGreen + image[h][w].rgbtGreen + image[h][w - 1].rgbtGreen + image[h + 1][w].rgbtGreen + image[h + 1][w - 1].rgbtGreen)/6;
                blur[h][w].rgbtRed = (image[h - 1][w - 1].rgbtRed + image[h -1][w].rgbtRed + image[h][w].rgbtRed + image[h][w - 1].rgbtRed + image[h + 1][w].rgbtRed + image[h + 1][w - 1].rgbtRed)/6;
            }
            //possibility 7: top-right corner
            else if (h == 0 && w == width -1)
            {
                blur[h][w].rgbtBlue = (image[h][w - 1].rgbtBlue + image[h][w].rgbtBlue + image[h + 1][w - 1].rgbtBlue + image[h + 1][w].rgbtBlue)/4;
                blur[h][w].rgbtGreen = (image[h][w - 1].rgbtGreen + image[h][w].rgbtGreen + image[h + 1][w - 1].rgbtGreen + image[h + 1][w].rgbtGreen)/4;
                blur[h][w].rgbtRed = (image[h][w - 1].rgbtRed + image[h][w].rgbtRed + image[h + 1][w - 1].rgbtRed + image[h + 1][w].rgbtRed)/4;
            }
            //possibility 8: top corner, not in the right nor left extremities
            else if (h == 0 && w != 0 && w != width-1)
            {
                blur[h][w].rgbtBlue = (image[h][w - 1].rgbtBlue + image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue + image[h + 1][w - 1].rgbtBlue + image[h + 1][w].rgbtBlue + image[h + 1][w + 1].rgbtBlue)/6;
                blur[h][w].rgbtGreen = (image[h][w - 1].rgbtGreen + image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen + image[h + 1][w - 1].rgbtGreen + image[h + 1][w].rgbtGreen + image[h + 1][w + 1].rgbtGreen)/6;
                blur[h][w].rgbtRed = (image[h][w - 1].rgbtRed + image[h][w].rgbtRed + image[h][w + 1].rgbtRed + image[h + 1][w - 1].rgbtRed + image[h + 1][w].rgbtRed + image[h + 1][w + 1].rgbtRed)/6;
            }
            // last possibility: the pixel is not in any corner, therefore a 3x3 grid is possible
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
