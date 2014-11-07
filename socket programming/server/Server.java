package myserver.model;

import java.io.*;
import java.net.*;
import java.util.Date;
import java.util.Hashtable;
import java.util.LinkedList;



class Server 
{
	public static Hashtable<String,String> userpwd;
	
	public static Hashtable<String,servertoclientthread> online=new Hashtable<String,servertoclientthread>();
	public static Hashtable<String,Date> logintime=new Hashtable<String,Date>();
	public static Hashtable<String,LinkedList<String>> outlinemessage=new Hashtable<String,LinkedList<String>>();
	
	public static void main(String argv[]) throws Exception
      {
	     Server server=new Server();
      }
   
   
   public Server(){
	  userpwd =new Hashtable<String,String>();
	   try {
			
			BufferedReader br = new BufferedReader(new FileReader("/Users/wmy/Desktop/ex/user_pass.txt"));
			String line;
			
			
			while((line=br.readLine())!=null){
			//	System.out.println(line);
				
				String[] arr=line.split(" ");  //split the whole line according " ", name and password
				
				userpwd.put(arr[0],arr[1]);
				
				LinkedList<String> messagelist=new LinkedList<String>();
				outlinemessage.put(arr[0], messagelist);
				
			}
			
		//	System.out.print(userpwd);	
				
				
				
				br.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
	   
	   
	   
         String clientSentence;
         String capitalizedSentence;
         String username;
         String password;
         
         ServerSocket ss;
		try {
			ss = new ServerSocket(7777);
			System.out.println("listening at port 7777");
		      while(true) 
		         {
		            Socket s = ss.accept();
		            
		            if(s!=null){
		            	 serverloginthread slogthread=new serverloginthread(s);
				            slogthread.start();
		            }
		           
		            
		             
		          
		           
		         }
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
         
   
      }
}
