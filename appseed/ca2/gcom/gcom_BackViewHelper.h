#pragma once

namespace gcom
{
   namespace backview
   {
      class Main;

      class CLASS_DECL_ca2 Helper : 
         virtual public ::ca::object
      {
      private:
         Main & m_main;

      public:
         Helper(Main & main);
      
         Main & HelperGetMain();
      };

   }
}
