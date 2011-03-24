#pragma once

namespace querydb
{
   
   class CLASS_DECL_CA2_QUERYDB query_view :
      virtual public ::userbase::edit_plain_text_view
   {
   public:
      query_view(::ca::application * papp);

   };

} // namespace querydb
