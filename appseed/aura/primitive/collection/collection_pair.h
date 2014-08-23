#pragma once


template < typename T1, typename T2 >
class pair
{
public:
   
   
   T1       first;
   T2       second;

   
   pair()
   {
   }

   pair(const T1 & element1)
   {
      first = element1;
   }

   pair(const T1 & element1, const T2 & element2)
   {
      first = element1;
      second = element2;
   }


   inline T1 & element1()  { return first; }
   inline T2 & element2() { return second; }

   inline const T1 & element1() const { return first; }
   inline const T2 & element2() const { return second; }

   

};

