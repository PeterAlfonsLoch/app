#pragma once


struct __POSITION {};
typedef __POSITION* POSITION;
#define BEFORE_START_POSITION ((POSITION)-1L)


template<class TYPE, class ARG_TYPE>
BOOL simple_CompareElements(const TYPE* pElement1, const ARG_TYPE* pElement2)
{
   return *pElement1 == *pElement2;
}


template<class ARG_KEY>
inline UINT simple_HashKey(ARG_KEY key)
{
   // default identity hash - works for most primitive values
   return (DWORD)(((DWORD_PTR)key)>>4);
}



template<> CLASS_DECL_____ UINT simple_HashKey<const wchar_t *> (const wchar_t * key);
template<> CLASS_DECL_____ UINT simple_HashKey<const char *> (const char * key);
template<> CLASS_DECL_____ UINT simple_HashKey<verisimple_string> (verisimple_string key);
template<> CLASS_DECL_____ UINT simple_HashKey<verisimple_wstring> (verisimple_wstring key);
/*template<> CLASS_DECL_____ UINT HashKey<vsstring> (vsstring key);
template<> CLASS_DECL_____ UINT HashKey<wstring> (wstring key);*/
