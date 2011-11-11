#pragma once


namespace webserver
{


   namespace fun
   {


      class CLASS_DECL_ca friend_search :
         virtual public dynamic_source::ptr
      {
      public:

         var m_usera;
         int m_iPage;
         int m_iStartRecord;
         int m_iRecordsPerPage;
         int64_t m_iFunUserCount;
         int64_t m_iPageCount;


         friend_search(int iPage);

         var get_friends(int iStartRecord, int iRecordPerPage);

         void print_nav();

         void print_friends();

      };


   } // namespace fun


} // namespace webserver


