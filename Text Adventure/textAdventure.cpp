// Brady Chiles
// 11/5/17
// bmchiles@dmacc.edu

/*
This program is a text adventure. The player will start at a given location and move around to different locations to collect items in order to vanquish the darkness.
The items are explained at the beginning as well as where they need to go. There is a time limit of 66 moves. If they cannot collect the necessary item and reach the 
abyss location, then they lose. There is also a combat element that takes place in the jungle. The player must defeat a beast with a given item in order defeat the monster
and receive its item. There is a system, where the player must first get an item before getting another one. There are hints in the look dialogue.
*/


#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


struct Location{
	string name;
	vector<string> items;
};

//Global Variables
vector<Location> locations;
int daysLeft = 90;


class Player{
	private:
		int location;
		vector<string> inventory;
		
	public:
		void setLocation(int locationIn){location = locationIn;}
		int getLocation(){return location;}
		void openingDialogue();
		void checkDaysLeft();
		void locationDialogue(int);
		void choiceDialogue();
		void look(int);
		bool correctItemTest();
		bool correctItemTest(string);
		void correctItemDialogue();
		void jungleCombat();
		void abyssDialogue();
		char getDirection();
		void changeLocation(char);
		void displayInventory();
		void addItem();
		void useItem();
		void removeItem(string);
		void loadLocations();
};

//Dialogue that explains the premise of the game and adds some flavor
void Player::openingDialogue(){
	cout << "The abyss has been devouring the land at a hungering pace. You must stop it before it swallows your village." << endl 
	<< "You will need to gather 4 powerful relics to help you banish the darkness:" << endl 
	<< "An onyx cloak crafted from the same subastance of the abyss." << endl 
	<< "A radiant light to cast away the shadows." << endl
	<< "A lustrous elixr to fortify your strength." << endl 
	<< "Finally a noble blade to vanquish what awaits you in the very core of the abyss." << endl
	<< "You have 90 days to your relics and enter the abyss, or else you, your family, your village, and everything else you " << endl
	<< "hold dear will be claimed by the dark powers within." 
	<< endl << endl << endl << endl;
}

