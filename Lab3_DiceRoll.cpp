#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;


struct PlayerDetails 
{
	string firstName, lastName;
	int p1turn_total, p2turn_total, p1overall_total, p2overall_total;

	//constructor
	PlayerDetails(int p1tt = 0, int p2tt = 0, int p1ot = 0, int p2ot = 0, string fN="", string lN="")
	{
		p1turn_total = p1tt;
		p2turn_total = p2tt;
		p1overall_total = p1ot;
		p2overall_total = p2ot;
		firstName = fN;
		lastName = lN;
	}
};

struct rollResults 
{
	int p1roll1, p1roll2, p2roll1, p2roll2;
	//constructor
	rollResults(int p11 = 0, int p12 = 0,  int p21 = 0, int p22 = 0)
	{
		p1roll1 = p11;
		p1roll2 = p12;
		p2roll1 = p21;
		p2roll2 = p22; 
	}
};

//function prototype
int diceRoll(int rollPointer);
//int passingVecTest(const vector<rollResults>& p);

int main()
{
	int maxScore = 180;
	int maxRollsize = maxScore / 6;
	
	vector<rollResults> p1vec, p2vec;
	//rollResults* p1ptr = new vector<rollResults>();
	vector<rollResults>* p1ptr = new vector<rollResults>();


	p1vec.resize(maxRollsize);

	for (int i = 0; i < maxRollsize; i++)
	{
		
		diceRoll(p1vec[i].p1roll1);
		diceRoll(p1vec[i].p1roll2);		//not working yet... figure out what i actually want to do in pseudocode first!!
		diceRoll(p2vec[i].p2roll1);
		diceRoll(p2vec[i].p2roll2);
	}
 	


}


int diceRoll(int rollPointer)
{
	srand(time(NULL));
	int diceroll = rand() % 6 + 1;
	rollPointer = diceroll;

	cout << diceroll << " <-diceroll debug\n"; //for debugging 
	cout << rollPointer << "<- rollPointer debug\n"; //for debugging 

	return rollPointer;

}

//int passingVecTest(vector<rollResults>& p)
//{
//	cout << "test" << p(0);
//	cout << "The value of p1vec is " << p[0];
//}

int setMaxScore()
{
	cout << "What is the maximum score that you'd like to roll for?"
}