#pragma once


namespace _template
{

   class CLASS_DECL_ca compare
   {
   public:
      
      template < class TYPE, class ARG_TYPE >
      int CompareElements(const TYPE * pElement1, const ARG_TYPE * pElement2)
      {
         if(*pElement1 > *pElement2)
            return 1;
         else if(*pElement1 < *pElement2)
            return -1;
         else
            return 0;
      }


   };


} // namespace _template


