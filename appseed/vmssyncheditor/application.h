#pragma once

namespace vmssyncheditor
{

   class application : 
      public ca84::application
   {
   public:
	   application();

      bool MessageWindowListener(unsigned int,unsigned int,long);

	   virtual bool initialize_instance();

	   DECL_GEN_SIGNAL(_001OnAppAbout)
   };




} // namespace vmssyncheditor