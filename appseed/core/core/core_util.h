#ifndef _UTIL__UTIL_
#define _UTIL__UTIL_

template<class TYPE> static void freePointer(TYPE * * pointer);
//template<class TYPE> void CMemory::freePointer(TYPE * * pointer)
template<class TYPE> void freePointer(TYPE * * pointer)
{
   free((void *) *pointer);
   *pointer = NULL;
}

CLASS_DECL_CORE ::user::menu *  FindPopupMenuFromID(::user::menu * pMenu, UINT nID, UINT nData);
CLASS_DECL_CORE ::user::menu *  FindPopupMenuFromID(::user::menu * pMenu, UINT nID);


namespace core
{
//   string CLASS_DECL_CORE file_as_string(const char * lpcsz);
//   bool CLASS_DECL_CORE file_put_contents(const char * lpcszFileNmae, const char * lpcszContents);
//   void CLASS_DECL_CORE mkdirp(const char * lpcszFolderPath);
//   void CLASS_DECL_CORE split_path(stringa & stra, const char * lpcszPath);
//   void CLASS_DECL_CORE mkdir(const char * lpcszFolderPath);
//   bool CLASS_DECL_CORE is_dir(const char * lpcszCandidate);

   
} //namespace core

#endif // _UTIL__UTIL_