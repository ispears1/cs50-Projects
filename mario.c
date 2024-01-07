//A program that creates texts of block staircases like in the Mario games
#include <cs50.h>
#include <stdio.h>

void build(int size);

int main(void)
{
    int size = 0;
    do
    {
        size = get_int("Enter an integer between 1 and 8: ");
    }
    while (size < 1 || size > 8);
    build(size);
}

void build(int size)
{
    for (int level = 1; level < size + 1; level++)
    {
        for (int i = 0; i < (size - level); i++)
        {
            printf(" ");
        }
        for (int j = 0; j < level; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int k = 0; k < level; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
