#pragma once




namespace file
{


   class exception;         // file exception
   class binary_buffer;
   typedef sp(binary_buffer) binary_buffer_sp;

   class byte_ostream;
   class byte_istream;
   class serializable;


   class CLASS_DECL_AURA byte_istream  :
      virtual public istream
   {
   public:


      byte_istream();
      byte_istream(stream_buffer * preader);
      byte_istream(const istream & istream);
      virtual ~byte_istream();

      void read_arbitrary(int32_t & i);
      void read_arbitrary(uint32_t & ui);
      void read_arbitrary(int64_t & i);
      void read_arbitrary(uint64_t & ui);

      using istream::read;
      virtual void read (bool & b);
      virtual void read (char & ch);
      virtual void read (uchar & uch);
      virtual void read (unichar & wch);
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
      virtual void read (property & property);
      virtual void read (string & str);

      // read until MSB is not set ignoring this MSB when writing to target
      void read_arbitrary(void * p, ::count nMax);

      virtual string get_location() const;

      istream & operator = (const istream & istream);

      /*
      file_position seek(file_offset offset, e_seek seekOrigin);
      */

      void full_load(string & str);

   };









} // namespace file




