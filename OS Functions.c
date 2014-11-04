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

char buffer[20];
int position=0;
int lock = 0;
extern int sequenciaArquivo;
extern int pos;

extern LONG lInsArqTId;  
extern LONG lImpArqTId; 

extern HANDLE mutex;			// Mutex - Binary Semaphores {0, 1}
extern HANDLE posicoesOcupadas;	// Event sync semaphores
extern HANDLE posicoesLivres;	// Event sync semaphores

void capturaTeclado() 
{
	while(1) 
	{     
		/*
		As the main thread, this thread also needs to verify 
		if any key was pressed
		*/
		if(kbhit())
		{
		   char c = getch();
			if(c==27)
				exit(0);
			else if(lock==0)
			
			//Verifies if ASCII character	
			if(isascii(c))
				{
					LOCK(mutex);
					buffer[position]=c;
					position++;
					UNLOCK(mutex);
				}
				else
					printf("Not ASCII\n\n");
		}

		//Case twentieth position beep and return cursor
		if(position==20)
		{
			position=0;
			lock=1;
			printf("\a");
		}
	}
}


void imprimeCaracteres() 
{
	while(1) 
	{
		//Counter to print buffer's character 
		Sleep(5000);
		LOCK(mutex);
			int i=0;
			
			//Verifies if buffer is empty
				if(!strlen(buffer) == 0)
				{
					for(i=0; i<20;i++)
						printf("%c", buffer[i]);
					
						//clear buffer after print
						memset(buffer,0,20);

						/*
						Returns cursor to initial position, otherwise will just print
						every time the buffer reaches his next max value in the subsequent
						turn
						*/
						position=0;
						lock=0;
						printf("\n\n################### BUFFER DUMPED ###################\n\n");
						UNLOCK(mutex);
				}
				else
				{
					printf("Buffer is empty \n\n");
					UNLOCK(mutex);
				}
		}
	}

//Semaphore operations
void DOWN(HANDLE h)
{
	WaitForSingleObject(h, INFINITE);	
}

void UP(HANDLE h)
{
	ReleaseSemaphore(h, 1, NULL);
}

void LOCK(HANDLE h)
{
	WaitForSingleObject(h, INFINITE);	
}

void UNLOCK(HANDLE h) 
{
    ReleaseMutex(h);			    
}


