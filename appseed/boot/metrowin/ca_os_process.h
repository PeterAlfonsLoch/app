#pragma once


CLASS_DECL_ca void call_sync(const char * path, const char * param);


CLASS_DECL_ca bool process_modules(stringa & stra, DWORD processID);

   
CLASS_DECL_ca bool load_modules_diff(stringa & straOld, stringa & straNew, const char * pszExceptDir);



