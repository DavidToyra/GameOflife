/*
 * Programmering i  C
 * Fall 16
 * Assignment 3

 * File:         ou3.c
 * Description:  A simple implementation of Conway's Game of Life.
 * Author:		 David T�yr�
 * CS username:	 dv15dta
 * Date:		 2016-10-19
 * Input:        Choice of initial configuration and then instruction to step
 *               or exit.
 * Output:       Prints the game field in each step.
 * Limitations:  No validation of input.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Constants, representation of states */
#define ALIVE 'X'
#define DEAD '.'

const int rows = 20;
const int cols = 20;

/* Declaration of data structure */
typedef struct{
  char current;
  char next;
} cell;

/* Declaration of functions */
void initField(const int rows, const int cols, cell field[rows][cols]);
void loadGlider(const int rows, const int cols, cell field[rows][cols]);
void loadSemaphore(const int rows, const int cols, cell field[rows][cols]);
void loadRandom(const int rows, const int cols, cell field[rows][cols]);
void loadCustom(const int rows, const int cols, cell field[rows][cols]);
void printField(cell field[rows][cols]);
void loadNext(cell field[rows][cols]);
void printMenu();
int neighbors(cell field[rows][cols],int r,int c);
void copyField(cell field[rows][cols]);


/* Function:    main
 * Description: Start and run games, interact with the user.
 * Input:       About what initial structure and whether to step or exit.
 * Output:      Information to the user, and the game field in each step.
 */

int main(void) 
{
	
	cell field[rows][cols];
	char input;

	initField(rows, cols, field);
	
	do
	{	
		printField(field);
		printMenu();
		scanf("%c", &input);
		loadNext(field);
	}
	while(input=='\n');
	
    return 0;
}

/*
	Prints the 2D-array stored in the cell datatype
*/
void printField(cell field[rows][cols])
{
	for(int r = 0; r<rows; r++)
	{
		for(int c = 0; c<cols; c++)
		{
			printf("%c ", field[r][c].current);
				
		}
		printf("\n");
	
	}		
}

/*
	Prints the menu
*/
void printMenu()
{
	printf("Select one of the following options:\n");
	printf("	(enter) Step\n");
	printf("	(any)	Exit\n");
	
}


/*
	Loads the next generation
	Sets each cell to either DEAD or ALIVE according to the rules.
*/
void loadNext(cell field[rows][cols])
{
	int r,c;
	for( r = 0; r<rows; r++)
	{
		for(c = 0; c<cols; c++)
		{
			if(field[r][c].current==ALIVE && neighbors(field,r,c)==2)
			field[r][c].next=ALIVE;
			
			else if( field[r][c].current==ALIVE && neighbors(field,r,c)==3)
			field[r][c].next=ALIVE;
			
			else if(field[r][c].current==DEAD && neighbors(field,r,c)==3)
			field[r][c].next=ALIVE;
			
			else
			field[r][c].next=DEAD;
			
		}
	}
	
	copyField(field);

}

/*
	Copies the 2D-array in the datatype to another member of the structure
*/
void copyField(cell field[rows][cols]) 
{
	
	for(int r = 0; r<rows; r++)
	{
		for(int c = 0; c<cols; c++)
		{
			field[r][c].current = field[r][c].next;
				
		}
	}
	
 
}

/*
	Checks each adjecant neighbor for a cell and returns the number of neighbors
	as an integer.
*/
int neighbors(cell field[rows][cols],int r,int c) 
{
	
	
    int count = 0;
    if (field[r][c - 1].current==ALIVE && c-1 >=0) 
	{
        ++count;
    }
    if (field[r - 1][c - 1].current==ALIVE && r-1>=0 && c-1 >=0) 
	{
        ++count;
    }
    if (field[r + 1][c - 1].current==ALIVE && c-1>=0 && r+1<=19) 
	{
        ++count;
    }
    if (field[r + 1][c].current==ALIVE && r+1<=19) 
	{
        ++count;
    }
    if (field[r + 1][c + 1].current==ALIVE && r+1<=19 && c+1<=19)
	{
        ++count;
    }
    if (field[r][c + 1].current==ALIVE && c+1<=19)
	{
        ++count;
    }
    if (field[r- 1][c + 1].current==ALIVE && r-1>= 0 && c+1<=19) 
	{
        ++count;
	}
    if (field[r - 1][c].current==ALIVE && r-1>=0)
	{
        ++count;
    }
    
    return count;
}




/* Function:    initField
 * Description: Initialize all the cells to dead, then asks the user about
 *              which structure to load, and finally load the structure.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void initField(const int rows, const int cols, cell field[rows][cols]) {

    for (int r = 0 ; r < rows ; r++) {
        for (int c = 0 ; c < cols ; c++) {
            field[r][c].current = DEAD;
        }
    }

    printf("Select field spec to load ([G]lider, [S]emaphore, [R]andom ");
    printf("or [C]ustom): ");

    int ch = getchar();
    switch (ch) {
        case 'g':
        case 'G':
            loadGlider(rows, cols, field);
            break;
        case 's':
        case 'S':
            loadSemaphore(rows, cols, field);
            break;
        case 'r':
        case 'R':
            loadRandom(rows, cols, field);
            break;
        case 'c':
        case 'C':
        default:
            loadCustom(rows, cols, field);
            break;
    }

	

    /* Ignore following newline */
    if (ch != '\n') {
        getchar();
    }
}


/* Function:    loadGlider
 * Description: Inserts a glider into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void loadGlider(const int rows, const int cols, cell field[rows][cols]) {

    field[0][1].current = ALIVE;
    field[1][2].current = ALIVE;
    field[2][0].current = ALIVE;
    field[2][1].current = ALIVE;
    field[2][2].current = ALIVE;
}


/* Function:    loadSemaphore
 * Description: Inserts a semaphore into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void loadSemaphore(const int rows, const int cols, cell field[rows][cols]) {

    field[8][1].current = ALIVE;
    field[8][2].current = ALIVE;
    field[8][3].current = ALIVE;
}


/* Function:    loadRandom
 * Description: Inserts a random structure into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated. There is a 50 % chance that a cell
 *              is alive.
 */

void loadRandom(const int rows, const int cols, cell field[rows][cols]) {
	
	
	srand(time(NULL));
	int random;
	
	for(int r = 0; r<rows; r++)
	{
		for(int c = 0; c<cols; c++)
		{
			random=rand() % 2;
			if(random==1)
			field[r][c].current=ALIVE;
			else if(random==0)
			field[r][c].current=DEAD;
				
		}
	}
	
	

}


/* Function:    loadCustom
 * Description: Lets the user specify a structure that then is inserted into
 *              the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void loadCustom(const int rows, const int cols, cell field[rows][cols]) {

    printf("Give custom format string: ");
    do {
        int r, c;
        scanf("%d,%d", &r, &c);
        field[r][c].current = ALIVE;
    } while (getchar() != '\n');
}



