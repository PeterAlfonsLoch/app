#pragma once

namespace npca2
{

   class plugin;

   class system :
      virtual public ::icube::system
   {
   public:


      plugin * m_pplugin;

      
      virtual bool os_native_bergedge_start();

   };


} // namespace npca2