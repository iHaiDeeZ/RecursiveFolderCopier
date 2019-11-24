	/* 
 *  Author: ShiroKlein
 *  Description: KiwiDog Task
 */
 
#include<stdio.h>
#include<dirent.h>
#include<string.h>
//#include <sys/stat.h>
#include <errno.h>	
#include <stdlib.h>
void copying_file(char *filecopied,char *argm);
int isFile(const char *ff_name);
void openandclosedir(char *argn,char* filepath);
int copying_folders(char *foldercopied, char *path);

int main(int argc, char* argv[] ){
	
  char* originalpath= ".";

	//Messages to be printed

		openandclosedir(originalpath, originalpath);

	return 0;


}
// Open Parent Dir 
void openandclosedir(char *argn,char* filepath)
{
	FILE *Shiro,*Tut1;
	DIR* folder;
	struct dirent *shit;

  char *currentPath, *NextPath;
  
   // Go Parent directory, then Open RecursiveFolderCoper Folder
  
	//struct stat file_info;
	char Arr[512];
	//Shiro = fopen("Gay123.txt","r");
	//Tut1 = fopen("Tut1.txt","w");

  if (argn != "."){
    currentPath =filepath;
    sprintf(NextPath,"%s/%s/",currentPath,argn);

  }
  else{
    currentPath=".";
    NextPath=".";

  }
   folder = opendir(currentPath);

	//Checks folder/file Situation Open/NOTopen
		if ( folder == NULL ){ // Shiro == NULL && Tut1 == NULL &&
			//Printfail message
		printf("Sorry, File/Folder has not been opened");
	
	}


	else{
		//print success message
		printf("File opened successlly");
			
			/*fscanf(Shiro,"%[^\0]s",Arr); proof of concpet learning
			fprintf(Tut1,"%s\n Znullptr is gay ",Arr);*/

        		while((shit=readdir(folder))!=NULL){
        			if (strcmp(shit->d_name, ".") == 0) continue;   /* current dir */
    				if (strcmp(shit->d_name, "..") == 0) continue;  /* parent dir  */
    				
    				if((isFile(shit->d_name) == 1) ){
     					printf("%s\t",shit->d_name);
     					printf("This is not a direcotry\n");
              
     					copying_file(shit->d_name, NextPath);
    				}
    				if(isFile(shit->d_name) == 0 ){
            			printf("%s\t",shit->d_name);
     					printf("This is a direcotry\n") ;    
                      copying_folders(shit->d_name,NextPath);    		
            						}


            							}
			closedir(folder);
			//fclose(Tut1);
			//fclose(Shiro);
	}

}

int isFile(const char *ff_name)
{

	char fileX[]= "./";
	strcat(fileX,ff_name);

	DIR* directory =opendir(fileX);
    

    if(directory != NULL)
    {
     
     return 0;
    }


    if(errno == ENOTDIR)
    {
     return 1;
    }

    return -1;
}
// Copies files existed in the Dir
void copying_file(char *filecopied,char *argm)
{
	char ch;
  char *filepath="../RecursiveFolderCopier/";;

	FILE *original,*target;

  long size;
	original = fopen(filecopied,"r");

	 if (original == NULL)
   {
      printf("Press any key to exit...\n");
      exit(EXIT_FAILURE);
   }
   strcat(filepath,filecopied);
   target = fopen(filepath, "w");

   	if(target == NULL)
    {
        
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    //copies file char by char
     while ((ch = fgetc(original)) != EOF)
      fputc(ch, target);
        size= ftell(target);
  	   printf(" %s successfully copied.\n %s Size : %ld bytes ",filecopied,filecopied,size);

 
   fclose(original);
   fclose(target);

}


int copying_folders(char *foldercopied, char *path)
{
	char ch,*folderpath="../RecursiveFolderCopier/";
  char *Hpath;
  sprintf(Hpath,"%s/%s",folderpath, path);
	DIR* folder1;
	  folder1 = opendir(Hpath);

	
	if(folder1 == NULL)
    {
     
     return EXIT_FAILURE;
    }

    else{

    	
        mkdir(foldercopied);
    	 openandclosedir(foldercopied,path);


    }


}

/* UnWanted commentes
lstat(shit->d_name,&file_info);

            		puts(dir_element->d_name);                       // show current filename
        		printf("file mode: %d\n", file_info.st_mode);*/



/* Refrences 

https://www.programmingsimplified.com/c-program-copy-file

https://www.tutorialspoint.com/cprogramming/c_structures.htm
https://www.programiz.com/c-programming/c-structures-pointers
https://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html
https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/rtope.htm
https://www.tutorialspoint.com/c_standard_library/c_function_fclose.htm
https://fresh2refresh.com/c-programming/c-strings/c-strcat-function/
https://en.cppreference.com/w/cpp/error/errno
https://www.zentut.com/c-tutorial/c-write-text-file/
https://stackoverflow.com/questions/8149569/scan-a-directory-to-find-files-in-c
https://stackoverflow.com/questions/4553012/checking-if-a-file-is-a-directory-or-just-a-file
https://www.geeksforgeeks.org/basics-file-handling-c/
https://www.geeksforgeeks.org/create-directoryfolder-cc-program/
https://www.gnu.org/software/libc/manual/html_node/Error-Codes.html
https://android.googlesource.com/kernel/lk/+/upstream-master/include/errno.h
http://www.cplusplus.com/reference/cstdio/ftell/
*/
