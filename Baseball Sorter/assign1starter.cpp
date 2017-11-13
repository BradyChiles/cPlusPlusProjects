// Joe Struss, jastruss@dmacc.edu, Sept. 15, 2016
// Starter Program for those you are stuck on Assignment1A

// This program uses three files and brings in the data from Teams.txt, Leagues.txt and WorldSeriesWinners.txt
//   and puts that data for the first two files into Teams and League arrays.  The program then processes the third file and
//   puts that information into the Wins array.  The program displays information when it reads in the data and
//   also display additional information at the very end once the data is processed.

//  Use this program if you are stuck and see if you can find a way to sort out to the screen the National and American
//    Team Winners in separate lists with the most winning teams sorted first.   Chapter 8 might be helpful in showing
//    sorting techniques that you can use.   Good luck.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main()
{
	ifstream WinnersIn;		
	ifstream TeamsIn;			
	ifstream LeagueIn;        
	string input;
	string Teams[30];
	int Wins[30];
	string League[30];
	int counter;
	
	TeamsIn.open("Teams.txt");
	LeagueIn.open("Leagues.txt");
	WinnersIn.open("WorldSeriesWinners.txt");

	counter = 0;
	while (getline(TeamsIn, input))
	{
		Teams[counter] = input;
		Wins[counter] = 0;
		cout << "Team " << counter << " " << input << endl;
		counter++;
	}

	counter = 0;
	while (getline(LeagueIn, input))
	{
		League[counter] = input;
		cout << "League " << counter << " " << input << endl;
		counter++;
	}

	counter = 0;
	while (getline(WinnersIn, input))
	{
		cout << "Winners " << counter << " " << input << endl;
		for (int x = 0; x < 30; x++)
		{
			if (Teams[x] == input)
			{
				Wins[x]++;
			}
		}
		counter++;

	}

	for (int x = 0; x < 30; x++)
	{
		cout << Teams[x] << " (" << League[x] << ") had " << Wins[x] << " World Series victories" << endl;
	}

	TeamsIn.close();
	LeagueIn.close();
	WinnersIn.close();

	return 0;
}
