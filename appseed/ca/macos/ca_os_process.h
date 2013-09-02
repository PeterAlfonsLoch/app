#pragma once


CLASS_DECL_c void call_sync(const char * path, const char * param);
CLASS_DECL_c int create_process(const char * _cmd_line, int * pprocessId);
CLASS_DECL_c int get_process_pid(const char * csProcessName);
