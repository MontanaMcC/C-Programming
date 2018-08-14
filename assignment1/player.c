/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "player.h"

void initialisePlayer(Player * player, Position * position, Direction direction)
{
    player->position = *position;
    player->direction = direction;
    player->moves = 0;
    
}

void turnDirection(Player * player, TurnDirection turnDirection)
{
    if (turnDirection == TURN_LEFT) {
        if (player->direction == NORTH) {
            player->direction = WEST;
        }
        else if (player->direction == WEST) {
            player->direction = SOUTH;
        }
        else if (player->direction == SOUTH) {
            player->direction = EAST;
        }
        else if (player->direction == EAST) {
            player->direction = NORTH;
        }
    }
    if (turnDirection == TURN_RIGHT) {
        if (player->direction == NORTH) {
            player->direction = EAST;
        }
        else if (player->direction == WEST) {
            player->direction = NORTH;
        }
        else if (player->direction == SOUTH) {
            player->direction = WEST;
        }
        else if (player->direction == EAST) {
            player->direction = SOUTH;
        }
    }
}

Position getNextForwardPosition(const Player * player)
{
    Position forwardPosition = {0};
    if (player->direction == NORTH) {
        forwardPosition.x = player->position.x;
        forwardPosition.y = player->position.y - 1;
    }
    else if (player->direction == SOUTH) {
        forwardPosition.x = player->position.x;
        forwardPosition.y = player->position.y + 1;
    }
    else if (player->direction == EAST) {
        forwardPosition.x = player->position.x + 1;
        forwardPosition.y = player->position.y;
    }   
    else if (player->direction == WEST) {
        forwardPosition.x = player->position.x - 1;
        forwardPosition.y = player->position.y;
    }
    return forwardPosition;
}

void updatePosition(Player * player, Position position)
{
    player->position = position;

}

void displayDirection(Direction direction)
{
    if (direction ==  NORTH) {
        printf("|%s|", DIRECTION_ARROW_OUTPUT_NORTH);
    }
    else if (direction == SOUTH) {
        printf("|%s|", DIRECTION_ARROW_OUTPUT_SOUTH);
    }
    else if (direction == EAST) {
        printf("|%s|", DIRECTION_ARROW_OUTPUT_EAST);
    }
    else if (direction == WEST) {
        printf("|%s|", DIRECTION_ARROW_OUTPUT_WEST);
    }


}
