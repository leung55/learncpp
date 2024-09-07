#include "random.h"
#include "input_handling.h"
#include <vector>
#include <string>
#include <iostream>
#include <cassert>

#ifdef DEBUG
int main() {
    int guessesLeft{Words::guesses};
    int numCorrectGuesses{0};
    char charGuessed{};
    std::vector<char> incorrectGuessedChars{};
    std::vector<char> correctGuessedChars{};
    std::string_view correctWord{getRandomWord()};
    std::size_t correctWordSize{correctWord.size()};
    std::vector<char> revealedChars(correctWordSize,'_');

    while(numCorrectGuesses < correctWordSize && guessesLeft > 0) {
        std::cout << "The word: ";
        for(char ch : revealedChars) {
            std::cout << ch;
        }
        std::cout << "\tWrong guesses: ";
        for(int i{0}; i < guessesLeft; ++i) {
            std::cout << '+';
        }
        for(char ch : incorrectGuessedChars) {
            std::cout << ch;
        }
        std::cout << "\nEnter your next letter: ";
        std::cin >> charGuessed;
        if(idxesOfMatchingChars(correctGuessedChars, charGuessed).size() > 0) {
            continue;
        }
        std::vector<std::size_t> correctPositionsGuessed{idxesOfMatchingChars(correctWord, charGuessed)};
        for(std::size_t idx : correctPositionsGuessed) {
            revealedChars[idx] = correctWord[idx];
            numCorrectGuesses++;
        }
        if(correctPositionsGuessed.size() == 0 && idxesOfMatchingChars(incorrectGuessedChars, charGuessed).size() == 0){
            incorrectGuessedChars.push_back(charGuessed);
            --guessesLeft;
        }
        else if(correctPositionsGuessed.size() > 0) {
            correctGuessedChars.push_back(charGuessed);
        }
        
    }
    if(numCorrectGuesses == correctWordSize) {
        std::cout << "Congrats, you guessed the correct word!\n";
    }
    else if(guessesLeft == 0) {
        std::cout << "You lost! The correct word was " << correctWord << '\n';
    }
    std::cout << "end";
    return 0;
}

std::vector<std::size_t> idxesOfMatchingChars(const auto& word, char charGuessed) {
    std::vector<std::size_t> idxs{};
    for(std::size_t i{0}; i < word.size(); ++i) {
        if(charGuessed == word[i]) {
            idxs.push_back(i);
        }
    }
    return idxs;
}
#endif
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

void revealMoreChars(const auto& correctWord, auto& revealedChars, const auto charGuessed, const std::size_t word_size, int& numCorrectGuesses) {
    assert(correctWord.size() == revealedChars.size());
    assert(correctWord.size() == word_size);
    for(std::size_t i{0}; i < word_size; ++i) {
        if(correctWord[i] == charGuessed) {
            assert(revealedChars[i] == '_');
            revealedChars[i] = charGuessed;
            ++numCorrectGuesses;
        }
    }
}

void addWrongGuess(auto& wrongGuessesChars, const auto charGuessed, const int wrongGuessesLeft, const int num_guesses) {
    assert(wrongGuessesLeft >= 0);

    //iterate from newly used up guess thru second last element for alphabetical ordering
    for(int i{wrongGuessesLeft}; i < num_guesses - 1; ++i) {
            //character guess is less than next element, place char guess at curr position
        if (charGuessed < wrongGuessesChars[i+1]) {
            wrongGuessesChars[i] = charGuessed;
            return;
        }
        //if not alphabetical order, move character in next idx to current idx, increment idx and test again
        wrongGuessesChars[i] = wrongGuessesChars[i+1];
    }
    //char guess is last alphabetically - make it last element
    wrongGuessesChars[num_guesses - 1] = charGuessed;
}

template <typename T>
T getUserChar(const std::vector<T>& revealedChars, const std::vector<T>& wrongGuessesChars) {
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

void playHangman(const int num_guesses, const std::string_view correctWord) {
    int wrongGuessesLeft{num_guesses};
    int numCorrectGuesses{0};
    char charGuessed{};
    const std::size_t correctWordSize{correctWord.size()};

    std::vector<char> incorrectGuessedChars{};
    std::vector<char> revealedChars(correctWordSize,'_');
    std::vector<char> wrongGuessesChars(num_guesses, '+');

    std::cout << "Welcome to C++man (a variant of Hangman)\nTo win: guess the word. To lose: run out of pluses.\n";

    while(numCorrectGuesses < correctWordSize && wrongGuessesLeft > 0) {
        charGuessed = getUserChar(revealedChars, wrongGuessesChars);

        //if character already guessed (correct or incorrect), ask for another guess
        if(isCharInWord(revealedChars, charGuessed) || isCharInWord(wrongGuessesChars, charGuessed)) {
            continue;
        }

        //if character is a correct guess, reveal the new characters to be shown on next guess and increase correct guess count
        if(isCharInWord(correctWord, charGuessed)) {
            revealMoreChars(correctWord, revealedChars, charGuessed, correctWordSize, numCorrectGuesses);
        }
        //else if character is incorrect, add it to wrong guesses vector
        else {
            --wrongGuessesLeft;
            addWrongGuess(wrongGuessesChars, charGuessed, wrongGuessesLeft, num_guesses);
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

int main() {
    playHangman(Words::guesses, getRandomWord());
    return 0;
}
