#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//#include "rpiGpio.h"
#include <pthread.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <softPwm.h>
#include <stdint.h>


typedef  unsigned char uint8_t;


void* Motorcontrol (void* param);  
void* dist (void* param); //thread function
void Motorinit();
void* socketServer();

pthread_t socketThread;



uint8_t MotorHF[7] = {7,3,0xa5,2,3,0xa5,2}; 
// High speed forward left + right; add explanation

uint8_t MotorST[7] = {7,0,0,0,0,0,0};
// Stop left + right; add explanation

uint8_t MotorHR[7] = {7,3,0xa5,1,3,0xa5,1};
//High speed reverse left + right; add explanation

uint8_t MotorTurnL[7] = {7,3,0xa5,1,3,0xa5,2};
//High speed turn Left ?

uint8_t MotorTurnR[7] = {7,3,0xa5,2,3,0xa5,1};
//High speed turn right ?

int fd;
int ds;





void motorInit()
{
    uint8_t Totalpower[2]={4,250};     // power between 0 and 255
    uint8_t Softstart[3]={0x91,23,0};  // add explanation


    wiringPiSetup () ;
    pullUpDnControl(0,PUD_DOWN);

    fd=wiringPiI2CSetup(0x32);

    write(fd,&Totalpower[0], 2);  
    write(fd,&Softstart[0],3);  
   
    //number of bytes = 3
    //What is a soft start?
}



void* socketServer()
{
    socklen_t sockfd, newsockfd, portno, clilen;//socklen_t is een unsigned int van 32 bits
    char buffer[256];//Hier komt de ontvangen data van de client
    char buffer2[256];//Data dat wordt gestuurd naar de client wordt hier bewaard

    struct sockaddr_in serv_addr, cli_addr;//declaratie van het server adres/client adres als type struct sockaddr_in
    int  n;

    //Roept de socket functie aan
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));//bzero plaatst bytes (lengte van serv_addr) met als null als waarde op de positie van serv_addr
    portno = 55000;
    //declaratie van de variabele van de struct serv_addr
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    //Geeft de socket weer vrij nadat het programma wordt afgesloten
    int yes = 1;
    if ( setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1 )
        printf("Error so_reusaddr");


    /* Now bind the host address using bind() call.*/
	//De local socket serv_addr wordt toegewezen aan het adres van socket sockfd
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR on binding");
        exit(1);
    }

        //wacht in slaapstand tot een client verbinding probeert te maken
        listen(sockfd,5);
        clilen = sizeof(cli_addr);

        //Accepteert connectie van de client
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0)
        {
            perror("ERROR on accept");
            exit(1);
        }
	while(1){
        bzero(buffer,256);//Buffer wordt naar null gezet
        n = read( newsockfd,buffer,255 );//Leest de waarde van de buffer uit
        //Controleert of er data is ontvangen van de client
        if (n < 0)
        {
            perror("ERROR reading from socket");
            exit(1);
        }

       




int ch;
ch = *buffer;//De ontvangen waarde wordt in button gedaan


	if(ch  =='w'){
       write(fd,&MotorHF[0],7);  //forward
	delay(23);
      write(fd,&MotorST[0],7);
     }

 if(ch  == 48){
       write(fd,&MotorHF[0],7);  //forward
	delay(23);
write(fd,&MotorST[0],7);
      
     }  if(ch == 's'){
	write(fd,&MotorHR[0],7);
        delay(23);
write(fd,&MotorST[0],7);
        
     }   if (ch == 'd'){
	write(fd,&MotorTurnR[0],7);
        delay(23);
write(fd,&MotorST[0],7);
        
     }  if (ch == 'a'){
        write(fd,&MotorTurnL[0],7);
        delay(23);
write(fd,&MotorST[0],7);
        
     } if (ch == 'x'){
	write(fd,&MotorST[0],7);  //stop
	}

uint8_t MotorHF[7] = {7,3,0xa5,2,3,0xa5,2}; 
// High speed forward left + right; add explanation

uint8_t MotorST[7] = {7,0,0,0,0,0,0};
// Stop left + right; add explanation

uint8_t MotorHR[7] = {7,3,0xa5,1,3,0xa5,1};
//High speed reverse left + right; add explanation

uint8_t MotorTurnL[7] = {7,3,0xa5,1,3,0xa5,2};
//High speed turn Left ?

uint8_t MotorTurnR[7] = {7,3,0xa5,2,3,0xa5,1};
        
        if (n < 0)
        {
            perror("ERROR writing to socket");
            exit(1);
        }
    }

}


int main()
{
    
    motorInit();//Functie motorInit wordt aangeroepen

    pthread_create(&socketThread,NULL,socketServer,0);//Start socketserver in een thread
    

//Loop zodat het programma aan blijft
    while(1)
    {

    }

    return 0;

}


