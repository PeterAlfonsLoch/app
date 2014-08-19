#pragma once


class CLASS_DECL_BASE departament_container_base :
   virtual public ::object
{
public:


   departament_container_base();
   virtual ~departament_container_base();


   ::axis::application * get_departament_app();


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


