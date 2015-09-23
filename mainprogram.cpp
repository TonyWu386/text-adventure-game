/*
File name: mainprogram.cpp
Date Created: Jan. 12 2013
Date last modified: Feb. 8 2013

Dependencies: help.h, quote.h

--------------------------------------------------------------------------------------
NOTICE: THIS IS A COMPLETED BUT ABANDONED PROJECT FROM EARLY 2013. IT IS OLD SOFTWARE
THAT HAS NOT BEEN UPDATED SINCE. IT IS NOT AN UP TO DATE REFLECTION OF ITS DEVELOPERS.
--------------------------------------------------------------------------------------

A product of the "Generic Game Studios" group (2013)

Lead Developer: Tony Wu (Xiangbo)
Email: xb.wu@mail.utoronto.ca

Additional developers: Sean Lo, Joshua Chu

License: GNU GPL v2.0

Copyright (c) 2013-2015 [Tony Wu], All Right Reserved
*/

#define WKEY          77
#define AKEY          61
#define SKEY          73
#define DKEY          64

#include <iostream>
#include <conio.h>
#include <fstream>
#include <string.h>
#include <windows.h>
#include <time.h>

#include "quote.h"	//For quotes feature
#include "help.h" //For help file feature

using namespace std;

int howmuchcost (string names[31], string itemnum, int buySell) {

    //A function for calculating the cost of items

	int cost;
	//Used names[31] in the event the name of the items change
	if (itemnum == names[0]) {
        cost = 25/buySell;
    } //health potion
	if (itemnum == names[1]) {
        cost = 60/buySell;
    } //G. health potion
	if (itemnum == names[2]) {
        cost = 150/buySell;
    } //Elixir
	if (itemnum == names[3]) {
        cost = 100/buySell;
    } //Berserk potion
	if (itemnum == names[4]) {
        cost = 100/buySell;
    } //Accuracy potion
	if (itemnum == names[5]) {
        cost = 100/buySell;
    } //spell potion
	if (itemnum == names[6]) {
        cost = 100/buySell;
    } //flashbang
	if (itemnum == names[7]) {
        cost = 100/buySell;
    } //he grenade
	if (itemnum == names[8]) {
        cost = 75/buySell;
    }
	if (itemnum == names[9]) {
        cost = 100/buySell;
    }
	if (itemnum == names[10]) {
        cost = 60/buySell;
    }
	if (itemnum == names[11]) {
        cost = 100/buySell;
    }
	if ((itemnum == names[12]) || (itemnum == names[16]) || (itemnum == names[23]) || (itemnum == names[27])) {
        cost = 25;
    }
	if ((itemnum == names[13]) || (itemnum == names[17]) || (itemnum == names[24]) || (itemnum == names[28])) {
        cost = 75;
    }
	if ((itemnum == names[14]) || (itemnum == names[18]) || (itemnum == names[25]) || (itemnum == names[29])){
        cost = 150;
	}
	if ((itemnum == names[15]) || (itemnum == names[19]) || (itemnum == names[20]) || (itemnum == names[21]) ||
     (itemnum == names[22]) || (itemnum == names[26]) || (itemnum == names[30])) {
		cost = 300;
    }

    return cost;
    //End of function
}

string monstergen (char command) {

    //A function for generating monsters

    srand(time(NULL)); //Generates a seed.

    string retmonster;
    int enemytype = 0;

    int rNum; //Random number

    rNum = rand()%10;

    //Forest area
    if (command == '=') {
        if (rNum < 7) {
            enemytype = 3;
        }
        else
        {
            if (rNum < 9) {
                enemytype = 1;
            } else {
                enemytype = 4;
            }
        }
    }

    // Cave
    if (command == '^') {
        if (rNum < 4) {
            enemytype = 1;
        } else if (rNum < 8) {
            enemytype = 2;
        } else {
        enemytype = 4;
        }
    }

    //Plains
    if (command == '.') {
        if (rNum < 5) {
            enemytype = 4;
        } else if (rNum < 7) {
            enemytype = 1;
        } else if (rNum < 9) {
            enemytype = 2;
        } else {
            enemytype = 4;
        }
    }

    //Dungeon
    if (command == 'n') {
        if (rNum <5) {
            enemytype = 2;
        } else if (rNum < 7) {
            enemytype = 1;
        } else if (rNum < 8) {
            enemytype = 3;
        } else if (rNum < 9) {
            enemytype = 5;
        } else {
            enemytype = 4;
        }
    }

    //Mountain
    if (command == 'M') {
        if (rNum < 6) {
            enemytype = 5;
        } else {
            if (rNum < 8) {
                enemytype = 2;
            } else {
                if (rNum < 9) {
                    enemytype = 1;
                } else {
                    enemytype = 4;
                }
            }
        }
    }

    switch (enemytype)
    {
        case 1: retmonster = "goblin";
        break;
        case 2: retmonster = "orc";
        break;
        case 3: retmonster = "elf";
        break;
        case 4: retmonster = "human";
        break;
        case 5: retmonster = "giant";
        break;
        case 6: retmonster = "dragon"; //Currently not in use but stick this here for when we need it
    }

    return retmonster;

    //End of function
}

int buffs (int &bonus, int &stat, int &def, string name)
{

    //Function for spell and berserk potion. Accuracy potion is a bit different though

	if (bonus > 0)	//If the player uses another potion while one is still active
	{
		stat = stat - bonus;
		def = def + 2;
	}
	bonus = rand()% 3 + 2;	//+ 2 - 5 att, - 2 def
	cout <<"\nYou've gained " << bonus <<" " << name <<"\n";
	cout <<"at the cost of 2 defense\n";
	bonus ++;	//Offset a little bit since subtraction comes at the beginning of battle
	stat = stat + bonus;
	def = def - 2;
	if (def < 0) {
		def = 0;
	}

    return bonus;
}

//MAIN PROGRAM BELOW

