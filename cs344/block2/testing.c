#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
 
int main()
{

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

  printf("Newest entry found is: %s\n", newestDir->d_name);
  return 0;

}
