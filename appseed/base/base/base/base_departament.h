#pragma once


class CLASS_DECL_BASE base_departament :
   virtual public signalizable
{
public:


   base_departament(::base::application * papp);
   virtual ~base_departament();


   virtual void construct(sp(::base::application) papp);
   virtual void connect_to_application_signal();


   virtual bool process_initialize();


   virtual bool initialize();
   virtual bool initialize1();
   virtual bool initialize2();
   virtual bool initialize3();
   virtual bool initialize_instance();

   virtual bool finalize();
   virtual int32_t exit_instance();


   void on_signal(signal_details * pobj);

};


