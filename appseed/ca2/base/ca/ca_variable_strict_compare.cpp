#include "framework.h"

variable_strict_compare::variable_strict_compare(const class var & var) :
   m_var(var)
{
}

variable_strict_compare::variable_strict_compare(const variable_strict_compare & compare) :
   m_var(compare.m_var)
{
}

bool variable_strict_compare::operator == (const class var & var) const
{
   return m_var.strict_equal(var);
}

bool variable_strict_compare::operator == (const char * psz) const
{
   return m_var.strict_equal(psz);
}

bool variable_strict_compare::operator == (const string & str) const
{
   return m_var.strict_equal(str);
}

bool variable_strict_compare::operator == (double d) const
{
   return m_var.strict_equal(d);
}

bool variable_strict_compare::operator == (int32_t i) const
{
   return m_var.strict_equal(i);
}

bool variable_strict_compare::operator == (bool b) const
{
   return m_var.strict_equal(b);
}

bool variable_strict_compare::operator != (const class var & var) const
{
   return m_var.strict_different(var);
}

bool variable_strict_compare::operator != (const char * psz) const
{
   return m_var.strict_different(psz);
}

bool variable_strict_compare::operator != (const string & str) const
{
   return m_var.strict_different(str);
}

bool variable_strict_compare::operator != (double d) const
{
   return m_var.strict_different(d);
}

bool variable_strict_compare::operator != (int32_t i) const
{
   return m_var.strict_different(i);
}

bool variable_strict_compare::operator != (bool b) const
{
   return m_var.strict_different(b);
}

bool operator == (const char * psz, const variable_strict_compare & var)
{
   return strict_equal(psz, var.m_var);
}

bool operator == (const string & str, const variable_strict_compare & var)
{
   return strict_equal(str, var.m_var);
}

bool operator == (double d, const variable_strict_compare & var)
{
   return strict_equal(d, var.m_var);
}

bool operator == (int32_t i, const variable_strict_compare & var)
{
   return strict_equal(i, var.m_var);
}

bool operator == (bool b, const variable_strict_compare & var)
{
   return strict_equal(b, var.m_var);
}

bool operator != (const char * psz, const variable_strict_compare & var)
{
   return strict_different(psz, var.m_var);
}

bool operator != (const string & str, const variable_strict_compare & var)
{
   return strict_different(str, var.m_var);
}

bool operator != (double d, const variable_strict_compare & var)
{
   return strict_different(d, var.m_var);
}

bool operator != (int32_t i, const variable_strict_compare & var)
{
   return strict_different(i, var.m_var);
}

bool operator != (bool b, const variable_strict_compare & var)
{
   return strict_different(b, var.m_var);
}
