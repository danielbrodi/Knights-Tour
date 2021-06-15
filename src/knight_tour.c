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


/******************************************************************************/
int Tour(int position, unsigned char path[64])
{
	/*	create board of 8X8 as an unsigned long (64 bits) 			*/
	unsigned long board = 0;
	
	/*	create path array which will store the right path (if exists)	*/
	/*	a '1' bit will indicate on a visited location on the board 		*/ 
	unsigned char path[64] = {0};
	
	/*	asserts*/
	assert(position > -1);
	assert(path);
	
	return (TourImp(path, position, board, 1));
}
/******************************************************************************/
int TourImp(unsigned char path[64], int pos, unsigned long board, int step_num)
{
	size_t is_path_found = 1;
	
	/*	asserts*/
	assert(path);
	
	/*	if this is the last step*/
	/*		update path to be as board*/
	/*		return 0*/
	if (64 == step_num)
	{
		board ^= (1 << pos);
		path = board;
		return (0);
	}
	
	/*	if this is step leads out of bounds or to a previously visited location */
	/*		return 1*/
	if (63 < pos || board & (1 << pos))
	{
		return (1);
	}


	/*	increment step and tick curr position at the board*/
	++step_num;
	
	board ^= (1 << pos);
		
	/*	recursively call 8 available positions 	*/
	is_path_found = (TourImp(path, RIGHT_UP(pos), board, step_num)
	& TourImp(path, RIGHT(pos), board, step_num)
	& TourImp(path, RIGHT_DOWN(pos), board, step_num)
	& TourImp(path, DOWN(pos), board, step_num)
	& TourImp(path, LEFT_DOWN(pos), board, step_num)
	& TourImp(path, LEFT(pos), board, step_num)
	& TourImp(path, LEFT_UP(pos), board, step_num;
	& TourImp(path, UP(pos), board, step_num));
	
	/*	if path is not 0*/
	return (is_path_found);
	
}