//Checks how many days are left for the player, displays them to the console.
//If the user has run out of days, a message to the player will be displayed and the game will end.
void Player::checkDaysLeft(){
	if(daysLeft > 0){
		cout << endl << "You have " << daysLeft << " until the abyss swallows everything you hold dear..." << endl << endl;
		daysLeft--;
	}else{
		cout << "You have not vanquished the evil within the abyss int time! It has spread across the land swallowing everything " << endl
		<< "in its path. Including you and your village. If only you had been a little quicker or perhaps a bit wiser... " << endl
		<< "Oh well, enjoy the darkness!" << endl;
		exit(0);
	}

}
//Brief information about the area that fires when they arrive
void Player::locationDialogue(int location){
	checkDaysLeft();
	
	switch(location){
		//Forest
		case 1 :
			cout << "Thick woods surround you on all sides. The broad leaves nearly blocking out the sun. " << endl
			<< "There is a shimmering pond nearby. Dragonflies flit accross the surface." << endl << endl;
			break;
		//Mountains
		case 2 :
			cout << "Rocky crags shoot out of the ground towards the heavens. Snow blankets their peaks. " << endl
			<< "Bones litter the ground. Hopefully you do not meet a similar fate." << endl << endl;
			break;
		//Beach
		case 3 :
			cout << "Foamy water laps against the sandy shore. The fresh scent of brine on the air. " << endl
			<< "Shells and seaweed are strewn along the beach. A mound of sand nearby." << endl << endl;
			break;
		//Cave
		case 4 :
			cout << "It is pitch black. You cannot even see your hand wave before your face. " << endl 
			<< "Shrieking can be heard deep within. A thump is heard near your feet." << endl << endl;
			break;
		//Tower
		case 5 :
			cout << "The tall stone tower brushes against the clouds. A crackling sound surrounds you. " << endl
			<< "Dark steel knockers hang from the door. The door shakes with an impact from within." << endl << endl;
			break;
		//Abyss
		case 6 :
			cout << "You have reached the abyss. Cries of agony and anguish pierce your ears. " << endl
			<< "You shudder at the though of entering. You must find the relics before it is too late!" << endl << endl;
			break;
		//Castle
		case 7 :
			cout << "Thick stone walls lay before you. Behind them lies the resplendant castle of your king. " << endl
			<< "A guard will need to open the gate. A shout can be heard from atop the wall." << endl << endl;
			break;
		//Swamp
		case 8 :
			cout << "A retched stench burns your nostrils. The ground sinks beneath your feet. " << endl
			<< "The surface of the murky water shudders as something makes its way towards you." << endl << endl;
			break;
		//Jungle
		case 9 :
			cout << "The cacophany of sound is deafening. The air hangs heavy with moisture. " << endl
			<< "The brush cracks as something crashes along the jungle floor." << endl << endl;
			jungleCombat();
			break;
		//Lake
		case 10 :
			cout << "A boat rocks against the dock. Moss and slime drip from its sides. " << endl
			<< "A long pole hangs off the side. There looks to be a large box on the bottom." << endl << endl;
			break;
		//Farm
		case 11 :
			cout << "Rows and rows of corn and wheat, and beans. A cow moos in the distance. " << endl
			<< "The swishing of blades can be heard nearby. It's harvest season." << endl << endl;
			break;
		//Village
		case 12 :
			cout << "Home sweet home. Your family surrounds you with their love. " << endl
			<< "Unfortunately if you don't get a move on, you won't have a family left!" << endl << endl;
			break;
		//Coven
		case 13 :
			cout << "Chanting can be heard from within the animal skin tents. Light illuminating figures inside. " << endl
			<< "As you walk closer, you begin to question the material of which the tents are made..." << endl << endl;
			break;
		//Mine
		case 14 :
			cout << "The clanging of metal against stone can be heard inside. Flickering light dances across the walls. " << endl
			<< "The screeching of wheels of draws near, a blinding light fills your vision." << endl << endl;
			break;
		//Hills
		case 15 :
			cout << "Rolling green hills stretch off in all directions. Fuzzy white and black sheep can be seen grazing. " << endl
			<< "Coming over the hill you see a shephards hook bobbing, followed by a hooded figure." << endl << endl;
			break;
		//Portal
		case 16 :
			cout << "A swirling purple portal stands before you. There are corpses littered all the way up the steps. " << endl
			<< "It is impossible to know where the portal may lead..." << endl << endl;
			break;
	}
	
	if(correctItemTest()){
		cout << "You have an item in your inventory that can be used here..." << endl << endl;
	}
}

//Dialogue that fires at each location after its initial dialogue.
//This will lead off to additional dialogues depending on the choice.
void Player::choiceDialogue(){
	char choice;
	
	if(location != 9){
		if(correctItemTest()){
			do{
				cout << "What would you like to do?" << endl
					 << "[U]se Item" << endl
					 << "[L]ook" << endl
					 << "[M]ove" << endl
					 << "[D]isplay Inventory" << endl << endl;
				 cin >> choice;
				 
				 if(choice == 'U' || choice == 'u'){
				 	useItem();
				 }else if(choice == 'L' || choice == 'l'){
				 	look(location);
				 	choiceDialogue();
				 	
				 }else if(choice == 'M' || choice == 'm'){
				 	char direction = getDirection();
				 	changeLocation(direction);
				 	choiceDialogue();
				 	
				 }else if(choice == 'D' || choice == 'd'){
				 	displayInventory();
				 	choiceDialogue();
				 	
				 }else{
				 	choice = 'v'; //Sets to not valid
				 	cout << "That is not a valid command!" << endl << endl;
				 }
			}while(choice == 'v');
			
		}else{
			do{
				cout << "What would you like to do?" << endl
				 << "[L]ook" << endl
				 << "[M]ove" << endl
				 << "[D]isplay Inventory" << endl << endl;
				 cin >> choice;
				 
				 if(choice == 'L' || choice == 'l'){
				 	look(location);
				 	choiceDialogue();
				 	
				 }else if(choice == 'M' || choice == 'm'){
				 	char direction = getDirection();
				 	changeLocation(direction);
				 	choiceDialogue();
				 	
				 }else if(choice == 'D' || choice == 'd'){
				 	displayInventory();
				 	choiceDialogue();
				 	
				 }else{
				 	choice = 'v'; //Sets to not valid
				 	cout << "That is not a valid command!" << endl << endl;
				 }
				 
			}while(choice == 'v');
		}
	}
}

