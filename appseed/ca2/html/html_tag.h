#pragma once


namespace html
{

   class tag : public base
   {
   public:
      tag(tag * pparent);
      virtual ~tag();

      type get_type() const;

      attribute_array & attra();
      const attribute_array & attra() const;

      void set_name(const char * pszName);
      string get_name() const;

      attribute * get_attr(const char * pszAttrName);
      const attribute * get_attr(const char * pszAttrName) const;
      string get_attr_value(const char * pszAttrName) const;

      tag * get_parent();
      const tag * get_parent() const;

      base_ptr_array & baseptra();
      const base_ptr_array & baseptra() const;


   protected:
      string            m_strName;
      attribute_array   m_attra;
      base_ptr_array    m_baseptra;
   };



} // namespace html