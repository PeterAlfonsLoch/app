#pragma once


namespace uinteraction
{


   class CLASS_DECL_ca interaction :
      virtual public ::radix::object
   {
   public:


      gen::property_set       m_set;


      interaction(::ca::application * papp);
      virtual ~interaction();

      virtual void update();


      virtual void get_frame_schema_list(stringa & stra);

      virtual frame::frame * get_frame_schema(const char * pszSchema);


   };


} // namespace uinteraction