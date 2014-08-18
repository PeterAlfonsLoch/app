#pragma once


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::InitHashTable(
   UINT nHashSize, bool bAllocNow)
   //
   // Used to force allocation of a hash table or to override the default
   //   hash table size of (which is fairly small)
{
   ASSERT_VALID(this);
   ASSERT(m_nCount == 0);
   ASSERT(nHashSize > 0);

   if (m_ppassocHash != NULL)
   {
      // free hash table
      delete[] m_ppassocHash;
      m_ppassocHash = NULL;
   }

   if (bAllocNow)
   {
      m_ppassocHash = new assoc * [nHashSize];
      ENSURE(m_ppassocHash != NULL);
      memset(m_ppassocHash, 0, sizeof(assoc*) * nHashSize);
   }

   m_nHashTableSize = nHashSize;

}
