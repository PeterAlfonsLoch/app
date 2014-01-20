// argcargv.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#include "framework.h"

#ifdef WINDOWSEX

#define _MAX_CMD_LINE_ARGS  32
char *_argv[_MAX_CMD_LINE_ARGS+1];
static char *_rawCmd = 0;

int32_t _init_args()
{
	_argv[0] = 0;

	char *sysCmd = GetCommandLine();
	int32_t szSysCmd = lstrlen(sysCmd);

	// copy the system command line
	char *cmd = (char*)HeapAlloc(GetProcessHeap(), 0, sizeof(char)*(szSysCmd+1));
	_rawCmd = cmd;
	if (!cmd)
		return 0;
	lstrcpy(cmd, sysCmd);

	// Handle a quoted filename
	if (*cmd == _T('"'))
	{
		cmd++;
		_argv[0] = cmd;						// argv[0] = exe name

		while (*cmd && *cmd != _T('"'))
			cmd++;

		if (*cmd)
			*cmd++ = 0;
		else
			return 0;						// no end quote!
	}
	else
	{
		_argv[0] = cmd;						// argv[0] = exe name

		while (*cmd && !isspace_dup(*cmd))
			cmd++;

		if (*cmd)
			*cmd++ = 0;
	}

	int32_t argc = 1;
	for (;;)
	{
		while (*cmd && isspace_dup(*cmd))		// Skip over any whitespace
			cmd++;

		if (*cmd == 0)						// End of command line?
			return argc;

		if (*cmd == _T('"'))					// Argument starting with a quote???
		{
			cmd++;

			_argv[argc++] = cmd;
			_argv[argc] = 0;

			while (*cmd && *cmd != _T('"'))
				cmd++;

			if (*cmd == 0)
				return argc;

			if (*cmd)
				*cmd++ = 0;
		}
		else
		{
			_argv[argc++] = cmd;
			_argv[argc] = 0;

			while (*cmd && !isspace_dup(*cmd))
				cmd++;

			if (*cmd == 0)
				return argc;

			if (*cmd)
				*cmd++ = 0;
		}

		if (argc >= _MAX_CMD_LINE_ARGS)
			return argc;
	}
}

void _term_args()
{
	if (_rawCmd)
		HeapFree(GetProcessHeap(), 0, _rawCmd);
}


#endif
