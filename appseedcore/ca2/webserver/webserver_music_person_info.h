#pragma once


namespace webserver
{


   namespace music
   {


      class CLASS_DECL_ca person_info :
         virtual public dynamic_source::ptr
      {
      public:
         

         var                  m_namea;
         var                  m_ida;   
         var_array            m_persona;   
         var                  m_persons;
         var                  m_sida;


         person_info();


      };


   } // namespace music


} // namespace webserver

