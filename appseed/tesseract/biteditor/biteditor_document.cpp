#include "StdAfx.h"
#include "biteditor_document.h"


biteditor_document::biteditor_document(::ca::application * papp) :
   ca(papp),
   data_container(papp),
   ::document(papp),
   ::userbase::document(papp),
   m_memfile(papp),
   ex1::tree_data(papp),
   ::ca::data(papp),
   ex1::tree(papp)
{
   m_iBranch = 0;
   m_pgroupcommand = NULL;

   if(!ex1::tree_data::initialize_data())
      throw simple_exception();

   m_ptreeitem = get_base_item();

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
   m_memfile.write(str, str.get_length());
   m_pfile = &m_memfile;
   m_peditfile = new ex1::edit_file(get_app());
   m_peditfile->SetFile(m_pfile);

   /*box.m_strText = "Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!";
   box.m_pt.x = 20;
   box.m_pt.y = 80;
   m_plaintextboxa.add(box);
   m_elementptraVisible.add(&m_plaintextboxa[1]);
   box.m_strText = "Assinado Camilo Sasuke Tsumanuma.";
   box.m_pt.x = 20;
   box.m_pt.y = 110;
   m_plaintextboxa.add(box);
   m_elementptraVisible.add(&m_plaintextboxa[2]);
   box.m_strText = "Visible or Note?";
   box.m_pt.x = 20;
   box.m_pt.y = 200;
   m_plaintextboxa.add(box);*/
   //m_elementptraVisible.add(&m_plaintextboxa[3]);

   connect_update_cmd_ui("edit_undo", &biteditor_document::_001OnUpdateEditUndo);
   connect_command("edit_undo", &biteditor_document::_001OnEditUndo);
   connect_update_cmd_ui("edit_redo", &biteditor_document::_001OnUpdateEditRedo);
   connect_command("edit_redo", &biteditor_document::_001OnEditRedo);
   connect_update_cmd_ui("file_save", &biteditor_document::_001OnUpdateFileSave);
   connect_command("file_save", &biteditor_document::_001OnFileSave);
   connect_update_cmd_ui("edit_cut", &biteditor_document::_001OnUpdateEditCut);
   connect_command("edit_cut", &biteditor_document::_001OnEditCut);
   connect_update_cmd_ui("edit_copy", &biteditor_document::_001OnUpdateEditCopy);
   connect_command("edit_copy", &biteditor_document::_001OnEditCopy);
   connect_update_cmd_ui("edit_paste", &biteditor_document::_001OnUpdateEditPaste);
   connect_command("edit_paste", &biteditor_document::_001OnEditPaste);

}

bool biteditor_document::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)  
{
/*   gen::application * papp = gen::get_app();
   CommandIdSpace idspace;
   if (nCode == CN_UPDATE_COMMAND_UI)
   {
      cmd_ui * pcmdui = (cmd_ui *) pExtra;
      if(nID == papp->GetResourceId(idspace, "file_save"))
      {
         OnUpdateFileSave(pcmdui);
         return TRUE;
      }
      else if(nID == papp->GetResourceId(idspace, "edit_undo"))
      {
         OnUpdateEditUndo(pcmdui);
         return TRUE;
      }
      else if(nID == 1003)
      {
         OnUpdateEditRedo(pcmdui);
         return TRUE;
      }
      else if(nID == 1004)
      {
         OnUpdateFilePut(pcmdui);
         return TRUE;
      }
   }
   else
   {
      int nMsg = HIWORD(nCode);
      nCode = LOWORD(nCode);

      // for backward compatibility HIWORD(nCode)==0 is WM_COMMAND
      if (nMsg == 0)
         nMsg = WM_COMMAND;

      if(nMsg == WM_COMMAND)
      {
         if(nID == 1001)
         {
            on_file_save();
            return TRUE;
         }
         else if(nID == 1002)
         {
            OnEditUndo();
            return TRUE;
         }
         else if(nID == 1003)
         {
            OnEditRedo();
            return TRUE;
         }
         else if(nID == 1004)
         {
            OnFilePut();
            return TRUE;
         }
      }
   }*/
   return ::userbase::document::_001OnCmdMsg(pcmdmsg);
}


BOOL biteditor_document::on_new_document()
{
   if (!::userbase::document::on_new_document())
      return FALSE;

   update_all_views(NULL, 0);

   return TRUE;
}

biteditor_document::~biteditor_document()
{
}



#ifdef _DEBUG
void biteditor_document::assert_valid() const
{
   ::userbase::document::assert_valid();
}