//More detailed information about the area.
//Fires if look is chosen from the choiceDialogue.
void Player::look(int location){
	cout << endl;
		
	switch(location){
		//Forest
		case 1 :
			cout << "You approach the pond. A faint glow can be seen coming up from the bottom. You can barely make out its long pointed shape. " << endl
			<< "Too bad you don't have anything to fish it out. Perhaps a rope or something." << endl << endl;
			break;
		//Mountains
		case 2 :
			cout << "You fish through the remains, and find a pack marked with a name. Felix H. Monnicker. Perhaps you can return something " << endl
			<< "to his family. Most of the bones are crushed from the elements. The skull is pretty intact though..." << endl << endl;
			addItem();
			break;
		//Beach
		case 3 :
			cout << "You use your hands to dig through the mound of sand. Your fingers brush against something hard and jagged. " << endl
			<< "You grab and pull, revealing a large hollow conch! Perhaps you can use this to carry something..." << endl << endl;
			addItem();
			break;
		//Cave
		case 4 :
			cout << "You bend down and feel around the floor as best you can. Your hand wraps around a long wooden handle. " << endl 
			<< "You carry your prize out into the sun. Its a pickaxe! Now you just have to find something to unearth." << endl << endl;
			addItem();
			break;
		//Tower
		case 5 :
			cout << "You give the heavy iron knockers a toss. The door creaks open. A pair of eyes hidden behind an enormous beard peer out. " << endl
			<< "He raises his eyebrows, eyeing your sack. You rummage through but nothing interests this mysterious wizard. Perhaps something " << endl
			<< "magical he can use for his potions." << endl << endl;
			break;
		//Abyss
		case 6 :
			cout << "There is nothing else too see. You better hurry and find those relics! " << endl << endl;
			break;
		//Castle
		case 7 :
			cout << "A guard peers down from the battlements. He shouts down to you, but most of the words are lost in the wind. " << endl
			<< "Through a series of hand signals and undulations, you gather that they are too terrified of a monster that lurks about. " << endl
			<< "Perhaps if you slayed it..." << endl << endl;
			break;
		//Swamp
		case 8 :
			cout << "You don't bother to stick around and find out what lays below the water's surface. " << endl
			<< "You turn around and book it out as quick as you can." << endl << endl;
			changeLocation('E');
			break;
		//Jungle
		case 9 :
			cout << "An enormous beast with dripping fangs erupts from the brush, pinning you to the ground. You wrestle the beast, " << endl
			<< "keeping its jaws from clamping on your face. You finally get a hand free and punch it on the nose, sending it " << endl
			<< "sprawling back. It begins to circle you." << endl << endl;
			break;
		//Lake
		case 10 :
			cout << "The box looks quite weathered, and with a quick shake you can tell there are items inside. A sturdy metal lock is barring" << endl
			<< " your way. You try to break the latch with rocks you find along the shore to no avail, you need something bigger, and wider..." << endl << endl;
			break;
		//Farm
		case 11 :
			cout << "You wander towards the farmhouse nestled in between the fields. A small sign out front has the words 'Monicker Farm' " << endl
			<< "painted on it. You remember hearing that name before, something about them losing their son last winter. " << endl
			<< "Perhaps if you were to find him, they would be willing to help you..." << endl << endl;
			break;
		//Village
		case 12 :
			cout << "There is nothing else they can do for you. You better get going! " << endl << endl;
			break;
		//Coven
		case 13 :
			cout << "The chanting suddenly stops, the figures shuffle inside, the front flap swings open. An old crone, with long, white hair " << endl 
			<< "creeps towards you. She fixes you with her one good eye. You try to explain your plight. She returns to the tent and " << endl
			<< "returns with a small hard lump. She wants another one..." << endl << endl;
			break;
		//Mine
		case 14 :
			cout << "A large rippling man appears pushing a mining cart with a headlight. He explains that he can't get any of his workers " << endl
			<< "to stay and needs any help he can get. You offer your services, in exchange for some pay. But wait, you don't "
			<< "even have any tools. If only you had a pickaxe..." << endl << endl;
			break;
		//Hills
		case 15 :
			cout << "The humble shephard smiles when he sees you. He offers you a drink from his waterskin. You lay beneath the single shady " << endl
			<< "tree speaking of journeys. He shows you a small hard lump, explaining its magical properties. He would be willing " << endl
			<< "to part with it for something of equal value, a jewel perhaps..." << endl << endl;
			break;
		//Portal
		case 16 :
			cout << "You walk the steps towards the swirling mass, being careful not to trip over the bodies. A fine dust coats everything. " << endl
			<< "You see a large pile of the dust, it sparkles of its own accors. If only you had something to hold it..." << endl << endl;
			break;
	}
		
	if(location != 9){
		choiceDialogue();
	}
}

