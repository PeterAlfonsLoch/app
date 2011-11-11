#pragma once


namespace webserver
{


   class CLASS_DECL_ca cynce_database :
      virtual public database
   {
   public:
      cynce_database(::ca::application * papp);
      virtual bool initialize();



   };


} // namespace webserver


