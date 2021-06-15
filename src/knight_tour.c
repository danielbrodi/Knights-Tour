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

#include <assert.h>	/*	assert	*/

#include "bit_array.h"

enum board
{ 
NUM_OF_ROWS = 8,
NUM_OF_COLUMNS = 8,
BOARD_SIZE = NUM_OF_ROWS * NUM_OF_COLUMNS;
};

/**************************** Forward Declarations ****************************/

static void IndexToCartesianIMP(int index, int *x, int *y);

static int CartesianToIndexIMP(int *x, int *y);

/* direction is 0-7, position is 0-63 /
/ returns -1 if move in direction takes you out of the board */
static int NextPositionIMP(int curr_position, int direction);

static int IsPositionOutOfBoundsIMP(int position);

static int IsPositionBeenVisitedIMP(bitsarr_ty board, int position);

static bitsarr_ty MarkPositionAsVisitedIMP(bitsarr_ty board, int position);

/******************************************************************************/
int Tour(int position, unsigned char path[BOARD_SIZE])
{
	/*	create a chess board of 8X8 as a bits array 			*/
	bitsarr_ty board = 0;
	
	/*	create path array which will store the right path (if exists)	*/
	/*	a '1' bit will indicate on a visited location on the board 		*/ 
	unsigned char path[BOARD_SIZE] = {0};
	
	/*	asserts*/
	assert(position > -1);
	assert(path);
	
	return (TourImp(path, position, board, 1));
}
/******************************************************************************/
int TourImp(unsigned char path[BOARD_SIZE], int pos, bitsarr_ty board, int step_num)
{
	size_t is_path_found = 1;
	
	/*	asserts*/
	assert(path);
	
	/* if each location at the board has been visited */
	if (!BitArrayCountOff(board))
	{
		*path = pos;
		
		return (0);
	}
	
	/*	if this is step leads out of bounds or to a previously visited location */
	/*		return 1*/
	if (IsPositionOutOfBoundsIMP(position) ^ 
									IsPositionBeenVisitedIMP(board, position))
	{
		return (1);
	}


	/*	increment step and tick curr position at the board*/
	++step_num;
	
	board = MarkPositionAsVisitedIMP(board, position);
	*path = pos;
	
	/*	recursively call 8 available positions 	*/
	NextPositionIMP
	
	/*	if path is not 0*/
	return (is_path_found);
	
}

/******************************************************************************/
static int NextPositionIMP(int curr_position, int direction)
{
	int new_position = -1;
	
	enum directions
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
	
	static const int MovePosition[8] = {-17, -15, -6, 10, 7, 17, 15, 6, -10}
	
	assert (0 <= direction & direction <= 7);
	
	new_position = curr_position + MovePosition[direction];
	
	return (IsPositionOutOfBoundsIMP(new_position) ? -1 : new_position);
}

/******************************************************************************/
static bitsarr_ty MarkPositionAsVisitedIMP(bitsarr_ty board, int position)
{
	return (BitArraySetOn(board, position));
}
/******************************************************************************/
static int IsPositionOutOfBoundsIMP(int position)
{
	return (position <= -1 ^ BOARD_SIZE <= position);
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
	
	*x = index / NUM_OF_ROWS;
	*y = index % NUM_OF_COLUMNS;
}
/******************************************************************************/
static int CartesianToIndexIMP(int *x, int *y)
{
	assert(x && y);
	
	return ((*x * NUM_OF_ROWS) + *y);
}
