#pragma once


namespace file
{

   inline path & path::operator = (const var & var) { return operator = (var.get_string()); }
   inline path & path::operator += (const var & var) { return operator += (var.get_string()); }
   inline path path::operator -- () const { return ::file::path(::dir::name((const string &)*this),m_epath); }
   inline path path::sibling(const path & path) const   { return ::file::path(::dir::name((const string &)*this) + sep() + string(path).trim_left("\\/"),m_epath); }
   inline path path::sibling(const string & str) const   { return ::file::path(::dir::name((const string &)*this) + sep() + string(str).trim_left("\\/"),m_epath); }
   inline path path::sibling(const char * psz) const   { return ::file::path(::dir::name((const string &)*this) + sep() + string((const string &)psz).trim_left("\\/"),m_epath); }
   inline string path::extension() const { return file_extension_dup(operator const char *()); }
   inline patha path::ascendants_path() const { patha patha; return ascendants_path(patha); }
   inline patha path::ascendants_name() const { patha patha; return ascendants_name(patha); }

} // namespace file