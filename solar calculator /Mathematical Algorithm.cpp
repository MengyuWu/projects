#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h> 

#define PI 3.1416 
#define DP_Move 0.256806

#define Watt_Per_10_Minutes 1
        
        
double Location_Latitude,Location_Longtitude;   /*Global Variables Coordinate*/ 
double Direct_Point;                            /*Global Variables of which latitude the sun irradiate */ 
double Elevation_Angle,Azimuth;                 /*Global Variables of Elevation Angle and Azimuth */ 
int Time_Zone;                                  /*Global Variables Time_zone*/ 
int Year,Month,Date,Hour,Minute,Second;         /*Global Variables Y-M-D h-m-s*/ 
double Hour_Angle; 
//----------------------------------------------------------------------
double Surface_Data[3][3];
double Surface_Para[4];
double Fringe[100][2];
double Direction[3]; 
double Projection_Point[10000][3];
double threeD_Shadow_Coordinate[10000][3];
//----------------------------------------------------------------------
double Sum_Point[60000][4];   //Sum_Point[M][0] = x , Sum_Point[M][1] = y , Sum_Point[M][2] = Watts;
int Model_Count; 
int Accuracy;
int Year_Start,Year_End;
//Haven't make an Initialization , do it later;
struct Model_Data
{
 int Number;
 int Type;
 double Coordinate[3];
 double Radius;
 double Height;       
}Model[100];
/*
  Function:
           Get_Location();
           Get_Time();
           Cal_Direct_Point(); 
           Cal_Hour_Angle(); 
           Cal_Elevation_Angle();
           Cal_Azimuth();  
*/
/*
  Function:
           Read_Accuracy();
           Read_Roof();
                                   Read Roof's Coordinates.
                                   Global Varialbes to save data;
                                   Surface_Data[3][3];
           Cal_Surface_Formula();  
                                   Global Variables to save Surface_Para[4]:ax+by+cz+d=0;
                                   Calculate from Surface_data[3][3]:(x1,y1,z1),(x2,y2,z2),(x3,y3,z3);
           Cal_Direction();
                                   Use Cal_Elevation_Angle() & Cal_Azimuth() to get data.
                                   Global Variables to save Directional Derivative Direction[3]:(a,b,c);
           Cal_Projection_Point_1();
                                   Global Variables to get data about type and other parameters;
                                   Calculate setting numbers of points[Setting_Projection_Point] saved in Projection_Point[100][3]
           Cal_Projection_Point_2();
                                   Global Variables to get data about type and other parameters;
                                   Calculate setting numbers of points[Setting_Projection_Point] saved in Projection_Point[100][3]
           Read_Projection();
                                   Read projection point data from .txt
           Read_Models();
                                   Read models' data use struct Model_Data from .txt
           
           Cal_Shadow_3DP();
                                   Use Call_Projection_Point_1() & Cal_Direction() to get data;
                                   Approximation algorithm use surface formula with abs(ax+by+cz+d<0.01) step by 0.001 or so.
                                   Save the calculation in the 3D_Shadow_Coordinate[100][3];
           Cal_Shadow_2DP();
                                   Use 3D_Shadow_Coordinate[100][3] & Cal_Surface_Formula() to get x-0-y coordinates
                                   Save the calculation in the 2D_Shadow_Coordinate[100][2];
           Max();Min();            
                                   Use Bubble Sort Algorithm;
           Segmation();
                                   Segmate the roof with setting numbers of points [Setting_Segmation_Point] 
                                   Get the Feature Points and save the coordinates in Feature_Points[SSP][2];
           Judge_shadow();
                                   Judge whether the coordinates in Feature_Points[SSP][2] are in the Shadow of the trees. 
           
           main();
                      

*/
// Get location from files or screens , endow them to  [Location_Latitude,Location_Longtitude] [Time_zone] 
// Success then return 1 ,otherwise return 0; 
int Get_Location()
{

    printf("Latitude:");
    scanf("%lf",&Location_Latitude);
    printf("Longtitude:");
    scanf("%lf",&Location_Longtitude);
    if(Location_Latitude <= 90  && 
       Location_Latitude >= -90 && 
       Location_Longtitude >= -180 &&
       Location_Longtitude <= 180)
       {
        Location_Latitude = Location_Latitude / 180 * PI ;
        Location_Longtitude = Location_Longtitude / 180 * PI ;
        return 1;                    
       } 
    else 
       {
        printf("error: cannot get the proper location.\n"); 
        return 0;
       } 
}  

