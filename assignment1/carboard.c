/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "carboard.h"
#include "board.h"
#include "game.h"
void showStudentInformation();
void showPlayCommands();
int startGame();
void menu();
void initialiseBoard();
void playGame();

int main()
{
    /* TODO */
    menu(); 
    return EXIT_SUCCESS;
}

void showStudentInformation()
{ 
    printf("-------------------------------- \n");
    printf("%s \n", STUDENT_NAME);
    printf("No: %s \n", STUDENT_ID);
    printf("Email: %s \n", STUDENT_EMAIL);
    printf("-------------------------------- \n \n");
}

void menu()
{
    int choice;

    printf("Welcome to Car Board \n");
    printf("-------------------- \n");          
    printf("1. Play game \n");
    printf("2. Show student's information \n");
    printf("3. Quit \n \n");
    do {
        printf("Please enter your choice: ");
        scanf("%i", &choice);
        if (choice == 1) {
            playGame();
           
       }
        else if (choice == 2) {
            showStudentInformation();
        }
        else if (choice == 3) {
            exit(0);
        }
        else {
            printf("Invalid Input \n\n ");
        }
    } while(choice !=1);
}

void showPlayCommands() 
{
    printf("You can use the following commmands to play the game: \n");
    printf("load <g> \n");
    printf("    g: number of the game board to load \n");
    printf("init <x>, <y>, <direction> \n");
    printf("    x: horizontal postion of the car on the board (between 0 & 9 \n");
    printf("    y: vertical postion of the car on the board (between 0 & 9 \n");
    printf("    direction: direction of the car's movement( north, south, east, west \n");
    printf("forward (or f) \n");
    printf("turn_left (or l) \n");
    printf("turn_right (or r) \n");
    printf("quit \n\n");
    printf("\n\n");
}

int startGame() 
{
    char command[30];
    int valid = 0;
    do {
        printf("Available commands: \n");
        printf("load<g> \n");
        printf("quit \n\n");
        scanf("%s", command);
        if (strcmp(command, "quit") == 0)
        {
            valid=1;
            return(1);
        }
        else if (strcmp(command, "load1") == 0)
        {
            valid=1;
            return(2);
        }
        else if (strcmp(command, "load2") == 0)
        {
            valid=1;
            return(3);                    
        }
        else {
            printf("Invalid Input \n\n");
            valid=0;
        }
    } while (valid==0);
    return EXIT_SUCCESS;
}
