#include <python2.7/Python.h>
#include "definition.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.c"
#include "shuffle.c"


int main(int argc,char *argv[])
{
	Py_SetProgramName(argv[0]);
	Py_Initialize();
	PySys_SetArgv(argc, argv);
	
	
	char *x,*y;
    x = (char*)malloc(100);
    y = (char*)malloc(100);
    
	while(1)
	{
		printf("\nEnter\n 1.to create a playlist\n2 to play a playlist.\n3 to go to shuffle mode\n4.Exit\n");
		int mainChoice;
		scanf("%d",&mainChoice);
		if(mainChoice == 1)
		{
			printf("\n\n1.Insert Song at Beginning.\n2.Insert Song at End.\n3.Insert Song at Position.\n4.Delete a Particular Song.");
   			printf("\n5.Play from Beginning.\n6.Play from End.\n7.Make Playlist.\n8.Exit");
   			struct feature *head = (struct feature *)malloc(sizeof(struct feature));
			head->ptr = NULL;
   			while(1)
   			{
   				int ch;
   				printf("\nEnter your choice:");
        		scanf("%d", &ch);
        		if(ch == 8)
        		{
        			break;
        		}
	        	switch (ch)
	        	{

		       		case 1 : printf("Enter the Song Name: ");
	                    	 scanf("%s",x);
	                     	 insertBegin(&head,x);
	                     	 break;

		        	case 2 : printf("Enter the Song Name: ");
		        		 	 scanf("%s",x);
	                     	 insertEnd(&head,x);
	                     	 break;

		        	case 3 : printf("Enter the Song (to be inserted): ");
		        		 	 scanf("%s",x);
		        		     printf("Enter the Previous Song: ");
		        		     scanf("%s",y);
	                         insertAfter(&head,x,y);
		        		     break;

		        	case 4 : printf("Enter the Song to be Deleted: ");
		        	     	 scanf("%s",x);
		        		     deleteNode(&head,x);
				             break;

		            case 5 : play_from_beg(head);
				             break;

		        	case 6 : play_in_rev(head);
				             break;

	            	case 7 : createPlaylist(&head);
	                         printf("\nPlaylist Made :)");
	                         break;

					default: printf("\nInvalid Choice");

		        
	       		}
   			}	
		}
		else if(mainChoice == 3)
		{
			struct feature *head = (struct feature *)malloc(sizeof(struct feature));
			head->ptr = NULL;
			shuffle(&head);
		}
		else if(mainChoice == 2)
		{
			struct feature *head = (struct feature *)malloc(sizeof(struct feature));
			head->ptr = NULL;
			playPlaylist(&head);
		}
		else if (mainChoice == 4)
		{
			printf("Goodbye\n");
			exit(0);
		}
	}
}