// Get accurate time from files or screens , endow them to  [Location_Latitude,Location_Longtitude] 
// Success then return 1 ,otherwise return 0; 
int Get_Time()
{
    printf("Year:"); 
    scanf("%d",&Year);
    printf("Month:");
    scanf("%d",&Month);
    printf("Date:");
    scanf("%d",&Date);
    printf("Hour:");
    scanf("%d",&Hour);
    printf("Minute:");
    scanf("%d",&Minute);
    printf("Second:");
    scanf("%d",&Second);
     
    if(Year >= 2000 &&
       Year <= 3000 &&
       Month >0  &&
       Month <13 &&
       Date > 1  &&
       Date < 31 && 
       Hour > 0  &&
       Hour < 24 &&
       Minute >= 0 &&
       Minute <= 60 &&
       Second >=0 &&
       Second <=60
   
       )
       {
        return 1;
       }
     else
       {
        printf("error:cannot get the proper time."); 
        return 0; 
       } 
} 


// Use Approximate Algorithm 23.45бу*4  per 365.256 days 0.256806бу per day. 
// Use 2012/12/21 20:15 as the accurate time when the sun irradiate the Tropic of Capricorn 
double Cal_Direct_Point()
{
 int day = 0,i = 0; 
 double dou_hour,dou_minute,dou_second; 
 double Gap_Days = 0,Gap_Temp_Time = 0; 
 int temp; 
 
 dou_hour = Hour;
 dou_minute = Minute;
 dou_second = Second; 
 int a[2][13] = {
                  {0,31,28,31,30,31,30,31,31,30,31,30,31},
                  {0,31,29,31,30,31,30,31,31,30,31,30,31}
                };  
 int b[2] = {365,366}; 
 int leap;
 
 leap = (Year%400==0 || (Year%4==0 && Year%100!=0));    
 day = Date;
  
 for(i=1;i<Month;i++){ 
     day+=a[leap][i];
                     } 

 Gap_Temp_Time = dou_hour/24 + dou_minute/1440 + dou_second/86400 + 0.15625;  
 for(i=2013;i<Year;i++){
     leap = (i%400==0 || (i%4==0 && i%100!=0));
     Gap_Days += b[leap];
                       }
 Gap_Days = Gap_Days + 10 + Gap_Temp_Time + day - 1 ;  
 Gap_Days = fmod(Gap_Days , 365.256);
 
 if(Gap_Days > 182.628) {Direct_Point = 23.43- (Gap_Days - 182.628)*DP_Move;}
 else{Direct_Point = -23.43 + Gap_Days*DP_Move;}
 
 Direct_Point =  Direct_Point / 180 * PI;
 return Direct_Point; 
}

// Use Approximate Algorithm
// ****************************************** IMPORTANT PLACE TO IMPROVE ALGORITHM  
// Set 12:00 as the transit time of the sun 
// ****************************************** IMPORTANT PLACE TO IMPROVE ALGORITHM 
double Cal_Hour_Angle()
{
       double Temp_Time;
       Temp_Time = Hour + Minute / 60 + Second / 3600 ;
       Temp_Time = fabs (Temp_Time - 12);
       Hour_Angle = 15 * Temp_Time;
       Hour_Angle = Hour_Angle / 180 * PI ; 
       return Hour_Angle; 
} 
// Use sin Elevation_Angle =sin Location_Latitude sin Direct_Point+cos Location_Latitudecos Direct_Point cos Hour_Angle 
// Calculate the elevation angle of the sun 
// Function need no parameters cause we have global variables. 
double Cal_Elevation_Angle()
{
      double temp_1,temp_2,temp_sum;
      
      temp_1 = sin(Location_Latitude)*sin(Direct_Point);
      temp_2 = cos(Location_Latitude)*cos(Direct_Point)*cos(Hour_Angle);
      temp_sum = temp_1 + temp_2;
      Elevation_Angle = asin(temp_sum);
      if(Elevation_Angle >= 0 && Elevation_Angle <= PI/2)
      {
       return Elevation_Angle;    
      } 
      else
      {
//     printf("the sun does not rise or something is wrong with the calculation.\n");
       Elevation_Angle = 0; 
       return Elevation_Angle ;    
      } 

} 

