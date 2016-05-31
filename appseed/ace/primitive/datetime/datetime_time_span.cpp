

namespace datetime
{


   const char * const szInvalidDateTimeSpan = "Invalid DateTimeSpan";


   date_span::date_span()
   {
      m_iMonth = 0;
      m_iYear = 0;
      m_bConstraintMonth = 0;

   }
   /////////////////////////////////////////////////////////////////////////////
   // time_span
   /////////////////////////////////////////////////////////////////////////////

   time_span::time_span() throw():
      m_timeSpan(0)
   {
   }

   time_span::time_span(__time64_t time) throw():
      m_timeSpan(time)
   {
   }

   time_span::time_span(int64_t lDays,int32_t nHours,int32_t nMins,int32_t nSecs) throw()
   {
      m_timeSpan = nSecs + 60 * (nMins + 60 * (nHours + int64_t(24) * lDays));
   }

   int64_t time_span::GetDays() const throw()
   {
      return(m_timeSpan / (24 * 3600));
   }

   int64_t time_span::GetTotalHours() const throw()
   {
      return(m_timeSpan / 3600);
   }

   int32_t time_span::GetHours() const throw()
   {
      return(LONG(GetTotalHours() - (GetDays() * 24)));
   }

   int64_t time_span::GetTotalMinutes() const throw()
   {
      return(m_timeSpan / 60);
   }

   int32_t time_span::GetMinutes() const throw()
   {
      return(LONG(GetTotalMinutes() - (GetTotalHours() * 60)));
   }

   int64_t time_span::GetTotalSeconds() const throw()
   {
      return(m_timeSpan);
   }

   int32_t time_span::GetSeconds() const throw()
   {
      return(LONG(GetTotalSeconds() - (GetTotalMinutes() * 60)));
   }

   __time64_t time_span::GetTimeSpan() const throw()
   {
      return(m_timeSpan);
   }

   time_span time_span::operator+(time_span span) const throw()
   {
      return(time_span(m_timeSpan + span.m_timeSpan));
   }

   time_span time_span::operator-(time_span span) const throw()
   {
      return(time_span(m_timeSpan - span.m_timeSpan));
   }

   time_span& time_span::operator+=(time_span span) throw()
   {
      m_timeSpan += span.m_timeSpan;
      return *this;
   }

   time_span& time_span::operator-=(time_span span) throw()
   {
      m_timeSpan -= span.m_timeSpan;
      return *this;
   }

   bool time_span::operator==(time_span span) const throw()
   {
      return(m_timeSpan == span.m_timeSpan);
   }

   bool time_span::operator!=(time_span span) const throw()
   {
      return(m_timeSpan != span.m_timeSpan);
   }

   bool time_span::operator<(time_span span) const throw()
   {
      return(m_timeSpan < span.m_timeSpan);
   }

   bool time_span::operator>(time_span span) const throw()
   {
      return(m_timeSpan > span.m_timeSpan);
   }

   bool time_span::operator<=(time_span span) const throw()
   {
      return(m_timeSpan <= span.m_timeSpan);
   }

   bool time_span::operator>=(time_span span) const throw()
   {
      return(m_timeSpan >= span.m_timeSpan);
   }


   string time_span::Format(const char * pFormat) const
      // formatting timespans is a little trickier than formatting CTimes
      //  * we are only interested in relative time formats, ie. it is illegal
      //      to format anything dealing with absolute time (i.e. years, months,
      //         day of week, day of year, timezones, ...)
      //  * the only valid formats:
      //      %D - # of days
      //      %H - hour in 24 hour format
      //      %M - minute (0-59)
      //      %S - seconds (0-59)
      //      %% - percent sign
      //   %#<any_of_mods> - skip leading zeros
   {
      ASSERT(pFormat != NULL);
      if(pFormat == NULL)
         throw hresult_exception(get_thread_app(),E_INVALIDARG);

      string strBuffer;
      // string hmsFormats [_CTIMESPANFORMATS] = {"%ca","%02ld","%d"};
      //   string dayFormats [_CTIMESPANFORMATS] = {"%ca","%I64d","%I64d"};
      strBuffer.Preallocate(maxTimeBufferSize);
      char ch;

      while((ch = *pFormat++) != '\0')
      {
         enum _CTIMESPANFORMATSTEP formatstep = _CTFS_NONE;
         if(ch == '%')
         {
            formatstep = _CTFS_FORMAT;
            ch = *pFormat++;
            if(ch == '#')
            {
               formatstep = _CTFS_NZ;
               ch = *pFormat++;
            }
         }
         switch(ch)
         {
         case '%':
            strBuffer += ch;
            break;
         case 'D':
            //            strBuffer.AppendFormat(dayFormats[formatstep], formatstep ? GetDays()    : ch);
            break;
         case 'H':
            //            strBuffer.AppendFormat(hmsFormats[formatstep], formatstep ? GetHours()   : ch);
            break;
         case 'M':
            //            strBuffer.AppendFormat(hmsFormats[formatstep], formatstep ? GetMinutes() : ch);
            break;
         case 'S':
            //            strBuffer.AppendFormat(hmsFormats[formatstep], formatstep ? GetSeconds() : ch);
            break;
         default:
            if(formatstep)
            {
#pragma warning (push)
#pragma warning (disable: 4127)  // conditional expression constant
               ENSURE(FALSE);      // probably a bad format character
#pragma warning (pop)
            }
            else
            {
               strBuffer += ch;
#ifdef _MBCS
               if(_istlead(ch))
               {
                  strBuffer += *pFormat++;
               }
#endif
            }
            break;
         }
      }

      return strBuffer;
   }




} // namespace datetime





dump_context & operator <<(dump_context & dumpcontext,::datetime::time_span timeSpan)
{
   return dumpcontext << "time_span(" << timeSpan.GetDays() << " days, " <<
      timeSpan.GetHours() << " hours, " <<
      timeSpan.GetMinutes() << " minutes and " <<
      timeSpan.GetSeconds() << " seconds)";
}

::file::ostream & operator <<(::file::ostream & os,::datetime::time_span span)
{

   os.write_arbitrary((int64_t)span.m_timeSpan);

   return os;

}

::file::istream & operator >>(::file::istream & is,::datetime::time_span & span)
{

   is.read_arbitrary((int64_t &)span.m_timeSpan);

   return is;

}




