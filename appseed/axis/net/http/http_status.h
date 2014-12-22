#pragma once


namespace http
{
   

   enum e_status
   {
      
      status_unchanged,
      status_ok,
      status_connection_timed_out,
      status_fail
         
         
   };


   bool CLASS_DECL_BASE succeeded(e_status estatus);
   bool CLASS_DECL_BASE status_succeeded(int64_t i);
   bool CLASS_DECL_BASE failed(e_status estatus);
   bool CLASS_DECL_BASE status_failed(int64_t i);


} // namespace http




