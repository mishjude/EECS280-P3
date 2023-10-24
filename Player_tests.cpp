#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    delete alice;
}

// TEST(test_simple_add_card_to_player) {
//     Player* simple = Player_factory("Simple");
//     Card ace_of_hearts(ACE, HEARTS);
//     simple->add_card(ace_of_hearts);
//     // Here you could potentially check the player's hand to make sure the card was added
//     delete simple;
// }

// TEST(test_player_decision_to_make_trump) {
//     Player* simple = Player_factory("Simple");
//     Card ace_of_hearts(ACE, HEARTS);
//     simple->add_card(ace_of_hearts);

//     Suit order_up_suit;
//     Card upcard(TEN, CLUBS);
//     bool result = simple->make_trump(upcard, false, 1, order_up_suit);
//     ASSERT_EQUAL(false, result);
//     delete simple;
// }

TEST(test_factory_creates_simple_player) {
    Player* simple = Player_factory("TestSimple", "Simple");
    ASSERT_EQUAL("TestSimple", simple->get_name());
    delete simple;
}

TEST(test_factory_creates_human_player) {
    Player* human = Player_factory("TestHuman", "Human");
    ASSERT_EQUAL("TestHuman", human->get_name());
    delete human;
}

TEST(test_player_card_play_decision) {
    Player * alice = Player_factory("Alice", "Simple");

    Card ace_clubs = Card(ACE,CLUBS);
    Suit trump = CLUBS;
    alice->add_card(ace_clubs);
    
    ASSERT_EQUAL(ace_clubs, alice->play_card(ace_clubs, trump));

    delete alice; 
}

TEST(test_card_addition_and_discard_decision) {
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(QUEEN, DIAMONDS));
    bob->add_card(Card(KING, CLUBS));
    bob->add_card(Card(ACE, SPADES));

    bob->add_and_discard(Card(NINE, HEARTS));  // upcard

    Card card_led = bob->lead_card(HEARTS);
    Card ace_spades(ACE, SPADES);
    ASSERT_EQUAL(card_led, ace_spades); 

    delete bob;
}

// Add more tests here

TEST_MAIN()

