#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>
using namespace std;

string destination,source,aftercp;
struct  stat thestat;

static int display_info(const char *fpath, const struct stat *sb,int tflag, struct FTW *ftwbuf){
	if(tflag==FTW_F){
		string temp1=fpath + ftwbuf->base;
		string temp=destination+"/"+(temp1);
		cout<<temp<<" ";
		std::ifstream src(source,std::ios::binary);
		std::ofstream dst(temp, std::ios::binary);
		dst<<src.rdbuf();
	}
	if(tflag==FTW_D){
		string temp1=fpath + ftwbuf->base;
		destination=destination+"/"+(temp1);
		cout<<temp1<<" ";
		const int e=mkdir(destination.c_str(),sb->st_mode);
	}
	return 0;
}

int copy(string s, string dest){
	int flags=0;
	source=s;
	destination=dest;
	if (nftw(source.c_str(), display_info, 20, flags)== -1) {
        perror("nftw");
        exit(EXIT_FAILURE);
    }
    return 0;
}