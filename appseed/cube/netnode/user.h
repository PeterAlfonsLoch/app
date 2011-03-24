#pragma once

class CLASS_DECL_CA2_CUBE ui_nav_item : public ptr
{
public:
   bool     m_bEnable;
   bool     m_bCurrent;
   string   m_strLink;
   string   m_strTitle;
};

class CLASS_DECL_CA2_CUBE ui_nav : public ptr_array < ui_nav_item >
{
public:

};


class CLASS_DECL_CA2_CUBE ui_menu : public ptr_array < ui_menu >
{
public:

   virtual ~ui_menu();
   ui_menu(
      const char * pszTitle = NULL, 
      const char * pszLink = NULL, 
      const char * pszId = NULL);

   string   m_strTitle;
   string   m_strLink;
   string   m_strId;
};

namespace netnode
{

   class CLASS_DECL_CA2_CUBE user : 
      public ptr
   {
   public:
      void veriwell_ws_print_menu(var name, var title, ui_menu * pmenu);
      void veriwell_printOutNav1(var linka, var titlea);
      void karaoke_printOutTabNav1(ui_nav * pnav);
      void karaoke_printOutTabNav5(ui_nav * pnav);
      void karaoke_printOutTabNav2(ui_nav * pnav);
      void karaoke_printOutTabNav70(ui_nav * pnav);
   };

} // namespace netnode

   