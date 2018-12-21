#include "ls_edited.h"
#include "arrow_movement.h"
#include<stack>
#include<string>

using namespace std;
stack <string> dir_path_left;
stack <string> dir_path_right;
extern struct dirent **namelist;
extern int n;
string status;
char ch;

int main(){
	dir_path_left.push("."); 
	string temp;
	status="First Call";
	temp=dir_path_left.top();
	ls_edited(temp,0,status);		
}