// Use cos Azimuth = (sin Direct_Point cos Location_Latitude - cos Hour_Angle cos Direct_Point sin Location_Latitude)/cos Evevation_Angle; 
// Calculate the azimuth of the sun 
// Function need no parameters cause we have global variables. 
double Cal_Azimuth()
{
      double temp_1,temp_2,temp_3,temp_4,temp_sum;
      int temp_sum1;
 
      temp_1 = sin(Direct_Point)*cos(Location_Latitude);
      temp_2 = cos(Hour_Angle)*cos(Direct_Point)*sin(Location_Latitude);
      temp_3 = temp_1 - temp_2;
      
      temp_4 = cos(Cal_Elevation_Angle()); 
      
      if (temp_4 == 0){return 0;} 
      else 
      {
       temp_sum1 = (temp_3 / temp_4)*1000;
       temp_sum = temp_sum1;
       temp_sum = temp_sum/1000;
       if(temp_sum >=-1 && temp_sum <=1 ) {Azimuth =  acos(temp_sum);}
       else {
             Azimuth = 0 ; 
             return Azimuth; 
            }    
      } 
      return Azimuth;       
} 
/*
int main()
{
 Location_Latitude = -34/180*PI;
 Location_Longtitude = 151/180*PI; //East - Positive ; West - Negative;
 int End_Year,End_Month;

 int a[2][13] = {
                  {0,31,28,31,30,31,30,31,31,30,31,30,31},
                  {0,31,29,31,30,31,30,31,31,30,31,30,31}
                };  
 int leap;                
 FILE *fp;
 fp=fopen("Data_Sidney_2013-2023.xls","a");
     //fprintf(fp,"Year |Month| Day |Hour|Ele_Angle|  Azi   |\n");
for(Year=2013;Year<=2023;Year++)
{
 leap = (Year%400==0 || (Year%4==0 && Year%100!=0));
 for(Month=1;Month<=12;Month++)
 {
  for(Date=1;Date<=a[leap][Month];Date++)
  {
   for(Hour=6;Hour<=18;Hour++)
   {
    Cal_Direct_Point();
    Cal_Hour_Angle();
    Cal_Elevation_Angle();
    Cal_Azimuth();         
    Elevation_Angle = Elevation_Angle*180/PI;
    Azimuth = Azimuth * 180/PI; 
    fprintf(fp,"%4d  %3d  %3d  %2d %6.3f  %6.3f\n",Year,Month,Date,Hour,Elevation_Angle,Azimuth);                 
   }
  } 
 } 
}
  printf("SUCCESSFULLY DONE!");
  fclose(fp);
  getch();
  getch();                      
}
*/
//******************************************************************************
int Read_Time()
{
    int temp_Y;
    
    FILE *fp;
    fp = fopen("Data_Time.txt","r");
    fscanf(fp,"%d",&temp_Y);
    Year_Start = temp_Y;
    fscanf(fp,"%d",&temp_Y);
    Year_End = temp_Y;
    
    fclose(fp);
    return 1;
}
//*Thinks to be improved.


int Read_Accuracy()
{
 FILE *fp;
 fp = fopen("Data_Accuracy.txt","r");
 
 fscanf(fp,"%d",&Accuracy);
 
 fclose(fp);    
 
}
int Read_Roof()
{
 double temp;
 int i,j;
 int k;
 
 FILE *fp;
 fp = fopen("Data_Roof.txt","rt");
 

 for(i=0;i<=2;i++)
 {
  for(j=0;j<=2;j++)
   {                
   fscanf(fp,"%lf",&temp);
    Surface_Data[i][j] = temp; 
    printf("(%d,%d):%.3f\n",i,j,Surface_Data[i][j]);
    getch(); 
   }
 } 
 
 fclose(fp);   
 return 1;
}

