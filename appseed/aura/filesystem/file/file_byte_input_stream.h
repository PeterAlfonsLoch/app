#pragma once




namespace file
{


   class exception;         // file exception
   class binary_buffer;
   typedef sp(binary_buffer) binary_buffer_sp;

   class byte_output_stream;
   class byte_input_stream;
   class serializable;


   class CLASS_DECL_AURA byte_input_stream  :
      virtual public input_stream
   {
   public:


      byte_input_stream();
      byte_input_stream(stream_buffer * preader);
      byte_input_stream(const input_stream & istream);
      virtual ~byte_input_stream();

      void read_arbitrary(int32_t & i);
      void read_arbitrary(uint32_t & ui);
      void read_arbitrary(int64_t & i);
      void read_arbitrary(uint64_t & ui);

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
      virtual void read (serializable & serializable);
      virtual void read (id & id);
      virtual void read (var & var);
      virtual void read (string & str);

      // read until MSB is not set ignoring this MSB when writing to target
      void read_arbitrary(void * p, ::count nMax);

      virtual string get_location() const;

      input_stream & operator = (const input_stream & istream);

      /*
      file_position seek(file_offset offset, e_seek seekOrigin);
      */

      void full_load(string & str);

   };









} // namespace file




