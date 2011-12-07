#pragma once


namespace webserver
{


   namespace fun
   {


      class CLASS_DECL_ca user :
         virtual public dynamic_source::ptr
      {
      public:


         int      m_iId;
         int      m_iImage;
         string   m_strName;
         string   m_strFirstName;
         string   m_strLastName;
         string   m_strEmail;
         int      m_iMergeId;
         string   m_strCurrentBoard;
         comparable_array < user * > m_userptraMerge;
         void prepare();
         double get_credit();
         bool votagus(const char * pszId);


      };


   } // namespace fun


} // namespace webserver


