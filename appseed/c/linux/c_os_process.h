#pragma once


CLASS_DECL_c void call_sync(const char * path, const char * param);
int create_process(const char * _cmd_line, int * pprocessId);
int get_process_pid(const char * procNameParam);
