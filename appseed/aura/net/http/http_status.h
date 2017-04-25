#pragma once


namespace http
{
   

   enum e_status
   {
      
      status_unchanged,
      status_ok,
      status_connection_timed_out,
      status_timed_out,
      status_fail
         
         
   };


   bool CLASS_DECL_AURA succeeded(e_status estatus);
   bool CLASS_DECL_AURA status_succeeded(int64_t i);
   bool CLASS_DECL_AURA failed(e_status estatus);
   bool CLASS_DECL_AURA status_failed(int64_t i);

   CLASS_DECL_AURA string conn_status(property_set & set);


} // namespace http




