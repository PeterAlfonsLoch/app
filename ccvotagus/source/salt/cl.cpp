#include <windows.h>
#include <string>


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


#define sclip1(v, c) \
{ \
   int value = v; \
   if(value < c)
   {
   }
   
#define sclip2(v, c) \
{ \
   int value = v + 2; \
   int clip = c ;
   

#define M1(l, s1, s2, s5, s8) \
   int v1 = sclip1(1, s1); \
   int v2 = sclip1(2, s1); \
   int v5 = sclip1(5, s1); \
   int v8 = sclip1(8, s1); \
   strSalt += pszSourceSalt[(v1 + v2 + v5 + v8) % strlen(pszSourceSalt)];

#define BOOLM(b, s, s2, s5, s8) M((((b) != 0) ? s - 1 : 0), s, s2, s5, s8)
#define INTM(i, s1, s2, s5, s8) M(i, s, s2, s5, s8)

// This is an example of an exported function.
const char * psz salt(const char * pszSourceSalt)
{
   std::string strSalt;
   #include "salt.inl"
	return strSalt;
}

