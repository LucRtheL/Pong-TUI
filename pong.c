#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/keys.h"

void clear(){					// Clear the screen. Don't use unless necessary, use line 50 instead if we're just redrawing the board
	printf("\033[H\033[J");
}
void showscore(int pscore, int cpuscore, char name[]){
	if(pscore > cpuscore){			// Highlight the winning score green
		printf(" %s: \e[32;1m%d\e[0m\n CPU: \e[31;1m%d\e[0m",name,pscore,cpuscore);
	} else if(cpuscore > pscore){
		printf(" %s: \e[31;1m%d\e[0m\n CPU: \e[32;1m%d\e[0m",name,pscore,cpuscore);
	} else if(cpuscore == pscore){
		printf(" %s: \e[1m%d\e[0m\n CPU: \e[1m%d\e[0m",name,pscore,cpuscore);
	}
}
void drawfield(unsigned int diff){ 			// Render out the field freaky fast using escape sequences
	printf("\n╔═══════════════════════════════════════════════╗\n");
	for ( int i = 0; i < 15; i++ ){
		printf("║\033[%d;49H║\n",i+4);
	}
	printf("╟───────────────────────────────────────────────╢\n");
	for ( int i = 0; i < 15; i++ ){
		printf("║\033[%d;49H║\n",i+20);
	}
	printf("╚═══════════════════════════════════════════════╝");
	printf("\033[1;14H║ Difficulty: ");
	for(int i = 0; i < diff; i++){			// Diff box is 13 from edge
		if(i<6){
			printf("\033[32m█\e[0m");
		} else if(i<12){
			printf("\033[33m█\e[0m");
		} else {
			printf("\033[31m█\e[0m");
		}
	}
	printf("\033[1;49H║\033[2;14H╚══════════════════════════════════╝");
}
void drawplayer(int x){
	printf("\033[4;%dH🮃🮃🮃",x);
}
void drawcpu(int x){
	printf("\033[34;%dH🬭🬭🬭",x);
}
void drawball(int x, int y){
	printf("\033[%d;%dHo",y,x);
}

int main(int argc, char *argv[]) {
	// Set up the terminal (include the 49L x 33T playfield) and reset scores
	clear();
	int playerscore = 0;
	int cpuscore = 0;
	char name[] = "Bob";
	int playerx = 24;
	int cpux = 24;
	int ballx = 24;
	int bally = 19;
	unsigned int difficulty = 1;
	if(argc > 1){difficulty = atoi(argv[1]);difficulty = difficulty % 21;}	// Read difficulty from launch parameters, max being 20
	if(difficulty==0){difficulty++;}	  				// Make sure that we don't end up with 0 difficulty
	// Get player info and finalize setup
	printf("What is your name?\n# ");
	scanf("%s",&name);
	clear();
	printf("\33[?25l");
	// Start the actual game ticking
	while(1==1){
		int tick = 0; 							// Redraw the board every 3rd tick
		printf("\033[0;0H");
		showscore(playerscore, cpuscore, name);
		if (tick == 0){
			drawfield(difficulty);
		}
		drawplayer(playerx);
		drawcpu(cpux);
		drawball(ballx,bally);
		tick++; tick % 2;
		// Read keyboard input //
	}
	printf("\033[38;0H");
	return 0;
}
