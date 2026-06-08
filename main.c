#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define WIDTH 60
#define HEIGHT 25

char canvas[HEIGHT][WIDTH];
char drawChar = '*';

void clearCanvas()
{
    for(int i = 0; i < HEIGHT; i++)
    {
        for(int j = 0; j < WIDTH; j++)
        {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas()
{
    for(int i = 0; i < HEIGHT; i++)
    {
        for(int j = 0; j < WIDTH; j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

void plot(int x, int y)
{
    if(x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        canvas[y][x] = drawChar;
    }
}

void drawRectangle(int x1, int y1, int x2, int y2)
{
    for(int x = x1; x <= x2; x++)
    {
        plot(x, y1);
        plot(x, y2);
    }

    for(int y = y1; y <= y2; y++)
    {
        plot(x1, y);
        plot(x2, y);
    }
}

void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while(1)
    {
        plot(x1, y1);

        if(x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if(e2 > -dy)
                {
            err -= dy;
            x1 += sx;
        }

        if(e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void drawCircle(int xc, int yc, int r)
{
    for(int y = yc - r; y <= yc + r; y++)
    {
        for(int x = xc - r; x <= xc + r; x++)
        {
            int dx = x - xc;
            int dy = y - yc;

            if(dx * dx + dy * dy <= r * r)
            {
                plot(x, y);
            }
        }
    }
}

void drawTriangle(int x1, int y1,
                  int x2, int y2,
                  int x3, int y3)
{
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

void savePNG(const char *filename)
{
    unsigned char *image =
        (unsigned char *)malloc(WIDTH * HEIGHT * 3);

    if(image == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    for(int y = 0; y < HEIGHT; y++)
    {
        for(int x = 0; x < WIDTH; x++)
        {
            int index = (y * WIDTH + x) * 3;

            if(canvas[y][x] == '_')
            {
                image[index]     = 255;
                image[index + 1] = 255;
                image[index + 2] = 255;
            }
            else
            {
                image[index]     = 0;
                image[index + 1] = 0;
                image[index + 2] = 0;
            }
        }
    }

    stbi_write_png(
        filename,
        WIDTH,
        HEIGHT,
        3,
        image,
        WIDTH * 3
    );

    free(image);

    printf("\nPNG saved as %s\n", filename);
}

int main()
{
    int choice;

    do
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Draw Rectangle\n");
        printf("2. Draw Line\n");
        printf("3. Draw Circle\n");
        printf("4. Draw Triangle\n");
        printf("5. Clear Canvas\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        int x1, y1, x2, y2;
        int x3, y3, r;
                switch(choice)
        {
            case 1:
                clearCanvas();

                printf("Enter drawing character: ");
                scanf(" %c", &drawChar);

                printf("Enter x1 y1 x2 y2: ");
                scanf("%d%d%d%d",
                      &x1, &y1,
                      &x2, &y2);

                drawRectangle(x1, y1, x2, y2);

                displayCanvas();

                savePNG("rectangle.png");

                break;

            case 2:
                clearCanvas();

                printf("Enter drawing character: ");
                scanf(" %c", &drawChar);

                printf("Enter x1 y1 x2 y2: ");
                scanf("%d%d%d%d",
                      &x1, &y1,
                      &x2, &y2);

                drawLine(x1, y1, x2, y2);

                displayCanvas();

                savePNG("line.png");

                break;

            case 3:
                clearCanvas();

                printf("Enter drawing character: ");
                scanf(" %c", &drawChar);

                printf("Enter center x y and radius: ");
                scanf("%d%d%d",
                      &x1, &y1, &r);

                drawCircle(x1, y1, r);

                displayCanvas();

                savePNG("circle.png");

                break;

            case 4:
                clearCanvas();

                printf("Enter drawing character: ");
                scanf(" %c", &drawChar);

                printf("Enter x1 y1 x2 y2 x3 y3: ");
                scanf("%d%d%d%d%d%d",
                      &x1, &y1,
                      &x2, &y2,
                      &x3, &y3);

                drawTriangle(
                    x1, y1,
                    x2, y2,
                    x3, y3
                );

                displayCanvas();

                savePNG("triangle.png");

                break;

            case 5:
                clearCanvas();

                printf("Canvas Cleared\n");

                displayCanvas();

                break;

            case 0:
                printf("Exiting Program...\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while(choice != 0);

    return 0;
}