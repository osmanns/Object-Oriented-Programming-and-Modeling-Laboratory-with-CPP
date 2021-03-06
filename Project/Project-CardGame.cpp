/*=============================
Program name : BlackJack
Programmer : Nuttasit Kaewthong
StudentID : 59160651
Program : C++ 
Major : SE
=============================*/

#include <iostream>
#include <cstdlib> // random number generator
#include <string> 
#include <ctime>
#include <conio.h>
#include <fstream>

using namespace std;

#ifndef Card_H
#define Card_H
class Card // ====== Class Card ======
{
	//Overloading the Stream Insertion (<<) Operators
	friend ostream& operator<<(ostream& out, const Card& obj);
	
	private :
		int face;
		int suit;

	public :
		Card();	// default constructer	
		Card(int cardFace, int cardSuit); // constructer with parameters
		void setCard(int cardFace, int cardSuit); // set the face and suit with parameters
		int getFace(); // return the face of card will be displayed
		int getSuit(); // return the suit of card will be displayed
};
#endif

Card::Card() 
{	
}

Card::Card(int cardFace, int cardSuit) 
{
	face = cardFace;
	suit = cardSuit;
}

void Card::setCard(int cardFace, int cardSuit) 
{
	face = cardFace;
	suit = cardSuit;
}

int Card::getFace()
{
	if(face <= 10){
        return face;
    }
	else{
        return 10;
    }
}

int Card::getSuit()
{	
	return suit;
}

ostream& operator<<(ostream& out, const Card& obj){
	if(obj.face == 1){
       out << "A";
   	}else if(obj.face == 11){
       out << "J";
  	 }else if(obj.face == 12){
       out << "Q";
  	 }else if(obj.face == 13){
       out << "K";
  	 }else{
       out << obj.face;
  	 }

  	 out << " of ";
 
  	 if(obj.suit == 1){
       out << "Hearts";
  	}else if(obj.suit == 2){
       out << "Diamons";
  	}else if(obj.suit == 3){
       out << "Clubs";
  	}else if(obj.suit == 4){
       out << "Spades";
  	}

   return out;
}

const int number = 52; // Declare global constant variables

class DeckOfCards // ====== Class DeckOfCard ======
{
	private :
		Card *cards;
		int currentCard;
		int index;
		
	public :
		
		DeckOfCards(); // default constructer		
		void shuffleCards(); // shuffles rearranges the cards in the deck
		Card dealCards(); // deals out one card from the deck				
		void print(); // displays the given card's face and suit
};

DeckOfCards::DeckOfCards()
{
	currentCard = 0;
	index = 0;
		/*
		string faces[] = {"A", "2", "3", "4", "5", "6", 
					  	  "7", "8", "9", "10", "J", "Q", "K"};   
		string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
		
				for(int count=0; count<number; count++){
					cards[count] = Card(faces[count % 13], suits[count / 13]);
				}
		*/	
			cards = new Card[number];			
			for(int i=1; i<=4; i++){
				for(int j=1; j<=13; j++){
					cards[index++].setCard(j, i);
				}     			
       		}								
}

void DeckOfCards::shuffleCards()
{	
	srand(time(NULL));
	for(int i=0; i<500; i++){			
	
		int p1 = rand() % number;
		int p2 = rand() % number;
	
			Card temp;
			temp = cards[p1];
 			cards[p1] = cards[p2];
			cards[p2] = temp;
	}
}

Card DeckOfCards::dealCards()
{
	if(currentCard > number){
		shuffleCards();
	}
	if(currentCard <= number)
	{
		return (cards[currentCard++]);
	}	
}

void DeckOfCards::print()
{
    for(int j = 1 ; j <= 4; j++){
        for(int i = 1 ; i <= 13; i++){
            cout << cards[currentCard++] << endl;
        }
    }	
}

class Game // ====== Class Player ======
{
	public :
		DeckOfCards deck;
		Card player[7];
		Card dealer[7];
		int pointPlayer;
		int pointDealer;
		
