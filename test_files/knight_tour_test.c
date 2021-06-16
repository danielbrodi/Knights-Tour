/*********************************FILE__HEADER*********************************\
* File:				knight_tour_test.c						 		  								
* Author:			Daniel Brodsky					  								
* Date:				14-06-2021
* Code Reviewer:							   								
* Version:			1.0					   								
* Description:		knight_tour implementation tests file.		 
\******************************************************************************/

/********************************* Inclusions *********************************/

#include <stddef.h>	/*	size_t						*/
#include <stdio.h>	/*	printf						*/
#include <stdlib.h>	/*	rand, srand					*/
#include <time.h>	/*	time						*/

#include "utils.h"	/*	PRINT_COLOR, COLOR			*/
#include "knight_tour.h"

/***************************** Macros Definitions *****************************/

/* generates random number from -99 to 99 			*/
#define RANDOM_NUM ((rand() % 200 - 100))	

/**************************** Forward Declarations ****************************/



/******************************************************************************/
/******************************* Main__Function *******************************/

int main()
{
	int position = 0, i = 0;
	unsigned char path[64] = {0};
	
	printf("Enter start position: ");
	scanf("%d", &position);
	
	Tour(position, path);
	
	while (i < 64)
	{
		printf("%d->", path[i]);
		++i;
	}
	
	return (0);
}

/******************************************************************************/


/******************************************************************************/


/******************************************************************************/
