#pragma once


namespace user
{


   class view_update_hint :
      virtual public object
   {
   public:

      
      enum e_hint
      {

         hint_none,
         hint_open_document,
         hint_create_views

      };

      
      e_hint         m_ehint;

   
      view_update_hint(sp(base_application) papp);


   };


} // namespace user



