#include "framework_c.h"



#include "framework.h"



//_flag values (not the ones used by the normal CRT

_FILE __iob[3];

void _init_file()
{
	// STDIN
	__iob[0]._base = (char *) GetStdHandle(STD_INPUT_HANDLE);
	__iob[0]._flag = _FILE_TEXT;

	// STDOUT
	__iob[1]._base = (char *) GetStdHandle(STD_OUTPUT_HANDLE);
	__iob[1]._flag = _FILE_TEXT;

	// STDERR
	__iob[2]._base = (char *) GetStdHandle(STD_ERROR_HANDLE);
	__iob[2]._flag = _FILE_TEXT;
}

_FILE *__iob_func_dup() {return (_FILE*)__iob;}

   // used directly by the stdin, stdout, and stderr macros