//Tests to see if the player has the correct item in their inventory to use a ta given location
bool Player::correctItemTest(){
	bool correctItem = false;
	
	//The abyss
	if(location == 6){
		bool blade = false;
		bool elixr = false;
		bool cloak = false;
		bool light = false;
		
		for(int i = 0; i < inventory.size(); i++){
			if(inventory[i] == "Noble Blade"){
				blade = true;
			}else if(inventory[i] == "Lustrous Elixr"){
				elixr = true;
			}else if(inventory[i] == "Onyx Cloak"){
				cloak = true;
			}else if(inventory[i] == "Radiant Light"){
				light = true;
			}
		}
		if(blade == true || elixr == true || cloak == true || light == true){
//			abyssDialogue();
		}
	}
		
	//Forest
	if(location == 1){
		for(int i = 0; i < inventory.size(); i++){
			if(inventory[i] == "Rope with Hook"){
				correctItem = true;
			}
		}
	//Tower
	}else if(location == 5){
		for(int i = 0; i < inventory.size(); i++){
			if(inventory[i] == "Mana Dust"){
				correctItem = true;
			}
		}
	//Castle
	}else if(location == 7){
		for(int i = 0; i < inventory.size(); i++){
			if(inventory[i] == "Saber Tooth"){
				correctItem = true;
			}
		}
	//Jungle
	}else if(location == 9){
		for(int i = 0; i < inventory.size(); i++){
			if(inventory[i] == "Noble Blade"){
				correctItem = true;
			}
		}
	//Lake
	}else if(location == 10){
		for(int i = 0; i < inventory.size(); i++){
			if(inventory[i] == "Shovel"){
				correctItem = true;
			}
		}
	//Farm
	}else if(location == 11){
		for(int i = 0; i < inventory.size(); i++){
			if(inventory[i] == "Skull"){
				correctItem = true;
			}
		}
	//Coven
	}else if(location == 13){
		for(int i = 0; i < inventory.size(); i++){
			if(inventory[i] == "Bezoar"){
				correctItem = true;
			}
		}
	//Mine
	}else if(location == 14){
		for(int i = 0; i < inventory.size(); i++){
			if(inventory[i] == "Pickaxe"){
				correctItem = true;
			}
		}
	//Hills
	}else if(location == 15){
		for(int i = 0; i < inventory.size(); i++){
			if(inventory[i] == "Glimmering Gem"){
				correctItem = true;
			}
		}
	//Portal
	}else if(location == 16){
		for(int i = 0; i < inventory.size(); i++){
			if(inventory[i] == "Conch"){
				correctItem = true;
			}
		}
	}
	
	if(correctItem == true){
		return true;
	}else{
		return false;
	}
}

//Correct item test, taking a string representing an item as an argument
//Same functionality as the above function
bool Player::correctItemTest(string item){
	bool correctItem = false;
	
	//Forest
	if(location == 1){
		if(item == "Rope with Hook"){
			correctItem = true;
		}
	//Tower
	}else if(location == 5){
		if(item == "Mana Dust"){
			correctItem = true;
		}
	//Castle
	}else if(location == 7){
		if(item == "Saber Tooth"){
			correctItem = true;
		}
	//Lake
	}else if(location == 10){
		if(item == "Shovel"){
			correctItem = true;
		}
	//Farm
	}else if(location == 11){
		if(item == "Skull"){
			correctItem = true;
		}
	//Coven
	}else if(location == 13){
		if(item == "Bezoar"){
			correctItem = true;
		}
	//Mine
	}else if(location == 14){
		if(item == "Pickaxe"){
			correctItem = true;
		}
	//Hills
	}else if(location == 15){
		if(item == "Glimmering Gem"){
			correctItem = true;
		}
	//Portal
	}else if(location == 16){
		if(item == "Conch"){
			correctItem = true;
		}
	}
	
	if(correctItem == true){
//		correctItemLookDialogue();
		return true;
	}else{
		return false;
	}
}

