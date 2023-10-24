#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;

// Test default constructor for Card
TEST(test_card_default_ctor) {
    Card c;
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
}

// Test parameterized constructor for Card
TEST(test_card_param_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

// Test the is_face_or_ace() function
TEST(test_card_face_or_ace) {
    Card c1(TWO, SPADES);
    Card c2(JACK, SPADES);
    Card c3(ACE, SPADES);
    ASSERT_FALSE(c1.is_face_or_ace());
    ASSERT_TRUE(c2.is_face_or_ace());
    ASSERT_TRUE(c3.is_face_or_ace());
}

// Test the right bower function
TEST(test_right_bower) {
    Card c(JACK, SPADES);
    ASSERT_TRUE(c.is_right_bower(SPADES));
    ASSERT_FALSE(c.is_right_bower(CLUBS));
}

// Test the left bower function
TEST(test_left_bower) {
    Card c1(JACK, CLUBS);
    Card c2(JACK, SPADES);
    ASSERT_TRUE(c1.is_left_bower(SPADES));
    ASSERT_FALSE(c2.is_left_bower(SPADES));
}

// Test the is_trump() function
TEST(test_is_trump) {
    Card c1(JACK, CLUBS);
    Card c2(ACE, CLUBS);
    Card c3(TWO, HEARTS);
    ASSERT_TRUE(c1.is_trump(SPADES));
    ASSERT_TRUE(c2.is_trump(CLUBS));
    ASSERT_FALSE(c3.is_trump(CLUBS));
}

// Add more tests if necessary
// Test the equality (==) operator for Card
TEST(test_card_equality) {
    Card c1(ACE, HEARTS);
    Card c2(ACE, HEARTS);
    Card c3(TWO, SPADES);
    ASSERT_TRUE(c1 == c2);
    ASSERT_FALSE(c1 == c3);
}

// Test the inequality (!=) operator for Card
TEST(test_card_inequality) {
    Card c1(ACE, HEARTS);
    Card c2(TWO, SPADES);
    ASSERT_TRUE(c1 != c2);
    ASSERT_FALSE(c1 != c1);
}

// Test the comparison (<, <=, >, >=) operators for Card
TEST(test_card_comparison) {
    Card c1(ACE, HEARTS);
    Card c2(TWO, SPADES);
    Card c3(ACE, DIAMONDS);
    
    ASSERT_TRUE(c2 < c1);
    ASSERT_TRUE(c2 <= c1);
    ASSERT_FALSE(c1 < c2);
    ASSERT_FALSE(c1 <= c2);
    
    ASSERT_TRUE(c1 > c2);
    ASSERT_TRUE(c1 >= c2);
    ASSERT_FALSE(c2 > c1);
    ASSERT_FALSE(c2 >= c1);
    
    ASSERT_TRUE(c1 <= c3);
    ASSERT_FALSE(c1 >= c3);
    ASSERT_FALSE(c1 < c3);
    ASSERT_FALSE(c1 > c3);
}
// Test the Card_less() function
TEST(test_card_less_trump) {
    Card c1(JACK, SPADES); // Right bower when SPADES is trump
    Card c2(JACK, CLUBS);  // Left bower when SPADES is trump
    Card c3(TEN, SPADES);
    ASSERT_FALSE(Card_less(c1, c2, SPADES));
    ASSERT_TRUE(Card_less(c2, c1, SPADES));
    ASSERT_TRUE(Card_less(c3, c1, SPADES));
    ASSERT_TRUE(Card_less(c3, c2, SPADES));
}
TEST(test_card_default_ctor_mutation) {
    Card c;
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
}

TEST(test_bower_detection_mutation) {
    Card right_bower(JACK, SPADES);
    Card wrong_bower(JACK, HEARTS);
    ASSERT_TRUE(right_bower.is_right_bower(SPADES));
    ASSERT_FALSE(wrong_bower.is_right_bower(SPADES));

    Card left_bower(JACK, CLUBS);
    ASSERT_TRUE(left_bower.is_left_bower(SPADES));
    ASSERT_FALSE(wrong_bower.is_left_bower(SPADES));
}
TEST(test_trump_detection_mutation) {
    Card trump_card(TEN, SPADES);
    Card non_trump_card(TEN, HEARTS);
    ASSERT_TRUE(trump_card.is_trump(SPADES));
    ASSERT_FALSE(non_trump_card.is_trump(SPADES));
}
TEST(test_face_or_ace_detection_mutation) {
    Card face_card(JACK, SPADES);
    Card non_face_card(TWO, SPADES);
    ASSERT_TRUE(face_card.is_face_or_ace());
    ASSERT_FALSE(non_face_card.is_face_or_ace());
}
TEST(test_card_comparison_mutation) {
    Card c1(TWO, HEARTS);
    Card c2(THREE, HEARTS);
    ASSERT_TRUE(c1 < c2);
    ASSERT_FALSE(c1 > c2);
    ASSERT_TRUE(c1 <= c2);
    ASSERT_FALSE(c1 >= c2);
}
TEST(test_suit_next_mutation) {
    ASSERT_EQUAL(CLUBS, Suit_next(SPADES));
    ASSERT_EQUAL(DIAMONDS, Suit_next(HEARTS));
}
TEST(test_card_stream_overload_mutation) {
    Card c1(ACE, SPADES);
    stringstream ss;
    ss << c1;
    ASSERT_EQUAL("Ace of Spades", ss.str());
    Card c2;
    ss >> c2;
    ASSERT_EQUAL(c1, c2);
}
//Tests highest rank 
TEST(test_highest_rank){
    Card c1(ACE,HEARTS);
    Card c2(QUEEN,DIAMONDS);


    ASSERT_TRUE(c1>c2);

}



TEST_MAIN()
