#pragma once


namespace md5
{

   enum e_pane_view
   {
      pane_view_none,
      pane_view_md5,
      pane_view_file_manager,
   };


   class CLASS_DECL_CA2_MD5 pane_view_update_hint :
      public ::radix::object  
   {
   public:


      enum e_type
      {
         TypeGetView,
         TypeSetView,
         TypeOnShowKaraoke,
         TypeOnShowView,
      };


      e_pane_view       m_eview;
      e_type            m_etype;


      pane_view_update_hint();
	   virtual ~pane_view_update_hint();


      void set_type(e_type etype);
	   bool is_type_of(e_type etype);



   };


} // namespace md5