	public :	
		Game(); // default constructer	
		void setPoint();	 
		void handPlayer(); // set card on playerhand dealerhand 
		int playerHit(); // player hit or stand card
		int dealerHit(); // dealer hit or stand card
		int getAcePlayer(); // player has a ace card on the hand	
		int getAceDealer(); // dealer has a ace card on the hand
		int getPointPlayer(); // return the player point of card will be displayed	
		int getPointDealer(); // return the dealer point of card will be displayed				
};		

Game::Game()
{
	pointPlayer = 0;
	pointDealer = 0;
}

void Game::setPoint()
{
	pointPlayer = 0;
	pointDealer = 0;
}

void Game::handPlayer()
{
	deck.shuffleCards();
	for(int i=0; i<5; i++){
		player[i] = deck.dealCards();
		dealer[i] = deck.dealCards();
	}
	system("cls");
		cout << "The Dealer shuffled and dealt you each your cards." << endl << endl;
			// player hand			
			cout << "Player hand : " << endl;
				for(int i=0; i<2; i++){
						cout << "\t\t"  << player[i] << endl;			
						pointPlayer += player[i].getFace();			
				}	
				cout << "\nPoint : " << "[" << pointPlayer << "]" << endl;				
				getAcePlayer();	// player has a ace card on the hand			
		
			// dealer hand		
			cout << "\nDealer hand : " << endl;
				for(int i=0; i<2; i++){					
					dealer[i].getFace();				
					if(i == 0){
						cout << "\t\t" << "*********** ?" << endl;					
					}
					else
						cout << "\t\t" << dealer[1] << endl;
						pointDealer += dealer[i].getFace();				
				getAceDealer();	// dealer has a ace card on the hand											
				}						
		playerHit();
}

int Game::playerHit()
{

	cout << "\n\n\nWould you like to hit or stand? (h/s) >> ";
	
		string ch = "h, s";
		cin >> ch;
		do{
	
		system("cls");
		if(ch != "h" && ch != "s"){
			cout << "\n\n\nWould you like to hit or stand? (h/s) >> ";  
			cin >> ch;
		}
			if(ch == "h"){			
				{ // player hand
					cout << "Player hand : " << endl;
						for(int i=0; i<2; i++){
							cout << "\t\t" << player[i] << endl;				
						}
						for(int i=4; i<5; i++){	
							cout << "\t\t[Player hit]" << endl;
							cout << "\t\t" << player[i] << endl;
							pointPlayer += player[i].getFace();
						}				
					getAcePlayer(); //  has a ace card on the hand
					cout << "\nPoint : " << "[" << pointPlayer << "]" << endl;
				}
				{ // dealer hand
					cout << "\nDealer hand : " << endl;
						for(int i=0; i<2; i++){
							dealer[i];
						
							if(i == 0){
								cout << "\t\t" << dealer[0] << endl;					
							}
							else
								cout << "\t\t" << dealer[1] << endl;																		
						}				
					dealerHit(); // dealer point less than 17									
					getAceDealer(); // Dealer has a ace card on the hand
				}
			}
			else if(ch == "s"){
				 // player hand
					cout << "Player hand : " << endl;
						for(int i=0; i<2; i++){
							cout << "\t\t" << player[i] << endl;				
						}
							cout << "\nPoint : " << "[" << pointPlayer << "]" << endl;
				// dealer hand			
					cout << "\nDealer hand : " << endl;
						for(int i=0; i<2; i++){
							dealer[i];
						
						if(i == 0){
							cout << "\t\t" << dealer[0] << endl;					
						}
						else
							cout << "\t\t" << dealer[1] << endl;																		
						}				
					dealerHit(); // dealer point less than 17								
					getAceDealer();	// dealer has a ace card on the hand
			}				
		return pointPlayer;
		return pointDealer;	
	}while(ch != "h" && ch != "s");
}
			
int Game::dealerHit()
{
	if(pointDealer <= 16){
		cout << "\t\t[Dealer hit]" << endl;	
		
			for(int i=4; i<5; i++){
				cout << "\t\t" << dealer[i] << endl;
					pointDealer += dealer[i].getFace();
			}		
	}
	cout << "\nPoint : " << "[" << pointDealer << "]" << endl;	
					
	return pointDealer;
}
	
