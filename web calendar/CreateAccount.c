//
//  main.c
//  step2
//
//  Created by 吴梦宇 on 6/18/14.
//  Copyright (c) 2014 ___mengyu wu___. All rights reserved.
//


//check the input
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>



void showFirstForm(){
    printf("<form action=\"CreateAccount.exe\" method=\"GET\"> <p>");
    printf("Please enter name: <input type=\"text\"name=\"string\"></p>");
    printf("Please enter password: <input type=\"password\"name=\"passwd\"></p>");
    printf("Please enter email: <input type=\"text\"name=\"email\"></p>");
    printf("Add an account:<input type=\"submit\"value=\"submit\">");
    printf("</form>");
}


void showLoginForm(){
    printf("<form action=\"MainProject1.exe\" method=\"GET\"> <p>");
    printf("GO BACK TO LOGIN:<input type=\"submit\"value=\"login page\">");
    printf("</form>");
    
    printf("<form action=\"CreateAccount.exe\" method=\"GET\"> <p>");
    printf("Create account:<input type=\"submit\"value=\"Create an account\">");
    printf("</form>");
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
//decode 2 not good
void urldecoder(char *p)
{
    register int i=0;
    while(*(p+i))
    {
        if ((*p=*(p+i)) == '%')
        {
            *p=*(p+i+1) >= 'A' ? ((*(p+i+1) & 0XDF) - 'A') + 10 : (*(p+i+1) - '0');
            *p=(*p) * 16;
            *p+=*(p+i+2) >= 'A' ? ((*(p+i+2) & 0XDF) - 'A') + 10 : (*(p+i+2) - '0');
            i+=2;
        }
        else if (*(p+i)=='+')
        {
            *p=' ';
        }
        p++;
    }
    *p='\0';
    
}


int main(int argc, const char * argv[])
{
    char  *user;
    char *password;
    char *email;
    char *account;
    //char account[100];
    char *temp;
    int len=30;
    int exist=0;
    int testlen=0;
    
    char* usertemp;
    char *qstring;
    
    char *result;
    char *part1[3];
    char *value[3];
    int i;
    
    FILE *fw;
    FILE *fr;
    
    //md5 password

    FILE *pipe;
    char md5password[128];
    char *command;
    
    //add a new directory for every user;
    
    char *pathname;
    int status;
    
    
  
  
  account=(char *)malloc(sizeof(char)*100);
    
  printf( "Content-type: text/html \n\n" );
    
  
    printf("<html><head><title>Test 1</title></head> <body>");
   
    qstring=(char*)malloc(sizeof(char)*100);
    qstring=getenv("QUERY_STRING");
    testlen=strlen(qstring);
    
    if(testlen!=0 && strcmp(qstring,"todo=error")!=0 ){
        
        //do I need to give some memory to char *qstring?
     //   printf("1: %s ",qstring);
       
        // get the key value through separating & and =
        
        result=(char*)malloc(sizeof(char)*(strlen(qstring)+1));
        result=strtok(qstring,"&");
       
        
        for (i=0; result!=NULL; i++)
        {
            part1[i]=(char *)malloc(sizeof(char)*(strlen(result)+1));
            
            //  printf("result is: %s \n",result);
            strcpy(part1[i],result);
            //  printf("result is: %s \n",(p[i]));
            result = strtok( NULL, "&" );
        
        }
        
        for(i=0; i<3; i++ ){
            value[i]=(char *)malloc(sizeof(char)*(strlen(part1[i])+1));
            strtok(part1[i],"=");
            value[i]=strtok(NULL,"=");
          //  printf("value: %s \n",value[i]);
            
            
        }
        
        
        //check value if it is empty
        
       if(value[0]==NULL||value[1]==NULL||value[2]==NULL){
           // if input is not correct
           
           printf("<a href=\"CreateAccount.exe?todo=error\">Error! Click here to go back </a>");
        
       }else{
           // if input is correct process here
           
       
       
       
       
       
       
           //dealwith the input name password and email
           user=(char *)malloc(sizeof(char)*(strlen(value[0])+1));
           user=value[0];
           
           password=(char *)malloc(sizeof(char)*(strlen(value[1])+1));
           password=value[1];
           
           email=(char *)malloc(sizeof(char)*(strlen(value[2])+1));
           
           email=value[2];
           
           
           
           
           
           
           
           
           //join user password eamil into single string
           //decode the url
           
           urldecode(user,strlen(user)+1);
           urldecode(password,strlen(password)+1);
           urldecode(email,strlen(email)+1);
           
           
           
           
           
           
           
           //create md5 password here
           printf("create md5 </p>");
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
                   printf("md5 password: %s </p>",md5password);
                   password=md5password;
           }
           
           
           /* close */
           pclose(pipe);

           
           
           
           
           
           
           
           
           
           
           
           strcat(account,user);
           strcat(account,"=");
           strcat(account,password);
           strcat(account,"=");
           strcat(account,email);
           strcat(account,"\n");
           printf("account: %s", account);
           
           
           if((fr=fopen("password.txt","r+"))==NULL){
               perror("can't read \n");
               exit(1);
           }else{
               // printf("read!");
           }
           //a+ - open for reading and writing (append if file exists)
           if((fw=fopen("password.txt","a+"))==NULL){
               perror("can't open password file \n");
               exit(1);
           }else{
               // printf("write!");
           }
           
           
           //read each line;
           temp=(char *)malloc(sizeof(char)*(testlen+1));
           while(fgets(temp,100,fr)!=NULL)
           {
               usertemp=(char *)malloc(sizeof(char)*len);
               //  printf("temp: %s \n",temp);
               usertemp=strtok(temp,"=");
               // printf("user: %s \n", usertemp);
               if(strcmp(usertemp,user)==0){
                   printf("user has already been existed \n");
                   exist=1;
                   break;
               }
               
           }
           
           if(exist==0){
               printf("add account success!\n");
               fputs(account,fw);
               
               //add a new dir for a new user
               pathname=(char *)malloc(sizeof(char)*100);
               
               //cgi-executables directory can not make dir,you need to create another directory and you
               //can create directory and file in the doc
               strcat(pathname,"/Library/WebServer/CGI-Executables/doc/");
               strcat(pathname,user);
               printf("path: %s </p>",pathname);

               //makefile
               status = mkdir(pathname,0777);
               (!status) ? (printf("Directory created\n")) :
               (printf("Unable to create directory\n"));
           }
           
           
           showLoginForm();

       
       
       
       
       
       
       
       
       
       
       
       
       
       } // else end
        
        
     
  
        
    }
    else{
        
        showFirstForm();
    }

    
  
    
    fclose(fr);
    free(user);
    free(password);
    free(email);
    free(account);
    free(temp);
    free(usertemp);
    free(qstring);
    free(value);
    free(part1);
    free(command);
    fclose(fw);
    

    
    printf("</html>");
    
    
   
    
    
    return 0;
}

