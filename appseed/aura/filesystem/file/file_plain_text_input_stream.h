#pragma once


namespace file
{


   class CLASS_DECL_AXIS plain_text_input_stream :
      virtual public input_stream,
      virtual public plain_text_stream_base
   {
   public:


      plain_text_input_stream();
      plain_text_input_stream(stream_buffer * preader);
      plain_text_input_stream(const input_stream & istream);
      virtual ~plain_text_input_stream();


      using input_stream::read;
      virtual void read (bool & b);
      virtual void read (char & ch);
      virtual void read (uchar & uch);
      virtual void read (wchar_t & wch);
      virtual void read (int16_t & sh);
      virtual void read (uint16_t & uint16_t);
      virtual void read (int32_t & i);
      virtual void read (uint32_t & ui);
      virtual void read (int64_t & i);
      virtual void read (uint64_t & ui);
      virtual void read (float & f);
      virtual void read (double & d);
      virtual void read (LPRECT lprect);
      virtual void read (SIZE & size);
      virtual void read (sp(type) info);
      virtual void read (serializable & writable);

      virtual ::string get_location() const;

      input_stream & operator = (const input_stream & istream);

      operator void * ()
      {
         return this;
      }

   };





} // namespace axis