int Cal_Surface_Formula()
{
    int count,count_1,count_2,flag;
    // First , in this program , we read Surface_Data on the screen.
    double temp;
    double Surface_Vector[2][3];
    
    
    printf("(%lf ,%lf,%lf)\n",Surface_Data[0][0],Surface_Data[0][1],Surface_Data[0][2]); 
    printf("(%lf ,%lf,%lf)\n",Surface_Data[1][0],Surface_Data[1][1],Surface_Data[1][2]); 
    printf("(%lf ,%lf,%lf)\n",Surface_Data[2][0],Surface_Data[2][1],Surface_Data[2][2]); 
    
    for(count_1=0;count_1<=1;count_1++)
    {
     for(count_2=0;count_2<=2;count_2++)
     {
      Surface_Vector[count_1][count_2]=Surface_Data[count_1+1][count_2]-Surface_Data[count_1][count_2];
     }                             
    }
    
    printf("(%lf , %lf , %lf)\n",Surface_Vector[0][0],Surface_Vector[0][1],Surface_Vector[0][2]); 
    printf("(%lf , %lf , %lf)\n",Surface_Vector[1][0],Surface_Vector[1][1],Surface_Vector[1][2]); 
    
    if(Surface_Vector[0][1]*Surface_Vector[1][2]-Surface_Vector[0][2]*Surface_Vector[1][1]==0)
    {
     Surface_Para[0]=0;
     if(Surface_Vector[0][1]*Surface_Vector[1][2] != 0 )
     {
      Surface_Para[1] = 1;
      Surface_Para[2] = -Surface_Vector[0][1]/Surface_Vector[0][2];                                             
     }
     else
     {
      if(Surface_Vector[0][1] == 0 && Surface_Vector[0][2] !=0){Surface_Para[1] = 1;Surface_Para[2] = 0;}
      else if(Surface_Vector[0][1] == 0 && Surface_Vector[0][2] ==0)
      {
       if(Surface_Vector[1][1] == 0){Surface_Para[1] = 1;Surface_Para[2] = 0;}
       else if(Surface_Vector[1][2] == 0){Surface_Para[2] = 1;Surface_Para[1] = 0;}
       else{Surface_Para[1] = 1;
            Surface_Para[2] = -Surface_Vector[1][1]/Surface_Vector[1][2];}                        
      } 
      
      else if(Surface_Vector[1][2]==0 && Surface_Vector[1][1] !=0){Surface_Para[2] = 1;Surface_Para[1] = 0;}
      else if(Surface_Vector[1][2]==0 && Surface_Vector[1][1] ==0) 
      {
       if(Surface_Vector[0][1] == 0){Surface_Para[1] = 1;Surface_Para[2] = 0;}
       else if(Surface_Vector[0][2] == 0){Surface_Para[2] = 1;Surface_Para[1] = 0;}
       else{Surface_Para[1] = 1;
            Surface_Para[2] = -Surface_Vector[0][1]/Surface_Vector[0][2];}   
      }
     } 
    }
  //printf("%lf CY %lf\n",Surface_Vector[0][0]*Surface_Vector[1][1]-Surface_Vector[1][0]*Surface_Vector[0][1],Surface_Vector[0][1]*Surface_Vector[1][2]-Surface_Vector[0][2]*Surface_Vector[1][1]);
  //printf("%lf CY %lf\n",Surface_Vector[0][0]*Surface_Vector[1][2]-Surface_Vector[1][0]*Surface_Vector[0][2],Surface_Vector[0][2]*Surface_Vector[1][1]-Surface_Vector[0][1]*Surface_Vector[1][2]); 
    else 
    { 
    Surface_Para[0]=1;
    Surface_Para[2]=(Surface_Vector[0][0]*Surface_Vector[1][1]-Surface_Vector[1][0]*Surface_Vector[0][1])/(Surface_Vector[0][1]*Surface_Vector[1][2]-Surface_Vector[0][2]*Surface_Vector[1][1]);
    Surface_Para[1]=(Surface_Vector[0][0]*Surface_Vector[1][2]-Surface_Vector[1][0]*Surface_Vector[0][2])/(Surface_Vector[0][2]*Surface_Vector[1][1]-Surface_Vector[0][1]*Surface_Vector[1][2]);
    } 
    
    Surface_Para[3]=-Surface_Data[0][0]*Surface_Para[0]-Surface_Data[0][1]*Surface_Para[1]-Surface_Data[0][2]*Surface_Para[2];
    printf("%.3f X + %.3f Y + %.3f Z + %.3f = 0\n",Surface_Para[0],Surface_Para[1],Surface_Para[2],Surface_Para[3]);
    return 1;
}

