#pragma once


class CLASS_DECL_CORE html_view_update_hint : public object
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