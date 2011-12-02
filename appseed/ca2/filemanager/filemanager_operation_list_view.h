#pragma once



class CLASS_DECL_ca file_manager_operation_list_view :
   virtual public ::userbase::view,
   virtual public ::user::list
{
public:

   file_manager_operation_list_view(::ax::application * papp);

   virtual void install_message_handling(::gen::message::dispatch * pinterface);

   void _001InsertColumns();

   virtual void OnDraw(::ax::graphics * pdc);

   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnTimer)

   virtual count _001GetItemCount();
   virtual void _001GetItemText(::user::list_item * pitem);

   void OnFileOperationStep(int iOperation, bool bFinal);

   ::user::list_cache               m_listcache;
   simple_list_header_control       m_headerctrl;

   DECL_GEN_SIGNAL(_001OnInitialUpdate)

   DWORD                            m_dwLast123Update;

   

   void on_update(::view * pSender, LPARAM lHint, ::radix::object * pHint);
   file_manager_operation_document * get_document();
};
      