int main () {

    char mainmapmatrix[14][12], dun1matrix[5][7], dun2matrix[5][7], dun3matrix[5][7], titlematrix[80][11], tertype, keystroke;
    int locatex = 5, locatey = 5, map = 0, monchance = 0, plvl = 1, pHP = 0, pATT = 0, pDEF = 0, pACC = 0, pMAGIC = 0, uCommand = 0, pExp = 0;
    int elvl, eHP, eATT, eDEF, eACC, eMAGIC;
    int monlimit = 2, moncounter = 0;
    bool didbattlehappen = false;
    int pMP, cpMP, eMP, ceMP; //Mana points

    int cpHP,ceHP,cpACC,ceACC,pMlvl;

    int uFormat;  //For formatting purposes

    int pCritChance; //player's chance to critical strike for 50% additional damage

    int bCommand [5];

	int pHits = 0; //Counts the number of attacks the player has made
	bool pBerserk = false; //Holds whether the player is going to berserk on his next attack (only for Berserkers)

    int pRadiantEnd = 0; //Counts the number of turns the Radiance buff will last for
    bool pRadiant = false; //Whether the player has the Radiance buff or not

    int pSpellCD [11]; //Spell cooldown timers
    int pSpellMCD [11]; //The actual length of the cooldowns, stored in an array
    int pSpellCost [11]; //The mana costs of the spells, store in an array
    int pSpellMlvl [11]; //The required level to cast that spell
    bool pSpellAvail [11]; //Whether a spell is available or not

    bool eBoss = false; //Whether the current enemy is a boss type enemy

    int pFlee; //The chance for the player to run away. Its higher the weaker the enemy is

    //Timers and checks for confusion and poison

    bool pConf = false;
    int pConfCure = 0;

    bool eConf = false;
    int eConfCure = 0;

    bool pPois = false;
    int pPoisCure = 0;

    bool ePois = false;
    int ePoisCure = 0;

    bool pCold = false;
    int pColdCure = 0;

    bool eCold = false;
    int eColdCure = 0;

    int eNumBoss = 0; //The number of bosses encountered thus far

    bool d1Boss = false; //Whether the respective dungeon bosses have been defeated yet
    bool d2Boss = false;
    bool d3Boss = false;
    bool finalBoss = false;

    //For temporarily storing the random number inside a variable to compare against in battle
    int uAcc;

    bool uPTurn;

    bool pMGuard = false; //Whether the Magic Guard buff is on

    bool pMHide = false; //Whether the Hide buff is on

    int shopTimer = 3;	//Refreshes every 3 monster battles
    int shopItems[5];	//List of 5 available shop items
   	int gold = 0; //Currency

    int pMHideEnd = 0;

    int tCount = 0;    //Counting the number of turns in battle

    string pWep = "none";  //For calling weapons but change when necessary
    string eWep;
    string eClass = "default";
    string eType = "default";
    string pClass = "default";
    string pName = "";
    int eLevel = 1;

    string victor;    //The victor of the battle: stored in a variable

    int uTurn; //UCommand is

    bool uCheck = false; //if the parameters are acceptable or not

   	char choice;	//User input
	int monsterType;	//Determines what the player kills and collects. If you want, this can be just a local variable (within the block of code)

	int questType = 0;	//0 = none, 1 = kill, 2 = collect
	int quantity = 0;	//The number of items required to complete the quest
	int part;	//The name of the part of monster. Only used for collecting. Just like the monsterType variable, it can just be local
	int qTrack = 0;	//For keeping track of the items gained
	string partName = ".";	//The name of the part. Strictly for comical purposes
	string monster = "None";	//The name of the monster

	ifstream load; //This will be the method of saving and loading. Note that it should say ifstream load, not ifstream save
	ofstream save;	//Writing out to a text file

    string comd, montype;

    srand(time(NULL));

    ifstream titlepic;
    titlepic.open ("Title.txt");

    ifstream mainmapfile;
    mainmapfile.open ("OverworldMap.txt");

    ifstream dun1mapfile;
    dun1mapfile.open ("Dungeon1Map.txt");

    ifstream dun2mapfile;
    dun2mapfile.open ("Dungeon2Map.txt");

    ifstream dun3mapfile;
    dun3mapfile.open ("Dungeon3Map.txt");

    for (int countery = 0; countery < 12; countery++) {             //intakes overworld map
        for (int counterx = 0; counterx < 14; counterx++) {
            mainmapfile >> mainmapmatrix[counterx][countery];
        }
    }

    for (int countery = 0; countery < 7; countery++) {
        for (int counterx = 0; counterx < 5; counterx++) {
            dun1mapfile >> dun1matrix[counterx][countery];
        }
    }

    for (int countery = 0; countery < 7; countery++) {
        for (int counterx = 0; counterx < 5; counterx++) {
            dun2mapfile >> dun2matrix[counterx][countery];
        }
    }

    for (int countery = 0; countery < 7; countery++) {
        for (int counterx = 0; counterx < 5; counterx++) {
            dun3mapfile >> dun3matrix[counterx][countery];
        }
    }

    for (int countery = 0; countery < 11; countery++) {
        for (int counterx = 0; counterx < 80; counterx++) {
            titlepic >> titlematrix[counterx][countery];
        }
    }

    //Loading and Saving System

	int item [31];	//Quantity of items
	char inventorySelect;	//Lists the items/weapons that are more than 0
	char invCommand;
	int tempWeapon;
	int findItem = -1;	//Finds the items selected
	int select;	//User input for selecting items
	int pwepType = -1;
	bool fBonus = false;	//firestorm and fireball + 20%
	bool mBonus = false;	//magic missile and moonfall + 20%
	bool iBonus = false;	//ice bolts and icestorm + 20%
	bool vBonus = false;	//vampirism bonus
	bool hBonus = false; //heal bonus
	bool sBonus = false;	//free spell bonus - 10%
	string itemName [31];	//Names of the items

	int bpBonus = 0; //Berserk potion bonus
	int apBonus = 0; //Accuracy potion bonus
	int spBonus = 0; //Spell potion
	int eBlind = 0;	//Debuff for enemy
	int iCrit = 0;	//Increase critical damage
	int sDuration = 0; //Storm potion duration
	bool eStun = false;	//Stun for 1 turn if true

    //Prints out game introduction

    cout << endl;
    cout << "                          Generic Game Studios Present" << endl << endl;
    Sleep(200);
    cout << "                      A Generic RPG powered by CryEngine3(TM)" << endl << endl;
    Sleep(200);

    cout << endl;

    for (int countery = 0; countery < 11; countery++) {
         for (int counterx = 0; counterx < 80; counterx++) {
             cout << titlematrix[counterx][countery];
         }
         Sleep(200);
         cout << endl;
    }

    cout << endl << endl;
    Sleep(200);

    cout <<"Load game (y/n)?\n";	//Will get information from text file if confirmed
    do
    {
        uCommand = getch();
        uCommand = toupper(uCommand);
    } while ((uCommand != 'Y') && (uCommand != 'N'));

    load.open("Load.txt");

    //Loads the item and weapon names and quantity
    for(int counter = 0; counter < 31; counter++)
    {
        load >> item[counter];
        getline (load, itemName[counter]);
    }	//DO NOT FORGET THE FOR LOOP TO RETURN ALL ITEMS TO 0.

    if (uCommand == 'Y')	//Starts here
    {
        getline(load, pName);
        load >> pClass >> plvl >> gold >> pExp >> questType >> monster >> partName >> quantity >> qTrack >> pHP >> cpHP >> pMP >>
        cpMP >> pATT >> pMAGIC >> pDEF >> pACC >> pCritChance >> d1Boss >> d2Boss >> d3Boss >> moncounter;
    }
    else
    {
        for (int counter = 0; counter < 31; counter++)
        {
            item[counter] = 0;
        }

        cout << "Please enter your name: ";
        cin >> pName;
        cout << endl;

        do {  //This part of the program is gathering stats for the battle
            cout << "   What class do you want to be? " << endl << endl;
            cout << "     (1) Rogue " << endl;
            cout << "     (2) Mage " << endl;
            cout << "     (3) Berserker " << endl;
            cout << "     (4) Paladin " << endl;
            uCommand = getch();
            cout << endl;
            uCheck = true;
            switch (uCommand) {
                case 49:
                    pHP = 40;
                    pMP = 4;
                    pATT = 6;
                    pACC = 80;
                    pDEF = 1;
                    pMAGIC = 2;
                    pClass = "Rogue";
                    break;
                case 50:
                    pHP = 35;
                    pMP = 10;
                    pATT = 3;
                    pACC = 65;
                    pDEF = 0;
                    pMAGIC = 4;
                    pClass = "Mage";
                    break;
                case 51:
                    pHP = 45;
                    pMP = 2;
                    pATT = 8;
                    pACC = 70;
                    pDEF = 0;
                    pMAGIC = 1;
                    pClass = "Berserker";
                    break;
                case 52:
                    pHP = 45;
                    pMP = 7;
                    pATT = 5;
                    pACC = 70;
                    pDEF = 3;
                    pMAGIC = 1;
                    pClass = "Paladin";
                    break;
                default:
                    system("CLS");
                    cout << " Invalid! Please enter a number between 1 and 4. " << endl << endl;
                    uCheck = false;
                    break;
            }
        } while (uCheck == false);
    }

    if (pClass == "Rogue") {
        pCritChance = 10;
    } else {
        pCritChance = 5;
    }
    cpHP = pHP;
    cpMP = pMP;
    pMlvl = plvl;
    if (pClass == "Mage") {
        pMlvl += 2;
    }

    cout << "Welcome, " << pName << ", to Text Adventure! Running on the revolutionary CryEngine3," << endl;
    cout << "Text Adventure is one of the most graphically advanced video games of all time!" << endl << endl;
    cout <<"We strongly suggest taking a look at the help section before playing.\nWant to check it out? (y/n)\n";

    do
    {
        uCommand = getch();
        uCommand = toupper(uCommand);
    } while ((uCommand != 'Y') && (uCommand != 'N'));

    if (uCommand == 'Y') {
        help();
    }

    //Closes text file
    load.close();

    do {                                                           //main loop
        system ("CLS");

        cout << "Your Class: " << pClass << "                   Level: " << plvl << endl;
        cout << "Health: " << cpHP << "/" << pHP << "                      Mana: " << cpMP << "/" << pMP << endl;
        cout << "Current EXP: " << pExp << "                             Gold: " << gold << endl << endl;


        if (map == 0) {                                                 //main map generation
            for (int countery = 0; countery < 12; countery++) {
                cout << "      ";
                for (int counterx = 0; counterx < 14; counterx++) {
                    if ((locatex == counterx)&&(locatey == countery)) {
                        cout << "@ ";
                        tertype = mainmapmatrix[counterx][countery];} else {
                    cout << mainmapmatrix[counterx][countery] << " ";}
                }
                cout << endl;
            }
        }

         if (map == 1) {                                                //dungeon 1 map generation
            for (int countery = 0; countery < 7; countery++) {
                cout << "      ";
                for (int counterx = 0; counterx < 5; counterx++) {
                    if ((locatex == counterx)&&(locatey == countery)) {
                        cout << "@ ";
                        tertype = dun1matrix[counterx][countery];} else {
                    cout << dun1matrix[counterx][countery] << " ";}
                }
                cout << endl;
            }
        }

         if (map == 2) {                                                 //dungeon 2 map generation
            for (int countery = 0; countery < 7; countery++) {
                cout << "      ";
                for (int counterx = 0; counterx < 5; counterx++) {
                    if ((locatex == counterx)&&(locatey == countery)) {
                        cout << "@ ";
                        tertype = dun2matrix[counterx][countery];} else {
                    cout << dun2matrix[counterx][countery]  << " ";}
                }
                cout << endl;
            }
        }

         if (map == 3) {                                                 //dungeon 3 map generation
            for (int countery = 0; countery < 7; countery++) {
                cout << "    ";
                for (int counterx = 0; counterx < 5; counterx++) {
                    if ((locatex == counterx)&&(locatey == countery)) {
                        cout << "@ ";
                        tertype = dun3matrix[counterx][countery];} else {
                    cout << dun3matrix[counterx][countery] << " ";}
                }
                cout << endl;
            }
        }

        cout << endl;
        cout << "Current Tile: ";                                             //Displays the player's current tile
        if (tertype == '.') {cout << "Grass" << endl;}
        if (tertype == '^') {cout << "Hills" << endl;}
        if (tertype == 'M') {cout << "Mountains" << endl;}
        if (tertype == '=') {cout << "Swamp" << endl;}
        if (tertype == '#') {cout << "Skyule CastleTown" << endl;}
        if (tertype == 'n') {cout << "Dungeon Entrance" << endl;}
        if (tertype == 'X') {cout << "Gate to Dragon's Layer" << endl;}
        if (tertype == 'F') {
            if (moncounter < 3) {
                cout << "???" << endl;
            } else {
                if (moncounter > 3) {
                    cout << "You have already defeated the final boss." << endl;
                } else {
                    montype = "Ganondorf";}
            }
        }

        monchance = rand()%10;
        if (montype != "Ganondorf") {
            if (tertype == 'R') {
                montype = "dragon";
            } else if ((monchance < monlimit)&&(tertype != '#')&&(tertype != 'F')&&(tertype != 'X')&&(didbattlehappen == false)) {
                montype = monstergen(tertype);
            } else {
                montype = "None";
                didbattlehappen = false;
            }
        }

        if (montype == "dragon") {                                  //Tells the player if they've already defeated the boss here
            if ((map == 1)&&(d1Boss == true)) {
                cout << "You've already defeated the boss here.\n";           //In the first dungeon
                montype = "None";
            }
            if ((map == 2)&&(d2Boss == true)) {
                cout << "You've already defeated the boss here.\n";            //In the second dungeon
                montype = "None";
            }
            if ((map == 3)&&(d3Boss == true)) {
                cout << "You've already defeated the boss here.\n";            //In the third dungeon
                montype = "None";
            }
        }

        if (montype == "dragon") {
            eBoss = true;
        } else {
            eBoss = false;
        }

        //COMBAT SYSTEM BELOW

        if (montype != "None") {
            cpACC = pACC;		//Put at here at the top
            sBonus = false;
            fBonus = false;
            mBonus = false;
            iBonus = false;
            vBonus = false;
            hBonus = false;
            int winGold;	//Monster gold

            do{
                do{
                    inventorySelect = 97;		//The letter a
                    uCheck = false;	//Not needed?
                    system("CLS");
                    if (montype != "Ganondorf") {
                        cout << "You have encountered a " << montype << "!" << endl;} else {
                        cout << "You have encountered Ganondorf! As you step forward, ready to fight, you feel the" << endl;      //Intro text for the final boss
                        cout << "earth rumble beneath your feet. Suddenly, a circular column of earth rises" << endl;
                        cout << "beneath you and Ganondorf rises to form a floating platform." << endl << endl;
                        cout << "There is now no escape. Ganondorf begins walking towards you..." << endl;}

                        cout << "Prepare for battle!" << endl;
                        cout << endl << " Select a weapon for you to use. " << endl;
                        cout << "You may only choose a weapon which can be used by " << pClass << "s." << endl;
                        cout << endl << " (a)No weapon " << endl;

                        for(int counter = 12; counter < 31; counter++)	//The weapons for 12 iterations, each time increasing the value of counter by 1
                        {
                            if (item[counter] > 0) //if the value stored in the [counter]'th element of the array item is greater than 0
                            {
                                inventorySelect++;	//Lists the items
                                cout <<inventorySelect <<") "; //outputs the inventory item number selected
                                cout << itemName[counter] << ": " <<item[counter] <<"\n"; //outputs the name of the item
                            }
                        }

                        //User input
                        invCommand = getch();

                } while ((invCommand > inventorySelect) || (invCommand < 97));
                //repeats all this as long as the invCommand variable is greater than the inventorySelect variable, or while it is less than the invCommand variable

            if (invCommand != 97)	//Which is none
            {
                inventorySelect = 97;	//Restarts the list and compares it to the number the player selected
                findItem = -1;	//Becuase if findItem == 0, it could select the healthpotion
                for(int counter = 12; counter < 31; counter++) //for 19 iterations beginning with the variable counter assigned to 12, increasing by 1 with each iteration
                {
                    if (item[counter] > 0)//if the value stored in the [counter]th element of the array item
                    {
                        inventorySelect++;//increase the value of inventorySelect by 1
                        if(inventorySelect == invCommand)	//If the list number and the user input are the same, it means the user selected that item
                        {
							findItem = counter;	//Used like item[counter]
						}
                    }
                }
                if (((pClass == "Rogue") && ((findItem > 11) && (findItem < 16))) || ((pClass == "Mage") && ((findItem > 15) && (findItem < 23))) ||
                    ((pClass == "Berserker") && ((findItem > 22) && (findItem < 27))) || ((pClass == "Paladin") && ((findItem > 26) && (findItem < 31))))
                {
                    //"Equip" weapon
                    item[findItem]--; //decreases the value of the [finditem]th element of the array item by 1 (effectively to 0)
                    pWep = itemName[findItem]; //sets the value of pWep to the string stored in the [finditem]th element of the array itemName
                    pwepType = findItem; //sets the weapon type to the type stored in the variable findItem
                    tempWeapon = pwepType; //sets the temporary weapon value variable to the current weapon

                if (pClass == "Rogue")		//Stat enhance for rogues
                {
                    pATT = pATT + (2*(pwepType - 11));	//+2 att
                    cpACC = cpACC + (5*(pwepType - 12));	//+5 acc
                    if (pwepType == 15) {
                        pCritChance = pCritChance + 10;	//Stiletto = + 10 crit. chance
                    }
                }
                else if (pClass == "Mage")
                {
				//Wands don't get pATT bonuses. Only staffs
				if ((pwepType > 19) && (pwepType < 23))
				{
					pMAGIC = pMAGIC + 10;	//+10 magic for wands
					if (pwepType == 20) {
						mBonus = true;}		//Equip arcanomancer's wand
					else if (pwepType == 21) {
						fBonus = true;}		//Equip pyromancer's wand
					else {
						iBonus = true;}	//Equip cryomancer's wand
				}
				else	//Staffs
				{
					pMAGIC = pMAGIC + (2*(pwepType - 16));	//+2 magic bonus
					pATT = pATT + (pwepType - 15);	//+1 att bonus
					if (pwepType == 19)	//Maelstrom staff
					{
						sBonus = true;	//10% no mana cost
					}
				}
			}
			else if (pClass == "Berserker")
			{
				pATT = pATT + (3*(pwepType - 22));	//+3 att
				if (pwepType == 26)	//Battleaxe
				{
					vBonus = true;	//+10% vampirism bonus per level
				}
			}
			else	//paladin
			{
				pDEF = pDEF + (pwepType - 26)/2;	//+1 def every two weapons
				pATT = pATT + (pwepType - 26);	//+1 att
				if (pwepType >= 29)
					cpACC = cpACC + 5*((pwepType - 28));	//+5 acc on third and fourth weapon
				if(pwepType == 30)
				{
					hBonus = true;	//+10 heal bonus
				}
			}
			uCheck = true;

			if (cpACC > 100)
				cpACC = 100;
			if (pCritChance > 100)
				pCritChance = 100;
			}
			else
			{
				cout <<"Cannot equip that weapon!\n";        //alerts the player when the choose a weapon designed for another class
				system("PAUSE");
			}
		}
		//If the player selects none
		else if (invCommand == 97)
		{
			pwepType = -1;
			tempWeapon = -1;
			pWep = "None";
			uCheck = true;
		}

		} while (uCheck == false);
        eType = montype;

        elvl = plvl;

        eWep = "none";

        //Enemy stat bonus

        if (eType == "goblin") {      //Gives stat bonuses to the enemy depending on their class
            eHP = 10;
            eMP = 1;
            eATT = 4 + elvl/2 + elvl/4;
            eMAGIC = 0;
            eDEF = 0;
            eACC = 60;
        }
        if (eType == "orc") {
            eHP = 15;
            eMP = 2;
            eATT = 6 + elvl/2 + elvl/3;
            eMAGIC = 0;
            eDEF = 1;
            eACC = 75;
        }
        if (eType == "elf") {
            eHP = 20;
            eMP = 7;
            eATT = 5;
            eMAGIC = 3;
            eDEF = 1 + elvl/3 + elvl/5;
            eACC = 70;
        }
        if (eType == "human") {
            eHP = 20 + elvl/3;
            eMP = 4;
            eATT = 6;
            eMAGIC = 2;
            eDEF = 1;
            eACC = 75;
        }
        if (eType == "giant") {
            eHP = 27 + elvl + elvl/3;
            eMP = 3;
            eATT = 12 + elvl/4 + elvl/5;
            eMAGIC = 0;
            eDEF = 3 + elvl/3;
            eACC = 60;
        }
        if (eType == "dragon") {
            eNumBoss ++;
            eHP = 60 + 15*eNumBoss;
            eATT = 18 + 5*eNumBoss;
            eDEF = 5 + (4*eNumBoss);
            eMAGIC = 10;
            eACC = 85;
            eMP += 8*eNumBoss;
        }

        if (eType != "dragon") {
            eHP += 2*elvl;
            eATT += elvl;
        }

        if (eType == "Ganondorf") {
            eNumBoss ++;
            eHP = 150;
            eATT = 20;
            eDEF = 10;
            eMAGIC = 20;
            eACC = 85;
        }

        //Enemy racial bonuses

        if ((eType == "elf")||(eType == "human")) {              //Gives additional bonuses based on class
            eMAGIC += elvl;
        } else {
            eMAGIC += elvl/2;
        }

        //Add other modifiers from weapons and other items here

        //Battle statistics
        bool uBattleover = false;

        //a prefix of c denotes current health/accuracy/mana poitns etc. This should be saved to the character's profile and to the save file
        //I've placed it here because the stats for units are selected before this.

        ceHP = eHP;
        ceMP = eMP;
        //cpACC = pACC;		MOVED UP TO THE TOP
        ceACC = eACC;

        pConf = false;
        pConfCure = 0;

        eConf = false;
        eConfCure = 0;

        pPois = false;
        pPoisCure = 0;

        ePois = false;
        ePoisCure = 0;

        pCold = false;
        pColdCure = 0;

        eCold = false;
        eColdCure = 0;

        pSpellMCD [1] = 4; //Magic Missile
        pSpellMCD [2] = 6; //Fire Bolt
        pSpellMCD [3] = 8; //Ice Bolt
        pSpellMCD [4] = 10;//Venom Bolt
        pSpellMCD [5] = 5; //Cure
        pSpellMCD [6] = 10;//Magic Armor
        pSpellMCD [7] = 7; //Hide
        pSpellMCD [8] = 7; //Vampirism
        pSpellMCD [9] = 9; //Shockwave
        pSpellMCD [10]= 20;//Radiance

        //Sets the mana costs of each spell. When a spell is cast, the mana cost is subtracted from the player's current mana.
	    //If the mana cost for a certain spell is greater than your current mana, you cannot cast that spell


        pSpellCost [1] = 2;
        pSpellCost [2] = 2;
        pSpellCost [3] = 3;
        pSpellCost [4] = 4;
        pSpellCost [5] = 5;
        pSpellCost [6] = 3;
        pSpellCost [7] = 3;
        pSpellCost [8] = 5;
        pSpellCost [9] = 4;

        //Each spell has a minimum required magic level to be able to cast it. For example, Cure has a magic level of 4. That means
	    //that in order to cast it you have to be a level 2 mage or a level 4 rogue, paladin, or berserker.

        pSpellMlvl [1] = 3;
        pSpellMlvl [2] = 5;
        pSpellMlvl [3] = 7;
        pSpellMlvl [4] = 8;
        pSpellMlvl [5] = 4;
        pSpellMlvl [6] = 6;
        pSpellMlvl [7] = 6;
        pSpellMlvl [8] = 9;
        pSpellMlvl [9] = 10;
        pSpellMlvl [10]= 11;

        //To conserve code, this variable (pSpellAvail) calculates whether a spell is available at the beginning of each new turn.
	    //This way it is not necessary to check whether a spell is castable every time a player wants to cast a spell.

        for (int count = 1; count < 11; count ++) {
            pSpellAvail [count] = false;
        }
        for (int count = 1; count < 11; count ++) {
            pSpellCD [count] = 0;
        }

        //For temporarily storing the random number inside a variable to compare against in battleint uAcc;

    pMlvl = plvl;

    if (pClass == "Mage") {
        pMlvl +=2;
    }
    if (pClass == "Rogue") {
        pCritChance = 15;
    } else {
        pCritChance = 5;
    }

    uPTurn = true;

    pCold = false;
    pPois = false;
    pConf = false;
    pMHide = false;
    pMGuard = false;

    eConf = false;
    ePois = false;
    eCold = false;

    //MAIN COMBAT LOOP

    do {
        system ("CLS");
        uFormat = 0;
        pSpellCost[10] = (cpMP*3/4);
        uAcc = rand()%100;

        /*
        If in the last repetition there was a turn used (not just checking the options)
        */
        if (uPTurn == true) {

        //Mana point recovery
            if (cpMP < pMP) {
                cpMP ++;
            }
            if (ceMP < eMP) {
                ceMP ++;
            }
        //Confusion, Cold, and Poison curing
            if (pColdCure > 0) {
                pColdCure--;
            }
            if (eColdCure > 0) {
                eColdCure--;
            }
            if (pCold == true) {
                if (pColdCure == 0) {
                    pCold = false;
                    cout << "You feel a little warmer now." << endl;
                    uFormat++;
                }
            }
            if (eCold == true) {
                if (eColdCure == 0) {
                    eCold = false;
                    uFormat++;
                    cout << "The " << eType << " doesn't look so cold now." << endl;
                }
            }
            if (pConf == true) {
                if (uAcc < pConfCure) {
                    pConf = false;
                    cout << "You get ahold of yourself." << endl;
                    uFormat++;
                }
            }
            if (pPois == true) {
                if (uAcc < pPoisCure) {
                    pPois = false;
                    cout << "The poison wears off. " << endl;
                        uFormat++;
                }
            }
            if (eConf == true) {
                if (uAcc < eConfCure) {
                    eConf = false;
                    cout << "The enemy looks less confused." << endl;
                    uFormat++;
                }
            }
            if (ePois == true) {
                if (uAcc < ePoisCure) {
                    ePois = false;
                    cout << "The enemy doesn't seem to be poisoned anymore." << endl;
                    uFormat++;
                }
            }
            if (pMGuard == true) {
                if (uAcc <= 10) {
                    pMGuard = false;
                    cout << "The magical shield around you suddenly fades." << endl;
                    uFormat ++;
                }
            }
            if (pMHide == true) {
                if (uAcc < pMHideEnd) {
                    cout << "You are no longer hidden!" << endl;
                    uFormat ++;
                    pMHide = false;
                }
            }
            if (pRadiant == true) {    //If player is in a radiant state
                pRadiantEnd -= 1;      //Reduces turns left by 1
                if (pRadiantEnd == 0) { //If turns left is 0
				    cout << "The glow around you disappears."; //Generic status ending message
				    pRadiant = false; //Ends the status
				    pATT -= 8;        //Reduces attack
				    pMAGIC -= 8;      //Reduces magic
				    cpACC -= 30;      //Reduces accuracy
                }
            }
            pConfCure += 20; //Timers for various conditions on player and enemy
            eConfCure += 20;
            pPoisCure += 20;
            ePoisCure += 20;
            pMHideEnd += 20;
            //Spell Cooldowns
            for (int count = 1; count < 11; count ++) {
                if (pSpellCD [count] == 1) {
                    pSpellCD [count] = 0;
                } else if (pSpellCD [count] >= 2) {
                    pSpellCD [count] -= 1;
                }
                if ((pSpellCD [count] == 0)&&(pSpellCost[count] <= cpMP)&&(pMlvl >= pSpellMlvl[count])) {
                    pSpellAvail [count] = true;
                }
            }
        }
    uPTurn = false;   //This allows for checking whether the player has performed an action yet

    for (int count = 3; count > uFormat; count--) {
        cout << endl;
    }
    //PLEASE NOTE THAT I CHANGED peACC TO pACC!!!
    //Outputs several lines informing the player about their current health, max health, attack, accuracy, magic, defence, current mana and max mana

    cout << "Player)" << endl;
    cout << "Level: " << plvl << endl;
    cout << "HP: " << cpHP << "/" << pHP << "               ATTACK: " << pATT << "               ACCURACY: " << cpACC << endl;
    cout << "MAGIC: " << pMAGIC << "                   DEFENSE: " << pDEF << ", MP: " << cpMP << "/" << pMP << endl;
    cout << "Class: " << pClass << "               Current Weapon: " << pWep;

    if (pPois == true) {
        cout << "!POISONED ";
    }
    if (pConf == true) {
        cout << "!CONFUSED ";
    }
    if (pMGuard == true) {
        cout << "#PROTECTED ";
    }
    if (pMHide == true) {
		cout << "#HIDDEN ";
    }
    if (pRadiant == true) {
		cout <<  "#RADIANT ";
    }
    if (pBerserk == true) {
		cout << "@ENRAGED ";
    }

    cout << endl << endl;

    //Outputs several lines once more, detailing the various stats of the enemy that the player should be concerned about

    cout << "Enemy)" << endl;
    cout << "HP: " << ceHP << "/" << eHP << "               ATTACK: " << eATT << "               ACCURACY: " << ceACC << endl;
    cout << "MAGIC: " << eMAGIC << "                   DEFENSE: " << eDEF << endl;
    cout << "Race: " << eType;
    if (ePois == true) {
        cout << "!POISONED ";
    }
    if (eConf == true) {
        cout << "!CONFUSED ";
    }
    if (eCold == true) {
		cout << "!COLD ";
    }
    if (sDuration > 0) {
		cout << "!SHOCKED ";
    }
    if (eStun == true) {
        cout << "!STUNNED ";
    }

    cout << endl << endl;

    cout << "Do what? (1)   Attack" << endl;                         //Available commands during battle
    cout << "         (2)   Cast a spell " << endl;
    cout << "         (3)   Use an item " << endl;
    cout << "         (4)   Change equipment " << endl;
    if (montype != "Ganondorf") {
    cout << endl << "         (5) Run" << endl;                     //One simply does not run away from Ganondorf
    }

    uCommand = getch();

    cout << endl << endl;
    //Player move
    if (uCommand == 49) {
        uPTurn = true;
        uAcc = (rand()%100)+1;
        pCritChance = 5;
        if (pClass == "Rogue") {
            pCritChance += 10;
        }
    	int dmg = rand()% ((pATT * 12)/10 - (pATT * 7)/10 + 1) + (pATT * 7)/10;	//Range. It works
        int crit = rand()% 100 + 1;
		if (pConf == true) {
            uAcc += 20;
        }
		if (uAcc <= cpACC) {
            cout << "You hit the " << eType << "!" << endl;
            cpACC -= 2;
            if (crit <= pCritChance) {
                cout << "A critical hit!" << endl;      //Critical
                if (iCrit > 0)	//Jarate
				{
				    dmg = dmg*iCrit/10;
                }
                ceHP -= (dmg*3/2 - eDEF/3);           //Critical hits ignore 2/3s of the enemy's defense
            } else {
                if (dmg <= eDEF) {
                    cout << "But it deals no damage." << endl;
                    cpACC+=2;
                } else {
                    ceHP -= (dmg - eDEF);
                }
            }

         		//Special ability for berserkers

		if (pClass == "berserker") { //If the player is a berserker
			if (pBerserk == true) {  //and if this player has a berserk strike stored up
				cout << "You released your fury in a berserk swing!\n"; // Releases his fuuuury!
				ceHP -= (((pHP-cpHP)/2)+plvl); //Decreases the enemy's health by a lot
				cout << "You strike the " << eType << " with all your energy!\n";
				pBerserk = false; //Sets berserk mode fo false
				pHits = 0;
            } else if (pHits == 0) { //If current hit count is 0
				cout << "You are beginning to feel the fury of battle...\n"; //Hes gettin pumped
				pHits = 1;   				//Increases hit count by 1
			} else if (pHits == 1) {     //If current hit count is 1
				cout << "You are relishing the excitement!\n"; //Oh boy
				pHits = 2;	//Increases hit count by 1
			} else if (pHits == 2) {     //If current hit count is 2
				cout << "You almost can't contain the fury within you!\n"; //Uh oh
				pHits = 3;				//Increases hit count to 3
			}

        }

    } else {
        if (pConf == true) {
            cout << "You swing wildly in your confusion and miss!" << endl;
        } else {
            cout << "You miss the " << eType << "." << endl;
            cpACC+=2;
        }
    }
    }

    if (uCommand == 50) {          //Player chooses to cast a spell
        cout << "Use which spell? " << endl << endl;
        cout << " Player Magic level: " << pMlvl << endl;
        for (int count = 1; count < 11; count++) {
            if ((pSpellCD [count] == 0)&&(pSpellCost [count] <= cpMP)&&(pMlvl >= pSpellMlvl[count])) {
                pSpellAvail [uCommand] = true;
            } else {
                pSpellAvail [uCommand] = false;
            }
            if (pSpellAvail[count] == true) {
                if ((count == 1)&&(pMlvl > 2)) {
                    cout << "   (1) Magic missile (2mp) ";
                }
                if ((count == 2)&&(pMlvl > 4)) {
                    cout << "   (2) Fire bolt (2mp) ";
                }
                if ((count == 3)&&(pMlvl > 6)) {
                    cout << "   (3) Ice bolt (3mp) ";
                }
                if ((count == 4)&&(pMlvl > 3)) {
                    cout << "   (4) Venom blast (4mp) ";
                }
                if ((count == 5)&&(pMlvl > 5)) {
                    cout << "   (5) Cure (5mp) ";
                }
                if ((count == 6)&&(pMlvl > 5)) {
                    cout << "   (6) Magic armor (3mp) ";
                }
                if ((count == 7)&&(pMlvl > 5)) {
                    cout << "   (7) Hide (3mp) ";
                }
                if ((count == 8)&&(pMlvl > 8)) {
                    cout << "   (8) Vampirism (5mp) ";
                }
                if ((count == 9)&&(pMlvl > 9)) {
                    cout << "   (9) Shockwave (4mp) ";
                }
                if ((count == 10)&&(pMlvl > 10)) {
                    cout << "   (10) Radiance (" << pSpellCost[10] << "mp) ";
                }
                if (pSpellCD[count] == 1) {
                    cout << ", 1 turn left";
                } else if (pSpellCD[count] > 1) {
                    cout << ", " << pSpellCD[count] << " turns left";
                }
                if (pSpellAvail[count] == true) {
                    cout << endl;
                }
            }
        }
        /*
        Adding more spells later, just checking functionality
        */
        cout << endl;
        uCommand = getch();
        uCommand = uCommand - 48;
        if ((uCommand > 10)||(uCommand < 1)) {
            uCommand = 1;
        }
        if (pSpellAvail[uCommand]== false) {     //Alerts the player if spell is not avaliable
            if (cpMP < pSpellCost[uCommand]) {
                cout << "You don't have enough mana to cast that." << endl;    //Alerts the player of not enough mana
            } else if (pSpellCD[uCommand] > 0) {
                cout << "The cooldown must be 0 in order to cast a spell." << endl;    //Alerts the player of cooldown
                cout << "CD: " << pSpellCD[uCommand] << endl;
            } else {
                cout << "You don't know that spell." << endl;
            }
        } else if (pSpellAvail[uCommand] == true) {

            pSpellCD [uCommand] = pSpellMCD[uCommand];
            pSpellAvail [uCommand] = false;
            cpMP -= pSpellCost[uCommand];

            if (sBonus == true)	//Comes from the Maelstorm staff. At a 10% chance, the Maelstrom staff will let you cast a spell for free.
            {
                int check = rand() % 10;
                if (check == 0)
                {
                    cout <<"The Maelstrom Staff suddenly glows! You feel a surge of power.\n";
                    cpMP = cpMP + pSpellCost [uCommand];
                }
                cout <<check <<"\n";
            }

            switch (uCommand) {
                case 1:
                    cout << "You cast Magic Missile!" << endl;
                    uAcc = rand()%20;
                    uPTurn = true;
                    if (uAcc > 0) {
                        cout << "It hits the " << eType << "!" << endl;
                        ceHP -= (pMAGIC+2);

                        if (pClass == "mage") {
                            if (mBonus == true) {
                                ceHP = ceHP - ((plvl/3 + 1)*20)/10;
                            } else {
                                ceHP -= (plvl/3 +1);
                            }
                        }

                        if (mBonus == true)	//+5% bonus
                            uAcc = rand()% 95;
                        else
                            uAcc = rand()%100;

                        if (uAcc <= plvl*3 + 35) {
                            cout << "The magic missiles confuse the " << eType << "!." << endl;
                            eConf = true;
                            eConfCure = 0;
                        }
                    } else {
                        uAcc = rand()%3;
                        if (uAcc = 0) {
                            cout << "But you slip up! The magic missiles go astray!" << endl;
                        }
                        if (uAcc = 1) {
                            cout << "But the magic power dissipates!" << endl;
                        }
                        if (uAcc = 2) {
                            cout << "But it doesn't connect with the enemy!" << endl;
                        }
                    }
                    break;
                case 2:
                    cout << "You cast Fire Bolt!" << endl;
                    uAcc = rand()%20;
                    uPTurn = true;
                    if (uAcc > 0) {
                        cout << "It hits the " << eType << "!" << endl;
                        ceHP -= (pMAGIC*11/10);
                        if (pClass == "mage") {
                            if (fBonus == true) {
                                ceHP = ceHP - (pMAGIC*15/10);	//1.5x damage
                            } else {
                                ceHP -= (plvl/3 +1);	//Maximum 4 damage???
                            }
                        }
                        uAcc = rand()%2;
                        if (uAcc = 1) {
                            cout << "A great shot!" << endl;
                            if (fBonus == true) {
                                ceHP = ceHP - ((pMAGIC*15/10) + 3);
                            }
                            ceHP -= (pMlvl/2 +2);
                        }

                        } else {
                            cout << "But it doesn't work! The fires fizzle and go out." << endl;
                        }
                    break;
                case 3:
                    cout << "You cast Ice Bolt!" << endl;
                    uAcc = rand()%20;
                    uPTurn = true;
                    if (uAcc > 0) {
                        cout << "It hits the " << eType << "!" << endl;
                        ceHP -= (pMAGIC*12/10);
                        if (pClass == "mage") {
                            if (iBonus == true)
                                ceHP = ceHP - (pMAGIC*15)/10;
                            else
                                ceHP -= (plvl/3 +1);
                        }
                        cout << "The " << eType << " looks a little cold." << endl;
                        eCold = true;
                        eColdCure = 0;
                    } else {
                        cout << "But the icicles suddenly evaporate!" << endl;
                    }
                    break;
                case 4:
                    cout << "You cast Venom Blast!" << endl;
                    uAcc = rand()%20;
                    uPTurn = true;
                    if (uAcc > 0) {
                        cout << "It hits the " << eType << "!" << endl;
                        ePois = true;
                        ePoisCure = 0;
                        cout << "The " << eType << " looks sick." << endl;
                    } else {
                            cout << "But they miss completely!";
                    }
                    break;
                case 5:
                    cout << "You cast Cure!" << endl;
                    uAcc = rand()%20;
                    uPTurn = true;
                    if (uAcc > 0) {
                        if (pPois = true) {
                            cout << "You feel much better." << endl;
                            pPois = false;
                        }
                        if (pConf = true) {
                            cout << "You feel less confused." << endl;
                            pConf = false;
                        }
                        if (pCold = true) {
                            cout << "You feel a little warmer now." << endl;
                            pCold = false;
                        }
                    } else {
                        cout << "But it didn't work!" << endl;
                    }
                    break;
                case 6:
                    cout << "You cast Magic Armor." << endl;
                    uAcc = rand()%20;
                    uPTurn = true;
                    if (uAcc > 0) {
                        cout << "You feel protected!" << endl;
                        pMGuard = true;
                    } else {
                        cout << "But nothing happens!" << endl;
                    }
                    break;
                case 7:
                    cout << "You cast Hide." << endl;
                    uAcc = rand()%20;
                    uPTurn = true;
                    if (uAcc > 0) {
                        cout << "You feel hidden!" << endl;
                        pMHide = true;
                        pMHideEnd = 50;
                    } else {
                        cout << "But it didn't do anything!" << endl;
                    }
                    break;
                case 8:
                    cout << "You cast Vampirism!\n";
                    uAcc = rand()%20;
                    if (pConf == true) { //There is an additional 20% chance to miss if you are confused
                        uAcc -= 4;
                    }
                    uPTurn = true;
                    if (uAcc > 0) {
                        cout << "You absorb some of your enemy's lifeforce!\n"; //Vampirism absorbs 1/3 of your missing health from the enemy
                        uAcc = (pHP - cpHP)/3; //The uAcc variable also serves as a temporary storage variable...
                        ceHP -= uAcc;      //The enemy loses health equal to 1/3 or your missing health.
                        if (vBonus = true)	{ //Vampirism bonus
                            cpHP = cpHP + 15;
                            if (ceHP > pHP) {
                                cpHP = pHP;
                            }
                            cout <<"You heal some additional health.\n";
                        }
                        cout << "You feel more alive! The " << eType << " looks a little weaker!\n"; //Generic informative message

                    } else {
                        cout << "But it doesn't work!!\n";
                    }
                    break;
                case 9:
                    cout << "You cast Shockwave.\n"; //Unlike any of the other attack spells Shockwave does not have any secondary effects other than damage.
                    uAcc = rand()%20;
                    if (pConf == true) { //There is an additional 20% chance to miss if you are confused
                        uAcc -= 4;
                    }
                    uPTurn = true;
                    if (uAcc > 0) {
                        cout << "The shockwave hits the" << eType << "!\n";
                        ceHP -= (((pMlvl + pMAGIC)*6/5 +3));
                        if (pClass == "mage") {
                            ceHP -= plvl/2 +1;
                        }
                    } else {
                        cout << "But it completely missed!\n";	 //ANOTHER generic failure message, like all the other ones.
                    }
                    break;
                case 10:
                    cout << "You cast Radiance!\n"; //Radiance is a gamble spell...it could give good or bad effects
                    uAcc = rand()%20;
                    if (pConf == true) { //There is an additional 20% chance to miss if you are confused
                        uAcc -= 4;
                    }
                    uPTurn = true;
                    if (uAcc > 0) {
                        uAcc = rand()%10;
                        if (uAcc < 3) {  //At a 30% chance,
                            cout << "You are soothed in a radiant light.\n"; //...Radiance heals the caster for the cost in MP
                            cpHP += pSpellCost[10];
                            if (hBonus == true)	{//Additional health from shining blade
                                cpHP = cpHP + (plvl*15)/10;
                            }
                            if (cpHP > pHP) {
                                cpHP = pHP;
                            } //If the player's health went past its max it is reduced accordingly
                        }
                        if ((uAcc < 6)&&(uAcc > 2)) { //At a 30% chance,
                            cout << "Beams of light spike the" << eType << "!\n"; //...Radiance damages the enemy for the cost in MP
                            if (hBonus == true)	//NOTE: THE BONUS IS ADDED TO THE REGULAR ATTACK UNLIKE ALL THE OTHER WEAPON BUFFS
                                ceHP =  ceHP - pDEF/3;
                            ceHP -= pSpellCost[10];
                        }
                        if ((uAcc < 9)&&(uAcc > 5)) { //At a 30% chance,
                            cout << "You feel like a killing machine!\n"; //Radiance makes you much scarier
                            pRadiant = true;
                            pRadiantEnd = 5;
                            pATT += 10;
                            pMAGIC += 10;
                            cpACC += 30;
                        }
                        if (uAcc == 9) { //At a 10% chance,
                            cout << "You feel vaguely nervous...\n"; //Radiance does nothing!
                        }
                    }
                    break;
                default:
                    cout << "That's not a valid choice." << endl;
                    break;
                }
            }
            uCommand = 2;
    }
    // Using items
    if (uCommand == 51) {
        uCheck = false;
        cout << "Use which item? " << endl;
        cout <<"Inventory:\n";	//Output the items available
        inventorySelect = 96;
        for(int counter = 0; counter < 12; counter++)
        {
            if (item[counter] > 0)
            {
                inventorySelect++;	//Lists the items
                cout <<inventorySelect <<") ";
                cout << itemName[counter] << ": " <<item[counter] <<"\n";
            }
        }
        inventorySelect++;
        cout <<inventorySelect <<") Exit\n";
        do {
            invCommand = getch();

            if((invCommand > inventorySelect) || (invCommand < 97)) {
                cout <<"Not a valid choice!\n";
                system("PAUSE");
            }
        }while ((invCommand > inventorySelect) || (invCommand < 97));

        if (invCommand != inventorySelect) {

            inventorySelect = 96;	//Restarts the list and compares it to the number the player selected
            findItem = -1;	//Becuase if findItem == 0, it could select the healthpotion
            for(int counter = 0; counter < 12; counter++){
                if (item[counter] > 0) {
                    inventorySelect++;
                    if(inventorySelect == invCommand) {	//If the list number and the user input are the same, it means the user selected that item
                        findItem = counter;	//Used like item[counter]
                    }
                }
            }
                    //It did output the name of the item but no longer will due to
            item[findItem]--;

            if (findItem == 0) {	//Health potion heals 25% hp and 25% mp

                if (cpHP + ((pHP * 25)/100) > pHP)
                {
                    cout <<"\nYou heal " << pHP - cpHP <<" hp\n";	//To find whatever is left of the missing hp
                    cpHP = pHP;
                }
                else
                {
                    cpHP = cpHP + ((pHP * 25)/100);
                    cout <<"\nYou heal " << (pHP*25)/100  <<" hp\n";
                }
                if (cpMP + ((pMP * 25)/100 >> pMP))
                {
                    cout <<"\nYou gain " << pMP - cpMP <<" mp\n";
                    cpMP = pMP;
                }
                else
                {
                    cpMP = cpMP + ((pMP * 25)/100);
                    cout <<"\nYou gain " << (pMP*25)/100 <<" mp\n";
                }
            }
            else if (findItem == 1)	//Greater health potion heals 50% hp and 50% mp
            {
                if (cpHP + ((pHP * 50)/100) > pHP)
                {
                    cout <<"You heal " << pHP - cpHP <<" hp\n";
                    cpHP = pHP;
                }
                else
                {
                    cpHP = cpHP + ((pHP * 50)/100);
                    cout <<"\nYou heal " << (pHP*50)/100 <<" hp\n";
                }
                if (cpMP + ((pMP * 50)/100 >> pMP))
                {
                    cout <<"\nYou gain " << pMP - cpMP <<" mp\n";
                    cpMP = pMP;
                }
                else
                {
                    cpMP = cpMP + ((pMP * 50)/100);
                    cout <<"\nYou gain " << (pMP*50)/100 <<" mp\n";
                }
            }
            else if (findItem == 2)	//Heals fully
            {
                cout <<"\nYou are completely healed!";
                cpHP = pHP;
                cpMP = pMP;
            }
            else if (findItem == 3)
            {
                bpBonus = buffs(bpBonus, pATT, pDEF, "attack");
            }
            else if (findItem == 4)	//Using the accuracy potion
            {
                if (apBonus > 0)	//If the player uses another Accuracy potion while one is still active
                {
                    cpACC = cpACC - apBonus;
                    pCritChance = pCritChance - apBonus;
                    pATT = pATT + 3;
                }
                apBonus = rand()% 11 + 5;	//+ 5 - 15% acc, - 3 atk
                if (apBonus + cpACC > 100)	//Checks for accuracy
                    apBonus = 100 - cpACC;
                if (apBonus + pCritChance > 100)	//Then critical chance
                    apBonus = 100 - pCritChance;
                cout <<"Your accuracy has and critical chance has increased by +" << apBonus <<"%\n";
                cout <<"at the cost of 3 attack\n";
                apBonus = apBonus + 5;	//Offset a little bit since subtraction comes at the beginning of battle
                cpACC = cpACC + apBonus;
                pCritChance = pCritChance + apBonus;
                if (pCritChance > 100)
                    pCritChance = 100;
                pATT = pATT - 3;
                if (pATT < 0)
                    pATT = 0;
                }
                else if (findItem == 5)	//Using the spell potion
                {
                    spBonus = buffs(spBonus, pMAGIC, pDEF, "magic");
                }
                else if (findItem == 6)
                {
                    int missHit = rand()% 6 + 1;	//20% miss chance

                    cout <<"You throw a flashbang!\n";
                    if (missHit != 1)
                    {
                        eBlind = rand()% 16 + 10;	//10 - 25% decrease
                        if (eACC < eBlind)
                            eBlind = eACC;
                        else
                            eACC = eACC - eBlind;
                        cout <<"The enemy is blinded by the flash!\n";
                        eBlind = eBlind + 5; //Offset
                    }
                    else
                        cout <<"But the enemy " << eType << " blocks his eyes from the flash\n";
                    }
                    else if (findItem == 7)	//Using a grenade. It ignores defence	- 5 - 30 damage
                    {
                        int rDamage = rand()% 26 + 5;

                        cout <<"Fire in the hole!\n";
                        if (rDamage >= ceHP)
                        {
                            int ctWin = rand()% 2;
                            if	(ctWin == 0)
                                cout <<"Counter Terrorists win!\n";
                            else
                                cout <<"Terrorists win!\n";
                            ceHP = 0;
                        }
                        else
                        {
                            ceHP = ceHP - rDamage;
                            cout <<"It deals " <<rDamage <<" damage!\n";
                        }
                    }
                    else if (findItem == 8)	//Jarate - starts from +100% critical damage
                    {
                        cout <<"You throw a bottle of jarate at the enemy\nDisgusting!";
                        iCrit = 110;	//Offset
                    }
                    else if (findItem == 9)	//Storm potion
                    {
                        cout <<"You throw a storm potion at the enemy. Pop-!\n";
                        sDuration = 3;
                    }
                    else if (findItem == 10)	//Poison dart
                    {
                        cout <<"You hit the enemy with a poisoned dart.\nThe " << eType << " looks a little sick now.\n";
                        ePois = true;
                        ePoisCure = 0;
                    }
                    cout << endl << endl;
          /*            if (uCheck == false) {
                           cout <<"What is this?\n";
                           }	*/	//No seriously, what is it?

                    uPTurn = true;	//Turn shifts over to the enemy
                }
		}
    // Changing equipment
    if (uCommand == 52) {
        do{
            inventorySelect = 97;
            uCheck = false;	//Not needed?
            cout << endl << " Select a weapon for you to use. " << endl;
            cout << "You may only choose a weapon which can be used by " << pClass << "s." << endl;
            cout << endl << " (a) No weapon " << endl;

            for(int counter = 12; counter < 31; counter++)	//The weapons
            {
				if (item[counter] > 0)
				{
					inventorySelect++;	//Lists the items
					cout <<inventorySelect <<") ";
					cout << itemName[counter] << ": " <<item[counter] <<"\n";
				}
            }
		    do
			{
                invCommand = getch();
			} while ((invCommand > inventorySelect) || (invCommand < 97));

            if (invCommand != 97)	//Which is none. I hate ASCII characters now
            {
                inventorySelect = 97;	//Restarts the list and compares it to the number the player selected
                findItem = -1;	//Becuase if findItem == 0, it could select the healthpotion
                for(int counter = 12; counter < 31; counter++)
                {
                    if (item[counter] > 0)
                    {
                        inventorySelect++;
                        if(inventorySelect == invCommand)	//If the list number and the user input are the same, it means the user selected that item
						{
							findItem = counter;	//Used like item[counter]
						}
                    }
                }
			if (((pClass == "Rogue") && ((findItem > 11) && (findItem < 16))) || ((pClass == "Mage") && ((findItem > 15) && (findItem < 23)))
            || ((pClass == "Berserker") && ((findItem > 22) && (findItem < 27))) || ((pClass == "Paladin") && ((findItem > 26) && (findItem < 31))))
			{
				//"Equip" weapon
				item[findItem]--;
				tempWeapon = pwepType;
				pWep = itemName[findItem];
				pwepType = findItem;
				if (tempWeapon > -1)
					item[tempWeapon]++;

			if (pwepType != -1)
			{
                if (pClass == "Rogue")		//Stat enhance for rogues
                {
                    pATT = pATT + (2*(pwepType - 11));	//+2 att
                    cpACC = cpACC + (5*(pwepType - 12));	//+5 acc
                    if (pwepType == 15)
                        pCritChance = pCritChance + 10;	//Stiletto = + 10 crit. chance
                }
                else if (pClass == "Mage")
                {
				//Wands don't get pATT bonuses. Only staffs
                    if ((pwepType > 19) && (pwepType < 23))
                    {
                        pMAGIC = pMAGIC + 10;	//+10 magic for wands
                        if (pwepType == 20)
                            mBonus = true;		//Unequip arcanomancer's wand
                        else if (pwepType == 21)
                            fBonus = true;		//Unequip pyromancer's wand
                        else
                            iBonus = true;	//Unequip cryomancer's wand
                    }
                    else	//Staffs
                    {
                        pMAGIC = pMAGIC + (2*(pwepType - 16));	//+2 magic bonus
                        pATT = pATT + (pwepType - 15);	//+1 att bonus
                        if (pwepType == 19)	//Maelstrom staff
                        {
                            sBonus = true;	//10% no mana cost
                        }
                    }
                }
                else if (pClass == "Berserker")
                {
                    pATT = pATT + (3*(pwepType - 22));	//+3 att
                    if (pwepType == 26)	//Battleaxe
                    {
                        vBonus = true;	//+10% vampirism bonus per level
                    }
			}
			else	//paladin
			{
				pDEF = pDEF + (pwepType - 26)/2;	//+1 def every two weapons
				pATT = pATT + (pwepType - 26);	//+1 att
				if (pwepType >= 29)
					cpACC = cpACC + 5*((pwepType - 28));	//+5 acc on third and fourth weapon
				if (cpACC > 100)

				if(pwepType == 30)
				{
					hBonus = true;	//+10 heal bonus
				}
			}
			cout <<"You have equipped a/an " <<itemName[findItem];
			uCheck = true;
			}
        }else {
            cout <<"Cannot equip that weapon!\n";
            system("PAUSE");
            system("CLS");}
		}
		//If the player selects none
		else if (invCommand == 97)
		{
			tempWeapon = pwepType;
			pwepType = -1;
			pWep = "None";
			cout <<"You have unequipped\n";
			uCheck = true;
		}

					if (tempWeapon != -1)
					{
						//Stat bonus explanations below
						if (pClass == "Rogue")
						{
							pATT = pATT - (2*(tempWeapon - 11));
							cpACC = cpACC - (5*(tempWeapon - 12));
							if (tempWeapon == 15)
								pCritChance = pCritChance - 10;
						}
						else if (pClass == "Mage")
						{
							if ((tempWeapon > 19) && (tempWeapon < 23))
							{
								pMAGIC = pMAGIC - 10;
								if (tempWeapon == 20)
									mBonus = false;		//Unequip arcanomancer's wand
								else if (tempWeapon == 21)
									fBonus = false;		//Unequip pyromancer's wand
								else
									iBonus = false;	//Unequip cryomancer's wand
							}
							else
							{
								pMAGIC = pMAGIC - ((tempWeapon - 16)*2);
								pATT = pATT - (tempWeapon - 15);
								if (tempWeapon == 19)
								{
									sBonus = false;
								}
							}
						}
						else if (pClass == "Berserker")
						{
							pATT = pATT - (3*(tempWeapon - 22));
							if (tempWeapon == 26)
								vBonus = false;
						}
						else	//paladin
						{
							pDEF = pDEF - (tempWeapon - 26)/2;
							pATT = pATT - (tempWeapon - 26);
							cpACC = cpACC - 5*((tempWeapon - 27)/2);
							if(tempWeapon == 30)
							{
								hBonus = false;
							}
						}
						uPTurn = false;	//Shifts over to enemy after equipping
					}

		if ((pwepType == -1) && (tempWeapon != -1))
		{
			item[tempWeapon]++;
			tempWeapon = -1;
			uPTurn = false;	//Shifts over to the enemy
		}
		if (cpACC > 100)
			cpACC = 100;
		if (cpACC < 0)
			cpACC = 0;
		if (pCritChance > 100)
			pCritChance = 100;
		if (pCritChance < 0)
			pCritChance = 0;

		}while (uCheck == false);
		}

    cout << endl;

    if (montype != "Ganondorf") {
    if (uCommand == 53) {
             if (eBoss == true) {
                       cout << "This is a boss battle. You cannot escape!\n";
             } else {
                    pFlee = plvl - elvl + 5;
                    if (pFlee < 2) {
                              pFlee = 2;
                              }
                    uAcc = rand() %10 +1;
                    if (uAcc <= pFlee) {
                             uBattleover = true;
                             } else {
                                    cout << "You try to run away, but he catches right up!\n";
                                    }
                    }
             }
    }
              //Enemy move
    if ((uPTurn == true)&&(uBattleover == false)) {
 			if (bpBonus > 0)
			{
				if (bpBonus == 1)
				{
					bpBonus--;
					pATT--;
					pDEF = pDEF + 2;
					cout <<"\nThe berserk potion wears off\n";
				}
				else
				{
					bpBonus--;
					pATT--;
				}
				if (pATT < 0)	//In the event of a freak accident
					pATT = 0;
			}
			if (apBonus > 0)
			{
				if ((apBonus - 5) <= 0)	//In other words, last turn
				{
					pCritChance = pCritChance - apBonus;
					cpACC = cpACC - apBonus;
					apBonus = 0;
					pATT = pATT + 3;
					cout <<"\nThe accuracy potion wears off\n";
				}
				else
				{
					apBonus = apBonus - 5;
					pCritChance = pCritChance - 5;
					cpACC = cpACC - 5;
				}
				if (pACC < 0)	//In the event of a freak accident
					cpACC = 0;
				if (pCritChance < 0)	//In the event of a freak accident
					pCritChance = 0;
			}
			if (spBonus > 0)
			{
				if (spBonus == 1)
				{
					spBonus--;
					pMAGIC--;
					pDEF = pDEF + 2;
					cout <<"\nThe spell potion wears off\n";
				}
				else
				{
					spBonus--;
					pMAGIC--;
				}
				if (pMAGIC < 0)	//In the event of a freak accident
					pMAGIC = 0;
			}
			if (sDuration > 0)
			{
				sDuration--;
				cout <<"The storm rages!\n";
				ceHP = ceHP - 10;
			}
			if (iCrit > 0)
			{
				iCrit = iCrit - 10;
				if (iCrit == 0)
					cout <<"The jarate wears off\n";
			}


                uAcc = rand()%100 +1;
                if (pMHide == true) {
                           uAcc = 101;
                           }
                if (eConf == true) {
                          uAcc += 20;
                }
                if (eStun == true) {
						uAcc += 100;
                }


				if (ceHP <= 0)
 					cout << "With its dying breath, the " <<eType <<" prepares for a final attack\n";
                if (uAcc < ceACC) {
                         cout << "The " << eType << " hits you!" << endl;
                         if (eATT <= pDEF) {
                                  uAcc = rand()%3;
                                  if (uAcc == 1) {
                                     cout << "But it just scratches the polish on your armor!" << endl;
                                     } else if (uAcc == 2) {
                                            cout << "But it doesn't even hurt!" << endl;
                                            } else {
                                                   cout << "But you just shake off the feeble blow." << endl;
                                                   }
                         } else {
                                cpHP -= (eATT - pDEF);
                                ceACC-=2;
                                }
                } else {
                       cout << "The " << eType << " misses you. " << endl;
                       ceACC+=2;
                       }
            	if (eStun == true) {
					cout << "The enemy recovers from your blow.\n";
					eStun = false;
            	}


                cout << endl;
                   if (pPois == true) {
                     cout << "You lost health from the poison!" << endl << endl;
                     cpHP -= (eMAGIC/2 +1);
                     }
                   if (ePois == true) {
                     cout << "The enemy lost health from the poison!" << endl << endl;
                     ceHP -= (pMAGIC/2 +1);
                     }
                }

    if ((ceHP <= 0)&&(cpHP <= 0)) {
          victor = "nobody";
          uBattleover = true;
          uAcc = rand()%3;
          if (uAcc == 0) {
             cout << "You slay the " << eType << "! But you die." << endl;
          } else if (uAcc == 1) {
                    cout << "The two of you strike mortal blows! You kill the " << eType << "! But you die." << endl;
                    } else if (uAcc == 2) {
                           cout << "You kill the " << eType << "! But you're dead too." << endl;
                           } else {
                                  cout << "You kill each other..." << endl;
                                  }
    } else if (ceHP <= 0) {
         int rIt;
         int random;
		 victor = "player";
         uBattleover = true;
		 shopTimer++;
         cout << "You kill the " << eType << "!" << endl;
    	 winGold = rand()% (plvl*9 + 1) + plvl;	//1x level gold to 10x level gold
		 gold = gold + winGold;

		 cout <<"You find " <<winGold <<" gold from the monster\n";

				random = rand()% 100;	//5% weapon, 1% good weapon
				if (random < 5)	// 0 - 4
				{
					do
					{
						rIt = rand()% 19 + 12;	//12 - 31
					}while((rIt == 15) || (rIt == 19) || (rIt == 20) || (rIt == 21) || (rIt == 22) || (rIt == 26) || (rIt == 30));
					cout << "and 1 " << itemName[rIt] <<"\n";
					item[rIt]++;
				}
				else if (random == 5)	//Rare weapons
				{
					random = rand()% 7 + 1;
					if (random == 1)
						rIt = 15;
					else if (random == 2)
						rIt = 19;
					else if (random == 3)
						rIt = 20;
					else if (random == 4)
						rIt = 21;
					else if (random == 5)
						rIt = 22;
					else if (random == 6)
						rIt = 26;
					else
						rIt = 30;

					cout <<	"and 1 " << itemName[rIt] <<"\n";
					item[rIt]++;

				}
				random = rand()% 100;	//15% chance of items
				if (random < 15)
				{
					rIt = rand()% 12;
					cout <<"as well as 1 " << itemName[rIt];
					item[rIt]++;
				}

		 if (monster == "gold")
			qTrack = qTrack + winGold;
		 if (monster == eType)
		{
			if (questType == 1)
				qTrack++;
			else if (questType == 2)
			{
				int success = rand()% 2;
				if (success == 0)
					{
						cout <<"\n\nYou have collected a/an " << monster <<" " <<partName <<"\n";
						qTrack++;
					}
				else
					cout <<"\n\nUnfortunately you don't find what you were looking for\n";
			}
		}
    } else if (cpHP <= 0) {
         victor = eType;
         uBattleover = true;
         cout << "Argh! A fatal blow..." << endl << endl;
         cout << "You die. " << endl;
    } else if (uBattleover == true) {
		victor = "nobody";
       cout << "You flee from battle" << endl;
 		shopTimer++;   //Shop timer increases even if you run from battle
    }
    cout << endl;

    getch();

    } while (uBattleover == false);

	iCrit = 0;
	if (bpBonus > 0)	//Take away the buffs to make sure they're not permanent
	{
		pDEF = pDEF + 2;
		pATT = pATT - bpBonus;
		bpBonus = 0;
	}
	if (apBonus > 0)
	{
		//cpACC has been taken care of elswhere
		pCritChance = pCritChance - apBonus;
		apBonus = 0;
	}
	if (spBonus > 0)
	{
		pDEF = pDEF + 2;
		pMAGIC = pMAGIC - spBonus;
		spBonus = 0;
	}


	//"Unequip" weapon
	for (int counter = 12; counter < 30; counter++)
	{
		if (pWep == itemName[counter])
			item[counter]++;
	}
	tempWeapon = pwepType;
	if (tempWeapon != -1)
					{
						if (pClass == "Rogue")
						{
							pATT = pATT - (2*(tempWeapon - 11));
							cpACC = cpACC - (5*(tempWeapon - 12));
							if (tempWeapon == 15)
								pCritChance = pCritChance - 10;
						}
						else if (pClass == "Mage")
						{
							if ((tempWeapon > 19) && (tempWeapon < 23))
							{
								pMAGIC = pMAGIC - 10;
								if (tempWeapon == 20)
									mBonus = 0;		//Unequip arcanomancer's wand
								else if (tempWeapon == 21)
									fBonus = 0;		//Unequip pyromancer's wand
								else
									iBonus = 0;	//Unequip cryomancer's wand
							}
							else
							{
								pMAGIC = pMAGIC - ((tempWeapon - 16)*2);
								pATT = pATT - (tempWeapon - 15);
								if (tempWeapon == 22)
								{
									sBonus = false;
								}
							}
						}
						else if (pClass == "Berserker")
						{
							pATT = pATT - (3*(tempWeapon - 22));
							if (tempWeapon == 26)
								vBonus = 0;
						}
						else	//paladin
						{
							pDEF = pDEF - (tempWeapon - 26)/2;
							pATT = pATT - (tempWeapon - 26);
							cpACC = cpACC - 5*((tempWeapon - 27)/2);
							if(tempWeapon == 30)
							{
								hBonus = 0;	//10*plvl
							}
						}
					}
					system("PAUSE");

			tempWeapon = -1;
    system ("CLS");

    if (cpHP < 0) {
         cpHP = 0;
         }
    if (ceHP < 0) {
           ceHP = 0;
           }

    cout << "Player: HP: " << cpHP << "/" << pHP << ", ATTACK: " << pATT << ", ACCURACY: " << cpACC << endl;
    cout << "MAGIC: " << pMAGIC << ", DEFENSE: " << pDEF << endl;
    cout << "Class: " << pClass << endl << endl;
    cout << "Enemy: HP: " << ceHP << "/" << eHP << ", ATTACK: " << eATT << ", ACCURACY: " << eACC << endl;
    cout << "MAGIC: " << eMAGIC << ", DEFENSE: " << eDEF << endl << endl << endl;

    if (victor == "player") {victor = pName;}

    cout << "Victory goes to: " << victor << "." << endl << endl;

    if (victor == pName) {int rExp = rand()% 5 + 1; pExp = pExp + rExp;}
    if (eType == "dragon") {
              if (map == 1) {
                      d1Boss = true;
                      }
              if (map == 2) {
                      d2Boss = true;
                      }
              if (map == 3) {
                      d3Boss = true;
                      }
    moncounter++;
    }

    if (eType == "Ganondorf") {
        moncounter++;}

    didbattlehappen = true;

    }

    if (moncounter > 3) {
        cout << "Congrats! You beat the game!" << endl;
        cout << "A winner is " << pName << "!" << endl; //(Gramatically incorrect on purpose)"
        cout << pName << ", you have saved the land of Skyule!" << endl;
        cout << "You are awesome!" << endl;
        cout << "Thank you for putting Link out of business!" << endl;
    }


         // LEVELING UP
         //Player stat boni
    if (pExp > 29) {
          cout << "You have leveled up!" << endl;
          cout << "Abilities improved." << endl;
          plvl++;
          pHP += 2;
          pMP += 1;
          pATT += 1;
          pMAGIC += 1;
          pExp = 0;

          //Same deal here perhaps

          if (pClass == "Rogue") {
              pHP += 1;
              pMP += 3;
              pATT += 1;
          }
          if (pClass == "Mage") {
              pMAGIC += 1;
              pMP += 1;
          }
          if (pClass == "Berserker") {
              pHP += 2;
              if (plvl%2 == 0) {
                 pATT += 1;
                 }
          }
          if (pClass == "Paladin") {
             pHP += 2;
             if (plvl%2 == 0) {
                        pDEF += plvl/2;
                        pMP += plvl/2;
                        }
          }
          cpMP = pMP;
    }

    if (tertype == '#') {
        quote(pName);
        cout <<"1) Inn (30 gold)\n2) Wanted board\n3) Shop\n4) Help\n5) Save\n";
    }

    keystroke = getch();

    cout << keystroke << endl;

    if ((map == 0)&&(locatey > 0)&&(keystroke == 'w')&&(mainmapmatrix[locatex][locatey-1] != '~')) {
        locatey = locatey - 1;
    }

    if ((map == 0)&&(locatey < 11)&&(keystroke == 's')&&(mainmapmatrix[locatex][locatey+1] != '~')) {
        locatey = locatey + 1;
    }

    if ((map == 0)&&(locatex < 13)&&(keystroke == 'd')&&(mainmapmatrix[locatex+1][locatey] != '~')) {
        locatex = locatex + 1;
    }

    if ((map == 0)&&(locatex > 0)&&(keystroke == 'a')&&(mainmapmatrix[locatex-1][locatey] != '~')) {
        locatex = locatex - 1;
    }

    if ((map > 0)&&(locatey > 0)&&(keystroke == 'w')) {
        if (((map == 1)&&(dun1matrix[locatex][locatey-1] != '~')&&(dun1matrix[locatex][locatey-1] != '-'))||
            ((map == 2)&&(dun2matrix[locatex][locatey-1] != '~')&&(dun2matrix[locatex][locatey-1] != '-'))||
            ((map == 3)&&(dun3matrix[locatex][locatey-1] != '~')&&(dun3matrix[locatex][locatey-1] != '-'))) {
            locatey = locatey - 1;
        }
    }

    if ((map > 0)&&(locatey < 6)&&(keystroke == 's')) {
        if (((map == 1)&&(dun1matrix[locatex][locatey+1] != '~')&&(dun1matrix[locatex][locatey+1] != '-'))||
            ((map == 2)&&(dun2matrix[locatex][locatey+1] != '~')&&(dun2matrix[locatex][locatey+1] != '-'))||
            ((map == 3)&&(dun3matrix[locatex][locatey+1] != '~')&&(dun3matrix[locatex][locatey+1] != '-'))) {
            locatey = locatey + 1;
        }
    }

    if ((map > 0)&&(locatex < 4)&&(keystroke == 'd')) {
        if (((map == 1)&&(dun1matrix[locatex+1][locatey] != '~')&&(dun1matrix[locatex+1][locatey] != '-'))||
            ((map == 2)&&(dun2matrix[locatex+1][locatey] != '~')&&(dun2matrix[locatex+1][locatey] != '-'))||
            ((map == 3)&&(dun3matrix[locatex+1][locatey] != '~')&&(dun3matrix[locatex+1][locatey] != '-'))) {
            locatex = locatex + 1;
        }
    }

    if ((map > 0)&&(locatex > 0)&&(keystroke == 'a')) {
        if (((map == 1)&&(dun1matrix[locatex-1][locatey] != '~')&&(dun1matrix[locatex-1][locatey] != '-'))||
            ((map == 2)&&(dun2matrix[locatex-1][locatey] != '~')&&(dun2matrix[locatex-1][locatey] != '-'))||
            ((map == 3)&&(dun3matrix[locatex-1][locatey] != '~')&&(dun3matrix[locatex-1][locatey] != '-'))) {
            locatex = locatex - 1;
        }
    }

    if ((map == 0)&&(locatex == 7)&&(locatey == 2)) {                   //dungeon 1
        if (keystroke == 'e') {map = 1;
            locatex = 2;
            locatey = 6;
            keystroke = ']';
        }
    }

    if ((map == 1)&&(locatex == 2)&&(locatey == 6)) {                  //dungeon 1 exit
        if (keystroke == 'e') {map = 0;
            locatex = 7;
            locatey = 2;
            keystroke = ']';
        }
    }

    if ((map == 0)&&(locatex == 11)&&(locatey == 9)) {                 //dungeon 2
        if (keystroke == 'e') {map = 2;
            locatex = 0;
            locatey = 6;
            keystroke = ']';
        }
    }

    if ((map == 2)&&(locatex == 0)&&(locatey == 6)) {                  //dungeon 2 exit
        if (keystroke == 'e') {map = 0;
            locatex = 11;
            locatey = 9;
            keystroke = ']';
        }
    }

    if ((map == 0)&&(locatex == 1)&&(locatey == 10)) {                 //dungeon 3
        if (keystroke == 'e') {map = 3;
            locatex = 3;
            locatey = 6;
            keystroke = ']';
        }
    }

    if ((map == 3)&&(locatex == 3)&&(locatey == 6)) {                 //dungeon 3 exit
        if (keystroke == 'e') {map = 0;
            locatex = 1;
            locatey = 10;
            keystroke = ']';
        }
    }

    if (keystroke == 'h') {
        keystroke = getch();
        if (keystroke == 'e') {
            keystroke = getch();
            if (keystroke == 'l') {
                keystroke = getch();
                if (keystroke == 'p') {
                    help();
                }
            }
        }
    }

    if (tertype == '#')
    {
        if (keystroke == '1')
        {
            if (gold >= 30)
            {
                cout <<"\n\nYou've rested up at the inn\n";
                cpHP = pHP;
                cpMP = pMP;
                gold = gold - 30;
                system("PAUSE");
            }
            else
            {
                cout <<"\nNot enough gold!\n";
                system("PAUSE");
            }
        }
        if (keystroke == '2')
        {
            cout <<"You come across a notice board\nDo you wish to look at it (y/n)?\n";
            //This is how to look at the current quest. Changes every time it's looked at

            do	//Error trapping
            {
                choice = getch();
                choice = toupper(choice);
            } while ((choice != 'Y') && (choice != 'N'));

            if ((choice == 'Y') && (monster == "None"))	//If the person chooses yes and isn't currently on a quest (i.e. monster = none).
            {
                questType = rand()% 3;	//Can have a quest to kill, a quest to collect or no quest at all

                if (questType == 0)
                    cout <<"There is nothing to do at the moment\n";
                else if (questType == 1)	//Killing monsters
                {
                    quantity = rand()% plvl + (plvl*15)/10;
                    monsterType = rand()% 5; //The 5 types of monsters

					cout <<"Kill ";
					if (monsterType == 0)
					{
						monster = "orc";
						cout << quantity <<" " << monster;
						if (quantity > 1)
							cout <<"s";
					}
					if (monsterType == 1)
					{
						monster = "goblin";
						cout << quantity <<" " << monster;
						if (quantity > 1)
							cout <<"s";
					}
					if (monsterType == 2)
					{
						monster = "elf";
						cout << quantity <<" " ;
					if (quantity > 1)
						cout <<"elves";
					else
						cout << monster;
					}
 				   if (monsterType == 3)
					{
						monster = "human";
						cout << quantity <<" " << monster;
						if (quantity > 1)
							cout <<"s";
						cout <<"\nSounds odd, but do it anyways\n";
					}
					if (monsterType == 4)
					{
                        monster = "giant";
                        cout << quantity <<" " << monster;
                        if (quantity > 1)
                            cout <<"s";
					}
					cout <<"\n";
			}
			else if (questType == 2)	//Collect quest
			{
				monsterType = rand()% 6;	//5 is gold
				if (monsterType == 5)
					{
						quantity = rand()% ((plvl*35) - (plvl*15) + 1) + (plvl*15);
						monster = "gold";
						partName = "(currency)";
					}
				else
					quantity = rand()% ((plvl*15)/10 - plvl + 1) + plvl;

				if (monsterType != 5)
				{
					part = rand()% 10;
					if (part == 0)
						partName = "ear";
					else if (part == 1)
						partName = "head";
					else if (part == 2)
						partName = "bone";
					else if (part == 3)
						partName = "sword";
					else if (part == 4)
						partName = "shield";
					else if (part == 5)
						partName = "wand";
					else if (part == 6)
						partName = "hat";
					else if (part == 7)
						partName = "bow";
					else if (part == 8)
						partName = "spear";
					else if (part == 9)
						partName = "rune";
				}

				cout <<"Collect " <<quantity <<" ";

				if (monsterType == 0)
				{
					monster = "orc";
				}
				else if (monsterType == 1)
				{
					monster = "goblin";
				}
				else if (monsterType == 2)
				{
					monster = "elf";
				}
				else if (monsterType == 3)
				{
					monster = "human";
				}
				else if (monsterType == 4)
				{
					monster = "giant";
				}

				cout <<monster <<" " <<partName;
				if ((quantity > 1) && (monster != "gold"))
					cout <<"s";
				if ((part < 3) && (partName != ""))
					cout <<"\nThey're a delicacy";
				cout <<"\n";
			}
			system("PAUSE");	//For now
		}
		else if ((choice != 'N') && (monster != "None") && (qTrack < quantity))
        //If you want, I can make it so that the program repeats the quest required.
		{
			cout <<"You're already on a quest!\n";
			system("PAUSE");
		}
			if ((qTrack >= quantity) && (questType != 0))	//The condition of the quest must be met
			{
				int number, rGold = 0, rExp, rIt = 0, random;	//random +4 = item, +1 = weapon, +3 = stat

				questType = 0;
				monster = "None";	//Resets the quest

				cout <<"\nQuest completed!\nYou have gained the following:\n";

				random = rand()% 20 + 1;	//10% weapon, 5% good weapon
				if ((random == 1) || (random == 2))
				{
					do
					{
						rIt = rand()% 19 + 12;	//12 - 31
					}while((rIt == 15) || (rIt == 19) || (rIt == 20) || (rIt == 21) || (rIt == 22) || (rIt == 26) || (rIt == 30));
					cout << "- 1 " << itemName[rIt] <<"\n";
					item[rIt]++;
				}
				else if (random == 3)	//Rare weapons
				{
					random = rand()% 7 + 1;
					if (random == 1)
						rIt = 15;
					else if (random == 2)
						rIt = 19;
					else if (random == 3)
						rIt = 20;
					else if (random == 4)
						rIt = 21;
					else if (random == 5)
						rIt = 22;
					else if (random == 6)
						rIt = 26;
					else
						rIt = 30;

					cout <<	"- 1 " << itemName[rIt] <<" Lucky you!\n";
					item[rIt]++;

				}

				random = rand()% 4 + 1;	//25% chance of items
				if (random == 1) //Random
				{
					rIt = rand()% 12;
					number = rand()% 3 + 1;
					if (rIt == 2)
					{
						number = 1;	//1 elixir awarded
					}
					cout <<"- "<<number <<" " << itemName[rIt];
					if (number > 1)
						cout <<"s";
					cout <<"\n";
					item[rIt] = item[rIt] + number;
				}

				random = rand()% 5 + 1;	//20% chance of stat bonus
				if (random == 1)
				{
					random = rand()% 6 + 1;
					number = rand() % 3 + 1;
					if (random == 1)
					{
						cout <<"- Hp has increased by " << number << "\n";
						pHP = pHP + number;
					}
					else if (random == 2)
					{
						cout <<"- Mp has increased by " << number <<"\n";
						pMP = pMP + number;
					}
					else if (random == 3)
					{
						cout <<"- Critical chance has increased by " << number <<"\n";
						pCritChance = pCritChance + number;
						if (pCritChance > 100)
							pCritChance = 100;

					}
					else if (random == 4)
					{
						cout <<"- Your defense has increased by 1\n";
						pDEF++;
					}
					else if (random == 5)
					{
						cout <<"- Your attack has increased by 1\n";
						pATT++;
					}
					else
					{
						cout <<"- Your magic attack has increased by 1\n";
						pMAGIC++;
					}

				}
				number = rand()% ((plvl*5)- plvl*3) + (plvl*3);	//30 - 50x the level exp
				cout <<"- " <<number <<" experience\n";
				pExp = pExp + number;

				number = rand()% ((plvl*25) - plvl*10) + (plvl*10);	//10 - 25x the level gold
				cout <<"- " <<number <<" gold\n";
				gold = gold + number;

				system("PAUSE");
			}
	}

    if (keystroke == '3') { // NEW SHOP SYSTEM
        cout << "Welcome to the shop!" << endl;
        cout << "Hey, try buying something from me!" << endl;

        if(shopTimer >= 3)	//"Refreshes" after 3 or more monster battles
        {
            shopTimer = 0;
            for (int counter = 0; counter < 5; counter++)
            {
                do {                              //Prevents same item from coming up twice
                    uCommand = rand()%11+1;
                } while ((uCommand == shopItems[counter- 1])||(uCommand == shopItems[counter- 2])||
                         (uCommand == shopItems[counter- 3])||(uCommand == shopItems[counter- 4]));
                shopItems[counter] = uCommand; 	//Store the item number of available items
            }
        }

        for (int counter = 0; counter < 5; counter++) {
            cout << counter + 1 << ":" << itemName[shopItems[counter]] << endl;                         //Outputs names of available items
            cout << " Cost: " << howmuchcost(itemName, itemName[shopItems[counter]], 1) << " Gold" << endl;                //Outputs the costs of the available items
        }

        cout <<"6: Sell\n7: Exit\n";

        do        //Error trapping
        {
            uCommand = getch();
            uCommand = uCommand - 49;
        }while ((uCommand < 0) || (uCommand > 6));

        if (uCommand == 5)
        {
            cout <<"Sell what?\n";
            inventorySelect = 97;	//Starts at a

            for (int counter = 0; counter < 31; counter++)
            {
                if (item[counter] > 0)
                {
                    cout <<inventorySelect <<") " <<itemName[counter] <<"\n";
                    inventorySelect++;	//Then b, then c etc.
                }
            }
            cout <<inventorySelect <<") Exit\n";

            do
            {
                uCommand = getch();
            }while ((uCommand < 97) || (uCommand > inventorySelect));

            if (uCommand != inventorySelect)	//Turns out you could use a char as an integer
            {
                char confirm;
                inventorySelect = 97;

                for (int counter = 0; counter < 31; counter++)
                {
                    if (item[counter] > 0)
                    {
                        if (inventorySelect == uCommand)
                            findItem = counter;
                        inventorySelect++;
                    }
                }
                uCommand = uCommand - 97;
                cout <<"Are you sure you want to sell a/an " << itemName[findItem] <<" for "<<howmuchcost(itemName, itemName[findItem], 2) <<" gold (y/n)?\n";

                do
                {
                    confirm = getch();
                    confirm = toupper(confirm);
                } while ((confirm != 'Y') && (confirm != 'N'));

                if (confirm == 'Y')
                {
                    item[findItem]--;
                    gold = gold + howmuchcost(itemName, itemName[findItem], 2);
                    cout <<"You have sold a/an " <<itemName[findItem] <<".\n";
                }
            }

        }
        else if (uCommand != 6)
        {
            if (gold - howmuchcost(itemName, itemName[shopItems[uCommand]], 1) > 0) {          //checks for enough gold
                if (uCommand == 0) {
                    item[shopItems[0]]++;
                }                              //Increase items you have
                if (uCommand == 1) {
                    item[shopItems[1]]++;
                }
                if (uCommand == 2) {
                    item[shopItems[2]]++;
                }
                if (uCommand == 3) {
                    item[shopItems[3]]++;
                }
                if (uCommand == 4) {
                    item[shopItems[4]]++;
                }

                cout << "Cost: " << howmuchcost(itemName, itemName[shopItems[uCommand]], 1) << endl;       //Confirms costs
                gold = gold - howmuchcost(itemName, itemName[shopItems[uCommand]], 1);                   //Subtract gold
                cout << "You bought a " << itemName[shopItems[uCommand]] << endl;       //Confirms buying
            } else {
                cout << "You don't have enough gold!" << endl;             //Not enough gold
            }
        }
            system("PAUSE");
            }
            if (keystroke == '4')
                help();
            if (keystroke == '5')
            {
				char choice;
				cout <<"Are you sure? You will overwrite your current save file (y/n)\n";
				do
				{
					cin >> choice;
					choice = toupper(choice);
				} while ((choice != 'Y') && (choice != 'N'));

				if (choice == 'Y')
				{
					save.open("Load.txt");
					//Saves the item and weapon names and quantity
					for(int counter = 0; counter < 31; counter++)
					{
						save << item[counter];
						save << itemName[counter];
						save <<"\n";
					}	//DO NOT FORGET THE FOR LOOP TO RETURN ALL ITEMS TO 0.

						save << pName <<"\n";
						save << pClass <<"\n" << plvl <<"\n" <<gold <<"\n" <<pExp <<"\n" << questType <<"\n";
						save << monster <<"\n" << partName <<"\n" << quantity <<"\n" << qTrack <<"\n" << pHP <<"\n" << cpHP <<"\n";
						save <<pMP <<"\n" <<cpMP <<"\n" <<pATT <<"\n" <<pMAGIC <<"\n" << pDEF <<"\n" << pACC <<"\n" << pCritChance <<"\n";
						save << d1Boss <<"\n" << d2Boss <<"\n" << d3Boss <<"\n" << moncounter;
					save.close();
				}
		  }
    }

    if (keystroke == 'i') {

        inventorySelect = 96;

        cout <<"ITEMS\n";	//Output the items available
        for(int counter = 0; counter < 31; counter++)
        {
            if (counter == 11)
                cout <<"WEAPONS\n";

            if (item[counter] > 0)
            {
                if ((counter >= 0) && (counter < 3))
                {
                    inventorySelect++;	//Lists the items
                    cout <<inventorySelect <<") ";
                }
                cout << itemName[counter] << ": " <<item[counter] <<"\n";
            }
        }
        inventorySelect++;	//Lists the items
        cout << inventorySelect <<") Exit";

		cout <<"\nWhat item do you wish to use (type in the number)?\n";

		//User input
        do
		{
            invCommand = getch();
		}while ((invCommand > inventorySelect) || (invCommand < 97));

		if (invCommand != inventorySelect)	//Which is exit
		{
			inventorySelect = 97;	//Restarts the list and compares it to the number the player selected
			findItem = -1;	//Because if findItem == 0, it could select the healthpotion
			for(int counter = 0; counter < 12; counter++)
			{
				if (item[counter] > 0)
				{
					if(inventorySelect == invCommand)
					//If the list number and the user input are the same, it means the user selected that item
                    {
                        findItem = counter;	//Used like item[counter]
                    }
                    inventorySelect++;
				}
			}

			if (findItem > 11)	//If the item is not found yet
			{
				cout <<"Cannot equip while out of battle\n";
			}
			else
			{
				cout << "You have used a/an " << itemName[findItem] <<"\n";	//If it's an item
				item[findItem]--;
			}
			getch();
		}
        }

        if (keystroke == 'g') {
        cout << "WARNING: THE FOLLOWING MODE IS FOR DEBUGGING ONLY" << endl;
            keystroke = getch();
            if (keystroke == 'm') {
                monlimit = 0;
                moncounter = 3;
                cout << "GOD MODE TURN ON" << endl;
                getch();
            }
        }

        if (keystroke == 'n') {
            cout << "YOU ARE ABOUT TO TURN OFF GOD MODE" << endl;
            keystroke = getch();
            if (keystroke == 'm') {
                monlimit = 2;
                cout << "GOD MODE TURN OFF" << endl;
                getch();
            }
        }

    } while ((keystroke != 'q')&&(cpHP > 0)&&(moncounter < 4));

    if (moncounter >= 4)	//Once the player completely beats the game. They can still keep their name
	{
		moncounter = 0;
		d1Boss = false;
		d2Boss = false;
		d3Boss = false;
		pClass = "Rogue";
		plvl = 1; gold = 0; pExp = 0; questType = 0; monster = "None"; partName = ".";
		quantity = 0; qTrack = 0; pHP = 30; cpHP = 30; pMP = 4; cpMP = 4; pATT = 6; pDEF = 1; pACC = 80; pCritChance = 10; pMAGIC = 2;

		cout <<"Time to start a new journey!\n";
		save.open("Load.txt");
		//Saves the item and weapon names and quantity
		for(int counter = 0; counter < 31; counter++)
		{
			save << item[counter];
			save << itemName[counter];
			save <<"\n";
		}

		save << pName <<"\n";
		save << pClass <<"\n" << plvl <<"\n" <<gold <<"\n" <<pExp <<"\n" << questType <<"\n";
		save << monster <<"\n" << partName <<"\n" << quantity <<"\n" << qTrack <<"\n" << pHP <<"\n" << cpHP <<"\n";
		save <<pMP <<"\n" <<cpMP <<"\n" <<pATT <<"\n" <<pMAGIC <<"\n" << pDEF <<"\n" << pACC <<"\n" << pCritChance <<"\n";
		save << d1Boss <<"\n" << d2Boss <<"\n" << d3Boss <<"\n" << moncounter;
		save.close();
    }
    system("PAUSE");

//End of program

}
