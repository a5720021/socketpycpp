#include <iostream>
#include <winsock2.h>
#include <stdio.h>

#define pkt_length 1024
#define port 8089
#define source_ip "192.168.1.34"
#define dest_ip "192.168.1.36"

using namespace std;

//find array
int find_size(char* str){
	int i = 0;
	while(i < pkt_length){
		if(str[i] == 0x00){
			break;
		}else{
			i++;
		}
	}
	return i;
}

int main() {
	
  //Initialize Socket data
  sockaddr_in dest,local;
  WSAData data;
  WSAStartup( MAKEWORD( 2, 2 ), &data );     //select wsa version 2.2

  //Assign source & destination information
  local.sin_family = AF_INET;      //ipv4
  local.sin_addr.s_addr = inet_addr(source_ip);
  local.sin_port = htons(port);           // choose any

  dest.sin_family = AF_INET;       //ipv4
  dest.sin_addr.s_addr = inet_addr(dest_ip);
  dest.sin_port = htons(port);
  
  // create the socket
  SOCKET s = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
  
  // bind to the local address
  bind( s, (sockaddr *)&local, sizeof(local) );
  
  //Choose connection type
  char conn;
  cout << "Please Choose connection >> Client or Server? (c/s)\r\n";
  cin >> conn;
  
  while(1)
  {
    if(conn == 'c'){
      
	  //Your Message
      char buf[pkt_length];
      char file_name[16];
      cout << "Enter Your File name : ";
      cin >> file_name;             //keyboard input
  	  FILE* file = fopen (file_name , "rb" );	//File you want to send (rb = read binary)
      fseek(file, 0, SEEK_END);					//point to end of file position
      int file_size = ftell(file);				//get file size from fseek
      fseek(file, 0, SEEK_SET);					//set postion to beginning
      fread(buf, file_size, sizeof(char), file);	//read file to buffer
      
      // send the pkt
      int ret = sendto( s, (char*)buf, find_size(buf), 0, (sockaddr *)&dest, sizeof(dest) );
	  memset(buf,0,sizeof(buf));				//Reset Buffer
	  
    }else if(conn == 's'){
      char buf[1024];
      FILE* file = fopen ( "recv" , "wb" );
	  int destlen = sizeof(sockaddr);
      int n = recvfrom(s, buf, sizeof(buf), 0, (sockaddr *)&dest, &destlen);
      if(n>0){
        cout << "Received a data : " << buf << "\r\n";	//debug
      }
      fwrite(buf, sizeof(buf)-1, sizeof(char), file);   //Write file
      memset(buf,0,sizeof(buf));						//Reset Buffer
  	}
  }
  return 0;
}
