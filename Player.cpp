#include "Player.hpp"
#include <array>
#include <string>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

//derived class

//SIMPLE PLAYER
class Simple: public Player {
  private:
    string player_name;
    vector<Card> player_hand;
  public:
    Simple(const std::string &p_name) : player_name(p_name) {}
    
    //EFFECTS returns player's name
    virtual const std::string & get_name() const {
      return player_name;
    }
    
    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    virtual void add_card(const Card &c) {
      player_hand.push_back(c);
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    virtual bool make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) const {

      assert(round <= 2);
      
      int num_trump = 0;
      if (round == 1) {
        for (int i = 0; i < player_hand.size(); i++) {
          if (player_hand[i].is_face_or_ace() && 
              player_hand[i].is_trump(upcard.get_suit())) {
            num_trump++;
          }
        }
        if (num_trump >= 2) {
          order_up_suit = upcard.get_suit();
          return true;
        }
      } else if (round == 2) {
        if (is_dealer) {
          order_up_suit = Suit_next(upcard.get_suit());
          return true;
        }
        int num_new_trump = 0; 
        for (int i = 0; i < player_hand.size(); i++) {
          if (player_hand[i].is_face_or_ace() && 
              player_hand[i].is_trump(Suit_next(upcard.get_suit()))) {
                num_new_trump++;
              }
        }
        if (num_new_trump >= 1) {
          order_up_suit = Suit_next(upcard.get_suit());
          return true;
        } else {
          return false;
        }
      } 
      return false; 
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    virtual void add_and_discard(const Card &upcard) {
      Suit trump = upcard.get_suit();
      int lowest_val = 0;
      player_hand.push_back(upcard);
      for (int i = 0; i < player_hand.size(); i++) {
        if (Card_less(player_hand[i], player_hand[lowest_val], trump)) {
          lowest_val = i;
        }
      }
      player_hand.erase(player_hand.begin() + lowest_val);
    }

   //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    virtual Card lead_card(Suit trump) {
      int highest_index = 0;
      int num_trumps = 0;
    
      //bool trumps = true;
      for (int i = 0; i < player_hand.size(); i++) {
        if (player_hand[i].get_suit() == trump || 
            (player_hand[i].get_suit() == Suit_next(trump) 
             && player_hand[i].get_rank() == JACK)) {
          num_trumps++;
        }
      }

      if (num_trumps == player_hand.size()) {
        for (int i = 0; i < player_hand.size(); i++) {
          if (Card_less(player_hand[highest_index], player_hand[i], trump)) {
            highest_index = i;
          }
        }
      } else {
          for (int i = 0; i < player_hand.size(); i++) {
            if (player_hand[i].get_suit() != trump && 
                !(player_hand[i].get_suit() == Suit_next(trump) 
                  && player_hand[i].get_rank() == JACK) 
                  && Card_less(player_hand[highest_index], player_hand[i], trump)) {
                     highest_index = i;
            }
          }
        
      }
      
      Card highest = player_hand[highest_index];
      player_hand.erase(player_hand.begin() + highest_index);
      return highest;
    }
    
    
    
    

    //REQUIRES Player has at least one card
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    virtual Card play_card(const Card &led_card, Suit trump) {
      int highest_index = 0;
      int lowest_index = 0;
      vector<Card> same_suit_cards;
      Card card_to_play;
      sort(player_hand.begin(), player_hand.end());
     
      for (int i = 0; i < player_hand.size(); i++) {
        if (player_hand[i].get_suit(trump) == led_card.get_suit()) {
          same_suit_cards.push_back(player_hand[i]);
        }
      }

      if (same_suit_cards.size() > 0) {
        for (int i = 0; i < same_suit_cards.size(); i++) {
          if (Card_less(player_hand[highest_index], player_hand[i], led_card, trump)) {
            highest_index = i;
          }
        }
        card_to_play = player_hand[highest_index];
        player_hand.erase(player_hand.begin() + highest_index);
      }
        
      

      for (int i = 0; i < player_hand.size(); i++) {
        if (player_hand[i].get_suit(trump) != led_card.get_suit()) {
          if (Card_less(player_hand[i], player_hand[lowest_index], led_card, trump)) {
            lowest_index = i;
          }
        }
        card_to_play = player_hand[lowest_index];
        player_hand.erase(player_hand.begin() + lowest_index);
        break;
      }
      return card_to_play;
    }
};
    
   


//HUMAN PLAYER
class Human: public Player {
  private:
    string player_name;
    vector<Card> player_hand;

    void print_hand() const {
      for (size_t i=0; i < player_hand.size(); ++i) {
        cout << "Human player " << player_name << "'s hand: "
         << "[" << i << "] " << player_hand[i] << endl;
      }
    }

  public:
    Human(const std::string &p_name) : player_name(p_name) {}

    virtual const std::string & get_name() const {
      return player_name;
    }
    
    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    virtual void add_card(const Card &c) {
      if (player_hand.size() < MAX_HAND_SIZE) {
        player_hand.push_back(c);
      }
      sort(player_hand.begin(), player_hand.end());
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    virtual bool make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) const {
      if (round == 1 || round == 2) {
        for (int i = 0; i < player_hand.size(); i++) {
          print_hand();
          cout << "Human player " << player_name << 
                  ", please enter a suit, or \"pass\":" << endl;
        }

        string response;
        cin >> response;

        if (response != "pass") {
          order_up_suit = string_to_suit(response);
          return true;
        } else {
          return false;
        }
      } 
      return false;
      
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    virtual void add_and_discard(const Card &upcard) {
      bool dealer = true;
      int round{};
      sort(player_hand.begin(), player_hand.end());
      string ordered_up_suit;
      if (dealer && round == 1 && 
          upcard.get_suit() == string_to_suit(ordered_up_suit)) {
        for (int i = 0; i < player_hand.size(); i++) {
          print_hand();
          cout << "Discard upcard: [-1]" << endl;
          cout << "Human player " << player_name << 
                  ", please select a card to discard:" << endl;

          int response = 0;
          cin >> response;

          if (response != -1) {
            player_hand.push_back(upcard);
          } else if (response == i) {
            player_hand.erase(player_hand.begin() + i);
          }
        }
      }
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    virtual Card lead_card(Suit trump) {

      sort(player_hand.begin(), player_hand.end());
      print_hand();
      cout << "Human player " << player_name << ", please select a card:" << endl;

      int response = 0;
      cin >> response;
      cout << player_hand[response] << " led by " << player_name << endl;

      player_hand.erase(player_hand.begin() + response);

      return player_hand[response];

    }
    //REQUIRES Player has at least one card
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    virtual Card play_card(const Card &led_card, Suit trump) {
      sort(player_hand.begin(), player_hand.end());

      print_hand();
      cout << "Human player " << player_name << 
              ", please select a card to discard:" << endl;

      int response = 0;
      cin >> response;
      player_hand.erase(player_hand.begin() + response);
      return player_hand[response];
    }
};

Player * Player_factory(const std::string &name, 
                        const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new Simple(name);
  } else if (strategy == "Human") {
    return new Human(name);
  } 
  assert(false);
  
}


std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}
