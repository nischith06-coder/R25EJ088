
#include <stdio.h>

#define MAX_SHAPES 100

typedef struct
{
    int type;
    char symbol;

    int x1, y1;
    int x2, y2;
    int x3, y3;

    int radius;
} Shape;

Shape shapes[MAX_SHAPES];
int shapeCount = 0;

void addShape()
{
    if(shapeCount >= MAX_SHAPES)
    {
        printf("Shape storage full!\n");
        return;
    }

    printf("Shape added successfully.\n");
    shapeCount++;
}

void deleteShape()
{
    int index;

    printf("Enter shape index to delete: ");
    scanf("%d", &index);

    if(index < 0 || index >= shapeCount)
    {
        printf("Invalid shape index!\n");
        return;
    }

    for(int i = index; i < shapeCount - 1; i++)
    {
        shapes[i] = shapes[i + 1];
    }

    shapeCount--;

    printf("Shape deleted successfully.\n");
}

void modifyShape()
{
    int index;

    printf("Enter shape index to modify: ");
    scanf("%d", &index);

    if(index < 0 || index >= shapeCount)
    {
        printf("Invalid shape index!\n");
        return;
    }

    printf("Shape modification feature placeholder.\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n===== OBJECT MANAGER =====\n");
        printf("1. Add Shape\n");
        printf("2. Delete Shape\n");
        printf("3. Modify Shape\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addShape();
                break;

            case 2:
                deleteShape();
                break;

            case 3:
                modifyShape();
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 0);

    return 0;
}

