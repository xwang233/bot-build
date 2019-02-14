Link: https://www.hackerrank.com/challenges/battleship

## My ranking 
29/783

## Description
Battleship is a popular 2-player game that takes place a 10 x 10 board. Ships
of various sizes are placed on the 10 x 10 board either horizontally or
vertically. The position of the ships are hidden to the user. Your task is to
sink all the ships.

Ships of the following size are given to each player.

Submarine (1 x 1) - 2 nos
Destroyer (2 x 1) - 2 nos
Cruiser (3 x 1) - 1 nos
Battleship(4 x 1) - 1 nos
Carrier (5 x 1) - 1 nos
In this version of the game, you will initially specify the positions of your
ships in a specific format and then start attacking the positions of your
opponent.

## Note

You can place the ships side by side.

## Input Format

The very first move would be a 4 letter word "INIT* which indicates that you are
to place your ships. The next set of moves follow the format as mentioned below.

First line contains N indicating the size of the board. N lines follow each line
contains 10 characters. If a cell is hit, it is denoted by character h (ascii
value 104), if a cell is a miss it is denoted by character m (ascii value 109),
if all the positions of a ship is destroyed, each of its position of the board
is denoted by character d ( ascii value 100 ). If a cell is not attacked by the
player, it is denoted by the character - (ascii value 45).

The board is indexed according to Matrix Convention

## Constraints

N = 10

## Output Format

For the very first move. Print the ships in the following format. In ascending
order of the size of each ship, print the start and end position of the ship.
For submarines, just print the start position. Sample output for ship positions
is shown below.

0 0
4 2
6 4:7 4
3 7:3 8
7 7:7 9
1 4:4 4
4 0:8 0
For the next set of moves,

Output the cell to be hit in your current move. The output consists of two
integers R and C separated by a single space.

## Sample Input:1

```
INIT
```
## Sample Output:1

```
0 0
4 2
6 4:7 4
3 7:3 8
7 7:7 9
1 4:4 4
4 0:8 0
```
## Explanation

Two submarines are positioned at (0,0) and (4,2). Each destroyer is positioned
inbetween (6,4)->(7,4) and (3,7)->(3,8) respectively. 1 cruiser is positioned
horizontally from (7,7)->(7,9). 1 battleship is positioned vertically from
(1,4)->(4,4). 1 carrier is positioned vertically from (4,0)->(8,0).

Start and end position of the ships can be interchanged.

## Sample Input:2

```
10
----------
----------
--------m-
----------
--d-----m-
---m-m----
------m---
-m---mmhh-
--m-------
------m---
```

## Sample Output:2

```
7 9
```
## Resultant Board

```
10
----------
----------
--------m-
----------
--d-----m-
---m-m----
------m---
-m---mmddd
--m-------
------m---
``` 
Here, a ship was hit at row 7 and column 9. As the ship was completely
destroyed, (7,7), (7,8) and (7,9) each are represented by character d.
