// ACM.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

// A struct to handle the tiles in the four Cardinal directions: N,E,S,W.
struct surroundings
{
	char North;
	char East;
	char South;
	char West;
};

// A struct to handle a position with 2 coordinates.
struct vector2
{
	int x, y;
};

// An enumeration to make Directions easier to manage.
enum direction { North=8, East=6, South=2, West=4 };

// The Player Object Definition.
class CPlayer
{
public:
	CPlayer(void){}
	~CPlayer(void){}

	vector2 Position;
	vector2 PreviousPosition;
	surroundings Surroundings;

	// Moves the player in the desired direction.
	void Move( direction direction )
	{
		switch( direction )
		{
		case North:
			Position.y--;
			break;
		case South:
			Position.y++;
			break;
		case East:
			Position.x++;
			break;
		case West:
			Position.x--;
			break;
		default:
			break;
		}
	}
	// Moves the Player back to the previously held position.
	void Revert()
	{
		Position = PreviousPosition;
	}

	int Choice;
};


// Return the index of the given Cartesian Coordinate.
int MapIndex( int x, int y );

// Return a surroundings struct that is filled with the map tiles around the Cartesian Coordinate.
surroundings GetSurroundings( int x, int y, char [] );

// Return an integer representing the Players Choice.
int GetPlayerChoice();


int main( int argc, char* argv[] )
{
	bool GameOver = false;
	const unsigned int MAP_MAX_INDEX = 100U;
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

	// The Player Object Instantiation.
	CPlayer Player;

	// Welcome message.
	cout << "Welcome to The RMU ACM Text Adventure. Your goal is navigate the map to find the Cheese. Good luck." << endl << endl;


	// Place the player at the start tile by looping through each tile until we find the S.
	for( int i = 0; i<MAP_MAX_INDEX; i++ )
	{
		if( Map[i] == 'S' )
		{

			Player.Position.x = (i % MapWidth);
			Player.Position.y = (i / MapWidth);
		}

	} // for( int i = 0; i<MAP_MAX_INDEX; i++ )

	while( !GameOver )
	{
		// Find out what is around the player
		Player.Surroundings = GetSurroundings( Player.Position.x, Player.Position.y, Map );
		// Display the the options for the player
		//cout << "Please type the number for the direction you wish to travel and press enter: " << endl;
		// Determine where the player can go and options. For now we only have walls to block us.
		if ( Player.Surroundings.North != 'X' )
		{
			// North is not a wall.
			cout << "You see a passage to the North. Enter: " << North << " if you want to go there." << endl;
		}
		if ( Player.Surroundings.East != 'X' )
		{
			// East is not a wall.
			cout << "You see a passage to the East. Enter: " << East << " to venture East." << endl;
		}
		if ( Player.Surroundings.South != 'X' )
		{
			// South is not a wall
			cout << "You see a passage to the South. Enter: " << South << " to go that way." << endl;
		}
		if ( Player.Surroundings.West != 'X' )
		{
			// West is not a wall
			cout << "You see a passage to the West. Enter: " << West << " to try your luck there." << endl;
		}
               
		// Let the player choose his direction.
		cin >> Player.Choice;

		// Store the previous position.
		Player.PreviousPosition.x = Player.Position.x;
		Player.PreviousPosition.y = Player.Position.y;
		// interpret the CPlayer.choice into a char from the map... Tile = map(choice)
		mi = MapIndex(Player.Position.x, Player.Position.y);
		switch( Player.Choice )
		{
			case North:
				// Player choose to go North;
				Player.Move(North);
				// check for array out of bounds
				Tile = ( mi < 0 || mi >= MAP_MAX_INDEX ) ? 'X' : Map[ MapIndex(Player.Position.x, Player.Position.y) ];
				break;
			case East:
				// Player choose to go East;
				Player.Move(East);
				Tile = ( mi < 0 || mi >= MAP_MAX_INDEX ) ? 'X' : Map[ MapIndex(Player.Position.x, Player.Position.y) ];
				break;
			case South:
				// Player choose to go South;
				Player.Move(South);
				Tile = ( mi < 0 || mi >= MAP_MAX_INDEX ) ? 'X' : Map[ MapIndex(Player.Position.x, Player.Position.y) ];
				break;
			case West:
				// Player choose to go West;
				Player.Move(West);
				Tile = ( mi < 0 || mi >= MAP_MAX_INDEX ) ? 'X' : Map[ MapIndex(Player.Position.x, Player.Position.y) ];
				break;
			default:
				Tile = ( mi < 0 || mi >= MAP_MAX_INDEX ) ? 'X' : Map[ MapIndex(Player.Position.x, Player.Position.y) ];
				break;
		}
               
		switch(Tile)
		{
			case '#':
				cout << "This is a trap. You have failed your mission." << endl;
				GameOver = true;
				break;
			case 'X':
				cout << "Uh, That wasn't an option... retard." << endl;
				Player.Revert();
				break;
			case ' ':
				cout << "You have wandered into an open room." << endl;
				break;
			case 'W':
				// If we found the cheese then set Victory to true
				cout << "Congratulations. You found the Cheese." << endl;
				GameOver = true;
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

surroundings GetSurroundings( int x, int y, char map[] )
{
	surroundings surr;
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
