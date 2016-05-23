#pragma once


namespace user
{


   class menu_base_item;


   class CLASS_DECL_BASE menu_base :
      virtual public ::user::box
   {
   public:


      sp(menu_base_item)      m_pitem;

      //sp(menu_base) *         m_pmenubaseThis;


      menu_base();
      menu_base(::aura::application * papp);
      menu_base(::aura::application * papp, menu_base_item * pitem);
      virtual ~menu_base();


      virtual void install_message_handling(::message::dispatch * pdispatch);


      bool create_menu(const stringa & straCommand, const stringa & straCommandTitle);
      bool LoadMenu(sp(::xml::node) lpnode);
      bool LoadXmlMenu(const char * pszMatter);


      virtual void clear();
      virtual void layout_menu(point pt) = 0;


      virtual bool TrackPopupMenu(int32_t iFlags, POINT pt, ::user::interaction * oswindowParent);

      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnDestroy);

   };


} // namespace user



