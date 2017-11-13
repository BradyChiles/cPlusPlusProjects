//Brady Chiles
// 9/24/17
// bmchiles@dmacc.edu


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Team {
	string name;
	string league;
	int wins;
};

bool sortCompare(Team one, Team two);

int main()
{
	int counter = 0;
	string input = "";
	Team t;
	vector<Team> allTeams;
	vector<Team> americanLeague;
	vector<Team> nationalLeague;
	vector<string> worldCupWinners;
	ifstream teamsIn;
	ifstream leagueIn;
	ifstream winnersIn;
	
	teamsIn.open("Teams.txt");
	leagueIn.open("Leagues.txt");
	winnersIn.open("WorldSeriesWinners.txt");

	counter = 0;
	while (getline(teamsIn, input))
	{
		t.name = input;
		t.league = "";
		t.wins = 0;
		allTeams.push_back(t);
		counter ++;
	}
	
	counter = 0;
	while (getline(leagueIn, input))
	{
		allTeams[counter].league = input;
		counter ++;
	}

	while (getline(winnersIn, input))
	{
		worldCupWinners.push_back(input);
			for (int i = 0; i < allTeams.size(); i++){
				if (allTeams[i].name == input){
					allTeams[i].wins++;
				}
			}
	}
/*
	for(int i = 0; i < allTeams.size(); i++){
		cout << allTeams[i].name << " " << allTeams[i].league << " " << allTeams[i].wins << endl;
	}
*/

	for(int i = 0; i < allTeams.size(); i++){
		if(allTeams[i].league == "American League"){
			americanLeague.push_back(allTeams[i]);
		}else if(allTeams[i].league == "National League"){
			nationalLeague.push_back(allTeams[i]);
		}
	}
	
	std::sort(americanLeague.begin(), americanLeague.end(), sortCompare);
	
	std::sort(nationalLeague.begin(), nationalLeague.end(), sortCompare);

	cout << "American League" << endl;
	cout << "-----------------------------------------------" << endl;
	
	
	counter = 1903;
	for (int i = 0; i < americanLeague.size(); i++){
		cout << americanLeague[i].name << " ";
		for(int j = 0; j < worldCupWinners.size(); j++){
			if(worldCupWinners[j] == americanLeague[i].name){
				cout << counter << " ";
				counter ++;
			}
		}
		cout << endl;
	}
	
	cout << endl << endl;
	
	counter = 1903;
	for (int i = 0; i < nationalLeague.size(); i++){
		cout << nationalLeague[i].name << " ";
		while (getline(winnersIn, input)){
			if(input == nationalLeague[i].name){
				cout << counter << " ";
				counter++;
			}
		}
		cout << endl;
	}
	
	return 0;	
}

bool sortCompare(Team one, Team two) { 
	return one.wins < two.wins; 
}
