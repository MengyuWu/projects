//
//  findspot.cpp
//  step6
//
//  Created by 吴梦宇 on 6/25/14.
//  Copyright (c) 2014 ___mengyu wu___. All rights reserved.
//


//
//  main.c
//  viewmeet
//
//  Created by 吴梦宇 on 6/21/14.
//  Copyright (c) 2014 ___mengyu wu___. All rights reserved.
//
#include "addgroupmeet.h"
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

char* findspot(vector<vector< char* > > gmeet, int startday, int starthour, int startmin, int interval);


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



int main(int argc, const char * argv[])
{
    
    
    
       
    printf( "Content-type: text/html\n\n" );
    
    
    //here is added
    
    //improcess input;
    
    qstring=getenv("QUERY_STRING");
    printf("qstring:: %s",qstring);
    
    
    results=(char*)malloc(sizeof(char)*(strlen(qstring)+1));
    results=strtok(qstring,"=");
    newmeet=(char*)malloc(sizeof(char)*(strlen(qstring)+1));
    newmeet=strtok(NULL,"=");
   
    printf("new group meet before decode: %s",newmeet);
    
    
    
    
    
    if(newmeet==NULL){
        printf("<a href=\"45form.exe\">Go back to find another free spot</a>");
    }else{
        
        
        
        
        
        
        // if not null change defalut;
        urldecode(newmeet,strlen(newmeet)+1);
       
        printf("new group meet after decode: %s",newmeet);

       
        
        
        dir = opendir(pathdir);
        
        while((ptr = readdir(dir)) != NULL)
        {
            vector <char * > cmeet;
            if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..")==0 || strcmp(ptr->d_name, ".DS_Store")==0)
                continue;    /* skip self and parent */
            
            //count dir user
            
            pathname=(char *)malloc(sizeof(char)*strlen(pathdir)+(strlen(ptr->d_name)+1));
            strcat(pathname,pathdir);
            strcat(pathname,"/");
            strcat(pathname,ptr->d_name);
            
            
           
            
            fdir=opendir(pathname);
            
            if(fdir!=NULL){
                //open the inner dirct=user;
              //  printf("<p>");
              //  printf("user name : %s\n", ptr->d_name);
              //  printf("</p>");
                dircount++;
           
                
                username=(char*)malloc(strlen(ptr->d_name)+1);
                strcpy(username,ptr->d_name);
                userall.push_back(username);
                
                
              
                
                
            }
            
            
            
        }
        
        printf("<p>");
        printf("there are: %d users \n",dircount);
        printf("</p>");
      //  printf("<p>");
      //  printf("there are: %d meetings \n",filecount);
      //  printf("</p>");
        closedir(dir);
        
        
        
     
        
        
        
        for(i=0;i<userall.size();i++){
            printf("<p>");
            printf("userall: %s \n",userall[i]);
            printf("</p>");
            
            
        }
        
        
        
        
   
         
         //add new meeting
         
         i=0;
        // printf("<p>");
        // cout<<"user size: "<<userall.size()<<endl;
       //  printf("</p>");
         for(i=0;i<userall.size();i++){
         filepath=(char*)malloc(100);
         
         strcat(filepath,pathdir);
         strcat(filepath,"/");
         strcat(filepath,userall[i]);
         strcat(filepath,"/");
         strcat(filepath,userall[i]);
         strcat(filepath,"-");
         strcat(filepath,newmeet);
         //   cout<<"test2:"<<filepath<<endl;
         
         fp=fopen(filepath, "a+");
         if(fp==NULL){
         printf("<p>");
         printf("can't open file \n");
         printf("</p>");
         //perror("can't open");
         }else{
         printf("<p>");
         printf("add a group meeting success!\n");
         printf("</p>");
         
         fputs("subject=",fp);
         fputs("group meeting\n",fp);
         fputs("information=",fp);
         fputs(newmeet,fp);
         fputs("\n",fp);
         
         }
         fclose(fp);
         
         
         }
         
         
         
        
        
        
    }
    
    
    //end here
    
    
    
    
    
    
    
    
    return 0;
}









