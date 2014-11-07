//
//  findspot.cpp
//  step6
//
//  Created by 吴梦宇 on 6/25/14.
//  Copyright (c) 2014 ___mengyu wu___. All rights reserved.
//

#include "find1.h"

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

char* month[]={"January","February","March","April","May","June","July","August","September","October","November","December"};


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



char* inttochar(int num){
    vector<char> cv;
    char cnum[5];
    char* charnum;
    
    int i=0;
    //num is one digit or two digits
    if(num==0){
        charnum="0";
        
    }else{
        while(num){
            
            cv.insert(cv.begin(),'0'+(num%10));
            num=num/10;
            
        }
        
        for(i=0; i<cv.size();i++){
            //    printf("c: %c",cv[i]);
            cnum[i]=cv[i];
        }
        cnum[i]='\0';
        
        charnum=(char*)malloc(sizeof(char)*strlen(cnum)+1);
        strcpy(charnum,cnum);
        
    }
    return charnum;
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


int main(int argc, const char * argv[])
{
    //local
    char *min;
    
    
    printf( "Content-type: text/html\n\n" );
    
    
   //here is added
    
    //improcess input;
    
    qstring=getenv("QUERY_STRING");
  //  printf("qstring:: %s",qstring);
    
    
    results=(char*)malloc(sizeof(char)*(strlen(qstring)+1));
    results=strtok(qstring,"&");
    
    //each seperate by & still include =
    for (i=0; results!=NULL; i++)
    {   //malloc is important
        parts[i]=(char *)malloc(sizeof(char)*(strlen(results)+1));
        
       // printf("result is: %s </p>",results);
        strcpy(parts[i],results);
        results = strtok( NULL, "&" );
        
    }
    
    
    
    
    
    
    
    for(i=0; i<3; i++ ){
        values[i]=(char *)malloc(sizeof(char)*(strlen(parts[i])+1));
        strtok(parts[i],"=");
        values[i]=strtok(NULL,"=");
        
    }
    
    
    
    
    if(values[0]==NULL||values[1]==NULL||values[2]==NULL){
        //should go back to main,NEED TO DEAL WITH
        printf("<a href=\"MainProject1.exe\">Go back,please input two dates!</a>");
    }else{
        
       
        
        datein1=values[0];
        time1in=values[1];
        timelen=values[2];
        
        
        
        // if not null change defalut;
        urldecode(datein1,strlen(datein1)+1);
        urldecode(time1in,strlen(time1in)+1);
        urldecode(timelen,strlen(timelen)+1);
    

        
        
        //change defalut day;
        
        sdates=datein1;
        interval=chartoint(timelen);
        
        
        
        //between two days and specfic time
        
        //starttime;
        i=0;
        temptime=(char *)malloc(sizeof(char)*(strlen(time1in)+1));
        strcpy(temptime,time1in);
        hour=strtok(temptime,":");
        
      //  printf("hour: %s \n", hour);
        rest=strtok(NULL,":");
      //  printf("rest: %s \n",rest);
        min=(char*)malloc(3);
        apm=(char*)malloc(3);
        
        if(rest!=NULL && strlen(rest)<=4){
            strncpy(min,rest,2);
            strcat(min,"\0");
          //  printf("min: %s \n",min);
            strncpy(apm,(rest+2),2);
            strcat(apm,"\0");
          //  printf("apm: %s \n",apm);
        }
        
        if(hour!=NULL&& min!=NULL && apm !=NULL){
            //change defalut;
            time1=(char*)malloc(10);
            strcpy(time1,hour);
            strcat(time1,":");
            strcat(time1,min);  //10:00;
            
            apm1=apm;
            
            stime=time1;
            
        }
        
        
        
        
        
        
        
        //begin process
        
        result2=(char *)malloc(sizeof(char)*(strlen(sdates)+1));
        strcpy(result2,sdates);
        smonth=strtok(result2,",");
        sday=strtok(NULL,",");
        syear=strtok(NULL,",");
        
        
        iday=chartoint(sday);
        imonth=getmonth(smonth);
        iyear=chartoint(syear);
        
     //   cout<<"specfic start dates:"<<smonth<<":"<<sday<<":"<<syear<<endl;
        
     //   cout<<"imonth:"<<imonth<<"iday"<<iday<<"iyear"<<iyear<<"</p>"<<endl;
        
        
        
        
        
        
        
        //requirement start time
        
        temptime=(char *)malloc(sizeof(char)*(strlen(stime)+1));
        strcpy(temptime,stime);
        shs=strtok(temptime,":");
        rest=strtok(NULL,":");
        smins=(char*)malloc(3);
        sapms=(char*)malloc(3);
        
        
        //to add "\0" to avoid mistake char to int;
        if(rest!=NULL && strlen(rest)<=4){
            strncpy(smins,rest,2);
            strcat(smins,"\0");
        //    printf("min: %s \n",min);
          //  cout<<"rest:"<<rest<<endl;
            strncpy(sapms,(rest+2),2);
            strcat(sapms,"\0");
        //  printf("apm: %s \n",apm);
        }
        
        
        inth=chartoint(shs);
       // cout<<"char to int inth:"<<inth<<"</p>"<<endl;
        
        intmin=chartoint(smins);
        
        
        //need to check!
       // cout<<"smins::"<<smins<<"</p>"<<endl;
       // cout<<"samps::"<<sapms<<"</p>"<<endl;
       
        
        //please use apm
        if(strcmp(apm,"pm")==0){
            inth=inth+12;
        }
        
      // cout<<"inth:"<<inth<<"</p>"<<endl;
        
        
     //   cout<<"specfic start time:"<<shs<<":"<<smins<<":"<<sapms<<endl;
     //   cout<<"int specfic start time:"<<inth<<":"<<intmin<<"</p>"<<endl;
        
        
        
        
        
        
     //to deal with the information about file
        
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
                /*
                printf("<p>");
                printf("user name : %s\n", ptr->d_name);
                printf("</p>");
               
                printf("<p>Meeting info :</p>");
                */
                 dircount++;
                username=(char*)malloc(strlen(ptr->d_name)+1);
                strcpy(username,ptr->d_name);
                userall.push_back(username);
                
                
                while((ftr=readdir(fdir))!=NULL)
                {
                    
                    if(strcmp(ftr->d_name, ".") == 0 || strcmp(ftr->d_name, "..")==0 || strcmp(ftr->d_name, ".DS_Store")==0)
                        continue;    /* skip self and parent */
                    filecount++;
                   
                    // printf("Meeting info : %s \n", ftr->d_name);
                    
                  //  printf("<p>");
                  //  printf(" %s \n", ftr->d_name);
                  //  printf("</p>");
                    
                    
                    //c++
                    
                    smeet=(char*)malloc(strlen(ftr->d_name)+1);
                    strcpy(smeet,ftr->d_name);
                    
                    
                    
                    cmeet.push_back(smeet);
                    
                    
                }
                gmeet.push_back(cmeet);
                
                
            }
            
            
            
        }
        
        printf("<p>");
        printf("System info: there are: %d users \n",dircount);
        printf("</p>");
        printf("<p>");
        printf("there are: %d meetings \n",filecount);
        printf("</p>");
        closedir(dir);
        
        
        
       
        
        
        
        
        
        char* newmeet;
        newmeet=(char*)malloc(sizeof(char)*(100));
        
  //  cout<<"<p>"<<imonth<<", "<< iday << ", "<<iyear <<"- "<<inth <<": "<<intmin <<" "<<interval<<endl;
        strcpy(newmeet,findspot(gmeet,imonth,iday,iyear,inth,intmin,interval));
        
       // cout<<"new meeting:  "<<newmeet<<endl;
        
        
    printf("<a href=\"addgroupmeet.exe?newmeet=%s\">Click here to add a group meet: %s </a></p>",newmeet,newmeet);
        
     
        

    }
    
    
 //end here
    
    
    
    return 0;
}




