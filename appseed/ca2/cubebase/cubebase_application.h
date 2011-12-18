#pragma once


namespace cubebase
{


   class CLASS_DECL_ca2 application : 
      virtual public ::plane::application
   {
   public:


      application();
      virtual ~application();


      virtual bool initialize1();
      virtual bool initialize();


      ::ca::application * get_system();


      virtual bool is_cube();

   };


   inline application & app_cast(::ca::application * papp)
   {
      return *(dynamic_cast < application * > (papp));
   }


} // namespace cube


