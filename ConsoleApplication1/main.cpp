/*
    Author: Adrian Vaflor
    Date: December 18, 2023

    Game Goal:
        Color Rush presents a puzzle in which players are provided with a 14x14 grid divided into colored regions.
        The objective is to fill the entire puzzle by coloring the top-left region using the fewest possible moves.

    Background:
        Color Rush is a copy of the Flood-It game made by LabPixies, an Israeli developer team, in March 2009.
        The puzzle has been proven to be NP-hard when the number of colors is greater than or equal to 3 (https://arxiv.org/abs/1001.4420).

    Solver:
        There are many heuristic approach to solve this game like Greedy and A*. But my approach is bruteforce, thinking 4 or 6 moves ahead, as I
        believe that it is enough to provide basis for the max turns. Like the heuristic approaches I mentioned, my solution does not
        guarantee optimal moves at all times, but the generated solutions beats me most of the time. It can actually find the most optimal moves
        at any color randomization (go to Grid.cpp, modify the numberOfMoves in solver, make it big like 1000 moves ahead), but the caveat is it will
        cost a lot of time and will not be playable.

    
    Future Plans:
        - Add blitz mode where players have to solve the grid for specific number of moves at a given time constraint.
        - Add multiplayer where two grids are displayed on screen and a change of the grid affects the other.
        - Add against computer as opposed to playing to friends
        - Make the screen resizable and automatically adjust the sprites.
        - Use unordered list for faster searching.
        - Improve the solver, probably shift from brute force and explore other approaches.
        - Improve graphics and add sound effects.
        - Add level reached statistics

    Notes:
        This may appear small in other laptop or pc becuse I did not consider varying screen resolutions.
        When it takes too long to set up the grid, modify the numberOfMoves in the solver.

*/


#include <iostream>
#include "Game.hpp"
#include "DEFINITIONS.hpp"

int main() {
    ColorRush::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Color Rush");
    return EXIT_SUCCESS;
}
