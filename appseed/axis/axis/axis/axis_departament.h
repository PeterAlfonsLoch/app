#pragma once



namespace base
{



   class CLASS_DECL_AXIS departament :
   virtual public signalizable
   {
   public:


      departament(application * papp);
      virtual ~departament();


      virtual void construct(sp(application) papp);
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




} // namespace base