//Dialogue that fires if the player has the correct item to pick up the item stored at this location
void Player::correctItemDialogue(){
	switch(location){
		//Forest
		case 1 :
			cout << "With the help of your trusty rope you are abke to get a hold of the thing at the bottom of the lake." << endl
			<< "As you pull it up onto the shore, you are elated to see that it is a sword. And guessing by the eerie glow, a magic one." << endl
			<< "You have found the Noble Blade! You are one step closer to vanquishing the abyss!"<< endl;
			addItem();
			break;
		//Tower
		case 5 :
			cout << "You hand the enigmatic qizard the conch full of dust. His face lights up and he ushers you inside. " << endl
			<< "He leads you over to his solar. He heads straight for a glowing vial. He quickly explains that the powers " << endl
			<< "rendered from this potion will protect you from the darkest of magics. You have found the Lustrous Elixr! " << endl
			<< "You are one step closer to vanquishing the abyss!" << endl;
			addItem();
			break;
		//Castle
		case 7 :
			cout << "You lift the might Beast's fang into the air. Cheering erupts over the walls. The gate quickly rises, a horde " << endl
			<< "of cheering peasants and guards pours out to meet you. You are quickly whisked away to the castle, where the court" << endl
			<< " mage meets you, a bolt of cloth, dark as nnight draped over his arms. This is your reward." << endl 
			<< "You have found the Onyx Cloak! You are one step closer to vanquishing the abyss."<< endl;
			addItem();
			break;
		//Jungle
		case 9 :
			cout << "You can feel the feral eyes upon you. The mighty Beast erupts from the trees, but with sword in hand you " << endl
			<< "swing with one wide arc, severing its head from its shoulders. Not fond of carrying a severed head around with" << endl
			<< " you, you yank one of its might fangs from its jaws, a worthy trophy for any hall." << endl << endl;
			addItem();
			break;
		//Lake
		case 10 :
			cout << "With the Monnicker shovel in hand you strike the latch with force, popping the lid wide open. Inside lies" << endl
			<< " a long coil of rope with a hook attached. Perhaps you can use this to retrieve something out of reach." << endl << endl;
			addItem();
			break;
		//Farm
		case 11 :
			cout << "You somberly walk towards the house. The mother rocks in her chair on the porch. As you reach into your pack, " << endl
			<< "she begins to wail. You hand her the skull of her son. The father has come from the house and nods to you with " << endl
			<< "respect. He leads you to the tool shed behind the barn and tells you to take your pick." << endl << endl;
			addItem();
			break;
		//Coven
		case 13 :
			cout << "The witches are sitting around the fire. The eldest rises as they see you approach. You fish in your pack for " << endl
			<< "the small hard lump. The crone breaks a toothless grin, patting you on the shoulder. She turns back to the tents" << endl
			<< " and returns a moment later with a bauble that shines with the light of the sun." << endl 
			<< "You have found the Radiant Light! You are one step closer to vanquishing the abyss!" << endl;
			addItem();
			break;
		//Mine
		case 14 :
			cout << "The foreman is delighted to see you, especially since you have a pickaxe hoisted over your shoulder." << endl
			<< " You get right to work in the mines. The work is hard, but the pay is decent. One day you stumble across " << endl
			<< "a radiant gem beneath the rock. You quietly pick it out and sneak it into your pack." << endl << endl;
			addItem();
			break;
		//Hills
		case 15 :
			cout << "The shephard beams from ear to ear as you pull the gem out of your pack. He hoists it into the air " << endl
			<< "spinning it around. He eagerly tosses you the small dark lump, and runs off over the hills to his flock." << endl << endl;
			addItem();
			break;
		//Portal
		case 16 :
			cout << "You scoop up a mound of the glittering dust with your trusty conch. The shell glows from within with " << endl
			<< "the power of the dust. Perhaps a wizard or mage would be interested in using this..." << endl << endl;
			addItem();
			break;
	}
	choiceDialogue();
}

