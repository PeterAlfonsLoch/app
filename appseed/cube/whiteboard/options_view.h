#pragma once


namespace whiteboard
{

   class CLASS_DECL_CA2_CUBE options_view : public form_view
   {
   public:
      options_view(::ca::application * papp);
      virtual ~options_view();

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   //protected:
//      virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

      document * get_document();

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 
      virtual void OnInitialUpdate();
      void OnEnChangeEditNick();
      void OnEnChangeEditPassword();

      // linux simple_combo_box m_comboSiteTag;
      afx_msg void OnCbnSelchangeComboSiteTag();
      // linux user::edit_plain_text m_editSiteUrl;
      afx_msg void OnEnChangeEditSiteUrl();
      afx_msg void OnBnClickedCheckShowTrayIconMrts();
      afx_msg void OnBnClickedCheckShowCalendarTrayIcon();
      afx_msg void OnBnClickedCheckShowTrayIconMrtsQuerylist();
   };


   #ifndef _DEBUG
   inline document * options_view::get_document()
   {
      return dynamic_cast < document * > (::view::get_document());
   }
   #endif

} // namespace whiteboard