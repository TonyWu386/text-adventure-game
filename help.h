/*
File name: help.h
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

#ifndef HELP_H
#define HELP_H

#include <iostream>
#include <string.h>
#include <time.h>
#include <windows.h>

using namespace std;

void help() {

    string select;

    do {
        system ("CLS");
        cout << " ==== HELP ==== \n\n" ;
        select = "0";
        if (select == "0") {
            cout << " (1) Backstory \n";
            cout << " (2) Navigation, map locations, and menus\n";
            cout << " (3) Battles and spells\n";
            cout << " (4) NPCs and Quests\n";
            cout << " (5) Main menu\n\n";
            cout << " >> ";
            select = getch();
        }
        if (select == "1") {
            cout << "You control a Skylian, who is seeking to defeat the restaurant owner, \n"; Sleep(100);
            cout << "Ganondorf, who has caused chaos in the land of Skyule. He has ruined many lives \n"; Sleep(50);
            cout << "with his bad-tasting and overpriced food. Eventually, he left Skyule Castletown. \n"; Sleep(50);
            cout << "He now lurks in the north-west of the region.\n\n"; Sleep(50);
            system("PAUSE");
            select = "0";
        }
        if (select == "2") {
            cout << "To move around, use the W (north), A (west), S (south), and D (east) keys.\n"; Sleep(50);
            cout << "Use E to enter or exit a dungeon. \n\n"; Sleep(50);
            cout << "   .     grassy land\n"; Sleep(100);
            cout << "   =     swamp\n"; Sleep(100);
            cout << "   ~     rivers \n";Sleep(100);
            cout << "   ^     hills \n";Sleep(100);
            cout << "   M     mountains \n";Sleep(100);
            cout << "   n     the entrance to a dungeon\n";Sleep(100);
            cout << "   -     wall (only found within dungeons)";Sleep(100);
            cout << "   #     Skyule Castletown\n\n"; Sleep(100);
            system ("PAUSE");
            system ("CLS");
            cout << " ==== HELP ==== \n\n" ; Sleep(50);
            cout << "Your inventory contains all the items your character has collected over \n";Sleep(50);
            cout << "the course of his adventurers. To check your inventory, press 'i'\n\n"; Sleep(50);
            system ("PAUSE");
            select = "0";
        }
        if (select == "3") {
            cout << "As you walk around the map you might encounter some unfriendly folks.\n"; Sleep(50);
            cout << "Before you enter battle, you are prompted to choose a weapon. It's highly\n"; Sleep(50);
            cout << "suggested you do.\n"; Sleep(300);
            cout << "If you do enter battle, you and the enemy will take turns performing  \n"; Sleep(50);
            cout << "actions and ultimately trying to kill the other. Each turn you can:\n\n"; Sleep(50);
            cout << " 1)Attack:        You try to hit the enemy. If you land a hit, imagine a \n"; Sleep(50);
            cout << "                   satisfying 'THUMP' sound. If you miss, imagine a \n"; Sleep(50);
            cout << "                   'WHOOSH' sound. Higher accuracy will make it much\n"; Sleep(50);
            cout << "                   easier to hit. Each blow will deal some damage to the \n"; Sleep(50);
            cout << "                   enemy's Hit Points (HP) until they die from their \n"; Sleep(50);
            cout << "                   wounds. The higher your Attack stat is, the greater\n"; Sleep(50);
            cout << "                   the damage you will deal. The greater the enemy's \n"; Sleep(50);
            cout << "                   defence, the less damage they'll take. \n\n"; Sleep(100);
            system ("PAUSE");
            cout << "\n\n 2)Cast a spell:  You try to do some magic. Mages begin the game with\n"; Sleep(50);
            cout << "                   knowledge of magic; all other classes can only cast\n"; Sleep(50);
            cout << "                   spells when they are a higher level. Magic uses up\n"; Sleep(50);
            cout << "                   Mana Points (MP) and if you want to cast a high cost \n"; Sleep(50);
            cout << "                   spell you will need more. Learn what spells do by \n"; Sleep(50);
            cout << "                   using them in battle!\n\n"; Sleep(100);
            system ("PAUSE");
            cout << " 3)Use an item:   If you have an item like a Health Potion you can use\n"; Sleep(50);
            cout << "                   it in battle with this command. \n\n"; Sleep(50);
            system ("PAUSE");
            cout << " 4)Switch weapon: If you have another weapon you would like to use you\n"; Sleep(50);
            cout << "                   can choose to use it instead with this command. \n\n"; Sleep(50);
            system ("PAUSE");
            cout << " 5)Flee/Run:      You run away as fast as possible. Doesn't work \n"; Sleep (50);
            cout << "                   occasionally.\n\n"; Sleep (200);
            system ("PAUSE");
            select = "0";
        }
        if (select == "4") {
            cout << "There are people in Skyule Castletown you can talk to! If you engage in \n"; Sleep(50);
            cout << "friendly conversation with an NPC, they may offer to sell you useful \n"; Sleep(50);
            cout << "stuff or perhaps give you a quest. If you do what they ask of you\n"; Sleep(50);
            cout << "you could get something nice in return.\n"; Sleep(50);
            cout << "If you are offered an item and have enough gold, you can buy it. \n"; Sleep(50);
            cout << "Do quests or kill monsters to get some money.\n\n"; Sleep(50);
            system ("PAUSE");
            select = "0";
        }
    } while (select != "5");


    cout << endl << endl;
    system ("PAUSE");
}

#endif
