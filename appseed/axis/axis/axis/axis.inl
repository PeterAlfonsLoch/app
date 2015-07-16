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

//#ifdef APPLEOS
//
//void * __cdecl operator new(size_t nSize) new_throw_spec;
//
//#else
//
//inline void * __cdecl operator new(size_t nSize) new_throw_spec
//{
//
//    return memory_alloc(nSize);
//
//}
//
//#endif




namespace file
{


   template < class T >
   bool system::output(::aura::application * papp,const ::file::path & pszOutput,T * p,bool (T::*lpfnOuput)(::file::ostream &,const ::file::path &),const ::file::path & lpszSource)
   {

      System.dir().mk(pszOutput.folder(),papp);

      ::file::buffer_sp fileOut = papp->m_paxissession->file().get_file(pszOutput,::file::mode_create | ::file::type_binary | ::file::mode_write);

      if(fileOut.is_null())
         return false;

      ::file::ostream ostream(fileOut);

      return (p->*lpfnOuput)(ostream,lpszSource);

   }

   /*
   template < class T >
   bool ::file::system::output(::aura::application * papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::file::ostream &, const char *), const char * lpszSource)
   {

   App(papp).dir().mk(Application.dir_name(pszOutput));

   ::file::buffer_sp fileOut = Sess(papp).file_get_file(pszOutput, ::file::mode_create | ::file::type_binary | ::file::mode_write);

   if(fileOut.is_null())
   return false;

   ::file::ostream ostream(fileOut);

   return (p->*lpfnOuput)(ostream, lpszSource);

   }
   */


   template < class T >
   bool ::file::system::output(::aura::application * papp,const ::file::path & pszOutput,T * p,bool (T::*lpfnOuput)(::file::ostream &,::file::istream &),const ::file::path & lpszInput)
   {

      App(papp).dir().mk(pszOutput.folder());

      string strDownloading = pszOutput;

      strDownloading += ".downloading";

      ::file::buffer_sp fileOut = Sess(papp).file().get_file(strDownloading,::file::mode_create | ::file::type_binary | ::file::mode_write);

      if(fileOut.is_null())
         return false;

      ::file::buffer_sp fileIn = Sess(papp).file().get_file(lpszInput,::file::type_binary | ::file::mode_read);

      if(fileIn.is_null())
         return false;

      {

         ::file::ostream ostream(fileOut);

         ::file::istream istream(fileIn);

         if(!(p->*lpfnOuput)(ostream,istream))
            return false;

      }

      try
      {

         fileOut->close();

      }
      catch(...)
      {

      }


      try
      {

         fileIn->close();

      }
      catch(...)
      {

      }

      if(::rename(strDownloading,pszOutput) != 0)
      {
         
         del(strDownloading, papp);

         return false;

      }

      return true;

   }



   template < class T >
   bool system::output(::aura::application * papp,const ::file::path & pszOutput,T * p,bool (T::*lpfnOuput)(::file::ostream &,::file::istream &),::file::istream & istream)
   {

      ::file::ostream ostream(get(pszOutput,papp));

      return (p->*lpfnOuput)(ostream,istream);

   }


} // namespace file




