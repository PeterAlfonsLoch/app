#include "framework.h"


void simple_shell_launcher::execute()
{
    
    if(m_iMode == 0)
    {
        
        if(m_vssOperation.is_empty())
        {
            call_sync(m_vssFile, m_vssParameters, m_vssDirectory, m_iShow, -1, 284, NULL, 0, &m_pid);
        }
        else if(stricmp(m_vssOperation, "open") == 0
        {
            call_sync("gnome-open", m_vssFile, m_vssDirectory, m_iShow, -1, 284, NULL, 0, &m_pid);
        }
                
    }
                
}
                
                
                
                
bool simple_shell_launcher::succeeded()
{
            
   return m_pid >= 0;
            
}
                
                
                
                
                
                
                
                
                
                
