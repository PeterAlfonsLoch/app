#pragma once


template < class TYPE, class ARG_TYPE >
inline static bool EqualsCompareElements(const TYPE * pElement1, const ARG_TYPE * pElement2)
{
   return *pElement1 == *pElement2;
}


namespace _template
{

   class CLASS_DECL_ca equals
   {
   public:
      
      template < class TYPE, class ARG_TYPE >
      inline static bool CompareElements(const TYPE * pElement1, const ARG_TYPE * pElement2)
      {
         return ::EqualsCompareElements < TYPE, ARG_TYPE > (pElement1, pElement2);
      }


   };


} // namespace _template


