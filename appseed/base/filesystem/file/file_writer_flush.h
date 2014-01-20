#pragma once


namespace file
{

   class writer_flush;

   typedef smart_pointer < writer_flush > writer_flush_sp;


   class CLASS_DECL_BASE writer_flush :
      virtual public ::object
   {
   public:
      
      
      virtual void flush();


   };

} // namespace file



