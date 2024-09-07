#include <iostream>

struct AdStats {
    int numAdsWatched{};
    double percentUsersClicked{};
    double avgEarningsPerClick{};
};

struct Fraction {
    int numerator{0};
    int denominator{1};
};

Fraction getFraction() {
    Fraction frac {};
    std::cout << "Enter numerator: ";
    std::cin >> frac.numerator;
    std::cout << "Enter denominator: ";
    std::cin >> frac.denominator;

    return frac;
}

constexpr Fraction returnProduct(const Fraction& frac1, const Fraction& frac2) {
    return {frac1.numerator * frac2.numerator, frac1.denominator * frac2.denominator};
}

void printFraction (const Fraction& frac) {
    std::cout << frac.numerator << "/" << frac.denominator << '\n';
}

void printAdStats(const AdStats& adstats) {
    std::cout << "Number of ads watched: " << adstats.numAdsWatched << '\n';
    std::cout << "Percentage of users who clicked on ad: " << adstats.percentUsersClicked << '\n';
    std::cout << "Average earnings per ad click: " << adstats.avgEarningsPerClick << '\n';
    std::cout << "Total earnings: " << adstats.numAdsWatched * adstats. percentUsersClicked * adstats.avgEarningsPerClick / 100 << '\n';
}

int main () {
    printAdStats({100, 96., 13.54});
    Fraction frac1{getFraction()};
    Fraction frac2{getFraction()};
    printFraction(returnProduct(frac1, frac2));
}