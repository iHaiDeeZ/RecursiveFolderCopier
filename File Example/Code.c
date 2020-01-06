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
#include <unistd.h>

#include <limits.h>
void copying_file(char *filecopied,char *argm);
void openandclosedir(char filepath[]);
//void openandclosedir2(char *argn,char* filepath);
int copying_folders(char *foldercopied, char *path);
int isFile(char *checkpath,const char *ff_name);
const char *  FolderPathcorrector(char *sher);




int main(int argc, char* argv[] ){
	
  char* originalpath= ".";

	//Messages to be printed

		openandclosedir(originalpath);

	return 0;


}
// Open Parent Dir 
void openandclosedir(char filepath[])
{
	//FILE *Shiro,*Tut1;
	DIR* folder;
	struct dirent *shit;

  char *currentPath;
  
   // Go Parent directory, then Open RecursiveFolderCoper Folder
  
	//struct stat file_info;
	//char Arr[512];
	//Shiro = fopen("Gay123.txt","r");
	//Tut1 = fopen("Tut1.txt","w");

  if (filepath[0] != "."){
    currentPath =filepath;
    

  }
  else{
    currentPath=".";
    

  }
   folder = opendir(currentPath);

	//Checks folder/file Situation Open/NOTopen
		if ( folder == NULL ){ // Shiro == NULL && Tut1 == NULL &&
			//Printfail message
		printf("Sorry, File/Folder has not been opened\n");
	
	}


	else{
		//print success message
		printf("Folder opened successlly\n");
			
			/*fscanf(Shiro,"%[^\0]s",Arr); proof of concpet learning
			fprintf(Tut1,"%s\n Znullptr is gay ",Arr);*/

        		while((shit=readdir(folder))!=NULL){

        			if (strcmp(shit->d_name, ".") == 0) continue;   /* current dir */
    				if (strcmp(shit->d_name, "..") == 0) continue;  /* parent dir  */
    				
    				if((isFile(currentPath,shit->d_name) == 1) ){
     					printf("%s\t",shit->d_name);
     					printf("This is not a direcotry\n");
              
     					copying_file(shit->d_name,currentPath);
    				}
    				else{
            			printf("%s\t",shit->d_name);
                  //printf("%s\t",shit->d_type);
     					printf("This is a direcotry\n") ;    
                      copying_folders(shit->d_name,currentPath);    		
            						}


            							}
			closedir(folder);
			//fclose(Tut1);
			//fclose(Shiro);
	}

}

int isFile(char *checkpath,const char *ff_name)
{
  char *rpath;
    if (checkpath !="."){

    sprintf(rpath,"%s/%s",checkpath,ff_name);


}
else{ 

  rpath = ff_name;
}  
	
	

	DIR* directory =opendir(rpath);
    

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
  char filepath[]="../RecursiveFolderCopier/";
  char tpath[260]="",rpath[260]="";
	
    if (argm !="."){

    //sprintf(rpath,"%s/%s",argm,filecopied);
    
    strcat(rpath,argm);
    strcat(rpath,"/");
    strcat(rpath,filecopied);
	
    sprintf(tpath,"%s/%s/%s",filepath,FolderPathcorrector(argm),filecopied);

}
else{ 

  strcat(rpath,filecopied);

  sprintf(tpath,"%s/%s",filepath,filecopied);
 
}  
	


	FILE *original,*target;

  long size;
	original = fopen(rpath,"r");

	 if (original == NULL)
   {
      printf("Press any key to exit...\n");
      exit(EXIT_FAILURE);
   }
   strcat(filepath,filecopied);
   target = fopen(tpath, "w");

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
char *folderpath="../RecursiveFolderCopier/";
  char *tpath,t2path[512];
  if (path !="."){

   
    sprintf(t2path,"%s/%s",path,foldercopied);
    sprintf(tpath,"%s/%s/%s",folderpath,FolderPathcorrector(path),foldercopied);
    mkdir(tpath);

}
else{ 

  
  sprintf(t2path,"./%s",foldercopied);
  sprintf(tpath,"%s/%s",folderpath,foldercopied);
  
 mkdir(tpath);
 printf("successfully created %s \n", foldercopied);
}  
  
	
  	DIR* folder1;
	  folder1 = opendir(tpath);

	
	if(folder1 == NULL)
    {
     
     return EXIT_FAILURE;
    }

    else{

      printf("%s\n", t2path);
        //openandclosedir(foldercopied,t2path);
    	openandclosedir(t2path);

    }


}
const char *  FolderPathcorrector(char *sher)
{




   char word2[512];

   strcpy(word2,&sher[2]);

   return word2;

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
