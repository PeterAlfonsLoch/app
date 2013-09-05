#include "framework.h"



namespace file
{


   // FindSignature.cpp
   // from 7-zip on 2012-12-23, lunch time
   //#include "framework.h"

   /*#include "Common/Buffer.h"

   #include "FindSignature.h"

   #include "../../Common/StreamUtils.h"*/


   input_stream::input_stream()
   {

      m_gcount = 0;

   }

   input_stream::input_stream(reader * preader)
   {
      
      m_spbuffer = preader;      
      m_gcount = 0;

   }

   input_stream::input_stream(const input_stream & istream)
   {
      
      m_spbuffer = istream.m_spbuffer;      
      m_gcount = 0;

   }

   input_stream::~input_stream()
   {
      
      close();

   }


   ::primitive::memory_size input_stream::read(void * lpBuf, ::primitive::memory_size nCount)
   {
      
      return m_gcount = m_spbuffer->read(lpBuf, nCount);
      
   }


   void input_stream::read_arbitrary(int32_t & i)
   {


   }

   void input_stream::read_arbitrary(uint32_t & ui)
   {


   }

   void input_stream::read_arbitrary(int64_t & i)
   {


   }

   void input_stream::read_arbitrary(uint64_t & ui)
   {


   }


   void input_stream::read (bool & b)
   {
      UNREFERENCED_PARAMETER(b);
      throw interface_only_exception(get_app());
   }


   void input_stream::read (char & ch)
   {
      UNREFERENCED_PARAMETER(ch);
      throw interface_only_exception(get_app());
   }


   void input_stream::read (uchar & uch)
   {
      UNREFERENCED_PARAMETER(uch);
      throw interface_only_exception(get_app());
   }


   void input_stream::read (wchar_t & wch)
   {
      UNREFERENCED_PARAMETER(wch);
      throw interface_only_exception(get_app());
   }


   void input_stream::read (int16_t & sh)
   {
      UNREFERENCED_PARAMETER(sh);
      throw interface_only_exception(get_app());
   }


   void input_stream::read (uint16_t & ui)
   {
      UNREFERENCED_PARAMETER(ui);
      throw interface_only_exception(get_app());
   }


   void input_stream::read (int32_t & i)
   {
      UNREFERENCED_PARAMETER(i);
      throw interface_only_exception(get_app());
   }


   void input_stream::read (uint32_t & ui)
   {
      UNREFERENCED_PARAMETER(ui);
      throw interface_only_exception(get_app());
   }


   void input_stream::read (int64_t & i)
   {
      UNREFERENCED_PARAMETER(i);
      throw interface_only_exception(get_app());
   }


   void input_stream::read (uint64_t & ui)
   {
      UNREFERENCED_PARAMETER(ui);
      throw interface_only_exception(get_app());
   }


   void input_stream::read (float & f)
   {
      UNREFERENCED_PARAMETER(f);
      throw interface_only_exception(get_app());
   }


   void input_stream::read (double & d)
   {
      UNREFERENCED_PARAMETER(d);
      throw interface_only_exception(get_app());
   }


   void input_stream::read (LPRECT lprect)
   {
      UNREFERENCED_PARAMETER(lprect);
      throw interface_only_exception(get_app());
   }


   void input_stream::read (SIZE & size)
   {
      UNREFERENCED_PARAMETER(size);
      throw interface_only_exception(get_app());
   }


   void input_stream::read (sp(type) info)
   {
      UNREFERENCED_PARAMETER(info);
      throw interface_only_exception(get_app());
   }


   void input_stream::read (serializable & serializable)
   {
      UNREFERENCED_PARAMETER(serializable);
      throw interface_only_exception(get_app());
   }


   void input_stream::read (id & id)
   {
      UNREFERENCED_PARAMETER(id);
      throw interface_only_exception(get_app());
   }


   void input_stream::read (var & var)
   {
      UNREFERENCED_PARAMETER(var);
      throw interface_only_exception(get_app());
   }


   void input_stream::read (string & str)
   {
      UNREFERENCED_PARAMETER(str);
      throw interface_only_exception(get_app());
   }

   void input_stream::close()
   {
   }


   input_stream & input_stream::operator = (const input_stream & istream)
   {

      m_spbuffer = istream.m_spbuffer;

      return *this;

   }


   bool input_stream::is_reader_null()
   {
      return m_spbuffer.is_null();
   }

   bool input_stream::is_reader_set()
   {
      return m_spbuffer.is_set();
   }

} // namespace file




