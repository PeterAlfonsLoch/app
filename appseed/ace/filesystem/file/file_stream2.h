#pragma once



namespace file
{

   class CLASS_DECL_ACE ostream2 :
      virtual public ostream
   {
   public:
      ostream2();
      ostream2(writer * pwriter);
      virtual ~ostream2();

      ostream2 & operator << (uchar uch);
      ostream2 & operator << (uint16_t ui);
      ostream2 & operator << (int32_t i);
      ostream2 & operator << (uint32_t ui);
      ostream2 & operator << (const RECT & rect);
      ostream2 & operator << (serializable & serializable);
      ostream2 & operator << (const char * psz);
      ostream2 & operator << (const string & str);
   };


} // namespace file






