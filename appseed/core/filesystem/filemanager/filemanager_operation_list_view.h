#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE operation_list_view:
      virtual public ::user::impact,
      virtual public ::user::list
   {
   public:


      ::user::list_cache               m_listcache;
      simple_list_header_control       m_headerctrl;
      uint32_t                         m_dwLast123Update;


      operation_list_view(sp(::base::application) papp);

      virtual void install_message_handling(::message::dispatch * pinterface);

      void _001InsertColumns();

      virtual void OnDraw(::draw2d::graphics * pdc);

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnTimer);

      virtual count _001GetItemCount();
      virtual void _001GetItemText(::user::list_item * pitem);

      void OnFileOperationStep(int32_t iOperation,bool bFinal);


      DECL_GEN_SIGNAL(_001OnInitialUpdate);

      
      void on_update(sp(::user::impact) pSender,LPARAM lHint,object * pHint);
      sp(operation_document) get_document();


   };


} // namespace filemanager














