#pragma once


#include <limits.h>
#include <memory.h>
#include <float.h>

namespace numeric_info_internal
{

   class numeric_info_base
   {
   public:

      static const bool is_signed = false;
      static const bool is_integer = false;

   };


   template < typename T >
   class numeric_info:
      public numeric_info_base
   {
   public:

      typedef T TYPE;
      typedef T OFFSET_TYPE;

      static inline TYPE maximum(){ return (TYPE) 0; }
      static inline TYPE minimum(){ return (TYPE) 0; }
      static inline TYPE null(){ return (TYPE) 0; }
      static inline TYPE unitary(){ return (TYPE) 1; }
      static inline TYPE allset(){ TYPE t; memset(&t,0xff,sizeof(TYPE)); return t; }



   };


   class numeric_integer_base:
      public numeric_info_base
   {
   public:

      static const bool is_integer = true;

   };


   class numeric_floating_base:
      public numeric_info_base
   {
   public:

      static const bool is_integer = false;

   };


   template < >
   class CLASS_DECL_AURA numeric_info < int8_t > :
   public numeric_integer_base
   {
   public:

      typedef int8_t TYPE;
      typedef int8_t OFFSET_TYPE;

      static inline TYPE maximum(){ return (TYPE)CHAR_MAX; }
      static inline TYPE minimum(){ return (TYPE)CHAR_MIN; }
      static inline TYPE null(){ return (TYPE)0; }
      static inline TYPE unitary(){ return (TYPE)1; }
      static inline TYPE allset(){ TYPE t; memset(&t,0xff,sizeof(TYPE)); return t; }

      static const bool is_signed = true;

   };

   template < >
   class CLASS_DECL_AURA numeric_info < uint8_t > :
   public numeric_integer_base
   {
   public:

      typedef uint8_t TYPE;
      typedef int8_t OFFSET_TYPE;

      static inline TYPE maximum(){ return (TYPE)UCHAR_MAX; }
      static inline TYPE minimum(){ return (TYPE)0; }
      static inline TYPE null(){ return (TYPE)0; }
      static inline TYPE unitary(){ return (TYPE)1; }
      static inline TYPE allset(){ TYPE t; memset(&t,0xff,sizeof(TYPE)); return t; }

      static const bool is_signed = false;

   };
   template < >
   class CLASS_DECL_AURA numeric_info < int16_t > :
   public numeric_integer_base
   {
   public:

      typedef int16_t TYPE;
      typedef int16_t OFFSET_TYPE;

      static inline TYPE maximum(){ return (TYPE)SHRT_MAX; }
      static inline TYPE minimum(){ return (TYPE)SHRT_MIN; }
      static inline TYPE null(){ return (TYPE)0; }
      static inline TYPE unitary(){ return (TYPE)1; }
      static inline TYPE allset(){ TYPE t; memset(&t,0xff,sizeof(TYPE)); return t; }

      static const bool is_signed = true;

   };

   template < >
   class CLASS_DECL_AURA numeric_info < uint16_t > :
   public numeric_integer_base
   {
   public:

      typedef uint16_t TYPE;
      typedef int16_t OFFSET_TYPE;

      static inline TYPE maximum(){ return (TYPE)USHRT_MAX; }
      static inline TYPE minimum(){ return (TYPE)0; }
      static inline TYPE null(){ return (TYPE)0; }
      static inline TYPE unitary(){ return (TYPE)1; }
      static inline TYPE allset(){ TYPE t; memset(&t,0xff,sizeof(TYPE)); return t; }

      static const bool is_signed = false;

   };

   template < >
   class CLASS_DECL_AURA numeric_info < int32_t > :
   public numeric_integer_base
   {
   public:

      typedef int32_t TYPE;
      typedef int32_t OFFSET_TYPE;

      static inline TYPE maximum(){ return (TYPE)INT_MAX; }
      static inline TYPE minimum(){ return (TYPE)INT_MIN; }
      static inline TYPE null(){ return (TYPE)0; }
      static inline TYPE unitary(){ return (TYPE)1; }
      static inline TYPE allset(){ TYPE t; memset(&t,0xff,sizeof(TYPE)); return t; }

      static const bool is_signed = true;

   };

   template < >
   class CLASS_DECL_AURA numeric_info < uint32_t > :
   public numeric_integer_base
   {
   public:

      typedef uint32_t TYPE;
      typedef int32_t OFFSET_TYPE;

      static inline TYPE maximum(){ return (TYPE)UINT_MAX; }
      static inline TYPE minimum(){ return (TYPE)0; }
      static inline TYPE null(){ return (TYPE)0; }
      static inline TYPE unitary(){ return (TYPE)1; }
      static inline TYPE allset(){ TYPE t; memset(&t,0xff,sizeof(TYPE)); return t; }

      static const bool is_signed = false;

   };

   template < >
   class CLASS_DECL_AURA numeric_info < int64_t > :
   public numeric_integer_base
   {
   public:

      typedef int64_t TYPE;
      typedef int64_t OFFSET_TYPE;

      static inline TYPE maximum(){ return (TYPE)LLONG_MAX; }
      static inline TYPE minimum(){ return (TYPE)LLONG_MIN; }
      static inline TYPE null(){ return (TYPE)0; }
      static inline TYPE unitary(){ return (TYPE)1; }
      static inline TYPE allset(){ TYPE t; memset(&t,0xff,sizeof(TYPE)); return t; }

      static const bool is_signed = true;

   };

