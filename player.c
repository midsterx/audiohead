//#include "definition.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void playSong(struct song *currentSong);
void nextSong(struct song **currentSong);
void previousSong(struct song **currentSong);

void playSong(struct song *currentSong)
{
	PyRun_SimpleString("from pygame import *");
	PyRun_SimpleString("mixer.init()");

	char command[10];

		
	while(scanf("%s",command) == 1)
	{
		if(strcmp("pause",command) == 0)
		{
			PyRun_SimpleString("mixer.music.pause()");
			continue;
		}



		else if(strcmp("resume",command) == 0)
		{
			PyRun_SimpleString("mixer.music.unpause()");
			continue;
		}
		else if(strcmp("next",command) == 0)
		{
			nextSong(&currentSong);
		}
		else if(strcmp("previous",command) == 0)
		{
			previousSong(&currentSong);
		}
		else if(strcmp("exit",command) == 0)
		{
			PyRun_SimpleString("mixer.music.pause()");
			break;
		}
		else if(strcmp("play",command) == 0)
		{}
		else
			continue;
		char exec1[50] = "mixer.music.load('')";
		char exec2[50];
		strncpy(exec2,exec1,18);
		exec2[18] = '\0';
		strcat(exec2,currentSong->songName);
		printf("song name is %s\n",currentSong->songName);
		strcat(exec2,exec1+18);
		//printf("currentSong->songName = %s\n",currentSong->songName);
		PyRun_SimpleString(exec2);
		PyRun_SimpleString("mixer.music.play()");
	}
}



void nextSong(struct song **currentSong)
{
	*currentSong = (*currentSong)->next;
}
void previousSong(struct song **currentSong)
{
	*currentSong = (*currentSong)->prev;
}