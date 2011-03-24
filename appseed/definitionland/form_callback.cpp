#include "StdAfx.h"

namespace definitionland
{

form_callback::form_callback()
{
}

form_callback::~form_callback()
{
}

void form_callback::OnUpdate(form_view * pview, BaseView* pSender, LPARAM lHint, base_object* phint) 
{
}


bool form_callback::BaseOnControlEvent(form_view * pview, BaseControlEvent * pevent)
{
   if(pevent->m_etype == basecontrol::EventButtonClicked)
   {
      if(pevent->m_pcontrol->m_strId == "lfs")
      {
         form_update_hint uh;
         uh.m_etype = form_update_hint::type_browse;
         uh.m_strForm = "filemanager_add_location_lfs.xhtml";
         pview->GetDocument()->UpdateAllViews(NULL, 0, &uh);
         Ex1VirtualGuieInterface * pguie = pview->GetChildByName("lfs");
         text_interface * ptext = dynamic_cast < text_interface * > (pguie);
         string strPath;
         ptext->_001SetText(strPath);
      }
      else if(pevent->m_pcontrol->m_strId == "ftp")
      {
         form_update_hint uh;
         uh.m_etype = form_update_hint::type_browse;
         uh.m_strForm = "filemanager_add_location_ftp.xhtml";
         pview->GetDocument()->UpdateAllViews(NULL, 0, &uh);
      }
      else if(pevent->m_pcontrol->m_strId == "submit")
      {
         if(pview->m_strPathName == "filemanager_add_location_lfs.xhtml")
         {
            AStrArray wstra;
            //VmsDataGet(m_pmanager->GetDDX().m_ptemplate->m_datakeyStatic, 0, 0, wstra);
            Ex1VirtualGuieInterface * pguie = pview->GetChildByName("lfs");
            text_interface * ptext = dynamic_cast < text_interface * > (pguie);
            string str;
            ptext->_001GetText(str);
            wstra.AddUnique(str);
            //VmsDataSet(m_pmanager->GetDDX().m_ptemplate->m_datakeyStatic, 0, 0, wstra);

         }
         else if(pview->m_strPathName == "filemanager_add_location_ftp.xhtml")
         {
         }
         else if(pview->m_strPathName == "filemanager\\replace_name_in_file_system.xhtml")
         {
            form_update_hint uh;
            Ex1VirtualGuieInterface * pguie = pview->GetChildByName("encontrar");
            text_interface * ptext = dynamic_cast < text_interface * > (pguie);
            //ptext->_001GetText(uh.m_strFind);
            pguie = pview->GetChildByName("substituir");
            ptext = dynamic_cast < text_interface * > (pguie);
            //ptext->_001GetText(uh.m_strReplace);
            pview->GetDocument()->UpdateAllViews(NULL, 0, &uh);
         }
      }
   }
   return false;
}

} // namespace definitionland