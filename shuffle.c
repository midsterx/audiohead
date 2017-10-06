//#include "definition.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "player.c"

struct songName
{
	char name[20];
	int val;
};

void append(struct feature **head,struct songName s[],int r1)
{
	char *name;
	for(int i = 0;i<10;i++)
	{
		if(s[i].val == r1)
		{
			name = (char *)malloc(sizeof(s[i].name));
			strcpy(name,s[i].name);
			break;
		}
	}
	struct song *newNode = (struct song *)malloc(sizeof(struct song));
	newNode->songName = (char *)malloc(sizeof(strlen(name+1)));
	strcpy(newNode->songName,name);
	newNode->prev = NULL;
	newNode->next = NULL;
	
	if((*head)->ptr == NULL)
	{
		(*head)->ptr = newNode;
		newNode->next = newNode;
		newNode->prev = newNode;
		return;	
	}
	
	struct song *first = (*head)->ptr;
	struct song *temp = (*head)->ptr;
	
	if(temp->next == first)
	{
		temp->next = newNode;
		newNode->prev = temp;
		newNode->next = temp;
		return;
	}
	
	while(temp->next!=first)
	{
		temp = temp->next;
	}
	temp->next = newNode;
	newNode->next = first;
	first->prev = newNode;
	newNode->prev = temp;
	return;
}

void shuffleSongs(struct feature **head)
{
	//printf("Hello!!\n");
	struct songName s[20];
	FILE *fp;
	fp = fopen("songsList.txt","r");
	//printf("file opened!!\n");
	int j = 0;
	while(!feof(fp))
	{
		//printf("hello!!\n");
		fscanf(fp,"%s %d",s[j].name,&s[j].val);
		//printf("s[j].name = %s\n",s[j].name);
		j++;
	}
	srand(time(NULL));
	int a[10];
	for(int i = 0;i<10;i++)
	{
		a[i] = i+1;
		//printf("%d ",a[i]);

	}
	printf("\n");
	int l = 9;
	while(l>=0)
	{
		int r = rand();
		int r1 = r%(l+1);
		append(head,s,a[r1]);
		a[r1] = a[l];
		l = l-1;
	}
}

void shuffle(struct feature **head)
{
	shuffleSongs(head);
	struct song *currentSong = (*head)->ptr;
	while(1)
	{
		playSong(currentSong);
		break;
	}
	
}

