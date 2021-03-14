#include <stdio.h> /* printf */

#include "../include/bit_array.h"

void PrintBits(bitsarr_ty bitarr);

int main()
{
	bitsarr_ty bitarr = 0;
	printf("Default:\n");
	PrintBits(bitarr);
	printf("BitArraySetAll:\n");
	bitarr = BitArraySetAll(bitarr);
	PrintBits(bitarr);
	printf("BitArrayResetAll:\n");
	bitarr = BitArrayResetAll(bitarr);
	PrintBits(bitarr);
	printf("BitArraySetOn:\n");
	bitarr = BitArraySetOn(bitarr, 6);
	PrintBits(bitarr);
	printf("BitArraySetOff:\n");
	bitarr = BitArraySetOff(bitarr, 6);
	PrintBits(bitarr);
	printf("BitArraySetBit:\n");
	bitarr = BitArraySetBit(bitarr, 6, ON);
	PrintBits(bitarr);
	printf("BitArrayGetVal:\n");
	printf("Index %d is: %d\n\n", 6, BitArrayGetVal(bitarr, ));
	return(0);
}

void PrintBits(bitsarr_ty bitarr)
{
	size_t i = 0;

	for (i = 1UL << 63; i > 0; i = i / 2)
	{
		(bitarr & i) ? printf("1") : printf("0");
	}
	printf("\n\n");
}
