#pragma once

namespace winactionarea
{

   class CLASS_DECL_CA2_WINACTIONAREA menu_right_view :
      public simple_list_view
   {
   public:
      menu_right_view(::ca::application * papp);

      class cpl_program
      {
      public:
         int      m_iImage;
         int      m_iIndex;
         string   m_strApplet;
         string   m_strName;
         string   m_strDescription;
      };


      count _001GetItemCount();

      array_ptr_alloc < cpl_program > m_cpla;
      image_list                    m_il;

      virtual void _001GetItemImage(::user::list_item * pitem);
      virtual void _001GetItemText(::user::list_item * pitem);

      void _001OnClick(UINT nFlags, point point) ;

      DECL_GEN_SIGNAL(_001OnCreate);

      virtual void _001InsertColumns();

      void install_message_handling(::user::win::message::dispatch * pinterface);

   };

} // namespace winactionarea