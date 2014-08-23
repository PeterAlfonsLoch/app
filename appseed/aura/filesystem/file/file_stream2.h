#pragma once



namespace file
{

   class CLASS_DECL_AXIS output_stream2 :
      virtual public output_stream
   {
   public:
      output_stream2();
      output_stream2(writer * pwriter);
      virtual ~output_stream2();

      output_stream2 & operator << (uchar uch);
      output_stream2 & operator << (uint16_t ui);
      output_stream2 & operator << (int32_t i);
      output_stream2 & operator << (uint32_t ui);
      output_stream2 & operator << (const RECT & rect);
      output_stream2 & operator << (serializable & serializable);
      output_stream2 & operator << (const char * psz);
      output_stream2 & operator << (const string & str);
   };


} // namespace file






