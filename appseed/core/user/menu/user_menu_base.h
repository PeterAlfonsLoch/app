#pragma once

namespace user
{

   class menu_item;

   class CLASS_DECL_CORE menu_base :
      virtual public ::object
   {
   public:


      sp(menu_item)  m_pitem;


      menu_base(sp(base_application) papp);
      virtual ~menu_base();


      bool create_menu(const stringa & straCommand, const stringa & straCommandTitle);
      bool LoadMenu(sp(::xml::node) lpnode);
      bool LoadXmlMenu(const char * pszMatter);


      virtual void clear();
      virtual void layout() = 0;
   };

} // namespace user
