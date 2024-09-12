
#include "input_handling.h"
#include "random.h"
#include <array>
#include <random>
#include <algorithm>
#include <iostream>
#include <iterator>

class FifteenPuzzle {
    static constexpr int rowLen{4}, colLen{4}, gridSize{rowLen*colLen};
    std::array<int,gridSize> grid{};
    const std::array<char,4> moveChars{'w','a','s','d'};
    static constexpr int blankNum{gridSize};
    static constexpr int lastIdx{gridSize - 1};
    int idxOf16{};
    int numMoves{0};
    
public:
    FifteenPuzzle() {
        for(std::size_t i{0}; i < grid.size(); ++i) {
            grid[i] = i + 1;
        }
        idxOf16 = 15;
        scramble();
        std::copy(grid.begin(), grid.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
        idxOf16 = (std::find(grid.begin(), grid.end(), blankNum)) - grid.begin();
        std::cout << "16 idx: " << idxOf16 << '\n';
    }
    bool blankAtTop() {return idxOf16 - rowLen < 0;}
    bool blankAtLeft() {return idxOf16 == 0 || ((idxOf16 - 1) % rowLen == (rowLen - 1));}
    bool blankAtRight() {return idxOf16 == lastIdx || ((idxOf16 + 1) % rowLen == 0);}
    bool blankAtBottom() {return idxOf16 + rowLen > lastIdx;}
    bool blankTopRight() {return blankAtTop() && blankAtRight();}
    bool blankTopLeft() {return blankAtTop() && blankAtLeft();}
    bool blankBottomLeft() {return blankAtBottom() && blankAtLeft();}
    bool blankBottomRight() {return blankAtBottom() && blankAtRight();}
    void scramble() {
        int scrambleNum{Random::get(100,200)};
        for(int i{0}; i < scrambleNum; ++i) {
            std::size_t randMove;
            //blank space in corner
            if(blankTopRight() || blankTopLeft() || blankBottomLeft() || blankBottomRight()) {
                randMove = Random::get(0,1);
                if(blankTopRight()) //only 'w' and 'd'
                    move(moveChars[(randMove + 3) % 4]);
                else if(blankTopLeft()) //only 'w' and 'a'
                    move(moveChars[randMove]);
                else if(blankBottomRight()) //only 's' and 'd'
                    move(moveChars[randMove + 2]);
                else if(blankBottomLeft()) //only 'a' and 's'
                    move(moveChars[randMove + 1]);
                continue;
            }
            //blank space on border but not corner
            else if(blankAtTop() || blankAtLeft() || blankAtRight() || blankAtBottom()) {
                randMove = Random::get(0,2);
                if(blankAtTop()) //only 'w' 'a' 'd'
                    move(moveChars[(randMove + 3) % 4]);
                else if(blankAtLeft()) //only 'w' 'a' 's'
                    move(moveChars[randMove]);
                else if(blankAtRight()) //only 'w' 's' 'd'
                    move(moveChars[(randMove + 2) % 4]);
                else if(blankAtBottom()) //only 'a' 's' 'd'
                    move(moveChars[randMove + 1]);
                continue;
            }
            //blank space in middle
            else {
                randMove = Random::get(0,3);
                move(moveChars[randMove]);
            }
        }
    }
    bool move(char userMove) {
        bool moveSuccess{false};
        switch(userMove) {
            case 's':
                if(!blankAtTop()) {
                    std::swap(grid[idxOf16 - rowLen], grid[idxOf16]);
                    idxOf16 -= rowLen;
                    moveSuccess = true;
                }
                break;
            case 'd':
                if(!blankAtLeft()) {
                    std::swap(grid[idxOf16 - 1], grid[idxOf16]);
                    idxOf16 -= 1;
                    moveSuccess = true;
                }
                break;
            case 'w': 
                if(!blankAtBottom()) {
                    std::swap(grid[idxOf16 + rowLen], grid[idxOf16]);
                    idxOf16 += rowLen;
                    moveSuccess = true;
                }
                break;
            case 'a': 
                if(!blankAtRight()) {
                    std::swap(grid[idxOf16 + 1], grid[idxOf16]);
                    idxOf16 += 1;
                    moveSuccess = true;
                }
                break;
            default:
                std::cout << "something went wrong.\n";
                return moveSuccess;
        }
        if(!moveSuccess) {
            std::cout << "Can't move that way.\n";
        }
        return moveSuccess;
    }
    void playGame() {
        std::cout << "Welcome to 15 puzzle - try to sort the grid\n";
        while(!std::is_sorted(grid.begin(), grid.end())) {
            printGrid();
            if(move(getUserMove()))
                numMoves++;
        }
        printGrid();
        std::cout << "Congrats, you solved the puzzle!\n";
    }
    char getUserMove() {
        char userMove;
        std::cout << "Move [w,a,s,d]: ";
        while(true) {
            std::cin >> userMove;
            if(InputHandling::clearFailedExtraction() || !(userMove == 'w' || userMove == 'a' || userMove == 's' || userMove == 'd')) {
                std::cout << "Bad input, try again [w,a,s,d]: ";
                continue;
            }
            InputHandling::ignoreLine();
            return userMove;
        }
    }

    void printGrid() {
        for(int i{0}; i < 4; ++i) {
            for(int j{0}; j < 4; ++j) {
                if(grid[4*i+j] != 16)
                    std::cout << grid[4*i+j];
                else
                    std::cout << "  ";
                std::cout << ' ';
                if(grid[4*i+j] < 10)
                    std::cout << ' ';
            }
            std::cout << '\n';
        }
        std::cout << "blank idx: " << idxOf16 << '\n';
        std::cout << "moves: " << numMoves << '\n';
    }
};

int main() {
    FifteenPuzzle fp{};
    fp.playGame();
    return 0;
}