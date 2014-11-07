package myclient.model;
import java.net.*;
import java.io.*;
import java.util.*;
public class clientreadthread extends Thread{
	public static int Time_out=20000;
	private Socket s;
	public String username;
	public clientreadthread(Socket s,String username){
		this.s=s;
		this.username=username;
	}
	

	public void run(){
		while(!s.isClosed()){
			 try {
				
				s.setSoTimeout(Time_out);
					
				BufferedReader inFromServer = new BufferedReader(new InputStreamReader(s.getInputStream()));
				String info=" ";
				info=inFromServer.readLine();
				if(info!=null){
					System.out.println("server:"+info);
					if(info.equals("logout")){
					
						
						  Client.clientreadht.get(this.username).interrupt();
						//  Client.clientwriteht.get(this.username).interrupt();
						  Client.clientreadht.remove(this.username);
						 // Client.clientwriteht.remove(this.username);
						   s.close();
						
						
						break;
					}
				}
				
			}catch(SocketTimeoutException e2){
				
				
				 System.out.println(this.username+"  readthread timeout");
				
				 
				Client.clientreadht.remove(this.username);
				Client.clientwriteht.get(this.username).interrupt();
				
				//stop client; important!!!!!!
				System.exit(1);
				
				
				 if(!s.isClosed()){
					 try {
						s.close();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				 }
				 
				   break;
					
			
						
					}  catch(java.net.SocketException e){
						 System.out.println("socekt closed-log out");
						 System.exit(1);
						 break;
						 
					 }catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

}
