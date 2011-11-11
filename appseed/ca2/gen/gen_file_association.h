#pragma once

namespace gen
{

   class CLASS_DECL_ca file_association :
      public ::win::registry
   {
   public:
      file_association(::ca::application * papp);
      virtual ~file_association();

   protected:
      HKEY m_hkeyClassesRoot;

   public:
      virtual bool Initialize();
      HKEY GetHKEYClassesRoot();

   };

}