int Game::getAcePlayer()
{
	// player has a ace card on the hand
	if(player[0].getFace() == 1 || player[1].getFace() == 1){
		int number;				
		cout << "\nWould you like your Ace to count as 1 or 11 points? (1/11) >> ";
		cin >> number;\
			do{
				if(number != 1 && number != 11){
					cout << "\nWould you like your Ace to count as 1 or 11 points? (1/11) >> ";
					cin >> number;
				}
			}while(number != 1 && number != 11);
		pointPlayer += number-1;
	}
		return pointPlayer;	
}

int Game::getAceDealer()
{
	// dealer has a ace card on the hand
	if(dealer[0].getFace() == 1 || dealer[1].getFace() == 1){
		if(pointDealer <= 10){
			pointDealer += 10;
		}
		else if(pointDealer <= 20){
			pointDealer += 0;
		}								
	}
		return pointDealer;
}	

int Game::getPointPlayer()
{
	return pointPlayer;
}

int Game::getPointDealer()
{
	return pointDealer;
}	
		


class User // ====== Class User ====== 
{
	private :
		string name;
		string password;
				
	public :
		double money;
		double betMoney;
		User(); // default constructer
		User(string n, string p, double m); // constructer with parameters
		void setUser(string n, string p); // set the name and password with parameters	
		void setMoney(double m); // set the money with parameters	
		void setBetMoney(double b); // set the betmoney with parameters
		void Register(); // register account
		void Login(); // login account
		string getName(); 
		string getPassword();
		double getMoney();
		double getBetMoney();
		int fileR(); // read file
		void fileW(); // write file
};

User::User()
{
	name = " ";
	money = 0;
	betMoney = 0;
}

User::User(string n, string p, double m)
{
	name = n;
	password = p;
	money = m;
}

void User::setUser(string n, string p)
{
	name = n;
	password = p;
}

void User::setMoney(double m)
{
	money = m;
}

void User::setBetMoney(double b)
{
	betMoney = b;
}

string User::getName()
{
	return name;
}

string User::getPassword()
{
	return password;
}

double User::getMoney()
{
	return money;
}

double User::getBetMoney()
{
	return betMoney;
}

void User::Register()
{
	cout << "===============================================\n";
	cout << "=          BLACKJACK  Register Account        =\n";
	cout << "===============================================\n\n\n";
	cout << "Please enter your username : ";
	cin >> name;
	cout << "\nPlease enter your password : ";
	cin >> password;
	cout << "\nPlease enter your money : ";
	cin >> money;
	system("cls");
}

void User::Login()
{
	cout << "===============================================\n";
	cout << "=          BLACKJACK  Register Account        =\n";
	cout << "===============================================\n\n\n";	
	cout << "Please enter your username : ";
	cin >> name;
	cout << "\nPlease enter your password : ";
	cin >> password;	
	system("cls");		
}

int User::fileR()
{
	ifstream data;
	 	string name, password;
		double money;
		data.open("user.txt");
	 		while(data>>name){
	 			data>>password;
	 		if(getName() == name && getPassword() == password){
	 			data>>money;
	 			setUser(name, password);
	 			setMoney(money);
	 		data.close();
	 		return 1;
		 }
	 }
}

void User::fileW()
{
	ofstream data;
		data.open("user.txt", ios::app);
		data << endl << getName() << endl;
		data << getPassword() << endl;
		data << getMoney() << endl;
		data << ".";
		data.close();
} 

class Main : public Game, public User // ====== Class Main ====== 
{			
	public :
		Main();
		void menu(); // show menu	
		void play(); // play game
		void howTo(); // how to play
		void end(); // exit
};

Main::Main()
{
}

