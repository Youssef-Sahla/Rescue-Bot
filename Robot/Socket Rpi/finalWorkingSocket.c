//Author: Youssef en Atef
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <softPwm.h>
#include <stdint.h>


int motorAddress;
int motorShift = 2;//Indiceert welk element van de array MotorSpeed gebruikt moet worden
uint8_t motorSpeed[7] = {0x0,0x46,0x59,0x6c,0x7f,0x92,0xa5};//De variabele snelheden van de servomotors


void* socketServer(); //Declaratie van de socketserver functie

pthread_t socketThread;//Socketserver thread
pthread_t distInitThread;// distance thread

int fd;



//Array met de waardes die naar de motorControl moet worden gestuurd
uint8_t achteruit[7] = {7, 3, 0xa5, 2, 3, 0xa5, 2};// Motors aan beide kanten naar achteren
uint8_t rechtsaf[7] = {7, 3, 0xa5, 1, 0, 0, 0};// Motors linkerkant naar voren
uint8_t linksaf[7] = {7, 0, 0, 0, 3, 0xa5, 1};// Motors rechterkant naar voren
uint8_t vooruit[7] = {7, 3, 0xa5, 1, 3, 0xa5, 1};//Motors aan allebei de kanten naar voren
uint8_t stop[7] = {7, 0, 0, 0, 0, 0, 0};// Alle motors stoppen



void* robotBesturen(uint8_t *invoerWaarde)
{
    int i;
    for(  i = 0; i < 8; i++)
    {
        wiringPiI2CWrite(motorAddress,invoerWaarde[i]);
    }


    return 0;

}
//Bepaalt welke array als parameter moet worden meegegeven aan robotBesturen
void charAndroid(char character)
{
    printf("ontvangen input in functie: %c \n", character);
    if(character == 'w')
    {
        robotBesturen(achteruit);
    }
    if(character == 'a')
    {
        robotBesturen(rechtsaf);
    }
    if(character == 's')
    {
        robotBesturen(vooruit);
    }
    if(character == 'd')
    {
        robotBesturen(linksaf);
    }
    if(character == 'x')
    {
        robotBesturen(stop);
	}

}

//Bepaalt het motoradres en voert een softstart uit
void motorInit()
{

    int i;
    uint8_t Totalpower[2] = {4, 250}; // power between 0 and 255
    uint8_t Softstart[3] = {0x91, 23, 0}; // ?
    motorAddress = wiringPiI2CSetup(0x32);

//Parameters worden geschreven naar de microcontroler
    for(  i = 0; i < 3; i++)
    {
        wiringPiI2CWrite (motorAddress,Softstart[i]);

    }
    for(  i = 0; i < 2; i++)
    {
        wiringPiI2CWrite (motorAddress,Totalpower[i]);

    }
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
    portno = 50000;
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

    while(1)
    {
        //wacht in totdat een client verbining probeert te maken
        listen(sockfd,5);
        clilen = sizeof(cli_addr);

        //Connectie geaccepteerd socket
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0)
        {
            perror("ERROR on accept");
            exit(1);
        }

        bzero(buffer,256);//Buffer wordt naar null gezet
        n = read( newsockfd,buffer,255 );//Leest de waarde van de buffer uit
        //is er data ontvangen?
        if (n < 0)
        {
            perror("ERROR reading from socket");
            exit(1);
        }

        char button;//rijrichting wordt opgeslagen in button
        int dist = 0;//afstand van het object wordt hier opgeslagen
 
        button = *buffer;//De ontvangen waarde wordt in button gedaan
        dist = 0;//distance haalt de afstand op, dit wordt in de variable gezet
		charAndroid(button);
       
        //return afstand
        if(button >= 48 && button <= 54)
        {
     
            //return de afstand
            //sprintf(buffer2, dist);
            //puts(buffer2);
            //n = write(newsockfd,buffer2,strlen(buffer2));

        }
        else
        {
            
			sprintf(buffer2, "%d cm  - %f - %d m/s \n");
            puts(buffer2);
            n = write(newsockfd,buffer2,strlen(buffer2));
        }

        if (n < 0)
        {
			//deze error krijgen we nooit.
            perror("ERROR writing to socket");
            exit(1);
        }
    }

}


int main()
{
    
    motorInit();//Functie motorInit wordt aangeroepen

    pthread_create(&socketThread,NULL,socketServer,0);//Start socketserver in een thread
    
	uint8_t TxData1[2] = {00,0x51}; //add second array element; 
    uint8_t TxData2[1] = {0x03}; //What is the function of memory location 3?
    uint8_t low=50;

    wiringPiSetup(); 
    fd=wiringPiI2CSetup(0x70);

    usleep(1000);

//loop zodat programma aanblijft
    while(1)
    {
	 // start a new measurement in centimeters
       write(fd,&TxData1[0],2);
       usleep(100000);  //give the sensor time for measurement

       write(fd,&TxData2[0],1);  //ask for the lower order byte of the range
       read(fd,&low,1);

       printf("Distance is %d cm  \n",low);
       usleep(2000000);
    }

    return 0;

}