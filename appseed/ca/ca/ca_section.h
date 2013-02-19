#pragma once


namespace ca
{


   class CLASS_DECL_ca section :
      virtual public ::radix::object
   {
   public:


      section();
      virtual ~section();


      virtual void construct(::ca::application * papp);


      virtual bool process_initialize();


      virtual bool initialize();
      virtual bool initialize1();
      virtual bool initialize2();
      virtual bool initialize3();
      virtual bool initialize_instance();

      virtual bool finalize();
      virtual int32_t exit_instance();


   };


} // namespace ca