void Main::menu()
{
	int n = 0;
	char c;
	
	for(int i=0; i<=100; i++){
		system("cls");
		for(int j=0; j<10000; j++){
		}
		cout << "\tLoading " << i << "%";
	}
		
	cout << "\n ";
	for(int i=0; i<30; i++){
		for(int j=0; j<1000000; j++){
		}
		cout << "*";
	}
	
	system("cls");
	cout << "===============================================\n";
	cout << "=               BLACKJACK  GAME               =\n";
	cout << "===============================================\n\n\n";
	cout << "Welcome : " << getName() << "\t Money : $ " << getMoney() << endl;
	cout << "\nBet : ";
	cin >> betMoney;
		do{
			system("cls");
			cout << "===============================================\n";
			cout << "=               BLACKJACK  GAME               =\n";
			cout << "===============================================\n\n\n";
			cout << "Your Money : " << getMoney() << endl;
				if(betMoney>money||betMoney <= 0){
					cout << "\nYou can not place a bet." << endl;
					cout << "Enter again >> ";
					cin >> betMoney;
					setBetMoney(betMoney);
			}
		}while(betMoney>money||betMoney <= 0);
	setBetMoney(betMoney);
			
	do{
		system("cls");
		(n==0) ? cout << "\n\n	" << "[o]" << "[ play ]	" : cout << "\n\n	" << "[ ]" << "[ play ]	"  ;
		(n==1) ? cout << "[o]" << "[ rule ]	" : cout << "[ ]" << "[ rule ]	"  ;
		(n==2) ? cout << "[o]" << "[exit]" <<endl : cout << "[ ]" << "[exit] " <<endl ;

		c = getch();	
	  			if(c == 'a')
				  		(n<0) ? n=0 : n-=1;
	  			if(c == 'd')
				  		(n>2) ? n=2 : n+=1;			
	}while(c != 13); 
	
	if(n==0){
		play();				
	}
	else if(n==1){
		system("cls");
		howTo();
	}
	else if(n==2){
		end();	
	}	
}

void Main::play()
{
	string c = "y";
	system("cls");
		do{
			handPlayer();	
			cout << "\n\t\t"    << "Player Point : " << "[" << getPointPlayer() << "]" << endl;
			cout << "\t\t     " << "VS" << endl; 
			cout << "\t\t"      << "Dealer Point : " << "[" << getPointDealer() << "]" << endl;
					
			if(getPointPlayer() == 21 && getPointPlayer() > getPointDealer()){
				money += (betMoney * 1.5);
				cout << "\n[Player BLACKJACK !] You get $ " << betMoney << endl;
			}
			else if(getPointDealer() == 21 && getPointPlayer() < getPointDealer()){
				money -= (betMoney * 1.5);
				cout << "\n[Dealer BLACKJACK !] You lost $ " << betMoney << endl;
			}	
			else if(getPointPlayer() < 21 && getPointPlayer() > getPointDealer()){
				money += (betMoney * 1);
				cout << "\n[Player WIN !] You get $ " << betMoney << endl;			
			}
			else if(getPointPlayer() < 21 && getPointPlayer() < getPointDealer()){
				money -= (betMoney * 1);
				cout << "\n[Dealer WIN !] You lost $ " << betMoney << endl;
			}
			else if(getPointPlayer() > 21 && getPointDealer() < 21){
				money -= (betMoney * 1);
				cout << "\n[Player BUSTED !] You lost $ " << betMoney << endl;
			}
			else if(getPointDealer() > 21 && getPointPlayer() < 21){
				money += (betMoney * 1);
				cout << "\n[Dealer BUSTED !] You get $ " << betMoney << endl;
			}
			else if(getPointPlayer() == getPointDealer()){
				cout << "\n[PUSH !]" << endl;
				money += (betMoney*0);
			}
				
				cout << "\nwould you like to play again game or end? (y/n) : ";
				cin >> c;
					if(c == "y"){
						system("cls");
						cout << "===============================================\n";
						cout << "=               BLACKJACK  GAME               =\n";
						cout << "===============================================\n\n\n";
						cout << "\nName : " << getName() << "\t Money : $ " << getMoney() << endl;
						cout << "\nBet : ";
						cin >> betMoney;
						do{
							system("cls");
							cout << "===============================================\n";
							cout << "=               BLACKJACK  GAME               =\n";
							cout << "===============================================\n\n\n";
							cout << "Your Money : " << getMoney() << endl;
								if(betMoney>money||betMoney <= 0){
									cout << "\nYou can not place a bet." << endl;
									cout << "Bet :>> ";
									cin >> betMoney;
									setBetMoney(betMoney);
								}
						}while(betMoney>money||betMoney <= 0);
						setBetMoney(betMoney);
						system("cls");
					}
					else if(c == "n"){
						setMoney(money);
						fileW();
						cout << "\nName : " << getName() << "\t Money : $ " << getMoney() << endl;
						exit(0);
					}	
					setPoint();	
					system("cls");
		}while(c != "n");	
		setMoney(money);
		fileW();
}

