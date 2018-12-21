#include <stdlib.h>
#include <stdio.h>
#include<iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include<dirent.h>
#include<stack>

#define gotoxy(x,y) printf("%s%d%s%d%s","\033[",(x),";",(y),"H");
using namespace std;

void arrow_movement(struct dirent **namelist, int n);
int snapshot(string path, string filename);
int rename(string oldname, string newname);	
int create(string command,string arg_name, string arg_path);
int search(string s1,string s2);
int copy(string source, string destination);
int del(string com, string source);	
int move(string to_be_moved, string dest);