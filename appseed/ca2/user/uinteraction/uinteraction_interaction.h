#pragma once


namespace uinteraction
{


   class CLASS_DECL_ca2 interaction :
      virtual public ::ca2::object
   {
   public:


      ::ca2::property_set       m_set;


      interaction(sp(::ca2::application) papp);
      virtual ~interaction();

      virtual void update();


      virtual void get_frame_schema_list(stringa & stra);

      virtual sp(frame::frame) get_frame_schema(const char * pszSchema);


   };


} // namespace uinteraction