#include "TurboC.h"

int getch()
{
   
   return App(::get_thread_app()).consoleprompt()->getch();

}