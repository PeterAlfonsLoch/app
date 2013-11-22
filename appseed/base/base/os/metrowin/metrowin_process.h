#pragma once


CLASS_DECL_BOOT void call_sync(const char * path, const char * param);


CLASS_DECL_BOOT bool process_modules(stringa & stra, DWORD processID);

   
CLASS_DECL_BOOT bool load_modules_diff(stringa & straOld, stringa & straNew, const char * pszExceptDir);



