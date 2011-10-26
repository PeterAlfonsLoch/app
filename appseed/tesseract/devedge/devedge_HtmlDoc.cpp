#include "StdAfx.h"
#include "HtmlDoc.h"

devedgeHtmlDoc::devedgeHtmlDoc(::ca::application * papp) :
   ca(papp),
   data_container(papp),
   ::document(papp),
   ::userbase::document(papp),
   m_memfile(papp),
   m_file(papp), 
   html_document(papp)
{
   m_iBranch = 0;

/*   string str = "\
Curitiba, 24 de fevereiro de 2008.\n\
\n\
Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!\n\
Assinado Camilo Sasuke Tsumanuma.\n\
";*/
   string str = "\
Curitiba, 24 de fevereiro de 2008.\n\
\n\
The LoadCursor function loads the cursor resource only\n\
if it has not been loaded; otherwise, it retrieves the\n\
handle to the existing resource. This function returns\n\
a valid cursor handle only if the lpCursorName parameter\n\
is a pointer to a cursor resource. If lpCursorName is\n\
a pointer to any type of resource other than a cursor\n\
(such as an icon), the return value is not NULL, even\n\
though it is not a valid cursor handle.\n\
";
}

bool devedgeHtmlDoc::_001OnUpdateCmdUi(cmd_ui * pcmdui)
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

bool devedgeHtmlDoc::_001OnCommand(id id)
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
      return TRUE;
   }
   return html_document::_001OnCommand(id);
}


BOOL devedgeHtmlDoc::on_new_document()
{
   if (!html_document::on_new_document())
      return FALSE;

   update_all_views(NULL, 0);

   return TRUE;
}

devedgeHtmlDoc::~devedgeHtmlDoc()
{
}



#ifdef _DEBUG
void devedgeHtmlDoc::assert_valid() const
{
   html_document::assert_valid();
}

void devedgeHtmlDoc::dump(dump_context & dumpcontext) const
{
   html_document::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// devedgeHtmlDoc serialization

/*
void devedgeHtmlDoc::Serialize(CArchive& ar)
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

bool devedgeHtmlDoc::on_open_document(var varFile)
{
   return html_document::on_open_document(varFile);
}


BOOL devedgeHtmlDoc::on_save_document(const char * lpszPathName)
{
   UNREFERENCED_PARAMETER(lpszPathName);
   return TRUE;
}

void devedgeHtmlDoc::OnUpdateFileSave(cmd_ui *pcmdui)
{
   pcmdui->Enable(TRUE);
}

void devedgeHtmlDoc::OnUpdateEditUndo(cmd_ui *pcmdui)
{
   UNREFERENCED_PARAMETER(pcmdui);
}

void devedgeHtmlDoc::OnUpdateEditRedo(cmd_ui *pcmdui)
{
   UNREFERENCED_PARAMETER(pcmdui);
}

void devedgeHtmlDoc::on_file_save()
{
   html_document::on_file_save();
}

void devedgeHtmlDoc::OnEditUndo()
{
}

void devedgeHtmlDoc::OnEditRedo()
{
}



