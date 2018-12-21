#include "ls_edited.h"
#include "arrow_movement.h"
#include<stack>
#include<string>
#include<string.h>
#include<sys/ioctl.h>
#include <limits.h>
#include <sys/stat.h>
#include<unistd.h>
#include<vector>
vector <int> length;
extern stack <string> dir_path_left;
extern string status;
struct dirent **namelist;
int n;
extern int  rows, cols;
extern struct winsize t;
using namespace std;

void ls_edited(string dir_path,int offset, string status)
{	
	int j,temp,print_till,temp_length=0;
	string for_length;
	struct stat thestat;	
	struct passwd *tf; 
	struct group *gf;
	char buf[512];
	printf("\033[3J");
	printf("\033[H\033[J");
	n=scandir(dir_path.c_str(),&namelist,NULL,alphasort);
	//i=n;
	cout<<cols;
	ioctl(STDIN_FILENO,TIOCGWINSZ,&t);
	rows=t.ws_row;
	cols=t.ws_col;
	if(offset == 0){
		gotoxy(0,0);
	}
	if(n > rows-5)
		print_till=offset+rows-5;
	else{	
		print_till=n;	
	}
	//cout<<cols<<" "<<rows<<" "<<n;
	//cout<<" "<<print_till;
	j=offset;	
	//while(j<=(rows-5+offset) && ((rows-5+offset)<=n)){
	for(j=offset;j<print_till;j++){ 
		//cout<<324;
		
			//cout<<j;  
			temp_length=0;     
			sprintf(buf, "%s/%s",dir_path.c_str(), namelist[j]->d_name);
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
			temp_length+=6;

	 	       tf = getpwuid(thestat.st_uid);
			for_length=tf->pw_name;
			temp=for_length.length();
	 	       printf("    %s ", tf->pw_name);

			temp_length+=4+temp;
	 	    gf = getgrgid(thestat.st_gid);
			for_length=gf->gr_name;
			temp=for_length.length();
	 	       printf("    %s ", gf->gr_name);

			temp_length+=4+temp;
	 	       printf("     %6.2fK",thestat.st_size/1024.0);

			temp_length+=7;
			char time[25];
			strcpy(time,ctime(&thestat.st_mtime));
			time[24]='\0';
			time[25]='\0';
	 	       printf("     %s", time);
			temp_length+=29;
		       printf("    %s\n", namelist[j]->d_name);
			for_length=namelist[j]->d_name;
			temp=for_length.size();
			temp_length+=4+temp;
			length.push_back(temp_length);
			//j++;
		
 	   }
	//for(int i=0;i<print_till;i++)
	//	cout<<length[i]<<" ";
	//cout<<endl;
	//cout<<1;
	//getchar();
//	if(strcmp(status.c_str(),"First Call")==0)
		arrow_movement(namelist,n);
} 
