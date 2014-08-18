#pragma once



namespace file
{

   class plain_text_output_stream;
   class plain_text_input_stream;


   class CLASS_DECL_AXIS plain_text_stream_base :
      virtual public stream_base
   {
   public:


      fmtflags          m_fmtflags;


      plain_text_stream_base();
      virtual ~plain_text_stream_base();


      fmtflags setf(fmtflags flagsAdd);
      fmtflags setf(fmtflags flagsAdd, fmtflags flagsRemove);




   };


} // namespace file



