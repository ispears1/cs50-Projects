//A Program that determines the reading level of a piece of text
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int letter_count(string this_sentence);
int word_count(string this_sentence);
int sentence_count(string this_sentence);

int main(void)
{
    string text = get_string("Text: ");
    int letters = letter_count(text);
    int words = word_count(text);
    int sentences = sentence_count(text);
    float L = ((float)letters / (float)words) * 100;
    float s = ((float)sentences / (float)words) * 100;
    int grade = round(0.0588 * L - 0.296 * s - 15.8);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    if (grade >= 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    printf("Grade %i\n", grade);
    return 0;
}

int letter_count(string this_sentence)
{
    int counter = 0;
    int letters = 0;
    while (this_sentence[counter] != '\0')
    {
        if (isalpha(this_sentence[counter]) != 0)
        {
            letters++;
        }
        counter++;
    }
    return letters;
}

int word_count(string this_sentence)
{
    int counter = 0;
    int words = 1;
    while (this_sentence[counter] != '\0')
    {
        if (this_sentence[counter] == 32)
        {
            words++;
        }
        counter++;
    }
    return words;
}

int sentence_count(string this_sentence)
{
    int counter = 0;
    int sentences = 0;
    while (this_sentence[counter] != '\0')
    {
        if (this_sentence[counter] == 33 || this_sentence[counter] == 46 || this_sentence[counter] == 63)
        {
            sentences++;
        }
        counter++;
    }
    return sentences;
}
