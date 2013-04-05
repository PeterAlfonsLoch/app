#pragma once


namespace uinteraction
{


   class CLASS_DECL_ca interaction :
      virtual public ::ca::object
   {
   public:


      ::ca::property_set       m_set;


      interaction(::ca::applicationsp papp);
      virtual ~interaction();

      virtual void update();


      virtual void get_frame_schema_list(stringa & stra);

      virtual frame::frame * get_frame_schema(const char * pszSchema);


   };


} // namespace uinteraction