#include "StdAfx.h"
#include "filemanager/SimpleFolderTreeView.h"

namespace veiev
{

   second_command_view::second_command_view(::ca::application * papp) :
      ca(papp),
      ::userbase::split_layout(papp),
      ::userbase::view(papp),
      ::userbase::split_view(papp),
      place_holder_container(papp)
   {
   }

   void second_command_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::split_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &second_command_view::_001OnCreate);
   }

   void second_command_view::_001OnCreate(gen::signal_object * pobj)
   {
//      ex1::tree_item * pitem;
//      ex1::simple_tree_item_data * pitemdata;
      pobj->previous();
      if(pobj->m_bRet)
         return;
      application * papp = dynamic_cast < application * > (get_app());
      papp->::veiev::application::m_pmainview = this;
      SetPaneCount(2);
      SetSplitOrientation(orientation_vertical);
      set_position_rate(0, 0.2);
      //create_context cc;

      ::user::interaction* pwnd = create_view(::ca::get_type_info < simple_tree_view > (), get_document(), this, 100);
      SetPane(0, pwnd, false);
      simple_tree_view * ptree = dynamic_cast <simple_tree_view * > (pwnd);
      ptree->m_etranslucency = user::interaction::TranslucencyPresent;

      ::tesseract::mail::document * pdocumentMail = dynamic_cast < ::tesseract::mail::document * > (Application.::tesseract::mail::application::m_ptemplate_html->open_document_file(NULL, FALSE));
      ::tesseract::mail::tree * ptreeMail = pdocumentMail->get_typed_view < ::tesseract::mail::tree >();
      ptree->merge(ptreeMail);


//      ::veiev::application * papp = dynamic_cast < ::veiev::application * > (get_app());

      ::veiev::document * pdocumentVeiev = dynamic_cast < veiev::document * > (papp->m_ptemplateVeiev->open_document_file(NULL, FALSE));
      veiev::tree * ptreeVeiev = pdocumentVeiev->get_typed_view < veiev::tree >();
      ptree->merge(ptreeVeiev);

      //ptreeMail->create_list(pitem);


/*      pitemdata = new ::ex1::simple_tree_item_data;
      pitem = ptree->insert_item(pitemdata, ex1::RelativeLastChild, ptree->get_base_item());
      pitemdata->m_str = "e-mail";

      ptreeMail->create_list(pitem);
      ptree->m_treeptra.add(ptreeMail);*/

      ::filemanager::document * pdoc = (::filemanager::document *) Application.GetStdFileManagerTemplate()->OpenChild(&Application, false, true);

      /*pitemdata = new ::ex1::simple_tree_item_data;
      pitem = ptree->insert_item(pitemdata, ex1::RelativeLastChild, ptree->get_base_item());
      pitemdata->m_str = "computador local";*/

      filemanager::SimpleFolderTreeView * ptreeFile = pdoc->get_typed_view < filemanager::SimpleFolderTreeView > ();
      
      //ptree->merge();
      //ptreeFile->_017UpdateList(NULL, NULL, pitem, 1);
      ptree->merge(ptreeFile);



//      ptree->m_treeptra.add(ptreeFile);

      pwnd = create_view(::ca::get_type_info < veiev::right_split_view > (), get_document(), this, 101);
      SetPane(1, pwnd, false);

      pdocumentMail->m_pholderMailList = get_pane_holder(1);
      pdocumentVeiev->m_pholderVeievList = get_pane_holder(1);
      pdoc->get_filemanager_data()->m_pholderFileList = get_pane_holder(1);
      ///pdoc->get_filemanager_data()->m_ptreeFileTreeMerge = dynamic_cast < ::user::interaction * > (ptree);

   }

   document * second_command_view::get_document()
   {
      return dynamic_cast < document * > (::userbase::split_view::get_document());
   }

   

} // namespace veiev