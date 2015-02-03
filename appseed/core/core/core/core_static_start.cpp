//
//  core_static_start
//

namespace core
{


   namespace static_start
   {


      CLASS_DECL_BASE void init()
      {
         


      }














































      CLASS_DECL_BASE void term()
      {




      }

      ::aura::system * aura_create_system()
      {
         return new ::core::system(NULL);
      }

      class static_start
      {
      public:
         static_start()
         {
            g_pfn_create_system = aura_create_system;
            static_start()
         {
            if(defer_core_init())
            {
               ::output_debug_string("defer_core_init Successful!!");
            }
            else
            {
               ::output_debug_string("Failed to defer_core_init!!");
            }
         }
         ~static_start()
         {
            if(defer_core_term())
            {
               ::output_debug_string("defer_core_term Successful!!");
            }
            else
            {
               ::output_debug_string("Failed to defer_core_term!!");
            }
         }
      };
      
      
      static_start g_corestaticstart;


   } // namespace static_start


} // namespace base





