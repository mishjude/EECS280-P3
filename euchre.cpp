#include <iostream>
#include <fstream>
#include "Pack.hpp"
#include "Card.hpp"
#include "Player.hpp"
#include <cstring>

using namespace std;

class Game {
 public:
 //add outside information as parameters then call it at the end of main
 //make sure parameter names are diff than private variable names
  Game(Pack& p, int &points_win, string &shuffled, 
        vector<Player*> &player_names_and_type) {
    pack = p;
  }

  void play();

 private:
  vector<Player*> players;
  Pack pack;
  Card upcard;
  bool is_dealer;
  string shuffle_or_no;
  int dealer_index;
  int round;
  Suit trump;
  int hand;
  int t1_points;
  int t2_points;
  int player_make_trump;
  int t1_num_tricks;
  int t2_num_tricks;
  int points_to_win;
  vector<Player*> t1;
  vector<Player*> t2;

  void shuffle(); 
  void deal(); 
  void make_trump(Card &upcard, int round, Suit trump); 
  void play_hand(); 
  void add_player(Player *player); 
  void change_dealer(); 
  void update_hand();
  void score();
  void make_teams(); 
  void pack_init(istream& file_name);
  
};

void Game::make_teams() {
  
  //team 1
  t1.push_back(players[0]);
  t1.push_back(players[2]);

  //team 2
  t2.push_back(players[1]);
  t2.push_back(players[3]);
}

//function implementation

void Game::update_hand() {
  hand++;
}

void Game::shuffle() {
  //how to use command line prompt to affect this?
  //if "shuffle", then call pack shuffle 
  //if no shuffle, then don't call pack shuffle
  pack.Pack::shuffle();
}

void Game::change_dealer() {
  dealer_index = (dealer_index + 1) % 4;
}

void Game::deal() {
  //3-2-3-2 then 2-3-2-3
  players[dealer_index + 1]->add_card(pack.deal_one());
  players[dealer_index + 1]->add_card(pack.deal_one());
  players[dealer_index + 1]->add_card(pack.deal_one());
  players[dealer_index + 2]->add_card(pack.deal_one());
  players[dealer_index + 2]->add_card(pack.deal_one());
  players[dealer_index + 3]->add_card(pack.deal_one());
  players[dealer_index + 3]->add_card(pack.deal_one());
  players[dealer_index + 3]->add_card(pack.deal_one());
  players[dealer_index]->add_card(pack.deal_one());
  players[dealer_index]->add_card(pack.deal_one());
  players[dealer_index + 1]->add_card(pack.deal_one());
  players[dealer_index + 1]->add_card(pack.deal_one());
  players[dealer_index + 2]->add_card(pack.deal_one());
  players[dealer_index + 2]->add_card(pack.deal_one());
  players[dealer_index + 2]->add_card(pack.deal_one());
  players[dealer_index + 3]->add_card(pack.deal_one());
  players[dealer_index + 3]->add_card(pack.deal_one());
  players[dealer_index]->add_card(pack.deal_one());
  players[dealer_index]->add_card(pack.deal_one());
  players[dealer_index]->add_card(pack.deal_one());

  Card upcard = pack.deal_one();
  cout << "Hand " << hand << endl;
  hand++;
  cout << players[dealer_index]->get_name() << " deals" << endl;
  cout << upcard << " turned up" << endl;


}

void Game::make_trump(Card &upcard, int round, Suit trump) {
  //iterate through all players
  for (int i = 0; i < 4; i++) {
    //if player orders up suit
    if (players[(dealer_index + i) % 4]->make_trump(upcard, is_dealer, round, trump)) {
      trump = upcard.get_suit();
      cout << players[(dealer_index + i) % 4]->get_name() << 
              " orders up " << trump << endl;
      players[dealer_index]->add_and_discard(upcard);
      player_make_trump = (dealer_index + i) % 4;
      return; //once someone orders up then leave function
    } else { //if player doesnt order up suit
      cout << players[(dealer_index + i) % 4]->get_name() << " passes" << endl;
    }
  }
}

void Game::play_hand() {
  int leader = (dealer_index + 1) % 4;
  Card led_card;
  Card highest = led_card;
  Suit trump = led_card.get_suit(); //??
  

  //5 tricks per hand - make a separate function to call the trick 5 times
  for (int i = 0; i < 5; i++) {
    //first player
    led_card = players[leader]->lead_card(trump);
    cout << led_card << " led by " << players[leader]->get_name() << endl;

    //iterate through the rest of the players 
    for (int j = 0; j < 3; j++) {
      cout << players[j]->play_card(led_card, trump) << 
              " played by " << players[j]->get_name() << endl; 

      //update leader
      if (Card_less(highest, players[j]->play_card(led_card, trump), trump)) {
        highest = players[j]->play_card(led_card, trump);
        leader = j;
      }
    }
    cout << players[leader]->get_name() << " takes the trick" << endl << endl;
    if (leader == 0 || leader == 2) {
      t1_num_tricks++;
    } else if (leader == 1 || leader == 3) {
      t2_num_tricks++;
    }
  }
}

