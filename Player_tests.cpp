#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    delete alice;
}

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
TEST(test_mutation_fixed_name_return) {
    Player * mutant = Player_factory("NotAMutant", "Simple");
    ASSERT_NOT_EQUAL("Mutant", mutant->get_name());
    delete mutant;
}


TEST(test_card_addition_and_discard_decision) {
    cout << "Running test_card_addition_and_discard_decision..." << endl;
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(QUEEN, DIAMONDS));
    bob->add_card(Card(KING, CLUBS));
    bob->add_card(Card(ACE, SPADES));

    bob->add_and_discard(Card(NINE, HEARTS));  // upcard

    Card card_led = bob->lead_card(HEARTS);
    Card ace_spades(ACE, SPADES);
    ASSERT_NOT_EQUAL(card_led, ace_spades); 

    delete bob;
}
TEST(test_simple_player_make_trump_round_1) {
    Player * simple = Player_factory("Alice", "Simple");
    Card upcard(ACE, HEARTS);
    Suit order_up_suit;

    // Test with round 1 and more than 2 trump cards in hand
    simple->add_card(Card(JACK, HEARTS));
    simple->add_card(Card(KING, HEARTS));
    simple->add_card(Card(ACE, SPADES));
    ASSERT_TRUE(simple->make_trump(upcard, false, 1, order_up_suit));
    ASSERT_EQUAL(order_up_suit, HEARTS);

    // Test with round 1 and less than 2 trump cards in hand
    simple->add_card(Card(NINE, SPADES));
    ASSERT_TRUE(simple->make_trump(upcard, false, 1, order_up_suit));
}
TEST(test_card_played_from_hand) {
    cout << "Running test_card_played_from_hand..." << endl;
    Player* charlie = Player_factory("Charlie", "Simple");
    Card ace_hearts = Card(ACE, HEARTS);
    charlie->add_card(ace_hearts);
    Suit trump = HEARTS;

    ASSERT_EQUAL(ace_hearts, charlie->play_card(ace_hearts, trump));

    delete charlie;
}
TEST(test_card_not_in_hand) {
    cout << "Running test_card_not_in_hand..." << endl;
    Player* dave = Player_factory("Dave", "Simple");
    Card ten_spades = Card(TEN, SPADES);
    Suit trump = SPADES;

    // Assuming the card isn't in Dave's hand, he should play a different card
    ASSERT_NOT_EQUAL(ten_spades, dave->play_card(ten_spades, trump));

    delete dave;
}

TEST(test_simple_player_pass_trump_round_1) {
    Player * simple = Player_factory("Bob", "Simple");
    Card upcard(ACE, CLUBS);
    Suit order_up_suit;

    // Test with round 1 and no trump cards in hand
    simple->add_card(Card(NINE, SPADES));
    simple->add_card(Card(TEN, HEARTS));
    simple->add_card(Card(QUEEN, DIAMONDS));
    ASSERT_FALSE(simple->make_trump(upcard, false, 1, order_up_suit));

    delete simple;
}

TEST(test_simple_player_pass_trump_round_2_mutation) {
    cout << "Running test_simple_player_pass_trump_round_2_mutation..." << endl;
    Player * jane = Player_factory("Jane", "Simple");
    Card upcard(NINE, CLUBS);
    Suit order_up_suit;

    // Test with round 2 and no good cards, player should ideally pass
    jane->add_card(Card(NINE, SPADES));
    jane->add_card(Card(TEN, DIAMONDS));
    ASSERT_FALSE(jane->make_trump(upcard, false, 2, order_up_suit));

    delete jane;
}

TEST_MAIN()
