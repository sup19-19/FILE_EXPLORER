#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
using namespace std;

int rename(string oldname, string newname){
	int result;
	//string oldname = "1";
	//string newname = "1_new";	
	result=rename(oldname.c_str(),newname.c_str());
	if(result == 0)	
		cout<<endl<<"File successfully renamed";
	else
		cout<<endl<<"Error renaming file";
	return 0;
}
