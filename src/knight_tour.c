/*********************************FILE__HEADER*********************************\
* File:				knight_tour.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				14-06-2021
* Code Reviewer:	Ariel					   								
* Version:			2.0  								
* Description:		Implementation of a basic and heuristic solutions for
					The Knight’s Tour problem, using a bit array.
\******************************************************************************/

/********************************* Inclusions *********************************/

#include <assert.h>		/*	assert					*/
#include <stddef.h>		/*	size_t, NULL			*/
#include <stdlib.h>		/*	exit, qsort				*/
#include <stdio.h>		/*	puts					*/
#include <time.h> 		/*	time_t, difftime		*/

#include "bit_array.h"	/* bits array operations	*/
#include "knight_tour.h"

/******************************* macros & enums *******************************/

/* properties of the played chess board		*/
enum board
{ 
	NUM_OF_ROWS = 8,
	NUM_OF_COLUMNS = 8,
	NUM_OF_DIRECTIONS = 8,
	BOARD_SIZE = NUM_OF_ROWS * NUM_OF_COLUMNS
};

typedef enum possibilities_lut_status
{
	NOT_INITIALIZED,
	INITIALIZED
} possibilities_lut_status_ty;

enum
{
	TWO_MINUTES = 120
};

static int possible_moves_lut[64] = {0};
static int next_positions_lut[64][8] = {0};

static possibilities_lut_status_ty possible_moves_lut_status = NOT_INITIALIZED;

/**************************** Forward Declarations ****************************/


/*	recursively runs through all the options to cover the whole board 	*/
static int TourIMP(unsigned char path[BOARD_SIZE], int position, 
												bitsarr_ty board, time_t timer);

/*	initalizes LUT's of the future moves of each position 
 *	on the first run of the program 						*/
static void InitPossibleMovesLutIMP(void);

/*	creates a LUT of 512 : 8 possible moves for each position (64 positions).
 *	creates a LUT of 64: each index will store the amount of legitimate moves,
 *	which keep the knight in bounds of the board.			*/												
static void CreatePossibleMovesLutIMP(void);

/*	the huristic solution to find a path in the fastest way based on
 *	moving each time to the location with the minimum 
 *	number of unvisited adjacent										*/															
static int HeuristicTourIMP(unsigned char path[BOARD_SIZE], int position,
												bitsarr_ty board);						
/*	direction is 0-7, position is 0-63.
 *	Returns -1 if move in direction takes you out of the board			*/
static int GetNextPositionIMP(int current_position, int direction);

/*	converts a given index to x and y coordinates of 0-7 each one 		*/
static void IndexToCartesianIMP(int index, int *x_coordinate, int *y_coordinate);

/*	converts x and y coordinates into an index of 0-63					*/
static int CartesianToIndexIMP(int x_coordinate, int y_coordinate);

/*	checks if a given position is out of bounds of the board.
 *	returns 1 if the given position is out of the board, 0 otherwise.	*/
static int IsPositionOutOfBoundsIMP(int x_coordinate, int y_coordinate);

/*	checks if a given position has been marked as visited 				*/
static int HasPositionBeenVisitedBeforeIMP(bitsarr_ty board, int position);

/*	marks a given position on the board as visited						*/
static bitsarr_ty MarkPositionAsVisitedIMP(bitsarr_ty board, int position);

/*	compares two given positions. Returns:
 *	Positive value if the first position has more legitimate available moves
 	than the other position.
 *	0 if both positions have the same amount of legitimate available moves.
 *	Negative value otherwise.	*/
static int ComparePositionsIMP(const void *data1, const void *data2);

