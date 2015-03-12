//#include "framework.h"



namespace file
{


   file_ostream::file_ostream()
   {

   }


   file_ostream::file_ostream(const char * lpszFileName,uint32_t nOpenFlags,::aura::application * papp)
   {

      open(lpszFileName,nOpenFlags,papp);

   }


   file_ostream::file_ostream(stream_buffer * preader)
   {

      m_spbuffer = preader;

   }

   file_ostream::file_ostream(const file_ostream & istream)
   {

      m_spbuffer = istream.m_spbuffer;

   }

   file_ostream::~file_ostream()
   {


   }


} // namespace file









