#pragma once


namespace userstack
{

   class CLASS_DECL_sphere pane_view_update_hint :
      public ::object
   {
   public:
      enum e_type
      {
         TypeGetView,
         TypeSetView,
         TypeOnShowKaraoke,
         TypeOnShowView,
      };
      // DECLARE_DYNAMIC(pane_view_update_hint)
   public:
      void set_type(e_type e_type);
      bool is_type_of(e_type e_type);

      pane_view_update_hint();
      virtual ~pane_view_update_hint();

      EPaneView m_eview;
   protected:
      e_type m_etype;

   };


} // namespace userstack



