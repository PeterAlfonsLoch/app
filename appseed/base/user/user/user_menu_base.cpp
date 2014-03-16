#include "framework.h"


namespace user
{


   menu_base::menu_base(sp(base_application) papp):
      element(papp)
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

   bool menu_base::create_menu(const stringa & straCommand, const stringa & straCommandTitle)
   {

      return m_pitem->create_menu(straCommand, straCommandTitle);

   }

   bool menu_base::LoadMenu(sp(::xml::node) lpnode)
   {

      return m_pitem->load_menu(lpnode);

   }

   bool menu_base::LoadXmlMenu(const char * pszMatter)
   {


      xml::document doc(get_app());

      doc.load(Application.file().as_string(Application.dir().matter(pszMatter)));

      return LoadMenu(doc.get_root());


   }


} // namespace user



