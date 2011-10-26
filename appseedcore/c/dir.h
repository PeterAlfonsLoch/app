#pragma once

#define PATH_SEPARATOR "\\"

class dir
{
public:
   static CLASS_DECL_____ vsstring beforeca2();
   static CLASS_DECL_____ vsstring ca2(const char * path1 = NULL, const char * path2 = NULL, const char * path3 = NULL, const char * path4 = NULL);
   static CLASS_DECL_____ vsstring afterca2();
   static CLASS_DECL_____ vsstring module_folder(const char * path = NULL);
   static CLASS_DECL_____ vsstring path(const char * path1, const char * path2, const char * path3 = NULL, const char * path4 = NULL, const char * path5 = NULL);
   static CLASS_DECL_____ vsstring name(const char * path1);
   static CLASS_DECL_____ vsstring appdata(const char * lpcsz);
   static CLASS_DECL_____ bool exists(const char * path1);
   static CLASS_DECL_____ bool mk(LPCTSTR lpcsz);
};
