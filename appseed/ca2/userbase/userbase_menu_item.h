#pragma once


namespace userbase
{

   class menu_item_ptra;

   class CLASS_DECL_ca2 menu_item :
      virtual public ::ca::object
   {
   public:


      id                   m_id;
      sp(menu_item_ptra)   m_spitema;
      int32_t                  m_iFullHeightItemCount;
      int32_t                  m_iSeparatorCount;
      menu_button          m_button;
      bool                 m_bPopup;
      int32_t                  m_iLevel;
      menu_base *          m_pbase;


      menu_item(::ca::application * papp);
      virtual ~menu_item();


      void add_item(menu_item * pitem);
      bool create_menu(const stringa & straCommand, const stringa & straCommandTitle);
      bool load_menu(xml::node * lpnode);
      bool load_menu(xml::node * lpnode, int32_t iLevel);

      virtual void OnAddRef();
      virtual void OnRelease();

      bool IsPopup();
      menu_item * find(id id);


   };

   class CLASS_DECL_ca2 menu_item_ptra :
      public array_app_alloc < menu_item >
   {
   public:
      
      
      menu_item *    m_pitemContainer;


      menu_item_ptra(menu_item * pitemContainer);
      virtual ~menu_item_ptra();


      menu_item * find(id id);

   };

} // namespace userbase