//initializes players?
void Game::add_player(Player *player) {
  players.push_back(player);
}

//initialises pack??
void Game::pack_init(istream& file_name) {
  
  ifstream pack_filename; //???? how to use command line argument here?
  pack = Pack(pack_filename);
}


void Game::score() {
  //t1 = 0 + 2, t2 = 1 + 3
  //if t1 won
  if (t1_num_tricks > t2_num_tricks) {
    //march?
    cout << t1[0] << " and " << t1[1] << " win the hand" << endl;
    if ((player_make_trump == 0 || player_make_trump == 2) 
        && t1_num_tricks == 5) {
          cout << "march!" << endl;
          t1_points += 2;
        } else if ((player_make_trump == 1 || player_make_trump == 3) 
                   && t1_num_tricks >= 3) { //euchred
          cout << "euchred!" << endl;
          t1_points += 2;
        } else if ((player_make_trump == 0 || player_make_trump == 2) 
                   && (t1_num_tricks == 4 || t1_num_tricks == 3)) {
                    t1_points++;
        }  
  } else if (t2_num_tricks > t1_num_tricks) {
    cout << t2[0] << " and " << t2[1] << " win the hand" << endl;
    if ((player_make_trump == 1 || player_make_trump == 3) 
        && t2_num_tricks == 5) {
          cout << "march!" << endl;
          t2_points += 2;
        } else if ((player_make_trump == 0 || player_make_trump == 2)
                   && t2_num_tricks >=3) {
                    cout << "euchred!" << endl;
                    t2_points += 2;
                   } else if ((player_make_trump == 1 || player_make_trump == 3) 
                              && (t2_num_tricks == 3 || t2_num_tricks == 4)) {
                                t2_points++;
                              }
  }
  cout << t1[0] << " and " << t1[1] << " have " << t1_points << " points" << endl;
  cout << t2[0] << " and " << t2[1] << " have " << t2_points << " points" << endl;

}


void Game::play() {

  
  while (t1_points < points_to_win && t2_points < points_to_win) { 
    deal();
    make_trump(upcard, round, trump);
    play_hand();
    score();
    change_dealer();
    update_hand();
  }
  

  for (size_t i = 0; i < players.size(); ++i) {
    delete players[i];
  }
}

//main
int main(int argc, char **argv) {

  //checking if there's the correct number of arguments
  if (argc != 12) {
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
  }

  //opening the file
  ifstream pack_filename;
  pack_filename.open(argv[1]);

  //checking if the file opened properly
  if (!(pack_filename.is_open())) {
    cout << "Error opening " << argv[1] << endl;
  }

  Pack p = Pack(pack_filename);
  
  
  //checking if command line argument has shuffle or no shuffle
  if (strcmp(argv[2], "shuffle") != 0 && strcmp(argv[2], "noshuffle") != 0) {
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
  }

  string shuffle = argv[2];

  //checking if the points to win the game are valid 
  int points = atoi(argv[3]);
  if (points < 1 || points > 100) {
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
  }


  //checking if the type of player is simple or human (arg 5, 7, 9, 11)
  if (((strcmp(argv[5], "Simple") != 0) && (strcmp(argv[5], "Human") != 0)) ||
      ((strcmp(argv[7], "Simple")) !=0 && (strcmp(argv[7], "Human") != 0)) ||
      ((strcmp(argv[9], "Simple")) !=0 && (strcmp(argv[9], "Human") != 0)) ||
      ((strcmp(argv[11], "Simple") !=0) && (strcmp(argv[11], "Human") != 0))) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
      }

  //print executable and all command line arguments 
  for (int i = 0; i < 12; i++) {
    cout << argv[i] << " ";
  }
  cout << endl;

  vector<Player*> players;

  Player * p1 = Player_factory(argv[4], argv[5]);
  Player * p2 = Player_factory(argv[6], argv[7]);
  Player * p3 = Player_factory(argv[8], argv[9]);
  Player * p4 = Player_factory(argv[10], argv[11]);

  players.push_back(p1);
  players.push_back(p2);
  players.push_back(p3);
  players.push_back(p4);
  

  //call game constructor
  Game game = Game(p, points, shuffle, players);

  //plays through the game
  game.play();
  
}
