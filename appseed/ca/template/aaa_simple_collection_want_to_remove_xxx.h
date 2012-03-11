#pragma once

#include "definition.h"
#include "checked.h"

/*#pragma push_macro("malloc")
#undef malloc
#pragma push_macro("calloc")
#undef calloc
#pragma push_macro("realloc")
#undef realloc
#pragma push_macro("_recalloc")
#undef _recalloc
#pragma push_macro("free")
#undef free*/


namespace _template
{

//   #pragma push_macro("new")
   #undef new
#undef delete

   /////////////////////////////////////////////////////////////////////////////
   // Collection helpers - CSimpleArray & CSimpleMap

   // template class helpers with functions for comparing elements
   // override if using complex types without operator==
   template <class T>
   class CSimpleArrayEqualHelper
   {
   public:
      static bool IsEqual(const T& t1, const T& t2)
      {
         return (t1 == t2);
      }
   };

   template <class T>
   class CSimpleArrayEqualHelperFalse
   {
   public:
      static bool IsEqual(const T&, const T&)
      {
         ATLASSERT(false);
         return false;
      }
   };

   template <class TKey, class TVal>
   class CSimpleMapEqualHelper
   {
   public:
      static bool IsEqualKey(const TKey& k1, const TKey& k2)
      {
         return CSimpleArrayEqualHelper<TKey>::IsEqual(k1, k2);
      }

      static bool IsEqualValue(const TVal& v1, const TVal& v2)
      {
         return CSimpleArrayEqualHelper<TVal>::IsEqual(v1, v2);
      }
   };

   template <class TKey, class TVal>
   class CSimpleMapEqualHelperFalse
   {
   public:
      static bool IsEqualKey(const TKey& k1, const TKey& k2)
      {
         return CSimpleArrayEqualHelper<TKey>::IsEqual(k1, k2);
      }

      static bool IsEqualValue(const TVal&, const TVal&)
      {
         ATLASSERT(FALSE);
         return false;
      }
   };

   template <class T, class TEqual = CSimpleArrayEqualHelper< T > >
   class CSimpleArray
   {
   public:
   // Construction/destruction
      CSimpleArray() : m_aT(NULL), m_nSize(0), m_nAllocSize(0)
      { }

      ~CSimpleArray();

      CSimpleArray(const CSimpleArray< T, TEqual >& src) : m_aT(NULL), m_nSize(0), m_nAllocSize(0)
      {
           if (src.get_size())
           {
            m_aT = (T*)calloc(src.get_size(), sizeof(T));
            if (m_aT != NULL)
            {
               m_nAllocSize = src.get_size();
               for (int i=0; i<src.get_size(); i++)
                  add(src[i]);
            }
         }
      }
      CSimpleArray< T, TEqual >& operator=(const CSimpleArray< T, TEqual >& src)
      {
         if (this->get_size() != src.get_size())
         {
            remove_all();
            m_aT = (T*)calloc(src.get_size(), sizeof(T));
            if (m_aT != NULL)
               m_nAllocSize = src.get_size();
         }
         else
         {
            for (int i = this->get_size(); i > 0; i--)
               remove_at(i - 1);
         }
         for (int i=0; i<src.get_size(); i++)
            add(src[i]);
         return *this;
      }

