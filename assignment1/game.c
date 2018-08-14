/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "game.h"
#include "carboard.h"

void playGame()
{   
    Cell board[BOARD_HEIGHT][BOARD_WIDTH] = {{ EMPTY }, { EMPTY }};
    
    int startGameReturn;
    int loadCommandsReturn;
    
    showPlayCommands();
    initialiseBoard(board);
    startGameReturn = startGame();
    if (startGameReturn==1) {
    menu();
    }
    else if (startGameReturn==2){
        loadBoard(board, BOARD_1);
        displayBoard(board, NULL);
    }
    else if (startGameReturn==3){
        loadBoard(board, BOARD_2);
        displayBoard(board, NULL);
    }
    
    do {
        loadCommandsReturn=loadCommands(board);
        if (loadCommandsReturn==1) {
            menu();
        }
        else if (loadCommandsReturn==2) {
            loadBoard(board, BOARD_1);
            displayBoard(board, NULL);
        }
        else if (loadCommandsReturn==3) {
            loadBoard(board, BOARD_2);
            displayBoard(board, NULL);
        }
    } while (loadCommandsReturn !=1 || loadCommandsReturn !=4);
}

int loadCommands(Cell board[BOARD_HEIGHT][BOARD_WIDTH]) {
    char input[30];
    char command[30];
    int posOne;
    int posTwo;
    char direction[30];
    int valid=0;
    printf("Available commands: \n");
    printf("load<g> \n");
    printf("init<x><y><direction> \n");
    printf("quit \n \n");
    do {
        fgets(input, 30, stdin);
        sscanf(input, "%s %d %d %s", command, &posOne, &posTwo, direction);
        if (strcmp(command, "quit") == 0) {
            return 1;
            valid=1; 
        }
        else if (strcmp(command, "load1") == 0) {
            return 2;
            valid=1;
        }
        else if (strcmp(command, "load2") == 0) {
            return 3;
            valid=1;
        }
        else if (strcmp(command, "init") == 0){
            Player player = {{0}};
            Position playerPosition = {0};
            Direction playerDirection = {0};
            playerPosition.x = posOne;
            playerPosition.y = posTwo;
            if (strcmp(direction, "north") == 0) {
                playerDirection = NORTH;
            }
            else if (strcmp(direction, "south") == 0) {
                playerDirection = SOUTH;
            }
            else if (strcmp(direction, "east") == 0) {
                playerDirection = EAST;
            }
            else if (strcmp(direction, "west") == 0) {
                playerDirection = WEST;
            }
            initialisePlayer(&player, &playerPosition, playerDirection);
            loadPlayCommands(board, &player);
            valid=1;
            return 4;
        }
        else {
            printf("Invalid input \n\n");
        }
    } while(valid != 1);
    return EXIT_SUCCESS;
}

void loadPlayCommands(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player * player) {
    char command[30];
    int valid = 0;
    TurnDirection playerTurn = {0};
    Position forwardPosition = {0};
    do {
        printf("\n\n");
        displayBoard(board,player);
        printf("\n\n");
        printf("Available Commands: \n");
        printf("forward \n");
        printf("turn_left (or l) \n");
        printf("turn_right (or r) \n");
        printf("quit \n\n");

        scanf("%s", command);
        if (strcmp(command, "quit") == 0) {
            printf("Total moves : %i \n\n", player->moves);
            menu();
            valid = 1;
        }
        else if (strcmp(command, "forward") == 0) {
            forwardPosition = getNextForwardPosition(player);
            if (forwardPosition.x > 9 || forwardPosition.x < 0 || forwardPosition.y < 0 || forwardPosition.y > 9) {
                printf("The car is at the edge of the board and cannot move further in that directioni \n\n");
            }
            else if (board[forwardPosition.y][forwardPosition.x] == BLOCKED) {
                printf("Cannot move forward because road is blocked \n\n");
            }
            else {
                board[player->position.y][player->position.x] = EMPTY;
                player->moves++;
                updatePosition(player, forwardPosition);
            }
        }   
        else if (strcmp(command, "turn_left") == 0 || strcmp(command, "l") == 0) {
            playerTurn= TURN_LEFT;
            turnDirection(player, playerTurn);
            
        }
        else if (strcmp(command, "turn_right") == 0 || strcmp(command, "r") == 0) {
            playerTurn = TURN_RIGHT;
            turnDirection(player, playerTurn);
        }
        else {
            printf("Invalid Input \n\n");
            valid = 0;
        }
    } while(valid!=1);
}
