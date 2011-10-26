#pragma once


#include "gen_ptri.h"


class var;


namespace gen
{


   class CLASS_DECL_ca object :
      virtual public ptri
   {
   public:

      object(void);
      object(const object & objectSrc);
      virtual ~object(void);


      object & operator = (const object & objectSrc);

   };


} // namespace gen


