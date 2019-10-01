#include "arrow_movement.h"	
#include "ls_edited.h"
#include<stack>
#include<string>
#include<string.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<vector>
#include <limits.h>
#include <sys/stat.h>
#include<stdio.h>
#include<fstream>
struct winsize t;
extern stack <string> dir_path_right;
extern stack <string> dir_path_left;
using namespace std;
extern char ch; 
extern vector <int> length;
extern string status;
int  rows, cols,offset=1,base=1;
int command_line();

string del_dir(string temp){
	int size=temp.size(),i;
	for(i=size-1;temp[i]!='/';i--){
	}
	dir_path_right.push(temp);
	temp.erase(i,size);
	return temp;
}

void status_bar(int rows, int cols){
	gotoxy(rows-3, 1);
	for(int i=1;i<=cols;i++){
		cout<<"-";
	}
	cout<<"\n";
	cout<<"Current location: ";
	cout<<"\n";
	cout<<"Please type your command: ";
	cout<<endl;
}

void arrow_movement(struct dirent **namelist,int n){
//cout<<1;
struct termios initial_settings, new_settings;
int y=1;
  int choice = 0;
  FILE *input;
  FILE *output;

  if (!isatty(fileno(stdout))) {
        fprintf(stderr,"You are nott a terminal, OK.\n");
        }
        input = fopen("/dev/tty", "r");
        output = fopen("/dev/tty", "w");
        if(!input || !output) {
        fprintf(stderr, "Unable to open /dev/tty\n");
        exit(1);
        }
        tcgetattr(fileno(input),&initial_settings);
        new_settings = initial_settings;
        new_settings.c_lflag &= ~ICANON;
        new_settings.c_lflag &= ~ECHO;
        if(tcsetattr(fileno(input), TCSANOW, &new_settings) != 0) {
        	fprintf(stderr,"could not set attributes\n");
  		}
	gotoxy(rows-2,20);
	cout<<dir_path_left.top();
	while(ch!='q'){
		ioctl(STDIN_FILENO,TIOCGWINSZ,&t);
		rows=t.ws_row;
		cols=t.ws_col;
		status_bar(rows,cols);
		gotoxy(base,1);
		ch = getchar();	  
        if (ch == '\033'){
         // if the first value is esc
            getchar(); // skip the [
            switch(getchar()){ // the real value
            case 'A':
                    // move up
					if(n>rows-5){
						if(base == 1 && offset==1){
							continue;									
							//ls_edited(namelist[offset-1]->d_name,offset-1,status);
						}
						else if(base == 1 && offset > (rows-5)){
							offset--;
							//cout<<"offset"<<offset-1<<" base:"<<base;
							//cout<<"base:"<<base<<"offset"<<offset;
							status="navigation";
							//prev_base=base;
							ls_edited(dir_path_left.top(),offset-1,status);
							gotoxy(base,1);							
						}
						else if(base >1 && base<=(rows-5)){
							offset--; //subtracting first as we have to move up and check whether the previous directory 										//need wrap around or not
							base--;
							//cout<<"offset"<<offset-1<<" base:"<<base;
							//cout<<"base:"<<base<<"offset"<<offset;
							/*if(length[offset-1] > cols){
							int diff=length[offset-1]/cols;
							//	prev_base=base-diff-1;
							gotoxy(base-diff-1,1);
							}
							else{
							//	prev_base=base-1;
							gotoxy(base-1,1);
							}*/
						}
						else if(base == 1 && offset <= (rows-5)){
							offset--;	
							//cout<<"offset"<<offset-1<<" base:"<<base;
							//cout<<"base:"<<base<<"offset"<<offset;
							status="navigation";
							ls_edited(dir_path_left.top(),offset-1,status);
							//prev_base=base;
							gotoxy(base,1);							
						}
					}
					else{
						if (base!=1)
							base--;
						//cout<<"offset"<<offset-1<<" base:"<<base;
							//cout<<"base:"<<base<<"offset"<<offset;
							/*if(length[offset-1] > cols){
								int diff=length[offset-1]/cols;
								//prev_base=base-diff-1;
								gotoxy(base-diff-1,1);
							}
						else{
								//prev_base=base-1;
								gotoxy(base-1,1);
						}*/					
					}
                    break;
                case 'B'://down arrow
					//cout<<1;
					if(n>rows-5 && offset <=n){
						//cout<<2;
						if(base < rows-5){
							if(length[offset-1]> cols){
								int diff=length[offset-1]/cols;
								//cout<<"diff"<<diff;
								gotoxy(base+diff+1,1);
							}
							else{
								//prev_base=base+1;
								gotoxy(base,1);
							}
							offset++;
							base++;
							status="navigation";
							//ls_edited(namelist[offset-1]->d_name,offset-rows-5-1,status);
							//prev_base=base;
							//gotoxy(base,1);							
						}
						else if(base==rows-5 && offset>=rows-5){
							if(length[offset-1]> cols){
								int diff=length[offset-1]/cols;
								//cout<<"diff"<<diff;
								gotoxy(base+diff+1,1);
							}	
							else{
								//prev_base=base+1;
								gotoxy(base,1);
							}
							//cout<<"offset abc"<<offset-1<<" base:"<<base;
							offset++;
							ls_edited(dir_path_left.top(),offset-rows+5-1,status);												
							//base++;
						}
					}			
					if(n<=rows-5){
						//cout<<3;							
						/*if(length[offset-1]> cols){
								//cout<<4;
								int diff=length[offset-1]/cols;
								//cout<<"diff"<<diff<<endl;
								//prev_base=base+diff+1;
								gotoxy(base+diff+1,1);
						}
						else{
						//cout<<5;
						//prev_base=base+1;
						gotoxy(base,1);						
						}*/
						//cout<<"n"<<n;
						if(base<=n){
							base++;
							//cout<<"offset"<<offset;
							offset++;
						}
					}
                    break;
                case 'C':// arrow right
                    if(!dir_path_right.empty()){
						string temp=dir_path_right.top();
						dir_path_right.pop();
						dir_path_left.push(temp);
						status="right navigation";
						ls_edited(temp,0,status);
					}                                                
                    break;
                case 'D':// arrow left                                      
					string temp=dir_path_left.top();	
					dir_path_left.pop();
					if(!dir_path_left.empty()){
						gotoxy(rows,1);	
						dir_path_right.push(temp);
						//cout<<dir_path_left.top();
						//dir_path_left.pop();
						//getchar();
						status="left navigation";
						ls_edited(dir_path_left.top(),0,status);
					}	
                    break;
            }
        }
		if(ch == ':'){
			int temp=rows-1;
			//cout<<"before goto "<<rows-1;
			printf("%s%d%s%s","\033[",1,";","K");
			status_bar(rows,cols);
			gotoxy(rows-1,27);
			command_line();
			//cout<<"using :";
		}
		if(ch == '\n'){
			//cout<<"Entered";
			if(offset>rows-5)
				offset-=1;
			if(offset==n && n>rows)
				offset--;
			gotoxy(1,1);
			struct stat thestat;
			char buf[512];				
			sprintf(buf, "%s/%s",(dir_path_left.top()).c_str(), namelist[offset-1]->d_name);
		  	stat(buf, &thestat);     				
			if((thestat.st_mode & S_IFMT) == S_IFDIR) {
				string temp =namelist[offset-1]->d_name;	
				//cout<<temp;
				//getchar();	
				string temp2=dir_path_left.top();	
				if(strcmp(temp.c_str(),"..")==0  && (strcmp(temp2.c_str(),".")!=0)){
					dir_path_right.push(dir_path_left.top());
					temp=del_dir(dir_path_left.top());
					dir_path_left.pop();
					dir_path_left.push(temp);
					//getchar();
					status="Entering another directory";
					gotoxy(1,1);
					//cout<<1;
					//getchar();
					base=1;
					offset=1;
					ls_edited(dir_path_left.top(),0,status);
					//cout<<2;
					gotoxy(1,1);
					break;
				}
				else if(strcmp(temp.c_str(),"..")==0  && (strcmp(temp2.c_str(),".")==0)){
					gotoxy(1,1);
				}
				else if(strcmp(temp.c_str(),".")==0){
					gotoxy(1,1);
					//cout<<x<<endl;
				}
				else{
					temp=dir_path_left.top();
					temp.append("/");
					temp.append(namelist[offset-1]->d_name);
					dir_path_left.push(temp);
					//getchar();
					status="Entering another directory";
					cout<<3;
					//getchar();
					base=1;
					offset=1;
					//cout<<offset;
					ls_edited(temp,0,status);
					//cout<<4;
					gotoxy(1,1);
					break;
				}
			}	
			if(S_ISREG(thestat.st_mode)){
				int pid=fork();
				if(pid==0){
					execl("/usr/bin/xdg-open","xdg-open",namelist[offset-1]->d_name,(char *)0);
					exit(1);
				}
			}
		}
		if(ch==127){
			gotoxy(rows,1);
			string p=dir_path_left.top();
			if(strcmp(p.c_str(),".")!=0){
				string temp=del_dir(dir_path_left.top());
				dir_path_left.pop();									
				dir_path_left.push(p);
				dir_path_left.push(temp);
				getchar();
				status="backspace";
				ls_edited(temp,0,status);
			}
		}
		if(ch=='h'){
			string p=dir_path_left.top();
			if(strcmp(p.c_str(),".")!=0){
				dir_path_left.push(".");
				status="home pressed";
				ls_edited(dir_path_left.top(),0,status);
			}	
		}
	}
                
 tcsetattr(fileno(input),TCSANOW,&initial_settings);    
}

