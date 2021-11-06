#include <iostream>
#include <stdlib.h>
#include <vector>
#include <sstream>

using namespace std;


struct PlayerDetails
{
	string firstName, lastName;
	int p1turnTotal, p2turnTotal;

	//constructor
	PlayerDetails(int p1tt = 0, int p2tt = 0, string fN = "", string lN = "")
	{
		p1turnTotal = p1tt;
		p2turnTotal = p2tt;
		firstName = fN;
		lastName = lN;
	}
};


//function prototype
void line(int length);
int mainScreen();
void instruction();
int setMaxScore(int &maxScore);
void registerPlayers(PlayerDetails& p1name, PlayerDetails& p2name);
string playGame(int maxScore, PlayerDetails& p1name, PlayerDetails& p2name, int* p1score, int* p2score);
//string playGame(int maxScore, PlayerDetails& p1name, PlayerDetails& p2name);
int RollingSum(int whichplayer, vector <PlayerDetails>& player);
int diceRollTurn();
vector <PlayerDetails> keepRolling(int whichplayer, vector <PlayerDetails>& p1At, int mS);
void displayScoreboard(string& passedScore);




int main()
{
	srand(time(NULL));
	int maxScore = 0;
	PlayerDetails p1name, p2name;
	int p1=0, p2=0;
	
displayMain:
	//cout << "debugging: current max score = " << maxScore;
	switch (mainScreen())
	{
	case 1:
		instruction();
		goto displayMain;
	case 2:
		maxScore = setMaxScore(maxScore);
		goto displayMain;
	case 3:
		registerPlayers(p1name, p2name);
		goto displayMain;
initPlay:
	case 4:
		if (maxScore == 0)
		{
			cout << "\nPlease set the max score before playing\n";
			setMaxScore(maxScore);
			goto initPlay;
		}
		else if (p1name.firstName == "")
		{
			cout << "\nPlease register player details before playing\n";
			registerPlayers(p1name, p2name);
			goto initPlay;
		}
		else
		{
			playGame(maxScore, p1name, p2name,&p1, &p2);
			goto displayMain;
		}
	case 5:
		line(50);
		cout << "The final score of " << p1name.firstName << " is " << p1;
		cout << "\n\nThe final score of " << p2name.firstName << " is " << p2;
		line(50);
	case 6:
		return 0;
	}


}

//############# DISPLAY FUNCTIONS #################
void line(int length)
{
	cout << "\n";
	for (int i = 0; i < length; i++)
	{
		cout << "*";
	}
	cout << "\n";
}

int mainScreen()
{
	int playChoice;
	cout << "\n\nTwo Player Dice Game -- Pre set Maximum Score";
	line(50);
	cout << "\n1. Instruction";
	cout << "\n2. Set Maximum Score";
	cout << "\n3. Register Players";
	cout << "\n4. Play";
	cout << "\n5. Display ScoreBoard";
	cout << "\n6. End";
	cout << "\n\nEnter your option :\t";
	cin >> playChoice;

	return playChoice;
}

void instruction()
{
	cout << "\n";
	line(80);
	cout << "\t\t\tInstruction";
	line(80);
	cout << "\n1. Players must feed their names and pre-set the maximum score before the game starts.";
	cout << "\n2. Each player has 2 6 face dice to roll, and the players take turns to earn scores.";
	cout << "\n3. For each roll, dice 1 and dice 2 values will be added together for the corresponding player.";
	cout << "\n4. If both dice values are the same, then the score will be 2 times the sum of the value";
	cout << "\n\t E.g. If the player rolls 3 for both dice 1 and dice 2, then they will score (3 + 3) x 2 = 12";
	cout << "\n5. Whoever reaches the maximum score first will be declared the winner, ending the game";
	cout << "\n6. After each roll, each player's scoreboard will be updated and displayed.";
	line(80);
}

void displayScoreboard(string &passedScore)
{
	cout << passedScore;
}

//################################
//INPUT FUNCTIONS
//################################
//Registering player details
void registerPlayers(PlayerDetails& p1name, PlayerDetails& p2name)
{
	cout << "\nEnter Player 1's first name:\t";
	cin >> p1name.firstName;
	cout << "Enter Player 1's last name:\t";
	cin >> p1name.lastName;

	cout << "\nEnter Player 2's first name:\t";
	cin >> p2name.firstName;
	cout << "Enter Player 2's last name:\t";
	cin >> p2name.lastName;
}

int setMaxScore(int& maxScore)
{
	cout << "What is the maximum score that you'd like to roll for? ";
	cin >> maxScore;

	return maxScore;
}

//####################################
//MAIN GAMEPLAY FUNCTIONS
//###################################

