#pragma once

CLASS_DECL_ca void ensure_trace_file();

CLASS_DECL_ca void trace(const char * psz);

CLASS_DECL_ca void trace_add(const char * psz);

CLASS_DECL_ca void trace_progress(double dRate);

CLASS_DECL_ca bool initialize_primitive_trace();

CLASS_DECL_ca void finalize_primitive_trace();