int Cal_Direction()
{
 // test process
  
    int Hour = 8; 
    
    int flag = 0,flag_1=0; 
    
    if(Azimuth > PI/2){flag = -1;}
    else flag =1; 
    
    if(Location_Latitude >= Direct_Point)
    {
     if(Hour <= 12){flag_1 = -1;}
     else {flag_1 = 1;}                     
    }
    else
    {
     if(Hour >= 12){flag_1 = 1;}
     else {flag_1 = -1;}    
    } 
    
    Direction[0]=flag_1;                                      //X
    Direction[1]=flag*tan(Azimuth-PI/2);                      //Y 
    Direction[2]=-tan(Elevation_Angle)/cos(Azimuth-PI/2);     //Z 
    printf("(%.3f,%.3f,%.3f)\n",Direction[0],Direction[1],Direction[2]); 
} 


//Global Variables to get data about type and other parameters;
//Calculate setting numbers of points[Setting_Projection_Point] saved in Projection_Point[100][3]; 
//Type 1 : BALL ; Type 2 : CONE ; Type 3 :PUMP TREE ; Type 4 : Cylinder;
//Need for a Data_Resource.txt like
/*
// First row is to explain what the data means.
No. Type   Coordinate    R     h
1    1     1 2 3         4     0
2    2     1 2 3         4     5   
3    3     1 2 3         8     3
4    2     2 3 4         5     6
5    4     1 2 0         3     8
// for Type 2 & 3 & 4 ,  h means the height of the cylinder-like thing.
*/

