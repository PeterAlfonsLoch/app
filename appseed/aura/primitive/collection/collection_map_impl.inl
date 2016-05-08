#pragma once


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR >
void map < KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR >::InitHashTable(
   UINT nHashSize, bool bAllocNow)
   //
   // Used to force allocation of a hash table or to override the default
   //   hash table size of (which is fairly small)
{

   ASSERT_VALID(this);
   ASSERT(m_nCount == 0);
   ASSERT(nHashSize > 0);

   m_hashtable.InitHashTable(nHashSize,bAllocNow);

}
