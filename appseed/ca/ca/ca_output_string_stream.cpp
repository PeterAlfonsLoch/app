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


_template_std_ostringstream::_template_std_ostringstream()
{
   m_pstr = &m_str;
}


string & _template_std_ostringstream::str()
{
   return m_str;
}

/*void _template_std_ostringstream::write(const void * p, primitive::memory_size size)
{
   ca::writer::write(p, size);
}*/



_template_std_stringstream::_template_std_stringstream()
{
   ::ca::str_reader::m_pstr = &m_str;
   ::ca::str_writer::m_pstr = &m_str;
}

_template_std_stringstream::_template_std_stringstream(const char * psz) :
   m_str(psz)
{
   ::ca::str_reader::m_pstr = &m_str;
   ::ca::str_writer::m_pstr = &m_str;
}

_template_std_stringstream::_template_std_stringstream(const string & str) :
   m_str(str)
{
   ::ca::str_reader::m_pstr = &m_str;
   ::ca::str_writer::m_pstr = &m_str;
}

string & _template_std_stringstream::str()
{
   return m_str;
}
