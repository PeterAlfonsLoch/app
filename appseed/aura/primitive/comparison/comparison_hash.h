#pragma once






template < class ARG_KEY >
inline UINT HashKey(ARG_KEY key)
{
   // default identity hash - works for most primitive values
   return (uint32_t)(((uint_ptr)key)>>4);
}


namespace comparison
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
   class CLASS_DECL_AURA hash < const wstring & >
   {
   public:

      inline static UINT HashKey (const wstring & key)
      {
         uint64_t * puiKey = (uint64_t *) (const wchar_t *) key;
         strsize counter = key.get_length() * sizeof(wchar_t);
         uint64_t nHash = 0;
         while(counter >= sizeof(*puiKey))
         {
            nHash = (nHash<<5) + nHash + *puiKey++;
            counter -= sizeof(*puiKey);
         }
         const wchar_t * pszKey = (const wchar_t *) puiKey;
         while(true)
         {
            counter -= 2;
            if(counter < 0)
               break;
               nHash = (nHash<<5) + nHash + *pszKey++;
         }
         return (UINT)(nHash & 0xffffffff);
      }

   };



} // namespace comparison



template<> CLASS_DECL_AURA UINT HashKey<const wchar_t *> (const wchar_t * key);




template<> inline UINT HashKey<const char *> (const char * key)
{
   uint64_t * puiKey = (uint64_t *) key;
   strsize counter = strlen(key);
   uint64_t nHash = 0;
   while(counter >= sizeof(*puiKey))
   {
      nHash = (nHash<<5) + nHash + *puiKey++;
      counter -= sizeof(*puiKey);
   }
   const char * pszKey = (const char *) puiKey;
   while(counter-- >= 0) nHash = (nHash<<5) + nHash + *pszKey++;
   return (UINT) nHash;
}


