#pragma once

class CLASS_DECL_ca2 os_history :
   virtual public ::ca2::history
{
public:

   os_history(sp(::application) papp);
         
   
   virtual bool hist(const char *psz);

};


