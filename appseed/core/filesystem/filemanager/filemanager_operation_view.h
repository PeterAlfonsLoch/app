#pragma once


class file_manager_operation_list_view;
class file_manager_operation_info_view;


class CLASS_DECL_CORE file_manager_operation_view :
   public ::user::split_view
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


   file_manager_operation_list_view * m_plistview;
   file_manager_operation_info_view * m_pinfoview;

   ::user::view_creator * m_pviewcreator;


   file_manager_operation_view(sp(base_application) papp);
   virtual ~file_manager_operation_view();

   sp(file_manager_operation_document) get_document();

   virtual void install_message_handling(::message::dispatch * pinterface);

   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnMainPostMessage);
   DECL_GEN_SIGNAL(_001OnDestroy);



};


