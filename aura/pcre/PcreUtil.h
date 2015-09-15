#pragma once

#include "aura/aura/aura.h"


#ifdef AURA_PCRE
#define CLASS_DECL_AURA_PCRE CLASS_DECL_EXPORT
#else
#define CLASS_DECL_AURA_PCRE CLASS_DECL_IMPORT
#endif



class CLASS_DECL_AURA_PCRE pcre_util :
   virtual public object
{
public:


   virtual ~pcre_util();


   static pcre_util * compile(::aura::application * papp, const string & str);

   virtual int matches(const string & str) = 0;


protected:

   pcre_util(::aura::application * papp);


};
