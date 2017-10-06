//#include "definition.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.c"


void insertEnd(struct feature **head, const char* song) // Insert Song in the End
{
    if ((*head)->ptr == NULL)
    {
        struct song *newnode = (struct song *)malloc(sizeof(struct song));
        newnode->songName = (char *)malloc(sizeof(strlen(song))+1);
        strcpy(newnode->songName,song);
        newnode->next = newnode->prev = newnode;
        (*head)->ptr = newnode;
        return;
    }
    struct song *start = (*head)->ptr;
    struct song *last = start->prev;
    struct song *newnode = (struct song *)malloc(sizeof(struct song));
    newnode->songName = (char *)malloc(sizeof(strlen(song))+1);
    strcpy(newnode->songName,song);
    newnode->next = start;
    start->prev = newnode;
    newnode->prev = last;
    last->next = newnode;
}

void insertBegin(struct feature **head, const char* song) // Insert Song in the Beginning
{
    struct song *last;
    struct song *newnode = (struct song *)malloc(sizeof(struct song));
    newnode->songName = (char *)malloc(sizeof(strlen(song)+1));
    strcpy(newnode->songName,song);
    newnode->next = NULL;
    newnode->prev = NULL;
    struct song *start = (*head)->ptr;
    if (start == NULL)
	{
        (*head)->ptr = newnode;
		last = newnode;
		newnode->next = newnode;
		newnode->prev = newnode;
		return;
	}
	last = start->prev;
	newnode->next = start;
	newnode->prev = last;
    last->next = start->prev = newnode;
    start = newnode;
}

void insertAfter(struct feature **head, const char* song1, const char* song2) // Insert Song at a Position
{
    struct song *newnode = (struct song *)malloc(sizeof(struct song));
    newnode->songName = (char *)malloc(sizeof(strlen(song1)+1));
    strcpy(newnode->songName,song1);
    struct song *temp = (*head)->ptr;
    while (strcmp(temp->songName,song2))
        temp = temp->next;
    struct song *next = temp->next;
    temp->next = newnode;
    newnode->prev = temp;
    newnode->next = next;
    next->prev = newnode;
}

void play_from_beg(struct feature *head) // To Play the Songs from the Beginning
{
    struct song *temp = head->ptr;
    while (temp->next != head->ptr)
    {
        printf("%s ", temp->songName);
        temp = temp->next;
    }
    printf("%s",temp->songName);
}

void play_in_rev(struct feature *head) // To Play the Songs in the End
{
    struct song *start = head->ptr;
    struct song *last = start->prev;
    struct song *temp = last;
    while (temp->prev != last)
    {
        printf("%s ", temp->songName);
        temp = temp->prev;
    }
    printf("%s",temp->songName);
}

void deleteNode(struct feature **head, const char* song) // To Delete a Song from the Playlist
{
    struct song *start = (*head)->ptr;
    if (start == NULL)
        return;
    struct song *curr = (*head)->ptr, *track = NULL;
    while (strcmp(curr->songName,song))
    {
        if (curr -> next == start)
        {
            printf("\nThe Song '%s' does not exist in the Playlist",song);
            return;
        }
        track = curr;
        curr = curr -> next;
    }
    if (curr -> next == start && track == NULL)
    {
        (*head)->ptr = NULL;
        free(curr);
        return;
    }
    if (curr == start)
    {
        track = start -> prev;
        start = start -> next;
        track -> next = start;
        start -> prev = track;
        free(curr);
    }
    else if (curr->next == start)
    {
        track -> next = start;
        start -> prev = track;
        free(curr);
    }
    else
    {
        struct song *temp = curr -> next;
        track -> next = temp;
        temp -> prev = track;
        free(curr);
    }
}

void createPlaylist(struct feature **head)
{
    char *name = (char*)malloc(25);
    printf("Enter the Name of the Playlist:");
    scanf("%s",name);
    char *fileName = (char*)malloc(25);
    strcpy(fileName,name);
    strcat(fileName,".txt");
    printf("file name = %s\n ",fileName);
    FILE* fp;
    fp = fopen(fileName,"w+");
    struct song *temp = (*head)->ptr;
    
    while (temp->next != (*head)->ptr)
    {
    	printf("song name = %s\n",temp->songName);
        fprintf(fp,"%s\n",temp->songName);
        temp = temp->next;
    }
    fprintf(fp,"%s\n",temp->songName);
    fclose(fp);
    
    FILE* fpNameList;
    fpNameList = fopen("playlists.txt","a");
    fprintf(fpNameList,"%s\n",name);
    fclose(fpNameList);
}

void playPlaylist()
{
    printf("These are the current available playlists\n");
    FILE* fpNameList;
    fpNameList = fopen("playlists.txt","r");
    while(!feof(fpNameList))
    {
        char NameOfPlayList[20];
        fscanf(fpNameList,"%s",NameOfPlayList);
        printf("%s\n",NameOfPlayList);
    }
    struct feature *head = (struct feature *)malloc(sizeof(struct feature));
    head->ptr = NULL;
    printf("Enter the name of your playlist\n");
    char *playListName;
    playListName = (char *)malloc(sizeof(20));
    scanf("%s",playListName);
    FILE *fp;
    strcat(playListName,".txt");
    printf("%s \n",playListName);
    fp = fopen(playListName,"r");
    if(fp == NULL)
    {
        printf("Playlist does not exist\n");
        return;
    }
    while(!feof(fp))
    {
        char songName[20];
        fscanf(fp,"%s",songName);
        strcat(songName,".mp3");
        insertEnd(&head,songName);
    }

    struct song *temp = head->ptr;
    while(1)
    {
        playSong(temp);
        return;
    }
    
}

