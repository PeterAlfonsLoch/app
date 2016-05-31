#pragma once


CLASS_DECL_AURA void call_sync(const char * path, const char * param);
CLASS_DECL_AURA int create_process(const char * _cmd_line, int * pprocessId);
CLASS_DECL_AURA int get_process_pid(const char * csProcessName);
