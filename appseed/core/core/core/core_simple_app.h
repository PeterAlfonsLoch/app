#pragma once


namespace core
{

   class CLASS_DECL_CORE simple_app:
      virtual public ::base::simple_app
   {
   public:


      simple_app();
      virtual ~simple_app();


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




