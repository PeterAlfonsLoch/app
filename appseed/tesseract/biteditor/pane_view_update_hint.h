#pragma once

namespace biteditor
{

   enum e_pane_view
   {
      pane_view_none = -1,
      pane_view_context_menu = 0,
      pane_view_bit_editor,
      pane_view_file_manager,
   };


   class _declspec(dllexport) pane_view_update_hint :
      public ::radix::object  
   {
   public:
      enum e_type
      {
         TypeGetView,
         TypeSetView,
         TypeOnShowKaraoke,
         TypeOnBeforeShowView,
         TypeOnShowView,
      };
      
   public:
      void set_type(e_type e_type);
      bool is_type_of(e_type e_type);

      pane_view_update_hint();
      virtual ~pane_view_update_hint();

      e_pane_view m_eview;
   protected:
      e_type m_etype;

   };

} // namespace biteditor