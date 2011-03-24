// WinAppImpl.h: interface for the WinAppImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINAPPIMPL_H__2F78A345_7CC7_48A6_92E2_EBA2D773CAC9__INCLUDED_)
#define AFX_WINAPPIMPL_H__2F78A345_7CC7_48A6_92E2_EBA2D773CAC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ex2/Ex2AppImpl.h"
#include "gen/CommandLineInfo.h"

namespace gen
{
   class CommandLineInfo;
}

CLASS_DECL_VMSWIN void __cdecl wparse_cmdline (
    WCHAR *cmdstart,
    WCHAR **argv,
    WCHAR *args,
    int *numargs,
    int *numchars
    );



class CLASS_DECL_VMSWIN WinAppImpl :
   public Ex2AppImpl
{
public:
	virtual HINSTANCE GetHinstance();
	BOOL _001OnDDECommand(LPCSTR lpcsz);
	virtual void _001EnableShellOpen();
	virtual void * _001OpenDocumentFile(LPCSTR lpcsz);
	virtual void _001OnFileNew();
	WinAppImpl();
	virtual ~WinAppImpl();

   virtual void _001ParseCommandLine(gen::CommandLineInfo& rCmdInfo);
   virtual bool _001ProcessShellCommand(gen::CommandLineInfo& rCmdInfo);

   gen::CommandLineInfo *    m_pcmdinfo;
   gen::CommandLineInfo    m_cmdinfo;
   WCHAR *              m_pszCmdLine;
   int                  m_argc;
   WCHAR **             m_argv;
   WCHAR *              m_pwszExeName;

   USHORT              m_atomApp;
   USHORT              m_atomSystemTopic;

   virtual string get_version();

   virtual void Ex1SetCommandLineInfo(gen::CommandLineInfo & rCmdInfo);
   virtual void Ex1GetCommandLineInfo(gen::CommandLineInfo & rCmdInfo);


};


#endif // !defined(AFX_WINAPPIMPL_H__2F78A345_7CC7_48A6_92E2_EBA2D773CAC9__INCLUDED_)
