//A program that reports how many years it would take a population to grow from one input to the next input
#include <cs50.h>
#include <stdio.h>

int get_startingPop(void);
int get_endingPop(int ogPop);
int calcYears(int ogPop, int endingPop);

int main(void)
{
    // Prompt for start size
    int startingPopulation = get_startingPop();

    // Prompt for end size
    int endingPopulation = get_endingPop(startingPopulation);

    // Calculate number of years until we reach threshold
    int years = calcYears(startingPopulation, endingPopulation);

    // Print number of years
    printf("Years: %i\n", years);
}

int get_startingPop(void)
{
    int originalPop = 0;
    do
    {
        originalPop = get_int("Enter the starting population size. Starting Population must be at least 9:");
    }
    while (originalPop < 9);
    return originalPop;
}

int get_endingPop(int ogPop)
{
    int endPop = 0;
    do
    {
        endPop = get_int("Enter the final population size (Please note this must be larger than the starting population size: ");
    }
    while (endPop < ogPop);
    return endPop;
}

int calcYears(int ogPop, int endingPop)
{
    int years = 0;
    while (ogPop < endingPop)
    {
        int holder = ogPop;
        ogPop = ogPop + (holder / 3);
        ogPop = ogPop - (holder / 4);
        years++;
    }
    return years;
}
