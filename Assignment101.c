#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ROOMS 8
#define MIN_ROOMS 6
#define xlenMax 78
#define ylenMax 19

#define maxRoomxlen (xlenMax / 2)
#define maxRoomylen (ylenMax / 2)
#define minRoomxlen 4
#define minRoomylen 3

typedef struct room
{
	int xloc;
	int yloc;
	int xlen;
	int ylen;
}room;

int makes_sense(room rooms[], int numRooms);

int main()
{
	//we will start out by creating a seed with time-0 to access some randomeness
	srand(time(0));

	//next we will print random numbers between variable i  and 50(fixed)

	//for (int i = 0; i<10; i++) printf("%d ", i + 1 + (rand()%(50-i)));

	//printf("\n\n");

	//fprintf(stdout, "Hello world!\n");
	
	room rooms[MAX_ROOMS];
	
	int numRooms = MIN_ROOMS + (rand() % (MAX_ROOMS - MIN_ROOMS + 1));
	printf("num Rooms = %d\n", numRooms);
	
	while (1)
	{

		for (int i = 0; i < numRooms; i++)
		{
			rooms[i].xloc = rand() % xlenMax;
			rooms[i].yloc = rand() % ylenMax;
			rooms[i].xlen = minRoomxlen + rand() % ((maxRoomxlen) - minRoomxlen);
			rooms[i].ylen = minRoomylen + rand() % ((maxRoomylen) - minRoomylen);
			/*printf("coordinates for %dth is (%d, %d) and the length is (%d, %d) \n",i, 
			rooms[i].xloc,
			rooms[i].yloc,
			rooms[i].xlen,
			rooms[i].ylen);
			*/
		}
		if (makes_sense(rooms, numRooms)) break;
		
		
	}
	
	printf("success\n");
	
	char grid[xlenMax][ylenMax];
	
	for (int i = 0; i < xlenMax; i++)
	{
		for (int j = 0; j < ylenMax; j++)
		{
			grid[i][j] = ' ';
		}
		//printf("\n");
	}
	
	
	for (int counter = 0; counter < numRooms; counter++)
	{
		
		for (int i = rooms[counter].xloc; i < (rooms[counter].xloc + rooms[counter].xlen); i++)
		{
			for (int j = rooms[counter].yloc; j < (rooms[counter].yloc + rooms[counter].ylen); j++)
			{
				grid[i][j] = '.';
			}
			//printf("|\n");
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
	
	/*
	while(1)
	{
		
	}
	*/

	
	
	return 0;
}

int makes_sense(room rooms[], int numRooms)
{
	//return 1;
	int checker = 1;
	
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
				
				
				
				/*rooms[i].xloc >= rooms[j].xloc &&
				rooms[i].xloc <= (rooms[j].xloc + rooms[j].xlen + 1) &&
				rooms[i].yloc >= rooms[j].yloc &&
				rooms[i].yloc <= (rooms[j].yloc + rooms[j].ylen + 1)
				) checker = 0;
				else if(
				rooms[i].xloc + rooms[i].xlen >= rooms[j].xloc &&
				rooms[i].xloc + rooms[i].xlen <= (rooms[j].xloc + rooms[j].xlen + 1) &&
				rooms[i].yloc >= rooms[j].yloc &&
				rooms[i].yloc <= (rooms[j].yloc + rooms[j].ylen + 1) 
				) checker = 0;*/
				
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
