#pragma once



class CLASS_DECL_CORE file_manager_operation_list_view :
   virtual public ::user::impact,
   virtual public ::user::list
{
public:

   file_manager_operation_list_view(sp(base_application) papp);

   virtual void install_message_handling(::message::dispatch * pinterface);

   void _001InsertColumns();

   virtual void OnDraw(::draw2d::graphics * pdc);

   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnTimer);

   virtual count _001GetItemCount();
   virtual void _001GetItemText(::user::list_item * pitem);

   void OnFileOperationStep(int32_t iOperation, bool bFinal);

   ::user::list_cache               m_listcache;
   simple_list_header_control       m_headerctrl;

   DECL_GEN_SIGNAL(_001OnInitialUpdate);

   uint32_t                            m_dwLast123Update;

   

   void on_update(sp(::user::impact) pSender, LPARAM lHint, object * pHint);
   sp(file_manager_operation_document) get_document();
};
      