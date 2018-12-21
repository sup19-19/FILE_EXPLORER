#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include<string.h>
#include "arrow_movement.h"

int main(int argc, char* argv[])
{
	struct dirent **namelist;
	int n;
	struct stat thestat;        
	struct passwd *tf; 
	struct group *gf;
	char buf[512];
	printf("\033[H\033[J");

	n = scandir(".",&namelist,NULL, alphasort);
	if(n<0){
		perror("scandir");
		exit(EXIT_FAILURE);
	}
	else if(argc==1){
		n=scandir(".",&namelist,NULL,alphasort);
	}
	else{
		n=scandir(argv[1],&namelist,NULL,alphasort);
	}	

	while(n--){        
		sprintf(buf, "%s/%s", argv[1], namelist[n]->d_name);
        	stat(buf, &thestat);        	
        	printf( (thestat.st_mode & S_IRUSR) ? "r" : " -");
        	printf( (thestat.st_mode & S_IWUSR) ? "w" : "-");
        	printf( (thestat.st_mode & S_IXUSR) ? "x" : "-");
        	printf( (thestat.st_mode & S_IRGRP) ? "r" : "-");
        	printf( (thestat.st_mode & S_IWGRP) ? "w" : "-");
        	printf( (thestat.st_mode & S_IXGRP) ? "x" : "-");
        	printf( (thestat.st_mode & S_IROTH) ? "r" : "-");
        	printf( (thestat.st_mode & S_IWOTH) ? "w" : "-");
        	printf( (thestat.st_mode & S_IXOTH) ? "x" : "-");
	
 	       tf = getpwuid(thestat.st_uid);
 	       printf("\t%s ", tf->pw_name);

 	       gf = getgrgid(thestat.st_gid);
 	       printf("\t%s ", gf->gr_name);

 	       printf("\t%zu",thestat.st_size);
		char time[25];
		strcpy(time,ctime(&thestat.st_mtime));
		time[24]='\0';
		time[25]='\0';
 	       printf(" \t%s", time);
	       printf(" %s\n", namelist[n]->d_name);
 	   }
 	   free(namelist);
	   arrow_movement();
}
