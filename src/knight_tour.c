/*********************************FILE__HEADER*********************************\
* File:				knight_tour.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				14-06-2021
* Code Reviewer:						   								
* Version:			1.5   								
* Description:		Find out if it's possible for a knight at a given position
					to fully go through a chess board without stepping at a
					location more than one time.
\******************************************************************************/

/********************************* Inclusions *********************************/

#include <assert.h>		/*	assert					*/
#include <stddef.h>		/*	size_t, NULL			*/
#include <stdlib.h>		/*	exit					*/
#include <stdio.h>		/*	puts					*/
#include <time.h> 		/*	time_t, difftime		*/

#include "bit_array.h"	/* bits array operations	*/
#include "knight_tour.h"

/* properties of the played chess board		*/
enum board
{ 
	NUM_OF_ROWS = 8,
	NUM_OF_COLUMNS = 8,
	NUM_OF_DIRECTIONS = 8,
	BOARD_SIZE = NUM_OF_ROWS * NUM_OF_COLUMNS
};

/**************************** Forward Declarations ****************************/

static int TourIMP(unsigned char path[BOARD_SIZE], int position, bitsarr_ty board,
																time_t timer);
																
/*	direction is 0-7, position is 0-63	*/
/*	returns -1 if move in direction takes you out of the board	*/
static int GetNextPositionIMP(int current_position, int direction);

static void IndexToCartesianIMP(int index, int *x_coordinate, int *y_coordinate);

static int CartesianToIndexIMP(int x_coordinate, int y_coordinate);

static int IsPositionOutOfBoundsIMP(int x_coordinate, int y_coordinate);


static int HasPositionBeenVisitedBeforeIMP(bitsarr_ty board, int position);

static bitsarr_ty MarkPositionAsVisitedIMP(bitsarr_ty board, int position);

/******************************************************************************/
int Tour(int position, unsigned char path[BOARD_SIZE])
{
	/*	create a chess board of 8X8 as a type of `bitsarr_ty` which
	 *	is a type of 64 bits 			*/
	bitsarr_ty board = 0;
	
	time_t start_time = time(&start_time);
	
	/*	asserts*/
	assert(position > -1);
	assert(path);
	
	return (TourIMP(path, position, board, start_time));
}
/******************************************************************************/
enum
{
	TWO_MINUTES = 120
};

int TourIMP(unsigned char path[BOARD_SIZE], int position, bitsarr_ty board,
																time_t timer)
{	
	int direction_to_go = 0;
	int position_x_coordinate = 0, position_y_coordinate = 0;
	
	time_t curr_time = time(&curr_time);
	
	IndexToCartesianIMP(position, &position_x_coordinate, &position_y_coordinate);
	
	/*	asserts*/
	assert(path);
	
	/* timout of 2 minutes - if no solution has been found - exit the program */
	if (difftime(curr_time, timer) >= TWO_MINUTES)
	{
		puts("Couldn't find a path in the given time.\nPlease try an other "
				"starting position.\n");
		exit(1);
	}
	
	/* if each location at the board has been visited */
	if (BitArrayCountOnLUT(board) == BOARD_SIZE)
	{
		return (0);
	}
	
	/*	verify the position is valid: */
		/*	-	is not out of the bounds of the board	*/
		/*	-	has not been visited before				*/	
	if (IsPositionOutOfBoundsIMP(position_x_coordinate, position_y_coordinate)
							|| HasPositionBeenVisitedBeforeIMP(board, position))
	{
		return (1);
	}
	

	/*	tick curr position at the board*/	
	board = MarkPositionAsVisitedIMP(board, position);

	/*	recursively call 8 available positions 	*/
	for (direction_to_go = 0; direction_to_go < NUM_OF_DIRECTIONS;
															 ++direction_to_go)
    {
        /* if TourIMP(path+1,...) in direction succeeds*/
        if (!TourIMP(path + 1, GetNextPositionIMP(position, direction_to_go),
         														board, timer))
        {
            /* save the last position in path array before exiting	*/
            *path = position;
            
            return (0);
        }
    }
	
	return (1);
}
/******************************************************************************/
static int GetNextPositionIMP(int curr_position, int direction)
{
	/* LUTs which indicate on the change that made by each direction	*/
	static const int MoveRowLUT[8] = {1, 2, 2, 1, -1, -2, -2, -1};
	static const int MoveColLUT[8] = {2, 1, -1, -2, -2, -1, 1, 2};
	
	int new_position_x = 0, new_position_y = 0;
	int curr_position_x = 0, curr_position_y = 0;
	
	assert (0 <= direction && direction <= 7);
	
	IndexToCartesianIMP(curr_position, &curr_position_x, &curr_position_y);
	
	/*	update position as the rule of the direction says */
	new_position_x = curr_position_x + MoveColLUT[direction];
	new_position_y = curr_position_y + MoveRowLUT[direction];
	
	/*	check if the new position is out of bounds and if not, return it */
	return (IsPositionOutOfBoundsIMP(new_position_x, new_position_y) ? (-1) :
						CartesianToIndexIMP(new_position_x, new_position_y));
}
/******************************************************************************/
bitsarr_ty MarkPositionAsVisitedIMP(bitsarr_ty board, int position)
{	
	assert(position >= 0);
	
	/*	a '1' bit will indicate on a visited location on the board 		*/ 
	return (BitArraySetOn(board, position));
}
/******************************************************************************/
int IsPositionOutOfBoundsIMP(int x_coordinate, int y_coordinate)
{							
	return (((0 > x_coordinate || 7 < x_coordinate || 0 > y_coordinate
														|| 7 < y_coordinate)));
}
/******************************************************************************/
int HasPositionBeenVisitedBeforeIMP(bitsarr_ty board, int position)
{
	assert(position >= 0);
	
	return (BitArrayGetVal(board, position));
}
/******************************************************************************/
void IndexToCartesianIMP(int index, int *x_coordinate, int *y_coordinate)
{
	assert(x_coordinate && y_coordinate);
	
	*x_coordinate = index % NUM_OF_COLUMNS;
	*y_coordinate = index / NUM_OF_ROWS;
}
/******************************************************************************/
int CartesianToIndexIMP(int x_coordinate, int y_coordinate)
{
	assert(x_coordinate >= 0 && y_coordinate >= 0);
	
	return ((y_coordinate * NUM_OF_ROWS) + x_coordinate);
}
/******************************************************************************/
