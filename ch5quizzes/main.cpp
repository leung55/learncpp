#include <iostream>
#include <string>
// Write the function getQuantityPhrase() here
constexpr std::string_view getQuantityPhrase(int maryApples) {
    if(maryApples < 0)
        return "negative";
    else if (maryApples == 0)
        return "0";
    else if (maryApples == 1)
        return "a single";
    else if (maryApples == 2)
        return "a couple of";
    else if (maryApples == 3)
        return "a few";
    else if (maryApples > 3)
        return "many";
    return "";
}
// Write the function getApplesPluralized() here
constexpr std::string_view getApplesPluralized(int maryApples) {
    return (maryApples == 1) ? "apple" : "apples";
}

int main()
{
    constexpr int maryApples { 3 };
    std::cout << "Mary has " << getQuantityPhrase(maryApples) << ' ' << getApplesPluralized(maryApples) << ".\n";

    std::cout << "How many apples do you have? ";
    int numApples{};
    std::cin >> numApples;

    std::cout << "You have " << getQuantityPhrase(numApples) << ' ' << getApplesPluralized(numApples) << ".\n";

    return 0;
}