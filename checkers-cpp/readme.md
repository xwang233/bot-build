Link: https://www.hackerrank.com/challenges/checkers

## My ranking and strategy
36/225 using `eval2()` with depth = 6 Minimax algorithm and Alpha-Beta pruning. 

Evaluation function `checkers::eval2()` refers strategy from https://github.com/kevingregor/Checkers. 
(With my own code)

Each pawn scores 5 points, each king scores 7.75 points, each piece in backrow scores 4 extra points, 
each piece in the mid-4 slots scores 2.5 extra points, each piece in the mid-side-4 slots 
scores 0.5 extra points, each vulnerable piece scores -3 points. 
Each protected piece scores 3 points, which has not been implemented yet. 
The final evaluation is your score minus your opponent's score. 

My next step is to introduce more parameters and static/dynamic evaluators, 
and use Machine Learning to optimize them, 
by playing against another bot. 

Visualizations of checkers game in *javascript* is added. Front-end *js* is a 
fork from [codethejason](https://github.com/codethejason/checkers) with bug-fix. 
I wrote the back-end using *C++* and 
[dlib](https://github.com/davisking/dlib) for networking, 
and the back-end is dynamically linked to this repo. 

## Short usage of the code 

If you want to use this code to read from **stdin** or compete on Hackerrank, 
use the main() function in `main.cpp_`. 

If you want to play against another bot, use the first `main()` function 
in `random_move.cpp`. 
The 
```c
#pragma omp parallel for
```
line is the OpenMP parallel code, which can easily use all of your CPU cores to 
let the bots play against each other:)

The second `main2()` function in `random_move.cpp` is used for debugging. 


## Description
Checkers or Draughts is a popular 2 player board game where the opponent discs are captured by jumping over them. The objective of the game is to capture as many discs of the opponent as possible or if the opponent has no valid moves left to make.

The game takes place on an 8 * 8 chess board as shown below.

![Draughts](draughts.png)

Each player occupies one of the 2 sides of the chess board where the pawns are placed. Black goes first.

## Rules

* Each player begins with 12 colored discs.
* The discs are positioned such that each player has a light square on the right side corner closest to him or her.
* Each player places his or her discs on the 12 dark squares closest to him or her.
* Black moves first and players alternate henceforth.
* Moves are allowed only on the dark squares, so the discs always move diagonally. discs are always limited to forward moves ( toward the opponent ).
* There are 2 kinds of moves - Capturing and Non-Capturing moves. In both types of moves, player can only move/jump to a vacant position.
* Non-Capturing moves may move only one square.
* If more than 1 Non-Capturing moves exist, any of the moves can be played.
* A disc making a Capturing move leaps over one of the opponent's discs that is 1 square away from itself and lands in a straight diagonal line, which is 2 squares away from itself. A jump can make only 1 capture, but the same disc can capture multiple opponent discs by doing multiple jumps in a single move.
* A captured disc is removed from the board.
* If a Capturing move exists, the jump has to be made. If more than one capture exists, a choice can be made.
* A player reaching the opponent's side of the board is crowned as a King. King's move is similar to that of a regular disc's move but restriction of forward only moves are lifted for the King's move. Multiple King's may exist.
* White discs are present at the bottom of the board and the black discs are present at the top of the board.

Black discs are represented by character 'b' (ascii value 98) and white discs are represented by character 'w' (ascii value 119). King's of respective discs are represented by 'B' (ascii value 66) and 'W' (ascii value 87). Empty squares are represented by character '_' ( ascii value 95)

## Input Format

The first line of the input contains the player's character 'b' or 'w' indicating the player's turn. 
The second line contains the size of the board (L). 
L lines follow each containing L characters as mentioned above.

## Output Format

For a Non-Capturing move, print 3 lines. 
The first line containing the number 1 indicating 1 hop has been made. 
The second line contains 2 space separated integers indicating the position of the disc to be moved. 
The third line contains 2 space separated integers indicating the new position of the disc.

For a Capturing move, 
the first line contains an integer indicating the number of hops (H) made while capturing. H+1 lines follow. 
The first line contains 2 space separated integers indicating the disc that is making the capture. 
H lines follow each line indicating the new position to which the disc has hopped to.

## Sample Input: Non-Capturing

```
b
8
_______W
b_______
___b____
________
_w______
w_____w_
_______b
w_____w_
```
## Sample Output: Non-Capturing

```
1
1 0
2 1
```
## Explanation: Non-Capturing

It is black's turn. A black disc is moved from 1 0 to 2 1.

## Sample Input: Capturing

```
w
8
________
b_b_b_b_
___b____
__b_____
_w______
w_b___w_
_w_____b
w_____w_
```
## Sample Output: Capturing

```
5
6 1
4 3
2 1
0 3
2 5
0 7
``` 
## Explanation: Capturing

It is white's turn. A single disc placed at 6 1 hops to 4 3 capturing black disc along 5 2, captures another black disc at 3 2 and hops to 2 1, captures yet another disc at 1 2 and hops to 0 3. At 0 3, it turns into a King disc. Now it is allowed to move backwards as well. It captures another black disc at 1 4 and moves to 2 5 and captures its final black disc at 1 6 and moves to 0 7.