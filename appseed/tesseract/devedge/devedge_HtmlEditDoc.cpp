#include "StdAfx.h"
#include "HtmlEditDoc.h"

devedgeHtmlEditDoc::devedgeHtmlEditDoc(::ca::application * papp) :
   ca(papp),
   data_container(papp),
   ::document(papp),
   ::userbase::document(papp),
   m_memfile(papp), 
   m_file(papp),
   html_document(papp)
{
}

bool devedgeHtmlEditDoc::_001OnUpdateCmdUi(cmd_ui * pcmdui)
{
   string strId(pcmdui->m_id);
   if(strId == "file::save")
   {
      OnUpdateFileSave(pcmdui);
      return TRUE;
   }
   else if(strId == "edit::undo")
   {
      OnUpdateEditUndo(pcmdui);
      return TRUE;
   }
   else if(strId == "edit::redo")
   {
      OnUpdateEditRedo(pcmdui);
      return TRUE;
   }
   return html_document::_001OnUpdateCmdUi(pcmdui);
}

bool devedgeHtmlEditDoc::_001OnCommand(id id)
{
   if(id == "file::save")
   {
      on_file_save();
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


BOOL devedgeHtmlEditDoc::on_new_document()
{
   if (!html_document::on_new_document())
      return FALSE;

   update_all_views(NULL, 0);

   return TRUE;
}

devedgeHtmlEditDoc::~devedgeHtmlEditDoc()
{
}



#ifdef _DEBUG
void devedgeHtmlEditDoc::assert_valid() const
{
   html_document::assert_valid();
}

void devedgeHtmlEditDoc::dump(dump_context & dumpcontext) const
{
   html_document::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// devedgeHtmlEditDoc serialization

/*
void devedgeHtmlEditDoc::Serialize(CArchive& ar)
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

bool devedgeHtmlEditDoc::on_open_document(var varFile)
{
   UNREFERENCED_PARAMETER(varFile);
   //if(m_file.IsOpened())
     // m_file.close();
   //if(!m_file.open(lpszPathName, ::ex1::file::type_binary | ::ex1::file::mode_read_write))
   //   return FALSE;
   return TRUE;
}


BOOL devedgeHtmlEditDoc::on_save_document(const char * lpszPathName)
{
   UNREFERENCED_PARAMETER(lpszPathName);
   return TRUE;
}

void devedgeHtmlEditDoc::OnUpdateFileSave(cmd_ui *pcmdui)
{
   pcmdui->Enable(TRUE);
}

void devedgeHtmlEditDoc::OnUpdateEditUndo(cmd_ui *pcmdui)
{
   UNREFERENCED_PARAMETER(pcmdui);
}

void devedgeHtmlEditDoc::OnUpdateEditRedo(cmd_ui *pcmdui)
{
   UNREFERENCED_PARAMETER(pcmdui);
}

void devedgeHtmlEditDoc::on_file_save()
{
   html_document::on_file_save();
}

void devedgeHtmlEditDoc::OnEditUndo()
{
}

void devedgeHtmlEditDoc::OnEditRedo()
{
}



