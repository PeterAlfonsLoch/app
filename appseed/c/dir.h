#pragma once


#define PATH_SEPARATOR "\\"


class stra_dup;


class dir
{
public:


   static CLASS_DECL_c vsstring beforeca2();
   static CLASS_DECL_c vsstring ca2(const char * path1 = NULL, const char * path2 = NULL, const char * path3 = NULL, const char * path4 = NULL);
   static CLASS_DECL_c vsstring afterca2();
   static CLASS_DECL_c vsstring module_folder(const char * path = NULL);
   static CLASS_DECL_c vsstring path(const char * path1, const char * path2, const char * path3 = NULL, const char * path4 = NULL, const char * path5 = NULL);
   static CLASS_DECL_c vsstring name(const char * path1);
   static CLASS_DECL_c vsstring appdata(const char * lpcsz);
   static CLASS_DECL_c bool exists(const char * path1);
   static CLASS_DECL_c bool mk(LPCTSTR lpcsz);
   static CLASS_DECL_c void ls(stra_dup & stra, const char *psz);


};



