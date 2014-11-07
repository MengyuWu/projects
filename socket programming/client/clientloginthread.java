package myclient.model;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;

public class clientloginthread extends Thread {
	
	private Socket s;
	static int block_time=10000;
	public clientloginthread(Socket s){
		this.s=s;
	}
	
	
	public void run(){
		while(!s.isClosed()){
			try {
				String username;
				String password;
				String fromserver;
				String result;
				DataOutputStream dos = new DataOutputStream(s.getOutputStream());
				BufferedReader br=new BufferedReader(new InputStreamReader(s.getInputStream()));
				BufferedReader brkey=new BufferedReader(new InputStreamReader(System.in));
				
				fromserver=br.readLine();
				System.out.println(fromserver);
				
				username=brkey.readLine();
				dos.writeBytes(username+'\n');   //important '\n'
				
				
				
				fromserver=br.readLine();
				System.out.println(fromserver);
				
				password=brkey.readLine();
				dos.writeBytes(password+'\n');
				
				
				
				result=br.readLine();
				System.out.println(result);

				
				
				 if(result.equals("success")){
					 System.out.println("add a new client to sever thread");
					 clientreadthread crt=new clientreadthread(s,username);
					 crt.start();
					
					 clientwritethread cwt=new clientwritethread(s,username);
					 cwt.start();
				
					 Client.clientreadht.put(username, crt);
					 Client.clientwriteht.put(username, cwt);
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
				
				
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
	}
	
}
