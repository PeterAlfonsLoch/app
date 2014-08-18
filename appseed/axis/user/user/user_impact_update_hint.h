#pragma once


namespace user
{


   class CLASS_DECL_AXIS view_update_hint :
      virtual public ::object
   {
   public:


      enum e_hint
      {

         hint_none,
         hint_open_document,
         hint_create_views

      };


      e_hint         m_ehint;
      bool           m_bOk;


      bool is_type_of(e_hint ehint) const;


      view_update_hint(sp(::base::application) papp);
      virtual ~view_update_hint();


   };


} // namespace user



