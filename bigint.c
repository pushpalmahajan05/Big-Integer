#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 309

typedef struct
{
    int nums[MAX_SIZE];
    int size;
    int sign;
} BigInt;

void initializeBigInt(BigInt *num)
{
    memset(num->nums, 0, sizeof(num->nums));
    num->size = 0;
    num->sign = 0;
}
void inputBigInt(BigInt *num)
{
    char input[MAX_SIZE + 1];
    printf("Enter a bigint number: ");
    scanf("%s", input);
    initializeBigInt(num);
    if (input[0] == '-')
    {
        num->sign = 1;
    }

    // Reverse the input string and convert each character to an integer
    int len = strlen(input);
    if (num->sign == 0)

    {

        for (int i = 0; i < len; i++)
        {
            num->nums[i] = input[len - 1 - i] - '0';
        }
        num->size = len;
    }
    else
    {

        for (int i = 0; i < len - 1; i++)
        {
            num->nums[i] = input[len - 1 - i] - '0';
        }
        num->size = len - 1;
    }
}

void printBigInt(BigInt *num)
{
    if (num->sign == 0)
    {

        for (int i = num->size - 1; i >= 0; i--)
        {
            printf("%d", num->nums[i]);
        }
        printf("\n");
    }
    else
    {
        printf("-");
        for (int i = num->size - 1; i >= 0; i--)
        {
            printf("%d", num->nums[i]);
        }
        printf("\n");
    }
}

void addBigInt(BigInt *result, BigInt *num1, BigInt *num2);
void subtractBigInt(BigInt *result, BigInt *num1, BigInt *num2);
void multiplyBigInt(BigInt *result, BigInt *num1, BigInt *num2);
int main()
{
    BigInt num1, num2;
    BigInt *result = malloc(sizeof(BigInt));
    initializeBigInt(&num1);
    initializeBigInt(&num2);
    initializeBigInt(result);
    inputBigInt(&num1);
    inputBigInt(&num2);
    addBigInt(result, &num1, &num2);
    printf("Addition: ");
    printBigInt(result);
    initializeBigInt(result);
    subtractBigInt(result, &num1, &num2);
    printf("\n Subtraction: ");
    printBigInt(result);
    initializeBigInt(result);
    multiplyBigInt(result, &num1, &num2);
    printf("\n Multiplication: ");
    printBigInt(result);
    return 0;
}

void addBigInt(BigInt *result, BigInt *num1, BigInt *num2)
{
    //  addition here
    int carry = 0;
    if (num1->sign == 0 && num2->sign == 0 || num1->sign == 1 && num2->sign == 1)
    {
        for (int i = 0; i < MAX_SIZE; i++)
        {
            int sum = num1->nums[i] + num2->nums[i] + carry;
            result->nums[i] = sum % 10; // Store the least significant digit
            carry = sum / 10;
        }

        for (int i = MAX_SIZE - 1; i >= 0; i--)
        {
            if (result->nums[i] != 0)
            {
                result->size = i + 1;
                break;
            }
        }

        result->sign = num1->sign;
    }
    else if (num1->sign == 0)
    {
        num2->sign = 0;
        subtractBigInt(result, num1, num2);
        num2->sign = 1;
    }
    else
    {
        num1->sign = 0;
        subtractBigInt(result, num2, num1);
        num1->sign = 1;
    }
}

void multiplyBigInt(BigInt *result, BigInt *num1, BigInt *num2)
{
    // multiplication here
    for (int i = 0; i < MAX_SIZE; i++)
    {
        int carry = 0;

        for (int j = 0; j < MAX_SIZE - i; j++)
        {
            int product = num1->nums[i] * num2->nums[j] + result->nums[i + j] + carry;

            result->nums[i + j] = product % 10; // Store the least significant digit
            carry = product / 10;               // Carry for the next iteration
        }
      
        
    }

    // Set the size of the result
    for (int i = MAX_SIZE - 1; i >= 0; i--)
    {
        if (result->nums[i] != 0)
        {
            result->size = i + 1;
            break;
        }
    }
    if (num1->sign == 0 && num2->sign == 0 || num1->sign == 1 && num2->sign == 1)
    {
        result->sign = 0;
    }
    else
    {
        result->sign = 1;
    }
}

void subtractBigInt(BigInt *result, BigInt *num1, BigInt *num2)
{
    // subtraction here
    int max_size;
    if (num1->size > num2->size)
    {
        max_size = num1->size;
    }
    else
    {
        max_size = num2->size;
    }
    if (num1->sign == 0 && num2->sign == 0 || num1->sign == 1 && num2->sign == 1)
    {
        int borrow = 0;
        result->size = max_size + 1;
        num1->nums[max_size] = 1;

        for (int i = 0; i <= max_size; i++)
        {
            int diff = num1->nums[i] - num2->nums[i] - borrow;

            if (diff < 0)
            {

                // the next higher digit
                borrow = 1;
                diff += 10; // Borrow from
            }
            else
            {
                borrow = 0;
            }

            result->nums[i] = diff % 10; // Store the least significant digit
        }
        if (result->nums[max_size] == 1)
        {
            result->sign = num1->sign;
            result->nums[max_size] = 0;
            result->size = max_size;
        }
        else
        {
            // first number is smaller than second number return the 10s compliment;
            result->nums[max_size] = 0;
            result->nums[0] = 10 - result->nums[0];
            int carry = (result->nums[0]) / 10;
            result->nums[0] = (10 - result->nums[0]) % 10;
            for (int i = 1; i < max_size; i++)
            {
                result->nums[i] = 9 - result->nums[i] + carry;
                carry = (result->nums[i]) / 10;
                result->nums[i] = (result->nums[i]) % 10;
            }
            result->size = max_size;

            if (num1->sign == 0)
            {
                result->sign = 1;
            }
            else
            {
                result->sign = 0;
            }
        }
        num1->nums[max_size] = 0;
    }

    else if (num2->sign == 1)
    {

        num2->sign = 0;
        addBigInt(result, num1, num2);
        result->sign = 0;
        num2->sign = 1;
    }
    else
    {
        num1->sign = 0;
        addBigInt(result, num1, num2);
        result->sign = 1;
        num1->sign = 1;
    }

    result->size = max_size;
}