#pragma once


WINBOOL AfxInternalPreTranslateMessage(MESSAGE* pMsg);


namespace macos
{

   

   
   class CLASS_DECL_AURA thread :
      virtual public ::ansios::thread_impl
   {
   public:
      

      
      thread(::aura::application * papp);
      virtual ~thread();
      
      

      
      
   };
 


} // namespace macos




