package myserver.model;

import java.io.*;
import java.net.*;
import java.util.Date;
import java.util.Hashtable;



class TCPServer 
{
	public static Hashtable<String,String> userpwd;
	
	public static Hashtable<String,servertoclientthread> online=new Hashtable<String,servertoclientthread>();
	public static Hashtable<String,Date> logintime=new Hashtable<String,Date>();
	
	
	public static void main(String argv[]) throws Exception
      {
	     TCPServer server=new TCPServer();
      }
   
   
   public TCPServer(){
	  userpwd =new Hashtable<String,String>();
	   try {
			
			BufferedReader br = new BufferedReader(new FileReader("/Users/wmy/Desktop/ex/user_pass.txt"));
			String line;
			
			
			while((line=br.readLine())!=null){
			//	System.out.println(line);
				
				String[] arr=line.split(" ");  //split the whole line according " ", name and password
				
				userpwd.put(arr[0],arr[1]);
				
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
		            
		            BufferedReader inFromClient =
		               new BufferedReader(new InputStreamReader(
		                  s.getInputStream()));
		            DataOutputStream outToClient =
		               new DataOutputStream(
		                  s.getOutputStream());
		          
		           int i=0; 
		        while(true){
		        	System.out.println("i:"+i);
		        	outToClient.writeBytes("Username:"+'\n');
		            username=inFromClient.readLine();
		        
		            System.out.println("username:"+username);
		            
		            outToClient.writeBytes("Password:"+'\n');
		            password=inFromClient.readLine();
		           
		            System.out.println("password:"+password);
		          
		            
		            
		      
		            
		            if(userpwd.containsKey(username) && userpwd.get(username).equals(password)){
		           	 System.out.println("Succesfully login");
		             outToClient.writeBytes("success"+'\n');
		             servertoclientthread stoc=new servertoclientthread(s,username);
		             stoc.start();
		            // long logtime=System.currentTimeMillis();
		             
		            // System.out.println("logintime:"+logtime);
		             java.util.Date date=new java.util.Date();
		             logintime.put(username,date);
		             System.out.println("date:"+date.getTime());
		             online.put(username,stoc);
		           //  outToClient.writeBytes("command:"+'\n');
		           	 break;
		            }else if(i<3){
		            	System.out.println("fail");
		            	outToClient.writeBytes("fail"+'\n');
		            	i++;
		            }else{ 
		        	   System.out.println("you are blocked for 30 miniutes");
		        	   outToClient.writeBytes("block"+'\n');
		        	   i=0;
		        	
		        	   
		        	   
		        	 
		           }
		        }
		        	 
		            
		             
		          
		           
		         }
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
         
   
      }
}
