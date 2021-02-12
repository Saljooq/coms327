#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ROOMS 12
#define MIN_ROOMS 6

#define xlenMax 78
#define ylenMax 19


#define minRoomxlen 4
#define minRoomylen 3

#define maxStairs 3
#define minStairs 1

typedef struct room
{
	int xloc;
	int yloc;
	int xlen;
	int ylen;
}room;

int makes_sense(room rooms[], int numRooms);
int not_so_rand_roomsize_resizer(int numRooms);

int main()
{
	//we will start out by creating a seed with time-0 to access some randomeness
	srand(time(0));
	
	room rooms[MAX_ROOMS];
	
	int numRooms = MIN_ROOMS + (rand() % (MAX_ROOMS - MIN_ROOMS + 1));
	
	int resizer = not_so_rand_roomsize_resizer(numRooms);
	
	int maxRoomxlen = xlenMax / resizer;
	if (maxRoomxlen <= minRoomxlen) maxRoomxlen = minRoomxlen + 1;
	
	
	int maxRoomylen = ylenMax / resizer;
	if (maxRoomylen <= minRoomylen) maxRoomylen = minRoomylen + 1;
	
	//printf("num Rooms = %d\n", numRooms);
	
	while (1)
	{

		for (int i = 0; i < numRooms; i++)
		{
			rooms[i].xloc = rand() % xlenMax;
			rooms[i].yloc = rand() % ylenMax;
			rooms[i].xlen = minRoomxlen + rand() % ((maxRoomxlen) - minRoomxlen);
			rooms[i].ylen = minRoomylen + rand() % ((maxRoomylen) - minRoomylen);
		}
		if (makes_sense(rooms, numRooms)) break;
		
		
	}
	
	
	char grid[xlenMax][ylenMax];
	
	for (int i = 0; i < xlenMax; i++)
	{
		for (int j = 0; j < ylenMax; j++)
		{
			grid[i][j] = ' ';
		}
	}
	
	
	for (int counter = 0; counter < numRooms; counter++)
	{
		
		for (int i = rooms[counter].xloc; i < (rooms[counter].xloc + rooms[counter].xlen); i++)
		{
			for (int j = rooms[counter].yloc; j < (rooms[counter].yloc + rooms[counter].ylen); j++)
			{
				grid[i][j] = '.';
			}
		}
	}
	
	for (int counter = 0; counter < numRooms - 1; counter++)
	{
		int middlex = rooms[counter].xloc;
		int middley = rooms[counter + 1].yloc;
		int i;
		
		if (rooms[counter].yloc > middley) i = 1;
		else i = -1;
		
		for (int j = middley; j != rooms[counter].yloc; j += i)
		{
			if (grid[middlex][j] != '.') grid[middlex][j] = '#';
		}
		
		if (rooms[counter + 1].xloc > middlex) i = 1;
		else i = -1;
		
		for (int j = middlex; j != rooms[counter + 1].xloc; j += i)
		{
			if (grid[j][middley] != '.') grid[j][middley] = '#';
		}
		
	}
	
	for (int i = 0; i < 2; i++)
	{
		char staircase;
		if (i == 0) staircase = '<';
		else staircase = '>';
		
		int numStairs = minStairs + rand() % ((maxStairs) - minStairs);
		
		for (int j = 0; j < numStairs; j++)
		{
	
			while (1)
			{
				int x = 1 + (rand() % (xlenMax - 2));//this ensures that we're not on the left or the right edge because the condition below checks horizontal neighbours
				int y = (rand() % (ylenMax));

				if (grid[x][y] == '.' && grid[x - 1][y] == '.' && grid[x + 1][y] == '.')
				{
					grid[x][y] = staircase;
					break;
				}
			}
			
			
		}
	}
	
	for (int i = 0; i < xlenMax; i++) {printf("-");}
	printf("\n");
	for (int i = 0; i < ylenMax; i++)
	{
		printf("|");
		for (int j = 0; j < xlenMax; j++)
		{
			printf("%c", grid[j][i]);
		}
		printf("|\n");
	}
	for (int i = 0; i < xlenMax; i++) {printf("-");}
	printf("\n\n\n");
	

	
	return 0;
}

int makes_sense(room rooms[], int numRooms)
{

	int checker = 1;//this essentially marks whether the program makes any sense, 0 indicates it doesnn't
	
	for (int i = 0; i < numRooms; i++)
	{
		for (int j = 0; j < numRooms; j++)
		{
			if (i != j)
			{
				if(
				rooms[i].yloc >= rooms[j].yloc &&
				rooms[i].yloc <= (rooms[j].yloc + rooms[j].ylen + 1)
				)
				{
					if(
					(rooms[i].xloc >= rooms[j].xloc &&
					rooms[i].xloc <= (rooms[j].xloc + rooms[j].xlen + 1) 
					) || (
					rooms[i].xloc + rooms[i].xlen >= rooms[j].xloc &&
					rooms[i].xloc + rooms[i].xlen <= (rooms[j].xloc + rooms[j].xlen + 1) 
					) || (
					rooms[i].xloc < rooms[j].xloc &&
					rooms[i].xloc + rooms[i].xlen > (rooms[j].xloc + rooms[j].xlen + 1)
					)
					) checker = 0;
				}
				
				
			}
			
			if (checker == 0) break;
			
		}
		
		if (
			(rooms[i].xloc + rooms[i].xlen >= xlenMax - 1) || 
			(rooms[i].yloc + rooms[i].ylen >= ylenMax - 1)
			) checker = 0;
		
		if (checker == 0) break;
	}
	
	return checker;
}

int not_so_rand_roomsize_resizer(int numRooms)
{
	int roomSizer = (numRooms/2) - 1;

	return roomSizer;
}
