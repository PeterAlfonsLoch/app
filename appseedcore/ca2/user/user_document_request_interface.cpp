#include "StdAfx.h"


namespace user
{

   ::document * document_request_interface::open_document_file(
      var varFile, 
      bool bMakeVisible, 
      ::user::interaction * puiParent,
      ::view * pviewAlloc)
   {

      var varQuery;
      varQuery["make_visible_boolean"] = bMakeVisible;
      varQuery["parent_user_interaction"] = puiParent;
      varQuery["allocation_view"] = pviewAlloc;
      request(varFile, varQuery);
      return varQuery["document"].ca2 < ::document > ();
   }

} // namespace user


