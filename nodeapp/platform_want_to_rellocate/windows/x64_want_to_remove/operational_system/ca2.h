#pragma once

#define WIN64
#define _AMD64_

#define _CRT_SECURE_NO_WARNINGS

#define DRAWDIB_INCLUDE_STRETCHDIB

#pragma pointers_to_members( full_generality, virtual_inheritance )
#include "include/x64_system.h"
#define _ApplicationFrameworkDLL


#include <typeinfo.h>


typedef std::type_info std_type_info;


#include "include/inttypes.h"



#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")
//#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "shell32.lib")
//#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "shlwapi.lib")

#pragma comment(lib, "vfw32.lib") 
#pragma comment(lib, "opengl32.lib") 


