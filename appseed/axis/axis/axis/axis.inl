#pragma once


//template<class TYPE>
//void dump_elements(dump_context & dumpcontext, const TYPE* pElements, ::count nCount)
//{
//   ENSURE(nCount == 0 || pElements != NULL);
//   ASSERT(nCount == 0 ||
//      __is_valid_address(pElements, (size_t)nCount * sizeof(TYPE), FALSE));
//#ifdef WINDOWS
//   &dumpcontext; // not used
//   pElements;  // not used
//   nCount; // not used
//#endif
//   // default does nothing
//}
//
//
//template<class TYPE>
//inline void CopyElements(TYPE* pDest, const TYPE* pSrc, ::count nCount)
//{
//   ENSURE(nCount == 0 || pDest != 0 && pSrc != 0);
//   ASSERT(nCount == 0 ||
//      __is_valid_address(pDest, (size_t)nCount * sizeof(TYPE)));
//   ASSERT(nCount == 0 ||
//      __is_valid_address(pSrc, (size_t)nCount * sizeof(TYPE)));
//
//   // default is element-copy using assignment
//   while (nCount--)
//      *pDest++ = *pSrc++;
//}



#undef new





namespace file
{


   namespace axis
   {


      template < class T >
      bool system::output(::aura::application * papp, const path & pszOutput, const path & lpszSource)
      {

         return output(papp, pszOutput, &System.compress(), &::axis::compress::null, lpszSource);

      }


      template < class T >
      bool system::output(::aura::application * papp, const path & pszOutput, ::file::file * pfileIn)
      {

         return output(papp, pszOutput, &System.compress(), &::axis::compress::null, pfileIn);

      }


      template < class T >
      bool system::output(::aura::application * papp, const path & pszOutput, ::file::istream & istream)
      {

         return output(papp, pszOutput, &System.compress(), &::axis::compress::null, istream);

      }


      template < class T >
      bool application::output(const path & pszOutput, const path & lpszSource)
      {

         return output(pszOutput, &System.compress(), &::axis::compress::null, lpszSource);

      }


      template < class T >
      bool application::output(const path & pszOutput, ::file::file * pfileIn)
      {

         return output(pszOutput, &System.compress(), &::axis::compress::null, pfileIn);

      }


      template < class T >
      bool application::output(const path & pszOutput, ::file::istream & istream)
      {

         return output(pszOutput, &System.compress(), &::axis::compress::null, istream);

      }


   }

} // namespace file




