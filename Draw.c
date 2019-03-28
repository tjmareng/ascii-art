// Student stub code for ASCII Drawing assignment

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

// TODO: add a parameter list and the implementation for the following 6 functions:
void initImage(int width, int height, double *image)
{
   // LOOP THROUGH ITEMS IN THE ARRAY AND SET THEM TO 0
   for (int i = 0; i < height; i++)
   {
      for (int j = 0; j < width; j++)
      {
         *image = 0.0; // SET ELEMENT EQUAL TO 0
         image += 1;   // ADJUST POINTER TO NEXT ELEMENT
      }
   }
}

void printImage(int width, int height, double *image)
{
   // PRINT CORNER
   printf("+");

   // LOOP THROUGH THE WIDTH OF THE ARRAY
   for (int i = 0; i < width; i++)
   {
      printf("-"); // PRINT TOP OF FRAME
   }

   // PRINT CORNER
   printf("+\n");

   // LOOP THROUGH THE HEIGHT OF THE ARRAY
   for (int i = 0; i < height; i++)
   {
      printf("|"); // PRINT FRAME

      // LOOP THROUGH THE WIDTH OF THE ARRAY
      for (int j = 0; j < width; j++)
      {

         // GET ELEMENT OF THE ARRAY AND PRINT THE ACCORDING COLOR
         if (0.0 <= *image && 0.2 > *image)
         {
            printf(" "); // [0.0, 0.2), output as space
         }
         else if (0.2 <= *image && 0.4 > *image)
         {
            printf("."); // [0.2, 0.4), output as .
         }
         else if (0.4 <= *image && 0.6 > *image)
         {
            printf("o"); // [0.4, 0.6), output as o
         }
         else if (0.6 <= *image && 0.8 > *image)
         {
            printf("O"); // [0.6, 0.8), output as O
         }
         else if (0.8 <= *image && 1.0 >= *image)
         {
            printf("@"); // [0.8, 1.0], output as @
         }
         else
         {
            printf(" "); // OTHERWISE PRINT SPACE
         }
         image += 1; // MOVE TO NEXT ELEMENT
      }
      printf("|\n"); // PRINT FRAME
   }

   // PRINT CORNER
   printf("+");

   // LOOP THROUGH THE WIDTH OF THE ARRAY
   for (int i = 0; i < width; i++)
   {
      printf("-"); // PRINT BOTTOM OF FRAME
   }
   printf("+\n");
}

void drawPoint(int width, int height, double *image, int x, int y, double color)
{
   // ADJUST POINTER
   image += (width * y) + x;

   // IF THE ELEMENT IS LESS THAN COLOR
   if (*image < color)
   {
      *image = color; // SET ELEMENT TO COLOR
   }
}

void drawRectangle(int width, int height, double *image, int left, int top, int rectangleWidth, int rectangleHeight, double color)
{

   // ADJUST POINTER
   image += (top * width) + left;

   // IF THE WIDTH IS OUT OF BOUNDS
   if (rectangleWidth >= width)
   {
      // ADJUST RECTANGLE WIDTH ACCORDINGLY
      rectangleWidth = width;

      // ADJUST POINTER ACCORDINGLY
      image -= left;
   }

   // IF THE HEIGHT IS OUT OF BOUNDS
   if (rectangleHeight > height)
   {
      // ADJUST RECTANGLE HEIGHT ACCORDINGLY
      rectangleHeight = (left - 1) * height;
   }

   // GO FROM 0 TO THE HEIGHT OF THE RECTANGLE
   for (int i = 0; i < rectangleHeight; i++)
   {
      int count = 0; // SET COUNTER TO 0

      // GO FROM 0 TO THE WIDTH OF THE RECTANGLE
      for (int j = 0; j < rectangleWidth; j++)
      {
         // IF THE ELEMENT IS LESS THAN COLOR
         if (*image < color)
         {
            *image = color; // SET ELEMENT TO COLOR
         }
         image += 1; // ADJUST POINTER
         count++;    // INCREMENT COUNTER
      }
      image += (width - count); // ADJUST POINTER FOR WIDTH
   }
}

