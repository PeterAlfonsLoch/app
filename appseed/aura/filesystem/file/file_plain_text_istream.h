#pragma once


namespace file
{


   class CLASS_DECL_AURA plain_text_istream :
      virtual public istream,
      virtual public plain_text_stream_base
   {
   public:


      plain_text_istream();
      plain_text_istream(stream_buffer * preader);
      plain_text_istream(const istream & istream);
      virtual ~plain_text_istream();


      using istream::read;
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

      istream & operator = (const istream & istream);

      operator void * ()
      {
         return this;
      }

   };





} // namespace aura




