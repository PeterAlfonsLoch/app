#include "StdAfx.h"
#include "file_association.h"

namespace vmsp
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
   
   if(!((gen::file_association *) this)->file_association::Initialize())
   {
      return false;
   }

   m_dataid = "file_association";

   return true;
}

void file_association::CheckAssociations()
{
   if(!Initialize())
   {
      System.simple_message_box(NULL, "Could not access the registry!.");
      return;
   }

   registry::Key keyMid(GetHKEYClassesRoot(), m_lpcszMidExtension, true);

   string str;
   keyMid.QueryValue("", str);

   int i;
   if(str != m_lpcszMidClassId)
   {
      if(data_get(m_lpcszMidEnsureRegistration, i))
      {
         data_get(m_lpcszMidOldClassId, str);
         if(i != 0)
         {
            keyMid.SetValue("", m_lpcszMidClassId);
         }
      }
   }

   registry::Key keyKar(GetHKEYClassesRoot(), m_lpcszKarExtension, true);

   keyKar.QueryValue("", str);

   if(str != m_lpcszKarClassId)
   {
      if(data_get(m_lpcszKarEnsureRegistration, i))
      {
         data_get(m_lpcszKarOldClassId, str);
         if(i != 0)
         {
            keyMid.SetValue("", m_lpcszKarClassId);
         }
      }
   }


   registry::Key keySt3(GetHKEYClassesRoot(), m_lpcszSt3Extension, true);

   keySt3.QueryValue("", str);

   if(str != m_lpcszSt3ClassId)
   {
      if(data_get(m_lpcszSt3EnsureRegistration, i))
      {
         data_get(m_lpcszSt3OldClassId, str);
         if(i != 0)
         {
            keySt3.SetValue("", m_lpcszSt3ClassId);
         }
      }
   }




}

void file_association::UpdateServerRegistration(const char * lpcszDostring)
{


}


} // namespace vmsp
