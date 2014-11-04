/**********************************************************************/
/*                                                                    */
/*         Lecture: Operating System							      */
/*         Author:  Victor Rocha                                      */
/*																	  */
/*	This is program simulates a print queue to test binary			  */
/*	semaphores and counters from windows API.						  */
/*                                                                    */
/**********************************************************************/

#include "OS SemaphoresWindows.h"

HANDLE MainTHD_PrintTime;   // Handle for Main Thread
HANDLE TecladoThread;		// Handle for File Insertion Thread
HANDLE ImprimeBufferThrd;   // Handle for File Print Thread
LONG   lInsArqTId;  
LONG   lImpArqTId; 

HANDLE mutex;				// Mutex - Binary Sempahore {0, 1}
HANDLE posicoesOcupadas;	// Events counter semaphore
HANDLE posicoesLivres;		// Events counter semaphore


int main(int argc, char **argv)
{
	time_t rawtime;
	struct tm * timeinfo;

	//Binary Semaphore - RC's Key {0,1}
    mutex = CreateMutex(NULL,FALSE, "Mutex_Queue");
   
    //Test if Mutex was correctly created
    if (mutex == NULL)
	{
        printf("\nError creating muxter: %d\n", GetLastError());
        ExitProcess(0);
    }

	//Counter semaphore used to control occupied positions
	posicoesOcupadas = CreateSemaphore(NULL,0,POSICOES,"Semaphores are full.");
    if (posicoesOcupadas == NULL)
    {
        printf("\nError creating busyPositions semaphore: %d\n", GetLastError());
        ExitProcess(0);
    }

	//Counter semaphore used to control free positions
	posicoesLivres = CreateSemaphore(NULL,POSICOES,POSICOES,"Semaphores are free.");
    if (posicoesLivres == NULL)
    {
        printf("\nError creating freePositions semaphore: %d\n", GetLastError());
        ExitProcess(0);
    }

    //Creates threads to use print spool
	TecladoThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)capturaTeclado,NULL,0,(LPDWORD) &lInsArqTId );
	ImprimeBufferThrd = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)imprimeCaracteres,NULL,0,(LPDWORD) &lImpArqTId);

	while(1)
	{
		//Verifies space key to exit the program case it's pressed
		if(kbhit())
		{
			char c = getch();
			if(c==27)
			exit(0);
		}

		//Refresh and prints time
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		printf ( "Current local time and date: %s\n", asctime (timeinfo) );
		Sleep(1000);
	}

	//A way to block one thread indefinitely
    MainTHD_PrintTime = GetCurrentThread();
    SuspendThread(MainTHD_PrintTime);
    exit(0);
}

