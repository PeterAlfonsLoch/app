#pragma once


namespace comparison
{


   template < typename TYPE, typename ARG_TYPE = const TYPE & >
   class binary
   {
   public:


      int operator ()(ARG_TYPE a, ARG_TYPE b)
      {
         if(a < b)
            return -1;
         else if(b < a)
            return 1;
         else
            return 0;
      }


   };

   template < >
   class CLASS_DECL_AURA binary < int32_t >
   {
   public:


      inline static int_ptr CompareElements(const int32_t * pElement1, const int32_t * pElement2)
      {
         return *pElement1 - *pElement2;
      }


   };



} // namespace comparison


