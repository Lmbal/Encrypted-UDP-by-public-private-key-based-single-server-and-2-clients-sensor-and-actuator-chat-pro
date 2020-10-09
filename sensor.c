#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//==========================================

// Secure

char* encryption(char* s) 
{ 
    
    int l = strlen(s); // s.length(); 
    int b = ceil(sqrt(l)); 
    int a = floor(sqrt(l)); 
    
    char* encrypted; 
    if (b * a < l) { 
        if (min(b, a) == b) { b = b + 1; } 
        else { a = a + 1; } 
    } 
  
    // Matrix to generate the  
    // Encrypted String 
    char arr[a][b]; 
    memset(arr, ' ', sizeof(arr)); 
    int k = 0; 
      
    // Fill the matrix row-wise 
    for (int j = 0; j < a; j++) { 
        for (int i = 0; i < b; i++) { 
             if (k < l){ arr[j][i] = s[k]; } 
            k++; 
        } 
    } 
  
    // Loop to generate  
    // encrypted string 
    for (int j = 0; j < b; j++) { 
        for (int i = 0; i < a; i++) { 
            encrypted = encrypted +  
                         arr[i][j]; 
        } 
    } 
    
    return encrypted; 
} 
  
// Function to decrypt the string 
char* decryption(char s[]){ 
    int l = strlen(s); 
    int b = ceil(sqrt(l)); 
    int a = floor(sqrt(l)); 
    char* decrypted; 
    char s0;

    printf("s %s\n", s);
    s0 =s[1];
    printf("s[1] %s\n", s[1]);

    printf("l = %ld\n", l);
    printf("a = %ld\n", a);
    printf("b = %ld\n", b);

    // Matrix to generate the  
    // Encrypted String 
    char arr[a][b]; 
    memset(arr, ' ', sizeof(arr)); 
    int k = 0; 
      
    // Fill the matrix column-wise 
    for (int j = 0; j < b; j++) { 
        for (int i = 0; i < a; i++) { 
            if (k < l){ 
                arr[j][i] = s[k]; 
            } 
            k++; 
        } 
    } 
  
    // Loop to generate  
    // decrypted string 
    for (int j = 0; j < a; j++) { 
        for (int i = 0; i < b; i++) { 
            printf("i = %ld\n", i);
            printf("j = %ld\n", j);
            printf("Code %s\n", arr[i][j]);
            /* decrypted = decrypted +  
                         arr[i][j];  */
        } 
    } 
    decrypted = "1234";
    return decrypted; 
} 
 
//==========================================

// Use encrypt, decrypt to be more Secure
char* encrypt(char myMsg[],int key)
{
    unsigned int i;
    for(i=0;i<strlen(myMsg);++i)
    {
        myMsg[i] = myMsg[i] - key;
    }

    return myMsg;
}

char* decrypt(char myMsg[],int key)
{
    unsigned int i;
    for(i=0;i<strlen(myMsg);++i)
    {
        myMsg[i] = myMsg[i] + key;
    }
    return myMsg;
}



int main(int argc, char **argv)
{
	WSADATA              wsaData;
	SOCKET               SendingSocket;
	SOCKADDR_IN          ReceiverAddr, SrcInfo;
	int                  Port = 5150;
	char				 *SendBuf = "Sending data from sensor to server.";
	int                  BufLength = 1024;
	int len;
	int TotalByteSent;
	int key = 0xFACA;
	char sendMsg[20];
	char* msg0;

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
	
	// Send a datagram to the receiver.
	printf("Client: Data to be sent: \"%s\"\n", SendBuf);
	printf("Client: Sending datagrams...\n");

	msg0 = encrypt(sendMsg,key);
	SendBuf = msg0;
	//free(SendBuf);
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
		strcpy(sendMsg, SendBuf);
		//free(sendMsg);	// deallocate memory once you've done
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
		
		strcpy(sendMsg, SendBuf);
		//free(sendMsg);	// deallocate memory once you've done

		msg0 = encrypt(sendMsg,key);
		//strcpy(sendMsg, msg0);
		printf("The value = %s\n",msg0);
		
		TotalByteSent = sendto(SendingSocket, SendBuf, BufLength, 0, (SOCKADDR *)&ReceiverAddr, sizeof(ReceiverAddr));
		//TotalByteSent = sendto(SendingSocket, msg0, BufLength, 0, (SOCKADDR *)&ReceiverAddr, sizeof(ReceiverAddr));

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

