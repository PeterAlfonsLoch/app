#pragma once


namespace user
{


   class menu_base_item;


   class CLASS_DECL_BASE menu_base :
      virtual public ::database::user::interaction
   {
   public:


      sp(menu_base_item)      m_pitem;

      sp(menu_base) *         m_pmenubaseThis;


      menu_base(sp(base_application) papp);
      virtual ~menu_base();


      virtual void install_message_handling(::message::dispatch * pdispatch);


      bool create_menu(const stringa & straCommand, const stringa & straCommandTitle);
      bool LoadMenu(sp(::xml::node) lpnode);
      bool LoadXmlMenu(const char * pszMatter);


      virtual void clear();
      virtual void layout() = 0;


      virtual bool TrackPopupMenu(int32_t iFlags, int32_t x, int32_t y, sp(::user::interaction) oswindowParent, sp(menu_base) * pthis);


      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnDestroy);



   };


} // namespace user



