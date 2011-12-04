#pragma once


namespace ca2
{


   namespace fs
   {


      class CLASS_DECL_ca2 application :
         virtual public ::userex::application
      {
      public:




         application();
         virtual ~application();

         bool initialize();


      };


   } // namespace fs


} // namespace ca2



