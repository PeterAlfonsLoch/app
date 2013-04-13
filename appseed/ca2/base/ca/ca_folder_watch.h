#pragma once

namespace ca
{

   class CLASS_DECL_ca2 folder_watch :
      virtual public ::ca::object
   {
   public:

      enum e_action
      {
         action_added,
         action_removed,
         action_renamed_old_name,
         action_renamed_new_name,
         action_unexpected,
      };

      class CLASS_DECL_ca2 callback
      {
      public:
         virtual void on_file_action(e_action eaction, const char * pszFolder, const char * psz);
      };
   
      
      string                  m_strPath;
      callback *              m_pcallback;

      
      virtual bool watch(const char * pszPath);

      virtual void on_file_action(e_action eaction, const char * psz);

   };


   typedef ::ca::smart_pointer < folder_watch > folder_watch_sp;

} // namespace ca