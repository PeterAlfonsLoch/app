#pragma once


template < typename T > class numeric_array;
typedef CLASS_DECL_AURA numeric_array < index > index_array;
typedef CLASS_DECL_AURA numeric_array < count > count_array;



#ifdef LINUX
#include <initializer_list>
#endif


namespace constructor
{


   template < class TYPE >
   class def
   {
   public:

      inline static void construct(void * p)
      {
         ::new(p) TYPE;
      }
      inline static void construct(void * p, ::count c)
      {
         while (c > 0)
         {
            ::new(p) TYPE;
            ((TYPE*&)p)++;
            c--;
         }
      }



   };


   template < class TYPE >
   class zero
   {
   public:

      inline static void construct(void * p)
      {

         ::zero(p, sizeof(TYPE));

      }

      inline static void construct(void * p, ::count c)
      {

         while (c > 0)
         {

            ::zero(p, sizeof(TYPE));

            ((byte*&)p) += sizeof(TYPE);

            c--;

         }

      }



   };


   template < class TYPE >
   class nodef
   {
   public:

      inline static void construct(void * p)
      {
         UNREFERENCED_PARAMETER(p);
      }
      inline static void construct(void * p, ::count c)
      {
         UNREFERENCED_PARAMETER(p);
         UNREFERENCED_PARAMETER(c);
      }

   };


} // namespace constructor

namespace destructor
{


   template < class TYPE >
   class def
   {
   public:

      inline static void destruct(TYPE * p)
      {
         p->~TYPE();
      }
      inline static void destruct(TYPE * p, ::count c)
      {
         while (c > 0)
         {
            p->~TYPE();
            p++;
            c--;
         }
      }



   };





   template < class TYPE >
   class nodef
   {
   public:

      inline static void destruct(TYPE * p)
      {
         UNREFERENCED_PARAMETER(p);
      }
      inline static void destruct(TYPE * p, ::count c)
      {
         UNREFERENCED_PARAMETER(p);
         UNREFERENCED_PARAMETER(c);
      }

   };


} // namespace destructor


namespace copier
{


   template < class TYPE >
   class def
   {
   public:

      inline static void copy(TYPE *pdst, const TYPE * psrc)
      {

         *pdst = *psrc;

      }

      inline static void copy(TYPE *pdst, const TYPE * psrc, ::count c)
      {

         while (c > 0)
         {
            *pdst = *psrc;
            pdst++;
            psrc++;
            c--;
         }

      }


   };


} // namespace copier


namespace heap
{

   template < class TYPE, class POOL >
   class allocator
   {
   public:

#if MEMDLEAK  || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char * pszFile, int iLine)
      {

         return (TYPE *)POOL::alloc(sizeof(TYPE) * c, pszFile, iLine);

      }
#else
      inline static TYPE * alloc(::count c)
      {

         return (TYPE *)POOL::alloc(sizeof(TYPE) * c);

      }
#endif


      inline static void _free(TYPE * p)
      {

         POOL::_free((void *)p);

      }


   };


   template < class TYPE >
   class def :
      public allocator < TYPE, default_memory_allocator>
   {

   };


   template < class TYPE >
   class processor_cache_oriented : // would it help for data-orientation-assumation ??!?!
      public allocator < TYPE, processor_cache_oriented_memory_allocator >
   {


   };


   template < class TYPE >
   class sys :
      public allocator < TYPE, system_memory_allocator>
   {

   };



} // namespace memory


namespace allocator
{


   template < class TYPE >
   class allocator
   {
   public:

      inline static void construct(TYPE * p)
      {
         constructor::nodef< TYPE >::construct(p);
      }

      inline static void construct(TYPE * p, ::count c)
      {
         constructor::nodef< TYPE >::construct(p, c);

      }

      inline static void destruct(TYPE * p)
      {
         destructor::nodef < TYPE >::destruct(p);
      }
      inline static void destruct(TYPE * p, ::count c)
      {
         destructor::nodef < TYPE >::destruct(p, c);
      }


      inline static void copy(TYPE *pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline static void copy(TYPE *pdst, const TYPE * psrc, ::count c)
      {

         copier::def< TYPE >::copy(pdst, psrc, c);

      }

      inline static TYPE * alloc(::count c)
      {

         return heap::def < TYPE >::alloc(c);

      }


      inline static void _free(TYPE * p)
      {

         heap::def < TYPE >::_free(p);

      }

   };


   template < class TYPE >
   class def
   {

   public:

      inline static void construct(TYPE * p)
      {
         constructor::def< TYPE >::construct(p);
      }

      inline static void construct(TYPE * p, ::count c)
      {
         constructor::def< TYPE >::construct(p, c);

      }

