#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>

enum position{START_ROOM, MID_ROOM, END_ROOM};

struct Room
{

  int id;
  char* name;
  int numOutboundConnections;
  struct Room* outboundConnections[5];
  enum position roomLocation;

};

struct Room *A;
struct Room *B;
struct Room *allRooms[10];
struct Room *rooms[7];

//int iterableRooms = 10;
//struct Room *remainingRooms[10];

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
/*
	else if (CanAddConnectionFrom(rooms[i])){
	  for (j = 0; j < 7; j++){
	      if (!ConnectionAlreadyExists(rooms[i], rooms[j]) && !IsSameRoom(rooms[i], rooms[j]) && CanAddConnectionFrom(rooms[j])){
		  return false;
	      }
	  }
 */       }
    }	
    return true;

}


void AddRandomConnection()  
{
  int i;

  while(true)
  {
    A = GetRandomRoom();

    if (CanAddConnectionFrom(A) == true)
      break;
  }

  for (i = 0; i < 7; i++)
	printf("Connections in room %s: %d\n", rooms[i]->name, rooms[i]->numOutboundConnections);

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
  srand(time(0));
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
  x->numOutboundConnections++;
  x->outboundConnections[x->numOutboundConnections - 1] = y;
  /*if (!CanAddConnectionFrom(x))
    resizeRoomsArr(x);*/
}


bool IsSameRoom(struct Room* x, struct Room* y)
{
  if (x->id == y->id)
        return true;
  return false;
}
/*
void resizeRoomsArr(struct Room *x){

  int i;
  for (i = 0; i < iterableRooms; i++){
	if (remainingRooms[i]->id == x->id){
	   remainingRooms[i] = remainingRooms[iterableRooms-1]; 
	   iterableRooms--;
	   break;
        }

  }
}*/


int main()
{

  
  char roomsDir[] = "shielcon.rooms.";
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

  for (i = 0; i < 10; i++)
        rooms[i]->name = calloc(16, sizeof(char));

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


  for (i = 0; i < 10; i++){
        rooms[i]->id = i;
        rooms[i]->numOutboundConnections=0;
	rooms[i]->roomLocation = MID_ROOM;
  }

  int i = 0;
  int j;
  int roomsAdded = 0;
  int random;
  bool alreadyAdded;

  srand(time(0));

  while (i < 7){
      alreadyAdded = false;
      random = rand() % 7;
      for (j = 0; j < roomsAdded; j++){
	if (allRooms[random]->id == rooms[j]->id)
	   alreadyAdded = true;
	   break;
      }
      if (alreadyAdded)
	continue;
      else {
	rooms[i] = allRooms[random];
	i++;
      }
  }

  bool endExists = false;

  rooms[rand() % 7]->roomLocation = START_ROOM;

  while (!endExists){
    random = rand() % 7
    if (rooms[random]->roomLocation != START_ROOM){
	rooms[random]->roomLocation = END_ROOM;
	break;
    }


  // Create all connections in graph
  while (IsGraphFull() == false)
  {
    AddRandomConnection();
  }

  printf("done\n");

  int j;

  for (i = 0; i < 10; i++){
	for (j = 0; j < rooms[i]->numOutboundConnections; j++)
	    printf("%d: %s\n", j, rooms[i]->outboundConnections[j]->name);
  }

  return 0;
 
}






