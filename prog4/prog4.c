#include <stdio.h>

// Structure with bitfields
typedef struct
{
    unsigned int firstbit : 1;   // only 1 bit
    unsigned int secondbit : 2;  // 2 bits
    unsigned int thirdbit : 3;   // 3 bits
} Bitfield;

int main()
{
    Bitfield a;

    // Assign values
    a.firstbit = 1;
    a.secondbit = 3;
    a.thirdbit = 5;

    // Display values
    printf("firstbit  = %u\n", a.firstbit);
    printf("secondbit = %u\n", a.secondbit);
    printf("thirdbit  = %u\n", a.thirdbit);

    return 0;
}