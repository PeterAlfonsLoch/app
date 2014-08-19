#pragma once


CLASS_DECL_BASE void call_sync(const char * path, const char * param);


CLASS_DECL_BASE bool process_modules(stringa & stra, uint32_t processID);

   
CLASS_DECL_BASE bool load_modules_diff(stringa & straOld, stringa & straNew, const char * pszExceptDir);



