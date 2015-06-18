#pragma once


namespace filehandler
{


   enum EPaneView
   {
      pane_view_none,
      pane_view_new
   };


   class CLASS_DECL_SPHERE pane_view_update_hint :
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
   
   public:
      void set_type(e_type e_type);
      bool is_type_of(e_type e_type);

      pane_view_update_hint();
      virtual ~pane_view_update_hint();

      EPaneView m_eview;
   protected:
      e_type m_etype;

   };


} // namespace filehandler


