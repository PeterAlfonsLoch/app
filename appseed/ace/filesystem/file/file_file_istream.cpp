//#include "framework.h"



namespace file
{


   file_istream::file_istream()
   {


   }

   
   file_istream::file_istream(const char * lpszFileName,uint32_t nOpenFlags,::ace::application * papp)
   {

      open(lpszFileName,nOpenFlags,papp);

   }


   file_istream::file_istream(stream_buffer * preader)
   {

      m_spbuffer = preader;

   }

   file_istream::file_istream(const file_istream & istream)
   {

      m_spbuffer = istream.m_spbuffer;

   }

   file_istream::~file_istream()
   {

      close();



   }


} // namespace file