   // Operations
      int get_size() const
      {
         return m_nSize;
         }
         BOOL add(const T& t)
         {
            if(m_nSize == m_nAllocSize)
            {
               T* aT;
               int nNewAllocSize = (m_nAllocSize == 0) ? 1 : (m_nSize * 2);


                  if (nNewAllocSize<0||nNewAllocSize>INT_MAX/sizeof(T))
               {


                     return FALSE;

               }



               aT = (T*)_recalloc(m_aT, nNewAllocSize, sizeof(T));
               if(aT == NULL)
                  return FALSE;
               m_nAllocSize = nNewAllocSize;
               m_aT = aT;

            }
            InternalSetAtIndex(m_nSize, t);
            m_nSize++;
            return TRUE;
         }
      BOOL remove(const T& t)
      {
         int nIndex = find(t);
         if(nIndex == -1)
            return FALSE;
         return remove_at(nIndex);
      }
      BOOL remove_at(int nIndex)
      {
         ATLASSERT(nIndex >= 0 && nIndex < m_nSize);
         if (nIndex < 0 || nIndex >= m_nSize)
            return FALSE;
         m_aT[nIndex].~T();
         if(nIndex != (m_nSize - 1))
            checked::memmove_s((void*)(m_aT + nIndex), (m_nSize - nIndex) * sizeof(T), (void*)(m_aT + nIndex + 1), (m_nSize - (nIndex + 1)) * sizeof(T));
         m_nSize--;
         return TRUE;
      }
      void remove_all()
      {
         if(m_aT != NULL)
         {
            for(int i = 0; i < m_nSize; i++)
               m_aT[i].~T();
            free(m_aT);
            m_aT = NULL;
         }
         m_nSize = 0;
         m_nAllocSize = 0;
       }
      const T& operator[] (int nIndex) const
      {
         ATLASSERT(nIndex >= 0 && nIndex < m_nSize);
         if(nIndex < 0 || nIndex >= m_nSize)
         {
            atl_raise_exception((DWORD)EXCEPTION_ARRAY_BOUNDS_EXCEEDED);
         }
         return m_aT[nIndex];
      }
      T& operator[] (int nIndex)
      {
         ATLASSERT(nIndex >= 0 && nIndex < m_nSize);
         if(nIndex < 0 || nIndex >= m_nSize)
         {
            atl_raise_exception((DWORD)EXCEPTION_ARRAY_BOUNDS_EXCEEDED);
         }
         return m_aT[nIndex];
      }
      T* get_data() const
      {
         return m_aT;
      }

      int find(const T& t) const
      {
         for(int i = 0; i < m_nSize; i++)
         {
            if(TEqual::IsEqual(m_aT[i], t))
               return i;
         }
         return -1;  // not found
      }

      BOOL SetAtIndex(int nIndex, const T& t)
      {
         if (nIndex < 0 || nIndex >= m_nSize)
            return FALSE;
         InternalSetAtIndex(nIndex, t);
         return TRUE;
      }

   // Implementation
      class Wrapper
      {
      public:
         Wrapper(const T& _t) : t(_t)
         {
         }
         template <class _Ty>
         void * __cdecl operator new(size_t, _Ty* p)
         {
            return p;
         }
         template <class _Ty>
         void __cdecl operator delete(void* /* pv */, _Ty* /* p */)
         {
         }
         T t;
      };

   // Implementation
      void InternalSetAtIndex(int nIndex, const T& t)
      {
         new(m_aT + nIndex) Wrapper(t);
      }

      typedef T _ArrayElementType;
      T* m_aT;
      int m_nSize;
      int m_nAllocSize;

   };

   #define CSimpleValArray CSimpleArray

      template <class T, class TEqual> inline  CSimpleArray<T, TEqual>::~CSimpleArray()
      {
         remove_all();
      }

   // intended for small number of simple types or pointers
   template <class TKey, class TVal, class TEqual = CSimpleMapEqualHelper< TKey, TVal > >
   class CSimpleMap
   {
   public:
      TKey* m_aKey;
      TVal* m_aVal;
      int m_nSize;

      typedef TKey _ArrayKeyType;
      typedef TVal _ArrayElementType;

   // Construction/destruction
      CSimpleMap() : m_aKey(NULL), m_aVal(NULL), m_nSize(0)
      { }

      ~CSimpleMap()
      {
         remove_all();
      }

