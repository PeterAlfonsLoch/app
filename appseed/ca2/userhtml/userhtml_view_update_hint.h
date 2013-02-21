#pragma once


class CLASS_DECL_ca2 html_view_update_hint : public ::gen::object
{
   
public:

   enum e_type
   {
      // url is filled
      type_document_complete, 
      
   };

   string m_strUrl;

   e_type m_etype;


};