#pragma once


namespace user
{

   class printer;


} // namespace user


namespace cubebase
{


   class CLASS_DECL_ca2 application : 
      virtual public ::plane::application,
      virtual public ca::smart_pointer < ::cubebase::application >
   {
   public:


      application();
      virtual ~application();


      virtual bool initialize1();
      virtual bool initialize();


      ::ca::application * get_system();


      virtual bool is_cube();

      
      virtual void CubeOnFactoryExchange();


      virtual ::user::printer * get_printer(const char * pszDeviceName);



      // ca::smart_pointer < ::cubebase::application >::oattrib
      // or any function needing it
      application & operator = (const application & app)
      {

         UNREFERENCED_PARAMETER(app);

         // do nothing

         return *this;

      }

      // get a file and if there are exceptions, should show end user friendly messages
      virtual ::ex1::filesp friendly_get_file(var varFile, UINT nOpenFlags);



   };



} // namespace cube


