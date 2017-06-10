#pragma once


namespace comparison
{

   class hash
   {
   public:

      template < typename TYPE >
      static UINT run(TYPE t)
      {

         // default identity hash - works for most primitive values

         return (uint32_t)(((uint_ptr)t) >> 4);

      }

   };

   inline uint64_t string_hash(const char * key, uint64_t nHash = 0)
   {

      while (*key)
      {

         nHash = (nHash << 5) + nHash + *key++;

      }

      return nHash;

   }

   inline uint64_t string_hash(const wchar_t * key, uint64_t nHash = 0)
   {

      while (*key)
      {

         nHash = (nHash << 5) + nHash + *key++;

      }

      return nHash;

      }


#if !defined(WINDOWS)

   inline uint64_t string_hash(const unichar * key, uint64_t nHash = 0)
   {

      while (*key)
      {

         nHash = (nHash << 5) + nHash + *key++;

      }

      return nHash;

   }

#endif


   template < >
   inline UINT hash::run < const char * > (const char * key)
   {

      return (UINT)string_hash(key);

   }



   template < >
   inline UINT hash::run < const wchar_t * >(const wchar_t * key)
   {

      return (UINT)string_hash(key);

   }

   template < >
   inline UINT hash::run < const string & >(const string &  key)
   {
         
      return (UINT)string_hash(key.m_pszData);

   }



   template < >
   inline UINT hash::run < const wstring & >(const wstring & key)
   {

#if defined(LINUX) || defined(__APPLE__) || defined(VSNORD)
      return run<unichar * >(key.c_str());
#else
      return run<const wchar_t * >(key.c_str());
#endif

   }





} // namespace comparison






namespace comparisontest
{

   class hash
   {
   public:

      template < typename TYPE >
      static UINT run(TYPE t)
      {

         // default identity hash - works for most primitive values

         return (uint32_t)(((uint_ptr)t) >> 4);

      }

   };


   inline uint64_t string_hash(const char * key, uint64_t nHash = 0)
   {

      while (*key)
      {

         nHash = (nHash << 5) + nHash + *key++;

      }

      return nHash;

   }

   inline uint64_t string_hash(const wchar_t * key, uint64_t nHash = 0)
   {

      while (*key)
      {

         nHash = (nHash << 5) + nHash + *key++;

      }

      return nHash;

   }


#if !defined(WINDOWS)

   inline uint64_t string_hash(const unichar * key, uint64_t nHash = 0)
   {

      while (*key)
      {

         nHash = (nHash << 5) + nHash + *key++;

      }

      return nHash;

   }

#endif


   template < >
   inline UINT hash::run < const char * >(const char * key)
   {

      return (UINT)string_hash(key);

   }



   template < >
   inline UINT hash::run < const wchar_t * >(const wchar_t * key)
   {

      return (UINT)string_hash(key);

   }

   template < >
   inline UINT hash::run < const string & >(const string &  key)
   {

      return (UINT)string_hash(key.m_pszData);

   }



   template < >
   inline UINT hash::run < const wstring & >(const wstring & key)
   {

#if defined(LINUX) || defined(__APPLE__) || defined(VSNORD)
      return run<unichar * >(key.c_str());
#else
      return run<const wchar_t * >(key.c_str());
#endif

   }




}




namespace comparisonok
{

   class hash
   {
   public:

      template < typename TYPE >
      static UINT run(TYPE t)
      {

         // default identity hash - works for most primitive values

         return (uint32_t)(((uint_ptr)t) >> 4);

      }

   };


   inline uint64_t string_hash(const char * key, uint64_t nHash = 0)
   {

      while (*key)
      {

         nHash = (nHash << 5) + nHash + *key++;

      }

      return nHash;

   }

   inline uint64_t string_hash(const wchar_t * key, uint64_t nHash = 0)
   {

      while (*key)
      {

         nHash = (nHash << 5) + nHash + *key++;

      }

      return nHash;

   }


#if !defined(WINDOWS)

   inline uint64_t string_hash(const unichar * key, uint64_t nHash = 0)
   {

      while (*key)
      {

         nHash = (nHash << 5) + nHash + *key++;

      }

      return nHash;

   }

#endif


   template < >
   inline UINT hash::run < const char * >(const char * key)
   {

      return (UINT)string_hash(key);

   }



   template < >
   inline UINT hash::run < const wchar_t * >(const wchar_t * key)
   {

      return (UINT)string_hash(key);

   }

   template < >
   inline UINT hash::run < const string & >(const string &  key)
   {

      return (UINT)string_hash(key.m_pszData);

   }



   template < >
   inline UINT hash::run < const wstring & >(const wstring & key)
   {

#if defined(LINUX) || defined(__APPLE__) || defined(VSNORD)
      return run<unichar * >(key.c_str());
#else
      return run<const wchar_t * >(key.c_str());
#endif

   }




}