#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;


// Mock Card class without specifying card names
/*
class Card {
public:
    Card() {}
};
*/

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    delete alice;
}

TEST(test_player_add_card) {
    Player * bob = Player_factory("Bob", "Simple");
    Card card1 = Card(SEVEN, CLUBS);
    
    //base case
    bob->add_card(card1);
    Card test = bob->lead_card(CLUBS);
    ASSERT_EQUAL(test, card1);
    delete bob;

    //other edge cases(?)
}


TEST(test_player_make_trump) {

    Player * charlie = Player_factory("Charlie", "Simple");
    Card card1 = Card(NINE, CLUBS);
    Card card2 = Card(QUEEN, CLUBS);
    Card card3 = Card(JACK, SPADES);
    Card card4 = Card(ACE, DIAMONDS);
    Card card5 = Card(QUEEN, SPADES);
    Card upCard = Card(KING, SPADES);
    Card upCard2 = Card(ACE, HEARTS);
    //Card upCard3 = Card(NINE, DIAMONDS);
   // Card upCard4 = Card(TEN, SPADES);

    charlie->add_card(card1);
    charlie->add_card(card2);
    charlie->add_card(card3);
    charlie->add_card(card4);
    charlie->add_card(card5);

    //upcard is king of spades, so the ordered up suit would be spades

    Suit order_up_suit = DIAMONDS; //order up suit should change to spades
    Suit order_up_suit_2 = SPADES; //order up suit should stay spades
    //Suit order_up_suit_3 = HEARTS; //should change to diamonds
   // Suit order_up_suit_4 = HEARTS; //should change to spades

    //round 1

    //charlie has 2 spades, so they would make the king of spades trump
    charlie->make_trump(upCard, true, 1, order_up_suit);
    //so then the upcard would be trump?
    ASSERT_TRUE(upCard.is_trump(order_up_suit));

    
    //charlie would pass here bc they dont have other heart cards
    charlie->make_trump(upCard2, true, 1, order_up_suit_2);
    ASSERT_FALSE(upCard2.is_trump(order_up_suit_2));

    
    //round 2

    //charlie has 2 spades, so they would make the king of spades trump
    //charlie->make_trump(upCard4, true, 2, order_up_suit_3);
    
    //so then the upcard would be trump?
    //ASSERT_TRUE(upCard.is_trump(order_up_suit_3));

    //charlie has one diamond so they would pick it up
    //charlie->make_trump(upCard3, true, 2, order_up_suit_4);
    //ASSERT_TRUE(upCard3.is_trump(order_up_suit_4));
    
    delete charlie;
}


TEST(test_player_add_and_discard) {
    
   Player * david = Player_factory("David", "Simple");
   Card card1 = Card(SEVEN, CLUBS);
   Card card2 = Card(QUEEN, CLUBS);
   Card card3 = Card(JACK, SPADES); //bower

   //base case
   david->add_card(card1);
   david->add_card(card1);
   david->add_card(card1);
   david->add_card(card1);
   david->add_card(card1);
   david->add_and_discard(card2);
   Card test = david->lead_card(SPADES);
   ASSERT_EQUAL(test, card2);

   //adding a bower
   david->add_card(card2);
   david->add_card(card2);
   david->add_card(card2);
   david->add_card(card2);
   david->add_card(card2);
   david->add_and_discard(card3);
   Card test2 =  david->lead_card(CLUBS);
   ASSERT_EQUAL(test2, card3);
   
   delete david;
}
/*
TEST(test_player_lead_card) {
    Player * eve = Player_factory("Eve", "Simple");
    eve->add_card(Card());
    eve->add_card(Card());
    eve->add_card(Card());
    Suit trump = DIAMONDS // Example trump suit
    Card leadCard = eve->lead_card(trump);
    // Define the expected behavior based on your logic
    ASSERT_TRUE();
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
    ASSERT_TRUE();
    delete frank;
}
*/


TEST_MAIN()
