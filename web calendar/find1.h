//
//  find1.h
//  find1
//
//  Created by 吴梦宇 on 7/4/14.
//  Copyright (c) 2014 ___mengyu wu___. All rights reserved.
//

#ifndef find1_find1_h
#define find1_find1_h
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


//c++
#include <iostream>
#include <string>
#include <vector>

using namespace std;
char* findspot(vector<vector< char* > > gmeet, int startmonth,int startday,int startyear, int starthour, int startmin, int interval);



//c++
vector<char*> userall;
vector <vector <char * > > gmeet;
//  vector <char * > cmeet;
char* smeet;

char * sdates="June,3,2014"; //default
char * stime="10:00am"; //default



// char * interval="3:00";

int interval=3;// defalut;


//after to doing spliting;
char *smonth="June";
char *sday="1";
char *syear="2014";

int iday;
// need to deal with it;
int imonth=1;//default
int iyear=2014;//default;



char *shs;
char *smins;
char *sapms;

int inth;
int intmin;



//string temp;


//c
//system infor variable
DIR * dir;
DIR * fdir;
struct dirent * ptr;
struct dirent * ftr;
int dircount=0;
int filecount=0;

//Note! please create a doc file and change your path
char pathdir[100]="/Library/WebServer/CGI-Executables/doc";



//userinfor variable
char *username;


//seperate process
char *qstring;

int e=0; //whether something is empty

char *result;
char *part1[6];
char *value[6];

int i=0;
int j=0;
//file process

char *pathname;

//search
char *start[3];
char *result2;
char *end[3];
char *result3;

//after get from query string and doing spliting
char *date1="1";
char *date2="20";


//need to change from string to int or ascii;
int d1;
int  d2;

int  sd;
int  ed;




//search specfic time
char *time1="10:00";
char *time2="12:00";
char *hour1;
char *min1;
char *hour2;
char *min2;
char *apm1="am";
char *apm2="am";
int ht1;
int ht2;
int mt1;
int mt2;




char *hour;
//char *min;
char *apm;
int h;
int m;



char *houre;
char *mine;
char *apme;
int he;
int me;


char *temptime;

char *rest;






//input dates

char * results;
char * parts[6];
char * values[6];
char * datein1;


//format of time1in: 10:00am
char *time1in;


char* timelen;



#endif
