#include "framework.h"
#include <Shellapi.h>


void simple_shell_launcher::execute()
{

   if(m_iMode == 0)
   {

      m_h = ::ShellExecute(m_oswindow, m_vssOperation, m_vssFile, m_vssParameters, m_vssDirectory, m_iShow);

   }
      
}



bool simple_shell_launcher::succeeded()
{
 
   return ((int32_t) m_h) >= 32;

}









