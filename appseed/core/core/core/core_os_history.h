#pragma once

class CLASS_DECL_CORE os_history :
   virtual public ::core::history
{
public:

   os_history(sp(::aura::application) papp);
         
   
   virtual bool hist(const char *psz);

};


