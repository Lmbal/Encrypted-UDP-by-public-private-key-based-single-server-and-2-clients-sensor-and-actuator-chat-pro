#include <winsock2.h>
#include <stdio.h>


int main(int argc, char **argv)
{
	WSADATA              wsaData;
	SOCKET               SendingSocket;
	SOCKADDR_IN          ReceiverAddr, SrcInfo;
	int                  Port = 5150;
	char                 *SendBuf = "Sending data from sensor to server.";
	int                  BufLength = 1024;
	int len;
	int TotalByteSent;
	
	// Initialize Winsock version 2.2
	if( WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		printf("Client: WSAStartup failed with error %ld\n", WSAGetLastError());
		// Clean up
		WSACleanup();
		// Exit with error
		return -1;
	}
	else
		printf("Client: The Winsock DLL status is %s.\n", wsaData.szSystemStatus);
	
	// Create a new socket to receive datagrams on.
	SendingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (SendingSocket == INVALID_SOCKET)
	{
		printf("Client: Error at socket(): %ld\n", WSAGetLastError());
		// Clean up
		WSACleanup();
		// Exit with error
		return -1;
	}
	else
		printf("Client: socket() is OK!\n");

	// Set up a SOCKADDR_IN structure that will identify who we
	// will send datagrams to. For demonstration purposes, let's
	// assume our receiver's IP address is 127.0.0.1 and waiting
	// for datagrams on port 5150.
	ReceiverAddr.sin_family = AF_INET;
	ReceiverAddr.sin_port = htons(Port);
	// Change the IP accordingly...
	ReceiverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
int yes=1;
     //Let's demonstrate the hijacking and anti-hijacking options here.
     if (setsockopt(SendingSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&yes, sizeof(yes)) < 0)
	{
		int e = WSAGetLastError();
		closesocket(SendingSocket);
		return -1;
	}


	// Send a datagram to the receiver.
	printf("Client: Data to be sent: \"%s\"\n", SendBuf);
	printf("Client: Sending datagrams...\n");
	TotalByteSent = sendto(SendingSocket, SendBuf, BufLength, 0, (SOCKADDR *)&ReceiverAddr, sizeof(ReceiverAddr));

	printf("Client: sendto() looks OK!\n");
	
	// Some info on the receiver side...
	// Allocate the required resources
	memset(&SrcInfo, 0, sizeof(SrcInfo));
	len = sizeof(SrcInfo);
	
	/* getsockname(SendingSocket, (SOCKADDR *)&SrcInfo, &len);
	printf("Client: Sending IP(s) used: %s\n", inet_ntoa(SrcInfo.sin_addr));
	printf("Client: Sending port used: %d\n", htons(SrcInfo.sin_port));

	// Some info on the sender side
	getpeername(SendingSocket, (SOCKADDR *)&ReceiverAddr, (int *)sizeof(ReceiverAddr));
	printf("Client: Receiving IP used: %s\n", inet_ntoa(ReceiverAddr.sin_addr));
	printf("Client: Receiving port used: %d\n", htons(ReceiverAddr.sin_port));
	printf("Client: Total byte sent: %d\n", TotalByteSent);
 	*/

 	
	int val = 0;
	int num = 0;
	
	while (val != 99){
		printf("Enter a value: ");
    	scanf("%d", &val);  
		SendBuf = "value=1 ";
		num = val;
		switch (num) {
            case 1: SendBuf = "value=1 "; break;
			case 2: SendBuf = "value=2 "; break;
			case 3: SendBuf = "value=3 "; break;
			case 4: SendBuf = "value=4 "; break;
			case 5: SendBuf = "value=5 "; break;
			case 6: SendBuf = "value=6 "; break;
			case 7: SendBuf = "value=7 "; break;
			case 8: SendBuf = "value=8 "; break;
			case 9: SendBuf = "value=9 "; break;
			case 10: SendBuf = "value=10 "; break;
			default:
				SendBuf = "value > 10 ";
        }
		
		TotalByteSent = sendto(SendingSocket, SendBuf, BufLength, 0, (SOCKADDR *)&ReceiverAddr, sizeof(ReceiverAddr));

		getpeername(SendingSocket, (SOCKADDR *)&ReceiverAddr, (int *)sizeof(ReceiverAddr));
	
	}
    
	// When your application is finished receiving datagrams close the socket.
	printf("Client: Finished sending. Closing the sending socket...\n");
	if (closesocket(SendingSocket) != 0)
		printf("Client: closesocket() failed! Error code: %ld\n", WSAGetLastError());
	else
		printf("Client: closesocket() is OK\n");
		
	// When your application is finished call WSACleanup.
	printf("Client: Cleaning up...\n");
	if(WSACleanup() != 0)
		printf("Client: WSACleanup() failed! Error code: %ld\n", WSAGetLastError());
	else
		printf("Client: WSACleanup() is OK\n");

	// Back to the system
	return 0;


}

