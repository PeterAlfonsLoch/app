#pragma once

CLASS_DECL_c void ensure_trace_file();

CLASS_DECL_c void trace(const char * psz);

CLASS_DECL_c void trace_add(const char * psz);

CLASS_DECL_c void trace_progress(double dRate);

CLASS_DECL_c bool initialize_primitive_trace();

CLASS_DECL_c void finalize_primitive_trace();
