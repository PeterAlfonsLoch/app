#pragma once


template < class TYPE, class ARG_TYPE >
inline bool EqualsCompareElements(const TYPE * pElement1, const ARG_TYPE element2)
{
   return *pElement1 == element2;
}

template < typename TYPE1, typename TYPE2 >
inline bool EqualsCompareElements(const TYPE1 & r1, const TYPE2 & r2)
{
   return r1 == r2;
}


namespace comparison
{

   template < class TYPE, class ARG_TYPE >
   class equals_type_arg_type
   {
   public:

      inline static bool CompareElements(const TYPE * pElement1, const ARG_TYPE element2)
      {
         return ::EqualsCompareElements < TYPE, ARG_TYPE > (pElement1, element2);
      }


   };


   template < typename TYPE1, typename TYPE2 >
   class equals_ref
   {
   public:
      
      inline static bool CompareElements(const TYPE1 & r1, const TYPE2 & r2)
      {
         return ::EqualsCompareElements < TYPE1, TYPE2 > (r1, r2);
      }
      
      
   };



} // namespace comparison



