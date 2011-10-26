#include "StdAfx.h"
#include "FrontDoc.h"

devedgeFrontDoc::devedgeFrontDoc(::ca::application * papp) :
   ca(papp),
   data_container(papp),
   ::document(papp),
   ::userbase::document(papp),
   m_memfile(papp), 
   m_file(papp),
   m_memfileBody(papp),
   html_document(papp)
{
/*   m_memfileBody << "<html>\n";
   m_memfileBody << "<head>\n";
   m_memfileBody << "</head>\n";
   m_memfileBody << "<body>\n";
   m_memfileBody << "<h1>Ti Amo Carlos Gustavo Cecyn Lundgren de 15 de novembro de 1984!</h1>\n";
   m_memfileBody << "<h1>Assinado Camilo Sasuke Tsumanuma de 2 de abril de 1977!</h1>\n";
   m_memfileBody << "<h1>Demais!</h1>\n";
   m_memfileBody << "</body>\n";*/
   //m_memfileBody.Truncate(0);
}

bool devedgeFrontDoc::_001OnUpdateCmdUi(cmd_ui * pcmdui)
{
   string strId(pcmdui->m_id);
   if(strId == "start")
   {
      OnUpdateStart(pcmdui);
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

bool devedgeFrontDoc::_001OnCommand(id id)
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


BOOL devedgeFrontDoc::on_new_document()
{
   if (!html_document::on_new_document())
      return FALSE;

   update_all_views(NULL, 0);

   return TRUE;
}

devedgeFrontDoc::~devedgeFrontDoc()
{
}


#ifdef _DEBUG
void devedgeFrontDoc::assert_valid() const
{
   html_document::assert_valid();
}

void devedgeFrontDoc::dump(dump_context & dumpcontext) const
{
   html_document::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// devedgeFrontDoc serialization

/*
void devedgeFrontDoc::Serialize(CArchive& ar)
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

bool devedgeFrontDoc::on_open_document(var varFile)
{
   UNREFERENCED_PARAMETER(varFile);
   //if(m_file.IsOpened())
     // m_file.close();
   //if(!m_file.open(lpszPathName, ::ex1::file::type_binary | ::ex1::file::mode_read_write))
     // return FALSE;
   return TRUE;
}


BOOL devedgeFrontDoc::on_save_document(const char * lpszPathName)
{
   UNREFERENCED_PARAMETER(lpszPathName);
   return TRUE;
}

void devedgeFrontDoc::OnUpdateStart(cmd_ui *pcmdui)
{
   pcmdui->Enable(TRUE);
}

void devedgeFrontDoc::OnUpdateEditUndo(cmd_ui *pcmdui)
{
   UNREFERENCED_PARAMETER(pcmdui);
}

void devedgeFrontDoc::OnUpdateEditRedo(cmd_ui *pcmdui)
{
   UNREFERENCED_PARAMETER(pcmdui);
}

void devedgeFrontDoc::OnStart()
{
   open_document("http://localhost:10011/");
}

void devedgeFrontDoc::OnEditUndo()
{
}

void devedgeFrontDoc::OnEditRedo()
{
}



void devedgeFrontDoc::get_output(const char * lpcsz, string & strHead, gen::memory_file & file)
{
   UNREFERENCED_PARAMETER(lpcsz);
   UNREFERENCED_PARAMETER(strHead);
   file = m_memfileBody;
}