   // Operations
      int get_size() const
      {
         return m_nSize;
      }
      BOOL add(const TKey& key, const TVal& val)
      {
         TKey* pKey;
         pKey = (TKey*)_recalloc(m_aKey, (m_nSize + 1), sizeof(TKey));
         if(pKey == NULL)
            return FALSE;
         m_aKey = pKey;
         TVal* pVal;
         pVal = (TVal*)_recalloc(m_aVal, (m_nSize + 1), sizeof(TVal));
         if(pVal == NULL)
            return FALSE;
         m_aVal = pVal;
         InternalSetAtIndex(m_nSize, key, val);
         m_nSize++;
         return TRUE;
      }
      BOOL remove(const TKey& key)
      {
         int nIndex = FindKey(key);
         if(nIndex == -1)
            return FALSE;
         return remove_at(nIndex);
      }
      BOOL remove_at(int nIndex)
      {
         ATLASSERT(nIndex >= 0 && nIndex < m_nSize);
         if (nIndex < 0 || nIndex >= m_nSize)
            return FALSE;
         m_aKey[nIndex].~TKey();
         m_aVal[nIndex].~TVal();
         if(nIndex != (m_nSize - 1))
         {
            checked::memmove_s((void*)(m_aKey + nIndex), (m_nSize - nIndex) * sizeof(TKey), (void*)(m_aKey + nIndex + 1), (m_nSize - (nIndex + 1)) * sizeof(TKey));
            checked::memmove_s((void*)(m_aVal + nIndex), (m_nSize - nIndex) * sizeof(TVal), (void*)(m_aVal + nIndex + 1), (m_nSize - (nIndex + 1)) * sizeof(TVal));
         }
         TKey* pKey;
         pKey = (TKey*)_recalloc(m_aKey, (m_nSize - 1), sizeof(TKey));
         if(pKey != NULL || m_nSize == 1)
            m_aKey = pKey;
         TVal* pVal;
         pVal = (TVal*)_recalloc(m_aVal, (m_nSize - 1), sizeof(TVal));
         if(pVal != NULL || m_nSize == 1)
            m_aVal = pVal;
         m_nSize--;
         return TRUE;
      }
      void remove_all()
      {
         if(m_aKey != NULL)
         {
            for(int i = 0; i < m_nSize; i++)
            {
               m_aKey[i].~TKey();
               m_aVal[i].~TVal();
            }
            free(m_aKey);
            m_aKey = NULL;
         }
         if(m_aVal != NULL)
         {
            free(m_aVal);
            m_aVal = NULL;
         }

         m_nSize = 0;
      }
      BOOL set_at(const TKey& key, const TVal& val)
      {
         int nIndex = FindKey(key);
         if(nIndex == -1)
            return FALSE;
         ATLASSERT(nIndex >= 0 && nIndex < m_nSize);
         m_aKey[nIndex].~TKey();
         m_aVal[nIndex].~TVal();
         InternalSetAtIndex(nIndex, key, val);
         return TRUE;
      }
      TVal Lookup(const TKey& key) const
      {
         int nIndex = FindKey(key);
         if(nIndex == -1)
            return NULL;    // must be able to convert
         return GetValueAt(nIndex);
      }
      TKey ReverseLookup(const TVal& val) const
      {
         int nIndex = FindVal(val);
         if(nIndex == -1)
            return NULL;    // must be able to convert
         return GetKeyAt(nIndex);
      }
      TKey& GetKeyAt(int nIndex) const
      {
         ATLASSERT(nIndex >= 0 && nIndex < m_nSize);
         if(nIndex < 0 || nIndex >= m_nSize)
            atl_raise_exception((DWORD)EXCEPTION_ARRAY_BOUNDS_EXCEEDED);

         return m_aKey[nIndex];
      }
      TVal& GetValueAt(int nIndex) const
      {
         ATLASSERT(nIndex >= 0 && nIndex < m_nSize);
         if(nIndex < 0 || nIndex >= m_nSize)
            atl_raise_exception((DWORD)EXCEPTION_ARRAY_BOUNDS_EXCEEDED);

         return m_aVal[nIndex];
      }

      int FindKey(const TKey& key) const
      {
         for(int i = 0; i < m_nSize; i++)
         {
            if(TEqual::IsEqualKey(m_aKey[i], key))
               return i;
         }
         return -1;  // not found
      }
      int FindVal(const TVal& val) const
      {
         for(int i = 0; i < m_nSize; i++)
         {
            if(TEqual::IsEqualValue(m_aVal[i], val))
               return i;
         }
         return -1;  // not found
      }

      BOOL SetAtIndex(int nIndex, const TKey& key, const TVal& val)
      {
         if (nIndex < 0 || nIndex >= m_nSize)
            return FALSE;
         InternalSetAtIndex(nIndex, key, val);
         return TRUE;
      }


   // Implementation

      template <typename T>
      class Wrapper
      {
      public:
         Wrapper(const T& _t) : t(_t)
         {
         }
         template <class _Ty>
         void *operator new(size_t, _Ty* p)
         {
            return p;
         }
         template <class _Ty>
         void operator delete(void* /* pv */, _Ty* /* p */)
         {
         }
         T t;
      };
      void InternalSetAtIndex(int nIndex, const TKey& key, const TVal& val)
      {
         new(m_aKey + nIndex) Wrapper<TKey>(key);
         new(m_aVal + nIndex) Wrapper<TVal>(val);
      }
   };

//   #pragma pop_macro("new")

};  // namespace _template


/*#pragma pop_macro("free")
#pragma pop_macro("realloc")
#pragma pop_macro("_recalloc")
#pragma pop_macro("malloc")
#pragma pop_macro("calloc")*/


