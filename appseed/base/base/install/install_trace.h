#pragma once

CLASS_DECL_BASE void ensure_trace_file();

CLASS_DECL_BASE void trace(const char * psz);

CLASS_DECL_BASE void trace_add(const char * psz);

CLASS_DECL_BASE void trace_progress(double dRate);

CLASS_DECL_BASE bool initialize_primitive_trace();

CLASS_DECL_BASE void finalize_primitive_trace();
