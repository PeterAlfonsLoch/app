#pragma once


namespace webserver
{


   namespace music
   {


      class CLASS_DECL_ca song_source :
         public dynamic_source::ptr
      {
      public:


         string m_strName;
         string m_strUrl;
         string m_strEmail;


      };


   } // namespace music


} // namespace webserver


