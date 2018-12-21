#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include<stdio.h>
#include <string.h>
#include<string>
#include <stdint.h>
#include <sys/stat.h>
using namespace std;


static int display_info(const char *fpath, const struct stat *sb,int tflag, struct FTW *ftwbuf){
	int e=remove(fpath);
	return e;
}

int del(string com,string source){
	if(com=="delete_dir"){
		if (nftw(source.c_str(), display_info, 20, FTW_DEPTH)== -1) {
	        perror("nftw");
	        exit(EXIT_FAILURE);
	    }
	}
	if(com=="delete_file"){
		if( remove(source.c_str()) != 0 )
    		perror( "Error deleting file" );
    }
  	return 0;
}