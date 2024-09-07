#include "random.h"
#include "input_handling.h"
#include <vector>
#include <string>
#include <iostream>
#include <cassert>

namespace Words {
    std::vector<std::string_view> list {
        "blue",
        "game",
        "mouse",
        "hangman"
    };

    const std::size_t list_length{list.size()};

    constexpr int guesses{5};
}

template <typename T>
std::ostream& operator<<(std::ostream& out, std::vector<T> ch_vec) {
    for(const auto& ch : ch_vec) {
        out << ch;
    }
    return out;
}

std::string_view getRandomWord() {
    return Words::list[Random::get(0,Words::list_length - 1)];
}

bool isCharInWord(const auto& word, const char ch_test) {
    for(const auto& ch : word) {
        if(ch == ch_test)
            return true;
    }
    return false;
}

template <typename T>
class Session {
    const int               numGuesses;
    const std::string_view  correctWord;
    const std::size_t       correctWordSize;
    int                     wrongGuessesLeft;
    int                     numCorrectGuesses;
    char                    charGuessed;
    std::vector<T>          incorrectGuessedChars;
    std::vector<T>          revealedChars;
    std::vector<T>          wrongGuessesChars;
    
public:
    Session(
            const int               numGuesses,
            const std::string_view  correctWord
    )
    : numGuesses           {numGuesses}
    , correctWord          {correctWord}
    , correctWordSize      {correctWord.size()}    
    , wrongGuessesLeft     {numGuesses}    
    , numCorrectGuesses    {0}        
    , charGuessed          {}
    , incorrectGuessedChars{}            
    , revealedChars        (this->correctWordSize, '_')    
    , wrongGuessesChars    (numGuesses, '+') {}

    T getUserChar() {
        T userChar{};
        while(true) {
            std::cout << "The word: " << revealedChars << "\tWrong Guesses: " << wrongGuessesChars <<"\nEnter your next letter: ";
            std::cin >> userChar;
            if(InputHandling::clearFailedExtraction() || userChar < 'a' || userChar > 'z') {
                InputHandling::ignoreLine();
                continue;
            }
            InputHandling::ignoreLine();
            return userChar;
        }
    }

    void revealMoreChars() {
        for(std::size_t i{0}; i < correctWordSize; ++i) {
            if(correctWord[i] == charGuessed) {
                assert(revealedChars[i] == '_');
                revealedChars[i] = charGuessed;
                ++numCorrectGuesses;
            }
        }
    }
    void addWrongGuess() {
        assert(wrongGuessesLeft >= 0);

        //iterate from newly used up guess thru second last element for alphabetical ordering
        for(int i{wrongGuessesLeft}; i < numGuesses - 1; ++i) {
                //character guess is less than next element, place char guess at curr position
            if (charGuessed < wrongGuessesChars[i+1]) {
                wrongGuessesChars[i] = charGuessed;
                return;
            }
            //if not alphabetical order, move character in next idx to current idx, increment idx and test again
            wrongGuessesChars[i] = wrongGuessesChars[i+1];
        }
        //char guess is last alphabetically - make it last element
        wrongGuessesChars[numGuesses - 1] = charGuessed;
    }

    void playHangman() {
        std::cout << "Welcome to C++man (a variant of Hangman)\nTo win: guess the word. To lose: run out of pluses.\n";

        while(numCorrectGuesses < correctWordSize && wrongGuessesLeft > 0) {
            charGuessed = getUserChar();

            //if character already guessed (correct or incorrect), ask for another guess
            if(isCharInWord(revealedChars, charGuessed) || isCharInWord(wrongGuessesChars, charGuessed)) {
                continue;
            }

            //if character is a correct guess, reveal the new characters to be shown on next guess and increase correct guess count
            if(isCharInWord(correctWord, charGuessed)) {
                revealMoreChars();
            }
            //else if character is incorrect, add it to wrong guesses vector
            else {
                --wrongGuessesLeft;
                addWrongGuess();
            }
        }
        std::cout << "The word: " << revealedChars << "\tWrong Guesses: " << wrongGuessesChars <<"\n";
        if(numCorrectGuesses == correctWordSize) {
            std::cout << "Congrats, you guessed the correct word!\n";
        }
        else if(wrongGuessesLeft == 0) {
            std::cout << "You lost! The correct word was " << correctWord << '\n';
        }
    }
};

int main() {
    Session<char> s{Words::guesses, getRandomWord()};
    s.playHangman();
    return 0;
}