int Read_Models()
{
 FILE *fp;
 fp=fopen("Model_data.txt","r");
 int temp,count=0;
 double temp_1,x,y,z;
 
 while( fscanf(fp,"%d",&temp) != EOF )
 {
  Model[count].Number = temp ; 
  fscanf(fp,"%d",&temp);
  Model[count].Type = temp;
  
  fscanf(fp,"%lf",&x);
  Model[count].Coordinate[0] = x;
  fscanf(fp,"%lf",&y);
  Model[count].Coordinate[1] = y;
  fscanf(fp,"%lf",&z);
  Model[count].Coordinate[2] = z;
  fscanf(fp,"%lf",&temp_1);
  Model[count].Radius = temp_1;
  fscanf(fp,"%lf",&temp_1);
  Model[count].Height = temp_1;
  count++;
 }
 printf("count:%d\n",count);
 
 Model_Count = count;
 for(temp=0;temp<count;temp++)
 {
 printf("%d %d x-%.2f y-%.2f z-%.2f R-%.2f H-%.2f\n\n\n\n",
            Model[temp].Number,Model[temp].Type,
            Model[temp].Coordinate[0],Model[temp].Coordinate[1],Model[temp].Coordinate[2],
            Model[temp].Radius,Model[temp].Height);
 }
 getch();
 getch();
 fclose(fp);
}
int Cal_Projection_Point_1()
{ 
 int i=0;
// 

        //Data : Direction[0]/Direction[1]/Direction[2] 
        //       Model[i].Coordinate[0],Model[i].Coordinate[1],Model[i].Coordinate[2]; 
        //       Radius;
        //Formula 1 : Z = Model[i].Coordinate[2];
        //Formula 2 : pow((x-Model[i].Coordinate[0]),2)+pow((y-Model[i].Coordinate[1]),2)+pow((z-Model[i].Coordinate[2]),2)-pow(Radius,2)=0;
        //Formula 3 : Direction[0](x-Model[i].Coordinate[0])+Direction[1](y-Model[i].Coordinate[1])+Direction[2](z-Model[i].Coordinate[2])=0;
        
        double X0,Y0,Z0;
        double R;
        double A,B,C;
        FILE *fp;
        
        fp = fopen("Data.txt","w");
         X0=Model[i].Coordinate[0];Y0=Model[i].Coordinate[1];Z0=Model[i].Coordinate[2];
         R=Model[i].Radius;
         A=Direction[0];B=Direction[1];C=Direction[2];
/**************************************************************       
        printf("X0 %.3f , Y0 %.3f Z0 %.3f \n R %.3f \n A %.3f B %.3f C %.3f\n",X0,Y0,Z0,R,A,B,C);
        getch();
***************************************************************/
        // For simple.  
        // WARNING************Did Not exclude special circumstances***********
        double Y_start,Y_end,Y_temp;
        double Step,M,N;
        double x,y,z;
        int count;
        double Ob_1,Ob_2;
/***************************************************************       
        Y_start = Y0-sqrt(pow(A*R,2)/(pow(A,2)+pow(B,2)));
        Y_end = Y0+sqrt(pow(A*R,2)/(pow(A,2)+pow(B,2)));
    

***************************************************************/

        Y_start = Y0 - R;
        Y_end = Y0 + R;
        Step = 2*R/Accuracy ;

        for(count=0;count<=Accuracy;count++)
        {
             Y_temp = Y_start + count * Step;
             M = pow(R,2)-pow((Y_temp - Y0),2);
             N = -B*(Y_temp - Y0);

                  if(( pow(C*N,2)-(pow(A,2)+pow(C,2))*(pow(N,2)-M*pow(A,2)) )>=0)
                  {        
                     y = Y_temp;
                     z = Z0+(C*N + sqrt( pow(C*N,2)-(pow(A,2)+pow(C,2))*(pow(N,2)-M*pow(A,2)) ))/(pow(A,2)+pow(C,2));
                     x = (N-C*(z-Z0))/A + X0 ;
         
                     Projection_Point[2*count][0] = x;
                     Projection_Point[2*count][1] = y;
                     Projection_Point[2*count][2] = z;
                     Projection_Point[2*count+1][0] = 2*X0-x;
                     Projection_Point[2*count+1][1] = 2*Y0-y;
                     Projection_Point[2*count+1][2] = 2*Z0-z;
        
                     Ob_1 = pow((x-X0),2)+pow((y-Y0),2)+pow((z-Z0),2)-pow(R,2); 
                     Ob_2 = A*(x-X0)+C*(z-Z0)-N;
                     fprintf(fp,"%d %.3f %.3f %.3f\n%d %.3f %.3f %.3f\n",2*count,Projection_Point[2*count][0],Projection_Point[2*count][1],Projection_Point[2*count][2],
                                                        2*count+1,Projection_Point[2*count+1][0],Projection_Point[2*count+1][1],Projection_Point[2*count+1][2]);  

                 }
        }
        fclose(fp);

} 

int Cal_Projection_Point_2()
{
   Read_Models();
   
   double Y_start,Y_end,X_start,X_end,Z_start,Z_end,Y_temp;
   double Step,Span,Step_X,Step_Y,Step_Z;
   double x,y,z;
   double x1,y1,x2,y2; 
   int count,flag;
   double X0,Y0,Z0,R,H;
   double A,B,C; 
   int temp; 
   int i = 1 ;
   
   FILE *fp;
   fp = fopen("Data.txt","w"); 
   
   X0=Model[i].Coordinate[0];Y0=Model[i].Coordinate[1];Z0=Model[i].Coordinate[2];
   R=Model[i].Radius;
   A=Direction[0];B=Direction[1];C=Direction[2];
   H = Model[i].Height; 
   
   Span = fabs(R*A/(pow(A,2)+pow(B,2)));
   
   Y_start = Y0 + Span;
   Y_end = Y0 - Span;
   Step = (Y_end - Y_start)/Accuracy; 
   
   for (count = 0;count <= Accuracy;count++)
   {
     Y_temp = Y_start + Step * count ;
     
     y = Y_temp;
     z = Z0;
     x = (A*X0+B*Y0-B*Y_temp)/A;
     
     Projection_Point[count][0] = x;
     Projection_Point[count][1] = y;
     Projection_Point[count][2] = z;            
   }
   printf("count:%d\n",count);
   flag = count + Accuracy; 
   if(A != 0){X_start = (A*X0+B*Y0-B*Y_start)/A;X_end = (A*X0+B*Y0-B*Y_end)/A ;}
   else {X_start = X0; X_end = X0;} 
   Z_start = Z0 ; Z_end = Z0 + H ; 
   
   Step_X = (X0 - X_start)/Accuracy;
   Step_Y = (Y0 - Y_start)/Accuracy;
   Step_Z = H/Accuracy;
   
   for(temp=0;temp < Accuracy;temp++)
   {
    
    x1 = temp*Step_X + X_start; 
    x2 = 2*X0-x1; 
    y1 = temp*Step_Y + Y_start;
    y2 = 2*Y0-y1; 
    z = temp*Step_Z + Z_start;       
    Projection_Point[count][0] = x1;
    Projection_Point[count][1] = y1;
    Projection_Point[count][2] = z;   
    count++; 
    Projection_Point[count][0] = x2;
    Projection_Point[count][1] = y2;
    Projection_Point[count][2] = z; 
    count++;
   }
   printf("count:%d\n",count); 
   for(temp = 0;temp<count;temp++)
   {
   fprintf(fp,"%d %.3f %.3f %.3f\n",temp,Projection_Point[temp][0],Projection_Point[temp][1],Projection_Point[temp][2]);         
   } 
   fclose(fp); 
   return 1; 
   
   
}

