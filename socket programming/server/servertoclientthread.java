package myserver.model;
import java.net.*;
import java.io.*;
import java.util.*;



public class servertoclientthread extends Thread{
   
	static long Last_hour=20000; //10s
	private Socket s;
	private String username;
	public static int Time_out=20000;
	public Socket getS() {
		return s;
	}

	public void setS(Socket s) {
		this.s = s;
	}

	public servertoclientthread(Socket s,String username){
		this.s=s;
		this.username=username;
		
		
	}
	
	
	
	public void run(){
		while(!s.isClosed()){
			 try {
				//set before hand, in other case must wait for fisrt info
				 s.setSoTimeout(Time_out);
				
				 String toclient="  ";
				String info=null;
				BufferedReader inFromclient = new BufferedReader(new InputStreamReader(s.getInputStream()));
				info=inFromclient .readLine();
				if(info!=null){
					
				
					
					System.out.println("from client:"+s.getPort()+" info:"+info);
					String[] strarr=info.split(" ");
					if(strarr[0].equals("whoelse")){
					  Set<String> onlineuser=Server.online.keySet();
					  
						
						Iterator<String> itr=onlineuser.iterator();
						while(itr.hasNext()){
						  String user=itr.next();
						  if(user.equals(this.username)){
							  continue;
						  }else{
							  toclient=toclient+user+" ";
						  }
						}
					  
				
					System.out.println("online users:"+toclient); 
					DataOutputStream outToclient = new DataOutputStream(s.getOutputStream());
					outToclient.writeBytes(toclient+'\n');
					System.out.println("server message sent");
					
					
					}else if(strarr[0].equals("broadcast")){
						//note message could include space
						toclient="";
						for(int i=1;i<strarr.length; i++){
							toclient=toclient+strarr[i]+" ";
						}
						System.out.println("from "+this.username+" broadcast "+"message is:"+toclient);
						toclient="from "+this.username+" : "+toclient;
					
						
						Set<String> online=Server.online.keySet();
						Iterator<String> itr=online.iterator();
						while(itr.hasNext()){
						  Socket onlines=Server.online.get(itr.next()).getS();
						  if(!onlines.equals(s)){
							  DataOutputStream dos = new DataOutputStream(onlines.getOutputStream());
								dos.writeBytes(toclient+'\n');
						  }
						  
						}
						 DataOutputStream outToclient = new DataOutputStream(s.getOutputStream());
							outToclient.writeBytes("broadcast message has been sent"+'\n');
					}else if(strarr[0].equals("message")){
						String user=strarr[1];
						//get the whole message
						for(int i=2;i<strarr.length; i++){
							toclient=toclient+strarr[i]+" ";
						}
						
						if(Server.online.containsKey(user)){
							
							DataOutputStream dos= new DataOutputStream(Server.online.get(user).getS().getOutputStream());
							dos.writeBytes("message from: "+this.username+": "+toclient+'\n');
							DataOutputStream outToclient = new DataOutputStream(s.getOutputStream());
							outToclient.writeBytes("   message has been sent"+'\n');
							
						}else{
							DataOutputStream outToclient = new DataOutputStream(s.getOutputStream());
							if(Server.userpwd.containsKey(user)){
								outToclient.writeBytes(" user doesn't online !"+'\n');
								
								//put the message at that user's outlinemessage ht;
								toclient=" from "+this.username+":"+toclient;
								Server.outlinemessage.get(user).add(toclient);
							}else{
								outToclient.writeBytes("This user doesn't exist !"+'\n');
							}
							
							
						}
						
						
						
					}else if(strarr[0].equals("logout")){
						DataOutputStream outToclient = new DataOutputStream(s.getOutputStream());
						outToclient.writeBytes("logout"+'\n');
						Server.online.get(username).interrupted();
					     Server.online.remove(this.username);
					   Server.logintime.remove(this.username);
						//s.close();
						break;
					}else if(strarr[0].equals("wholasthr")){
						long now=System.currentTimeMillis();
						String lasthrlist="   ";
						Iterator itr=Server.logintime.keySet().iterator();
						while(itr.hasNext()){
							String user=(String) itr.next();
							long logtime=Server.logintime.get(user).getTime();
						
							
							if((now-logtime)>=Last_hour){
							  // System.out.println(" longer than last_hour"+Last_hour);
								lasthrlist=lasthrlist+user+" ";
							}
						}
						
						DataOutputStream outToclient = new DataOutputStream(s.getOutputStream());
						outToclient.writeBytes("  lasthrlist: "+lasthrlist+'\n');
						
					}
					else{
						System.out.println("text message: "+info);
						DataOutputStream outToclient = new DataOutputStream(s.getOutputStream());
						outToclient.writeBytes("text message received"+'\n');
					}
					
					
					
					
					
				}
			
				
				
				
				
				
				
				
			}
  	     catch(SocketTimeoutException e2){
		
		 System.out.println(this.username+" timeout");
			Server.logintime.remove(this.username);
			Server.online.remove(this.username);
			
	
			
				try {
					this.s.close();
					break;
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
				
			}   catch(java.net.SocketException e){
				 System.out.println("log out");
				 
				 break;
				 
			 }
			 catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

}
