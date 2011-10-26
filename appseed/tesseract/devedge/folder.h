#pragma once

namespace devedge
{

   class project;

   class CLASS_DECL_CA2_TESSERACT folder :
      virtual public array_app_alloc < file, file & >
   {
   public:
      folder(::ca::application * papp);

      project *   m_pproject;
      string      m_strFilter;

      void load(project * pproject, const char * pszFilter);

      index find(const char * pszName);
      bool has(const char * pszName);
      
   };

} // namespace devedge