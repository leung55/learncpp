
#include "input_handling.h"
#include "random.h"
#include <array>
#include <random>
#include <algorithm>
#include <iostream>
#include <iterator>
namespace Moves {
    enum class moveSet {
        w,
        a,
        s,
        d,
        maxMoves,
    };
    moveSet& operator++( moveSet& c ) {
        using IntType = typename std::underlying_type<moveSet>::type;
        c = static_cast<moveSet>( static_cast<IntType>(c) + 1 );
        if ( c == moveSet::maxMoves )
            c = static_cast<moveSet>(0);
        return c;
    }
    moveSet& operator+=(moveSet& c, int inc) {
        using IntType = typename std::underlying_type<moveSet>::type;
        c = static_cast<moveSet>( static_cast<IntType>(c) + inc );
        if ( c == moveSet::maxMoves )
            c = static_cast<moveSet>(0);
        return c;
    }
    moveSet& operator--(moveSet& c) {
        using IntType = typename std::underlying_type<moveSet>::type;
        if(c == moveSet::w) {
            c = moveSet::d;
            return c;
        }
        c = static_cast<moveSet>( static_cast<IntType>(c) - 1 );
        return c;
    }
    moveSet operator++( moveSet &c, int ) {
        moveSet result = c;
        ++c;
        return result;
    }
}

using namespace Moves;
class FifteenPuzzle {
    using IntType = typename std::underlying_type<moveSet>::type;
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
        // std::random_device rd;
        // std::mt19937 g(rd());
        idxOf16 = 15;
        // std::shuffle(grid.begin(), grid.end(), g);
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
            moveSet randMove;
            //blank space in corner
            if(blankTopRight() || blankTopLeft() || blankBottomLeft() || blankBottomRight()) {
                randMove = static_cast<moveSet>(Random::get(0,1));
                if(blankTopRight())
                    move(moveChars[static_cast<IntType>(--randMove)]);
                else if(blankTopLeft())
                    move(moveChars[static_cast<IntType>(randMove)]);
                else if(blankBottomRight())
                    move(moveChars[static_cast<IntType>(randMove) + 2]);
                else if(blankBottomLeft())
                    move(moveChars[static_cast<IntType>(randMove) + 1]);
                continue;
            }
            //blank space on border but not corner
            else if(blankAtTop() || blankAtLeft() || blankAtRight() || blankAtBottom()) {
                randMove = static_cast<moveSet>(Random::get(0,2));
                if(blankAtTop())
                    move(moveChars[static_cast<IntType>(--randMove)]);
                else if(blankAtLeft())
                    move(moveChars[static_cast<IntType>(randMove)]);
                else if(blankAtRight())
                    move(moveChars[static_cast<IntType>(randMove += 2)]);
                else if(blankAtBottom())
                    move(moveChars[static_cast<IntType>(randMove) + 1]);
                continue;
            }
            //blank space in middle
            else {
                randMove = static_cast<moveSet>(Random::get(0,3));
                move(moveChars[static_cast<IntType>(randMove)]);
            }
            
        }
    }
    
#ifdef MOVE_SPACE
    void move() {
        char userMove{getUserMove()};
        bool moveSuccess{false};
        switch(userMove) {
            case 'w':
                if(idxOf16 - rowLen > 0) {
                    std::swap(grid[idxOf16 - rowLen], grid[idxOf16]);
                    idxOf16 -= rowLen;
                    moveSuccess = true;
                }
                break;
            case 'a':
                // space is not top-left corner and previous element doesn't wrap around to last element of above row
                if(idxOf16 > 0 && ((idxOf16 - 1) % rowLen != (rowLen - 1))) {
                    std::swap(grid[idxOf16 - 1], grid[idxOf16]);
                    idxOf16 -= 1;
                    moveSuccess = true;
                }
                break;
            case 's': 
                if(idxOf16 + rowLen < gridSize) {
                    std::swap(grid[idxOf16 + rowLen], grid[idxOf16]);
                    idxOf16 += rowLen;
                    moveSuccess = true;
                }
                break;
            case 'd': 
                // space is not bottom-right corner and next element isn't first element of next row
                if(idxOf16 < lastIdx && ((idxOf16 + 1) % rowLen != 0)) {
                    std::swap(grid[idxOf16 + 1], grid[idxOf16]);
                    idxOf16 += 1;
                    moveSuccess = true;
                }
                break;
            default:
                std::cout << "something went wrong.\n";
                return;
        }
        if(!moveSuccess) {
            std::cout << "Can't move that way.\n";
            return;
        }
        ++numMoves;
    }
#endif
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
                // space is not top-left corner and previous element doesn't wrap around to last element of above row
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
                // space is not bottom-right corner and next element isn't first element of next row
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