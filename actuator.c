#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


//======================================
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

//==========================================
// A sample of the select() return value

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
     int                Port = 6160;
     char               ReceiveBuf[1024];
     int                BufLength = 1024;
     SOCKADDR_IN        SenderAddr;
     int                SenderAddrSize = sizeof(SenderAddr);
     int                ByteReceived = 5, SelectTiming, ErrorCode;
     char ch = 'Y';
     int key = 0xFACA;
     char* msg0;

   // Initialize Winsock version 2.2
   if( WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
   {
        return -1;
   }
   else
          printf("Actuator: The Winsock DLL status is %s.\n", wsaData.szSystemStatus);
     
     ReceivingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
     if (ReceivingSocket == INVALID_SOCKET)
     {
          WSACleanup();
          return -1;
     }
          
     ReceiverAddr.sin_family = AF_INET;
     // Port no. 6160
     ReceiverAddr.sin_port = htons(Port);
     ReceiverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
   
   if (bind(ReceivingSocket, (SOCKADDR *)&ReceiverAddr, sizeof(ReceiverAddr)) == SOCKET_ERROR)
   {
        printf("Actuator: bind() failed! Error: %ld.\n", WSAGetLastError());
        closesocket(ReceivingSocket);
        WSACleanup();
        return -1;
     }
    

   // Some info on the receiver side...
   getsockname(ReceivingSocket, (SOCKADDR *)&ReceiverAddr, (int *)sizeof(ReceiverAddr));
   
   SelectTiming = recvfromTimeOutUDP(ReceivingSocket, 10, 0);
   switch (SelectTiming)
        {
             case 0:
                 printf("Actuator: Timeout lor while waiting you bastard client!...\n");
                 break;
             case -1:
                 printf("Actuator: Some error encountered with code number: %ld\n", WSAGetLastError());
                 break;
             default:
                 {
                      while (1)
                      {
                           ByteReceived = recvfrom(ReceivingSocket, ReceiveBuf, BufLength,0, (SOCKADDR *)&SenderAddr, &SenderAddrSize);
                           //msg0 = decrypt(ReceiveBuf,key);
                           if ( ByteReceived > 0 )
                           {
                               printf("***************************************************************\n"); 
                               printf("*                                                             *\n"); 
                               printf("      Actuator: \%s\n", ReceiveBuf);
                               printf("*                                                             *\n"); 
                               printf("***************************************************************\n"); 
                                                       
                           }
                           else if ( ByteReceived <= 0 )
                                printf("Actuator: Connection closed with error code: %ld\n",WSAGetLastError());
                           else
                                printf("Actuator: recvfrom() failed with error code: %d\n",WSAGetLastError());
                           // Some info on the sender side                         
                      }
                 }
   }
 
   printf("Actuator: Finished receiving. Closing the listening socket...\n");
   if (closesocket(ReceivingSocket) != 0)
        printf("Actuator: closesocket() failed! Error code: %ld\n", WSAGetLastError());
   else
        printf("Actuator: closesocket() is OK...\n");
   
   printf("Actuator: Cleaning up...\n");
   if(WSACleanup() != 0)
        printf("Actuator: WSACleanup() failed! Error code: %ld\n", WSAGetLastError());
   else
        printf("Actuator: WSACleanup() is OK\n");
   // Back to the system
   return 0;

}