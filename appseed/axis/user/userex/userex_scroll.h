#pragma once


namespace userex
{


   template < class BASE >
   class scroll :
      virtual public ::user::scroll < BASE >
   {
   public:


      size        m_sizeTotal;


      scroll()
      {

      }


      scroll(::aura::application * papp):
         object(papp)
      {

      }


      virtual ~scroll()
      {

      }


      virtual size get_total_size()
      {

         return m_sizeTotal;

      }


   };


   typedef ::user::show < scroll < ::user::control > > scroll_view;


} // namespace userex































