#pragma once

class CLASS_DECL_ca os_history :
   virtual public ::ca::history
{
public:

   os_history(sp(::ca::application) papp);
         
   
   virtual bool hist(const char *psz);

};


