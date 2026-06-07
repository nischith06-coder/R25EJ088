#include <stdio.h>
#include <stdlib.h>

#define WIDTH 50
#define HEIGHT 20

char canvas[HEIGHT][WIDTH];

void clearCanvas() {
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas() {
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

void plot(int x, int y) {
    if(x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        canvas[y][x] = '*';
    }
}

void drawRectangle(int x1, int y1, int x2, int y2) {

    for(int x = x1; x <= x2; x++) {
        plot(x, y1);
        plot(x, y2);
    }

    for(int y = y1; y <= y2; y++) {
        plot(x1, y);
        plot(x2, y);
    }
}

void drawLine(int x1, int y1, int x2, int y2) {

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while(1) {

        plot(x1, y1);

        if(x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if(e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if(e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

int main() {

    clearCanvas();

    drawRectangle(5, 3, 20, 10);

    drawLine(0, 0, 40, 15);

    displayCanvas();

    return 0;
}