//The combat element inside of the jungle. The playe rmust fight the best.
//If they have the sword they do more damage and can beat the best, if not, then they must run from the best when their health gets lowl.
void Player::jungleCombat(){
	char combatChoice;
	int beastHealth = 150;
	int playerHealth = 100;
	int beastDamage = 0;
	int playerDamage = 0;
	int rand();
	bool sword = correctItemTest();
	
	
	look(location);
	cout << "You better make quick work of this monster before it does the same to you!" << endl << endl;
	
	do{
		cout << "Beast Health: " << beastHealth << endl
		<< "Player Health: " << playerHealth << endl << endl;
		
		cout << "What would you like to do?" << endl
		<< "[A]ttack" << endl
		<< "[D]odge" << endl
		<< "[R]un" << endl << endl;
		cin >> combatChoice;
		
		if(combatChoice == 'a' || combatChoice == 'A'){
			beastDamage = (rand() % 20) + 10;
			if(sword){
				playerDamage = (rand() % 30) + 15;
			}else{
				playerDamage = (rand() % 10) + 1;	
			}
			
			playerHealth = playerHealth - beastDamage;
			beastHealth = beastHealth - playerDamage;
			combatChoice = 'v';
			
			if(beastHealth <= 0){
				correctItemDialogue();
			}
			if(playerHealth <= 0){
				cout << endl << "The beast deals you grievous wounds. You better get out of here before it finishes you off." << endl << endl;
				location = 10;
				locationDialogue(location);
				choiceDialogue();
			}
			
		}else if(combatChoice == 'd' || combatChoice == 'D'){
			cout << endl << "You dodge the incoming blow by inches, taking no damage." << endl << endl;
			combatChoice = 'v';
			
		}else if(combatChoice == 'r' || combatChoice == 'R'){
			cout << endl << "You run from the ferocious beast. I dont blame you! You turn tail and run through the trees until " << endl
			<< "you leave that wretched jungle far behind." << endl << endl;
			location = 10;
			locationDialogue(location);
			choiceDialogue();
		}else{
			combatChoice = 'v';
			cout << endl << "That is not a valid command!" << endl << endl;
		}
	}while(combatChoice == 'v');

}

//Dialogue that fires at the end after the player has gathered all of the items they need
void Player::abyssDialogue(){
	//End game dialogue
	exit(0);
}

//Will fire from the choice dialogue if the player wants to move.
//Will feed the direction into changeLocation().
char Player::getDirection(){
	char direction;
	
	cout << endl << "What direction would you like to go?" << endl
	<< " [N]orth, [S]outh, [E]ast, or [W]est" << endl << endl;
	cin >> direction;
	
	return direction;
}

//Changes location based on the direction chosen by the player.
void Player::changeLocation(char direction){
	int location = getLocation();
	
	if(direction == 'N' || direction == 'n'){
		int locationMoverNorth = 4;
		int locationMoverNorthWrap = 12;
		if(location != 1 && location != 2 && location != 3 && location != 4){
			location = location - locationMoverNorth;
		}else{
			location = location + locationMoverNorthWrap;
		}
	}else if(direction == 'E' || direction == 'e'){
		int locationMoverEast = 1;
		int locationMoverEastWrap = 3;
		if(location != 4 && location != 8 && location != 12 && location != 16){
			location = location + locationMoverEast;
		}else{
			location = location - locationMoverEastWrap;
		}
	}else if(direction == 'S' || direction == 's'){
		int locationMoverSouth = 4;
		int locationMoverSouthWrap = 12;
		if(location != 13 && location != 14 && location != 15 && location != 16){
			location = location + locationMoverSouth;
		}else{
			location = location - locationMoverSouthWrap;
		}
	}else if(direction == 'W' || direction == 'w'){
		int locationMoverWest = 1;
		int locationMoverWestWrap = 3;
		if(location != 1 && location != 5 && location != 9 && location != 13){
			location = location - locationMoverWest;
		}else{
			location = location + locationMoverWestWrap;
		}
	}else{
		
	}
	setLocation(location);
	locationDialogue(location);
}

