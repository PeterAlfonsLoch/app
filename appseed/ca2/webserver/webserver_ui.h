#pragma once


namespace webserver
{


   class CLASS_DECL_ca ui_nav_item : 
      virtual public dynamic_source::ptr
   {
   public:


      bool     m_bEnable;
      bool     m_bCurrent;
      string   m_strLink;
      string   m_strTitle;


   };

   class CLASS_DECL_ca ui_nav : 
      virtual public dynamic_source::ptr_array < ui_nav_item >
   {
   public:

   };


   class CLASS_DECL_ca ui_menu : 
      virtual public dynamic_source::ptr_array < ui_menu >
   {
   public:


      string   m_strTitle;
      string   m_strLink;
      string   m_strId;


      virtual ~ui_menu();
      ui_menu(const char * pszTitle = NULL, const char * pszLink = NULL, const char * pszId = NULL);

   };


   class CLASS_DECL_ca user : 
      public dynamic_source::ptr
   {
   public:


      void veriwell_ws_print_menu(var name, var title, ui_menu * pmenu);
      void veriwell_printOutNav1(var linka, var titlea);
      void karaoke_printOutTabNav1(ui_nav * pnav);
      void karaoke_printOutTabNav5(ui_nav * pnav);
      void karaoke_printOutTabNav2(ui_nav * pnav);
      void karaoke_printOutTabNav70(ui_nav * pnav);


   };


} // namespace webserver

