 I would like to show my project to you: please call me if it doesn't work:3473873658
I also create a screenVideoRecord to show all the steps.

Step5 and step6 only allowed the “admin” to operate!
it’s password is: 123


All file:
MainProject1.c MainProject1.h
CreateAccount.c 
password.txt
cal2.html
find1.h  find1.cpp
addgroupmeet.cpp addgroupmeet.h
screenVideoRecorder


Note:
Input format:
startdate/enddate: June,3,2014
starttime/endtime: 10:00am or 10:00pm


CreateAccount.c:
1 create an account, add the user=md5password=email to the password.txt file;
2 also create an directory for each new user

need to modify your path
char pathdir[100]="/Library/WebServer/CGI-Executables/doc";


step5,step6:
Note:
Since these functions are only allowed to admin, so only admin can see these information. When you login, please use the account: “admin”.

step6:
find1.h find1.cpp  and addgroupmeet.cpp addgroupmeet.h  
are for  Find a free spot, and add group meetings;





call: Make all

It will compile all files, and put *.exe files to your path:
I use Apache: so the path is /Library/WebServer/CGI-Executables

Also put passwords.txt and in that path; And create dir: “Doc” to put all the users subdirectories;

put cal2.html on the path:/Library/WebServer/Documents;







