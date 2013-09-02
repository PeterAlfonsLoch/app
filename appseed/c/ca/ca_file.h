#pragma once;


class simple_memory;


CLASS_DECL_c bool file_get_memory_dup(simple_memory & memory, const char * path);
CLASS_DECL_c bool file_put_contents_dup(const char * path, const simple_memory & memory);


CLASS_DECL_c vsstring get_file_md5(const char * file);


CLASS_DECL_c vsstring file_title_dup(const char * path);
CLASS_DECL_c vsstring file_name_dup(const char * path);
CLASS_DECL_c vsstring file_module_path_dup();


inline bool file_put_contents_dup(const char * path, const char * contents) { return file_put_contents_dup(path, contents, -1) != FALSE; }


#ifdef WINDOWS
CLASS_DECL_c void file_read_n_number_dup(HANDLE hfile, ::md5::md5 * pctx, int32_t & iNumber);
CLASS_DECL_c void file_read_gen_string_dup(HANDLE hfile, ::md5::md5 * pctx, vsstring & str);
#else
CLASS_DECL_c void file_read_n_number_dup(FILE * hfile, ::md5::md5 * pctx, int32_t & iNumber);
CLASS_DECL_c void file_read_gen_string_dup(FILE * hfile, ::md5::md5 * pctx, vsstring & str);
#endif


CLASS_DECL_c vsstring file_get_mozilla_firefox_plugin_container_path();


CLASS_DECL_c bool file_copy_dup(const char * pszDup, const char * pszSrc) {return file_copy_dup(pszDup, pszSrc, true) != FALSE;}

CLASS_DECL_c vsstring get_sys_temp_path();
