#include "framework.h"


_template_std_istringstream::_template_std_istringstream()
{
   m_pstr = &m_str;
}

_template_std_istringstream::_template_std_istringstream(const char * psz) :
   m_str(psz)
{
   m_pstr = &m_str;
}

_template_std_istringstream::_template_std_istringstream(const string & str) :
   m_str(str)
{
   m_pstr = &m_str;
}



string & _template_std_istringstream::str()
{
   return m_str;
}


::file::plain_text_output_stream::::file::plain_text_output_stream()
{
   m_pstr = &m_str;
}


string & ::file::plain_text_output_stream::str()
{
   return m_str;
}

string template_std_ostringstream::str() const
{
   return m_str;
}

/*void ::file::plain_text_output_stream::write(const void * p, primitive::memory_size size)
{
   ::file::writer::write(p, size);
}*/



::file::plain_text_stream::::file::plain_text_stream()
{
   ::ca2::str_reader::m_pstr = &m_str;
   ::ca2::str_writer::m_pstr = &m_str;
}

::file::plain_text_stream::::file::plain_text_stream(const char * psz) :
   m_str(psz)
{
   ::ca2::str_reader::m_pstr = &m_str;
   ::ca2::str_writer::m_pstr = &m_str;
}

::file::plain_text_stream::::file::plain_text_stream(const string & str) :
   m_str(str)
{
   ::ca2::str_reader::m_pstr = &m_str;
   ::ca2::str_writer::m_pstr = &m_str;
}

string & ::file::plain_text_stream::str()
{
   return m_str;
}