      inline static void destruct(TYPE * p)
      {
         destructor::def< TYPE>::destruct(p);
      }
      inline static void destruct(TYPE * p, ::count c)
      {
         destructor::def< TYPE>::destruct(p, c);
      }


      inline static void copy(TYPE *pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline static void copy(TYPE *pdst, const TYPE * psrc, ::count c)
      {

         copier::def< TYPE >::copy(pdst, psrc, c);

      }

#if MEMDLEAK  || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char * pszFile, int iLine)
      {

         return heap::def < TYPE >::alloc(c, pszFile, iLine);

      }
#else
      inline static TYPE * alloc(::count c)
      {

         return heap::def < TYPE >::alloc(c);

      }

#endif


      inline static void _free(TYPE * p)
      {

         heap::def < TYPE >::_free(p);

      }


   };

   template < class TYPE >
   class nodef
   {

   public:

      inline static void construct(TYPE * p)
      {
         constructor::nodef< TYPE >::construct(p);
      }

      inline static void construct(TYPE * p, ::count c)
      {
         constructor::nodef< TYPE >::construct(p, c);

      }

      inline static void destruct(TYPE * p)
      {
         destructor::nodef< TYPE>::destruct(p);
      }
      inline static void destruct(TYPE * p, ::count c)
      {
         destructor::nodef< TYPE>::destruct(p, c);
      }


      inline static void copy(TYPE *pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline static void copy(TYPE *pdst, const TYPE * psrc, ::count c)
      {

         copier::def< TYPE >::copy(pdst, psrc, c);

      }

#if MEMDLEAK || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char  * pszFile, int iLine)
      {

         return heap::def < TYPE >::alloc(c, pszFile, iLine);

      }
#else
      inline static TYPE * alloc(::count c)
      {

         return heap::def < TYPE >::alloc(c);

      }
#endif


      inline static void _free(TYPE * p)
      {

         heap::def < TYPE >::_free(p);

      }


   };


   template < class TYPE >
   class zero
   {

   public:

      inline static void construct(TYPE * p)
      {
         constructor::zero< TYPE >::construct(p);
      }

      inline static void construct(TYPE * p, ::count c)
      {
         constructor::zero< TYPE >::construct(p, c);

      }

      inline static void destruct(TYPE * p)
      {
         destructor::nodef< TYPE>::destruct(p);
      }
      inline static void destruct(TYPE * p, ::count c)
      {
         destructor::nodef< TYPE>::destruct(p, c);
      }


      inline static void copy(TYPE *pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline static void copy(TYPE *pdst, const TYPE * psrc, ::count c)
      {

         copier::def< TYPE >::copy(pdst, psrc, c);

      }

#if MEMDLEAK || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char * pszFile, int iLine)
      {

         return heap::def < TYPE >::alloc(c, pszFile, iLine);

      }
#else
      inline static TYPE * alloc(::count c)
      {

         return heap::def < TYPE >::alloc(c);

      }
#endif


      inline static void _free(TYPE * p)
      {

         heap::def < TYPE >::_free(p);

      }


   };

   template < class TYPE >
   class sys
   {

   public:

      inline static void construct(TYPE * p)
      {
         constructor::def< TYPE >::construct(p);
      }

      inline static void construct(TYPE * p, ::count c)
      {
         constructor::def< TYPE >::construct(p, c);

      }

      inline static void destruct(TYPE * p)
      {
         destructor::def< TYPE>::destruct(p);
      }
      inline static void destruct(TYPE * p, ::count c)
      {
         destructor::def< TYPE>::destruct(p, c);
      }


      inline static void copy(TYPE *pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline static void copy(TYPE *pdst, const TYPE * psrc, ::count c)
      {

         copier::def< TYPE >::copy(pdst, psrc, c);

      }

#if MEMDLEAK || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char * pszFile, int iLine)
      {

         return heap::sys < TYPE >::alloc(c, pszFile, iLine);

      }
#else
      inline static TYPE * alloc(::count c)
      {

         return heap::sys < TYPE >::alloc(c);

      }
#endif

      inline static void _free(TYPE * p)
      {

         heap::sys < TYPE >::_free(p);

      }


   };

} // namespace allocator

