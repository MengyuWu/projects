package myclient.model;

import java.io.*;
import java.net.*;
import java.util.Hashtable;
import java.util.Date;


class TCPClient 
{
	public static Hashtable<String,clientreadthread> clientreadht=new Hashtable<String,clientreadthread>();
	public static Hashtable<String,clientwritethread> clientwriteht=new Hashtable<String,clientwritethread>();
	
	static int block_time=10000;
 public static void main(String argv[]) throws Exception
 {
	 TCPClient client=new TCPClient();
 }
 
 public TCPClient(){
	 
  String username;
  String password;
  BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
  Socket s;
try {
	s = new Socket("localhost", 7777);
	
	
	 while(true){
		//  System.out.println("here:");
		  DataOutputStream outToServer = new DataOutputStream(s.getOutputStream());
	   
		  BufferedReader inFromServer = new BufferedReader(new InputStreamReader(s.getInputStream()));
			
		  System.out.println("FROM SERVER: " + inFromServer.readLine().trim());	  
		   username = inFromUser.readLine();
		  outToServer.writeBytes(username + '\n');
				
		  
		  System.out.println("FROM SERVER: " + inFromServer.readLine().trim());	 
		  password = inFromUser.readLine();
		  outToServer.writeBytes(password + '\n');	
		  
		 
		  //System.out.println(inFromServer.readLine());
		  String result=inFromServer.readLine();
		  result.trim();
		
		 if(result.equals("success")){
			 System.out.println("add a new client to sever thread");
			 clientreadthread crt=new clientreadthread(s,username);
			 crt.start();
			 clientwritethread cwt=new clientwritethread(s,username);
			 cwt.start();
			 clientreadht.put(username, crt);
			 clientwriteht.put(username, cwt);
			 break;
		 }else if (result.equals("fail")){
			 System.out.println("try again");
		 }else if(result.equals("block")){
			 try {
				Thread.sleep(block_time);
				System.out.println("go on");
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		 }
		  
	  }
	
} catch (UnknownHostException e) {
	// TODO Auto-generated catch block
	e.printStackTrace();
} catch (IOException e) {
	// TODO Auto-generated catch block
	e.printStackTrace();
}
 
 
  

  
  
  

 }
}