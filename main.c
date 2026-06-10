#include <stdio.h>
#include <stdlib.h>

#define WIDTH 60
#define HEIGHT 25
#define MAX_SHAPES 100

char canvas[HEIGHT][WIDTH];

typedef struct
{
    int type;      // 1 Rectangle, 2 Line, 3 Circle, 4 Triangle
    char symbol;

    int x1, y1;
    int x2, y2;
    int x3, y3;

    int radius;
} Shape;

Shape shapes[MAX_SHAPES];
int shapeCount = 0;

char drawChar='*';

void clearCanvas()
{
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            canvas[i][j]='_';
        }
    }
}

void displayCanvas()
{
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            printf("%c",canvas[i][j]);
        }
        printf("\n");
    }
}

void plot(int x,int y)
{
    if(x>=0 && x<WIDTH && y>=0 && y<HEIGHT)
    {
        canvas[y][x]=drawChar;
    }
}
void drawRectangle(int x1,int y1,int x2,int y2)
{
    for(int x=x1;x<=x2;x++)
    {
        plot(x,y1);
        plot(x,y2);
    }

    for(int y=y1;y<=y2;y++)
    {
        plot(x1,y);
        plot(x2,y);
    }
}

void drawLine(int x1,int y1,int x2,int y2)
{
    int dx=abs(x2-x1);
    int dy=abs(y2-y1);

    int sx=(x1<x2)?1:-1;
    int sy=(y1<y2)?1:-1;

    int err=dx-dy;

    while(1)
    {
        plot(x1,y1);

        if(x1==x2 && y1==y2)
            break;

        int e2=2*err;

        if(e2>-dy)
        {
            err-=dy;
            x1+=sx;
        }

        if(e2<dx)
        {
            err+=dx;
            y1+=sy;
        }
    }
}

void drawCircle(int xc,int yc,int r)
{
    for(int y=yc-r;y<=yc+r;y++)
    {
        for(int x=xc-r;x<=xc+r;x++)
        {
            int dx=x-xc;
            int dy=y-yc;

            if(dx*dx + dy*dy <= r*r)
            {
                plot(x,y);
            }
        }
    }
}

void drawTriangle(
    int x1,int y1,
    int x2,int y2,
    int x3,int y3)
{
    drawLine(x1,y1,x2,y2);
    drawLine(x2,y2,x3,y3);
    drawLine(x3,y3,x1,y1);
}

void redrawCanvas()
{
    clearCanvas();

    for(int i=0;i<shapeCount;i++)
    {
        drawChar = shapes[i].symbol;

        switch(shapes[i].type)
        {
            case 1:
                drawRectangle(
                    shapes[i].x1,
                    shapes[i].y1,
                    shapes[i].x2,
                    shapes[i].y2);
                break;

            case 2:
                drawLine(
                    shapes[i].x1,
                    shapes[i].y1,
                    shapes[i].x2,
                    shapes[i].y2);
                break;

            case 3:
                drawCircle(
                    shapes[i].x1,
                    shapes[i].y1,
                    shapes[i].radius);
                break;

            case 4:
                drawTriangle(
                    shapes[i].x1,
                    shapes[i].y1,
                    shapes[i].x2,
                    shapes[i].y2,
                    shapes[i].x3,
                    shapes[i].y3);
                break;
        }
    }
}

void deleteObject()
{
    int index;

    printf("Enter object number to delete: ");
    scanf("%d",&index);

    index--;

    if(index<0 || index>=shapeCount)
    {
        printf("Invalid Object!\n");
        return;
    }

    for(int i=index;i<shapeCount-1;i++)
    {
        shapes[i]=shapes[i+1];
    }

    shapeCount--;

    printf("Object Deleted Successfully!\n");
}

void modifyObject()
{
    int index;

    printf("Enter object number to modify: ");
    scanf("%d",&index);

    index--;

    if(index<0 || index>=shapeCount)
    {
        printf("Invalid Object!\n");
        return;
    }

    printf("Enter new symbol: ");
    scanf(" %c",&shapes[index].symbol);

    printf("Object Modified Successfully!\n");
}

