#include "StdAfx.h"

namespace userbase
{

   menu_base::menu_base(::ca::application * papp):
      ca(papp)
   {
      m_pitem = new menu_item(papp);
   }

   menu_base::~menu_base()
   {
   }

   void menu_base::clear()
   {
      m_pitem = new menu_item(get_app());
   }

   bool menu_base::LoadMenu(xml::node * lpnode)
   {
      return m_pitem->load_menu(lpnode);
   }

   bool menu_base::LoadXmlMenu(const char * pszMatter)
   {
      xml::node node(get_app());
      node.load(Application.file().as_string(System.dir().matter(pszMatter)));
      return LoadMenu(&node);
   }

} // namespace userbase