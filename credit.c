#include <cs50.h>
#include <stdio.h>

int luhnAlgo(long ccNum);
string getType(long ccNum);

//A Program that checks an entered credit card number for validity using the Luhn Algorithm, and then returns the type of credit card that was entered.

int main(void)
{
    long num = get_long("Enter your credit card number: \n");
    int validation = luhnAlgo(num);
    string type = getType(num);
    if (validation == 1)
    {
        printf("%s\n", type);
    }
    else
    {
        printf("INVALID\n");
    }
}

int luhnAlgo(long ccNum)
{
    long doublingNum = ccNum / 10;
    int doubled = 0;
    int sum = 0;
    int i = 0;

    while (ccNum > 0)
    {
        sum = sum + ccNum % 10;
        ccNum = ccNum / 100;
    }
    while (doublingNum > 0)
    {
        doubled = 2 * (doublingNum % 10);
        if (doubled > 9)
        {
            sum = sum + (doubled % 10) + 1;
        }
        else
        {
            sum = sum + doubled;
        }
        doublingNum = doublingNum / 100;
    }

    if (sum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

string getType(long ccNum)
{
    string type = "";
    if ((ccNum / 10000000000000 == 34) || (ccNum / 10000000000000 == 37))
    {
        type = "AMEX";
    }
    else if ((ccNum / 1000000000000 == 4) || (ccNum / 10000000000000 == 4) || (ccNum / 100000000000000 == 4) ||
             (ccNum / 1000000000000000 == 4))
    {
        type = "VISA";
    }
    else if ((ccNum / 100000000000000 == 51) || (ccNum / 100000000000000 == 52) || (ccNum / 100000000000000 == 53) ||
             (ccNum / 100000000000000 == 54) || (ccNum / 100000000000000 == 55))
    {
        type = "MASTERCARD";
    }
    else
    {
        type = "INVALID";
    }
    return type;
}
