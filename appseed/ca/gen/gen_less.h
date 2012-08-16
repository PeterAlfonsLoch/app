#pragma once


namespace gen
{


   template < typename TYPE >
   class less
   {
   public:
      
      
      inline static int CompareElements(const TYPE * pIsFirst, const TYPE * pCompare)
      {
         
         return *pIsFirst < *pCompare;

      }


   };



} // namespace gen


