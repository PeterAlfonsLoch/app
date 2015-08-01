//#include "framework.h"



namespace file
{


   // FindSignature.cpp
   // from 7-zip on 2012-12-23, lunch time
   ////#include "framework.h"

   /*//#include "Common/Buffer.h"

   //#include "FindSignature.h"

   //#include "../../Common/StreamUtils.h"*/


   istream::istream()
   {

      m_gcount = 0;

   }




   istream::istream(stream_buffer * preader)
   {
      
      m_spbuffer = preader;      
      m_gcount = 0;

   }

   istream::istream(const istream & istream)
   {
      
      m_spbuffer = istream.m_spbuffer;      
      m_gcount = 0;

   }

   istream::~istream()
   {
      
      close();

   }


   ::primitive::memory_size istream::read(void * lpBuf, ::primitive::memory_size nCount)
   {
      
      return m_gcount = m_spbuffer->read(lpBuf, nCount);
      
   }

   void istream::full_read(void * lpBuf, ::primitive::memory_size nCount)
   {

      if(fail())
      {

         return;

      }


      if(!m_spbuffer->full_read(lpBuf,nCount))
      {

         setstate(failbit);

         return;

      }

      

      m_gcount = nCount;
      
   }


   void istream::full_fill(::primitive::memory_base & m)
   {
      
      full_read(m.get_data(), m.get_size());

   }

   void istream::read_arbitrary(int32_t & i)
   {


   }

   void istream::read_arbitrary(uint32_t & ui)
   {


   }

   void istream::read_arbitrary(int64_t & i)
   {


   }

   void istream::read_arbitrary(uint64_t & ui)
   {


   }


   void istream::read (bool & b)
   {
      UNREFERENCED_PARAMETER(b);
      ::exception::throw_interface_only(get_app());
   }


   void istream::read (char & ch)
   {
      UNREFERENCED_PARAMETER(ch);
      ::exception::throw_interface_only(get_app());
   }


   void istream::read (uchar & uch)
   {
      UNREFERENCED_PARAMETER(uch);
      ::exception::throw_interface_only(get_app());
   }

#ifdef WINDOWS
   void istream::read (unichar & wch)
   {
      UNREFERENCED_PARAMETER(wch);
      ::exception::throw_interface_only(get_app());
   }

#endif
   void istream::read (int16_t & sh)
   {
      UNREFERENCED_PARAMETER(sh);
      ::exception::throw_interface_only(get_app());
   }


   void istream::read (uint16_t & ui)
   {
      UNREFERENCED_PARAMETER(ui);
      ::exception::throw_interface_only(get_app());
   }


   void istream::read (int32_t & i)
   {
      UNREFERENCED_PARAMETER(i);
      ::exception::throw_interface_only(get_app());
   }


   void istream::read (uint32_t & ui)
   {
      UNREFERENCED_PARAMETER(ui);
      ::exception::throw_interface_only(get_app());
   }


   void istream::read (int64_t & i)
   {
      UNREFERENCED_PARAMETER(i);
      ::exception::throw_interface_only(get_app());
   }


   void istream::read (uint64_t & ui)
   {
      UNREFERENCED_PARAMETER(ui);
      ::exception::throw_interface_only(get_app());
   }
   
#ifdef APPLEOS
   
   void istream::read(unsigned long & ui)
   {
      
   }
   
#endif
   
   void istream::read (float & f)
   {
      UNREFERENCED_PARAMETER(f);
      ::exception::throw_interface_only(get_app());
   }


   void istream::read (double & d)
   {
      UNREFERENCED_PARAMETER(d);
      ::exception::throw_interface_only(get_app());
   }


   void istream::read (LPRECT lprect)
   {
      UNREFERENCED_PARAMETER(lprect);
      ::exception::throw_interface_only(get_app());
   }


   void istream::read (SIZE & size)
   {
      UNREFERENCED_PARAMETER(size);
      ::exception::throw_interface_only(get_app());
   }


   void istream::read (sp(type) info)
   {
      UNREFERENCED_PARAMETER(info);
      ::exception::throw_interface_only(get_app());
   }


   void istream::read (serializable & serializable)
   {
      serializable.read(*this);
   }


   void istream::read (id & id)
   {
      UNREFERENCED_PARAMETER(id);
      ::exception::throw_interface_only(get_app());
   }


   void istream::read (var & var)
   {
      UNREFERENCED_PARAMETER(var);
      ::exception::throw_interface_only(get_app());
   }


   void istream::read(property & property)
   {
      UNREFERENCED_PARAMETER(property);
      ::exception::throw_interface_only(get_app());
   }


   void istream::read(string & str)
   {
      UNREFERENCED_PARAMETER(str);
      ::exception::throw_interface_only(get_app());
   }

   int istream::get()
   {
      unsigned char uch;

      if(read(&uch,1) == 1)
         return uch;

      return EOF;

   }


   int istream::peek()
   {
      unsigned char uch;

      if(read(&uch,1) == 1)
      {
         seek(-1,seek_current);
         return uch;
      }

      return EOF;

   }

   istream & istream::getline(char * sz,strsize n)
   {
      int c;
      while(n > 0)
      {
         c = get();
         if(c == EOF)
         {
            break;
         }
         else if(c == '\n')
         {
            c = get();
            if(c != '\r' && c != EOF)
               seek(-1,seek_current);
            break;
         }
         else if(c == '\r')
         {
            c = get();
            if(c != '\n' && c != EOF)
               seek(-1,seek_current);
            break;
         }
         *sz = (char)c;
         sz++;
         n--;
      }

      return *this;

   }


   istream & istream::operator = (const istream & istream)
   {

      m_spbuffer = istream.m_spbuffer;

      return *this;

   }


   bool istream::is_reader_null()
   {
      return m_spbuffer.is_null();
   }

   bool istream::is_reader_set()
   {
      return m_spbuffer.is_set();
   }


   void istream::read_to_hex(string & str, file_position dwStart, file_position dwEnd)
   {
      primitive::memory memory(get_app());
      if(dwStart == (file_position) -1)
      {
		   dwStart = tellg();
	   }
	   else
      {
         seek_from_begin(dwStart);
      }
      ::primitive::memory_position uiPos = 0;
      ::primitive::memory_size uiRead;
      memory.allocate(1024);

      strsize nCount;
      
      if (dwEnd == (file_position)-1)
      {

         nCount = ::numeric_info< strsize >::max();

      }
      else
      {

         nCount = (strsize)(dwEnd - dwStart);

      }
       
      while((uiRead = read(&memory.get_data()[uiPos], MIN(memory.get_size() - uiPos, (::primitive::memory_size) nCount))) > 0)
      {
         uiPos += uiRead;
         nCount -= uiRead;
         memory.allocate_add_up(1024 * 1024);
      }
      memory.allocate((::primitive::memory_size) uiPos);
      memory.to_hex(str);
   }



   
} // namespace file




