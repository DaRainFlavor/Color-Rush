# Color Rush

**Author:** Adrian Vaflor  
**Date:** December 18, 2023

## Game Goal
Color Rush presents a puzzle in which players are provided with a 14x14 grid divided into colored regions. The objective is to fill the entire puzzle by coloring the top-left region using the fewest possible moves.

## Background
Color Rush is inspired by the Flood-It game made by LabPixies, an Israeli developer team, in March 2009. The puzzle has been proven to be NP-hard when the number of colors is greater than or equal to 3. [More information](https://arxiv.org/abs/1001.4420).

This project builds upon my previous work from CMSC 21 Fundamentals of Programming (2nd Semester 2022-2023), where I initially developed the game. In this iteration, I enhanced it by adding a solver, which was completed as part of my project for CMSC 123 Data Structures (1st Semester AY 2023-2024).

## Solver
There are many heuristic approaches to solve this game like Greedy and A*. My approach is brute force, thinking 4 or 6 moves ahead, as I believe it is enough to provide a basis for the max turns. Like the heuristic approaches I mentioned, my solution does not guarantee optimal moves at all times, but the generated solutions beat me most of the time. It can actually find the most optimal moves at any color randomization (go to `Grid.cpp`, modify the `numberOfMoves` in the solver, make it big like 1000 moves ahead), but the caveat is it will cost a lot of time and will not be playable.

## Future Plans
- Add blitz mode where players have to solve the grid for a specific number of moves within a given time constraint.
- Add multiplayer where two grids are displayed on screen and a change in one grid affects the other.
- Add the option to play against the computer as opposed to playing against friends.
- Make the screen resizable and automatically adjust the sprites.
- Use unordered lists for faster searching.
- Improve the solver, possibly shifting from brute force to explore other approaches.
- Improve graphics and add sound effects.
- Add level reached statistics.

## Notes
This may appear small on other laptops or PCs because I did not consider varying screen resolutions. When it takes too long to set up the grid, modify the `numberOfMoves` in the solver.

## Trailer
Access it here: [Trailer](https://drive.google.com/drive/folders/1EFhOWdhmeGD8x9twkMiNhnSj1c8-1Jvf?usp=sharing)
