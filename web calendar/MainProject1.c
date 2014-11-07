//
//  main.c
//  step1
//
//  Created by 吴梦宇 on 6/18/14.
//  Copyright (c) 2014 ___mengyu wu___. All rights reserved.
//
#include "MainProject1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>


#include <sys/stat.h>

char* month[]={"January","February","March","April","May","June","July","August","September","October","November","December"};
char  *user="admin"; //global defalut;


void  MeetForm(){
    printf("<table style=\"width:300px\">");
    printf("<tr>");
    printf("<th>USERNAME</th>");
    printf("<th>STARTDATE</th>");
    printf("<th>STARTTIME</th>");
    printf("<th>ENDDATE</th>");
    printf("<th>ENDTIME</th>");
    printf("<th>SUBJECT</th>");
    printf("<th>INFORMATION</th>");
    printf("</tr>");
    
}

int getmonth(char *m){
    int i=0;
    for(i=0;i<12;i++){
        if(strcmp(m,month[i])==0){
            return i+1;
        }
    }
    return 0;
}


int chartoint(char * c){
    int j=0;
    int val=0;
    int len=strlen(c);
    
    for(j=0;j<len;j++){
        val=val*10+(c[j]-'0');
    }
    
    return val;
}




void searchstr(char* searchstr){
    //system infor variable
    DIR * dir;
    DIR * fdir;
    struct dirent * ptr;
    struct dirent * ftr;
    int dircount=0;
    int filecount=0;
    //char pathdir[100]="/Users/wmy/Desktop/project1/step3/step3/temp";
    char pathdir[100]="/Library/WebServer/CGI-Executables/doc";
    char *pathdirtmp;
    
    
    //userinfor variable
    char *username;
    char * startdate;
    char * starttime;
    char * enddate;
    char * endtime;
    char * subject;
    char * information;
    char * meet;
    
    
    //seperate process
    char *qstring;
    
    char *result;
    
    char *value[6];
    
    int i=0;
    
    //file process
    FILE *fr;
    char *pathname;
    
    
    int j;
    
    int num=0;
    
    char *temp;
    char **info;
    // char info[50];
    //how to improve it?
    //search
    
    
    //need to change from string to int or ascii;
    
    
    //search specfic time
    //query string
    
    char *qstr;
    qstr="group";//default;
    
    //option=4; search for string in file
    
    // insert code here...
    //   printf( "Content-type: text/html\n\n" );
    
    //at beggin; deal with the input query;
    
    
    //    qstring=getenv("QUERY_STRING");
    qstring=(char*)malloc(strlen(searchstr)+1);
    strcpy(qstring,searchstr);
    
    
    
    
    if(strlen(qstring)==0){
        //need modify;
        printf("<a href=\"MainProject1.exe\">Go back,please input query string!</a>");
    }else{
        
        //process qstring;
        
        result=(char*)malloc(sizeof(char)*(strlen(qstring)+1));
        result=strtok(qstring,"=");
        qstr=(char*)malloc(sizeof(char)*(strlen(qstring)+1));
        qstr=strtok(NULL,"=");
        
        
       printf("query string is: %s </p>",qstr);
        
        
        
        dir = opendir(pathdir);
        while((ptr = readdir(dir)) != NULL)
        {
            if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..")==0 || strcmp(ptr->d_name, ".DS_Store")==0)
                continue;    /* skip self and parent */
            
            //count dir user
            
            //problem here should new localtion other wise append after /
            
            pathdirtmp=(char *)malloc(sizeof(char)*strlen(pathdir)+(strlen(ptr->d_name)+1));
            strcat(pathdirtmp,pathdir);
            strcat(pathdirtmp,"/");
            strcat(pathdirtmp,ptr->d_name);
            
            
            //note: should print pathdirtmp;
            //fdir=opendir(pathdir);
            
            fdir=opendir(pathdirtmp);
            
            if(fdir!=NULL){
                //open the inner dirct=user;
                
                //get user name form the dir
                username=ptr->d_name;
                
                //dir
                //printf("user name : %s\n",username );
                dircount++;
                
                while((ftr=readdir(fdir))!=NULL)
                {
                    
                    if(strcmp(ftr->d_name, ".") == 0 || strcmp(ftr->d_name, "..")==0 || strcmp(ftr->d_name, ".DS_Store")==0)
                        continue;    /* skip self and parent */
                    filecount++;
                    
                    //file
               //  printf("Meeting info : %s \n", ftr->d_name);
                    meet=(char *)malloc(sizeof(char)*(strlen(ftr->d_name)+1));
                    strcpy(meet,ftr->d_name);
                    
                    //seperate;
                    //first sperate "."
                    meet=strtok(meet,".");
                    //      printf("meet: %s \n",meet);
                    
                    //second seperate "-" using for loop
                    //don't need first username info
                    
                    meet=strtok(meet,"-");
                    //      printf("value: %s \n",meet);
                    
                    
                    for(i=0;i<6;i++){
                        
                        meet=strtok(NULL,"-");
                        // printf("meet: %s \n",meet);
                        
                        if(meet==NULL){
                            break;
                        }
                        value[i]=(char*)malloc(sizeof(char)*(strlen(meet)+1));
                        strcpy(value[i],meet);
                        //    printf("v: %s \n",value[i]);
                    }
                    
                    //get info from the file name
                    startdate=value[0];
                    starttime=value[1];
                    //now they are empty
                    enddate=value[2];
                    endtime=value[3];
                    
                    
                    //get subject and information by reading file
                    //create a path=dir/filename;
                    pathname=(char*)malloc(sizeof(char)*(strlen(pathdirtmp)+strlen(ftr->d_name)+1));
                    strcat(pathname,"/Library/WebServer/CGI-Executables/doc");
                    strcat(pathname,"/");
                    strcat(pathname,username);
                    strcat(pathname,"/");
                    strcat(pathname,ftr->d_name);
                    
                  //printf("path: %s \n",pathname);
                    
                    
                    if((fr=fopen(pathname,"r"))==NULL){
                        perror("can't read \n");
                        exit(1);
                    }else{
                     // printf("read! \n");
                        
                        //read each line;
                        //note information may very long just one line may not work
                        
                        i=0;
                        temp=(char *)malloc(sizeof(char)*(100));
                        info=(char**)malloc(sizeof(char *)*100);
                        while(fgets(temp,100,fr)!=NULL)
                        {
                            *((info+i))=(char*)malloc(sizeof(char)*(strlen(temp)+1));
                            //chomp \n pay attention here!
                            *(temp+strlen(temp)-1)=' ';
                            *(temp+strlen(temp))='\n';
                            
                            strcpy(*((info+i)),temp);
                            i++;
                        }
                        
                        //subject is info[0];
                        subject=(char *)malloc(sizeof(char)*(strlen(*info)+1));
                        strtok(*info,"=");
                        subject=strtok(NULL,"=");
                        
                        
                        
                       //  printf("subject: %s </p>",subject);
                        
                        
                        
                        
                        //check whether the query string is the content of the subject(subject=)should not be considered as content;
                        
                        
                        
                        
                        //information may have several lines; //realloc(buffer,sizeof(char)*i)
                        
                        temp=(char *)malloc(sizeof(char)*200);
                        
                        j=1;
                        while((*(info+j))!=NULL){
                            strcat(temp,*(info+j));
                            j++;
                        }
                        
                        
                        information=(char*)malloc(strlen(temp)+1);
                        strtok(temp,"=");
                        information=strtok(NULL,"=");
                        
                      //  printf("information=%s </p> ",information);
                        
                        
                        //search in the subject and information seperately
                        
                        
                        //note problem! may be have punctuation after words!
                        //in subject
                        
                        i=0;
                        temp=(char *)malloc(sizeof(char)*200);
                        if(subject!=NULL){
                            temp=strtok(subject," ");
  
                        }
                        
                        if(temp!=NULL){
                            if(strcmp(temp,qstr)==0){
                                i++;
                                num++;
                                printf("<p>find: %s </p>",temp);
                                //printf("<p> find it in subject!</p>");
                                //printf("%s:is in %s",qstr,ftr->d_name);
                            }
                            
                            while((temp=strtok(NULL," "))!=NULL){
                                if(strcmp(qstr,temp)==0){
                                    i++;
                                    num++;
                                    printf("<p>find: %s </p>",temp);
                                  //  printf("<p> find it in subject!</p>");
                                   // printf("%s:is in %s",qstr,ftr->d_name);
                                }
                                
                            }

                        }
                        
                        
                      
                        
                        
                        
                        temp=(char *)malloc(sizeof(char)*200);
                        
                        //check information if NULL may have problem
                        
                        if(information!=NULL){
                             temp=strtok(information," ");
                        
                            if(strcmp(temp,qstr)==0){
                                i++;
                                num++;
                                printf("<p>find: %s </p>",temp);
                              //  printf("<p>find it in information! </p>");
                               // printf("<p>%s:is in %s </p>",qstr,ftr->d_name);
                            }

                        
                            temp=(char*)malloc(100);
                            
                            while((temp=strtok(NULL," "))!=NULL){
                                if(strcmp(qstr,temp)==0){
                                    i++;
                                    num++;
                                    printf("<p>find: %s </p>",temp);
                                   // printf("<p>find it in information! </p>");
                                   // printf("<p>%s:is in %s </p>",qstr,ftr->d_name);
                                }
                                
                                
                            }
                            
                        }
                       
                        
                        
                        
                        
                        if(i>0){
                            printf("<p>");
                            printf("There are  %d : \" %s \" ",i,qstr);
                            printf("</p>");
                            printf("<p>");
                            printf(" in file: %s ",ftr->d_name);
                            printf("</p>");
                            
                        }
    
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                    }
                    
                    
                    
                    
                }
                
                
            }
            
            
            
        }
        
             if(num==0){
            printf("There is no such string:[  %s  ]</p>",qstr);
            
        }else{
            printf("There are totally: %d  such string:[  %s  ] in all the file</p>",num,qstr);
            
        }
        
        
        printf("there are: %d users \n",dircount);
         printf("there are: %d meetings \n",filecount);
        closedir(dir);
        
        
        
        
    }//else end here
    
    
}













