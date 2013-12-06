#include "framework.h"


installation_lock_file_lock::installation_lock_file_lock(sp(base_application) papp) :
   element(papp)
{

   System.install().installation_file_lock(true);

}

installation_lock_file_lock::~installation_lock_file_lock()
{

   System.install().installation_file_lock(false);

}

