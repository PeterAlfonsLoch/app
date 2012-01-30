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


} // namespace colorertake5


