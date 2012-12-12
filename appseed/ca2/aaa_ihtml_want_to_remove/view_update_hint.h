#pragma once

namespace ihtml
{

class CLASS_DECL_CA2_IHTML view_update_hint : public base_object
{
   DECLARE_DYNAMIC(view_update_hint)
public:

   enum e_type
   {
      // url is filled
      type_document_complete, 
      
   };

   string m_strUrl;

   e_type m_etype;
};

} // namespace ihtml