#include "framework.h"
#include <stdarg.h>

#if defined(LINUX) || defined(APPLEOS)
#include <sys/time.h>
#include <sys/stat.h>
#include <ctype.h>
#include <unistd.h>
#endif


#include "install/_install.cpp"


#ifndef ANDROID
#include "aura/_aura_aura_aura.cpp"
#endif
#include "exception/_exception.cpp"
#include "message/_message.cpp"
#include "xml/_xml.cpp"
#include "process/_process.cpp"
#include "node/_node.cpp"
#include "os/_os.cpp"


//#include "compress/_compress.cpp"
//#include "crypto/_crypto.cpp"
//#include "fontopus/_fontopus.cpp"


