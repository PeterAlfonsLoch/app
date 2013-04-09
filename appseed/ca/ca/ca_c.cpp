#include "framework.h"


namespace ca
{
   
   c::c()
   {

      m_countReference = 1;

   }

   c::~c()
   {
   }


  void c::delete_this()
  {

     // quite verisimple default implementation
     delete this;

  }


  
} // namespace ca



