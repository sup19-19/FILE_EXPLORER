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
#include<unistd.h>
#include<fstream>
using namespace std;

//ofstream fout;
int snapshot(string  path, string filename ){
	//	cout<<"in snapshot";
	ofstream fout(filename.c_str(),ios::app);
	//fout(path.c_str(),ios::app);
	//cout<<"in snapshot";
	getchar();
	struct dirent **namelist;
	char buf[512], buf_file[512];
	int n;
	struct stat thestat; 
	n=scandir(path.c_str(),&namelist,NULL,alphasort);
	fout<<path<<":"<<endl;
	for(int i=0;i<n;i++){
		//sprintf(buf, "%s/%s",path, namelist[i]->d_name);
		//stat(buf, &thestat);
		if(strcmp(namelist[i]->d_name,".")==0 || strcmp(namelist[i]->d_name,"..")==0)
			continue;
		string temp=namelist[i]->d_name;        	
		fout<<temp<<" ";
	}
	fout<<endl;
	for(int i=0;i<n;i++){
		//cout<<1;
		sprintf(buf, "%s/%s",path.c_str(), namelist[i]->d_name);
		stat(buf, &thestat);        	
		//cout<<buf<<endl;
		if(strcmp(namelist[i]->d_name,".")==0 || strcmp(namelist[i]->d_name,"..")==0)
			continue;
		if(S_ISDIR(thestat.st_mode)){
			//cout<<2;
			string x(buf);
			//cout<<x<<" ";
			snapshot(x, filename);
			fout<<endl;
		}
	}
	fout.close();
	return 0;
}
