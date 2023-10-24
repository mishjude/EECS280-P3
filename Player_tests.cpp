#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;


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
    bob->add_card(card1);
    bob->add_card(card1);
    bob->add_card(card1);
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
    Card upCard3 = Card(NINE, DIAMONDS);
    Card upCard4 = Card(TEN, SPADES);

    charlie->add_card(card1);
    charlie->add_card(card2);
    charlie->add_card(card3);
    charlie->add_card(card4);
    charlie->add_card(card5);

    //upcard is king of spades, so the ordered up suit would be spades

    Suit order_up_suit = DIAMONDS; //order up suit should change to spades
    Suit order_up_suit_2 = SPADES; //order up suit should stay spades
    Suit order_up_suit_3 = HEARTS; //should change to diamonds
    Suit order_up_suit_4 = HEARTS; //should change to spades

    //round 1

    //charlie has 2 spades, so they would make the king of spades trump
    charlie->make_trump(upCard, true, 1, order_up_suit);
    //so then the upcard would be trump?
    ASSERT_TRUE(upCard.is_trump(order_up_suit));

    
    //charlie would pass here bc they dont have other heart cards
    charlie->make_trump(upCard2, true, 1, order_up_suit_2);
    ASSERT_FALSE(upCard2.is_trump(order_up_suit_2));

    
    //round 2

    //upcard 4 is 10 of spades
    //charlie would order up the card of the same colour as the upcard 
    charlie->make_trump(upCard4, true, 2, order_up_suit_3);
    
    //so then the upcard would be trump? -> plays queen of clubs here?
    ASSERT_TRUE(order_up_suit_3 == CLUBS);

    //charlie has no hearts so they would pass and the order_up_suit doesnt change (stays hearts in this case?)
    //confirm above for understanding -> only plays if they have the same colour next suit?
    charlie->make_trump(upCard3, true, 2, order_up_suit_4);
    ASSERT_TRUE(order_up_suit_4 == HEARTS); 
    
    delete charlie;
}


TEST(test_player_add_and_discard) {
    
   Player * david = Player_factory("David", "Simple");
   Card card1 = Card(NINE, HEARTS);
   Card card2 = Card(QUEEN, CLUBS);
   Card card3 = Card(JACK, SPADES); 
   Card card4 = Card(NINE, SPADES);
   Card card5 = Card(TEN, HEARTS);
   Card upcard = Card(QUEEN, DIAMONDS);

   //base case - no trumps (trump = diamonds)
   david->add_card(card1);
   david->add_card(card2);
   david->add_card(card3);
   david->add_card(card4);
   david->add_card(card5);
   david->add_and_discard(upcard); //adds trump
   ASSERT_EQUAL(david->lead_card(DIAMONDS), card2); //highest non-trump
   ASSERT_EQUAL(david->lead_card(DIAMONDS), card3);
   ASSERT_EQUAL(david->lead_card(DIAMONDS), card5);
   ASSERT_EQUAL(david->lead_card(DIAMONDS), card1);
   ASSERT_EQUAL(david->lead_card(DIAMONDS), upcard);

   delete david;
   
   Player * daniel = Player_factory("Daniel", "Simple");
   Card nine_clubs = Card(NINE, CLUBS);
   Card queen_diamonds = Card(QUEEN, DIAMONDS);
   Card jack_spades = Card (JACK, SPADES);
   Card ten_clubs = Card(TEN, CLUBS);
   Card ten_hearts = Card(TEN, HEARTS);
   Card bower_upcard = Card(JACK, DIAMONDS);

   //adding a bower - trump = hearts , jack of diamonds is bower
   daniel->add_card(nine_clubs); //discarded
   daniel->add_card(queen_diamonds);
   daniel->add_card(jack_spades);
   daniel->add_card(ten_clubs); 
   daniel->add_card(ten_hearts);
   daniel->add_and_discard(bower_upcard);
   ASSERT_EQUAL(daniel->lead_card(HEARTS), queen_diamonds);
   ASSERT_EQUAL(daniel->lead_card(HEARTS), jack_spades);
   ASSERT_EQUAL(daniel->lead_card(HEARTS), ten_clubs);
   ASSERT_EQUAL(daniel->lead_card(HEARTS), bower_upcard);
   ASSERT_EQUAL(daniel->lead_card(HEARTS), ten_hearts);

   delete daniel;

   //all trumps?
   

   
   
}

