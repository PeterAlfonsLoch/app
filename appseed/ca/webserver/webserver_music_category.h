#pragma once


namespace webserver
{

   namespace music
   {

      class CLASS_DECL_ca category : 
         public dynamic_source::ptr
      {
      public:


         var m_id;
         var m_navid;
         var m_name;
         var m_performercount;
         var m_songcount;
         var m_parentid;
         var m_childrenclass;


         category();


      };


   } // namespace music


} // namespace webserver


