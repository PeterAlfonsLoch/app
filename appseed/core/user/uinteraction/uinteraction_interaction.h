#pragma once


namespace user
{


   namespace uinteraction
   {


      class CLASS_DECL_CORE interaction :
         virtual public ::object
      {
      public:


         property_set       m_set;


         interaction(sp(::base::application) papp);
         virtual ~interaction();

         virtual void update();


         virtual void get_frame_schema_list(stringa & stra);

         virtual sp(frame::frame) get_frame_schema(const char * pszSchema);


      };


   } // namespace uinteraction


} // namespace user





