#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <hashlibpp.h>
#include <stdio.h>

#define pkt_length 1024
#define port 8089
#define source_ip "192.168.1.34"
#define dest_ip "192.168.1.40"

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
	
  //Initialize md5	
  hashwrapper *h = new md5wrapper();			//Initialize md5wrapper
	
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
      
      char buf[pkt_length];
      char file_name[16];
      
	  //Your File
      cout << "Enter Your File name : ";
      cin >> file_name;             			//enter file name
  	  FILE* file = fopen (file_name , "rb" );	//File you want to send (rb = read binary)
  	  
  	  //Find size of file
      fseek(file, 0, SEEK_END);					//point to end of file position
      int file_size = ftell(file);				//get file size from fseek
      fseek(file, 0, SEEK_SET);					//set postion to beginning
      
      //Send File name Before send
      sendto(s, file_name, find_size(file_name), 0, (sockaddr *)&dest, sizeof(dest) );
      
      //Send md5
      string md5 = h->getHashFromFile(file_name);		//Checksum before send
      sendto(s, (char *)&md5, file_size, 0, (sockaddr *)&dest, sizeof(dest) );
      cout<< "md5 : " << md5 << "\n";
      
      // send the pkt
      int sizeCheck = 0;				//initialize check size variable
	  while(sizeCheck < file_size){
		fread(buf, pkt_length, sizeof(char), file);	//read file to buffer
		sendto(s, buf, pkt_length, 0, (sockaddr *)&dest, sizeof(dest) );	//send once buffer
		sizeCheck += pkt_length;						//add size check += buffer size
		Sleep(10);
		cout << " .";										//Delay
	  }
	  memset(buf,0,sizeof(buf));				//Reset Buffer
	  cout << "\n --------------------------- Send Complete ---------------------------------\n";
	  
    }else if(conn == 's'){
      char buf[1024];							//recv buffer
      char file_name[16];
	  FILE* file;						//name of file	
	  int destlen = sizeof(sockaddr);
      int n = recvfrom(s, buf, sizeof(buf), 0, (sockaddr *)&dest, &destlen);
      if(n<=16){
      	file = fopen ( file_name, "wb" );				//Recieve file name packet
      }else if(n>16 && n<=32){
		string md5 = h->getHashFromFile(file_name);		//Recieve md5 packet
	  }else{
	  	fwrite(buf, sizeof(buf)-1, sizeof(char), file);   //Write file
	  }
      memset(buf,0,sizeof(buf));						//Reset Buffer
  	}
  }
  return 0;
}
