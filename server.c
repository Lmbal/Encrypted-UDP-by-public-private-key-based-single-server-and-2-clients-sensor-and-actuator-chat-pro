 
#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<math.h>


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

char* encrypt(char* myMsg,int key)
{
    int i;
    char* tData;
    for(i=0;i<strlen(myMsg);++i)
    {
        tData[i] = myMsg[i] - key;
    }

    return tData;
}

char* decrypt(char* myMsg,int key)
{
    int i;
    char* tData;
    for(i=0;i<strlen(myMsg);++i)
    {
        tData[i] = myMsg[i] + key;
    }
    return tData;
}

//==========================================

int recvfromTimeOutUDP(SOCKET socket, long sec, long usec)

{
    struct timeval timeout;
    struct fd_set fds;
    timeout.tv_sec = sec;
    timeout.tv_usec = usec;
    FD_ZERO(&fds);
    FD_SET(socket, &fds);
    // Return value:
    // -1: error occurred
    // 0: timed out
    // > 0: data ready to be read
    return select(0, &fds, 0, 0, &timeout);
}

int main(int argc, char **argv)
{
     // Connect with client1 to receive data
     WSADATA            wsaData;
     SOCKET             ReceivingSocket;
     SOCKADDR_IN        ReceiverAddr;
     int                Port = 5150;
     char               ReceiveBuf[1024];
     int                BufLength = 1024;
     SOCKADDR_IN        SenderAddr;
     int                SenderAddrSize = sizeof(SenderAddr);
     int                ByteReceived = 5, SelectTiming, ErrorCode;
     char ch = 'Y';
     // Connect with actuator to send data
     WSADATA              wsaData2;
	SOCKET               SendingSocket2;
	SOCKADDR_IN          ReceiverAddr2, SrcInfo;
	int                  Actuator_Port = 6160;
	char                 *SendBuf = "Receive data from server.";
	int                  BufLength2 = 1024;
	int len;
	int TotalByteSent;
    
    //Use encrypt, decrypt 
    char                myMsg[20] = "value = 1";
    int                 key = 0xFACA;     
    char*               msg0;
    char*               textData;

    /* msg0 = encrypt(myMsg,key);
    printf("Encrypted value = %s\n",msg0);
    decrypt(msg0,key);
    printf("Decrypted value = %s\n",msg0); */
    //=======================================


   // Initialize Winsock version 2.2
   if( WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
   {
        printf("Server: WSAStartup failed with error %ld\n", WSAGetLastError());
        return -1;
   }
   else
          printf("Server: The Winsock DLL status is %s.\n", wsaData.szSystemStatus);
     // Create a new socket to receive datagrams on.
     ReceivingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
     if (ReceivingSocket == INVALID_SOCKET)
     {
          printf("Server: Error at socket(): %ld\n", WSAGetLastError());
          // Clean up
          WSACleanup();
          // Exit with error
          return -1;
     }
     else
          printf("Server: socket() is OK!\n");
     // Set up a SOCKADDR_IN structure that will tell bind that we
     // want to receive datagrams from all interfaces using port 5150.
     // The IPv4 family
     ReceiverAddr.sin_family = AF_INET;
     // Port no. 5150
     ReceiverAddr.sin_port = htons(Port);
     // From all interface (0.0.0.0)
     ReceiverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
   // Associate the address information with the socket using bind.
   // At this point you can receive datagrams on your bound socket.
   if (bind(ReceivingSocket, (SOCKADDR *)&ReceiverAddr, sizeof(ReceiverAddr)) == SOCKET_ERROR)
   {
        printf("Server: bind() failed! Error: %ld.\n", WSAGetLastError());
        // Close the socket
        closesocket(ReceivingSocket);
        // Do the clean up
        WSACleanup();
        // and exit with error
        return -1;
     }
     else
          printf("Server: bind() is OK!\n");

   // Some info on the receiver side...
   getsockname(ReceivingSocket, (SOCKADDR *)&ReceiverAddr, (int *)sizeof(ReceiverAddr));

   printf("Server: Receiving IP(s) used: %s\n", inet_ntoa(ReceiverAddr.sin_addr));
   printf("Server: Receiving port used: %d\n", htons(ReceiverAddr.sin_port));
   printf("Server: I\'m ready to receive a datagram...\n");



     // For send data
     if( WSAStartup(MAKEWORD(2,2), &wsaData2) != 0)
	{
		//printf("Client: WSAStartup failed with error %ld\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}
	
	// Create a new socket to receive datagrams on.
	SendingSocket2 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (SendingSocket2 == INVALID_SOCKET)
	{
		//printf("Client: Error at socket(): %ld\n", WSAGetLastError());
		// Clean up
		WSACleanup();
		// Exit with error
		return -1;
	}
	ReceiverAddr2.sin_family = AF_INET;
	ReceiverAddr2.sin_port = htons(Actuator_Port);
	// Change the IP accordingly...
	ReceiverAddr2.sin_addr.s_addr = inet_addr("127.0.0.1");



//====================================================

   SelectTiming = recvfromTimeOutUDP(ReceivingSocket, 10, 0);
   switch (SelectTiming)
        {
             case 0:
                 // Timed out, do whatever you want to handle this situation
                 printf("Server: Timeout lor while waiting you bastard client!...\n");
                 break;
             case -1:
                 // Error occurred, maybe we should display an error message?
                // Need more tweaking here and the recvfromTimeOutUDP()...
                 printf("Server: Some error encountered with code number: %ld\n", WSAGetLastError());
                 break;
             default:
                 {
                      while (1)
                      {
                           // Call recvfrom() to get it then display the received data...
                           ByteReceived = recvfrom(ReceivingSocket, ReceiveBuf, BufLength,0, (SOCKADDR *)&SenderAddr, &SenderAddrSize);
                           textData = ReceiveBuf;
                           free(textData);
                           
                           //decrypt(ReceiveBuf,key);
                           if ( ByteReceived > 0 )
                           {
                               msg0 = decrypt(textData, key);
                               
                               //printf("Server: Total Bytes received: %d\n", ByteReceived);
                               printf("Server: Receive data is: \%s\n", ReceiveBuf);
                               if(strcmp(ReceiveBuf, "value=7 ") == 0){
                                   printf("=====================================================\n"); 
                                   printf("    Send data to the actuator:: \%s\n", ReceiveBuf);
                                   printf("=====================================================\n"); 
                              
                                   TotalByteSent = sendto(SendingSocket2, ReceiveBuf, BufLength2, 0, (SOCKADDR *)&ReceiverAddr2, sizeof(ReceiverAddr2));

                               }                            
                           }

                           else if ( ByteReceived <= 0 )
                                printf("Server: Connection closed with error code: %ld\n",WSAGetLastError());
                           else
                                printf("Server: recvfrom() failed with error code: %d\n",WSAGetLastError());
                           // Some info on the sender side                         

                           getpeername(ReceivingSocket, (SOCKADDR *)&SenderAddr, &SenderAddrSize);
                           /* printf("Server: Sending IP used: %s\n", inet_ntoa(SenderAddr.sin_addr));
                           printf("Server: Sending port used: %d\n", htons(SenderAddr.sin_port)); */
                      }
                 }
   }
 
   // When your application is finished receiving datagrams close the socket.
   printf("Server: Finished receiving. Closing the listening socket...\n");
   if (closesocket(ReceivingSocket) != 0)
        printf("Server: closesocket() failed! Error code: %ld\n", WSAGetLastError());
   else
        printf("Server: closesocket() is OK...\n");
   // When your application is finished call WSACleanup.
   printf("Server: Cleaning up...\n");
   if(WSACleanup() != 0)
        printf("Server: WSACleanup() failed! Error code: %ld\n", WSAGetLastError());
   else
        printf("Server: WSACleanup() is OK\n");
   // Back to the system
   return 0;

}