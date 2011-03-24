#pragma once


namespace html
{

   class tag : public base
   {
   public:
      tag(tag * pparent);
      virtual ~tag();

      type get_type();

      attribute_array & attra();

      void set_name(const char * pszName);
      string get_name();

      attribute * get_attr(const char * pszAttrName);
      string get_attr_value(const char * pszAttrName);

      tag * get_parent();

      base_ptr_array & baseptra();

   protected:
      string            m_strName;
      attribute_array   m_attra;
      base_ptr_array    m_baseptra;
   };



} // namespace html