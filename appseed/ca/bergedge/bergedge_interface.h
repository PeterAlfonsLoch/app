#pragma once


class CLASS_DECL_ca bergedge_interface :
   virtual public plane::application,
   virtual public ca::session
{
public:


   virtual bool open_by_file_extension(::ca::create_context * pcreatecontext);
   //virtual ::uinteraction::frame::frame * get_frame_schema(const char * pszLibrary, const char * pszFrameSchemaName);


   virtual void on_app_request_bergedge_callback(::ca2::application * papp);


   virtual ::fontopus::user * login(gen::property_set & set) = 0;

};




