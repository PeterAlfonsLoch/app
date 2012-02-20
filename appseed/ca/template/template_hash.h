#pragma once


#include "ca/primitive/rectangle.h"



template < class ARG_KEY >
inline UINT HashKey(ARG_KEY key)
{
   // default identity hash - works for most primitive values
   return (DWORD)(((DWORD_PTR)key)>>4);
}


namespace _template
{

   template < class ARG_KEY >
   class hash
   {
   public:

      inline static UINT HashKey(ARG_KEY key)
      {
         return ::HashKey < ARG_KEY > (key);
      }

   };

   template < >
   class CLASS_DECL_ca hash < const string & >
   {
   public:

      inline static UINT HashKey (const string & key)
      {
         register uint64_t * puiKey = (uint64_t *) (const char *) key;
         register strsize counter = key.get_length();
         register uint64_t nHash = 0;
         while(counter >= sizeof(*puiKey))
         {
            nHash = (nHash<<5) + nHash + *puiKey++;
            counter -= sizeof(*puiKey);
         }
         register const char * pszKey = (const char *) puiKey;
         while(counter-- >= 0) nHash = (nHash<<5) + nHash + *pszKey++;
         return (UINT) nHash;
      }

   };

   class CLASS_DECL_ca strid_hash
   {
   public:

      inline static UINT HashKey (const id & key)
      {
         return *((UINT*)(&key.m_psz));
      }

   };


} // namespace _template


// special versions for CComBSTR
//template<> void SerializeElements<CComBSTR> (CArchive& ar, CComBSTR* pElements, count nCount);
template<> CLASS_DECL_ca UINT HashKey<CComBSTR> (CComBSTR key);

template<> CLASS_DECL_ca UINT HashKey<const wchar_t *> (const wchar_t * key);


template<> inline UINT HashKey<rect> (rect key)
{
   return key.left | key.top | key.bottom | key.right;
}

template<> inline UINT HashKey<point> (point key)
{
   return key.x | key.y;
}

template<> inline UINT HashKey<size> (size key)
{
   return key.cx | key.cy;
}