void Main::howTo()
{
	cout << "===============================================================" << endl;
	cout << "==                 Welcome to Game Of Twenty One             ==" << endl;
	cout << "==                      ------------------                   ==" << endl;
	cout << "==                                                           ==" << endl;
	cout << "==  Rules                                                    ==" << endl;
	cout << "==    o Blackjack played with single deck has a lower house  ==" << endl;
	cout << "==                                                           ==" << endl;
	cout << "==    The card values                                        ==" << endl;
	cout << "==    o The numbered cards have values corresponding to      ==" << endl;
	cout << "==      their number                                         ==" << endl;
	cout << "==    o The faces cards have a value of 10                   ==" << endl;
	cout << "==    o The ace can either have a value of 1 hard value or   ==" << endl;
	cout << "==      11 soft value                                        ==" << endl;
	cout << "==                                                           ==" << endl;
	cout << "==  The purpose of the game is to come up with a hand value  ==" << endl;
	cout << "==  higher than the dealer's but not more than 21            ==" << endl;
	cout << "==                                                           ==" << endl;
	cout << "==  Should the player's hand be more than 21 the player      ==" << endl;
	cout << "==  automatically loses the game. (BUST)                     ==" << endl;
	cout << "==                                                           ==" << endl;
	cout << "==  In case the dealer has the same hand value as the        ==" << endl;
	cout << "==  player it's a push all. (PUSH)                           ==" << endl;
	cout << "==                                                           ==" << endl;
	cout << "==  BETS :                                                   ==" << endl;
	cout << "==    o Winning bets - 1 to 1                                ==" << endl;
	cout << "==        all winning bet are paid by the dealer at 1 to 1   ==" << endl;
	cout << "==                                                           ==" << endl;
	cout << "==    o Blackjack - 3 to 2                                   ==" << endl;
	cout << "==        in black jack hand that consists of an ace and     ==" << endl;
	cout << "==        a face card are paid at 3 to 2                     ==" << endl;
	cout << "==                                                           ==" << endl;	
	cout << "==    o in case the player loses, the dealer will take his   ==" << endl;
	cout << "==        bet                                                ==" << endl;
	cout << "==                                                           ==" << endl;
	cout << "===============================================================" << endl;
	cout << endl;
	
	string c = "b";
		do{					
			cout << "[Back (b)] >> ";	
			cin >> c;					
		}while(c != "b");	
	system("cls");
	menu();	
}

void Main::end()
{
	system("cls");
	cout << "\n\n      ==== Thank You ====       " << endl;
	exit(0);
}

int main()
{
	Main m;

	char choice;
	
	cout << "===============================================\n";
	cout << "=               BLACKJACK  GAME               =\n";
	cout << "===============================================\n\n\n";
	cout << "Do you have an account ?" << endl;
	cout << "1. YES" << endl;
	cout << "2. NO" << endl;
	cout << "3. EXIT" << endl;

	cout << "\n>> ";
	cin >> choice;
		do{		
			system("cls");
			if(choice != '1' && choice != '2' && choice != '3'){
				cout << "===============================================\n";
				cout << "=               BLACKJACK  GAME               =\n";
				cout << "===============================================\n\n\n";
				cout << "Do you have an account ?" << endl;
				cout << "1. YES" << endl;
				cout << "2. NO " << endl;
				cout << "Plesse select (1/2) >> ";
				cin >> choice;
			}
		}while(choice != '1' && choice != '2' && choice != '3');
		
		if(choice == '1'){
			system("cls");
			m.Login();
			m.fileR();
			
		}
		else if(choice == '2'){
			system("cls");
			m.Register();
			m.fileW();
		}
		else if(choice == '3'){
			exit(0);
		}	
	m.menu();	
}




		