   template < >
   class CLASS_DECL_AURA numeric_info < uint64_t >:
   public numeric_integer_base
   {
   public:

      typedef uint64_t TYPE;
      typedef int64_t OFFSET_TYPE;

      static inline TYPE maximum(){ return (TYPE)ULLONG_MAX; }
      static inline TYPE minimum(){ return (TYPE)0; }
      static inline TYPE null(){ return (TYPE)0; }
      static inline TYPE unitary(){ return (TYPE)1; }
      static inline TYPE allset(){ TYPE t; memset(&t,0xff,sizeof(TYPE)); return t; }

      static const bool is_signed = false;

   };


   template < >
   class CLASS_DECL_AURA numeric_info < float >:
   public numeric_floating_base
   {
   public:

      typedef float TYPE;
      typedef float OFFSET_TYPE;

      static inline TYPE maximum(){ return (TYPE)FLT_MAX; }
      static inline TYPE minimum(){ return (TYPE)FLT_MIN; }
      static inline TYPE null(){ return (TYPE)0.f; }
      static inline TYPE unitary(){ return (TYPE)1.f; }
      static inline TYPE allset(){ TYPE t; memset(&t,0xff,sizeof(TYPE)); return t; }

   };



   template < >
   class CLASS_DECL_AURA numeric_info < double >:
   public numeric_floating_base
   {
   public:

      typedef double TYPE;
      typedef double OFFSET_TYPE;


      static inline TYPE maximum(){ return (TYPE)DBL_MAX; }
      static inline TYPE minimum(){ return (TYPE)DBL_MIN; }
      static inline TYPE null(){ return (TYPE)0.0; }
      static inline TYPE unitary(){ return (TYPE)1.0; }
      static inline TYPE allset(){ TYPE t; memset(&t,0xff,sizeof(TYPE)); return t; }

      static const bool is_signed = false;

   };


} // namespace numeric_info_internal



template < typename T > 
class numeric_info:
   public numeric_info_internal::numeric_info < T >
{
public:
   
   typedef numeric_info_internal::numeric_info < T > INTERNAL_INFO;
   
   static inline typename numeric_info_internal::numeric_info < T >::TYPE maximum() { return INTERNAL_INFO::maximum(); }
   static inline typename numeric_info_internal::numeric_info < T >::TYPE minimum() { return INTERNAL_INFO::minimum(); }
   static inline typename numeric_info_internal::numeric_info < T >::TYPE null() { return INTERNAL_INFO::null(); }
   static inline typename numeric_info_internal::numeric_info < T >::TYPE unitary() { return INTERNAL_INFO::unitary(); }
   static inline typename numeric_info_internal::numeric_info < T >::TYPE allset() { return INTERNAL_INFO::allset(); }

   static inline typename numeric_info_internal::numeric_info < T >::TYPE get_maximum_value() { return maximum(); }
   static inline typename numeric_info_internal::numeric_info < T >::TYPE get_minimum_value() { return minimum(); }
   static inline typename numeric_info_internal::numeric_info < T >::TYPE get_null_value() { return null(); }
   static inline typename numeric_info_internal::numeric_info < T >::TYPE get_unitary_value() { return unitary(); }
   static inline typename numeric_info_internal::numeric_info < T >::TYPE get_allset_value() { return allset(); }

   static inline typename numeric_info_internal::numeric_info < T >::TYPE get_maximum() { return get_maximum_value(); }
   static inline typename numeric_info_internal::numeric_info < T >::TYPE get_minimum() { return get_minimum_value(); }
   static inline typename numeric_info_internal::numeric_info < T >::TYPE get_null() { return get_null_value(); }
   static inline typename numeric_info_internal::numeric_info < T >::TYPE get_unitary() { return get_unitary_value(); }
   static inline typename numeric_info_internal::numeric_info < T >::TYPE get_allset() { return get_allset_value(); }

   static inline typename numeric_info_internal::numeric_info < T >::TYPE maximum_value() { return get_maximum(); }
   static inline typename numeric_info_internal::numeric_info < T >::TYPE minimum_value() { return get_minimum(); }
   static inline typename numeric_info_internal::numeric_info < T >::TYPE null_value() { return get_null(); }
   static inline typename numeric_info_internal::numeric_info < T >::TYPE unitary_value() { return get_unitary(); }
   static inline typename numeric_info_internal::numeric_info < T >::TYPE allset_value() { return get_allset(); }

   static inline typename numeric_info_internal::numeric_info < T >::TYPE min() { return get_minimum_value(); }
   static inline typename numeric_info_internal::numeric_info < T >::TYPE max() { return get_maximum_value(); }

   template < typename T2 >
   static inline typename numeric_info_internal::numeric_info < T >::TYPE natural(const T2 & t2) { return MIN(max(), MAX(null(), (T) t2)); }

};


template < typename T, typename T2 >
inline T clip_assign(T & t, const T2 & t2)
{ 
   t = MIN(::numeric_info < T >::max(),MAX(::numeric_info < T >::min(),(T)t2));
}

template < typename T,typename T2 >
inline T natural_assign(T & t,const T2 & t2)
{
   t = MIN(::numeric_info < T >::max(),MAX(::numeric_info < T >::null(),(T)t2));
}



template <typename T>
int sgn(T val)
{
   return (::numeric_info < T >::null() < val) - (val < ::numeric_info < T >::null());
}