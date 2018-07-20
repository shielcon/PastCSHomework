#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

enum position{START_ROOM, MID_ROOM, END_ROOM};

struct Room
{

  int id;
  char* name;
  int numOutboundConnections;
  enum position roomLocation;
  struct Room *outboundConnections[6];

};

struct Room *allRooms[10];
struct Room *rooms[7];

bool IsGraphFull();
void AddRandomConnection();
struct Room *GetRandomRoom();
bool CanAddConnectionFrom(struct Room *x);
bool ConnectionAlreadyExists(struct Room* x, struct Room* y);
void ConnectRoom(struct Room* x, struct Room* y);
bool IsSameRoom(struct Room* x, struct Room* y);
void resizeRoomsArr(struct Room *x);


bool IsGraphFull()
{

    int i;
    int j;

    for (i = 0; i < 7; i++){
	if (rooms[i]->numOutboundConnections < 3)
	    return false;
    }
    	
    return true;

}


void AddRandomConnection()  
{
  int i;
  struct Room *A;
  struct Room *B;



  while(true)
  {
    A = GetRandomRoom();

    if (CanAddConnectionFrom(A) == true)
      break;
  }


  do
  {
    B = GetRandomRoom();
    
      
  }
  while(CanAddConnectionFrom(B) == false || IsSameRoom(A, B) == true || ConnectionAlreadyExists(A, B) == true);

  ConnectRoom(A, B);  // TODO: Add this connection to the real variables, 
  ConnectRoom(B, A);  //  because this A and B will be destroyed when this function terminates
}

struct Room *GetRandomRoom()
{
  int random = rand() % 7;
  return rooms[random];
}


bool CanAddConnectionFrom(struct Room* x) 
{
   if (x->numOutboundConnections < 6)
	return true;
   else
	return false;
}


bool ConnectionAlreadyExists(struct Room* x, struct Room* y)
{

  int xlength = x->numOutboundConnections;
  int ylength = y->numOutboundConnections;
  int i;

  for (i = 0; i < xlength; i++)
  {
	if (x->outboundConnections[i]->id == y->id)
	  return true;
  }
  for (i = 0; i < ylength; i++)
  {
	if (y->outboundConnections[i]->id == x->id)
	  return true;
  }

  return false;

}


void ConnectRoom(struct Room* x, struct Room* y) 
{
  x->outboundConnections[x->numOutboundConnections] = y;
  x->numOutboundConnections++;
  /*if (!CanAddConnectionFrom(x))
    resizeRoomsArr(x);*/
}


bool IsSameRoom(struct Room* x, struct Room* y)
{
  if (x->id == y->id)
        return true;
  return false;
}


int main()
{

  srand(time(0));
  
  char roomsDir[256];
  memset(roomsDir, '\0', 256);
  strcpy(roomsDir, "shielcon.rooms.");
  int pid = getpid();
  char process[20];
  sprintf(process, "%d", pid);
  strcat(roomsDir, process);
  int result = mkdir(roomsDir, 0755);

  struct Room theHall;
  struct Room Conservatory;
  struct Room Kitchen;
  struct Room BilliardRoom;
  struct Room Lounge;
  struct Room Library;
  struct Room Study;
  struct Room DiningRoom;
  struct Room Ballroom;
  struct Room MrBoddysGrave;


  allRooms[0] = &theHall;
  allRooms[1] = &Conservatory;
  allRooms[2] = &Kitchen;
  allRooms[3] = &BilliardRoom;
  allRooms[4] = &Lounge;
  allRooms[5] = &Library;
  allRooms[6] = &Study;
  allRooms[7] = &DiningRoom;
  allRooms[8] = &Ballroom;
  allRooms[9] = &MrBoddysGrave;

  int i;
  for (i = 0; i < 10; i++){
        allRooms[i]->name = calloc(16, sizeof(char));
	allRooms[i]->numOutboundConnections=0;
	allRooms[i]->id = i;
  }


  theHall.name = "Hall";
  Conservatory.name = "Conserve";
  Kitchen.name = "Kitchen";
  BilliardRoom.name = "Billiard";
  Lounge.name = "Lounge";
  Study.name = "Study";
  DiningRoom.name = "Dining";
  Ballroom.name = "Ballroom";
  MrBoddysGrave.name = "Grave";
  Library.name = "Library";

  i = 0;
  int j;
  int roomsAdded = 0;
  int random;
  bool alreadyAdded;


  while (i < 7){
      alreadyAdded = false;
      random = rand() % 10;
      for (j = 0; j < roomsAdded; j++){
	if (allRooms[random]->id == rooms[j]->id){
	   alreadyAdded = true;
	   break;
        }
      }
      if (!alreadyAdded){
	rooms[i] = allRooms[random];
	i++;
	roomsAdded++;
      }
  }

  rooms[rand() % 7]->roomLocation = 0;


  // Create all connections in graph
  while (IsGraphFull() == false)
  {
    AddRandomConnection();
  }

  for (i = 0; i < 7; i++)
	rooms[i]->roomLocation = 1;

  rooms[rand() % 7]->roomLocation = 0;



  while (true){
    random = rand() % 7;
    if (rooms[random]->roomLocation != 0){
        rooms[random]->roomLocation = 2;
        break;
    }
  }
  

 
  strcat(roomsDir, "/room_");
  int dirNameLen = strlen(roomsDir);
  int roomNameLen;
  int file_descriptor;
  char connectionNumber[1];
  for (i = 0; i < 7; i++){
	roomNameLen = strlen(rooms[i]->name);
	strcat(roomsDir, rooms[i]->name);
	file_descriptor = open(roomsDir, O_WRONLY | O_CREAT, 0600);
	
	write(file_descriptor, "ROOM NAME: ", 11);
	write(file_descriptor, rooms[i]->name, roomNameLen);
	write(file_descriptor, "\n", 1);
	j=0;
	while (j < rooms[i]->numOutboundConnections){
	    sprintf(connectionNumber, "%d", j); 
	    write(file_descriptor, "CONNECTION ", 11);
	    write(file_descriptor, connectionNumber, sizeof(char));
	    write(file_descriptor, ": ", 2);
	    write(file_descriptor, rooms[i]->outboundConnections[j]->name, strlen(rooms[i]->outboundConnections[j]->name));
	    write(file_descriptor, "\n", 1);
	    j++;
        }
	switch(rooms[i]->roomLocation){

	  case 0  :
		write(file_descriptor, "ROOM TYPE: START_ROOM\n", 22);
		break;
	  case 1  :
		write(file_descriptor, "ROOM TYPE: MID_ROOM\n", 20);
		break;

	  case 2  :
		write(file_descriptor, "ROOM TYPE: END_ROOM\n", 20);
		break;
	}
	close(file_descriptor);
	memset(roomsDir + dirNameLen, '\0', roomNameLen);
  }


  return 0;
 
}