int Read_Projection()
{
  int temp;
  double x,y,z;
  int count = 0;
  
  FILE *fp;
  fp = fopen("Data.txt","r");
  while( fscanf(fp,"%d",&temp) != EOF )  
  {
   fscanf(fp,"%lf",&x);
   fscanf(fp,"%lf",&y);
   fscanf(fp,"%lf",&z);
   Projection_Point[count][0] = x;
   Projection_Point[count][1] = y;
   Projection_Point[count][2] = z;
   count++;
  }
   
  fclose(fp);  
  return 1;
}

int Cal_Shadow_3DP()
{       
 double a=Surface_Para[0],b=Surface_Para[1],c=Surface_Para[2],d=Surface_Para[3];
 double V1=Direction[0],V2=Direction[1],V3=Direction[2];
 double Temp;
 int count;
 
 FILE *fp;
 fp=fopen("Column.txt","w");
	
 for(count=0;count<=Accuracy*2+1;count++)
 {
                                     
  if( V1*a+V2*b+V3*c==0)
  { 
   return 0;
  }
       
        Temp=(-d-a*Projection_Point[count][0]-b*Projection_Point[count][1]-c*Projection_Point[count][2])/(a*V1+b*V2+c*V3);
        threeD_Shadow_Coordinate[count][0]=V1*Temp+Projection_Point[count][0];
        threeD_Shadow_Coordinate[count][1]=V2*Temp+Projection_Point[count][1];
        threeD_Shadow_Coordinate[count][2]=V3*Temp+Projection_Point[count][2];
        
       
        fprintf(fp,"%.3f %.3f %.3f\n",threeD_Shadow_Coordinate[count][0],threeD_Shadow_Coordinate[count][1],threeD_Shadow_Coordinate[count][2]); 

 }
   fclose(fp);
// WARNING ************DIDN'T TEST THE RESULT*******************

}
int Cal_Shadow_2DP(){return 1;}
int Judge_Shadow(double x , double y ,int flag){return 1;}
                            //Data - in Global Variables.  return bool variables , 0 for in shadow , 1 for out.
                            // flag 1 = use Fringe Data[100][2]. flag 2 = use threeD_Shadow_Coordinate[10000][3]


int Read_Fringe()
{
  FILE *fp;
  fp = fopen("FringeData.txt","r");
  
  int temp,count = 0;
  double x,y;
  while( fscanf(fp,"%d",&temp) != EOF )
  {
   fscanf(fp,"%lf",&x);
   fscanf(fp,"%lf",&y);
   Fringe[count][0] = x;
   Fringe[count][1] = y;
   count++;
  }
  
  fclose(fp);  
  
  return count; 
}

double Max(int flag,int count)
{
 int i;
 double temp;
 temp = Fringe[0][flag];
 for(i=0;i<count;i++)
 {
  if(temp < Fringe[count][flag]){temp = Fringe[count][flag];}                     
 }
 
 return temp;
}

double Min(int flag,int count)
{
 int i;
 double temp;
 temp = Fringe[0][flag];
 for(i=0;i<count;i++)
 {
  if(temp > Fringe[count][flag]){temp = Fringe[count][flag];}                     
 }
 
 return temp;
}

