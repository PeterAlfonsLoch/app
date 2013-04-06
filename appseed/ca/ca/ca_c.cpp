#include "framework.h"


namespace ca
{
   
   c::c()
   {

      m_countReference = 1;

   }

   c::c(const c &)
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


  sp(::ca::application) c::get_app() const
  {

     return ::null();

  }

   allocer::allocer(sp(application) papp)
   {

      sp(allocator) spallocator = canew(allocator());

      spallocator->m_papp = papp;

      smart_pointer < allocator >::operator = (spallocator);

   }

} // namespace ca



