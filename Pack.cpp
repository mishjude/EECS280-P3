#include "Pack.hpp"
#include "Card.hpp"
#include <array>
#include <string>
#include <cassert>
#include <iostream>
#include <vector>


#define PACK_HPP

using namespace std;



// EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on.
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  Pack::Pack(){
    int index = 0;
    for (int i = 7; i <= 12; i++) {
      for (int j = 0; j <= 3; j++) {
        cards[index] = Card(static_cast<Rank>(i), static_cast<Suit>(j));
        index++;
      }
    }
    reset();
  }

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  Pack::Pack(std::istream& pack_input){
    Card card;
    int i = 0;
    while (pack_input >> card) {
      cards[i] = card;
      i++;
    }
    //how to use input with while loop to address undefined behaviour?
    /* int i = 0;
    while (i < PACK_SIZE && pack_input >> cards[i]) {
        i++;
    }
    
    
    for (int i = 0; i < PACK_SIZE; i++) {
      pack_input >> cards[i];
    }
    */
    
  }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one(){
    next++;
    return cards[next - 1];
  }

  // EFFECTS: Resets next index to first card in the Pack
  void Pack::reset(){
    next = 0;
  }

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
  void Pack::shuffle(){
    const int half_size = PACK_SIZE / 2;
    Card first_half[half_size];
    Card second_half[half_size];
    Card shuffled[PACK_SIZE];

    for (int m = 0; m < PACK_SIZE; m++) {
        shuffled[m] = cards[m];
    }

    for (int k = 0; k < 7; k++) {
        // Resets the first and second half of the decks after each shuffle
        for (int p = 0; p < half_size; p++) {
            first_half[p] = shuffled[p];
            second_half[p] = shuffled[half_size + p];
        }

        // Interweaves the deck
        for (int i = 0, j = 0; i < half_size; i++) {
            shuffled[j] = second_half[i];
            shuffled[j + 1] = first_half[i];
            j += 2;
        }
    }

    for (int l = 0; l < PACK_SIZE; l++) {
        cards[l] = shuffled[l];
    }

    reset();
  }

  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const{
    if (next >= PACK_SIZE) {
      return true;
    } else {
      return false;
    }
  }

  