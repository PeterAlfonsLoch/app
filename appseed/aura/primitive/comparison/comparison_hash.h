#pragma once






template < class ARG_KEY >
inline UINT HashKey(ARG_KEY key)
{
   // default identity hash - works for most primitive values
   return (uint32_t)(((uint_ptr)key)>>4);
}


template < >
inline UINT HashKey (const wstring & key)
{
   uint64_t * puiKey = (uint64_t *) (const unichar *) key;
   strsize counter = key.get_length() * sizeof(unichar);
   uint64_t nHash = 0;
   while(compare::ge(counter, sizeof(*puiKey)))
   {
      nHash = (nHash<<5) + nHash + *puiKey++;
      counter -= sizeof(*puiKey);
   }
   const unichar * pszKey = (const unichar *) puiKey;
   while(true)
   {
      counter -= 2;
      if(counter < 0)
         break;
      nHash = (nHash<<5) + nHash + *pszKey++;
   }
   return (UINT)(nHash & 0xffffffff);
}






template<> 
inline UINT HashKey<const char *> (const char * key)
{
   uint64_t * puiKey = (uint64_t *) key;
   strsize counter = strlen(key);
   uint64_t nHash = 0;
   while(compare::ge(counter, sizeof(*puiKey)))
   {
      nHash = (nHash<<5) + nHash + *puiKey++;
      counter -= sizeof(*puiKey);
   }
   const char * pszKey = (const char *) puiKey;
   while(counter-- >= 0) nHash = (nHash<<5) + nHash + *pszKey++;
   return (UINT) nHash;
}


template<>
inline UINT HashKey<string>(string key)
{

   return HashKey<const char * >(key);

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
