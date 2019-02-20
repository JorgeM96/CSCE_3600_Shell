/* 
* CSCE 3600 Major 1 Shell Assignment
* Author 1: Jorge Moreno Email: JorgeMoreno3@my.unt.edu EUID: JM1066
* Author 2: Tate Mosier Email: tatemosier@my.unt.edu EUDI: TCM0106
* Author 3: Justin Paul Email: JustinPaul2@my.unt.edu EUID: JKP0126
* Author 4: Hector Tamez Email: HectorTamez@my.unt.edu EUID: HT0158
*/
#include "ShellConstants.h"

int main(int argc,char *argv[])
{
  int batchMode = checkmode(argc);
  int next = true, stop = false;
  if(batchMode == 1)
  {
    batchFile = fopen(argv[1],"r+");
    if(batchFile == NULL)
    {
      batchMode = false;
      perror("File could not open, switching to interactive mode...\n");
    }
  }
  while(next == true)
  {
    if(batchMode == 1)
    {
      next = nextEntry(batchFile,batchMode,&stop);
    }
		else
		{
			printf("Prompt >");
			next = nextEntry(stdin,batchMode,&stop);
		}
  }
  return 0;
}