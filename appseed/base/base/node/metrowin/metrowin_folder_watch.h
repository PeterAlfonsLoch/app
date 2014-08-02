#pragma once

namespace metrowin
{

   class CLASS_DECL_BASE folder_watch :
      virtual public ::file::folder_watch,
      virtual public ::thread
   {
   public:
      
      folder_watch(::base::application * papp);

      virtual bool watch(const char * pszPath);

      virtual e_action translate_os_action(int iAction);

      virtual int run();

   };


} // namespace metrowin