int Segmation()
{
    int temp,i,j,flag;
    double Max_X,Min_X,Max_Y,Min_Y;
    double Step_X,Step_Y;
    double X_temp,Y_temp;
    int count = 0;
    
    flag = Read_Fringe();
    Max_X = Max(0,flag);
    Min_X = Min(0,flag);

    Max_Y = Max(1,flag);
    Min_Y = Min(1,flag);
    
    Step_X = (Max_X - Min_X)/Accuracy;
    Step_Y = (Max_Y - Min_Y)/Accuracy;
    for(i = 0;i<Accuracy;i++)
    {
      for(j =0;j<Accuracy;j++)
      {
        X_temp = Min_X + i * Step_X;
        Y_temp = Min_Y + j * Step_Y;
        flag = Judge_Shadow(X_temp,Y_temp,2);
        if(flag == 1 )
        {
         Sum_Point[count][0] = X_temp;
         Sum_Point[count][1] = Y_temp;
         count ++;
        }
      }
    }
    return count;
}



int main()
{
 
 /*
  Set Accuracy(From 1-100); accuracy*5 is the segments. 
   
  From Y-M-D to Y-M-D,step by 10minutes;
  1.Got Sun-Data from database;         ****Done****
  2.Cal_Direction;                      ****Done****
  3.Read_Models;                        ****Done****            
  4.Call_Projection_Point_1;            ****Done**** 
  5.Cal_Shadow_3DP;                     ****Done****
  6.Cal_Shadow_2DP;                     
  7.Segmation;                          
  8.Judge_shadow;
   a)if not in shadow Multiplied by 1/6*Watt per hour ;
   b)sum all the watts ;
  9.Create another segment which is never been in shadow;
  10.Show the Area availiable. 
 */


 /*
 Initial Data Resource:
         Data_Accuracy.txt
         Data_RoofSurface.txt
         Data_Obstacles.txt
         Data_RoofFringe.txt
         Data_Sun.txt
         Data_Time.txt
         
 Intermediate Data Resource:
         Data_Projection.txt
         Data_3DShadow.txt
 */
 int i,j,k,l;
 int Segmation_Number; 
 double temp_x,temp_y,temp_z; 
 int flag;
 
 int a[2][13] = {
                  {0,31,28,31,30,31,30,31,31,30,31,30,31},
                  {0,31,29,31,30,31,30,31,31,30,31,30,31}
                };  
 int leap;
 
 
 Get_Location();
 Read_Accuracy(); //use Data_Accuracy 
 Read_Roof(); //use roofsurface 
 Cal_Surface_Formula(); 
 Read_Fringe();// use Data_RoofFringe 
 Segmation_Number = Segmation(); // Sum_Point[10000][3];
 Cal_Direction();//use Read_SunData();
 Read_Models();
 Read_Time();
 
                
 for(Year=Year_Start;Year<=Year_End;Year++)
 {
   leap = (Year%400==0 || (Year%4==0 && Year%100!=0));
   for(Month=1;Month<=12;Month++)
   {
     for(Date=1;Date<=a[leap][Month];Date++)
     {
       for(Hour=6;Hour<=18;Hour++)
       {
         Cal_Direct_Point();
         Cal_Hour_Angle();
         Cal_Elevation_Angle();
         Cal_Azimuth();    
         Cal_Direction();
         for(j=0;j<=Model_Count;j++)
         {
           Model[j].Type = 1;       
           Cal_Projection_Point_1();
           Read_Projection();
           Cal_Shadow_3DP();
           Cal_Shadow_2DP();              
              
           for(k=0;k<Segmation_Number;k++)
           {
             temp_x = Sum_Point[k][0]; 
             temp_y = Sum_Point[k][1];
             if(Sum_Point[k][2] == 1){Sum_Point[k][2] = Judge_Shadow(temp_x,temp_y,2);}  
           }   
         }
   
        for(l=0;l<Segmation_Number;l++)
        {
          Sum_Point[k][3] += Sum_Point[k][2] * Watt_Per_10_Minutes;
        }
      }
    }   
   }
  }
 return 1;    
} 
