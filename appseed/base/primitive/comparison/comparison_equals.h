#pragma once


template < class TYPE, class ARG_TYPE >
inline bool EqualsCompareElements(const TYPE * pElement1, const ARG_TYPE element2)
{
   return *pElement1 == element2;
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

   template < >
   class equals_type_arg_type < string, const string & >
   {
   public:

      inline static bool CompareElements(const string * pElement1, const string & element2)
      {
         return *pElement1 == element2;
      }

   };

   template < >
   class equals_type_arg_type < id, const id & >
   {
   public:

      inline static bool CompareElements(const id * pElement1, const id & element2)
      {
         return pElement1->m_pstr == element2.m_pstr;
      }

   };


   


   class strid_equals
   {
   public:

      inline static bool CompareElements(const id * pElement1, const id & element2)
      {
         return pElement1->m_pstr == element2.m_pstr;
      }

   };




} // namespace comparison



