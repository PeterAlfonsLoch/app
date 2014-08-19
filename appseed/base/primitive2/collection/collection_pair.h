#pragma once


template < typename T1, typename T2 >
class pair
{
public:
   
   
   T1       m_element1;
   T2       m_element2;

   
   pair()
   {
   }

   pair(const T1 & element1)
   {
      m_element1 = element1;
   }

   pair(const T1 & element1, const T2 & element2)
   {
      m_element1 = element1;
      m_element2 = element2;
   }


   inline T1 & element1()  { return m_element1; }
   inline T2 & element2() { return m_element2; }

   inline const T1 & element1() const { return m_element1; }
   inline const T2 & element2() const { return m_element2; }

   

};

