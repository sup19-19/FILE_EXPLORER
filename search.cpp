#include"arrow_movement.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include<iostream>
#include <string>
#include <ftw.h>
#include<unistd.h>
int check_clr=0;
string file, curr_dir;
static int display_info(const char *fpath, const struct stat *sb,int tflag, struct FTW *ftwbuf)
{	//string temp=curr_dir+"/"+file;
	//cout<<temp<<endl;
    if((strcmp(fpath + ftwbuf->base,file.c_str()))==0){
    	cout<<fpath<<endl;
    	if(check_clr==0){
    		printf("\033[3J");
			printf("\033[H\033[J");
			check_clr=1;
		}
		cout<<fpath<<endl;
    }	
	return 0;    
}


int search(string s1,string s2){
	int flags=0;
	file=s1;
	curr_dir=s2;
	//cout<<curr_dir;
	if (nftw(curr_dir.c_str(), display_info, 20, flags)== -1) {
        perror("nftw");
        exit(EXIT_FAILURE);
    }
	return 0;
}



