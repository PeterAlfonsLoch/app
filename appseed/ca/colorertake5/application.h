#pragma once


namespace colorertake5
{


   class CLASS_DECL_ca application :
      virtual public ::calculator::application
   {
   public:


      ParserFactory * m_pparserfactory;


      application();
      virtual ~application();

      ParserFactory & parser_factory();

      virtual bool initialize();

   };


   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }


} // namespace colorertake5


