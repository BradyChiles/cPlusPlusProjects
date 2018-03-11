//Brady Chiles
// 9/24/17
// bmchiles@dmacc.edu

/*
This program will read in three files, one for the teams in the MLB, one for the corresponding league for each team, and one containing every World Cup winner starting from 1903.
It will take the teams and their corresponding league and store it in a vectore with all of the other teams. It will also determine the number of world cup wins for each team.
Furthermore it will sort all of the teams into each corresponding league. Once the leagues have been sorted it will sort the leagues from least to greatest based on number of 
World Cup wins. Finally it will output each league with their corresponding teams and the years each team won the World Cup.
*/

/*
The approach I took, was to take all of the input and store it together initially, then sort it out by league, then sort out the leagues from least to greatest by World Cup wins.
I thought storing the data in a struct was the easiest way to keep the information together, rather than splitting it into different arrays/vectors. Additionally, I thought it 
was easier to split the teams into two seperate league vectors rather than dealing with them in the same vector once all of the information was in. 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//Struct for the team information that will be held in various vectors
struct Team {
	string name;
	string league;
	int wins;
};

//Prototype for a function that will be used as the compare for the sort standard library function
bool sortCompare(Team one, Team two);

int main()
{
	//Variables
	int counter = 0;
	string input = "";
	int win = 0;
	Team t;
	vector<Team> allTeams;
	vector<Team> americanLeague;
	vector<Team> nationalLeague;
	vector<string> worldCupWinners;
	ifstream teamsIn;
	ifstream leagueIn;
	ifstream winnersIn;
	
	//Read file streams
	teamsIn.open("Teams.txt");
	leagueIn.open("Leagues.txt");
	winnersIn.open("WorldSeriesWinners.txt");

	//Read in the TEam file and store a team object for each team read inthe allTeams vector
	counter = 0;
	while (getline(teamsIn, input))
	{
		t.name = input;
		t.league = "";
		t.wins = 0;
		allTeams.push_back(t);
		counter ++;
	}
	
	//Read the leagues in from the Leagues file. This will match each team already in the allTeams vector. League will be added to eahch Team object in the vector
	counter = 0;
	while (getline(leagueIn, input))
	{
		allTeams[counter].league = input;
		counter ++;
	}

	//Read the world cup winners from the World Cup Winners file and store it in a vector for later use. Additionally it will increase the number of wins
	//for the correspondng team in allTeams<> for each world cup win it reads.
	while (getline(winnersIn, input))
	{
		worldCupWinners.push_back(input);
			for (int i = 0; i < allTeams.size(); i++){
				if (allTeams[i].name == input){
					allTeams[i].wins++;
				}
			}
	}
	
	//Sort the allTeams vector into two additional vectors, one for each league.
	for(int i = 0; i < allTeams.size(); i++){
		if(allTeams[i].league == "American League"){
			americanLeague.push_back(allTeams[i]);
		}else if(allTeams[i].league == "National League"){
			nationalLeague.push_back(allTeams[i]);
		}
	}
	
	//Sort the American League vector from least to greatest on the number of wins for each team
	std::sort(americanLeague.begin(), americanLeague.end(), sortCompare);
	
	//Sort the National League vector from least to greatest on the number of wins for each team
	std::sort(nationalLeague.begin(), nationalLeague.end(), sortCompare);

	//Output for American League
	cout << "American League" << endl;
	cout << "-----------------------------------------------" << endl;
	
	//Will run through the worldCupWinners vector for every team in the americanLeague vector. It will output the years they won the World Cup, starting from 1903.
	for (int i = 0; i < americanLeague.size(); i++){
		cout << americanLeague[i].name << ": ";
		counter = 1903;
		for(int j = 0; j < worldCupWinners.size(); j++){
			if(worldCupWinners[j] == americanLeague[i].name){
				cout << counter << " ";
			}
			counter++;
		}
		cout << endl;
	}
	
	cout << endl << endl;
	
	//Output for the National League
	cout << "National League" << endl;
	cout << "-----------------------------------------------" << endl;
	
	//Will run through the worldCupWinners vector for every team in the nationalLeague vector. It will output the years they won the World Cup, starting from 1903.
	for (int i = 0; i < nationalLeague.size(); i++){
		cout << nationalLeague[i].name << ": ";
		counter = 1903;
		for(int j = 0; j < worldCupWinners.size(); j++){
			if(worldCupWinners[j] == nationalLeague[i].name){
				cout << counter << " ";
			}
			counter++;
		}
		cout << endl;
	}
	
	std::getchar();
	
	return 0;	
}


//Function used with the standard library sort function. Will make the sort(), sort based on number of wins
bool sortCompare(Team one, Team two) { 
	return one.wins < two.wins; 
}
