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
            const std::string_view  correctWord,
            const std::size_t       correctWordSize,
            int                     wrongGuessesLeft,
            int                     numCorrectGuesses,
            char                    charGuessed,
            std::vector<T>          incorrectGuessedChars,
            std::vector<T>          revealedChars,
            std::vector<T>          wrongGuessesChars
            
    )
    : numGuesses           {numGuesses}
    , correctWord          {correctWord}
    , correctWordSize      {correctWordSize}
    , wrongGuessesLeft     {wrongGuessesLeft}
    , numCorrectGuesses    {numCorrectGuesses}
    , charGuessed          {charGuessed}
    , incorrectGuessedChars{incorrectGuessedChars}
    , revealedChars        (revealedChars}   
    , wrongGuessesChars    (wrongGuessesChars}
};

Session<T> s{numGuesses, correctWord, correctWord.size(), numGuesses, 0, '', std::vector<T>{}, std::vector<T>{}, std::vector<T>{}};