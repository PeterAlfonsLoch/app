#include "framework.h"


void simple_shell_launcher::execute()
{

   m_h = ::ShellExecute(m_hwnd, m_vssOperation, m_vssFile, m_vssParameters, m_vssDirectory, m_iShow);
      
}


#ifdef LINUX


#endif

