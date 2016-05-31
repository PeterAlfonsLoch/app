

namespace ace
{


   void shell_launcher::execute()
   {

      if(m_iMode == 0)
      {

         m_h = ::ShellExecute(m_oswindow,m_vssOperation,m_vssFile,m_vssParameters,m_vssDirectory,m_iShow);

      }

   }



   bool shell_launcher::succeeded()
   {

      return ((int_ptr)m_h) >= 32;

   }


} // namespace ace










