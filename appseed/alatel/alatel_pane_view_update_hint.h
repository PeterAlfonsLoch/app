#pragma once


namespace alatel
{

   enum e_pane_view
   {
      pane_view_none,
      pane_view_by_weekday,
      pane_view_alarm_test,
   };


   class CLASS_DECL_CA2_ALARM pane_view_update_hint :
      public ::radix::object  
   {
   public:


      enum EType
      {
         TypeGetView,
         TypeSetView,
         TypeOnShowKaraoke,
         TypeOnShowView,
      };

      e_pane_view m_eview;
      EType m_etype;


      void SetType(EType etype);
	   bool IsTypeOf(EType etype);

	   pane_view_update_hint();
	   virtual ~pane_view_update_hint();


   };


} // namespace alatel