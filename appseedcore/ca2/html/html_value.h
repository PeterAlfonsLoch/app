#pragma once


namespace html
{

   class value : public base
   {
   public:


      int      m_iIndex;


      value(class tag * pparent);
      virtual ~value();

      virtual type get_type();

      void set_value(const char * pszValue);
      string get_value();

   protected:
      string            m_strValue;
   };

} // namespace html