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

#include "bit_array.h"
#include "knight_tour.h"

enum board
{ 
	NUM_OF_ROWS = 8,
	NUM_OF_COLUMNS = 8,
	NUM_OF_DIRECTIONS = 8,
	BOARD_SIZE = NUM_OF_ROWS * NUM_OF_COLUMNS
};

/**************************** Forward Declarations ****************************/

int TourIMP(unsigned char path[BOARD_SIZE], int position, bitsarr_ty board,
																time_t timer);

static void IndexToCartesianIMP(int index, int *x, int *y);

static int CartesianToIndexIMP(int x, int y);

/* direction is 0-7, position is 0-63 /
/ returns -1 if move in direction takes you out of the board */
static int GetNextPositionIMP(int curr_position, int direction);

static int IsPositionOutOfBoundsIMP(int x_coordinate, int y_coordinate);

static int IsPositionBeenVisitedIMP(bitsarr_ty board, int position);

static bitsarr_ty MarkPositionAsVisitedIMP(bitsarr_ty board, int position);

/******************************************************************************/
int Tour(int position, unsigned char path[BOARD_SIZE])
{
	/*	create a chess board of 8X8 as a bits array 			*/
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
	TWO_MINUTES = 1
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

/*	if (difftime(curr_time, timer) >= TWO_MINUTES)*/
/*	{*/
/*		return (1);*/
/*	}*/
	
	/*	if this is step leads out of bounds or to a previously visited location */
	/*		return 1*/
	if (IsPositionOutOfBoundsIMP(position_x_coordinate, position_y_coordinate) 
								|| IsPositionBeenVisitedIMP(board, position))
	{
		return (1);
	}
	
		
	/* if each location at the board has been visited */
	if (!BitArrayCountOff(board))
	{
		return (0);
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
enum
{
	/*clockwise*/
	UP_LEFT = 0,
	UP_RIGHT = 1,
	RIGHT_UP = 2,
	RIGHT_DOWN = 3,
	DOWN_RIGHT = 4,
	DOWN_LEFT = 5,
	LEFT_DOWN = 6,
	LEFT_UP = 7
};

static int GetNextPositionIMP(int curr_position, int direction)
{
	int new_position_x = 0, new_position_y = 0;
	int curr_position_x = 0, curr_position_y = 0;
	
	static const int MoveRowLUT[8] = {-2, -2, -1, 1, 2, 2, 1, -1};
	static const int MoveColLUT[8] = {-1, 1, 2, 2, 1, -1, -2, -2};
	
	assert (0 <= direction && direction <= 7);
	
	IndexToCartesianIMP(curr_position, &curr_position_x, &curr_position_y);

	new_position_x = curr_position_x + MoveColLUT[direction];
	new_position_y = curr_position_y + MoveRowLUT[direction];
	
	return (IsPositionOutOfBoundsIMP(new_position_x, new_position_y) ? -1 :
							CartesianToIndexIMP(new_position_x, new_position_y));
}
/******************************************************************************/
static bitsarr_ty MarkPositionAsVisitedIMP(bitsarr_ty board, int position)
{
	/*	a '1' bit will indicate on a visited location on the board 		*/ 
	return (BitArraySetOn(board, position));
}
/******************************************************************************/
static int IsPositionOutOfBoundsIMP(int x_coordinate, int y_coordinate)
{							
	return (!(x_coordinate < NUM_OF_COLUMNS && x_coordinate > -1 &&
							y_coordinate < NUM_OF_ROWS && y_coordinate > -1));
}
/******************************************************************************/
static int IsPositionBeenVisitedIMP(bitsarr_ty board, int position)
{
	return ((int)BitArrayGetVal(board, position));
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
