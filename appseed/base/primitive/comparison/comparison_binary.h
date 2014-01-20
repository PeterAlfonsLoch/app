#pragma once


namespace comparison
{


   template < typename TYPE >
   class binary
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
   class CLASS_DECL_BASE binary < int32_t >
   {
   public:


      inline static int_ptr CompareElements(const int32_t * pElement1, const int32_t * pElement2)
      {
         return *pElement1 - *pElement2;
      }


   };

   class CLASS_DECL_BASE strid_binary
   {
   public:


      inline static int_ptr CompareElements(const id * pElement1, const id * pElement2)
      {
         return pElement1->m_pstr - pElement2->m_pstr;
      }


   };


} // namespace comparison


