// ACM.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

struct CPlayer
{
       int x;
       int y;
       int choice;
int prev[2];
};

struct Surroundings
{
       char North;
       char East;
       char South;
       char West;
};

int MapIndex( int x, int y );

Surroundings GetSurroundings( int x, int y, char [] );
int GetPlayerChoice();


int main( int argc, char* argv[] )
{
       bool Victory = false;
const unsigned int MAP_MAX_INDEX = 100;
       char Map[MAP_MAX_INDEX] = {	'X', ' ' , 'X', '#' , 'X', 'X' , 'X', 'X' , 'X', 'X' ,
'X', ' ' , 'X', ' ' , 'X', '#' , ' ', 'X' , '#', ' ' , 
'#', ' ' , 'X', ' ' , 'X', 'X' , ' ', 'X' , 'X', ' ' , 
'X', ' ' , ' ', ' ' , 'S', ' ' , ' ', 'X' , ' ', ' ' , 
'X', 'X' , 'X', ' ' , 'X', 'X' , ' ', 'X' , 'X', ' ' , 
' ', ' ' , ' ', ' ' , ' ', 'X' , ' ', ' ' , ' ', ' ' , 
' ', 'X' , 'X', 'X' , ' ', 'X' , ' ', 'X' , ' ', 'X' , 
' ', ' ' , 'W', 'X' , ' ', 'X' , ' ', 'X' , ' ', 'X' , 
'X', 'X' , 'X', 'X' , ' ', 'X' , '#', 'X' , ' ', 'X' , 
'X', '#' , ' ', ' ' , ' ', '#' , 'X', ' ' , ' ', '#' };
       char Tile = 'X';
int mi = 0, MapWidth = sqrt(MAP_MAX_INDEX);
       //char North, South, East, West;
       CPlayer Player;
       Surroundings PlayerSurroundings;
       cout << "Welcome to The Game!! woooo!" << endl;


       // Place the player at the start tile by looping through each tile until we find the S.
       for( int i = 0; i<MAP_MAX_INDEX; i++ )
{
if( Map[i] == 'S' )
{

Player.x = (i % MapWidth);
Player.y = (i / MapWidth);
}

}
       while( !Victory )
       {

               // Find out what is around the player
               PlayerSurroundings = GetSurroundings( Player.x, Player.y, Map );
               // Display the the options for the player
               cout << "Please type the number for the direction you wish to travel and press enter: " << endl;
               // Determine where the player can go and options. For now we only have walls to block us.
               if ( PlayerSurroundings.North != 'X' )
               {
                       // North is not a wall.
                       cout << "1: North." << endl;
               }
               if ( PlayerSurroundings.East != 'X' )
               {
                       cout << "2: East." << endl;
               }
               if ( PlayerSurroundings.South != 'X' )
               {
                       cout << "3: South." << endl;
               }
               if ( PlayerSurroundings.West != 'X' )
               {
                       cout << "4: West." << endl;
               }
               
               // Let the player choose his direction.
               cin >> Player.choice;
               // interpret the CPlayer.choice into a char from the map... Tile = map(choice)
Player.prev[0]=Player.x;
Player.prev[1]=Player.y;
mi = MapIndex(Player.x, Player.y);
switch( Player.choice )
               {
               case 1:
                   // Player choose to go North;
                   Player.y --;
// check for array out of bounds
Tile = ( mi < 0 || mi >= MAP_MAX_INDEX ) ? 'X' : Map[ MapIndex(Player.x, Player.y) ];
                   break;
               case 2:
                   // Player choose to go East;
                   Player.x++;
                   Tile = ( mi < 0 || mi >= MAP_MAX_INDEX ) ? 'X' : Map[ MapIndex(Player.x, Player.y) ];
                   break;
               case 3:
                   // Player choose to go South;
                   Player.y++;
                   Tile = ( mi < 0 || mi >= MAP_MAX_INDEX ) ? 'X' : Map[ MapIndex(Player.x, Player.y) ];
                   break;
               case 4:
                   // Player choose to go West;
                   Player.x--;
                   Tile = ( mi < 0 || mi >= MAP_MAX_INDEX ) ? 'X' : Map[ MapIndex(Player.x, Player.y) ];
                   break;
default:
Tile = ( mi < 0 || mi >= MAP_MAX_INDEX ) ? 'X' : Map[ MapIndex(Player.x, Player.y) ];
break;
               }
               
               switch(Tile){
               case '#':
                   cout << "This is a trap! You are history my friend." << endl;
                   Victory = true; // Actually hes dead. but we need to exit the loop.
                   break;
               case 'X':
                   cout << "There is there wall here.Please chose a new direction" << endl;
Player.x=Player.prev[0];
Player.y=Player.prev[1];
                   break;
               case ' ':
                   cout << "This is an open tile." << endl;
                   break;
               case 'W':
                   // If we found the cheese then set Victory to true
                   cout << "Congratulations. You found the cheese" << endl;
                   Victory = true;
                   break;
               default:
                                    
                   break;
               }
       }

       int c;
       cout << "Type anything and press Enter to quit" << endl;
       cin >> c;

       return 0;

}

int MapIndex( int x, int y )
{
       return y*10 + x;
}

int GetPlayerChoice()
{
       int choice = -1;
       
       return choice;
}

Surroundings GetSurroundings( int x, int y, char map[] )
{
       Surroundings surr;
       if( y <= 0 )
               surr.North = 'X';
       else
               surr.North = map[ MapIndex( x, y - 1) ];

       if( y >= 10 )
               surr.South = 'X';
       else
               surr.South = map[ MapIndex( x, y + 1) ];

       if( x <= 0 )
               surr.West = 'X';
       else
               surr.West = map[ MapIndex( x - 1, y ) ];

       if( x >= 10 )
               surr.East = 'X';
       else
               surr.East = map[ MapIndex( x + 1, y ) ];

       return surr;
}
