/*********************************FILE__HEADER*********************************\
* File:				knight_tour.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				14-06-2021
* Code Reviewer:	
* Pseudo Reviewer: 						   								
* Version:			1.0   								
* Description:		Find out if it's possible for a knight at a given position
					to fully go through a chess board without stepping at a
					location more than one time.
\******************************************************************************/

/********************************* Inclusions *********************************/

#include <assert.h>	/*	assert				*/
#include <stddef.h>	/*	size_t, NULL	*/
#include <time.h> /*	time_t, difftime	*/

#include "knight_tour.h"
#include "bit_array.h"

enum board
{ 
	NUM_OF_ROWS = 8,
	NUM_OF_COLUMNS = 8,
	NUM_OF_DIRECTIONS = 8,
	BOARD_SIZE = NUM_OF_ROWS * NUM_OF_COLUMNS
};

/**************************** Forward Declarations ****************************/

int TourIMP(unsigned char path[BOARD_SIZE], int position, unsigned long board,
																time_t timer);

static void IndexToCartesianIMP(int index, int *x, int *y);

static int CartesianToIndexIMP(int x, int y);

/* direction is 0-7, position is 0-63 /
/ returns -1 if move in direction takes you out of the board */
static int GetNextPositionIMP(int curr_position, int direction);

static int IsPositionOutOfBoundsIMP(int x_coordinate, int y_coordinate);

static int IsPositionBeenVisitedIMP(unsigned long board, int position);

static unsigned long MarkPositionAsVisitedIMP(unsigned long board, int position);

unsigned int CountONBitsIMP(unsigned long board);

/******************************************************************************/
int Tour(int position, unsigned char path[BOARD_SIZE])
{
	/*	create a chess board of 8X8 as a bits array 			*/
	unsigned long board = 0;
	
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

int TourIMP(unsigned char path[BOARD_SIZE], int position, unsigned long board,
																time_t timer)
{	
	int direction_to_go = 0;
	int position_x_coordinate = 0, position_y_coordinate = 0;
	
	time_t curr_time = time(&curr_time);
	
	IndexToCartesianIMP(position, &position_x_coordinate, &position_y_coordinate);
	
	/*	asserts*/
	assert(path);
	
/*	if (difftime(curr_time, timer) >= TWO_MINUTES)*/
/*	{*/
/*		return (1);*/
/*	}*/
	
		/* if each location at the board has been visited */
	if (BitArrayCountOnLUT(board) == 64)
	{
		return (0);
	}
		
	if (IsPositionOutOfBoundsIMP(position_x_coordinate, position_y_coordinate)
								|| IsPositionBeenVisitedIMP(board, position))
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
            /*break*/
            /*add pos to path*/
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
	return (IsPositionOutOfBoundsIMP(new_position_x, new_position_y) ? -1 :
						CartesianToIndexIMP(new_position_x, new_position_y));
}
/******************************************************************************/
static unsigned long MarkPositionAsVisitedIMP(unsigned long board, int position)
{
	unsigned long updated_board = board;
	
	assert(position >= 0);
	
	/*	a '1' bit will indicate on a visited location on the board 		*/ 
	updated_board |= (1UL << position);
	
	return (updated_board);
}
/******************************************************************************/
static int IsPositionOutOfBoundsIMP(int x, int y)
{							
	return (((0 > x || 7 < x || 0 > y || 7 < y)));
}
/******************************************************************************/
static int IsPositionBeenVisitedIMP(unsigned long board, int position)
{
	return (!!(board & (1UL << position)));
}
/******************************************************************************/
static void IndexToCartesianIMP(int index, int *x, int *y)
{
	assert(x && y);
	
	*x = index % NUM_OF_COLUMNS;
	*y = index / NUM_OF_ROWS;
}
/******************************************************************************/
static int CartesianToIndexIMP(int x, int y)
{
	return ((y * NUM_OF_ROWS) + x);
}
/******************************************************************************/
unsigned int CountONBitsIMP(unsigned long board)
{
	size_t curr_bit_index = 0;
	size_t set_bits_counter = 0; 
	
	for (curr_bit_index = 0; curr_bit_index < BOARD_SIZE; ++curr_bit_index) 
	{ 
		set_bits_counter += !!(board & (1UL << curr_bit_index));
		
		board &= ~(1UL << curr_bit_index);
		
		if (0 == board)
		{
			break;
		}
	} 
	 
	return (set_bits_counter); 
}
/******************************************************************************/
