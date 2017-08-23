#include <iostream>
#include <winsock2.h>

#define pkt_length 32
#define port 8089
#define source_ip "192.168.1.34"
#define dest_ip "192.168.1.38"

using namespace std;

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
      char pkt[pkt_length];
      memset(pkt,0,sizeof(pkt));
      cout << "Enter Your Message : ";
      cin >> pkt;             //keyboard input
  	
      // send the pkt
      int ret = sendto( s, pkt, find_size(pkt), 0, (sockaddr *)&dest, sizeof(dest) );
	  
    }else if(conn == 's'){
      char buf[1024];
      int n;
	  int destlen = sizeof(sockaddr);
      n = recvfrom(s, buf, 1024, 0, (sockaddr *)&dest, &destlen);
      //cout << n;
      if(n>0){
        cout << "Received a data : ";
		cout << buf;
	    cout << "\r\n";
	    memset(buf,0,sizeof(buf));
	  }
    }
  }
  return 0;
}
