#pragma once


#pragma once


namespace user
{


   class CLASS_DECL_AURA interactive :
      virtual public ::object
   {
   public:


      virtual string fontopus_get_cred(::aura::application * papp, const string & strRequestUrl, const RECT & rect, string & strUsername, string & strPassword, string strToken, string strTitle, bool bInteractive, ::user::interactive * pinteractive = NULL);


   };


} // namespace user




