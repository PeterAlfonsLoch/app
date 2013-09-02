#pragma once


namespace ca2
{

   class CLASS_DECL_c departament_container_base :
      virtual public object
   {
   public:


      departament_container_base();
      virtual ~departament_container_base();


      application * get_departament_app();


   };


   template < class SECTION >
   class departament_container :
      virtual public departament_container_base
   {
   public:

      
      sp(SECTION) m_pdepartament;


      departament_container()
      {
         
      }


      virtual ~departament_container()
      {
      }

   };


} // namespace ca2


