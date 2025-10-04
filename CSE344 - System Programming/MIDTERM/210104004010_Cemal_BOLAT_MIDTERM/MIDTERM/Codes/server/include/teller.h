#ifndef TELLER_H
#define TELLER_H

void*   deposit(void*); 
void*   withdraw(void*);
void    handle_teller_signal(int signo);

#endif // TELLER_H
