#pragma once

class file_manager_operation_list_view;
class file_manager_operation_info_view;

class CLASS_DECL_ca file_manager_operation_view :
   public ::userbase::split_view
{
public:

   enum e_message
   {
      MessageMainPost = WM_USER + 23,
   };
   enum EMessageMainPost
   {
      MessageMainPostFileOperation,
      MessageMainPostFileOperationFinal,
   };

   file_manager_operation_view(::ca::application * papp);
   virtual ~file_manager_operation_view();

   file_manager_operation_document * get_document();

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
   
   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnMainPostMessage)
   DECL_GEN_SIGNAL(_001OnDestroy)


   file_manager_operation_list_view * m_plistview;
   file_manager_operation_info_view * m_pinfoview;

   ::user::create_view * m_pcreateview;

};
      