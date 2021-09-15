# The Knight’s Tour Problem – Implementation of the Heuristic & the Naive Solutions

# Introduction

The knight’s tour puzzle is played on a chess board with a single chess piece, the knight. 

A knight is placed on any square of an empty board and, moving according to the rules of chess, must visit each square exactly once, like so:

![example of a knight tour](./images/knights-tour.gif) ![another example](./images/Knights-Tour-Animation.gif)

The Knight’s Tour is actually a mathematical (Hamiltonian Path) problem dating back centuries.  Many solutions have 
been proposed, ranging from brute force algorithms to neural networks.

# Data Structure

Since every square on the board can be either visited or not, and there are 64 squares (for a standard chess board 8X8), we can use a **Bit Array**.

I have implemented a bit array: [API](./api/bit_array.h), [Source code](./src/bit_array.c).

We will treat the chess board as 64 bits, which will be either 0 or 1 to indicate if the knight has visitied a certain sqaure on the board.
- '0' its the initial state of all the bits which means that no square has been visitied yet by the knight.
- '1' means the the square has been visited by the knight and **cannot be visited again in the same tour**.

# Naive Algorithm - Brute Force Solution








