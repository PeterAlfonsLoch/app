#include "framework.h"

::comparison::var_strict::::comparison::var_strict(const class var & var) :
   m_var(var)
{
}

::comparison::var_strict::::comparison::var_strict(const ::comparison::var_strict & compare) :
   m_var(compare.m_var)
{
}

bool ::comparison::var_strict::operator == (const class var & var) const
{
   return m_var.strict_equal(var);
}

bool ::comparison::var_strict::operator == (const char * psz) const
{
   return m_var.strict_equal(psz);
}

bool ::comparison::var_strict::operator == (const string & str) const
{
   return m_var.strict_equal(str);
}

bool ::comparison::var_strict::operator == (double d) const
{
   return m_var.strict_equal(d);
}

bool ::comparison::var_strict::operator == (int32_t i) const
{
   return m_var.strict_equal(i);
}

bool ::comparison::var_strict::operator == (bool b) const
{
   return m_var.strict_equal(b);
}

bool ::comparison::var_strict::operator != (const class var & var) const
{
   return m_var.strict_different(var);
}

bool ::comparison::var_strict::operator != (const char * psz) const
{
   return m_var.strict_different(psz);
}

bool ::comparison::var_strict::operator != (const string & str) const
{
   return m_var.strict_different(str);
}

bool ::comparison::var_strict::operator != (double d) const
{
   return m_var.strict_different(d);
}

bool ::comparison::var_strict::operator != (int32_t i) const
{
   return m_var.strict_different(i);
}

bool ::comparison::var_strict::operator != (bool b) const
{
   return m_var.strict_different(b);
}

bool operator == (const char * psz, const ::comparison::var_strict & var)
{
   return strict_equal(psz, var.m_var);
}

bool operator == (const string & str, const ::comparison::var_strict & var)
{
   return strict_equal(str, var.m_var);
}

bool operator == (double d, const ::comparison::var_strict & var)
{
   return strict_equal(d, var.m_var);
}

bool operator == (int32_t i, const ::comparison::var_strict & var)
{
   return strict_equal(i, var.m_var);
}

bool operator == (bool b, const ::comparison::var_strict & var)
{
   return strict_equal(b, var.m_var);
}

bool operator != (const char * psz, const ::comparison::var_strict & var)
{
   return strict_different(psz, var.m_var);
}

bool operator != (const string & str, const ::comparison::var_strict & var)
{
   return strict_different(str, var.m_var);
}

bool operator != (double d, const ::comparison::var_strict & var)
{
   return strict_different(d, var.m_var);
}

bool operator != (int32_t i, const ::comparison::var_strict & var)
{
   return strict_different(i, var.m_var);
}

bool operator != (bool b, const ::comparison::var_strict & var)
{
   return strict_different(b, var.m_var);
}
