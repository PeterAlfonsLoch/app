// only windows and this component is certainly present.
// spa may not be installed
// if spa is installed, it may not be up-to-date.
// ca2 may not be installed
// if ca2 is installed, it may not be up-to-date.
// so certainly if windows and this component is installed,
// windows functions can be called and also minimal
// install_spaboot source code functions can be called.
#include <windows.h>
#include <WinINet.h>

// str.cpp
void strcat_dup(char * dest, const char * cat);
void strcpy_dup(char * dest, const char * cat);
int  strlen_dup(const char * cat);
const char * strdup_dup(const char * src);
const char * strstr_dup(const char * src, const char * find);
const char * stristr_dup(const char * src, const char * find);
char to_lower(int ch);
int stricmp_dup(const char * sz1, const char * sz2);
int strcmp_dup(const char * sz1, const char * sz2);
char * strrch_dup(char * sz, char ch);



// heap.cpp
void memset_dup(void * p, unsigned char uch, int iSize);
void memcpy_dup(void * dst, void * src, int iSize);
void * __cdecl malloc(size_t size);
void __cdecl free(void * p);



int cube_run(const char * id);
void execute_sync(SHELLEXECUTEINFOA * pinfoa);
void call_self_privileged_sync(const char * param);
int install_spaboot();

int install_npca2plugin();
int npca2plugin_start();

// http.cpp
void initialize_http_dup();
bool ms_download_dup(const char * host, const char * request, const char * pszFile);
const char * ms_get_dup(const char * host, const char * request);
const char * ca2_get_build();


// file.cpp
bool file_exists_dup(const char * path1);
bool read_resource_as_file_dup(const char * pszFile, HINSTANCE hinst, UINT nID, LPCTSTR lpcszType);
void get_ca2_folder(char * lpszModuleFolder);
const char * get_file_md5(const char * file);
bool is_file_ok(const char * path1, const char * pszTemplate);
bool file_put_contents(const char * path, const char * contents);
const char * file_get_contents_dup(const char * path);



// starter_start
void update_spa_installed();
void update_spa_updated();
void update_ca2_installed();
void update_ca2_updated();

bool is_spa_installed();
bool is_spa_updated();
bool is_ca2_installed();
bool is_ca2_updated();

//registry.cpp
int registry_register(const char * lpszFile);


int seal_spaboot_installation();


//void __cdecl _null_se_translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers);

int starter_start(const char * id);

const char * read_resource_as_string_dup(HINSTANCE hinst, UINT nID, LPCTSTR lpcszType);

void spa_platform_cat_dup(char * psz);

void get_ca2_folder_dup(char * lpszModuleFolder);

void call_privileged_sync(const char * path, const char * param);


void initialize_heap();
void finalize_heap();