//Display Inventory to console
void Player::displayInventory(){
	if(inventory.size() == 0){
		cout << endl << "You do not have any items in your inventory!" << endl << endl;
	}else{
		cout << endl << "Inventory" << endl
		<< "------------" << endl << endl;
		for(int i = 0; i < inventory.size(); i++){
			cout << inventory[i] << endl;
		}
		cout << endl << endl;
	}
}


//Add the item from the location to the player inventory
void Player::addItem(){
	
	if(locations[location-1].items.size() > 0){
		string item = locations[location-1].items[0];
		locations[location-1].items.erase(locations[location-1].items.begin());
		
		inventory.push_back(item);
		cout << item << " has been added to your inventory!" << endl << endl;	
	}
}

//When the player choses to use an item at a given location (they must have the correct item first)
//SHows the user their inventory and has them choose an item.
void Player::useItem(){
	int itemChoice;
	string item;
	bool correctItem = false;
	
	do{
		cout << "What item would you like to use?" << endl;
		for(int i = 0; i < inventory.size(); i++){
			cout << i + 1 << ".  " << inventory[i] << endl;
		}
		cout << "0.  Exit" << endl << endl;
		cin >> itemChoice;
		item = inventory[itemChoice-1];
		
		if(itemChoice == 0){
			break;
		}else{	
			if(correctItemTest(item)){
				correctItem = true;
				removeItem(item);
				correctItemDialogue();
			}else{
				cout << "That isn't the correct item. Try again." << endl << endl;
			}
		}
	}while(correctItem == false);
}

//Removes the item the player uses from their inventory.
void Player::removeItem(string item){
	cout << item << " has been removed from your inventory." << endl << endl;
	inventory.erase(std::remove(inventory.begin(), inventory.end(), item), inventory.end());
}

//Loads all of the locations into a locations vector
void Player::loadLocations(){
	Location forest, mountains, beach, cave, tower, abyss, castle, swamp, jungle, lake, farm, village, coven, mine, hills, portal;
	
	forest.name = "Forest";
	mountains.name = "Mountains";
	beach.name = "Beach";
	cave.name = "Cave";
	tower.name = "Tower";
	abyss.name = "Abyss";
	castle.name = "Castle";
	swamp.name = "Swamp";
	jungle.name = "Jungle";
	lake.name = "Lake";
	farm.name = "Farm";
	village.name = "Village";
	coven.name = "Coven";
	mine.name = "Mine";
	hills.name = "Hills";
	portal.name = "Portal";
	
	forest.items.push_back("Noble Blade");
	mountains.items.push_back("Skull");
	beach.items.push_back("Conch Shell");
	cave.items.push_back("Pickaxe");
	tower.items.push_back("Lustrous Elixr");
	castle.items.push_back("Onyx Cloak");
	swamp.items.push_back("Gator Hide");
	jungle.items.push_back("Saber Tooth");
	lake.items.push_back("Rope with Hook");
	farm.items.push_back("Shovel");
	coven.items.push_back("Radient Light");
	mine.items.push_back("Shimmering Gem");
	hills.items.push_back("Bezoar");
	portal.items.push_back("Mana Dust");
	
	locations.push_back(forest);
	locations.push_back(mountains);
	locations.push_back(beach);
	locations.push_back(cave);
	locations.push_back(tower);
	locations.push_back(abyss);
	locations.push_back(castle);
	locations.push_back(swamp);
	locations.push_back(jungle);
	locations.push_back(lake);
	locations.push_back(farm);
	locations.push_back(village);
	locations.push_back(coven);
	locations.push_back(mine);
	locations.push_back(hills);
	locations.push_back(portal);
}


int main()
{	
	Player playerOne;
		
	playerOne.loadLocations();
	playerOne.openingDialogue();
	playerOne.setLocation(12);
	playerOne.locationDialogue(playerOne.getLocation());
	playerOne.choiceDialogue();
	
	return 0;
}
