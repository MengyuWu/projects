package myclient.model;

import java.io.*;
import java.net.*;
import java.util.Hashtable;
import java.util.Date;


class Client 
{
	public static Hashtable<String,clientreadthread> clientreadht=new Hashtable<String,clientreadthread>();
	public static Hashtable<String,clientwritethread> clientwriteht=new Hashtable<String,clientwritethread>();
	
	static int block_time=10000;
 public static void main(String argv[]) throws Exception
 {
	 Client client=new Client();
 }
 
 public Client(){
	 
  String username;
  String password;
  BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
  Socket s;
try {
	s = new Socket("localhost", 7777);
	
	clientloginthread cloginthread=new clientloginthread(s);
	cloginthread.start();
		  

	 
	
} catch (UnknownHostException e) {
	// TODO Auto-generated catch block
	e.printStackTrace();
} catch (IOException e) {
	// TODO Auto-generated catch block
	e.printStackTrace();
}
 
 
  

  
  
  

 }
}