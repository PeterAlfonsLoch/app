#pragma once


namespace user
{


   class CLASS_DECL_BASE view_update_hint :
      virtual public ::object
   {
   public:


      enum e_hint
      {

         hint_none,
         hint_open_document,
         hint_create_views,
         hint_pre_close_document

      };


      e_hint         m_ehint;
      bool           m_bOk;


      bool is_type_of(e_hint ehint) const;


      view_update_hint(::aura::application * papp);
      virtual ~view_update_hint();


   };


} // namespace user



