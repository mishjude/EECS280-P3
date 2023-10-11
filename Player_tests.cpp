#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;


// Mock Card class without specifying card names
class Card {
public:
    Card() {}
};

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    delete alice;
}

TEST(test_player_add_card) {
    Player * bob = Player_factory("Bob", "Simple");
    Card card;
    bob->add_card(card);
    ASSERT_EQUAL(1, bob->get_hand().size());
    delete bob;
}

TEST(test_player_make_trump) {
    Player * charlie = Player_factory("Charlie", "Simple");
    Suit orderSuit = Suit::Spades;
    Card upCard;
    bool isDealer = true;
    int round = 1;
    bool orderUp = charlie->make_trump(upCard, isDealer, round, orderSuit);
    // Define the expected result based on your logic
    bool expectedOrderUp = true; // or false
    ASSERT_EQUAL(expectedOrderUp, orderUp);
    delete charlie;
}

TEST(test_player_add_and_discard) {
    Player * david = Player_factory("David", "Simple");
    Card upCard;
    david->add_card(Card());
    david->add_card(Card());
    david->add_and_discard(upCard);
    ASSERT_EQUAL(MAX_HAND_SIZE, david->get_hand().size());
    delete david;
}

TEST(test_player_lead_card) {
    Player * eve = Player_factory("Eve", "Simple");
    eve->add_card(Card());
    eve->add_card(Card());
    eve->add_card(Card());
    Suit trump = Suit::Diamonds; // Example trump suit
    Card leadCard = eve->lead_card(trump);
    // Define the expected behavior based on your logic
    ASSERT_TRUE(/* Add your condition here */);
    delete eve;
}

TEST(test_player_play_card) {
    Player * frank = Player_factory("Frank", "Simple");
    frank->add_card(Card());
    frank->add_card(Card());
    Suit trump = Suit::Hearts; // Example trump suit
    Card ledCard;
    Card playedCard = frank->play_card(ledCard, trump);
    // Define the expected behavior based on your logic
    ASSERT_TRUE(/* Add your condition here */);
    delete frank;
}


TEST_MAIN()