  // raw_array is an array that does not call constructors or destructor in elements
  // array is an array that call only copy constructor and destructor in elements
  // array is an array that call default constructors, copy constructs and destructors in elements
template < class TYPE, class ALLOCATOR = allocator::nodef < TYPE > >
class array_base :
   virtual public ::object
{
public:

   typedef TYPE BASE_TYPE;


   //bool           m_bRaw;     // if raw, does not call destructors or constructors
   TYPE *         m_pData;    // the actual array of data
   ::count        m_nSize;    // # of elements (upperBound - 1)
   ::count        m_nMaxSize; // MAX allocated
   ::count        m_nGrowBy;  // grow amount

   array_base(int iTypeSize, bool bRaw);
   array_base(::aura::application * papp, int iTypeSize, bool bRaw);
   virtual ~array_base();

   inline ::count get_size() const;
   inline ::count get_size_in_bytes() const;
   inline ::count get_count() const;
   inline ::count get_byte_count() const;
   inline ::count size() const;
   inline ::count count() const;

   inline bool is_empty(::count countMinimum = 1) const;
   inline bool empty(::count countMinimum = 1) const;
   inline bool has_elements(::count countMinimum = 1) const;
   inline index get_upper_bound(index i = -1) const;


   TYPE * element_at(index i) const { return &m_pData[i]; }


   ::count set_size(index nNewSize, ::count nGrowBy = -1); // does not call default constructors on new items/elements
   ::count allocate(index nNewSize, ::count nGrowBy = -1); // does not call default constructors on new items/elements
   ::count allocate_in_bytes(index nNewSize, ::count nGrowBy = -1); // does not call default constructors on new items/elements
   ::count set_raw_size(index nNewSize, ::count nGrowBy = -1); // does not call constructors and destructors on items/elements
   ::count resize(index nNewSize, ::count nGrowBy = -1); // does not call default constructors on new items/elements
   void free_extra();
   virtual void destroy();

   void zero(index iStart = 0, ::count c = -1);


   inline void remove_last();
   inline ::count remove_all();
   inline void clear();


   void on_construct_element(TYPE * p) { ALLOCATOR::construct(p); }
   void on_construct_element(TYPE * p, ::count c) { ALLOCATOR::construct(p, c); }
   void on_destruct_element(TYPE * p) { ALLOCATOR::destruct(p); }
   void on_copy_element(index i, const TYPE * p) { ALLOCATOR::copy(&m_pData[i], p); }


   index insert_at(index nIndex, const TYPE * newElement, ::count nCount = 1);
   index remove_at(index nIndex, ::count nCount = 1);
   index insert_at(index nStartIndex, array_base * pNewArray);


   virtual ::count append(const array_base & src); // return old size
   virtual void copy(const array_base & src);

   virtual void on_after_read();

   template < typename PRED >
   ::count pred_each(PRED pred, index iStart = 0, ::count c = -1)
   {

      index iEnd = c < 0 ? get_count() + c : iStart + c - 1;

      int cProcessed = 0;

      for (index i = iStart; i <= iEnd; i++)
      {

         pred(m_pData[i]);

         cProcessed++;

      }

      return cProcessed;

   }

   template < typename PRED >
   index pred_find_first(PRED pred, index iStart = 0)
   {
      for (index i = iStart; i < get_count(); i++)
      {

         if (pred(m_pData[i]))
         {

            return i;

         }

      }

      return -1;

   }

   template < typename PRED >
   index pred_find_last(PRED pred, index iLast = -1)
   {

      if (iLast < 0)
      {

         iLast += get_count();

      }

      for (index i = iLast; i >= 0; i--)
      {

         if (pred(m_pData[i]))
         {

            return i;

         }

      }

      return -1;

   }

   template < typename PRED >
   TYPE * pred_get_first(PRED pred)
   {
      for (int i = 0; i < get_count(); i++)
      {

         if (pred(m_pData[i]))
         {

            return &element_at(i);

         }

      }

      return NULL;

   }


   template < typename PRED >
   ::count pred_get_count(PRED pred)
   {

      ::count c = 0;

      for (int i = 0; i < get_count(); i++)
      {

         if (pred(m_pData[i]))
         {

            c++;

         }

      }

      return c;

   }


   template < typename PRED >
   void pred_remove(PRED pred)
   {

      for (int i = 0; i < get_count();)
      {

         if (!pred(m_pData[i]))
         {
            i++;
         }
         else
         {

            int iStart = i;

            int iCount = 1;

            i++;

            for (; i < get_count();)
            {

               if (!pred(m_pData[i]))
               {

                  break;

               }

               iCount++;

               i++;

            }

            remove_at(iStart, iCount);

            i = iStart;

         }

      }

   }

   template < typename PRED >
   bool pred_add_unique(TYPE t, PRED pred)
   {

      if (this->pred_find_first(pred) >= 0)
      {

         return false;

      }

      this->add(t);

      return true;

   }
   template < typename F >
   void each(F f)
   {

      for (index i = 0; i < get_count(); i++)
      {
         f(m_pData[i]);
      }

   }


};
