#pragma once


CLASS_DECL_AURA int_bool ensure_file_size_fd(int32_t fd, size_t iSize);
CLASS_DECL_AURA size_t get_file_size(int32_t fd);

BEGIN_EXTERN_C

CLASS_DECL_AURA int is_dir(const char * path1);

END_EXTERN_C


