package myserver.model;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;



public class serverloginthread extends Thread {

	
	private Socket s;
	int counter=0;
	
	public serverloginthread(Socket s){
		this.s=s;
	}
	
	public void run(){
		while(!s.isClosed()){
			
			String username=null;
			String password=null;
		
			try {
				
				
				DataOutputStream dos = new DataOutputStream(s.getOutputStream());
				BufferedReader br=new BufferedReader(new InputStreamReader(s.getInputStream()));
				dos.writeBytes("Username:"+'\n');
			   
				username=br.readLine();
				System.out.println("user:"+username);
				
				dos.writeBytes("Password:"+'\n');
			   
				
				
				password=br.readLine();
				System.out.println("pwd:"+password);
			    
	            if((!Server.online.containsKey(username))&&Server.userpwd.containsKey(username) && Server.userpwd.get(username).equals(password)){
	           	 System.out.println("Succesfully login");
	             dos.writeBytes("success"+'\n');
	             servertoclientthread stoc=new servertoclientthread(s,username);
	             stoc.start();
	             
	             
	             
	             
	            // long logtime=System.currentTimeMillis();
	             
	            // System.out.println("logintime:"+logtime);
	             java.util.Date date=new java.util.Date();
	             Server.logintime.put(username,date);
	             System.out.println("date:"+date.getTime());
	             Server.online.put(username,stoc);
	           //  outToClient.writeBytes("command:"+'\n');
	           	
	             //when one client on lien, first read outlinemessage;
	             
	             if(Server.outlinemessage.get(username)!=null && !Server.outlinemessage.get(username).isEmpty()){
	            	 DataOutputStream outToclient = new DataOutputStream(s.getOutputStream());
						outToclient.writeBytes(" outline message: "+Server.outlinemessage.get(username).toString()+'\n');
						//after send youshould clean that message
						Server.outlinemessage.get(username).clear();
	             }
	             
	             
	             
	             break;
	            }else if(Server.online.containsKey(username)){
	            	System.out.println("You have already logged in");
	            	dos.writeBytes("you have already logged in"+'\n');
	            	counter++;
	            	
	            }else if(counter<2){
	            	System.out.println("fail");
	            	dos.writeBytes("fail"+'\n');
	            	counter++;
	            }else{ 
	        	   System.out.println("you are blocked for 30 miniutes");
	        	   dos.writeBytes("block"+'\n');
	        	   counter=0;
	        	
	        	   
	        	   
	        	 
	           }
			    
			    
				
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			
			
			
			
			
		}
	}
	
}
