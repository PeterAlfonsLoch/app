#pragma once

class form_view;

class CLASS_DECL_ca2 form_update_hint : 
   virtual public ::radix::object
{
public:
   

   enum e_type
   {
      type_browse,
      type_after_browse,
      type_get_form_view,
   };


   form_view *    m_pformview;
   e_type         m_etype;
   string         m_strForm;
};
