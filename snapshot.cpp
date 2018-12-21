#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include<iostream>
using namespace std;
 int flags = 0;
static int check=1,level_check=0;

static int display_info(const char *fpath, const struct stat *sb,
             int tflag, struct FTW *ftwbuf, int level_check_in_fun)
{
    int count=0;
    if(check){
        if(ftwbuf->level == level_check){
            cout<< fpath + ftwbuf->base<<":"<<endl;
            if (nftw(fpath + ftwbuf->base, recur_disp, 20, flags) == -1,level_check+1) {
                check=0;
                perror("nftw");
                exit(EXIT_FAILURE);
            }
            level_check++;        
        }
    return 0;
    }
}
static int recur_disp(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf, int level_check_in_fun){
    cout<<fpath+ftwbuf->base<<"   ";
}
int main(int argc, char *argv[]){
   if (nftw((argc < 2) ? "." : argv[1], display_info, 20, flags)
            == -1) {
        perror("nftw");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}