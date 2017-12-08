#include "messagebox.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>

int main (int argc, char* argv[]){

	int file_desc, ret_val;
	int returnValue=0;
	int choice;
	int maxValue;
	char username[15];

	file_desc = open("/dev/messagebox", 0);
	if (file_desc < 0) {
		printf("Can't open device file: /dev/messagebox\n");
		exit(-1);
	}
	
	printf("Exclude Mode (0)\nInclude Mode (1)\nDelete All Messages (2)\nMaximum Unread Message Count(3)\nEnter your choice: ");
    scanf("%d", &choice);
	
	switch(choice){
		case 0:
			returnValue = ioctl (file_desc, MESSAGEBOX_SET_EXCLUDE_MODE); 
			break;
		case 1:
			returnValue = ioctl (file_desc, MESSAGEBOX_SET_INCLUDE_MODE); 
			break;
		case 2:
			printf("Enter username: \n");
			scanf("%s", username);
			returnValue = ioctl (file_desc, MESSAGEBOX_DELETE_ALL_MESSAGES_MODE, username); 
			break;
		case 3:
			printf("Enter the maximum value: \n");
			scanf( "%d", &maxValue);
			returnValue = ioctl (file_desc, MESSAGEBOX_MAX_UNREAD_MODE, maxValue); 
			break;
		default:
			printf("Invalid choice!");
	
	}
	if (returnValue != 0){
		printf("Permission Error\n");
	}

	close(file_desc);
	return returnValue;
}
