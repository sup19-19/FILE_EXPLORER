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
#include<fstream>

using namespace std;

int create(string command,string create_name, string arg_path){
	if(strcmp(command.c_str(),"create_dir")==0){
        string temp=arg_path+"/"+create_name;
        const int d = mkdir(temp.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    if(strcmp(command.c_str(),"create_file")==0){
        string temp=arg_path+"/"+create_name;
        ofstream fout;
        fout.open(temp);
        fout.close();
    }    return 0;
}