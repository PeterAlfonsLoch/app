#include "StdAfx.h"

namespace ca
{
   
   exception::~exception()
   {
   }

   void exception::Delete()
   {
      delete this;
   }

   void CLASS_DECL_ca rethrow(exception * pe)
   {
      throw pe;
   }


} // namespace ca