#include "framework.h"


simple_document::simple_document(sp(base_application) papp) : 
   element(papp),
<<<<<<< .mine
   ::user::object(papp),
=======
   ::data::data_container_base(papp),
   
   ::user::object(papp),
>>>>>>> .r7014
   m_set(papp)
{
}

simple_document::~simple_document()
{
}