string playGame(int maxScore, PlayerDetails& p1name, PlayerDetails& p2name, int *p1score, int *p2score)
{
	vector <PlayerDetails> p1AllTurnScores, p2AllTurnScores;
	int p1sum=0, p2sum=0, pid1 = 1, pid2 = 2;
	int p1rollTimes = 0, p2rollTimes = 0;

	*p1score = 0;
	*p2score = 0;

rollAgain:
	cout << "\nPress any key to roll the dice...\n";
	cin.ignore();
	//cout << "\ndebugging: p1rolltimes\t" << p1rollTimes << "\tand rolling score\t" << p1sum;
	//cout << "\ndebugging: p1rolltimes\t" << p2rollTimes << "\tand rolling score\t" << p2sum;
	if (p1rollTimes <= p2rollTimes)
	{
		cout << "\n" << p1name.firstName << "'s roll #" << p1rollTimes + 1 << endl;
		keepRolling(pid1, p1AllTurnScores, maxScore);
		RollingSum(pid1, p1AllTurnScores);
		p1sum += p1AllTurnScores[p1rollTimes].p1turnTotal;
		cout << "\nPlayer 1's total rolling score:\t" << p1sum;
		p1rollTimes += 1;
		if (p1sum < maxScore)
		{
			goto rollAgain;
		}
		else
		{
			cout << "\n\nCongratulations " << p1name.firstName << " " << p1name.lastName << ", you won!";
		
		}
	}
	else
	{
		cout << "\n" << p2name.firstName << "'s roll #" << p2rollTimes + 1 << endl;
		keepRolling(pid2, p2AllTurnScores, maxScore);
		RollingSum(pid2, p2AllTurnScores);
		p2sum += p2AllTurnScores[p2rollTimes].p2turnTotal;
		cout << "\nPlayer 2's total rolling score:\t" << p2sum;
		p2rollTimes += 1;
		if (p2sum < maxScore)
		{
			goto rollAgain;
		}
		else
		{
			cout << "\n\nCongratulations " << p1name.firstName << " " << p1name.lastName << ", you won!";

		}
	}
	/*keepScore << "\n\nThe final score of " << p1name.firstName << " is " << p1sum << "\n\nThe final score of " << p2name.firstName << " is " << p2sum;
	string keptScore = keepScore.str();
	return keptScore;*/
	*p1score = p1sum;
	*p2score = p2sum;
	return "success";
}


//This function adds the total score stored within the players' respective arrays
int RollingSum(int whichplayer, vector <PlayerDetails>& player)
{
	int arrayTotal = 0;
	for (int i = 0; i < player.size(); i++)
	{
		if (whichplayer == 1)
		{
			arrayTotal += player[i].p1turnTotal;
		}
		else
		{
			arrayTotal += player[i].p2turnTotal;
		}
	}
	return arrayTotal;
}

//This function rolls the dice, then stores the value in the tempTurnStore array, which is then pushed back to the respective players' score keeping arrays
vector <PlayerDetails> keepRolling(int whichplayer, vector <PlayerDetails>& p1At, int mS)
{
	PlayerDetails tempTurnStore; //receiving each player's turn results 

	
	if (whichplayer == 1)
	{
		tempTurnStore.p1turnTotal = diceRollTurn();
		p1At.push_back(tempTurnStore);
		cout << "\nPlayer's score for this round:\t" << tempTurnStore.p1turnTotal;
	}
	else
	{
		tempTurnStore.p2turnTotal = diceRollTurn();
		p1At.push_back(tempTurnStore);
		cout << "\nPlayer's score for this round:\t" << tempTurnStore.p2turnTotal;
	}
	
	return p1At;
}



//This function simulates rolling 2 dice and recording the sum. If both dice values are equal, the sum value is doubled
int diceRollTurn()
{
	int rollResultTotal, rollResult1 = 0, rollResult2 = 0;

	rollResult1 = rand() % 6 + 1;

	cout << "\nDice 1:\t" << rollResult1;

	rollResult2 = rand() % 6 + 1;
	cout << "\nDice 2:\t" << rollResult2;

	if (rollResult1 == rollResult2)
	{
		rollResultTotal = (rollResult1 + rollResult2) * 2;
		//cout << "\n"<< rollResultTotal << " <-diceroll debug\n"; //for debugging 
	}
	else
	{
		rollResultTotal = rollResult1 + rollResult2;
		//cout << "\n" << rollResultTotal << " <-diceroll debug\n"; //for debugging 
	}
	return rollResultTotal;
	
}






//############# PERSONAL NOTES ON ARRAY RESIZING ################
//In theory, vectors seem to be much more efficient. But if there is some reason an array is being used and needs to be resized
//p1vec.resize(maxRollArraySize); //cool to remember for future array resizing, even though not necessary
//It's then possible to determine the max array size based on input and resize it
//int setMaxScore(int& user_input)
//{
//	cout << "What is the maximum score that you'd like to roll for? ";
//	cin >> user_input;
//	//The minimum score a player can roll for each round is 1+2, so arranging for maximum array size
//	int maxArraySize = user_input / 3;
//
//	return maxArraySize;
//}