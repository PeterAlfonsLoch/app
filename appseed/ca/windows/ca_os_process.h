#pragma once


CLASS_DECL_ca void call_sync(const char * path, const char * param);


CLASS_DECL_ca bool process_modules(stra_dup & stra, uint32_t processID);

   
CLASS_DECL_ca bool load_modules_diff(stra_dup & straOld, stra_dup & straNew, const char * pszExceptDir);



