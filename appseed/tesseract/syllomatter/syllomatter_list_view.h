#pragma once

class syllomatter_pane_view;
class svn_view;

class CLASS_DECL_CA2_TESSERACT syllomatter_list_view :
   public simple_list_view
{
public:


   class CLASS_DECL_CA2_TESSERACT update_thread : public simple_thread
   {
   public:
      update_thread(::ca::application * papp);
      syllomatter_list_view * m_plistview;
      ::fs::item_array m_itema;
      int run();
   };

   class CLASS_DECL_CA2_TESSERACT commit_thread : public simple_thread
   {
   public:
      commit_thread(::ca::application * papp);
      syllomatter_list_view * m_plistview;
      stringa m_stra;
      int run();
   };

   stringa m_straStatus;
   stringa m_stra;

   update_thread m_updatethread;
   commit_thread m_committhread;

   ::user::list_cache               m_cache;
   simple_list_header_control       m_headerctrl;
   ::fs::item_array       m_itema;
   syllomatter_pane_view *    m_ppaneview;
   svn_view *                 m_psvnview;


   syllomatter_list_view(::ca::application * papp);
   virtual ~syllomatter_list_view();


   virtual void install_message_handling(::user::win::message::dispatch * pinterface);


   virtual void Commit_(::fs::item_array & itema);
   virtual void Update(::fs::item_array & itema);

   static void Commit_Swap(LPVOID lparg, index dwa, index dwb);
   static index CompareStatus(LPVOID lparg, index dwa, index dwb);
   static index ComparePath(LPVOID lparg, index dwa, index dwb);

   virtual INT_PTR _001GetItemCount();
   virtual void _001GetItemText(::user::list_item * pitem);

   static index StatusSortWeight(string & strStatus);

   virtual void _001GetItemColor(::user::list_item * pitem);


   void _001GetItemImage(::user::list_item * pitem);

   

   

   void _001InsertColumns();

   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnGeneralEvent)
   
   DECL_GEN_SIGNAL(_001OnAdd)
   DECL_GEN_SIGNAL(_001OnUpdateAdd)
   DECL_GEN_SIGNAL(_001OnDelete)
   DECL_GEN_SIGNAL(_001OnUpdateDelete)
   DECL_GEN_SIGNAL(_001OnRevert)
   DECL_GEN_SIGNAL(_001OnUpdateRevert)
   DECL_GEN_SIGNAL(_001OnCommit)
   DECL_GEN_SIGNAL(_001OnUpdateCommit)
   DECL_GEN_SIGNAL(_001OnVerisvnwellListMessage)

   
};
