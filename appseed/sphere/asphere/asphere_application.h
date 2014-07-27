#pragma once


namespace user
{

   class printer;


} // namespace user


namespace asphere
{


   class CLASS_DECL_sphere application : 
      virtual public ::core::application
   {
   public:


      application();
      virtual ~application();


      virtual bool initialize1();
      virtual bool initialize();



   };



} // namespace sphere


