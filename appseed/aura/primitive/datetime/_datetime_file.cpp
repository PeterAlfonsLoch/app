#include "framework.h"


#include "aura/filestream.h"


#include "datetime.h"


::file::ostream & operator <<(::file::ostream & os, ::datetime::time_span span)
{

   os.write_arbitrary((int64_t)span.m_timeSpan);

   return os;

}

::file::istream & operator >> (::file::istream & is, ::datetime::time_span & span)
{

   is.read_arbitrary((int64_t &)span.m_timeSpan);

   return is;

}



::file::ostream & operator <<(::file::ostream & os, ::datetime::time time)
{

   os.write_arbitrary((int64_t)time.m_time);

   return os;

}

::file::istream & operator >> (::file::istream & is, ::datetime::time& rtime)
{

   is.read_arbitrary((int64_t &)rtime.m_time);

   return is;

}



::file::ostream & operator <<(::file::ostream & os, ::datetime::zonetime zonetime)
{

   os.write_arbitrary((int64_t)zonetime.m_time);
   os.write_arbitrary((int32_t)zonetime.m_iZoneOffset);

   return os;

}

::file::istream & operator >> (::file::istream & is, ::datetime::zonetime& rtime)
{

   is.read_arbitrary((int64_t &)rtime.m_time);
   is.read_arbitrary((int32_t &)rtime.m_iZoneOffset);

   return is;

}

