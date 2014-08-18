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


   bool CLASS_DECL_AXIS succeeded(e_status estatus);
   bool CLASS_DECL_AXIS status_succeeded(int64_t i);
   bool CLASS_DECL_AXIS failed(e_status estatus);
   bool CLASS_DECL_AXIS status_failed(int64_t i);


} // namespace http




