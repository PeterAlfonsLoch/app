#pragma once


namespace ca2
{

   class CLASS_DECL_ca2 section_container_base :
      virtual public ::ca2::object
   {
   public:


      section_container_base();
      virtual ~section_container_base();


      ::ca2::application * get_section_app();


   };


   template < class SECTION >
   class section_container :
      virtual public section_container_base
   {
   public:

      
      sp(SECTION) m_psection;


      section_container()
      {
         
      }


      virtual ~section_container()
      {
      }

   };


} // namespace ca2


