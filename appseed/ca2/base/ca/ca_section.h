#pragma once


namespace ca2
{


   class CLASS_DECL_ca2 section :
      virtual public ::ca2::signalizable
   {
   public:


      section(::ca2::application * papp);
      virtual ~section();


      virtual void construct(sp(::ca2::application) papp);
      virtual void connect_to_application_signal();


      virtual bool process_initialize();


      virtual bool initialize();
      virtual bool initialize1();
      virtual bool initialize2();
      virtual bool initialize3();
      virtual bool initialize_instance();

      virtual bool finalize();
      virtual int32_t exit_instance();


      void on_signal(::ca2::signal_object * pobj);

   };


} // namespace ca2




