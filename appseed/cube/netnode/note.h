#pragma once

namespace ca2
{
   
   class CLASS_DECL_CA2_CUBE note :
      public ptr
   {
   public:
      var m_user;
      var m_object;
      var m_note;
      var m_title;
      var m_text;
      var m_insertiondatetime;
      var m_modifieddatetime;
      var m_tags;
      var m_taga;

      bool has_tag_by_id(const char * pszTagId);

   };

} // namespace ca2