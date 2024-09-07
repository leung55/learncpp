#include "cards.h"
#include "blackjack.h"
#include "random.h"
#include <iostream>

using namespace Cards;

std::ostream& Cards::operator<<(std::ostream& out, const Cards::Card card) {
    if(card.rank > Cards::ace && card.rank < Cards::jack)
        return out << card.rank + 1 << Cards::suits[card.suit];
    return out << ((card.rank == Cards::ace) ? Cards::ranks[card.rank] : Cards::ranks[card.rank - 9]) << Cards::suits[card.suit];
}


int main() {
    Cards::Card card{Cards::ace, Cards::heart};
    Cards::Card card2{Cards::five, Cards::spade};
    std::cout << card;
    std::cout << card2;
    std::cout << card.getCardValue() << '\n';
    std::cout << card2.getCardValue() << '\n';

    Cards::Deck deck{};
    for(auto& card : deck.getDeck()) {
        std::cout << card;
    }
    std::cout << "Dealing cards\n";
    for(int i{0}; i < Cards::deckSize; i++) {
        std::cout << deck.dealCard();
    }
    std::cout << "shuffling cards\n";
    deck.shuffle();
    for(int i{0}; i < Cards::deckSize; i++) {
        std::cout << deck.dealCard();
    }
    std::cout << '\n';
    Blackjack::BlackjackGame bj{100};
    bj.playBJ();
    return 0;
}