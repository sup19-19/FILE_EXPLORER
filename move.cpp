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
#include "arrow_movement.h"
using namespace std;

int move(string to_be_moved,string dest){	
	struct stat thestat;
	stat(to_be_moved.c_str(), &thestat);
	if((thestat.st_mode & S_IFMT) == S_IFDIR){
		copy(to_be_moved,dest);
		del("delete_dir",to_be_moved);
	}
	if((thestat.st_mode & S_IFMT) == S_IFDIR){
		copy(to_be_moved,dest);
		del("delete_file",to_be_moved);
	}
	return 0;
}