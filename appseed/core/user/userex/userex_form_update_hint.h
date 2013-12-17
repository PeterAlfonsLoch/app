#pragma once


class form_view;


class CLASS_DECL_CORE form_update_hint :
   virtual public ::object
{
public:


   enum e_type
   {
      type_browse,
      type_after_browse,
      type_get_form_view,
   };

   
   sp(form_view)           m_pformview;
   e_type                  m_etype;
   string                  m_strForm;
   ::action::context      m_actioncontext;


   form_update_hint();
   virtual ~form_update_hint();




};
