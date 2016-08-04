#pragma once






template < class ARG_KEY >
inline UINT HashKey(ARG_KEY key)
{
   // default identity hash - works for most primitive values
   return (uint32_t)(((uint_ptr)key)>>4);
}



template<>
inline UINT HashKey<const char *> (const char * key)
{
   uint64_t * puiKey = (uint64_t *) key;
   size_t counter = strlen(key);
   uint64_t nHash = 0;
   while(counter > sizeof(*puiKey))
   {
      nHash = (nHash<<5) + nHash + *puiKey++;
      counter -= sizeof(*puiKey);
   }
   const char * pszKey = (const char *) puiKey;
   while (counter > 0)
   {
      nHash = (nHash << 5) + nHash + *pszKey++;
      counter--;
   }
   return (UINT) nHash;
}



#if !defined(WINDOWS)

template<>
inline UINT HashKey<const unichar *> (const unichar * key)
{
//   ENSURE_ARG(__is_valid_string(key));
   UINT nHash = 0;
   while (*key)
      nHash = (nHash<<5) + nHash + *key++;
   return nHash;
}

#endif

template<>
inline UINT HashKey<const wchar_t *>(const wchar_t * key);



template<>
inline UINT HashKey<wstring>(wstring key)
{
#if defined(LINUX) || defined(__APPLE__) || defined(VSNORD)
   return HashKey(key.c_str());
#else
   return HashKey<const wchar_t * >(key.c_str());
#endif

}








template<>
inline UINT HashKey<const string &>(const string &  key)
{

   return HashKey<const char * >(key.c_str());

}




//template < >
//inline UINT HashKey(const string & key)
//{
//   uint64_t * puiKey = (uint64_t *)(const char *)key;
//   strsize counter = key.get_length();
//   uint64_t nHash = 0;
//   while(::compare::ge(counter,sizeof(*puiKey)))
//   {
//      nHash = (nHash << 5) + nHash + *puiKey++;
//      counter -= sizeof(*puiKey);
//   }
//   const char * pszKey = (const char *)puiKey;
//   while(counter-- >= 0) nHash = (nHash << 5) + nHash + *pszKey++;
//   return (UINT)(nHash & 0xffffffff);
//}







//
//template <  >
//inline UINT HashKey(const ::file::path & path)
//{
//
//   return HashKey<const string &> ((const string &) path);
//}
//
