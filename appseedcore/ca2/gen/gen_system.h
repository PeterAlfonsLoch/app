#pragma once


namespace gen
{

   class CLASS_DECL_ca system :
      public ::ca::system
   {
   public:


      system();
      virtual ~system();


      using ::ca::system::id;
      inline class id id(const var & var);
      inline class id id(const gen::property & prop);


   };

   inline id system::id(const class var & var)
   {
      return ::id((const char *) (class var &) var);
   }

   inline id system::id(const gen::property & prop)
   {
      return ::id((const char *) (gen::property &) prop);
   }

} // namespace gen