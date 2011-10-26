#include "StdAfx.h"
#include "front_document.h"


front_document::front_document(::ca::application * papp) :
   ca(papp),
   data_container(papp),
   ::document(papp),
   ::userbase::document(papp),
   m_memfile(papp), 
   m_file(papp),
   html_document(papp)
{
}

bool front_document::_001OnCommand(id id)
{
   if(id == "start")
   {
      OnStart();
      return true;
   }
   else if(id == "edit::undo")
   {
      OnEditUndo();
      return true;
   }
   else if(id == "edit::redo")
   {
      OnEditRedo();
      return true;
   }
   return html_document::_001OnCommand(id);
}

bool front_document::_001OnUpdateCmdUi(cmd_ui * pcmdui)
{
   if(pcmdui->m_id == "start")
   {
      OnUpdateStart(pcmdui);
      return TRUE;
   }
   else if(pcmdui->m_id == "edit::undo")
   {
      OnUpdateEditUndo(pcmdui);
      return TRUE;
   }
   else if(pcmdui->m_id == "edit::redor")
   {
      OnUpdateEditRedo(pcmdui);
      return TRUE;
   }
   return html_document::_001OnUpdateCmdUi(pcmdui);
}

BOOL front_document::on_new_document()
{
   if (!html_document::on_new_document())
      return FALSE;

   update_all_views(NULL, 0);

   return TRUE;
}

front_document::~front_document()
{
}



#ifdef _DEBUG
void front_document::assert_valid() const
{
   html_document::assert_valid();
}

void front_document::dump(dump_context & dumpcontext) const
{
   html_document::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// front_document serialization

/*
void front_document::Serialize(CArchive& ar)
{
   if (ar.IsStoring())
   {
      // TODO: add storing code here
   }
   else
   {
      // TODO: add loading code here
   }
}
*/


bool front_document::on_open_document(var varFile)
{
   UNREFERENCED_PARAMETER(varFile);
   //if(m_file.IsOpened())
     // m_file.close();
   //if(!m_file.open(lpszPathName, ::ex1::file::type_binary | ::ex1::file::mode_read_write))
     // return FALSE;
   return TRUE;
}


BOOL front_document::on_save_document(const char * lpszPathName)
{
   UNREFERENCED_PARAMETER(lpszPathName);
   return TRUE;
}

void front_document::OnUpdateStart(cmd_ui *pcmdui)
{
   pcmdui->Enable(TRUE);
}

void front_document::OnUpdateEditUndo(cmd_ui *pcmdui)
{
   UNREFERENCED_PARAMETER(pcmdui);
}

void front_document::OnUpdateEditRedo(cmd_ui *pcmdui)
{
   UNREFERENCED_PARAMETER(pcmdui);
}

void front_document::OnStart()
{
   open_document("http://localhost:10011/");
}

void front_document::OnEditUndo()
{
}

void front_document::OnEditRedo()
{
}




