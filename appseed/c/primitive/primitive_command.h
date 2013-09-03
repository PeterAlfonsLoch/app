#pragma once


class CLASS_DECL_c command :
   virtual public object
{
public:


   command(sp(base_application) papp);
   virtual ~command();

   virtual var run();


   virtual void on_request(sp(create_context) pcreationcontext);


   virtual string get_description();


};



