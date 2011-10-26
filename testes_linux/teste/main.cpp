#define __USE_GNU
#include <stdio.h>
#include <signal.h>


void sig_handler(int signo)
{
   throw 1984;
}


int main(int argc, char **argv)
{

   struct sigaction act;
   struct sigaction oact;
   sigset_t sset;

   sigemptyset(&sset);
   sigaddset(&sset, SIGSEGV);


   act.sa_flags = SA_NODEFER ;
   act.sa_mask = sset;
   act.sa_handler = sig_handler;

   sigaction(SIGSEGV, (const struct sigaction *) &act, NULL);

   try
   {
      *(char*)0 = '\0';
   }
   catch(int i)
   {
      printf("caught exception %d", i);
   }

   printf("Normal execution after sigsegv");


   printf("Done here!\n");

 return 0;
}
