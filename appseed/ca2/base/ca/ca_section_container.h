#pragma once


namespace ca
{

   class CLASS_DECL_ca2 section_container_base :
      virtual public ::ca::object
   {
   public:


      section_container_base();
      virtual ~section_container_base();


      ::ca::application * get_section_app();


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


} // namespace ca