char* findspot(vector<vector< char* > > gmeet,int startmonth,int startday,int startyear, int starthour, int startmin, int interval){
    cout<<"-------------findspot---------------"<<endl;
    char* newmeet;
    
    
    int y=0;
    int x=0;
    char* start[3];
    char * end[3];
    
    char* startdate;
    char*  starttime;
    char * enddate;
    char*  endtime;
    
    while(x!=gmeet.size()){
        
       // printf("<p>");
      //  cout<<"begin:x:"<<x<<"y:"<<y;
       // cout<<"size"<<gmeet[x].size()<<endl;
      //  printf("</p>");
        
        if(y>(gmeet[x].size()-1)||(gmeet[x].size()==0)){
            x++;
            y=0;
            continue;
        }else{
            
          //  printf("<p>");
          //  cout<<"x:"<<x<<"y:"<<y;
         //   cout<<"read in:"<<gmeet[x][y]<<endl;
          //  printf("</p>");
            
            char * tmp;
            tmp=gmeet[x][y];
            
            char* meet=(char *)malloc(sizeof(char)*((strlen(tmp))+1));
            strcpy(meet,tmp);
            meet=strtok(meet,".");
            
            meet=strtok(meet,".");
            meet=strtok(meet,"-");
            startdate=strtok(NULL,"-");
            starttime=strtok(NULL,"-");
            enddate=strtok(NULL,"-");
            endtime=strtok(NULL,"-");
            //       cout<<"startdate: "<<endtime<<endl;
            //     cout<<"endtime: "<<startdate<<endl;
            //       cout<<"meet: "<<meet<<endl;
            
            
            //startday!
            int   i=0;
            char*  result2=(char *)malloc(sizeof(char)*(strlen(startdate)+1));
            strcpy(result2,startdate);
            
            start[0]=strtok(result2,",");
            for(i=1; i<3; i++){
                start[i]=strtok(NULL,",");
                
                if(start[i]==NULL){
                    break;
                }
            }
            
            
            
            //enddate infor
            i=0;
            char*    result3=(char *)malloc(sizeof(char)*(strlen(enddate)+1));
            strcpy(result3,enddate);
            
            end[0]=strtok(result3,",");
            for(i=1; i<3; i++){
                end[i]=strtok(NULL,",");
                
                if(end[i]==NULL){
                    break;
                }
            }
            
            
            
            //between two days and specfic time
            // if doesn't have am/pm defaulst am
            //starttime;
            i=0;
            char *    temptime=(char *)malloc(sizeof(char)*(strlen(starttime)+1));
            strcpy(temptime,starttime);
            char*   hour=strtok(temptime,":");
            // printf("hour: %s \n", hour);
            char*    rest=strtok(NULL,":");
            // printf("rest: %s \n",rest);
            char*    min=(char*)malloc(3);
            char*    apm=(char*)malloc(3);
            if(rest!=NULL && strlen(rest)<=4){
                strncpy(min,rest,2);
                strcat(min,"\0");
                //   printf("min: %s \n",min);
                strncpy(apm,(rest+2),2);
                strcat(apm,"\0");
                //  printf("apm: %s \n",apm);
            }
            
            
            
            //endtime;
            i=0;
            temptime=(char *)malloc(sizeof(char)*(strlen(endtime)+1));
            strcpy(temptime,endtime);
            char*   houre=strtok(temptime,":");
            //  printf("houre: %s \n", houre);
            rest=strtok(NULL,":");
            //  printf("reste: %s \n",rest);
            char*   mine=(char*)malloc(3);
            char*   apme=(char*)malloc(3);
            if(rest!=NULL && strlen(rest)<=4){
                strncpy(mine,rest,2);
                strcat(mine,"\0");
                // printf("mine: %s \n",min);
                strncpy(apme,(rest+2),2);
                strcat(apme,"\0");
                // printf("apme: %s \n",apme);
            }
            
            
            
            //modify;
            
            int sm=getmonth(start[0]);
            int em=getmonth(end[0]);
            
            
            int  sd=chartoint(start[1]);
            int   ed=chartoint(end[1]);
            
            int sy=chartoint(start[2]);
            int ey=chartoint(start[2]);
            
            
         //   cout<<"sm:"<<sm<<"sd"<<sd<<"sy"<<sy<<"</p>"<<endl;
         //   cout<<"em:"<<sm<<"ed"<<sd<<"ey"<<sy<<"</p>"<<endl;
            
            
            int   h=chartoint(hour);
            int   m=chartoint(min);
            int  he=chartoint(houre);
            int me=chartoint(mine);
            
            
           //modify am/pm to 24:00
            
            if(strcmp(apm,"pm")==0){
                h=h+12;
            }
            
            
            if(strcmp(apme,"pm")==0){
                he=he+12;
            }
            
            
        // printf("sd: %d, ed: %d \n",sd ,ed);
         
         //  printf("h: %d, m: %d apm: %s </p>",h ,m,apm);
            
         //  printf("he: %d, me: %d apme: %s </p>",he ,me,apme);
            
           
            
            
           
            //if not in the same month or year there is no conflict
            
            if(ey<startyear|| em<startmonth){
               /*
                printf("<p>");
                cout<<"startmonth,startyear :"<<startmonth<<"   "<<startyear<<endl;
                cout<<"startday,starthour :"<<startday<<"   "<<starthour<<" "<<startmin<<endl;
                printf("</p>");
                
                cout<<"consider next!"<<gmeet[x][y]<<endl;
                */
                y++;
                continue;
            }
            
            if(sy>startyear|| sm>startmonth){
                /*
                printf("<p>");
                cout<<"startmonth,startyear :"<<startmonth<<"   "<<startyear<<endl;
                cout<<"startday,starthour :"<<startday<<"   "<<starthour<<" "<<startmin<<endl;
                printf("</p>");
                cout<<"consider next!"<<gmeet[x][y]<<endl;*/
                y++;
                continue;
            }
            
            
            
            
            //conflict
            if(sy<startyear&& ey>startyear ){
                printf("year conflict</p>");
                cout<<"<p> conflict:"<<gmeet[x][y]<<"</p>"<<endl;
                //erase this meeting in array
                gmeet[x].erase(gmeet[x].begin()+y);
                x=0;
                y=0;
                startmonth=em;
                startyear=ey;
                startday=ed;
                starthour=he;
                startmin=me;
                continue;

            }
            
            
            
            //conflict
            if(sm<startmonth&& em>startmonth ){
                printf("month conflict</p>");
                cout<<"<p> conflict:"<<gmeet[x][y]<<"</p>"<<endl;
                //erase this meeting in array
                gmeet[x].erase(gmeet[x].begin()+y);
                x=0;
                y=0;
                startmonth=em;
                startyear=ey;
                startday=ed;
                starthour=he;
                startmin=me;
                continue;
                
            }

            
            
            
            
            
            if(sd>startday && ed>startday){
                /*
                printf("<p>");
                cout<<"startday,starthour :"<<startday<<"   "<<starthour<<endl;
                printf("</p>");
                cout<<"consider next!"<<gmeet[x][y]<<endl;
                 */
                y++;
                continue;
            }
            
            
            
            
            if(sd<startday && ed<startday){
                /*
                //no need to consider some meeting before the requirement time;
                printf("<p>");
                cout<<"startday,starthour :"<<startday<<"   "<<starthour<<endl;
                printf("</p>");
                cout<<"no need to consider:"<<gmeet[x][y]<<endl; */
                gmeet[x].erase(gmeet[x].begin()+y);
                
               // x++;
               // y=0;
                y++;
                continue;
                
            }
            
            
            //check this meeting conflict with the requirement
            
            
            //another case need to consider, that start and end day are not the same
            
            if((sd==startday||sd<startday)  && ed>startday){
                //conflict;
                /*
                printf("<p>");
                cout<<"startday,starthour :"<<startday<<"   "<<starthour<<endl;
                printf("</p>"); */
            
               cout<<"<p> Now: startday: "<<startday<<" starthour: "<<starthour<<"interval: " <<interval<<"</p>"<<endl;
                cout<<"<p> conflict:"<<gmeet[x][y]<<"</p>"<<endl;
            
                gmeet[x].erase(gmeet[x].begin()+y);
                x=0;
                y=0;
                startday=ed;
                if(he>=(24-interval)){
                    
                    
                    
                    //increase the startday!
                    if(startday>=30){
                        if(startmonth==12){
                            startyear++;
                            startmonth=1;
                            startday=1;
                            starthour=0;
                            startmin=0;
                        }else{
                            startmonth++;
                            startday=1;
                            starthour=0;
                            startmin=0;
                        }
                    
                    }else{
                        startday++;
                        starthour=0;//or start from 6:00 according to the design;
                        startmin=0;
                    }
     
                    
                   
                }else{
                    startmonth=em;
                    startyear=ey;
                    startday=ed;
                    starthour=he;
                    startmin=me;
                }
                
                
                continue;
                
            }
           
            
            if((sd==startday||sd<startday)  && ed>startday){
                //conflict;
              
               
              cout<<"<p> Now: startday: "<<startday<<" starthour: "<<starthour<<"interval: " <<interval<<"</p>"<<endl;
               
                
                cout<<"<p> conflict:"<<gmeet[x][y]<<"</p>"<<endl;
                
                gmeet[x].erase(gmeet[x].begin()+y);
                x=0;
                y=0;
                startday=ed;
                if(he>=(24-interval)){
                    
                    
                    
                    //increase the startday!
                    if(startday>=30){
                        if(startmonth==12){
                            startyear++;
                            startmonth=1;
                            startday=1;
                            starthour=0;
                            startmin=0;
                        }else{
                            startmonth++;
                            startday=1;
                            starthour=0;
                            startmin=0;
                        }
                        
                    }else{
                        startday++;
                        starthour=0;//or start from 6:00 according to the design;
                        startmin=0;
                    }
                    
                    
                    
                }else{
                    startmonth=em;
                    startyear=ey;
                    startday=ed;
                    starthour=he;
                    startmin=me;
                }

                
                
                continue;
                
            }
            

            
            //if min conflict;
            
            if(  (sd==startday)&& (h==starthour)&&(m>startmin)){
                //min conflict
                printf("min conflict</p>");
                cout<<"<p> conflict:"<<gmeet[x][y]<<"</p>"<<endl;
                gmeet[x].erase(gmeet[x].begin()+y);
                x=0;
                y=0;
                
                //should start after this meeting;
                startmonth=em;
                startyear=ey;
                startday=ed;
                starthour=he;
                startmin=me;
                
                continue;
                
            }
            
            
            
            
            
            
            if(  (sd==startday) && !( (he<=starthour) || (h>=starthour+interval) )) {
                //conflict;
                /*
                printf("<p>");
                cout<<"startday,starthour :"<<startday<<"   "<<starthour<<endl;
                printf("</p>");
                printf("<p>");
                cout<<"conflict:"<<gmeet[x][y]<<endl;
                printf("</p>"); */
cout<<"<p> Now: startday: "<<startday<<" starthour: "<<starthour<<"interval: " <<interval<<"</p>"<<endl;
                cout<<"<p> conflict:"<<gmeet[x][y]<<"</p>"<<endl;
                gmeet[x].erase(gmeet[x].begin()+y);
                x=0;
                y=0;
                //reset the starting time to the end of the meeting;
                //check whether the startday should increase, it increase when the end hour of the meeting is >=(24-interval);
                
                if(he>=(24-interval)){
                    
                    
                    
                    //increase the startday!
                    if(startday>=30){
                        if(startmonth==12){
                            startyear++;
                            startmonth=1;
                            startday=1;
                            starthour=0;
                            startmin=0;
                        }else{
                            startmonth++;
                            startday=1;
                            starthour=0;
                            startmin=0;
                        }
                        
                    }else{
                        startday++;
                        starthour=0;//or start from 6:00 according to the design;
                        startmin=0;
                    }
                    
                    
                    
                }else{
                    startmonth=em;
                    startyear=ey;
                    startday=ed;
                    starthour=he;
                    startmin=me;
                }
                
                
                continue;
            }else {
                // cout<<" other case that is not conflit:"<<gmeet[x][y]<<endl;
                //if this time is not conflict with the yth meeting of user x; then check user x=1;
               y++;
                continue;
            }
            
            
        }
        
        
        
        
        
    }
    
    
    
    
    cout<<"<p>startday: "<<startday<<" starthour: "<<starthour<<" free interval"<<interval<<"</p>"<<endl;
    
    
    
    
    
    
    
    // cout<<"notes!!!!need improve somthing here !!!!!!!!!!!!!!!";
    
    //malloc memoery to new meet
    
    
    //format:june,4,2014-0:00am-june,5,2014-5:00am.app.txt
    
    
    
    
    
    newmeet=(char*)malloc(sizeof(char)*100);
    
    //only consider day , need to take startmonth,and stardtyear into consideration!!!!!
    //start month=start[0]. start year=start[2];
    
    char* charday=inttochar(startday);
    //  cout<<"charday:"<<charday<<endl;
    //deal with hour;
    
    //start and end apm;
    char* sapm;
    char* eapm;
    
    
    //didn't consider mints here;
    int endhour=starthour+interval;
  //  cout<<"endhour"<<endhour<<endl;
    
    
    
    if(starthour>12){
        starthour-=12;
        sapm="pm";
    }else{
        sapm="am";
    }
    char* charstarthour=inttochar(starthour);
 //   cout<<"charstarthour "<<charstarthour<<endl;
    
    
    
    char* charstartmin="00"; //defalut;
    if(startmin!=0){
        charstartmin=inttochar(startmin);
    }
   
 //   cout<<"charstartmin "<<charstartmin<<"</p>"<<endl;
    

    int endday;
    
    if((endhour)>12&& endhour<=24){
        endhour-=12;
        eapm="pm";
        endday=startday;
        
    }else if(endhour>24){
        // if > 1 day;
        endhour-=24;
        eapm="am";
        
        endday=startday+1;
        
    }else{
        eapm="am";
        endday=startday;
    }
    
    char* charendhour=inttochar((endhour));
  // cout<<"charendhour "<<charendhour<<endl;
    
    
    char* charendday=inttochar(endday);
    // cout<<"charendday "<<charendday<<endl;
    

    cout<<"<p>"<<month[startmonth-1]<<","<<startday<<","<<startyear<<" at : "<<charstarthour<<":"<<charstartmin<<" "<<sapm<<" every one have free interval for:"<<interval<<" hours"<<"</p>"<<endl;

    
    
    
    
    strcat(newmeet,month[startmonth-1]);
    strcat(newmeet,",");
    strcat(newmeet,charday);
    strcat(newmeet,",");
    strcat(newmeet,inttochar(startyear));//year
    strcat(newmeet,"-");
    
    
    strcat(newmeet,charstarthour);
    strcat(newmeet,":");
    strcat(newmeet,charstartmin);
    strcat(newmeet,sapm);
    strcat(newmeet,"-");
    
    //doesn't consider the startday and endday is not at same day; need to consider it;
    strcat(newmeet,month[startmonth-1]);
    strcat(newmeet,",");
    //here may be the end day is not same day;if the interval is >24hour;
    strcat(newmeet,charendday);
    strcat(newmeet,",");
    strcat(newmeet,inttochar(startyear));
    strcat(newmeet,"-");
    
    
    strcat(newmeet,charendhour);
    strcat(newmeet,":");
    strcat(newmeet,charstartmin);
    strcat(newmeet,eapm);
    
    
    
    
    
    
    strcat(newmeet,".app.txt");
    
    
    
    
  //  cout<<"<p> new meeting: "<<newmeet<<"</p>"<<endl;
    
    
    
    
    
    
    return newmeet;
}






