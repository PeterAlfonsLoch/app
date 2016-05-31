#pragma once


template <  typename PAIR >
class map_association : 
   public PAIR
{
public:


   typedef PAIR                        pair;
   typedef typename PAIR::TYPE1        TYPE1;
   typedef typename PAIR::TYPE2        TYPE2;
   

   map_association *                   m_pprev;
   map_association *                   m_pnext;
   map_association *                   m_pnextHash;
   map_association **                  m_ppprevHash;

   map_association()
   {
   }
   map_association(const TYPE1 & element1) :
      pair(element1)
   {
   }
   map_association(const TYPE1 & element1,const TYPE2 & element2):
      pair(element1, element2)
   {
   }

};
