// ConsoleApplication6.cpp : Defines the entry point for the console application.
//

//cin >> moveRight;
/*
How I precieve the game. the game is like grid with coridantes (x,y). so the screen size is pretty mcuh the array size in sqaures. ie. (20x40y)
all assests on the screen have array coridantes. they can move freely through out the array i.e (1x2y -> 1x4y)

movment is acheievd by moving the asset to the next array cell in the direction they wish to go. so to move right the x value increase, to move left x value decreses. then up and down or the same with y.
GetAsyncKeyState() reconizes keystokes based on hexidecimal.

collision check is acheived by checking whats around our player asset. so we can check the sqaures around him to see if it is empty before moving. depending on whats inside he lose health, etc.
all movment must be done at once and in sequnce. i.e) always move the map first, then the player, project tile,enemey, etc. smae constant flow to make collison dectetion not fuck up.

camera movement can be achieved by moving the map elemnts on a fixed interval(counter).

for efficiency we will move to a double buffer system rather than our current system(clear). do a second check to see what squares need to changed to achieve new frame
*/

// play around with some things to see how it would works coding wise
//http://www.cs.uah.edu/~rcoleman/Common/C_Reference/C++%20For%20DUMMIES.pdf link to C++ for dummies book, I've always found these great for learning
#include "stdafx.h"
#include<string>
#include<iostream>
#include <windows.h>
#include <memory>
using namespace std;
string moveRight;
int counterRIGHT(3); int counterLEFT(3);
string* empolyeeType = new string[80];



int main()

{
	
	while (true) {
	
		if (GetAsyncKeyState(68/*d on keyborad uses hex*/)) {
			counterRIGHT++;
			//counter to see how long the user is pressing the d key, moving it based on that. pretty much how much is pressing key move it that much
			//should be one counters shared for left and right. when i used tow diffent counters left started form 0
			//with one shared counter should start from where the right one left off when moving left and vice versa
			
			//made the i is 1 value greate than the counter (cells start at 0)
			for (int i = counterRIGHT-1; i != counterRIGHT; i++)
			{
				system("CLS");
				cout << empolyeeType[40];
				empolyeeType[i]= "--@@->>";
				empolyeeType[40] = "<{+}>"; 

				if (empolyeeType[i+1] == "<{+}>"){
					cout << "death" <<endl;
					system("pause");
					break;
				}
				if (i > 1) 
					empolyeeType[i - 1] = " ";

					for (int n = 1; n != i; n++)
					{
						cout << empolyeeType[n];
						//cout << empolyeeType[40];

					}

					cout << empolyeeType[i];
					

				}

			}
		}
		
		
	
	//pause program for readabilty
	system("pause");
	//reurn 0 to see if program ran succesfully
    return 0;
}

