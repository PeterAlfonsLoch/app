#include "framework.h"


namespace ca
{


   c::~c()
   {
   }


  void c::delete_this()
  {

     // quite verisimple default implementation
     delete this;

  }


  ::ca::applicationsp c::get_app() const
  {

     return ::null();

  }

} // namespace ca



