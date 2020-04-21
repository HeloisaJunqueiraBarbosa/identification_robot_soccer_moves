#pragma once
//this are the cosntants values used in source code

//defining maximum game length
#define MAX_NUMBER_OF_CYCLES 10000

//defining player maximum length
#define MAX_PLAY_LENGTH 150

//defining manual book constants
#define PLAYER_BODY 0.085
#define PLAYER_SIZE 0.3
#define PLAYER_AREA (PLAYER_BODY + PLAYER_SIZE)
#define KICK_MARGIN 0.7
#define ERROR_MARGIN 1.05
#define KICKABLE_AREA (PLAYER_AREA + KICK_MARGIN) * ERROR_MARGIN
#define PLAYER_MOVEMENT 1.2 * ERROR_MARGIN
#define DASH_DISTANCE PLAYER_MOVEMENT * 2
#define REACTION_TIME 1.5
#define REACTION 2 * (KICKABLE_AREA) / REACTION_TIME
#define INTERACTION_TRESHOLD 0.4

//after a play is finished there a number of cycles
//between the finalization of play and the referee
//playmode message, wich makes evaluating last
//team on ball hard.
#define CHANGE_PLAYMODE_DELAY 5