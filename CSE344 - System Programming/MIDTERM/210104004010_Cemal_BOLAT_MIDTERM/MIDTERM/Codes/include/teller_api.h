#ifndef TELLER_API_H
#define TELLER_API_H

#include <sys/types.h>

// func: main gibi davranacak fonksiyon, sadece arg alır
pid_t Teller(void* (*func)(void*), void* arg);
int waitTeller(pid_t pid, int* status);


#endif // TELLER_API_H
