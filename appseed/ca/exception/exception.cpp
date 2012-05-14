#include "framework.h"

namespace ca
{
   
//   exception::~exception()
  // {
   //}

} // namespace ca



// exception support
 resource_exception::resource_exception()
   : simple_exception() { }
 resource_exception::resource_exception(BOOL bAutoDelete, UINT nResourceID)
   : simple_exception(bAutoDelete) { m_nResourceID = nResourceID; }
 resource_exception::~resource_exception()
   { }


  user_exception::user_exception()
   : simple_exception() { }
 user_exception::user_exception(BOOL bAutoDelete, UINT nResourceID)
   : simple_exception(bAutoDelete) { m_nResourceID = nResourceID; }
 user_exception::~user_exception()
   { }



