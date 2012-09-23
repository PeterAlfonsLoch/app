#pragma once


namespace gen
{


   template < typename TYPE >
   class compare
   {
   public:


      inline static int_ptr CompareElements(const TYPE * pElement1, const TYPE * pElement2)
      {
         if(*pElement1 > *pElement2)
            return 1;
         else if(*pElement1 < *pElement2)
            return -1;
         else
            return 0;
      }


   };

   template < >
   class CLASS_DECL_ca compare < int >
   {
   public:


      inline static int_ptr CompareElements(const int * pElement1, const int * pElement2)
      {
         return *pElement1 - *pElement2;
      }


   };

   class CLASS_DECL_ca strid_compare
   {
   public:


      inline static int_ptr CompareElements(const id * pElement1, const id * pElement2)
      {
         return id_cmp(pElement1, pElement2);
      }


   };


} // namespace gen