void displayObjects()
{
    printf("\n===== OBJECT LIST =====\n");

    for(int i=0;i<shapeCount;i++)
    {
        printf("Object %d -> ",i+1);

        switch(shapes[i].type)
        {
            case 1:
                printf("Rectangle");
                break;

            case 2:
                printf("Line");
                break;

            case 3:
                printf("Circle");
                break;

            case 4:
                printf("Triangle");
                break;
        }

        printf(" Symbol:%c\n",
               shapes[i].symbol);
    }

    if(shapeCount==0)
    {
        printf("No Objects Stored!\n");
    }
}
int main()
{
    int choice;

    clearCanvas();

    do
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Add Rectangle\n");
        printf("2. Add Line\n");
        printf("3. Add Circle\n");
        printf("4. Add Triangle\n");
        printf("5. Delete Object\n");
        printf("6. Modify Object\n");
        printf("7. Display Current Canvas\n");
        printf("8. Display All Stored Objects\n");
        printf("9. Display Object List\n");
        printf("10. Clear All Objects\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
            {
                clearCanvas();

                Shape s;
                s.type = 1;

                printf("Enter drawing character: ");
                scanf(" %c",&s.symbol);

                printf("Enter x1 y1 x2 y2: ");
                scanf("%d%d%d%d",
                      &s.x1,&s.y1,
                      &s.x2,&s.y2);

                if(shapeCount < MAX_SHAPES)
                {
                    shapes[shapeCount++] = s;
                }

                drawChar = s.symbol;
                drawRectangle(
                    s.x1,s.y1,
                    s.x2,s.y2);

                printf("\nRectangle Added Successfully!\n\n");
                displayCanvas();

                break;
            }

            case 2:
            {
                clearCanvas();

                Shape s;
                s.type = 2;

                printf("Enter drawing character: ");
                scanf(" %c",&s.symbol);

                printf("Enter x1 y1 x2 y2: ");
                scanf("%d%d%d%d",
                      &s.x1,&s.y1,
                      &s.x2,&s.y2);

                if(shapeCount < MAX_SHAPES)
                {
                    shapes[shapeCount++] = s;
                }

                drawChar = s.symbol;
                drawLine(
                    s.x1,s.y1,
                    s.x2,s.y2);

                printf("\nLine Added Successfully!\n\n");
                displayCanvas();

                break;
            }

            case 3:
            {
                clearCanvas();

                Shape s;
                s.type = 3;

                printf("Enter drawing character: ");
                scanf(" %c",&s.symbol);

                printf("Enter center x y radius: ");
                scanf("%d%d%d",
                      &s.x1,
                      &s.y1,
                      &s.radius);

                if(shapeCount < MAX_SHAPES)
                {
                    shapes[shapeCount++] = s;
                }

                drawChar = s.symbol;
                drawCircle(
                    s.x1,
                    s.y1,
                    s.radius);

                printf("\nCircle Added Successfully!\n\n");
                displayCanvas();

                break;
            }

            case 4:
            {
                clearCanvas();

                Shape s;
                s.type = 4;

                printf("Enter drawing character: ");
                scanf(" %c",&s.symbol);

                printf("Enter x1 y1 x2 y2 x3 y3: ");
                scanf("%d%d%d%d%d%d",
                      &s.x1,&s.y1,
                      &s.x2,&s.y2,
                      &s.x3,&s.y3);

                if(shapeCount < MAX_SHAPES)
                {
                    shapes[shapeCount++] = s;
                }

                drawChar = s.symbol;
                drawTriangle(
                    s.x1,s.y1,
                    s.x2,s.y2,
                    s.x3,s.y3);

                printf("\nTriangle Added Successfully!\n\n");
                displayCanvas();

                break;
            }

            case 5:
            {
                deleteObject();
                break;
            }

            case 6:
            {
                modifyObject();
                break;
            }

            case 7:
            {
                displayCanvas();
                break;
            }

            case 8:
            {
                redrawCanvas();
                displayCanvas();
                break;
            }

            case 9:
            {
                displayObjects();
                break;
            }

            case 10:
            {
                shapeCount = 0;
                clearCanvas();

                printf("All Objects Cleared!\n");
                break;
            }

            case 0:
            {
                printf("Exiting Program...\n");
                break;
            }

            default:
            {
                printf("Invalid Choice!\n");
            }
        }

    } while(choice != 0);

    return 0;
}