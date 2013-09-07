#ifndef _UTIL__UTIL_
#define _UTIL__UTIL_

template<class TYPE> static void freePointer(TYPE * * pointer);
//template<class TYPE> void CMemory::freePointer(TYPE * * pointer)
template<class TYPE> void freePointer(TYPE * * pointer)
{
   free((void *) *pointer);
   *pointer = NULL;
}

CLASS_DECL_ca2 ::user::menu *  FindPopupMenuFromID(::user::menu * pMenu, UINT nID, UINT nData);
CLASS_DECL_ca2 ::user::menu *  FindPopupMenuFromID(::user::menu * pMenu, UINT nID);


namespace core
{
//   string CLASS_DECL_ca2 file_as_string(const char * lpcsz);
//   bool CLASS_DECL_ca2 file_put_contents(const char * lpcszFileNmae, const char * lpcszContents);
//   void CLASS_DECL_ca2 mkdirp(const char * lpcszFolderPath);
//   void CLASS_DECL_ca2 split_path(stringa & stra, const char * lpcszPath);
//   void CLASS_DECL_ca2 mkdir(const char * lpcszFolderPath);
//   bool CLASS_DECL_ca2 is_dir(const char * lpcszCandidate);

   
} //namespace core

#endif // _UTIL__UTIL_