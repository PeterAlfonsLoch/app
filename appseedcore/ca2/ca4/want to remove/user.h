#pragma once

namespace ca27
{

   class CLASS_DECL_ca2api00200002 user :
      public ca2::user
   {
   public:
      user();
      virtual ~user();
      ::http::cookies * m_phttpcookies;

      static ca27::user * cast(ca2::user * puser);
   };



} // namespace ca27

#undef User
#define User(pbaseuser)  ca27::user::cast(pbaseuser)