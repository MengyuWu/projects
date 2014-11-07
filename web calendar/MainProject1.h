//
//  MainProject1.h
//  step1
//
//  Created by 吴梦宇 on 6/18/14.
//  Copyright (c) 2014 ___mengyu wu___. All rights reserved.
//

#ifndef step1_MainProject1_h
#define step1_MainProject1_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>


void showFirstForm();//login form

void  MeetForm();  // for : username/startdate...
int getmonth(char *m); // put in June, get 6
int chartoint(char * c); // from char to in
int urldecode(char *str, int len); // decode url;



void addmeet(char * uname);//step3 (1) add new meeting
void savemeet(char *info);// savemeet; for step3 and step4 
void viewmeet(char *uname);// step3 (2) show all current meetings added to the system by this user


void caladdmeet(char * info);//step4 calendar add meeting;


void twodays(char *twodayinfo);//step5 (2)schedule between 2 dates
void specfictime(char *specficinfo);//step5 (3)all schedule between 2 dates and between specific times
void searchstr(char* searchstr); //step5 (4)search string;


//variable

char *qstring; //query string

char *temp;


//only use once
int testlen;

char *password;



char *result;
char *part1[3];
char *value[3];
int i=0;

FILE *fr;
char *part2[3];

int login=-1;





char md5password[128];
char *command;






//new here

char *option=" "; //default
char *thisuser=" ";//default

//  char *option="newmeet"; //default
// char *thisuser="mw2907";//default
char *tmpstr;


//caladdmeet
char* info;
char* tail;





#endif
