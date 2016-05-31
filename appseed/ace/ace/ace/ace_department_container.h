#pragma once


class CLASS_DECL_ACE department_container_base :
   virtual public ::object
{
public:


   department_container_base();
   virtual ~department_container_base();


   ::ace::application * get_department_app();


};


template < class SECTION >
class department_container :
   virtual public department_container_base
{
public:


   sp(SECTION) m_pdepartment;


   department_container()
   {

   }


   virtual ~department_container()
   {
   }

};


