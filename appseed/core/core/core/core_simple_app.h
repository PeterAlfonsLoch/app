#pragma once


namespace core
{

   class CLASS_DECL_CORE app:
      virtual public ::base::app
   {
   public:


      app();
      virtual ~app();


      template < class APP >
      static int32_t s_main()
      {

         if(!defer_core_init())
         {
            return -1;
         }

         APP  * papp = new APP;

         int32_t iRet = papp->main();

         try
         {

            delete papp;

            papp = NULL;

         }
         catch(...)
         {
         }

         defer_core_term();

         return iRet;

      }

   };


} // namespace core




