#pragma once


namespace gen
{

   typedef CLASS_DECL_ca primitive::memory_file < primitive::memory > memory_file;

} // namespace gen


// vc6 workaround
typedef CLASS_DECL_ca ::gen::memory_file gen_memory_file;
