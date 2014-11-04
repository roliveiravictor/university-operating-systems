/**********************************************************************/
/*                                                                    */
/*         Lecture: Operating System								  */
/*         Author:  Victor Rocha                                      */
/*                                                                    */
/**********************************************************************/

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

#ifndef SEMAPHORES_H
#define SEMAPHORES_H 1

#define POSICOES 20


// Prototipos
void capturaTeclado();
void imprimeCaracteres();

/**
Operações sobre semáforos contadores
*/
void DOWN(HANDLE);
void UP(HANDLE);
void LOCK(HANDLE);
void UNLOCK(HANDLE);

#endif

