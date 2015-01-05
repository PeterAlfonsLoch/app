#include "framework.h"
#include "ansios.h"
#if defined(ANDROID)
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#elif defined(LINUX)
#include <sys/wait.h>
#include <unistd.h>
#include <spawn.h>
extern char **environ;
#elif defined(APPLEOS)
#include <sys/wait.h>
#include <unistd.h>
#include <spawn.h>
#include <pthread.h>
#include <stdlib.h>
extern char * const * environ;
#endif
#if defined(LINUX) || defined(ANDROID)
#include <fcntl.h>
#include <unistd.h>
#endif

//O volume na unidade C n∆o tem nome.
 //O N£mero de SÇrie do Volume Ç 72AC-5E14

 //Pasta de C:\nordroid\app\appseed\aura\aura\node\ansios

#include "ansios_pipe.cpp"
#include "ansios_process.cpp"
#include "ansios_thread_impl.cpp"
//2015-01-05  08:57                 0 _ansios_nod.cpp"
//               4 arquivo(s)         20.265 bytes
//               0 pasta(s)   19.156.402.176 bytes dispon°veis