void biteditor_document::dump(dump_context & dumpcontext) const
{
   ::userbase::document::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// biteditor_document serialization

/*
void biteditor_document::Serialize(CArchive& ar)
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


void biteditor_document::data_on_after_change(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
}

bool biteditor_document::on_open_document(var varFile)
{

   ex1::filesp spfile;
   m_pfile = spfile;
   m_bReadOnly = false;
   spfile(Application.get_file(varFile, ::ex1::file::type_binary | ::ex1::file::mode_read_write | ::ex1::file::shareDenyNone));
   if(spfile.is_null())
   {
      m_bReadOnly = true;
      spfile(Application.get_file(varFile, ::ex1::file::type_binary | ::ex1::file::mode_read | ::ex1::file::shareDenyNone));
      if(spfile.is_null())
         return FALSE;
   }
   m_peditfile->SetFile(m_pfile);
   return TRUE;

}

void biteditor_document::reload()
{
   if(m_pfile != &m_memfile)
   {
      if(m_pfile->IsOpened())
         m_pfile->close();
      if(!m_pfile->open(get_path_name(), ::ex1::file::type_binary | ::ex1::file::mode_read_write |
         ::ex1::file::shareDenyNone))
         return;
   }
   m_peditfile->SetFile(m_pfile);
   update_all_views(NULL);
}


BOOL biteditor_document::on_save_document(const char * lpszPathName)
{
   UNREFERENCED_PARAMETER(lpszPathName);
   m_peditfile->Flush();
   return TRUE;
}

void biteditor_document::_001OnUpdateFileSave(gen::signal_object * pobj)
{
   SCAST_PTR(base_cmd_ui, pcmdui, pobj)
   pcmdui->m_pcmdui->Enable(TRUE);
}

void biteditor_document::_001OnUpdateFilePut(gen::signal_object * pobj)
{
   SCAST_PTR(base_cmd_ui, pcmdui, pobj)
   pcmdui->m_pcmdui->Enable(TRUE);
}

void biteditor_document::_001OnUpdateEditUndo(gen::signal_object * pobj)
{
   SCAST_PTR(base_cmd_ui, pcmdui, pobj)
   pcmdui->m_pcmdui->Enable(m_peditfile->CanUndo());
}

void biteditor_document::_001OnUpdateEditRedo(gen::signal_object * pobj)
{
   SCAST_PTR(base_cmd_ui, pcmdui, pobj)
   pcmdui->m_pcmdui->Enable(m_peditfile->GetRedoBranchCount() > 0);
}

void biteditor_document::_001OnUpdateEditCut(gen::signal_object * pobj)
{
   SCAST_PTR(base_cmd_ui, pcmdui, pobj)
   pcmdui->m_pcmdui->Enable(TRUE);
}

void biteditor_document::_001OnUpdateEditCopy(gen::signal_object * pobj)
{
   SCAST_PTR(base_cmd_ui, pcmdui, pobj)
   pcmdui->m_pcmdui->Enable(TRUE);
}

void biteditor_document::_001OnUpdateEditPaste(gen::signal_object * pobj)
{
   SCAST_PTR(base_cmd_ui, pcmdui, pobj)
   pcmdui->m_pcmdui->Enable(TRUE);
}

void biteditor_document::_001OnFileSave(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   ::userbase::document::on_file_save();
}

void biteditor_document::_001OnEditCut(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
}

void biteditor_document::_001OnEditCopy(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
}

void biteditor_document::_001OnEditPaste(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
}

void biteditor_document::_001OnFilePut(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   ::userbase::document::on_file_save();
   Put();
}

void biteditor_document::_001OnEditUndo(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   Undo();
}

void biteditor_document::_001OnEditRedo(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   Redo();
}

void biteditor_document::MacroRecord(Command * pcommand)
{
   if(m_pgroupcommand != NULL
     && m_pgroupcommand != pcommand)
   {
      m_pgroupcommand->add(pcommand);
      return;
   }
   if(m_ptreeitem->get_expandable_children_count() > 0 && m_iBranch < m_ptreeitem->get_expandable_children_count())
   {
      m_ptreeitem = m_ptreeitem->get_expandable_child(m_iBranch);
   }
   ex1::tree_item * pitem = insert_item(pcommand, ex1::RelativeLastSibling, m_ptreeitem);
   if(pitem != NULL)
   {
      m_ptreeitem = pitem;
   }

}


bool biteditor_document::CanUndo()
{
   return m_ptreeitem != get_base_item();
}


int biteditor_document::GetRedoBranchCount()
{
   return m_ptreeitem->get_expandable_children_count() 
        + (m_ptreeitem->m_pnext != NULL ? 1 : 0)
        + (m_ptreeitem->m_pchild != NULL ? 1 : 0);
}

bool biteditor_document::Undo()
{
   if(!CanUndo())
      return false;

   Command * pcommand = (Command *) m_ptreeitem->m_pitemdata;
   pcommand->Undo(this);
   m_ptreeitem = m_ptreeitem->get_previous();
   update_all_views(NULL, 789231, NULL);
   return true;
}
bool biteditor_document::Redo()
{
   if(m_iBranch < 0
      || m_iBranch >= GetRedoBranchCount())
   {
      return false;
   }
   Command * pcommand = NULL;
   ::ex1::tree_item * ptreeitem;
   if(m_iBranch < m_ptreeitem->get_expandable_children_count())
   {
      ptreeitem = m_ptreeitem->get_expandable_child(m_iBranch);
   }
   else if(m_ptreeitem->m_pnext != NULL)
   {
      ptreeitem = m_ptreeitem->m_pnext;
   }
   else
   {
      ptreeitem = m_ptreeitem->m_pchild;
   }
   if(ptreeitem == NULL)
      return true;
   m_ptreeitem = ptreeitem;
   pcommand = (Command *) ptreeitem->m_pitemdata;
   pcommand->Redo(this);
   update_all_views(NULL, 789231, NULL);
   return true;
}

void biteditor_document::MacroBegin()
{
   GroupCommand * pgroupcommand = new GroupCommand;
   pgroupcommand->m_pparent = m_pgroupcommand;
   m_pgroupcommand = pgroupcommand;
}

void biteditor_document::MacroEnd()
{
   if(m_pgroupcommand == NULL)
   {
      ASSERT(FALSE);
      return;
   }
   if(m_pgroupcommand->m_pparent == NULL)
   {
      MacroRecord(m_pgroupcommand);
   }
   m_pgroupcommand = m_pgroupcommand->m_pparent;
}


void biteditor_document::SetSelCommand::Undo(biteditor_document * pdoc)
{
   pdoc->m_iSelStart = m_iPreviousSelStart;
   pdoc->m_iSelEnd = m_iPreviousSelEnd;
   pdoc->update_all_views(NULL, 789232, NULL);
}
void biteditor_document::SetSelCommand::Redo(biteditor_document * pdoc)
{
   pdoc->m_iSelStart = m_iSelStart;
   pdoc->m_iSelEnd = m_iSelEnd;
   pdoc->update_all_views(NULL, 789232, NULL);
}

void biteditor_document::FileCommand::Undo(biteditor_document * pdoc)
{
   pdoc->m_peditfile->Undo();
   pdoc->update_all_views(0, 1001, NULL);
}

void biteditor_document::FileCommand::Redo(biteditor_document * pdoc)
{
   pdoc->m_peditfile->Redo();
   pdoc->update_all_views(0, 1001, NULL);
}


void biteditor_document::GroupCommand::Undo(biteditor_document * pdoc)
{
   for(int i = get_upper_bound(); i >= 0; i--)
   {
      element_at(i)->Undo(pdoc);
   }
}
void biteditor_document::GroupCommand::Redo(biteditor_document * pdoc)
{
   for(int i = 0; i < get_size(); i++)
   {
      element_at(i)->Redo(pdoc);
   }
}

void biteditor_document::Put()
{
   string strVotagusFolder;
   System.dir().votagus(strVotagusFolder);
   string strCommon;
   string strRemote;
   strCommon = System.dir().path(strVotagusFolder, "cast\\seed\\ca2\\fontopus\\net\\ds\\common");
   if(strCommon.CompareNoCase(get_path_name().Mid(0, strCommon.get_length())) == 0)
   {
      strCommon = get_path_name().Mid(strCommon.get_length());
      strCommon.replace("\\", "/");
      strRemote = "cast/seed/ca2/fontopus/net/ds/common" + strCommon;
      FtpPut(get_path_name(), strRemote);
   }
}

void biteditor_document::FtpPut(const char * lpcszLocal, const char * lpcszRemote)
{
   UNREFERENCED_PARAMETER(lpcszLocal);
   UNREFERENCED_PARAMETER(lpcszRemote);
   throw not_implemented_exception();

//   CInternetSession sess("MyProgram/1.0");

  /* CFtpConnection* pConnect = NULL;

    try
    {
        // Request a connection to ftp.microsoft.com. Default
        // parameters mean that we'll try with username = ANONYMOUS
        // and password set to the machine name @ domain name
        pConnect = sess.GetFtpConnection("votagus.net", "votagus", "1p.t5mL.1..");

        pConnect->PutFile(lpcszLocal, lpcszRemote);

    }
    catch (CInternetException* pEx)
    {
        string str;
        pEx->GetErrorMessage(str);
        printf_s("ERROR!  %s\n", str);
        pEx->Delete();
     }

    // if the connection is open, close it
    if (pConnect != NULL) 
    {
        pConnect->close();
        delete pConnect;
    }
*/
}


ex1::tree_item_data * biteditor_document::on_allocate_item()
{
   return new Command;
}

void biteditor_document::on_delete_item(ex1::tree_item_data * pitem)
{
   delete (Command *) pitem;
}
