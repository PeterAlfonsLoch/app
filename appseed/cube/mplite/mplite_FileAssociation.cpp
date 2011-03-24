#include "StdAfx.h"
#include "file_association.h"
#include "_vmspConfiguration.h"

namespace vmplite
{

   const char * file_association::m_lpcszMidExtension = ".mid";
   const char * file_association::m_lpcszKarExtension = ".kar";
   const char * file_association::m_lpcszSt3Extension = ".st3";
   const char * file_association::m_lpcszMidClassId = "VeriwellMusicalStudio.Mid.::userbase::document";
   const char * file_association::m_lpcszKarClassId = "VeriwellMusicalStudio.Kar.::userbase::document";
   const char * file_association::m_lpcszSt3ClassId = "VeriwellMusicalStudio.St3.::userbase::document";
   const char * file_association::m_lpcszMidOldClassId = "VeriwellMusicalStudio.Mid.::userbase::document.Old";
   const char * file_association::m_lpcszKarOldClassId = "VeriwellMusicalStudio.Kar.::userbase::document.Old";
   const char * file_association::m_lpcszSt3OldClassId = "VeriwellMusicalStudio.St3.::userbase::document.Old";
   const char * file_association::m_lpcszMidEnsureRegistration = "ensure .mid registration";
   const char * file_association::m_lpcszKarEnsureRegistration = "ensure .kar registration";
   const char * file_association::m_lpcszSt3EnsureRegistration = "ensure .st3 registration";

   file_association::file_association(::ca::application * papp) :
      ca(papp),
      gen::file_association(papp)
   {

   }

   file_association::~file_association()
   {

   }

   bool file_association::Initialize()
   {
      ::database::client::initialize(get_app());
   
      if(!((gen::file_association *) this)->file_association::Initialize())
      {
         return false;
      }

   //   DISetSection("file_association");

      return true;
   }

   void file_association::CheckAssociations()
   {
      if(!Initialize())
      {
         System.simple_message_box(NULL, "Could not access the registry!.");
         return;
      }

      Key keyMid(GetHKEYClassesRoot(), m_lpcszMidExtension, false);

      string str;
      keyMid.QueryValue("", str);

      int i;
      if(str != m_lpcszMidClassId)
      {
         if(data_get("ForceMidRegistration", ::ca::system::idEmpty, i))
         {
            data_set("MidOldRegistration", ::ca::system::idEmpty, str);
            if(i != 0)
            {
               keyMid.SetValue("", m_lpcszMidClassId);
            }
         }
      }

      Key keyKar(GetHKEYClassesRoot(), m_lpcszKarExtension, false);

      keyKar.QueryValue("", str);

      if(str != m_lpcszKarClassId)
      {
         if(data_get("ForceKarRegistration", ::ca::system::idEmpty, i))
         {
            data_set("KarOldRegistration", ::ca::system::idEmpty, str);
            if(i != 0)
            {
               keyKar.SetValue("", m_lpcszKarClassId);
            }
         }
      }


      Key keySt3(GetHKEYClassesRoot(), m_lpcszSt3Extension, false);

      keySt3.QueryValue("", str);

      if(str != m_lpcszSt3ClassId)
      {
         if(data_get("ForceSt3Registration", ::ca::system::idEmpty, i))
         {
            data_set("St3OldRegistration", ::ca::system::idEmpty, str);
            if(i != 0)
            {
               keySt3.SetValue("", m_lpcszSt3ClassId);
            }
         }
      }




   }

   void file_association::UpdateServerRegistration(const char * lpcszDocString)
   {
      UNREFERENCED_PARAMETER(lpcszDocString);
   }


} // namespace _vmsp
