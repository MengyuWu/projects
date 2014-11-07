package myclient.model;
import java.net.*;
import java.io.*;
import java.util.*;




public class clientwritethread extends Thread{
	public static int Time_out=20000;
	private Socket s;
	public Socket getS() {
		return s;
	}

	public void setS(Socket s) {
		this.s = s;
	}

	public String username;
	public clientwritethread(Socket s,String username){
		this.s=s;
		this.username=username;
	}
	
	public void run(){
		while(!s.isClosed()){
			 try {
				//define to time out ,one in write thread one in server
		        //no sense to set write timeout
			  //	  before input, otherwise wait for input, they will not set timeout
				
				 s.setSoTimeout(Time_out);	
				 
				System.out.println("command:");
				if(s.isClosed()){
					System.out.println("disconnected to server,logout");
					break;
				}
				DataOutputStream outToServer = new DataOutputStream(s.getOutputStream());
				
				//PrintWriter outToServer=new PrintWriter(s.getOutputStream(),true);
			
				BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
				String toserver="";
				try {
					Thread.sleep(500);
					toserver=br.readLine();
				} catch (InterruptedException e) {
					System.out.println("interrupted log out");
					break;
					
				}
                
				
		
				
				
				
				if(s.isClosed()){
					System.out.println("disconnected to server,logout");
					break;
				}
				
				outToServer.writeBytes(toserver+'\n');
				
				
				if(toserver.trim().equals("logout")){
					
					
				//  Client.clientreadht.get(this.username).interrupt();
				  Client.clientwriteht.get(this.username).interrupt();
				//  Client.clientreadht.remove(this.username);
				  Client.clientwriteht.remove(this.username);
				   s.close();
				   break;
				}
				
				
		
				
				
				
				
				
			
				
			}
			 catch(SocketTimeoutException e2){
				
				 System.out.println(this.username+" at writerthread timeout");
				
				 
				  Client.clientwriteht.remove(this.username);
				 // Client.clientwriteht.remove(this.username);
				 if(!s.isClosed()){
					 try {
						s.close();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				 }
				 
				   break;
					
			
					
						
						
						
					} 
			 catch(java.net.SocketException e){
				 //socket close
				 System.out.println("log out-socekt close");
				 System.exit(1);
				 break;
				 
			 }
			 
			 catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

}
