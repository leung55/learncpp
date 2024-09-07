#include "blackjack.h"
#include <vector>
#include <cassert>

namespace Blackjack {
    constexpr int scoreLimit{21};
    constexpr int dealerStandLimit{17};
    using H = Hand;
    void H::resetHand() {
        cards.clear();
        value = 0;
        ace11 = false;
        bust = false;
    }
    void H::addCard(const Card& new_cd) {
        cards.push_back(new_cd);
        value += new_cd.getCardValue();

        // if new card is an ace (which already added 1), 
        // there isn't an ace contributing 11 to the count, and the current value is 11 or less,
        // add the extra 10 to make the ace worth 11
        if(new_cd.rank == ace && !ace11 && value <= 11) {
            value += 10;
            ace11 = true;         
        }

        //if there is an ace counting as an 11 and the value is over the score limit, 
        // make the ace count as a 1
        else if(ace11 && value > scoreLimit) {
            value -= 10;
            ace11 = false;
        }
        bust = (value > scoreLimit);
    }
    using P = Player;
    void P::setChips(int userChips) {chips = userChips;}
    void P::makeABet() {
        assert(chips > 0);
        std::cout << "You have " << chips << " chips. How much would you like to bet?: ";
        while(true) {
            std::cin >> bet;
            if(InputHandling::clearFailedExtraction() || bet < 0) {
                std::cout << "Invalid input. Try again: ";
            }
            else if(bet > chips) {
                std::cout << "You can't bet more chips than you have! Enter a valid bet: ";
                InputHandling::ignoreLine();
            }
            else {
                InputHandling::ignoreLine();
                return;
            }
        }
    }
    bool P::playAgain() {
        std::cout << "Deal again? [y/n]: ";
        char again{};
        while(true) {
            std::cin >> again;
            if(InputHandling::clearFailedExtraction() || (again != 'y' && again != 'n')) {
                std::cout << "Invalid input. Try again: ";
            }
            else {
                InputHandling::ignoreLine();
                return again == 'y';
            }
            InputHandling::ignoreLine();
        }
    }
    void P::reset() {
        bet = 0;
        stand = false;
        pHand.resetHand();
    }
    void Dealer::reset() {
        stand = false;
        dHand.resetHand();
    }
    using BJ = BlackjackGame;
    BJ::BlackjackGame(int playerChips=0) {
        deck.shuffle();
        player.setChips(playerChips);
    }

    void BJ::dealCards() {
        player.pHand.addCard(deck.dealCard());
        dealer.dHand.addCard(deck.dealCard());
        player.pHand.addCard(deck.dealCard());
        dealer.dHand.addCard(deck.dealCard());
        std::cout << "Cards have been dealt.\n";
        displayCards();
        if(player.pHand.value == scoreLimit) {
            std::cout << "Blackjack!\n";
            player.stand = true;
        }
    }
    void BJ::resetPlay() {
        player.reset();
        dealer.reset();
        deck.shuffle();
    }
    void BJ::playerHit() {
        player.pHand.addCard(deck.dealCard());
    }
    void BJ::dealerHit() {
        dealer.dHand.addCard(deck.dealCard());
    }
    void BJ::hitOrStand() {
        std::cout << "Hit or Stand? [h/s]: ";
        char hit_stand{};
        while(true) {
            std::cin >> hit_stand;
            if(InputHandling::clearFailedExtraction() || (hit_stand != 'h' && hit_stand != 's')) {
                std::cout << "Invalid input. Try again: ";
                InputHandling::ignoreLine();
                continue;
            }
            InputHandling::ignoreLine();
            break;
        }
        if(hit_stand == 'h') {
            playerHit();
        }
        else {
            player.stand = true;
            std::cout << "Player stands\n";
            return;
        }
        if(player.pHand.bust) {
            std::cout << "Player bust!\n";
            return;
        }
        if(player.pHand.value == scoreLimit) {
            player.stand = true;
            return;
        }
    }
    void BJ::dealerDrawCards() {
        bool dealerPickup{dealer.dHand.value < dealerStandLimit};
        while(dealer.dHand.value < dealerStandLimit) {
            dealerHit();
        }
        if(dealerPickup)
            displayCards();
        if(dealer.dHand.bust) {
            std::cout << "Dealer bust!\n";
            return;
        }
        dealer.stand = true;
    }
    void BJ::displayCards() {
        bool playerTurn{!(player.pHand.bust || player.stand)};
        std::cout << "Dealer's hand-value / cards: ";
        //if player can still draw cards, don't show the first one
        if(playerTurn) {
            assert(std::size(dealer.dHand.cards) == 2);
            std::cout << "??" << " / ";
            std::cout << "??" << ' ';
        }
        else {
            assert(std::size(dealer.dHand.cards) >= 1);
            std::cout << dealer.dHand.value << " / ";
            std::cout << dealer.dHand.cards[0] << ' ';
        }
        for(std::size_t i{1}; i < std::size(dealer.dHand.cards); ++i)
            std::cout << dealer.dHand.cards[i] << ' ';

        std::cout << "\nPlayer's hand-value cards: " << player.pHand.value << " / ";
        for(const Card& cd : player.pHand.cards)
            std::cout << cd << ' ';
        std::cout << '\n';
    }
    void BJ::playBJ() {
        std::cout << "Let's play some Blackjack\n";
        if(player.chips > 0)
        do {
            player.makeABet();        
            dealCards();
            //player's turn
            while(!player.stand && !player.pHand.bust) {
                hitOrStand();
                displayCards();
            }
            //player bust and lost
            if(player.pHand.bust) {
                player.chips -= player.bet;
                std::cout << "You lost " << player.bet << " chips.\n";
                resetPlay();
                continue;
            }
            assert(player.stand);
            //dealer's turn
            dealerDrawCards();
            //player won
            if(dealer.dHand.bust || dealer.stand && player.pHand.value > dealer.dHand.value) {
                player.chips += player.bet;
                std::cout << "You won " << player.bet << " chips.\n";
                resetPlay();
                continue;
            }
            assert(dealer.stand && player.pHand.value <= dealer.dHand.value);
            //player lost
            if(player.pHand.value < dealer.dHand.value) {
                player.chips -= player.bet;
                std::cout << "You lost " << player.bet << " chips.\n";
            }
            //player and dealer tied
            if(player.pHand.value == dealer.dHand.value)
                std::cout << "You tied.\n";
            resetPlay();
        } while(player.chips > 0 && player.playAgain());
        assert(player.chips >= 0);
        if(player.chips == 0) {
            std::cout << "You're out of money!\n";
        }
        else {
            std::cout << "You came out with " << player.chips << " chips.\n";
        }
    }
}