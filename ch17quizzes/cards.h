#ifndef CARDS_H
#define CARDS_H

#include "random.h"
#include <array>
#include <algorithm>
#include <cassert>

namespace Cards {
    enum Rank {
        ace,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        ten,
        jack,
        queen,
        king,
        maxRank,
    };
    enum Suit {
        heart,
        spade,
        club,
        diamond,
        maxSuit,
    };
    struct Card {
        Rank rank;
        Suit suit;
        int getCardValue() const {
            return (rank < ten) ? rank + 1 : 10;
        }
    };
    constexpr std::array suits{'H','S','C','D'};
    constexpr std::array ranks{'A','J','Q','K'};
    constexpr int deckSize{52};
    class Deck {
        std::array<Card,deckSize> deck;
        std::size_t deckIdx;
    public:
        Deck() : deckIdx{0} {
            std::size_t deckIdx{0};
            for(int suit{heart}; suit < maxSuit; ++suit) {
                for(int rank{ace}; rank < maxRank; ++rank) {
                    deck[deckIdx++] = {static_cast<Cards::Rank>(rank), static_cast<Cards::Suit>(suit)};
                }
            }
        }

        auto& getDeck() const {return deck;}
        auto& dealCard() {
            assert(deckIdx < deckSize && "ran out of cards");
            return deck[deckIdx++];
        }
        void shuffle() {
            deckIdx = 0;
            std::shuffle(deck.begin(), deck.end(), Random::mt);
        }
    };
    std::ostream& operator<<(std::ostream& out, const Cards::Card card);
}
#endif