//search between two days and two specifc timew;

void specfictime(char *specficinfo){
    DIR * dir;
    DIR * fdir;
    struct dirent * ptr;
    struct dirent * ftr;
    int dircount=0;
    int filecount=0;
    //char pathdir[100]="/Users/wmy/Desktop/project1/step3/step3/temp";
    char pathdir[100]="/Library/WebServer/CGI-Executables/doc";
    char *pathdirtmp;
    
    
    //userinfor variable
    char *username;
    char * startdate;
    char * starttime;
    char * enddate;
    char * endtime;
    char * subject;
    char * information;
    char * meet;
    
    //seperate process
    char *qstring;
    
    
    
    
    
    char *value[6];
    
    int i=0;
    
    //file process
    FILE *fr;
    char *pathname;
    
    
    int j;
    
    
    
    char *temp;
    char *info[6];
    
    //search
    char *start[3];
    char *result2;
    char *end[3];
    char *result3;
    
    char *date1="1";  //defalut   require
    char *date2="30";  //defalut
    
    char* qmonth1="1";//defalut;
    
    char* qyear1="2014";//defalut;
    
    char* qmonth2="1";//defalut;
    
    
    char* qyear2="2014";//defalut;
    
    
    //need to change from string to int or ascii;
    
    int d1;  //query
    int  d2;
    int qy1;
    int qy2;
    int qm1;
    int qm2;
    
    
    
    int  sd;   //in file
    int  ed;
    
    //int  y1;
    int y2;
    
    int m1;
    int m2;
    
    
    //search specfic time
    char *time1="0:00";  //defalut
    char *time2="12:00";  //defalut
    char *hour1;
    char *min1;
    char *hour2;
    char *min2;
    char *apm1="am";  //defalut
    char *apm2="am";  //defalut;
    int ht1=0;    //query defalut;
    int ht2=0;
    int mt1=0;
    int mt2=0;
    
    
    
    
    char *hour;
    char *min;
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
    //query string
    
    
    
    //input dates
    
    char * results;
    char * parts[6];
    char * values[6];
    char * datein1;
    char * datein2;
    char *starts[3];
    char *ends[3];
    //format of time1in: 10:00am
    char *time1in;
    char *time2in;
    
    
    
    int  y1;
    
    
    // printf( "Content-type: text/html\n\n" );
    
    //improcess input;
    
    //qstring=getenv("QUERY_STRING");
    qstring=(char*)malloc(strlen(specficinfo)+1);
    strcpy(qstring,specficinfo);
    
    
    
    //  printf("qstring:: %s",qstring);
    
    
    results=(char*)malloc(sizeof(char)*(strlen(qstring)+1));
    results=strtok(qstring,"&");
    
    //each seperate by & still include =
    for (i=0; results!=NULL; i++)
    {   //malloc is important
        parts[i]=(char *)malloc(sizeof(char)*(strlen(results)+1));
        
        //  printf("result is: %s \n",results);
        strcpy(parts[i],results);
        results = strtok( NULL, "&" );
        
    }
    
    
    
    
    
    
    
    for(i=0; i<4; i++ ){
        values[i]=(char *)malloc(sizeof(char)*(strlen(parts[i])+1));
        strtok(parts[i],"=");
        values[i]=strtok(NULL,"=");
        // printf("value : %s \n", values[i]);
        
    }
    
    if(values[0]==NULL||values[1]==NULL){
        printf("<a href=\"MainProject1.exe\">Go back,please input two dates!</a>");
    }else{
        
        //datein is june,1,2014
        datein1=values[0];
        datein2=values[1];
        time1in=values[2];
        time2in=values[3];
        
        //  printf("datein1 %s",datein1);
        //  printf("datein2 %s",datein2);
        
        
        //already decode
        // if not null change defalut;
        //     urldecode(datein1,strlen(datein1)+1);
        //     urldecode(datein2,strlen(datein2)+1);
        //     urldecode(time1in,strlen(time1in)+1);
        //     urldecode(time2in,strlen(time2in)+1);
        
        
        // printf("<p>date1 %s",datein1);
        // printf("date2 %s",datein2);
        // printf("time1in %s",time1in);
        // printf("time2in%s </p>",time2in);
        
        
        //between two days and specfic time
        
        //starttime;
        i=0;
        temptime=(char *)malloc(sizeof(char)*(strlen(time1in)+1));
        strcpy(temptime,time1in);
        hour=strtok(temptime,":");
        // printf("hour: %s \n", hour);
        rest=strtok(NULL,":");
        // printf("rest: %s \n",rest);
        min=(char*)malloc(3);
        apm=(char*)malloc(3);
        if(rest!=NULL && strlen(rest)<=4){
            strncpy(min,rest,2);
            strcat(min,"\0");
            // printf("min: %s \n",min);
            strncpy(apm,(rest+2),2);
            strcat(apm,"\0");
            // printf("apm: %s \n",apm);
        }
        
        if(hour!=NULL&& min!=NULL && apm !=NULL){
            //change defalut;
            time1=(char*)malloc(10);
            strcpy(time1,hour);
            strcat(time1,":");
            strcat(time1,min);
            
            apm1=apm;
            
            //to int
            ht1=chartoint(hour);
            mt1=chartoint(min);
            
        }
        
        
        
        
        
        //endtime;
        i=0;
        temptime=(char *)malloc(sizeof(char)*(strlen(time2in)+1));
        strcpy(temptime,time2in);
        houre=strtok(temptime,":");
        //printf("houre: %s \n", houre);
        rest=strtok(NULL,":");
        // printf("reste: %s \n",rest);
        mine=(char*)malloc(3);
        apme=(char*)malloc(3);
        if(rest!=NULL && strlen(rest)<=4){
            strncpy(mine,rest,2);
            strcat(mine,"\0");
            //printf("mine: %s \n",min);
            strncpy(apme,(rest+2),2);
            strcat(apme,"\0");
            //printf("apme: %s \n",apme);
        }
        
        if(houre!=NULL&& mine!=NULL && apme !=NULL){
            //change defalut;
            time2=(char*)malloc(10);
            strcpy(time2,houre);
            strcat(time2,":");
            strcat(time2,mine);
            
            apm2=apme;
            
            //to int
            ht2=chartoint(hour);
            mt2=chartoint(min);
        }
        
        
        
        
        
        
        
        
        //inputs process:between two dates:
        //startdate infor
        i=0;
        result2=(char *)malloc(sizeof(char)*(strlen(datein1)+1));
        strcpy(result2,datein1);
        starts[0]=strtok(result2,",");
        for(i=1; i<3; i++){
            starts[i]=strtok(NULL,",");
            
            if(starts[i]==NULL){
                break;
            }
        }
        if(starts[1]!=NULL){
            //  printf("start day: %s \n",starts[1]);
        }
        
        
        
        //enddate infor
        i=0;
        result3=(char *)malloc(sizeof(char)*(strlen(datein2)+1));
        strcpy(result3,datein2);
        ends[0]=strtok(result3,",");
        for(i=1; i<3; i++){
            ends[i]=strtok(NULL,",");
            
            if(ends[i]==NULL){
                break;
            }
        }
        if(ends[1]!=NULL){
            // printf("end day: %s \n",ends[1]);
        }
        
        
        if(starts[1]!=NULL && ends[1]!=NULL){
            //date1 that is day1
            date1=starts[1];
            date2=ends[1];
            //printf("int date1:%d </p>",chartoint(date1));
            // printf("int date2:%d </p>",chartoint(date2));
            
        }
        
        
        
        
        //modify get month and year;//
        if(starts[0]!=NULL && ends[0]!=NULL){
            //date1 that is day1
            qmonth1=starts[0];
            qmonth2=ends[0];
            
            qm1=getmonth(qmonth1);
            qm2=getmonth(qmonth2);
            // printf("qm1: %d  </p>",qm1);
            // printf("qm2: %d  </p>",qm2);
            
            
        }
        
        
        //year
        if(starts[2]!=NULL && ends[2]!=NULL){
            //date1 that is day1
            qyear1=starts[2];
            qyear2=ends[2];
            // printf("int qyear1:%d </p>",chartoint(qyear1));
            //  printf("int qyear2:%d </p>",chartoint(qyear2));
            
        }
        
        
        
        
        
        
        //puthere
        //option
        //   int option;
        // option=1; view all;
        //option=2; search between 2days;
        //option=3; search between 2 days and a specific time;
        //option=4; search for string in file
        
        // insert code here...
        
        
        //at beggin; deal with the input query;
        temptime=(char *)malloc(sizeof(char)*(strlen(time1)+1));
        strcpy(temptime,time1);
        hour1=strtok(temptime,":");
        min1=strtok(NULL,":");
        ht1=chartoint(hour1);
        mt1=chartoint(min1);
        if(strcmp(apm1,"pm")==0){
            ht1=ht1+12;   //change to 24:00
        }
        // printf("hour %d, min %d \n", ht1, mt1);
        
        free(temptime);
        
        
        temptime=(char *)malloc(sizeof(char)*(strlen(time2)+1));
        strcpy(temptime,time2);
        hour2=strtok(temptime,":");
        min2=strtok(NULL,":");
        ht2=chartoint(hour2);
        mt2=chartoint(min2);
        if(strcmp(apm2,"pm")==0){
            ht2=ht2+12;   //change to 24:00
        }
        //  printf("hour %d, min %d \n", ht2, mt2);
        
        free(temptime);
        
        
        
        
        
        
        MeetForm();
        
        
        dir = opendir(pathdir);
        while((ptr = readdir(dir)) != NULL)
        {
            if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..")==0 || strcmp(ptr->d_name, ".DS_Store")==0)
                continue;    /* skip self and parent */
            
            //count dir user
            
            //problem here should new localtion other wise append after /
            
            pathdirtmp=(char *)malloc(sizeof(char)*strlen(pathdir)+(strlen(ptr->d_name)+1));
            strcat(pathdirtmp,pathdir);
            strcat(pathdirtmp,"/");
            strcat(pathdirtmp,ptr->d_name);
            
            username=ptr->d_name;
            //dir
            //  printf("user name : %s\n",username );
            dircount++;
            
            //note: should print pathdirtmp;
            
            
            fdir=opendir(pathdirtmp);
            
            if(fdir!=NULL){
                //open the inner dirct=user;
                
                //get user name form the dir
                
                
                
                
                while((ftr=readdir(fdir))!=NULL)
                {
                    
                    if(strcmp(ftr->d_name, ".") == 0 || strcmp(ftr->d_name, "..")==0 || strcmp(ftr->d_name, ".DS_Store")==0)
                        continue;    /* skip self and parent */
                    filecount++;
                    
                    //file
                    //  printf("Meeting info : %s \n", ftr->d_name);
                    meet=(char *)malloc(sizeof(char)*(strlen(ftr->d_name)+1));
                    strcpy(meet,ftr->d_name);
                    
                    //seperate;
                    //first sperate "."
                    meet=strtok(meet,".");
                    //      printf("meet: %s \n",meet);
                    
                    //second seperate "-" using for loop
                    //don't need first username info
                    
                    meet=strtok(meet,"-");
                    //      printf("value: %s \n",meet);
                    
                    
                    for(i=0;i<6;i++){
                        
                        meet=strtok(NULL,"-");
                        // printf("meet: %s \n",meet);
                        
                        if(meet==NULL){
                            break;
                        }
                        value[i]=(char*)malloc(sizeof(char)*(strlen(meet)+1));
                        strcpy(value[i],meet);
                        //    printf("v: %s \n",value[i]);
                    }
                    
                    //get info from the file name
                    startdate=value[0];
                    starttime=value[1];
                    //now they are empty
                    enddate=value[2];
                    endtime=value[3];
                    
                    
                    //get subject and information by reading file
                    //create a path=dir/filename;
                    pathname=(char*)malloc(sizeof(char)*(strlen(pathdirtmp)+strlen(ftr->d_name)+1));
                    strcat(pathname,"/Library/WebServer/CGI-Executables/doc");
                    strcat(pathname,"/");
                    strcat(pathname,username);
                    strcat(pathname,"/");
                    strcat(pathname,ftr->d_name);
                    
                    //  printf("path: %s \n",pathname);
                    
                    
                    if((fr=fopen(pathname,"r"))==NULL){
                        perror("can't read \n");
                        exit(1);
                    }else{
                        // printf("read! \n");
                        
                        //read each line;
                        //note information may very long just one line may not work
                        
                        i=0;
                        temp=(char *)malloc(sizeof(char)*(100));
                        while(fgets(temp,100,fr)!=NULL && i<3)
                        {
                            info[i]=(char*)malloc(sizeof(char)*(strlen(temp)+1));
                            strcpy(info[i],temp);
                            i++;
                        }
                        
                        //subject is info[0];
                        subject=(char *)malloc(sizeof(char)*(strlen(info[0])+1));
                        strtok(info[0],"=");
                        subject=strtok(NULL,"=");
                        
                        //information=info[1];
                        //information may have several lines; //realloc(buffer,sizeof(char)*i)
                        
                        temp=(char *)malloc(sizeof(char)*200);
                        
                        j=1;
                        while(info[j]!=NULL&& strlen(temp)<200){
                            strcat(temp,info[j]);
                            j++;
                        }
                        
                        strtok(temp,"=");
                        information=strtok(NULL,"=");
                        
                        
                        
                        
                        
                        
                        
                        //between two dates:
                        //startdate infor
                        i=0;
                        result2=(char *)malloc(sizeof(char)*(strlen(startdate)+1));
                        strcpy(result2,startdate);
                        start[0]=strtok(result2,",");
                        for(i=1; i<3; i++){
                            start[i]=strtok(NULL,",");
                            
                            if(start[i]==NULL){
                                break;
                            }
                        }
                        if(start[1]!=NULL){
                            // printf("start day: %s \n",start[1]);
                        }
                        
                        
                        
                        //enddate infor
                        i=0;
                        result3=(char *)malloc(sizeof(char)*(strlen(enddate)+1));
                        strcpy(result3,enddate);
                        end[0]=strtok(result3,",");
                        for(i=1; i<3; i++){
                            end[i]=strtok(NULL,",");
                            // printf("end day: %s \n",end[i]);
                            if(end[i]==NULL){
                                break;
                            }
                        }
                        if(end[1]!=NULL){
                            //printf("end day: %s \n",end[1]);
                        }
                        
                        
                        
                        
                        //between two days and specfic time
                        
                        //starttime;
                        i=0;
                        temptime=(char *)malloc(sizeof(char)*(strlen(starttime)+1));
                        strcpy(temptime,starttime);
                        hour=strtok(temptime,":");
                        // printf("hour: %s \n", hour);
                        rest=strtok(NULL,":");
                        // printf("rest: %s \n",rest);
                        min=(char*)malloc(3);
                        apm=(char*)malloc(3);
                        if(rest!=NULL && strlen(rest)<=4){
                            strncpy(min,rest,2);
                            strcat(min,"\0");
                            // printf("min: %s \n",min);
                            strncpy(apm,(rest+2),2);
                            strcat(apm,"\0");
                            // printf("apm: %s \n",apm);
                        }
                        
                        
                        
                        //endtime;
                        i=0;
                        temptime=(char *)malloc(sizeof(char)*(strlen(endtime)+1));
                        strcpy(temptime,endtime);
                        houre=strtok(temptime,":");
                        //  printf("houre: %s \n", houre);
                        rest=strtok(NULL,":");
                        //  printf("reste: %s \n",rest);
                        mine=(char*)malloc(3);
                        apme=(char*)malloc(3);
                        if(rest!=NULL && strlen(rest)<=4){
                            strncpy(mine,rest,2);
                            strcat(mine,"\0");
                            //  printf("mine: %s \n",min);
                            strncpy(apme,(rest+2),2);
                            strcat(apme,"\0");
                            // printf("apme: %s \n",apme);
                        }
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        if(start[1]!=NULL && end[1]!=NULL)
                        {
                            //start[0]is a char * pointer, it is address of a string
                            
                            
                            
                            d1=chartoint(date1);  //query data
                            d2=chartoint(date2);
                            sd=chartoint(start[1]); //get from every file;
                            ed=chartoint(end[1]);
                            
                            qy1=chartoint(qyear1);
                            qy2=chartoint(qyear2);
                            
                            y1=chartoint(start[2]);
                            y2=chartoint(end[2]);
                            
                            
                            m1=getmonth(start[0]);
                            m2=getmonth(end[0]);
                            qm1=getmonth(qmonth1);
                            qm2=getmonth(qmonth2);
                            
                            
                            /*   printf("sd: %d, ed: %d </p>",sd ,ed);
                             
                             printf("d1: %d, d2: %d </p>",d1 ,d2);
                             
                             printf("y1: %d, y2: %d </p>",y1 ,y2);
                             
                             printf("qy1: %d, qy2: %d </p>",qy1 ,qy2);
                             
                             printf("m1: %d, m2: %d </p>",m1 ,m2);
                             
                             printf("qm1: %d, qm2: %d </p>",qm1 ,qm2);
                             
                             */
                            
                            
                            
                            //change from am/pm to 24:00
                            
                            
                            
                            h=chartoint(hour);
                            m=chartoint(min);
                            if(strcmp(apm,"pm")==0){
                                h=h+12;
                            }
                            
                            //  printf("h: %d, m: %d apm: %s</p>",h ,m,apm);
                            
                            
                            
                            
                            
                            
                            
                            he=chartoint(houre);
                            me=chartoint(mine);
                            if(strcmp(apme,"pm")==0){
                                he=he+12;
                            }
                            
                            
                            
                            // printf("he: %d, me: %d apme: %s </p>",he ,me,apme);
                            //  printf("ht1: %d, mt1: %d apme1: %s </p>",ht1 ,mt1,apm1);
                            //  printf("ht2: %d, mt2: %d apme2: %s </p>",ht2 ,mt2,apm2);
                            
                            
                            if(y1>=qy1 && y2<=qy2 && m1>=qm1 && m2<=qm2&& sd>=d1 && ed<=d2 ){
                                if( ((h==ht1 && m>=mt1)||h>ht1) && (he<ht2||(he==ht2 && me<=mt2))  ){
                                    //find
                                    //  printf("find specfic ");
                                    
                                    
                                    printf("<tr>");
                                    printf("<th>");
                                    printf("%s",username);
                                    printf("</th>");
                                    
                                    printf("<th>");
                                    printf("%s",startdate);
                                    printf("</th>");
                                    
                                    printf("<th>");
                                    printf("%s",starttime);
                                    printf("</th>");
                                    
                                    
                                    printf("<th>");
                                    printf("%s",enddate);
                                    printf("</th>");
                                    
                                    printf("<th>");
                                    printf("%s",endtime);
                                    printf("</th>");
                                    
                                    printf("<th>");
                                    printf("%s",subject);
                                    printf("</th>");
                                    
                                    
                                    printf("<th>");
                                    printf("%s",information);
                                    printf("</th>");
                                    
                                    printf("</tr>");
                                }
                                
                                
                            }
                        }
                        
                        
                        
                        
                        
                        
                        
                    }
                    
                    
                    
                    
                }
                
                
            }
            
            
            
        }
        
        printf("<p>");
        printf("there are: %d users \n",dircount);
        printf("there are: %d meetings \n",filecount);
        printf("</p>");
        
        closedir(dir);
        
        //
        
        
        
        
        
        
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
}












void twodays(char *twodayinfo)
{
    
    
    //system infor variable
    DIR * dir;
    DIR * fdir;
    struct dirent * ptr;
    struct dirent * ftr;
    int dircount=0;
    int filecount=0;
    //char pathdir[100]="/Users/wmy/Desktop/project1/step3/step3/temp";
    char pathdir[100]="/Library/WebServer/CGI-Executables/doc";
    char *pathdirtmp;
    
    
    //userinfor variable
    char *username;
    char * startdate;
    char * starttime;
    char * enddate;
    char * endtime;
    char * subject;
    char * information;
    char * meet;
    
    //seperate process
    char *qstring;
    
    
    char *value[6];
    
    int i=0;
    
    //file process
    FILE *fr;
    char *pathname;
    
    
    int j;
    
    
    
    char *temp;
    char *info[6];
    
    //search
    char *start[3];
    char *result2;
    char *end[3];
    char *result3;
    
    char *date1="1";  //defalut   require
    char *date2="30";  //defalut
    
    char* qmonth1="1";//defalut;
    
    
    char* qyear1="2014";//defalut;
    
    char* qmonth2="1";//defalut;
    
    
    char* qyear2="2014";//defalut;
    
    
    
    
    
    
    //need to change from string to int or ascii;
    int d1;  //query
    int  d2;
    int qy1;
    int qy2;
    int qm1;
    int qm2;
    
    
    
    int  sd;   //in file
    int  ed;
    
    //int y1;
    int y2;
    
    int m1;
    int m2;
    
    
    //search specfic time
    char *time1="0:00";  //defalut
    char *time2="12:00";  //defalut
    char *hour1;
    char *min1;
    char *hour2;
    char *min2;
    char *apm1="am";  //defalut
    char *apm2="pm";  //defalut;
    int ht1;
    int ht2;
    int mt1;
    int mt2;
    
    
    
    char *temptime;
    
    //query string
    
    
    
    //input dates
    
    char * results;
    char * parts[2];
    char * values[2];
    char * datein1;
    char * datein2;
    char *starts[3];
    char *ends[3];
    
    
    
    
    
    
    
    int y1;
    
    
    
    
    //  printf( "Content-type: text/html\n\n" );
    
    //improcess input;
    
    // qstring=getenv("QUERY_STRING");
    qstring=(char*)malloc(strlen(twodayinfo)+1);
    
    strcpy(qstring,twodayinfo);
    
    
    
    //  printf("qstring:: %s",qstring);
    
    
    results=(char*)malloc(sizeof(char)*(strlen(qstring)+1));
    results=strtok(qstring,"&");
    
    //each seperate by & still include =
    for (i=0; results!=NULL; i++)
    {   //malloc is important
        parts[i]=(char *)malloc(sizeof(char)*(strlen(results)+1));
        
        //  printf("result is: %s \n",results);
        strcpy(parts[i],results);
        results = strtok( NULL, "&" );
        
    }
    
    
    
    
    
    
    
    for(i=0; i<2; i++ ){
        values[i]=(char *)malloc(sizeof(char)*(strlen(parts[i])+1));
        strtok(parts[i],"=");
        values[i]=strtok(NULL,"=");
        // printf("value : %s \n", values[i]);
        
    }
    
    if(values[0]==NULL||values[1]==NULL){
        printf("<a href=\"MainProject1.exe\">Go back,please input two dates!</a>");
    }else{
        
        //datein is june,1,2014
        datein1=values[0];
        datein2=values[1];
        
        //   printf("datein1 %s",datein1);
        //   printf("datein2 %s </p>",datein2);
        
        
        //already decode
        
        // if not null change defalut;
        //    urldecode(datein1,strlen(datein1)+1);
        //   urldecode(datein2,strlen(datein2)+1);
        //   printf("date1 %s",datein1);
        //     printf("date2 %s </p>",datein2);
        
        
        
        
        
        
        
        //in puts process:between two dates:
        //startdate infor
        i=0;
        result2=(char *)malloc(sizeof(char)*(strlen(datein1)+1));
        strcpy(result2,datein1);
        starts[0]=strtok(result2,",");
        for(i=1; i<3; i++){
            starts[i]=strtok(NULL,",");
            
            if(starts[i]==NULL){
                break;
            }
        }
        if(starts[1]!=NULL){
            // printf("start day: %s </p>",starts[1]);
        }
        
        
        
        //enddate infor
        i=0;
        result3=(char *)malloc(sizeof(char)*(strlen(datein2)+1));
        strcpy(result3,datein2);
        ends[0]=strtok(result3,",");
        for(i=1; i<3; i++){
            ends[i]=strtok(NULL,",");
            
            if(ends[i]==NULL){
                break;
            }
        }
        if(ends[1]!=NULL){
            //  printf("end day: %s </p>",ends[1]);
        }
        
        
        
        if(starts[1]!=NULL && ends[1]!=NULL){
            //date1 that is day1
            date1=starts[1];
            date2=ends[1];
            // printf("int date1:%d </p>",chartoint(date1));
            // printf("int date2:%d </p>",chartoint(date2));
            
        }
        
        
        
        
        //modify get month and year;//
        if(starts[0]!=NULL && ends[0]!=NULL){
            //date1 that is day1
            qmonth1=starts[0];
            qmonth2=ends[0];
            
            qm1=getmonth(qmonth1);
            qm2=getmonth(qmonth2);
            //  printf("qm1: %d  </p>",qm1);
            //  printf("qm2: %d  </p>",qm2);
            
            
        }
        
        
        //year
        if(starts[2]!=NULL && ends[2]!=NULL){
            //date1 that is day1
            qyear1=starts[2];
            qyear2=ends[2];
            //  printf("int qyear1:%d </p>",chartoint(qyear1));
            //  printf("int qyear2:%d </p>",chartoint(qyear2));
            
        }
        
        
        
        
        
        
        
        //no need here
        
        
        
        //puthere
        //option
        
        
        // option=1; view all;
        //option=2; search between 2days;
        //option=3; search between 2 days and a specific time;
        //option=4; search for string in file
        
        // insert code here...
        
        
        //at beggin; deal with the input query;
        temptime=(char *)malloc(sizeof(char)*(strlen(time1)+1));
        strcpy(temptime,time1);
        hour1=strtok(temptime,":");
        min1=strtok(NULL,":");
        ht1=chartoint(hour1);
        mt1=chartoint(min1);
        if(strcmp(apm1,"pm")==0){
            ht1=ht1+12;   //change to 24:00
        }
        // printf("hour %d, min %d \n", ht1, mt1);
        
        free(temptime);
        
        
        temptime=(char *)malloc(sizeof(char)*(strlen(time2)+1));
        strcpy(temptime,time2);
        hour2=strtok(temptime,":");
        min2=strtok(NULL,":");
        ht2=chartoint(hour2);
        mt2=chartoint(min2);
        if(strcmp(apm2,"pm")==0){
            ht2=ht2+12;   //change to 24:00
        }
        //printf("hour %d, min %d \n", ht2, mt2);
        
        free(temptime);
        
        
        
        //get option from query string 1,2,3,4
        
        
        
        
        MeetForm();
        dir = opendir(pathdir);
        while((ptr = readdir(dir)) != NULL)
        {
            if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..")==0 || strcmp(ptr->d_name, ".DS_Store")==0)
                continue;    /* skip self and parent */
            
            //count dir user
            
            //problem here should new localtion other wise append after /
            
            pathdirtmp=(char *)malloc(sizeof(char)*strlen(pathdir)+(strlen(ptr->d_name)+1));
            strcat(pathdirtmp,pathdir);
            strcat(pathdirtmp,"/");
            strcat(pathdirtmp,ptr->d_name);
            
            username=ptr->d_name;
            //dir
            //printf("user name : %s </p>",username );
            dircount++;
            
            //note: should print pathdirtmp;
            
            
            fdir=opendir(pathdirtmp);
            
            if(fdir!=NULL){
                //open the inner dirct=user;
                
                //get user name form the dir
                
                
                
                
                while((ftr=readdir(fdir))!=NULL)
                {
                    
                    if(strcmp(ftr->d_name, ".") == 0 || strcmp(ftr->d_name, "..")==0 || strcmp(ftr->d_name, ".DS_Store")==0)
                        continue;    /* skip self and parent */
                    filecount++;
                    
                    //file
                    //  printf("Meeting info : %s </p>", ftr->d_name);
                    meet=(char *)malloc(sizeof(char)*(strlen(ftr->d_name)+1));
                    strcpy(meet,ftr->d_name);
                    
                    //seperate;
                    //first sperate "."
                    meet=strtok(meet,".");
                    //      printf("meet: %s \n",meet);
                    
                    //second seperate "-" using for loop
                    //don't need first username info
                    
                    meet=strtok(meet,"-");
                    //      printf("value: %s \n",meet);
                    
                    
                    for(i=0;i<6;i++){
                        
                        meet=strtok(NULL,"-");
                        // printf("meet: %s \n",meet);
                        
                        if(meet==NULL){
                            break;
                        }
                        value[i]=(char*)malloc(sizeof(char)*(strlen(meet)+1));
                        strcpy(value[i],meet);
                        //    printf("v: %s \n",value[i]);
                    }
                    
                    //get info from the file name
                    startdate=value[0];    //June,4,20114
                    starttime=value[1];    //10:00am;
                    //now they are empty
                    enddate=value[2];
                    endtime=value[3];
                    
                    
                    
                    
                    //no need to reading file just for search between 2days;
                    
                    
                    //get subject and information by reading file
                    //create a path=dir/filename;
                    pathname=(char*)malloc(sizeof(char)*(strlen(pathdirtmp)+strlen(ftr->d_name)+1));
                    strcat(pathname,"/Library/WebServer/CGI-Executables/doc");
                    strcat(pathname,"/");
                    strcat(pathname,username);
                    strcat(pathname,"/");
                    strcat(pathname,ftr->d_name);
                    
                    //  printf("path: %s \n",pathname);
                    
                    
                    if((fr=fopen(pathname,"r"))==NULL){
                        perror("can't read \n");
                        exit(1);
                    }else{
                        // printf("read! \n");
                        
                        //read each line;
                        //note information may very long just one line may not work
                        
                        i=0;
                        temp=(char *)malloc(sizeof(char)*(100));
                        while(fgets(temp,100,fr)!=NULL && i<3)
                        {
                            info[i]=(char*)malloc(sizeof(char)*(strlen(temp)+1));
                            strcpy(info[i],temp);
                            i++;
                        }
                        
                        //subject is info[0];
                        subject=(char *)malloc(sizeof(char)*(strlen(info[0])+1));
                        strtok(info[0],"=");
                        subject=strtok(NULL,"=");
                        
                        //information=info[1];
                        //information may have several lines; //realloc(buffer,sizeof(char)*i)
                        
                        temp=(char *)malloc(sizeof(char)*200);
                        
                        j=1;
                        while(info[j]!=NULL&& strlen(temp)<200){
                            strcat(temp,info[j]);
                            j++;
                        }
                        
                        strtok(temp,"=");
                        information=strtok(NULL,"=");
                        
                        
                        
                        
                        
                        
                        
                        //between two dates:
                        //startdate infor
                        i=0;
                        result2=(char *)malloc(sizeof(char)*(strlen(startdate)+1));
                        strcpy(result2,startdate);
                        start[0]=strtok(result2,",");
                        for(i=1; i<3; i++){
                            start[i]=strtok(NULL,",");
                            
                            if(start[i]==NULL){
                                break;
                            }
                        }
                        if(start[1]!=NULL){
                            //printf("start day: %s \n",start[1]);
                        }
                        
                        
                        
                        //enddate infor
                        i=0;
                        result3=(char *)malloc(sizeof(char)*(strlen(enddate)+1));
                        strcpy(result3,enddate);
                        end[0]=strtok(result3,",");
                        for(i=1; i<3; i++){
                            end[i]=strtok(NULL,",");
                            // printf("end day: %s \n",end[i]);
                            if(end[i]==NULL){
                                break;
                            }
                        }
                        if(end[1]!=NULL){
                            //  printf("end day: %s \n",end[1]);
                        }
                        
                        
                        
                        
                        
                        
                        //between two days; //search
                        //compare month, day
                        
                        if(start[0]!=NULL && end[0]!=NULL&&start[1]!=NULL && end[1]!=NULL&& start[2]!=NULL && end[2]!=NULL)
                        {
                            //start[0]is a char * pointer, it is address of a string
                            
                            d1=chartoint(date1);  //query data
                            d2=chartoint(date2);
                            sd=chartoint(start[1]); //get from every file;
                            ed=chartoint(end[1]);
                            
                            qy1=chartoint(qyear1);
                            qy2=chartoint(qyear2);
                            
                            y1=chartoint(start[2]);
                            y2=chartoint(end[2]);
                            
                            
                            m1=getmonth(start[0]);
                            m2=getmonth(end[0]);
                            qm1=getmonth(qmonth1);
                            qm2=getmonth(qmonth2);
                            
                            /*
                             printf("sd: %d, ed: %d </p>",sd ,ed);
                             
                             printf("d1: %d, d2: %d </p>",d1 ,d2);
                             
                             printf("y1: %d, y2: %d </p>",y1 ,y2);
                             
                             printf("qy1: %d, qy2: %d </p>",qy1 ,qy2);
                             
                             printf("m1: %d, m2: %d </p>",m1 ,m2);
                             
                             printf("qm1: %d, qm2: %d </p>",qm1 ,qm2);  */
                            
                            //same year and same month,between two days
                            if(y1>=qy1 && y2<=qy2 && m1>=qm1 && m2<=qm2&& sd>=d1 && ed<=d2 ){
                                
                                
                                printf("<tr>");
                                printf("<th>");
                                printf("%s",username);
                                printf("</th>");
                                
                                printf("<th>");
                                printf("%s",startdate);
                                printf("</th>");
                                
                                printf("<th>");
                                printf("%s",starttime);
                                printf("</th>");
                                
                                
                                printf("<th>");
                                printf("%s",enddate);
                                printf("</th>");
                                
                                printf("<th>");
                                printf("%s",endtime);
                                printf("</th>");
                                
                                printf("<th>");
                                printf("%s",subject);
                                printf("</th>");
                                
                                
                                printf("<th>");
                                printf("%s",information);
                                printf("</th>");
                                
                                printf("</tr>");
                            }
                        }
                        
                        
                        
                        
                        
                        
                        
                    }
                    
                    
                    
                    
                }
                
                
            }
            
            
            
        }
        
        printf("<p>");
        printf("there are: %d users \n",dircount);
        printf("there are: %d meetings \n",filecount);
        printf("</p>");
        
        closedir(dir);
        
        
        
        
        
        
        
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
}





/**
 * @param str need to be decode
 * @param len the len of string
 * @return int the len after decoding
 */
int urldecode(char *str, int len)
{  //str should be char [] instaed of char * because can't use char *p="abc" point to const ,can't change value;
    char *dest = str;
    char *data = str;
    
    int value;
    int c;
    
    while (len--) {
        if (*data == '+') {
            
            *dest=' ';
            
        }
        else if (*data == '%' && len >= 2 && isxdigit((int) *(data + 1))
                 && isxdigit((int) *(data + 2)))
        {
            
            c = ((unsigned char *)(data+1))[0];
            if (isupper(c))
                c = tolower(c);
            value = (c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10) * 16;
            c = ((unsigned char *)(data+1))[1];
            if (isupper(c))
                c = tolower(c);
            value += c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;
            
            *dest = (char)value ;
            data += 2;
            len -= 2;
        } else {
            *dest=*data;
        }
        data++;
        dest++;
    }
    *dest = '\0';
    
    return dest - str;
    
}




void viewmeet(char *uname)
{
    //system infor variable
    DIR * dir;
    DIR * fdir;
    struct dirent * ptr;
    struct dirent * ftr;
    int dircount=0;
    int filecount=0;
    //char pathdir[100]="/Users/wmy/Desktop/project1/step3/step3/temp";
    char pathdir[100]="/Library/WebServer/CGI-Executables/doc";
    char *pathdirtmp;
    
    
    //userinfor variable
    char *username;
    char * startdate;
    char * starttime;
    char * enddate;
    char * endtime;
    char * subject;
    char * information;
    char * meet;
    
    //seperate process
    
    char * thisuser="admin";//defalut
    char *qstring;
    char *result;
    
    
    
    char *value[6];
    
    int i=0;
    
    //file process
    FILE *fr;
    char *pathname;
    
    
    char *temp;
    char *info[6];
    
    
    
    thisuser=(char*)malloc(sizeof(char)*(strlen(uname)+1));
    strcpy(thisuser,uname);
    printf("<p> This user is:  %s</p>", thisuser);
    
    
    
    MeetForm();
    
    dir = opendir(pathdir);
    
    while((ptr = readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..")==0 || strcmp(ptr->d_name, ".DS_Store")==0)
            continue;    /* skip self and parent */
        
        //count dir user
        
        //problem here should new localtion other wise append after /
        
        pathdirtmp=(char *)malloc(sizeof(char)*strlen(pathdir)+(strlen(ptr->d_name)+1));
        strcat(pathdirtmp,pathdir);
        strcat(pathdirtmp,"/");
        strcat(pathdirtmp,ptr->d_name);
        
        //strcat(pathdir,"/");
        // strcat(pathdir,ptr->d_name);
        
        
        //    printf("pathdir: %s \n",pathdir);
        //note: should print pathdirtmp;
        //fdir=opendir(pathdir);
        
        fdir=opendir(pathdirtmp);
        
        if(fdir!=NULL){
            //open the inner dirct=user;
            
            //get user name form the dir
            username=ptr->d_name;
            
            //dir
            //  printf("user name : %s\n",username );
            dircount++;
            
            while((ftr=readdir(fdir))!=NULL)
            {
                
                if(strcmp(ftr->d_name, ".") == 0 || strcmp(ftr->d_name, "..")==0 || strcmp(ftr->d_name, ".DS_Store")==0)
                    continue;    /* skip self and parent */
                filecount++;
                
                //file
                //    printf("Meeting info : %s \n", ftr->d_name);
                meet=(char *)malloc(sizeof(char)*(strlen(ftr->d_name)+1));
                strcpy(meet,ftr->d_name);
                
                //seperate;
                //first sperate "."
                meet=strtok(meet,".");
                //      printf("meet: %s \n",meet);
                
                //second seperate "-" using for loop
                //don't need first username info
                
                meet=strtok(meet,"-");
                //      printf("value: %s \n",meet);
                
                
                for(i=0;i<6;i++){
                    
                    meet=strtok(NULL,"-");
                    // printf("meet: %s \n",meet);
                    
                    if(meet==NULL){
                        break;
                    }
                    value[i]=(char*)malloc(sizeof(char)*(strlen(meet)+1));
                    strcpy(value[i],meet);
                    //    printf("v: %s \n",value[i]);
                }
                
                //get info from the file name
                startdate=value[0];
                starttime=value[1];
                //now they are empty
                enddate=value[2];
                endtime=value[3];
                
                
                //get subject and information by reading file
                //create a path=dir/filename;
                pathname=(char*)malloc(sizeof(char)*(strlen(pathdirtmp)+strlen(ftr->d_name)+1));
                strcat(pathname,"/Library/WebServer/CGI-Executables/doc");
                strcat(pathname,"/");
                strcat(pathname,username);
                strcat(pathname,"/");
                strcat(pathname,ftr->d_name);
                
                //  printf("path: %s \n",pathname);
                
                
                if((fr=fopen(pathname,"r"))==NULL){
                    perror("can't read \n");
                    exit(1);
                }else{
                    // printf("read! \n");
                    
                    //read each line;
                    i=0;
                    temp=(char *)malloc(sizeof(char)*(100));
                    while(fgets(temp,100,fr)!=NULL)
                    {
                        info[i]=(char*)malloc(sizeof(char)*(strlen(temp)+1));
                        strcpy(info[i],temp);
                        //just get subject=123 after "="
                        strtok(info[i],"=");
                        info[i]=strtok(NULL,"=");
                        // printf("info: %s \n",info[i]);
                        i++;
                    }
                    
                    //subject is info[0];
                    subject=info[0];
                    information=info[1];
                    
                    
                    //table form output meeting information
                    
                    if(strcmp(username,thisuser)==0){
                        
                        printf("<tr>");
                        printf("<th>");
                        printf("%s",username);
                        printf("</th>");
                        
                        printf("<th>");
                        printf("%s",startdate);
                        printf("</th>");
                        
                        printf("<th>");
                        printf("%s",starttime);
                        printf("</th>");
                        
                        
                        printf("<th>");
                        printf("%s",enddate);
                        printf("</th>");
                        
                        printf("<th>");
                        printf("%s",endtime);
                        printf("</th>");
                        
                        printf("<th>");
                        printf("%s",subject);
                        printf("</th>");
                        
                        
                        printf("<th>");
                        printf("%s",information);
                        printf("</th>");
                        
                        printf("</tr>");
                        
                        
                    }
                    
                    
                }
                
                
                
                
            }
            
            
        }
        
        
        
    }
    
    // printf("<p>there are: %d users </p>",dircount);
    // printf("<p>there are: %d meetings </p>",filecount);
    closedir(dir);
    
    
}


void savemeet(char *info){
    int status;
    FILE *fp;
    
    char * startdate;
    char * starttime;
    char * enddate;
    char * endtime;
    char * subject;
    char * information;
    
    //username should change according to the login info
    
    // char username[10]="mengyuwu";
    char *username;
    char *pathname;
    char *filename;
    char *filepath;
    
    
    
    char *qstring;
    
    
    
    int e=0; //whether something is empty
    
    char *result;
    char *part1[8];
    char *value[7];
    int i=0;
    /*cgi so lets print out */
    //  printf( "Content-type: text/html\n\n" );
    /* lets check if we are processing inputs */
    printf("<html><head><title>addmeet 1</title></head> <body>");
    
    qstring=(char*)malloc(strlen(info)+1);
    strcpy(qstring,info);
    
    
    
    if(strlen(qstring)!=0)
        //do I need to give some memory to char *qstring?
    {
        // printf("TEST: %s ",qstring);
        // printf("Am processing input");
        // get the key value through separating & and =
        
        
        result=(char*)malloc(sizeof(char)*(strlen(qstring)+1));
        result=strtok(qstring,"&");
        
        //each seperate by & still include =
        for (i=0; result!=NULL; i++)
        {
            part1[i]=(char *)malloc(sizeof(char)*(strlen(result)+1));
            
            // printf("result is: %s \n",result);
            //copy into
            strcpy(part1[i],result);
            // printf("result is: %s \n",(p[i]));
            result = strtok( NULL, "&" );
            
        }
        
        
        
        for(i=0; i<7; i++ ){
            value[i]=(char *)malloc(sizeof(char)*(strlen(part1[i])+1));
            strtok(part1[i],"=");
            value[i]=strtok(NULL,"=");
            
            //  printf("value: %s \n",value[i]);
            
            
        }
        
        
        
        for(i=0; i<7; i++ ){
            //  printf("%d: %s ",i,value[i]);
            if(value[i]==NULL){
                e=1;
            }
        }
        
        
        //check
        if(e){
            
            printf("please enter informations \n");
            printf("<a href=\"MainProject1.exe?todo=newmeet\">Click here for new appointment</a><p>");
            
            
            
        }else{
            //some times it is const can't change value
            
            for(i=0; i<7;i++){
                //decode important;
                //already save
                //     urldecode(value[i],strlen(value[i])+1);
                // printf("value: %s",value[i]);
            }
            
            startdate=(char *)malloc(sizeof(char)*(strlen(value[0])+1));
            startdate=value[0];
            
            starttime=(char *)malloc(sizeof(char)*(strlen(value[1])+1));
            starttime=value[1];
            
            enddate=(char *)malloc(sizeof(char)*(strlen(value[2])+1));
            enddate=value[2];
            
            endtime=(char *)malloc(sizeof(char)*(strlen(value[3])+1));
            endtime=value[3];
            
            subject=(char *)malloc(sizeof(char)*(strlen(value[4])+1));
            subject=value[4];
            
            information=(char *)malloc(sizeof(char)*(strlen(value[5])+1));
            information=value[5];
            
            username=(char *)malloc(sizeof(char)*(strlen(value[6])+1));
            username=value[6];
            
            //decode the url
            
            //  urldecode(user,strlen(user)+1);
            // urldecode(password,strlen(password)+1);
            
            // printf("user: %s  ", user);
            //  printf("password: %s  ", password);
            
            
            
            //save file:
            
            pathname=(char *)malloc(sizeof(char)*100);
            
            
            
            //cgi-executables directory can not make dir,you need to create another directory and you
            //can create directory and file in the doc
            strcat(pathname,"/Library/WebServer/CGI-Executables/doc/");
            strcat(pathname,username);
         //   printf("path: %s",pathname);
            
            filename=(char *)malloc(sizeof(char)*100);
            strcat(filename,username);
            strcat(filename,"-");
            strcat(filename,startdate);
            strcat(filename,"-");
            strcat(filename,starttime);
            strcat(filename,"-");
            strcat(filename,enddate);
            strcat(filename,"-");
            strcat(filename,endtime);
            
            strcat(filename,".app.txt");
           // printf("filename: %s",filename);
            
            
            filepath=(char *)malloc(sizeof(char)*100);
            strcat(filepath,pathname);
            strcat(filepath,"/");
            strcat(filepath,filename);
          printf("filepath: %s",filepath);
            
            
            //makefile
            status = mkdir(pathname,0777);
            (!status) ? (printf("Directory created\n")) :
            (printf("Unable to create directory\n"));
            
            fp=fopen(filepath, "a+");
            if(fp==NULL){
                printf("can't open");
                perror("can't open");
            }else{
                printf("write \n");
                strcat(subject,"\n");
                strcat(information,"\n");
                fputs("subject=",fp);
                fputs(subject,fp);
                fputs("information=",fp);
                fputs(information,fp);
            }
            
            
            
            
            
            
            
            
        }
        
        
        
    }
    else{
        printf("<a href=\"MainProject1.exe\">Click here for new appointment</a><p>");
    }
    
    
    
    
    
    
    free(result);
    free(pathname);
    free(filename);
    free(filepath);
    fclose(fp);
    
    
    
    printf("</html>");
    
}




void caladdmeet(char * info){
    
    printf("caladdmeet in function </p>");
    printf("info: %s </p>",info);
    
    char * startdate="June,1,2014";
    char * starttime="0:00am";
    
    
    
    
    //username should change according to the login info
    
    // char username[10]="mengyuwu";
    char *username="mw2907";//default
    char *qstring;
    
    int e=0; //whether something is empty
    
    char *result;
    char *part1[8];
    char *value[7];
    int i=0;
    
    //get the query string;
    
    qstring=(char*)malloc(strlen(info)+1);
    strcpy(qstring,info);
    
    
    
    
    /*cgi so lets print out */
    // printf( "Content-type: text/html\n\n" );
    
    if(strlen(qstring)!=0){
        
        // printf("TEST: %s ",qstring);
        //  printf("Am processing input");
        // get the key value through separating & and =
        
        
        result=(char*)malloc(sizeof(char)*(strlen(qstring)+1));
        result=strtok(qstring,"&");
        
        //each seperate by & still include =
        for (i=0; result!=NULL; i++)
        {
            part1[i]=(char *)malloc(sizeof(char)*(strlen(result)+1));
            
           // printf("result is: %s  \n",result);
            //copy into
            strcpy(part1[i],result);
            result = strtok( NULL, "&" );
            
        }
        
        
        
        for(i=0; i<3; i++ ){
            value[i]=(char *)malloc(sizeof(char)*(strlen(part1[i])+1));
            strtok(part1[i],"=");
            value[i]=strtok(NULL,"=");
            
          //  printf("value: %s \n",value[i]);
            
            
        }
        
        
        
        for(i=0; i<3; i++ ){
          //  printf("%d: %s ",i,value[i]);
            if(value[i]==NULL){
                e=1;
            }
        }
        
        
        //check
        if(e){
            
            printf("please enter informations \n");
            printf("<a href=\"/cal2.html\">Go back to calendar</a><p>");
            
            
            
        }else{
            //some times it is const can't change value
            
            for(i=0; i<3;i++){
                //decode important;
                
                
                //note: already decode
                //  urldecode(value[i],strlen(value[i])+1);
              //  printf("decode-value: %s",value[i]);
            }
            
            startdate=(char *)malloc(sizeof(char)*(strlen(value[0])+1));
            startdate=value[0];
           // printf("startdate: %s",startdate);
            starttime=(char *)malloc(sizeof(char)*(strlen(value[1])+1));
            starttime=value[1];
            
            
            username=(char *)malloc(sizeof(char)*(strlen(value[2])+1));
            username=value[2];
            
            //cal add event form
            
            
            
            /* lets check if we are processing inputs */
            printf("<html><head><title>addmeet 1</title></head> <body>");
            
            printf("<form action=\"MainProject1.exe\" method=\"GET\"> <p>");
            //the startdate form should be June 15,2014
            printf("start date: <input type=\"text\"name=\"startdate\"value=\%s></p>",value[0]);
            // printf("start date: <input type=\"text\"readonly=\"true\"name=\"startdate\"value=\%s></p>",startdate);
            printf("start time: <input type=\"time\"name=\"starttime\"value=\%s></p>",starttime);
            
            printf("end date: <input type=\"text\"name=\"enddate\"></p>");
            printf("end time: <input type=\"time\"name=\"endtime\"></p>");
            printf("subject: <input type=\"text\"name=\"subject\"></p>");
            printf("information: <input type=\"text\"name=\"information\"></p>");
            printf("username: <input type=\"text\"name=\"username\"value=\%s></p>",username);
            //printf("username: <input type=\"text\"value=\"username variables\"></p>");
            printf("<input type=\"submit\"value=\"add meeting\">");
            printf("</form>");
            
            
            
            
            printf("<a href=\"/cal2.html\">Go back to calendar</a><p>");
            
            
            free(startdate);
            free(starttime);
            free(username);
            free(qstring);
            free(result);
            
        }
        
    }else{
        //note use /cal.html don't ignore /
        printf("<a href=\"/cal2.html\">Go back to calendar</a><p>");
    }
    
    
    
    
    
    
    
    
    
    
    
    printf("</html>");
    
    
    
    
    
}








void addmeet(char * uname){
    
    
    //username should change according to the login info
    
    // char username[10]="mengyuwu";
    char *username;
    //printf( "Content-type: text/html\n\n" );
    
    username=(char *)malloc(sizeof(char)*(strlen(uname)+1));
    strcpy(username,uname);
    
    /* lets check if we are processing inputs */
    printf("<html><head><title>addmeet 1</title></head> <body>");
    
    printf("<form action=\"MainProject1.exe\" method=\"GET\"> <p>");
    //the startdate form should be June 15,2014
    // printf("start date: <input type=\"text\"name=\"startdate\"value=\%s></p>",value[0]);
    // printf("start date: <input type=\"text\"readonly=\"true\"name=\"startdate\"value=\%s></p>",startdate);
    // printf("start time: <input type=\"time\"name=\"starttime\"value=\%s></p>",starttime);
    printf("start date: <input type=\"text\"name=\"startdate\"></p>");
    printf("start time: <input type=\"time\"name=\"starttime\"></p>");
    printf("end date: <input type=\"text\"name=\"enddate\"></p>");
    printf("end time: <input type=\"time\"name=\"endtime\"></p>");
    printf("subject: <input type=\"text\"name=\"subject\"></p>");
    printf("information: <input type=\"text\"name=\"information\"></p>");
    printf("username: <input type=\"text\"readonly=\"true\"name=\"username\"value=\%s></p>",username);
    //printf("username: <input type=\"text\"value=\"username variables\"></p>");
    printf("<input type=\"submit\"value=\"add meeting\">");
    printf("</form>");
    
    
    
    
    printf("<a href=\"MainProject1.exe?todo=newmeet=\%s\">Click here for new appointment</a><p>",username);
    
    free(username);
    
    
    printf("</html>");
    
}







void showFirstForm(){
    printf("<form action=\"MainProject1.exe\" method=\"GET\"> <p>");
    printf("Please enter username: <input type=\"text\"name=\"string\"></p>");
    printf("Please enter password: <input type=\"password\"name=\"passwd\"></p>");
    printf("<input type=\"submit\"value=\"login\">");
    printf("</form>");
    
    printf("<form action=\"CreateAccount.exe\" method=\"GET\"> <p>");
    printf("<input type=\"submit\"value=\"Click here to create a new account\">");
    printf("</form>");
    printf("<p>Mengyu WU, uni:mw2907 </p>");
    printf("<a href=\"https://courseworks.columbia.edu/welcome/\"  target=\"_blank\">Go to courseworks</a>");
}


//don't use it erro!
void meetingForm(char * uname){
    char *username;
    username=(char*)malloc(50);
    strcpy(username,uname);
    printf("<p><b>Options</b> </p>");
    printf("<a href=\"addmeet.exe?user=\%s\">add meeting</a><p>",username);
    printf("<a href=\"viewmeet.exe?user=\%s\">view meeting</a><p>",username);
    printf("<a href=\"MainProject1.exe?todo=systeminfo\">Click here for for system informations</a></p>");
}




//do not use this
void addMeetForm(){
    //note:add href at savemeet.exe to go back
    printf("<form action=\"savemeet.exe\" method=\"GET\"> <p>");
    printf("start date: <input type=\"text\"name=\"startdate\"></p>");
    printf("start time: <input type=\"text\"name=\"starttime\"></p>");
    printf("end date: <input type=\"text\"name=\"enddate\"></p>");
    printf("end time: <input type=\"text\"name=\"endtime\"></p>");
    printf("subject: <input type=\"text\"name=\"subject\"></p>");
    printf("information: <input type=\"text\"name=\"information\"></p>");
    printf("username: <input type=\"text\"name=\"username\"></p>");
    //printf("username: <input type=\"text\"value=\"username variables\"></p>");
    printf("<input type=\"submit\"value=\"add meeting\">");
    printf("</form>");
    
}

//don't use this one
void viewMeetForm(){
    //note:add href at viewmeet.exe to go back
    
    printf("<form action=\"viewmeet.exe\" method=\"GET\"> <p>");
    printf("<input type=\"submit\"value=\"viewmeet\">");
    printf("</form>");
    
}




//you could write a another cgi
void systeminfo(){
    DIR * dir;
    DIR * fdir;
    struct dirent * ptr;
    struct dirent * ftr;
    int dircount=0;
    int filecount=0;
    // char pathdir[100]="/Users/wmy/Desktop/project1/step3/step3/temp";
    char pathdir[100]="/Library/WebServer/CGI-Executables/doc";
    char *pathname;
    dir = opendir(pathdir);
    
    while((ptr = readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..")==0 || strcmp(ptr->d_name, ".DS_Store")==0)
            continue;    /* skip self and parent */
        
        //count dir user
        
        pathname=(char *)malloc(sizeof(char)*strlen(pathdir)+(strlen(ptr->d_name)+1));
        strcat(pathname,pathdir);
        strcat(pathname,"/");
        strcat(pathname,ptr->d_name);
        
        
        //  strcat(pathdir,"/");
        //  strcat(pathdir,ptr->d_name);
        
        
        //    printf("pathdir: %s \n",pathdir);
        
        fdir=opendir(pathname);
        
        if(fdir!=NULL){
            //open the inner dirct=user;
            printf("<p>");
            printf("user name : %s\n", ptr->d_name);
            printf("</p>");
            dircount++;
            printf("<p>Meeting info :</p>");
            while((ftr=readdir(fdir))!=NULL)
            {
                
                if(strcmp(ftr->d_name, ".") == 0 || strcmp(ftr->d_name, "..")==0 || strcmp(ftr->d_name, ".DS_Store")==0)
                    continue;    /* skip self and parent */
                filecount++;
                // printf("Meeting info : %s \n", ftr->d_name);
                printf("<p>");
                printf(" %s \n", ftr->d_name);
                printf("</p>");
            }
            
            
        }
        
        
        
    }
    printf("<p>");
    printf("there are: %d users \n",dircount);
    printf("</p>");
    printf("<p>");
    printf("there are: %d meetings \n",filecount);
    printf("</p>");
    closedir(dir);
    
}










int main(){
   /*
    char *qstring;
    
    char *temp;
    char *usertemp;
    int testlen=strlen(getenv("QUERY_STRING"));
    
    
    char *password;
    //md5 password   */
    
    FILE *pipe;
  /*  char md5password[128];
    char *command;
    
    
    char *result;
    char *part1[3];
    char *value[3];
    int i=0;
    
    FILE *fr;
    char *part2[3];
    
    int login=-1;
    
    
    //new here
    
    char *option=" "; //default
    char *thisuser=" ";//default
    
    //  char *option="newmeet"; //default
    // char *thisuser="mw2907";//default
    char *tmpstr;
    
    
    //caladdmeet
    char* info;
    char* tail; */
    
    
    
    
    
    
    /*cgi so lets print out */
    printf( "Content-type: text/html\n\n" );
    /* lets check if we are processing inputs */
    printf("<html><head><title>Test 1</title></head> <body>");
    
    qstring=getenv("QUERY_STRING");
    
    
    
    
    if( strlen(qstring)!=0){
        tmpstr=(char*)malloc(strlen(qstring)+1);
        strcpy(tmpstr,qstring);
        
      //  printf("<P> tmpstr %s </p>",tmpstr);
        
        option=(char*)malloc(strlen(qstring)+1);
        thisuser=(char*)malloc(strlen(qstring)+1);
        
        option=strtok(tmpstr,"=");
        
        
        if(strcmp(option,"str")==0){
            // printf("search string ");
            
            tail=(char*)malloc(strlen(qstring));
            info=(char*)malloc(strlen(qstring));
            
            tail=strtok(NULL,"");
            printf("search string :[ %s ]</p>",tail);
            
            strcat(info,"str=");
            strcat(info,tail);
            
         //  printf("<p>searchstr: %s   </p>",info);
            
           urldecode(info,strlen(info));
            
         printf("<p>decodeinfo: %s   </p>",info);
            
            //function
            
           searchstr(info);
            
            
            
        }else if(strcmp(option,"specfictimestartdate")==0){
            //save meeting because it starts with startdate
            printf("between two days and two specfic times</p>");
            
            tail=(char*)malloc(strlen(qstring));
            info=(char*)malloc(strlen(qstring));
            
            tail=strtok(NULL,"");
         //   printf("twodaystail :%s</p>",tail);
            
            strcat(info,"startdate=");
            strcat(info,tail);
            
           // printf("<p>saveinfo: %s   </p>",info);
            
            urldecode(info,strlen(info));
         
            printf("<p>decodeinfo: %s   </p>",info);
            
            //function
            
            specfictime(info);
            
            
            
        }else if(strcmp(option,"2daysstartdate")==0){
            //save meeting because it starts with startdate
            printf("between two days </p>");
            
            tail=(char*)malloc(strlen(qstring));
            info=(char*)malloc(strlen(qstring));
            
            tail=strtok(NULL,"");
          //  printf("twodaystail :%s</p>",tail);
            
            strcat(info,"startdate=");
            strcat(info,tail);
            
          //  printf("<p>saveinfo: %s   </p>",info);
            
            urldecode(info,strlen(info));
            
           printf("<p>decodeinfo: %s   </p>",info);
            
            //function
            
            twodays(info);
            
            
            
            
        }else if(strcmp(option,"startdate")==0){
            //save meeting because it starts with startdate
            printf("save </p>");
            
            tail=(char*)malloc(strlen(qstring));
            info=(char*)malloc(strlen(qstring));
            
            tail=strtok(NULL,"");
         //   printf("caltail :%s</p>",tail);
            
            strcat(info,"startdate=");
            strcat(info,tail);
            
          //  printf("<p>saveinfo: %s   </p>",info);
            
            urldecode(info,strlen(info));
            
            printf("<p>decodeinfo: %s   </p>",info);
            
            
            
            //function:
            savemeet(info);
            
            
            
            
        }else if(strcmp(option,"day")==0){
            printf("<p>caladdmeet:</p>");
            
            tail=(char*)malloc(strlen(qstring));
            info=(char*)malloc(strlen(qstring));
            
            tail=strtok(NULL,"");
           // printf("caltail :%s</p>",tail);
            
            strcat(info,"day=");
            strcat(info,tail);
            
           // printf("<p>calinfo: %s   </p>",info);
            
            urldecode(info,strlen(info));
            
            
            //function:
            caladdmeet(info);
            
            
        }else{
            
            //format: todo=newmeet=user;
            option=strtok(NULL,"=");
            if(option!=NULL){
                thisuser=strtok(NULL,"=");
             //   printf("<P> option is: %s , this user is: %s </p>",option,thisuser);
            }
            
            
        }
        
        
        
        
    }
    
    
    
    
    
    
    
    
    if(strcmp(option,"newmeet")==0){
        printf("todo=newmeet ");
        printf("username: %s </p>", thisuser);
        
        //function:
        if(thisuser!=NULL)
        {
            addmeet(thisuser);
        }
        
        
        
        
        
    }else if(strcmp(option,"viewmeet")==0){
        printf("todo=viewmeet ");
        printf("<p>username: %s </p>", thisuser);
        
        
        //function:
        if(thisuser!=NULL)
        {
            viewmeet(thisuser);
        }
        
        
        
    }else if(strcmp(qstring,"todo=systeminfo")==0){
        printf("todo=systeminfo");
        
        
        
        //function
        systeminfo();
        
        
    }else if(strlen(getenv("QUERY_STRING"))!=0 && strcmp(qstring,"todo=error")!=0&& strcmp(option,"str")!=0&& strcmp(option,"startdate")!=0 && strcmp(option,"day")!=0 && strcmp(option,"2daysstartdate")!=0 && strcmp(option,"specfictimestartdate")!=0)
        //do I need to give some memory to char *qstring?
    {  // qstring=getenv("QUERY_STRING");
       // printf("NEW TEST: %s ",qstring);
       // printf("Am processing input");
        // get the key value through separating & and =
        
        
        result=(char*)malloc(sizeof(char)*(strlen(qstring)+1));
        result=strtok(qstring,"&");
        
        //each seperate by & still include =
        for (i=0; result!=NULL; i++)
        {
            part1[i]=(char *)malloc(sizeof(char)*(strlen(result)+1));
            
            //  printf("result is: %s \n",result);
            strcpy(part1[i],result);
            //  printf("result is: %s \n",(p[i]));
            result = strtok( NULL, "&" );
            
        }
        
        
        
        for(i=0; i<2; i++ ){
            value[i]=(char *)malloc(sizeof(char)*(strlen(part1[i])+1));
            strtok(part1[i],"=");
            value[i]=strtok(NULL,"=");
            
            // printf("value: %s \n",value[i]);
            
            
        }
        
        if(value[0]==NULL||value[1]==NULL){
            // if input is not correct
            
            printf("<a href=\"MainProject1.exe?todo=error\">Error! Click here to go back </a>");
        }else{
            
            //if input is correct proccess start here
            
            //some times it is const can't change value
            user=(char *)malloc(sizeof(char)*(strlen(value[0])+1));
            user=value[0];
            
            password=(char *)malloc(sizeof(char)*(strlen(value[1])+1));
            password=value[1];
            
            //decode the url
            
            urldecode(user,strlen(user)+1);
            urldecode(password,strlen(password)+1);
            
            printf("user: %s  ", user);
         //   printf("password: %s  ", password);
            
            
            
            //file:check
            if((fr=fopen("password.txt","r+"))==NULL){
                perror("can't read \n");
                exit(1);
            }else{
              //  printf("read!");
            }
            
            
            //read each line;
            temp=(char *)malloc(sizeof(char)*(testlen+1));
            while(fgets(temp,100,fr)!=NULL)
            {
                // printf("file: %s", temp);
                part2[0]=(char *)malloc(sizeof(char)*(strlen(temp)+1));
                part2[1]=(char *)malloc(sizeof(char)*(strlen(temp)+1));
                part2[0]=strtok(temp,"=");
                part2[1]=strtok(NULL,"=");
                
                //what is in file each line
                // printf("p20: %s ",part2[0]);
                // printf("p21: %s </P>", part2[1]);
                
                
                
                
                //create md5 password here
                // printf("create md5 </p>");
                command=(char*)malloc(100);
                strcat(command,"md5 <<< ");
                strcat(command,password);
                pipe=popen(command,"r");
                
                if (pipe == NULL) {
                    printf("Failed to get md5password\n" );
                    exit(0);
                }
                
                while(!feof(pipe)) {
                    if(fgets(md5password, 128,pipe) != NULL)
                        //since get string from file,should remove the last "\n", so use strtok;
                        strtok(md5password,"\n");
                    //  printf("md5 password: %s </p>",md5password);
                    
                }
                
                
                /* close */
                pclose(pipe);
                
                
                
            
                
                //check
                if(strcmp(part2[0],user)==0 &&strcmp(part2[1],md5password)==0 ){
                    //  printf("login success!");
                    login=0;
                    break;
                }else if(strcmp(part2[0],user)==0 && strcmp(part2[1],md5password)!=0){
                    //  printf("password fail");
                    login=1;
                }else{
                    // printf("Don't have this user");
                    login=2;
                }
                
                
                
            }
            
            
            if(login==0){
                
                
                
                
                printf("<p><a href=\"MainProject1.exe?todo=newmeet=\%s \">add new meeting</a></p>",user);
                
                printf("<p><a href=\"MainProject1.exe?todo=viewmeet=\%s \">view your meetings</a></p>",user);
                
                printf("<a href=\"MainProject1.exe?todo=systeminfo\">Click here for for system informations</a></p>");
                
                
                
                
                
                
                
                
                
                //calendar
                printf("<a href=\"/cal2.html?user=\%s\">Go to calendar</a><p>",user);
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                //step5 and step6 for specfic
                
   printf("<P>---------  -ONLY ADMIN ARE ALLOWED TO DO FOLLOWING THING------(STEP5 AND 6 )-------------</P>");
           
                
                
                
                
                
                
                //if the user is admin you can add a group meeting;
                if(strcmp("admin",user)==0){
                    
                    printf("<html><head><title>step5 query</title></head> <body>");
                    //cal add event form
                    
                    //1.all schedules
                    
                    printf("<a href=\"MainProject1.exe?todo=systeminfo\">Click here for for all schedules</a></p>");
                    
                    //2 all shcedules between 2dates
                    
                    printf("search between two dates,please input starting and end days");
                    printf("</p>");
                    printf("Format:startdate:June,1,2014  enddate:June,10,2014");
                    printf("</p>");
                    printf("<form action=\"MainProject1.exe\" method=\"GET\"> <p>");
                    
                    printf("starting date: <input type=\"text\"name=\"2daysstartdate\">");
                    
                    printf("ending date: <input type=\"text\"name=\"enddate\">");
                    
                    printf("<input type=\"submit\"value=\"search\"></p>");
                    printf("</form>");
                    
                    
                    //3 all shcedules between 2dates and and between specific times
                    printf("search between two dates and time,please input starting and end days and time");
                    printf("</p>");
                    printf("Format:startdate:June,1,2014  enddate:June,10,2014, time between 10:00am and 1:00pm");
                    printf("</p>");
                    printf("<form action=\"MainProject1.exe\" method=\"GET\"> <p>");
                    
                    printf("starting date: <input type=\"text\"name=\"specfictimestartdate\">");
                    
                    printf("ending date: <input type=\"text\"name=\"enddate\">");
                    
                    printf("time between: <input type=\"text\"name=\"time1\">");
                    
                    printf("and: <input type=\"text\"name=\"time2\">");
                    
                    printf("<input type=\"submit\"value=\"search\"></p>");
                    printf("</form>");
                    
                    //4 search through the text info for specific string.
                    printf("search through the text info for specific string");
                    printf("</p>");
                    printf("Format should be words:search string: group");
                    printf("</p>");
                    
                    printf("<form action=\"MainProject1.exe\" method=\"GET\"> <p>");
                    
                    printf("search string: <input type=\"text\"name=\"str\">");
                    
                    printf("<input type=\"submit\"value=\"search\"></p>");
                    printf("</form>");
                    
                    
                    
                    
                    
                    
                    //step6   Find a free spot
                    printf("search between two dates and time,please input starting and end days and time");
                    printf("</p>");
                    printf("Format:startdate:June,1,2014 starting time: 10:00am   interval: 3 ");
                    printf("</p>");
                    printf("<form action=\"find1.exe\" method=\"GET\"> <p>");
                    
                    printf("starting date: <input type=\"text\"name=\"startdate\">");
                    printf("starting time: <input type=\"text\"name=\"startingtime\">");
                    printf("interval: <input type=\"text\"name=\"interval\">");
                    printf("hours");
                    printf("<input type=\"submit\"value=\"find free spot\"></p>");
                    printf("</form>");
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                 //   printf("<a href=\"45form.exe\">Go back to menu</a><p>");
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    printf("</html>");
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                }
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
            }else if(login==1){
                printf("password fail");
                printf("<a href=\"MainProject1.exe\">FAIL! Click here to go back </a>");
            }else{
                printf("Fail!Don't have this user");
                printf("<a href=\"MainProject1.exe\">FAIL! Click here to go back </a>");
            }
            
            
            
            
            
        }
        
        
        
        
        
        
        
        
        
        
    }
    else{
        //there are some problem when doing search str, so add some condition
        if(strcmp(option,"str")!=0&& strcmp(option,"startdate")!=0 && strcmp(option,"day")!=0 && strcmp(option,"2daysstartdate")!=0 && strcmp(option,"specfictimestartdate")!=0){
            showFirstForm();
        }

        
    }
    
    
    
    free(qstring);
    free(result);
    free(temp);
    free(user);
    free(password);
    free(part1);
    free(part2);
    free(value);
    fclose(fr);
    
    
    
    printf("</html>");
    return 0;
} /* end main */
