#pragma once


namespace filemanager
{



   class CLASS_DECL_CORE form_update_hint:
      virtual public ::user::form_update_hint
   {
   public:

      
      ::filemanager::manager::e_hint      m_ehint;

      string                              m_strFind;
      string                              m_strReplace;
      string                              m_str;


      form_update_hint(::filemanager::manager::e_hint ehint = ::filemanager::manager::hint_none);
      virtual ~form_update_hint();

   };



} // namespace filemanager













