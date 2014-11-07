//
//  addgroupmeet.h
//  addgroupmeet
//
//  Created by 吴梦宇 on 7/4/14.
//  Copyright (c) 2014 ___mengyu wu___. All rights reserved.
//

#ifndef addgroupmeet_addgroupmeet_h
#define addgroupmeet_addgroupmeet_h
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <String.h>
#include <stdlib.h>


//c++
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//c++
vector<char*> userall;
vector <vector <char * > > gmeet;
//  vector <char * > cmeet;




//c

//system infor variable
DIR * dir;
DIR * fdir;
struct dirent * ptr;

int dircount=0;

//please change your path
char pathdir[100]="/Library/WebServer/CGI-Executables/doc";



//userinfor variable
char *username;


//seperate process
char *qstring;




int i=0;

//file process

char *pathname;


//add file
FILE *fp;
char* filepath;

//input dates

char * results;




char* newmeet;



#endif
