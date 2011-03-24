#pragma once

namespace flag
{

   class CLASS_DECL_CA2_FLAG menu_right_view :
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

      index _001GetItemImage(index iItem, index iSubItem, index iListItem);
      virtual bool _001GetItemText(string &str, index iItem, index iSubItem, index iListItem);

      void _001OnClick(UINT nFlags, point point) ;

      DECL_GEN_SIGNAL(_001OnCreate);

      virtual void _001InsertColumns();

      void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

   };

} // namespace flag