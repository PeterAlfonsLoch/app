#pragma once


namespace ca
{


   class CLASS_DECL_ca section :
      virtual public ::ca::signalizable
   {
   public:


      section();
      virtual ~section();


      virtual void construct(sp(::ca::application) papp);
      virtual void connect_to_application_signal();


      virtual bool process_initialize();


      virtual bool initialize();
      virtual bool initialize1();
      virtual bool initialize2();
      virtual bool initialize3();
      virtual bool initialize_instance();

      virtual bool finalize();
      virtual int32_t exit_instance();


      void on_signal(::ca::signal_object * pobj);

   };


} // namespace ca




