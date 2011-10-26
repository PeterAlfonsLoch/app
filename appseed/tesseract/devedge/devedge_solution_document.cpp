#include "StdAfx.h"

namespace devedge
{

   solution_document::solution_document(::ca::application * papp) :
      ca(papp),
      data_container(papp),
      ::document(papp),
      ::userbase::document(papp),
      m_file(papp),
      m_fileSave(papp),
      m_projecta(papp),
      m_node(papp)
   {
      m_pview = NULL;
      m_iBranch = 0;

      string str = unitext("Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
      str += "Assinado Camilo Sasuke Tsumanuma.";
      str += "Visible or Note?";

      //command_signalid id;
      //gen::signalid * pid;


      /*id.m_id = System.id("edit_undo";
      pid = m_signalidaCommand.get(&id);
      id.m_id = "edit_redo";
      pid = m_signalidaCommand.get(&id);
      id.m_id = "file_save";
      pid = m_signalidaCommand.get(&id);*/
      connect_update_cmd_ui("file_save", &solution_document::_001OnUpdateFileSave);
      connect_command("file_save", &solution_document::_001OnFileSave);
      connect_update_cmd_ui("edit_cut", &solution_document::_001OnUpdateEditCut);
      connect_command("edit_cut", &solution_document::_001OnEditCut);
      connect_update_cmd_ui("edit_copy", &solution_document::_001OnUpdateEditCopy);
      connect_command("edit_copy", &solution_document::_001OnEditCopy);
      connect_update_cmd_ui("edit_paste", &solution_document::_001OnUpdateEditPaste);
      connect_command("edit_paste", &solution_document::_001OnEditPaste);
      connect_command("file_new", &solution_document::_001OnFileNew);
      connect_update_cmd_ui("file_new", &solution_document::_001OnUpdateFileNew);
   }



   BOOL solution_document::on_new_document()
   {
      if (!::userbase::document::on_new_document())
         return FALSE;

      set_path_name(System.file().time_square());
      if(m_file->IsOpened())
         m_file->close();
      if(!m_file->open(get_path_name(), ::ex1::file::type_binary | ::ex1::file::mode_read_write |
         ::ex1::file::shareDenyNone))
         return FALSE;

      update_all_views(NULL, 11);

      return TRUE;
   }

   solution_document::~solution_document()
   {
   }


 
   #ifdef _DEBUG
   void solution_document::assert_valid() const
   {
      ::userbase::document::assert_valid();
   }

   void solution_document::dump(dump_context & dumpcontext) const
   {
      ::userbase::document::dump(dumpcontext);
   }
   #endif //_DEBUG


   bool solution_document::on_open_document(var varFile)
   {
      //if(!::userbase::document::on_open_document(varFile))
        // return FALSE;
      if(!m_node.load(Application.file().as_string(varFile)))
         return FALSE;
      set_path_name(varFile);
      m_pview = get_typed_view < solution_view > ();
      m_pview->load();
      return TRUE;
   }

   void solution_document::reload()
   {
      if(m_file->IsOpened())
         m_file->close();
      if(!m_file->open(get_path_name(), ::ex1::file::type_binary | ::ex1::file::mode_read_write |
         ::ex1::file::shareDenyNone))
         return;
      update_all_views(NULL, 123);
   }


   BOOL solution_document::on_save_document(const char * lpszPathName)
   {
      if(!m_fileSave->open(lpszPathName, ::ex1::file::type_binary | ::ex1::file::mode_read_write | ::ex1::file::mode_create))
         return FALSE;
      update_all_views(NULL, 12345);
      return TRUE;
   }

   void solution_document::_001OnUpdateFileSave(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(TRUE);
   }

   void solution_document::_001OnUpdateFileNew(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(TRUE);
   }

   void solution_document::_001OnUpdateFilePut(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(TRUE);
   }


   void solution_document::_001OnUpdateEditCut(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(TRUE);
   }

   void solution_document::_001OnUpdateEditCopy(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(TRUE);
   }

   void solution_document::_001OnUpdateEditPaste(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(TRUE);
   }

   void solution_document::_001OnFileSave(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::userbase::document::on_file_save();
   }

   void solution_document::_001OnFileNew(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::userbase::document::on_new_document();
   }

   void solution_document::_001OnEditCut(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void solution_document::_001OnEditCopy(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void solution_document::_001OnEditPaste(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void solution_document::_001OnFilePut(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::userbase::document::on_file_save();
      Put();
   }




   void solution_document::Put()
   {
      string strVotagusFolder;
      System.dir().votagus(strVotagusFolder);
      string strCommon;
      string strRemote;
      strCommon = System.dir().path(strVotagusFolder, "seed\\ca2\\fontopus\\net\\ds\\common");
      if(strCommon.CompareNoCase(get_path_name().Mid(0, strCommon.get_length())) == 0)
      {
         strCommon = get_path_name().Mid(strCommon.get_length());
         strCommon.replace("\\", "/");
         strRemote = "seed/ca2/fontopus/net/ds/common" + strCommon;
         FtpPut(get_path_name(), strRemote);
      }
   }

   void solution_document::FtpPut(const char * lpcszLocal, const char * lpcszRemote)
   {
      UNREFERENCED_PARAMETER(lpcszLocal);
      UNREFERENCED_PARAMETER(lpcszRemote);
      throw not_implemented_exception();
   /*   CInternetSession sess("MyProgram/1.0");

      CFtpConnection* pConnect = NULL;

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

   xml::node * solution_document::node_get_projects()
   {
      return m_node.get_child("projects");
   }




} // namespace devedge