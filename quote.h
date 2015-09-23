/*
File name: quote.h
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

#ifndef QUOTE_H
#define QUOTE_H

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void quote(string pName)
{

    int quote;

	quote = rand()% 23 + 1;

	if (quote == 1)
		cout <<"\nWelcome " << pName << ", to Skyule Castle Town!\n\n";
	else if (quote == 2)
		cout <<"\nGuard: I used to be an adventurer like you. Then I took an arrow in the knee.\n\n";
	else if (quote == 3) {
		cout <<"\nScout: There are three caves throughout this land, but no one knows what's\n";
        cout <<"inside them.\n\n";}
	else if (quote == 4)
		cout <<"\nDruid: Come visit our zoo sometime! We've got a special exhibit of orcs today.\n\n";
	else if (quote == 5)
		cout <<"\nA thief tries to steal your gold. Nice greeting.\n\n";
	else if (quote == 6) {
		cout <<"\nMerchant: Need gold? Try robbing it from monsters that you kill! That's how I\n";
        cout <<"got rich.\n\n";}
	else if (quote == 7)
		cout <<"\nCompiler: Staring at the screen may be harmful to your eyes.\n\n";
	else if (quote == 8)
		cout <<"\nIsaac: Steven lives.\n\n";
	else if (quote == 9)
		cout <<"\nPaladin: A town in the middle of nowhere? Seems strange, doesn't it?\n\n";
	else if (quote == 10)
		cout <<"\nGuard: Unfortunately the princess is in another castle town.\n\n";
	else if (quote == 11)
		cout <<"\nGuard: The only trolls here are the ones under a bridge.\n\n";
	else if (quote == 12)
		cout <<"\nERROR: I AM ERROR\n\n";
	else if (quote == 13)
		cout <<"\nTwitter n.- The sound a bird makes; the sound an elf makes as it falls to your  weapon.\n\n";
	else if (quote == 14)
		cout <<"\n" << pName << ", I heard you had a good computer, but can it run Text Adventures?\n\n";
	else if (quote == 15)
		cout <<"\nCaptain Falcon: Show me your moves!\n\n";
	else if (quote == 16)
		cout <<"\nRogue: Our town's mascot is a sturgeon.\n\n";
	else if (quote == 17)
		cout <<"\nMage: Where alchemy will be the thing of the past!\n\n";
	else if (quote == 18)
		cout <<"\nMerchant: What? You don't accept cheques? Only gold?\n\n";
	else if (quote == 19)
		cout <<"\nTony: Muahahahaha!! This game is no match for my l33t hacks!!\n\n";
	else if (quote == 20) {
		cout <<"\nTony: Hey, " << pName << "! Do you suck at this game? Enter ''GM'' to enable god mode,\n";
        cout <<" ''PM'' to disable it. However, if you choose to use this mode, you'll be a\n";
        cout <<"n00b forever!\n\n";
    }
	else if (quote == 21)
		cout <<"\nTony: " << pName << ", did you hear? There's some guy going around randomly shooting arrows into people's knees.\n\n";
	else if (quote == 22) {
		cout <<"\nSasuke: You there! " << pName <<"! Annoyed that enemies just randomly appear? With the\n";
        cout <<"sharingan, you don't have to worry.\n\n";
    }
	else
		cout <<"\nTony: I beat this already!! You have not!!\n\n";
    return;
}
#endif
