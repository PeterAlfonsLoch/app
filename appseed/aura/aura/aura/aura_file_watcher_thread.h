#pragma once


namespace file_watcher
{


   class CLASS_DECL_AURA thread :
      virtual public file_watcher,
      virtual public ::thread
   {
   public:

      
      thread(::aura::application * papp);

      virtual int32_t run();


   };


} // namespace file_watcher



