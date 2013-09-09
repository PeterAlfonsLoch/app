#pragma once


namespace core
{


   class CLASS_DECL_ca2 system :
      virtual public ::application,
      virtual public base_system
      #ifdef LINUX
      , virtual public ::exception::translator
      #endif
   {
   public:


      system();
      virtual ~system();


      virtual sp(element) clone(sp(element) pobj);
      virtual void discard_to_factory(sp(element) pca);

      virtual bool is_system();


      virtual bool process_initialize();


      virtual bool initialize_instance();

   };


} // namespace core