void getImageStats(int width, int height, double *image, double *minColor, double *maxColor, double *avgColor)
{
   // SET UP VARIABLES
   double sum = 0.0;
   double count = 0;
   double min = DBL_MAX;
   double max = -DBL_MAX;

   // LOOP THROUGH THE ENTIRE ARRAY
   for (int i = 0; i < height; i++)
   {
      for (int j = 0; j < width; j++)
      {
         sum += *image; // CUMMULATIVE SUM

         if (*image < min)
         {
            min = *image; // IF ELEMENT IS LESS THAN MIN, ADJUST
         }
         if (*image > max)
         {
            max = *image; // IF ELEMENT IS GREATER THAN MAX, ADJUST
         }
         image += 1; // ADJUST POINTER
         count++;    // INCREMENT COUNT
      }
   }
   *minColor = min;           // SET MIN COLOR TO MIN
   *maxColor = max;           // DO THE SAME FOR MAX
   *avgColor = (sum / count); // DIVIDE SUM BY COUNT TO GET AVERAGE
}

void floodFill(int width, int height, double image[height][width], int x, int y, double color)
{

   // IF THE ELEMENT IS GREATER THAN COLOR OR WE ARE OUT OF BOUNDS
   if (image[y][x] >= color || x < 0 || x >= width || y < 0 || y >= height)
   {
      return; // RETURN
   }
   else if (image[y][x] < color)
   {
      // OTHERWISE SET ELEMENT TO COLOR
      image[y][x] = color;

      // GO UP, DOWN, LEFT, AND RIGHT
      floodFill(width, height, image, x + 1, y, color);
      floodFill(width, height, image, x - 1, y, color);
      floodFill(width, height, image, x, y + 1, color);
      floodFill(width, height, image, x, y - 1, color);
   }
}

// Read in a set of drawing instructions from standard input.
// Print the resulting greyscale image as ASCII art.
// DO NOT MODIFY!
int main(void)
{
   // Read in the size of the drawing canvas
   int width = 0;
   int height = 0;
   int result = scanf("%d %d", &width, &height);

   // Program only supports images that are 1x1 or bigger
   if ((width <= 0) || (height <= 0) || (result != 2))
   {
      printf("Failed to read a valid width and height from standard input!\n");
      return 0;
   }

   // Create the 2D arary and initialize all the greyscale values to 0.0
   double image[width][height];
   initImage(width, height, image);

   char command = '\0';
   double color = 0.0;

   // Keep reading in drawing commands until we reach the end of the input
   while (scanf(" %c", &command) == 1)
   {
      switch (command)
      {
      case 'p':
      {
         // Draw a point, read in: x, y, color
         int x = 0;
         int y = 0;
         result = scanf("%d %d %lf", &x, &y, &color);
         if (result != 3)
         {
            printf("Invalid point command!\n");
            return 0;
         }

         drawPoint(width, height, image, x, y, color);
         break;
      }

      case 'r':
      {
         // Draw a rectangle, read in: x, y, w, h, color
         int left = 0;
         int top = 0;
         int rectangleWidth = 0;
         int rectangleHeight = 0;
         result = scanf("%d %d %d %d %lf", &left, &top, &rectangleWidth, &rectangleHeight, &color);
         if (result != 5)
         {
            printf("Invalid rectangle command!\n");
            return 0;
         }

         drawRectangle(width, height, image, left, top, rectangleWidth, rectangleHeight, color);
         break;
      }

      case 'f':
      {
         // Flood fill a color in, read in: x, y, color
         int x = 0;
         int y = 0;
         result = scanf("%d %d %lf", &x, &y, &color);
         if (result != 3)
         {
            printf("Invalid flood fill command!\n");
            return 0;
         }

         floodFill(width, height, image, x, y, color);
         break;
      }

      default:
      {
         printf("Unknown command!\n");
         return 0;
      }
      }
   }

   // Print the final image
   printImage(width, height, image);

   // Finally display some statistics about the image
   double minColor = 0.0;
   double maxColor = 0.0;
   double avgColor = 0.0;
   getImageStats(width, height, image, &minColor, &maxColor, &avgColor);
   printf("Color range [%.2f, %.2f], average %.4f\n", minColor, maxColor, avgColor);
}
