# The Knight’s Tour Problem – Backtracking Recursive Solutions

# Introduction

The knight’s tour puzzle is played on a chess board with a single chess piece, the knight. 

A knight is placed on any square of an empty board and, moving according to the rules of chess, must visit each square exactly once, like so:

![example of a knight tour](./images/knights-tour.gif) ![another example](./images/Knights-Tour-Animation.gif)

The Knight’s Tour is actually a mathematical (Hamiltonian Path) problem dating back centuries.  Many solutions have 
been proposed, ranging from brute force algorithms to neural networks.

# Data Structure

Since every square on the board can be either visited or not, and there are 64 squares (for a standard chess board 8X8), we can use a **Bit Array**.

I have implemented a bit array that will be used in this program: [API](./api/bit_array.h), [Source code](./src/bit_array.c).

We will treat the chess board as 64 bits, which will be either 0 or 1 to indicate if the knight has visitied a certain sqaure on the board.
- '0' its the initial state of all the bits which means that no square has been visitied yet by the knight.
- '1' means the the square has been visited by the knight and **cannot be visited again in the same tour**.

# Validate Legal Position

**Each sqaure has 8 potential directions for the knight to go to.
But not all squares have 8 valid options because sometimes some of the steps will move the knight beyond board boundries 
i.e if we are looking at the chess board as a bit array whcih in 0 is first square on the board (top left corener) and 63 is the last square on the board (bottom right corner) so 65 is out of boundries as well as -1 and negative numbers.**
In my implementation, I use `Cartesian to Index` and `Index to Cartesian` converstion to convert indexes (0,1,2,...63) to (row,column) format.
For example:
* 0 -> 0,0
* 9 -> 1,1 (I start counting from 0).
* 0,1 -> 8

and in this way, its easier to check if the next move brings the knight to an illegal position (out of boundries for example if the row or column number is not in the range of 0-7).

![knight rules](./images/knight_rules.png)

# Naive Algorithm - Brute Force Solution

The Naive Algorithm is to generate all tours one by one and check if the generated tour satisfies the constraints (a square can be visited only once and the knight must stay in board boundries).
Typically, we start from an empty bit map and one by one add moves and steps. When we add a move, we check if adding the square that the knight reached to violates the problem constraint, if it does then we try other alternatives. If none of the alternatives works out then we go to the previous stage and remove the square/step added in the previous stage. If we reach the initial stage back then we say that no solution exists. If adding a step that doesn’t violate constraints then we recursively add moves/squares one by one. If the solution bit map becomes complete (all bits are set - means all squares have been visited) then we print the solution.

The knight will start from an empty square and then just try each option out of the 8 potential future moves.

The upper bound on the number of possible legal tours for an eight-by-eight chessboard is known to be ![equation](http://www.sciweavers.org/tex2img.php?eq=%201.305%C3%9710351.305%20%5Ctimes%2010%5E%7B35%7D1.305%C3%9710%E2%80%8B35%E2%80%8B%E2%80%8B&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=0).
However, there are even more possible dead ends. Clearly this is a some real computing power, or a lot of time.
There are `N^2` Cells and for each, we have a maximum of 8 possible moves to choose from, so the worst running time is `O(8N^2)`.
For that exact reason, I have also added a timeout of 2 minutes (or any other time if you want to change it) for finding a solution.

### Backtracking naive brute-force algorithm:

```
If timeout has reached
    terminate - no solution in reasonable time
If all squares are visited (all bits are set to 1)
    print the solution
If current square is illegal (out of boundries OR has been already visited)
    return failure
Else
   a) Add one of the next moves to solution bit map and recursively 
   check if this move leads to a solution (does't return failure). (A Knight can make maximum 
   eight moves. We choose one of the 8 moves in this step).
   
   b) If the move chosen in the above step doesn't lead to a solution (returns failure),
   then remove this move from the solution bit map and try other 
   alternative moves.
   
   c) If none of the alternatives work then return false (Returning false 
   will remove the previously added item in recursion and if false is 
   returned by the initial call of recursion then "no solution exists" )
   
  ```













