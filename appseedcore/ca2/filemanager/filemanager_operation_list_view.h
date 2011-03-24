#pragma once



class CLASS_DECL_ca file_manager_operation_list_view :
   virtual public ::userbase::view,
   virtual public ::user::list
{
public:

   file_manager_operation_list_view(::ca::application * papp);

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

   void _001InsertColumns();

   virtual void OnDraw(::ca::graphics * pdc);

   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnTimer)

   virtual count _001GetItemCount();
   virtual bool _001GetItemText(
      string &str,
      index iItem,
      index iSubItem, 
      index iListItem);

   void OnFileOperationStep(int iOperation, bool bFinal);

   ::user::list_cache              m_cache;
   simple_list_header_control    m_headerctrl;
   simple_scroll_bar             m_scrollbarVert;
   simple_scroll_bar             m_scrollbarHorz;

   DECL_GEN_SIGNAL(_001OnInitialUpdate)

   DWORD                   m_dwLast123Update;

   

   void on_update(::view * pSender, LPARAM lHint, ::radix::object * pHint);
   file_manager_operation_document * get_document();
};
      