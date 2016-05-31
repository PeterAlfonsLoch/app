#pragma once


CLASS_DECL_AURA void call_sync(const char * path, const char * param);
int32_t create_process(const char * _cmd_line, int32_t * pprocessId);
int32_t get_process_pid(const char * procNameParam);
