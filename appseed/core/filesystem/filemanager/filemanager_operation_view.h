#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE operation_view:
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


      sp(operation_list_view)    m_plistview;
      sp(operation_info_view)    m_pinfoview;

      ::user::view_creator *     m_pviewcreator;


      operation_view(sp(::aura::application) papp);
      virtual ~operation_view();

      sp(operation_document) get_document();

      virtual void install_message_handling(::message::dispatch * pinterface);

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnMainPostMessage);
      DECL_GEN_SIGNAL(_001OnDestroy);


   };


} // namespace filemanager













