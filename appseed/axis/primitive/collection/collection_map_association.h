#pragma once


template < typename T1, typename T2 >
class map_association : 
   public pair < T1, T2 >
{
public:


   typedef ::pair < T1, T2 >       pair;
   

   map_association *                   m_pprev;
   map_association *                   m_pnext;
   map_association *                   m_pnextHash;
   map_association **                  m_ppprevHash;

   map_association()
   {
   }
   map_association(const T1 & element1) :
      pair(element1)
   {
   }
   map_association(const T1 & element1, const T2 & element2) :
      pair(element1, element2)
   {
   }

};
