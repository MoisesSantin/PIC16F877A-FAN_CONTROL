#ifndef Fuses_h
#define Fuses_h

#include "16F877a.h"
#include "regs_16f87x.h"

#use delay (clock = 4000000)
#fuses xt,nowdt,noprotect,put,nobrownout,nolvp 

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                   Definição e inicialização dos port's                */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ZERO_RAM

#use fast_io(a)
#use fast_io(b)
#use fast_io(c)
#use fast_io(d)
#use fast_io(e)


#endif