#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "cards.h"
#include "input_handling.h"
#include <iostream>
#include <vector>

using namespace Cards;
namespace Blackjack {
    struct Hand {
        std::vector<Card> cards{};
        int value{0};
        bool ace11{false};
        bool bust{false};
        void addCard(const Card&); //update hand and value
        void resetHand();
    };
    struct Player {
        Hand pHand{};
        int chips{};
        int bet{};
        bool stand{false};
        void setChips(int);
        void makeABet();
        bool playAgain();
        void reset();
    };
    struct Dealer {
        Hand dHand{};
        bool stand{false};
        void reset();
    };
    class BlackjackGame {        
        Player player{};
        Dealer dealer{};
        Deck deck{};
    public:
        BlackjackGame(int playerChips);
        void dealCards();
        void resetPlay();
        void playerHit();
        void dealerHit();
        void hitOrStand();
        void dealerDrawCards();
        void displayCards();
        void playBJ();
    };
}

#endif