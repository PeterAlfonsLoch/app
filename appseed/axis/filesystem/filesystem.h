#pragma once


//#include "file/file.h"



namespace file
{
   
   
   // 'n' (natural) terminated ascii number, example: 245765487n
   CLASS_DECL_AXIS void write_n_number(::file::buffer_sp  pfile,MD5_CTX * pctx,int64_t iNumber);
   CLASS_DECL_AXIS void read_n_number(::file::buffer_sp  pfile,MD5_CTX * pctx,int64_t & iNumber);

   CLASS_DECL_AXIS void write_gen_string(::file::buffer_sp  pfile,MD5_CTX * pctx,string & str);
   CLASS_DECL_AXIS void read_gen_string(::file::buffer_sp  pfile,MD5_CTX * pctx,string & str);


} // namespace file