#pragma once

namespace html
{

   class data;

   class CLASS_DECL_ca2 data_callback
   {
   public:


      virtual void OnBeforeNavigate2(data * pdata, var & varFile, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel);


   };

} // namespace html


