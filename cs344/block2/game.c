#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

enum position{START_ROOM, MID_ROOM, END_ROOM};

struct Room
{

  int id;
  char name[10];
  int numOutboundConnections;
  enum position roomLocation;
  struct Room *outboundConnections[6];

};

struct linkedList
{
  struct Room *room;
  struct linkedList *next;
};

struct Room *rooms[7];
char roomFiles[7][48];

struct Room room1;
struct Room room2;
struct Room room3;
struct Room room4;
struct Room room5;
struct Room room6;
struct Room room7;


struct dirent *getDirectory(){

  int newestDirTime = -1;
  char targetDirPrefix[32] = "shielcon.rooms.";
  char newestDirName[256];
  memset(newestDirName, '\0', sizeof(newestDirName));

  DIR* dirToCheck;
  struct dirent *fileInDir;
  struct dirent *newestDir;
  struct stat dirAttributes;

  dirToCheck = opendir(".");

  if (dirToCheck > 0)
  {
    while ((fileInDir = readdir(dirToCheck)) != NULL)
    {
      if (strstr(fileInDir->d_name, targetDirPrefix) != NULL)
      {
        stat(fileInDir->d_name, &dirAttributes);
        if ((int)dirAttributes.st_mtime > newestDirTime)
        {
          newestDirTime = (int)dirAttributes.st_mtime;
          newestDir = fileInDir;
        }
      }
    }
  }

  closedir(dirToCheck);

  return newestDir;

}

void readRoomNames(struct dirent *dirToOpen){

  int k = 0;
  int j, i;

  //variables for finding the room names in the directory
  char fileName[10];
  DIR *namesDir = opendir(dirToOpen->d_name);
  struct dirent *fileInDir;
  char targetDirPrefix[7] = "room_";
  
  //variables for building the full room file paths from the 
  //current directory to store in roomFiles[]
  char filePath[48];
  int filePathLen;
  int roomNameLen;
  memset(filePath, '\0', 48);
  strcpy(filePath, dirToOpen->d_name);
  strcat(filePath, "/room_");
  filePathLen = strlen(filePath);

  if (namesDir > 0){
        while ((fileInDir = readdir(namesDir)) != NULL){
          if (strstr(fileInDir->d_name, targetDirPrefix) != NULL){
		memset(fileName, '\0', 10);
                i = 0;
		j = 5;
		while (fileInDir->d_name[j] != '\0'){
	          fileName[i] = fileInDir->d_name[j];
		  i++;
		  j++;
		}
		//store the names of the rooms in the 7 structs
		strcpy(rooms[k]->name, fileName);
		rooms[k]->id = k;

		//store the paths to the rooms in roomFiles[]
		strcat(filePath, fileName);
		strcpy(roomFiles[k], filePath);
		roomNameLen = strlen(fileName);
		memset(filePath + filePathLen, '\0', roomNameLen);
		k++;
          }
        }
  }
  closedir(namesDir);
}

void getRoomConnections(){

  int nameIndex = 14;  //index of the room name in each "connection" line of the file
  int typeIndex = 11;  //index of the room type in each "room type" line of the files
  FILE *file;
  char line[48];
  memset(line, '\0', 48);

  int i, j, k, p;

  for (i = 0; i < 7; i++){

	file = fopen(roomFiles[i], "r");
	j = 0;
	p = 0;
	while (fgets(line, sizeof line, file) != NULL){
	    memset(line + strlen(line)-1, '\0', 1);	//removes the \n character at the end
	    if (j == 0){
		j++;
		continue;
	    }
	    else if (line[0] == 'C')
	    {
		for (k = 0; k < 7; k++)
		{
		    if (strcmp(rooms[k]->name, &line[14]) == 0)
		    {
			rooms[i]->outboundConnections[p] = rooms[k];
			rooms[i]->numOutboundConnections++;
			p++;
			break;
		    
		    }
	        }
	    }
	    else if (line[0] == 'R'){

		if (strcmp("START_ROOM", &line[11]) == 0)
			rooms[i]->roomLocation = START_ROOM;
		else if (strcmp("MID_ROOM", &line[11]) == 0)
			rooms[i]->roomLocation = MID_ROOM;
		else
			rooms[i]->roomLocation = END_ROOM;

	    }
	    j++;

  	}
	fclose(file);

  }  
}

struct Room *getStartRoom(){
 
  int i; 
  for (i = 0; i < 7; i++)
  {
        if (rooms[i]->roomLocation == START_ROOM){
            return rooms[i];
        }
  }
}

struct Room *switchRooms(struct Room *curRoom){

  int i;
  printf("CURRENT LOCATION: %s\n", curRoom->name); 
  printf("POSSIBLE CONNECTIONS: ");
  for (i = 0; i < curRoom->numOutboundConnections; i++)
  {
	if (i == curRoom->numOutboundConnections - 1)
	    printf("%s.\n", curRoom->outboundConnections[i]->name);
	else
	    printf("%s, ", curRoom->outboundConnections[i]->name);
  }
  printf("WHERE TO? >");

  char *input;
  char choice[32];
  memset(choice, '\0', 32);
  size_t inputSize = 32;
  size_t characters;

  input = (char *)malloc(inputSize * sizeof(char));
  characters = getline(&input, &inputSize, stdin);
  printf("\n");

  strcpy(choice, input);
  memset(choice + strlen(choice) - 1, '\0', 1);

  for (i = 0; i < curRoom->numOutboundConnections; i++)
  {
	if (strcmp(choice, curRoom->outboundConnections[i]->name) == 0)
	{
		free(input);
		return curRoom->outboundConnections[i];
	}
  }

  free(input);
  printf("HUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
  return switchRooms(curRoom);

}



void playGame(){

  int i, j;
  struct Room *curRoom = getStartRoom();

  //linked list to hold the path
  struct linkedList *first;
  struct linkedList *current;
  struct linkedList *temp;

  i = 0;
  while (curRoom->roomLocation != END_ROOM)
  {
	curRoom = switchRooms(curRoom);
	if (i == 0)
	{
	    current = malloc(sizeof(struct linkedList));
	    current->room = curRoom;
	    current->next = NULL;
	    first = current;
	    printf("room chosen %s\n", current->room->name);
	}
	else
	{
	    temp = malloc(sizeof(struct linkedList));
	    current->next = temp;
	    current->next->room = curRoom;
	    current = temp;
	    current->next = NULL;
	    printf("room chosen %s\n", current->room->name);
	}
	
	
	i++;
  }

  printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
  printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", i);

  current = first;
  while (current != NULL)
  {
	printf("%s\n", current->room->name);
	temp = current;
	current = current->next;
	free(temp);
  }
}

int main(){

  rooms[0] = &room1;
  rooms[1] = &room2;
  rooms[2] = &room3;
  rooms[3] = &room4;
  rooms[4] = &room5;
  rooms[5] = &room6;
  rooms[6] = &room7;

  int i, j;

  struct dirent *dirToOpen = getDirectory();
  readRoomNames(dirToOpen);
  getRoomConnections();

  playGame();


  return 0;

}

