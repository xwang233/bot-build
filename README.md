## AI bot build 
This repo features some AI bot build I wrote for fun, mainly those code challenges from 
[Hackerrank](https://www.hackerrank.com/domains/ai) AI section. 

## Battleship 

I used a probability-based hit strategy. 
Please check [battleship-cpp/readme.md](battleship-cpp/readme.md) for details. 

## Tic-Tac-Toe 

By using minimax strategy, with alpha-beta pruning, all games are tied. 
(Unless your opponent's AI sucks.)

Please check [tic-tac-toe/readme.md](tic-tac-toe/readme.md) for details.

## Checkers (Draughts)

I used minimax strategy with alpha-beta pruning. 
My next step is to introduce more parameters and static/dynamic evaluators, 
and optimize them by playing against another bot. 

Visualization for checkers is added! Front-end with *javascript* is forked from 
*codethejason* with bug-fix. I wronte the back-end using *C++* and *dlib* for 
networking. The back-end is dynamically linked to the checkers repo. 

Please check [checkers-cpp/readme.md](checkers-cpp/readme.md) and 
[checkers-visualize/readme.md](checkers-visualize/readme.md) for details. 

## License 

MIT