TEST(test_player_lead_card) {
    Player * eve = Player_factory("Eve", "Simple");
    Card card1 = Card(NINE, HEARTS);
    Card card2 = Card(TEN, HEARTS);
    Card card3 = Card(JACK, HEARTS);
    Card card4 = Card(QUEEN, HEARTS);
    Card card5 = Card(KING, HEARTS);
    Card card6 = Card(JACK, DIAMONDS);

    //make trump hearts 

    //if all cards in hand are in trump
    eve->add_card(card1);
    eve->add_card(card2);
    eve->add_card(card3);
    eve->add_card(card4);
    eve->add_card(card5);
    
    Card test = eve->lead_card(HEARTS);
    //should lead with jack of hearts bc thats the highest?
    ASSERT_EQUAL(test, card3);
    //jack of hearts should be deleted now, so next card should be led
    test = eve->lead_card(HEARTS);
    ASSERT_EQUAL(test, card5);

    delete eve;

    Player * aika = Player_factory("Aika", "Simple");

    //all cards are trump (with bower)
    aika->add_card(card1);
    aika->add_card(card2);
    aika->add_card(card6); //bower jack
    aika->add_card(card4);
    aika->add_card(card3); //trump jack

    Card test2 = aika->lead_card(HEARTS);
    //should play trump jack first
    ASSERT_EQUAL(test2, card3);

    //then delete trump jack and play bower jack next 
    test2 = aika->lead_card(HEARTS);
    ASSERT_EQUAL(test2, card6);

    delete aika;

    Player * alexandre = Player_factory("Alexandre", "Simple");


    //all cards are non trump (trump = diamonds)
    Card queen_spades = Card(QUEEN, SPADES);
    Card nine_spades = Card(NINE, SPADES);
    Card jack_spades = Card(JACK, SPADES);
    Card ten_spades = Card(TEN, SPADES);
    Card king_spades = Card(KING, SPADES);

    alexandre->add_card(queen_spades);
    alexandre->add_card(nine_spades);
    alexandre->add_card(jack_spades);
    alexandre->add_card(ten_spades);
    alexandre->add_card(king_spades);

    //leads with highest non trump (king of spades)
    Card test3 = alexandre->lead_card(DIAMONDS);
    ASSERT_EQUAL(test3, king_spades);

    //then delete king of spades and play next highest (queen spades)
    test3 = alexandre->lead_card(DIAMONDS);
    ASSERT_EQUAL(test3, queen_spades);

    delete alexandre; //bc i dont know how to empty out someones hand KJSHDFKJH

    Player * azure = Player_factory("Azure", "Simple");
    Card queen_hearts = Card(QUEEN, HEARTS);
    //use nine spades from before
    Card queen_clubs = Card(QUEEN, CLUBS);
    //use jack spades from before
    Card nine_diamonds = Card(NINE, DIAMONDS);

    //some trump some non trump (trump = spades)
    azure->add_card(queen_hearts);
    azure->add_card(nine_spades);
    azure->add_card(queen_clubs);
    azure->add_card(jack_spades);
    azure->add_card(nine_diamonds);

    //should play highest non trump (should play queen of clubs)
    Card test4 = azure->lead_card(SPADES);
    ASSERT_EQUAL(test4, queen_clubs);

    delete azure;
}



TEST(test_player_play_card) {
    Player * frank = Player_factory("Frank", "Simple");
    
    Card jack_spades = Card(JACK, SPADES);
    Card nine_spades = Card(NINE, SPADES);
    Card queen_hearts = Card(QUEEN, HEARTS);
    Card queen_clubs = Card(QUEEN, CLUBS);
    Card nine_diamonds = Card(NINE, DIAMONDS);
    Card led_card = Card(TEN, SPADES);
    frank->add_card(queen_hearts);
    frank->add_card(nine_spades);
    frank->add_card(queen_clubs);
    frank->add_card(jack_spades);
    frank->add_card(nine_diamonds);
    ASSERT_EQUAL(frank->play_card(led_card, HEARTS), jack_spades);
    delete frank;
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


TEST_MAIN()