/************************* Functions  Implementations *************************/
int Tour(int position, unsigned char path[BOARD_SIZE])
{
	/*	creates a chess board of 8X8 as a type of `bitsarr_ty` which
	 *	is a type of 64 bits 			*/
	bitsarr_ty board = 0;
	
	time_t start_time = time(&start_time);
	
	/*	asserts*/
	assert(position > -1 && position < 64);
	assert(path);
	
	/*	the naive and simple solution	*/
/*	return (TourIMP(path, position, board, start_time));*/
	
	/*	the heuristic solution	*/
	return (HeuristicTourIMP(path, position, board));
}
/******************************************************************************/
int TourIMP(unsigned char path[BOARD_SIZE], int position, bitsarr_ty board,
																time_t timer)
{	
	int direction_to_go = 0;
	
	int position_x_coordinate = 0, position_y_coordinate = 0;
	
	time_t curr_time = time(&curr_time);
	
	IndexToCartesianIMP(position, &position_x_coordinate,
														&position_y_coordinate);
	
	/*	asserts*/
	assert(path);
	
	/*	initalizes LUT of position and their future position based on each 
	 *	direction. Initalized only on the first run of the program			*/
	if (NOT_INITIALIZED == possible_moves_lut_status)
	{
		InitPossibleMovesLutIMP();
		possible_moves_lut_status = INITIALIZED;
	}
	
	/* timout of 2 minutes - if no solution has been found - exit the program */
	if (difftime(curr_time, timer) >= TWO_MINUTES)
	{
		puts("Timeout Error: no solution has been found.");
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
            /* save the position that's correct in path array before exiting*/
            *path = position;
            
            return (0);
        }
    }
	
	return (1);
}
/******************************************************************************/
int GetNextPositionIMP(int curr_position, int direction)
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
	return (x_coordinate >= NUM_OF_COLUMNS || y_coordinate >= NUM_OF_ROWS ||
			x_coordinate < 0 || y_coordinate < 0);
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
	assert(x_coordinate >= 0 && y_coordinate >= 0 && 
				y_coordinate < NUM_OF_ROWS && x_coordinate < NUM_OF_COLUMNS);
	
	return ((y_coordinate * NUM_OF_ROWS) + x_coordinate);
}
/******************************************************************************/
void InitPossibleMovesLutIMP(void)
{
	if (NOT_INITIALIZED == possible_moves_lut_status)
	{
		CreatePossibleMovesLutIMP();
		possible_moves_lut_status = INITIALIZED;
	}
}
/*----------------------------------------------------------------------------*/
void CreatePossibleMovesLutIMP(void)
{
	int curr_position = 0, direction = 0, next_position = 0;
		
	/*	creates a LUT of 512 : 8 possible moves for each position.
	 *	some of the 8 possible moves may be invalid and out of bounds. */
	for (curr_position = 0; curr_position < BOARD_SIZE; ++curr_position)
	{
		for (direction = 0; direction < NUM_OF_DIRECTIONS; ++direction)
		{
			 next_position = GetNextPositionIMP(curr_position, direction);
			 
			 next_positions_lut[curr_position][direction] = next_position;
			 
			 /*	creates a LUT of 64: each index will store the amount of 
			  *	legitimate moves, which keep the knight in
			  *	bounds of the board.			*/
			 if (-1 != next_position)
			 {
			 	++possible_moves_lut[curr_position];
			 }
		}
	}
	
	/*	for each position, sort the possible future positions based on the
	 *	amount of their future legitimate moves. The array will be sorted from
	 *	the minimum to the maximum legitimate future positions.		*/ 
	 
	for (curr_position = 0; curr_position < BOARD_SIZE; ++curr_position)
	{
		qsort(next_positions_lut + curr_position, NUM_OF_DIRECTIONS, 
											sizeof(int), ComparePositionsIMP);
	}
}
/******************************************************************************/
int HeuristicTourIMP(unsigned char path[BOARD_SIZE], int position,
															bitsarr_ty board)
{	
	int position_x_coordinate = 0, position_y_coordinate = 0;
	
	int direction = 0, num_of_possible_directions = 0;
	
	/*	asserts*/
	assert(path);
	
	IndexToCartesianIMP(position, &position_x_coordinate, 
														&position_y_coordinate);
	
	/* initalize both LUT's	on the first run of the program	*/
	InitPossibleMovesLutIMP();
	
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
	
	/*	mark curr position at the board*/	
	board = MarkPositionAsVisitedIMP(board, position); 
	
	/*	count the number of legitimate possible moves out of 8 */
	num_of_possible_directions = 
							NUM_OF_DIRECTIONS - possible_moves_lut[position];
	
	/*	try each location from the sorted array but after skipping all the
	 *	invalid locations which indicated by (-1), which means they will
	 *	be shown in the beginning of the array and the first valid location
	 *	will appear on index of (num_of_directions - legitimate_future_moves) */
	 
	for (direction = num_of_possible_directions; direction < NUM_OF_DIRECTIONS;
																	++direction)
	{
		if (!HeuristicTourIMP(path + 1, next_positions_lut[position][direction],
																		board))
		{
			/* save the position that's correct in path array before exiting*/
			*path = position;

			return (0);
		}
	}

	return (1);
}
/******************************************************************************/
int ComparePositionsIMP(const void *data1, const void *data2)
{
	int position1 = 0, position2 = 0;
	
	assert(data1);
	assert(data2);
	
	position1 = *(int*)data1;
	position2 = *(int*)data2;
	
	return (possible_moves_lut[position1] - possible_moves_lut[position2]);
}
/******************************************************************************/
