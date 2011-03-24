#pragma once

namespace vmsp
{

   class file_association : 
      public gen::file_association,
      public ::database::client
   {
   public:

      static const char * m_lpcszMidExtension;
      static const char * m_lpcszKarExtension;
      static const char * m_lpcszSt3Extension;
      static const char * m_lpcszMidClassId;
      static const char * m_lpcszKarClassId;
      static const char * m_lpcszSt3ClassId;
      static const char * m_lpcszMidOldClassId;
      static const char * m_lpcszKarOldClassId;
      static const char * m_lpcszSt3OldClassId;
      static const char * m_lpcszMidEnsureRegistration;
      static const char * m_lpcszKarEnsureRegistration;
      static const char * m_lpcszSt3EnsureRegistration;
      
      file_association(::ca::application * papp);
      virtual ~file_association();


   public:
      void UpdateServerRegistration(const char * lpcszDostring);
      void CheckAssociations();
      virtual bool Initialize();

   };

} // namespace vmsp
