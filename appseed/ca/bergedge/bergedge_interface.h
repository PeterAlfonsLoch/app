#pragma once


class CLASS_DECL_ca bergedge_interface :
   virtual public plane::application,
   virtual public ca::session
{
public:


   virtual bool open_by_file_extension(::ca::create_context * pcreatecontext);


};




