#include <stdio.h>

// Function to print bits of an integer
void printBits(int n)
{
    int bits = sizeof(int) * 8;

    printf("Bits: ");

    for(int i = bits - 1; i >= 0; i--)
    {
        printf("%d", (n >> i) & 1);

        // Space after every 8 bits
        if(i % 8 == 0)
            printf(" ");
    }

    printf("\n");
}

// Function to count number of 1 bits
int countOneBits(int n)
{
    int count = 0;

    while(n != 0)
    {
        count += (n & 1);
        n = n >> 1;
    }

    return count;
}

int main()
{
    int n;

    printf("Enter an integer: ");
    scanf("%d", &n);

    printBits(n);

    printf("Number of 1 bits = %d\n", countOneBits(n));

    return 0;
}