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
    for (int i = 0; i < PACK_SIZE; i++) {
      pack_input >> cards[i];
    }
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
    int middle = cards.size()/2;
    Card shuffled[PACK_SIZE];

    int j = 0;
    int k = 0;

    while (j < middle) {
      shuffled[k++] = cards[j + middle];
      shuffled[k++] = cards[j++];
    }
    
    /*
    for (int i = 0; i < 7; i++) {
      for (int j = 0, k = 0; j < middle; j++, k++) {
        shuffled[k] = cards[j + middle];
        k++;
        shuffled[k] = cards[j];
        
      }
    }
    */

    for (int l = 0; l < PACK_SIZE; l++) {
      cards[l] = shuffled[l];
    }
  }

  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const{
    if (next >= PACK_SIZE) {
      return true;
    } else {
      return false;
    }
  }

  