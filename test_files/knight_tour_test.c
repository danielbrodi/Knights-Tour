/******************************************************************************
 *	Author:		Ariel White							 						  *
 *	file: 		knight_tour_test.c										 	  *
 *	date: 		15-06-2021						 							  *
 *	version:	1.0							 								  *
 ******************************************************************************/
 
/************ Includes ************/

#include <stddef.h>     /*  size_t, NULL */
#include <stdio.h>		/* fprintf, printf */
#include <stdlib.h>		/* malloc, free */
#include <string.h>		/* memcmp */
#include <assert.h>		/* assert */
#include <time.h>		/*	clock_t	*/
#include <ctype.h>		/*	isdigit	*/

#include "utils_testing_ariel.h"
#include "knight_tour.h"

/************ Defines ************/

/************ Helper Function Declarations ************/

static void ArrayCopyAndSort(unsigned char *dest, unsigned char *src);

static void InitializeArray(unsigned char *arr);

static void PrintPath(unsigned char path[64]);

static int CompareFunc(const void *elem1, const void *elem2);

/************ Testing Function Declarations ************/

/**************** MAIN *****************/

/* main was written by Daniel Brodsky & Ariel White */
int main()
{
	double execution_time = 0;
	clock_t time_start, time_passed;
	
	status_ty status = FAILURE;
	
	char input_position[2] = {0};
	
	int run_program = 1, num_of_digits = 0, starting_square = 0, curr_char = 0;
	
	unsigned char path[64] = {0};
	unsigned char sorted_path[64] = {0};
	unsigned char test_path[64] = {0};
	
    time_start = clock();
	
	while (run_program)
	{
		InitializeArray(test_path);
		
		printf(YELLOW "Enter a starting square between 0 and 63: " CYAN);
		
		scanf("%s" RESET, input_position);
		
		num_of_digits = strlen(input_position);
		
		for (curr_char = 0; curr_char < num_of_digits; ++curr_char)
		{
        	if (!isdigit(input_position[curr_char]))
        	{
        		printf(RED "Invalid input!\n" RESET);
            	return (1);
        	}
		}
		
		starting_square = atoi(input_position);
		
		if ((starting_square < 0) ^ (starting_square > 64))
		{
			return (0);
		}
		
		printf("\n");
		
		time_start = clock();
		
		if (!Tour(starting_square, path))
		{
			ArrayCopyAndSort(sorted_path, path);
			STATUS_TEST_3PARAM(memcmp, sorted_path, test_path, 64, 0, "Path")
			PrintPath(path);
			status = SUCCESS;
		}
		
		PRINT_SUCCESS(status)
		time_passed = clock() - time_start;
		execution_time = ((double)time_passed)/CLOCKS_PER_SEC;
		
		printf("The solution was found in %f seconds.\n", execution_time);
	}
	
	return (0);
}

/************************ Testing Function Definitions ************************/

/************ Helper Function Declarations ************/

static void ArrayCopyAndSort(unsigned char *dest, unsigned char *src)
{
	unsigned char *dest_runner = (assert(dest), dest);
	unsigned char *src_runner = (assert(src), src);
	unsigned char *end = src + 64;

	for (src_runner = src; src_runner < end; ++dest_runner, ++src_runner)
	{
		*dest_runner = *src_runner;
	}
	
	qsort(dest, 64, sizeof(char), CompareFunc);	
}

/*------------------------------------------*/

static int CompareFunc(const void *elem1, const void *elem2)
{
	assert(elem1);
	assert(elem2);
	
	return (*(char *)elem1 - *(char *)elem2);
}

/*------------------------------------------*/

static void InitializeArray(unsigned char *arr)
{
	unsigned char runner = 0;
	
	for (runner = 0; runner < 64; ++runner)
	{
		arr[runner] = runner;
	}
}

/*------------------------------------------*/

static void PrintPath(unsigned char path[64])
{
	size_t row_counter = 0;
	size_t column_counter = 0;
	unsigned char path_helper[64];
	size_t color = 0;
	
	for (row_counter = 0; row_counter < 64; ++row_counter)
	{
		path_helper[path[row_counter]] = row_counter;
	}
	
	for (row_counter = 0; row_counter < 8; ++row_counter)
	{
		printf(RESET "\n\t");
		
		for (column_counter = 0; column_counter < 8; ++column_counter)
		{
			if (color)
			{
				printf(BLKB WHT "      ");
			}
			else
			{
				printf(WHTHB BLK "      ");
			}
			
			color ^= 1;
		}
		
		printf(RESET);
		printf("\n\t");
		
		for (column_counter = 0; column_counter < 8; ++column_counter)
		{
			if (color)
			{
				printf(BLKB WHT "  %02d  ", 
					path_helper[row_counter * 8 + column_counter]);
			}
			else
			{
				printf(WHTHB BLK "  %02d  ", 
					path_helper[row_counter * 8 + column_counter]);
			}
			
			color ^= 1;
		}
		
		printf(RESET "\n\t");
		
		for (column_counter = 0; column_counter < 8; ++column_counter)
		{
			if (color)
			{
				printf(BLKB WHT "      ");
			}
			else
			{
				printf(WHTHB BLK "      ");
			}
			
			color ^= 1;
		}
		
		color ^= 1; 
	}
	
	printf(RESET "\n\n");
}