int command_line(){
	char ch;
	vector <string> mycom;
	string temp;
	int length=0;
	int iterator=1;
	while(iterator){
		ch=getchar();
		//cout<<1;
		if(ch==27)
			iterator=0;
		else if(ch!='\n'){
			cout<<ch;
			if(ch==' '){
				//cout<<2;
				//cout<<temp;
				length++;
				//cout<<length;
				mycom.push_back(temp);
				temp.clear();
			}
			else{
				length++;
				//cout<<length;
				temp+=ch;
			}
		}
		else{
			gotoxy(rows-1,length+27);
			length=0;
			if(!mycom.empty()){
				mycom.push_back(temp);
				//cout<<4;		
				//cout<<mycom[0];
				if(mycom[0]=="snapshot"){
					//cout<<1;
					struct dirent **namelist;
					char buf[512];
					struct stat thestat;
					int n;
					//cout<<2;
					n=scandir(mycom[2].c_str(),&namelist,NULL,alphasort);
					//cout<<3;
					if(stat(mycom[2].c_str(), &thestat)){
						//	cout<<4;
							snapshot(mycom[1],mycom[2]);
						//	cout<<5;
					}
					else{
						//	cout<<6;
							cout<<"File already exists";
						//	cout<<7;
					}
					for(int i=mycom.size()-1;i>=0;i--){
						mycom.pop_back();
					}
					status_bar(rows,cols);
				}
				else if(mycom[0]=="rename"){
					rename(mycom[1],mycom[2]);
					for(int i=mycom.size()-1;i>=0;i--){
						mycom.pop_back();
					}
					status_bar(rows,cols);
				}
				else if(mycom[0]=="create_file"){
					create(mycom[0],mycom[1],mycom[2]);
					for(int i=mycom.size()-1;i>=0;i--){
						mycom.pop_back();
					}
					status_bar(rows,cols);
				}
				else if(mycom[0]=="create_dir"){
					create(mycom[0],mycom[1],mycom[2]);
					for(int i=mycom.size()-1;i>=0;i--){
						mycom.pop_back();
					}
					status_bar(rows,cols);
				}	
				else if(mycom[0]=="search"){
					search(mycom[1],mycom[2]);
					cout<<"Pres backspace to go back.";
					char t=getchar();
					if(t==127){
						for(int i=mycom.size()-1;i>=0;i--){
							mycom.pop_back();
						}
						temp.clear();
						ls_edited(dir_path_left.top(),0,status);

					}
					status_bar(rows,cols);
				}
				else if(mycom[0]=="goto"){
					if(mycom[1]=="/"){
						dir_path_left.push(".");
						for(int i=mycom.size()-1;i>=0;i--){
							mycom.pop_back();
						}
						ls_edited(".",0,status);
					}
					else{
						dir_path_left.push(mycom[1]);
						for(int i=mycom.size()-1;i>=0;i--){
							mycom.pop_back();
						}
						ls_edited(mycom[1],0,status);
					}
				}
				else if(mycom[0]=="copy"){
					copy(mycom[1],mycom[2]);
					for(int i=mycom.size()-1;i>=0;i--){
							mycom.pop_back();
					}
				}
				else if(mycom[0]=="delete_dir"){
					del(mycom[0],mycom[1]);
					for(int i=mycom.size()-1;i>=0;i--){
							mycom.pop_back();
					}
				}
				else if(mycom[0]=="delete_file"){
					del(mycom[0],mycom[1]);
					for(int i=mycom.size()-1;i>=0;i--){
							mycom.pop_back();
					}
				}
				else if(mycom[0]=="move"){
					move(mycom[1],mycom[2]);
					for(int i=mycom.size()-1;i>=0;i--){
							mycom.pop_back();
					}
				}
				temp.clear();
				//cout<<1;
				printf("\033[1K");
				//cout<<"\033["<<rows-1<<";"<<
				status_bar(rows,cols);
				gotoxy(rows-1,27);
				//cout<<2;
			}
		}	
		if(ch==127){
			if(!temp.empty()){
	            cout<<"\b \b";
	            temp[temp.size()-2]='\0';
	        }
        }	
	}
return 0;
}
//g++ -g main_prog.cpp ls_edited.h ls_1.cpp arrow_movement.h arrow_movement.cpp
