#pragma once
/**
 * pugixml parser - version 1.5
 * --------------------------------------------------------
 * Copyright (C) 2006-2014, by Arseny Kapoulkine (arseny.kapoulkine@gmail.com)
 * Report bugs and download new versions at http://pugixml.org/
 *
 * This library is distributed under the MIT License. See notice at the end
 * of this file.
 *
 * This work is based on the pugxml parser, which is:
 * Copyright (C) 2003, by Kristen Wegner (kristen@tima.net)
 */

#ifndef PUGIXML_VERSION
// Define version macro; evaluates to major * 100 + minor so that it's safe to use in less-than comparisons
#	define PUGIXML_VERSION 150
#endif

// Include user configuration file (this can define various configuration macros)
#include "pugiconfig.hpp"

#ifndef HEADER_PUGIXML_HPP
#define HEADER_PUGIXML_HPP

// Include stddef.h for size_t and ptrdiff_t
#include <stddef.h>

// Include exception header for XPath
#if !defined(PUGIXML_NO_XPATH) && !defined(PUGIXML_NO_EXCEPTIONS)
#	include <exception>
#endif

//// Include STL headers
//#ifndef PUGIXML_NO_STL
//#	include <iterator>
//#	include <iosfwd>
//#	include <string>
//#endif

// Macro for deprecated features
#ifndef PUGIXML_DEPRECATED
#	if defined(__GNUC__)
#		define PUGIXML_DEPRECATED __attribute__((deprecated))
#	elif defined(_MSC_VER) && _MSC_VER >= 1300
#		define PUGIXML_DEPRECATED __declspec(deprecated)
#	else
#		define PUGIXML_DEPRECATED
#	endif
#endif

// If no API is defined, assume default
#ifndef PUGIXML_API
#	define PUGIXML_API
#endif

// If no API for classes is defined, assume default
#ifndef PUGIXML_CLASS
#	define PUGIXML_CLASS PUGIXML_API
#endif

// If no API for functions is defined, assume default
#ifndef PUGIXML_FUNCTION
#	define PUGIXML_FUNCTION PUGIXML_API
#endif

// If the platform is known to have long long support, enable long long functions
#ifndef PUGIXML_HAS_LONG_LONG
#	if defined(__cplusplus) && __cplusplus >= 201103
#		define PUGIXML_HAS_LONG_LONG
#	elif defined(_MSC_VER) && _MSC_VER >= 1400
#		define PUGIXML_HAS_LONG_LONG
#	endif
#endif

// Character interface macros
#ifdef PUGIXML_WCHAR_MODE
#	define PUGIXML_TEXT(t) L ## t
#	define PUGIXML_CHAR wchar_t
#else
#	define PUGIXML_TEXT(t) t
#	define PUGIXML_CHAR char
#endif

namespace xml
{
	// Character type used for all internal storage and operations; depends on PUGIXML_WCHAR_MODE
	typedef PUGIXML_CHAR char_t;

//#ifndef PUGIXML_NO_STL
//	// String type used for operations that work with STL string; depends on PUGIXML_WCHAR_MODE
//	typedef std::basic_string<PUGIXML_CHAR, std::char_traits<PUGIXML_CHAR>, std::allocator<PUGIXML_CHAR> > string_t;
//#endif

   typedef ::string string_t;

}

// The PugiXML namespace
namespace xml
{
	// Tree node types
	enum node_type
	{
		node_null,			// Empty (null) node handle
		node_document,		// A document tree's absolute root
		node_element,		// Element tag, i.e. '<node/>'
		node_pcdata,		// Plain character data, i.e. 'text'
		node_cdata,			// Character data, i.e. '<![CDATA[text]]>'
		node_comment,		// Comment tag, i.e. '<!-- text -->'
		node_pi,			// Processing instruction, i.e. '<?name?>'
		node_declaration,	// Document declaration, i.e. '<?xml version="1.0"?>'
		node_doctype		// Document type declaration, i.e. '<!DOCTYPE doc>'
	};

	// Parsing options

	// Minimal parsing mode (equivalent to turning all other flags off).
	// Only elements and PCDATA sections are added to the DOM tree, no text conversions are performed.
	const unsigned int parse_minimal = 0x0000;

	// This flag determines if processing instructions (node_pi) are added to the DOM tree. This flag is off by default.
	const unsigned int parse_pi = 0x0001;

	// This flag determines if comments (node_comment) are added to the DOM tree. This flag is off by default.
	const unsigned int parse_comments = 0x0002;

	// This flag determines if CDATA sections (node_cdata) are added to the DOM tree. This flag is on by default.
	const unsigned int parse_cdata = 0x0004;

	// This flag determines if plain character data (node_pcdata) that consist only of whitespace are added to the DOM tree.
	// This flag is off by default; turning it on usually results in slower parsing and more memory consumption.
	const unsigned int parse_ws_pcdata = 0x0008;

	// This flag determines if character and entity references are expanded during parsing. This flag is on by default.
	const unsigned int parse_escapes = 0x0010;

	// This flag determines if EOL characters are normalized (converted to #xA) during parsing. This flag is on by default.
	const unsigned int parse_eol = 0x0020;
	
	// This flag determines if ::xml::attribute values are normalized using CDATA normalization rules during parsing. This flag is on by default.
	const unsigned int parse_wconv_attribute = 0x0040;

	// This flag determines if ::xml::attribute values are normalized using NMTOKENS normalization rules during parsing. This flag is off by default.
	const unsigned int parse_wnorm_attribute = 0x0080;
	
	// This flag determines if document declaration (node_declaration) is added to the DOM tree. This flag is off by default.
	const unsigned int parse_declaration = 0x0100;

	// This flag determines if document type declaration (node_doctype) is added to the DOM tree. This flag is off by default.
	const unsigned int parse_doctype = 0x0200;

	// This flag determines if plain character data (node_pcdata) that is the only child of the parent node and that consists only
	// of whitespace is added to the DOM tree.
	// This flag is off by default; turning it on may result in slower parsing and more memory consumption.
	const unsigned int parse_ws_pcdata_single = 0x0400;

	// This flag determines if leading and trailing whitespace is to be removed from plain character data. This flag is off by default.
	const unsigned int parse_trim_pcdata = 0x0800;

	// This flag determines if plain character data that does not have a parent node is added to the DOM tree, and if an empty document
	// is a valid document. This flag is off by default.
	const unsigned int parse_fragment = 0x1000;

	// The default parsing mode.
	// Elements, PCDATA and CDATA sections are added to the DOM tree, character/reference entities are expanded,
	// End-of-Line characters are normalized, ::xml::attribute values are normalized using CDATA normalization rules.
	const unsigned int parse_default = parse_cdata | parse_escapes | parse_wconv_attribute | parse_eol;

	// The full parsing mode.
	// Nodes of all types are added to the DOM tree, character/reference entities are expanded,
	// End-of-Line characters are normalized, ::xml::attribute values are normalized using CDATA normalization rules.
	const unsigned int parse_full = parse_default | parse_pi | parse_comments | parse_declaration | parse_doctype;

	// These flags determine the encoding of input data for XML document
	enum encoding
	{
		encoding_auto,		// Auto-detect input encoding using BOM or < / <? detection; use UTF8 if BOM is not found
		encoding_utf8,		// UTF8 encoding
		encoding_utf16_le,	// Little-endian UTF16
		encoding_utf16_be,	// Big-endian UTF16
		encoding_utf16,		// UTF16 with native endianness
		encoding_utf32_le,	// Little-endian UTF32
		encoding_utf32_be,	// Big-endian UTF32
		encoding_utf32,		// UTF32 with native endianness
		encoding_wchar,		// The same encoding wchar_t has (either UTF16 or UTF32)
		encoding_latin1
	};

	// Formatting flags
	
	// Indent the nodes that are written to output stream with as many indentation strings as deep the node is in DOM tree. This flag is on by default.
	const unsigned int format_indent = 0x01;
	
	// Write encoding-specific BOM to the output stream. This flag is off by default.
	const unsigned int format_write_bom = 0x02;

	// Use raw output mode (no indentation and no line breaks are written). This flag is off by default.
	const unsigned int format_raw = 0x04;
	
	// Omit default XML declaration even if there is no declaration in the document. This flag is off by default.
	const unsigned int format_no_declaration = 0x08;

	// Don't escape ::xml::attribute values and PCDATA contents. This flag is off by default.
	const unsigned int format_no_escapes = 0x10;

	// Open file using text mode in document::save_file. This enables special character (i.e. new-line) conversions on some systems. This flag is off by default.
	const unsigned int format_save_file_text = 0x20;

	// The default set of formatting flags.
	// Nodes are indented depending on their depth in DOM tree, a default declaration is output if document has none.
	const unsigned int format_default = format_indent;
		
	// Forward declarations
	struct attribute_struct;
	struct node_struct;

	class node_iterator;
	class attribute_iterator;
	class named_node_iterator;

	class tree_walker;

	struct parse_result;

	class node;

	class text;
	
	#ifndef PUGIXML_NO_XPATH
	class xpath_node;
	class xpath_node_set;
	class xpath_query;
	class xpath_variable_set;
	#endif

	// Range-based for loop support
	template <typename It> class object_range
	{
	public:
		typedef It const_iterator;
		typedef It iterator;

		object_range(It b, It e): _begin(b), _end(e)
		{
		}

		It begin() const { return _begin; }
		It end() const { return _end; }

      ::count get_count() const
      {
         ::count c = 0;
         for(It i = begin(); i != begin(); i++)
         {
            c++;
         }
         return c;
      }

	private:
		It _begin, _end;
	};

	// Writer interface for node printing (see node::print)
	//class PUGIXML_CLASS writer
	//{
	//public:
	//	virtual ~writer() {}

	//	// Write memory chunk into stream/file/whatever
	//	virtual void write(const void* data, size_t size) = 0;
	//};

   typedef ::file::writer writer;

	// writer implementation for FILE*
	class PUGIXML_CLASS writer_file: public writer
	{
	public:
		// Construct writer from a FILE* object; void* is used to avoid header dependencies on stdio
		writer_file(void* file);

		virtual void write(const void* data, size_t size);

	private:
		void* file;
	};

	#ifndef PUGIXML_NO_STL
	// writer implementation for streams
	class PUGIXML_CLASS writer_stream: public writer
	{
	public:
		// Construct writer from an output stream object
      writer_stream(::file::output_stream & stream);

		virtual void write(const void* data, size_t size);

	private:
      ::file::output_stream* narrow_stream;
	};
	#endif

	// A light-weight handle for manipulating attributes in DOM tree
	class PUGIXML_CLASS attribute
	{
		friend class attribute_iterator;
		friend class node;

	private:
		attribute_struct* _attr;
	
		typedef void (*unspecified_bool_type)(::xml::attribute***);

	public:
		// Default constructor. Constructs an empty ::xml::attribute.
		attribute();
		
		// Constructs ::xml::attribute from internal pointer
		explicit attribute(attribute_struct* attr);

		// Safe bool conversion operator
		operator unspecified_bool_type() const;

		// Borland C++ workaround
		bool operator!() const;

		// Comparison operators (compares wrapped ::xml::attribute pointers)
		bool operator==(const ::xml::attribute& r) const;
		bool operator!=(const ::xml::attribute& r) const;
		bool operator<(const ::xml::attribute& r) const;
		bool operator>(const ::xml::attribute& r) const;
		bool operator<=(const ::xml::attribute& r) const;
		bool operator>=(const ::xml::attribute& r) const;

		// Check if ::xml::attribute is empty
		bool empty() const;

		// Get ::xml::attribute name/value, or "" if ::xml::attribute is empty
		const char_t* name() const;
		const char_t* value() const;

      string get_name() const { return name(); }
      string get_value() const { return value(); }



		// Get ::xml::attribute value, or the default value if ::xml::attribute is empty
		const char_t* as_string(const char_t* def = PUGIXML_TEXT("")) const;

		// Get ::xml::attribute value as a number, or the default value if conversion did not succeed or ::xml::attribute is empty
		int as_int(int def = 0) const;
		unsigned int as_uint(unsigned int def = 0) const;
		double as_double(double def = 0) const;
		float as_float(float def = 0) const;

	#ifdef PUGIXML_HAS_LONG_LONG
		long long as_llong(long long def = 0) const;
		unsigned long long as_ullong(unsigned long long def = 0) const;
	#endif

		// Get ::xml::attribute value as bool (returns true if first character is in '1tTyY' set), or the default value if ::xml::attribute is empty
		bool as_bool(bool def = false) const;

		// Set ::xml::attribute name/value (returns false if ::xml::attribute is empty or there is not enough memory)
		bool set_name(const char_t* rhs);
		bool set_value(const char_t* rhs);

		// Set ::xml::attribute value with type conversion (numbers are converted to strings, boolean is converted to "true"/"false")
		bool set_value(int rhs);
		bool set_value(unsigned int rhs);
		bool set_value(double rhs);
		bool set_value(bool rhs);

	#ifdef PUGIXML_HAS_LONG_LONG
		bool set_value(long long rhs);
		bool set_value(unsigned long long rhs);
	#endif

		// Set ::xml::attribute value (equivalent to set_value without error checking)
		::xml::attribute& operator=(const char_t* rhs);
		::xml::attribute& operator=(int rhs);
		::xml::attribute& operator=(unsigned int rhs);
		::xml::attribute& operator=(double rhs);
		::xml::attribute& operator=(bool rhs);

	#ifdef PUGIXML_HAS_LONG_LONG
		::xml::attribute& operator=(long long rhs);
		::xml::attribute& operator=(unsigned long long rhs);
	#endif

		// Get next/previous ::xml::attribute in the ::xml::attribute list of the parent node
		::xml::attribute next_attribute() const;
		::xml::attribute previous_attribute() const;

		// Get hash value (unique for handles to the same object)
		size_t hash_value() const;

		// Get internal pointer
		attribute_struct* internal_object() const;
	};

#ifdef __BORLANDC__
	// Borland C++ workaround
	bool PUGIXML_FUNCTION operator&&(const ::xml::attribute& lhs, bool rhs);
	bool PUGIXML_FUNCTION operator||(const ::xml::attribute& lhs, bool rhs);
#endif

	// A light-weight handle for manipulating nodes in DOM tree
	class PUGIXML_CLASS node
	{
		friend class attribute_iterator;
		friend class node_iterator;
		friend class named_node_iterator;

	protected:
		node_struct* _root;

		typedef void (*unspecified_bool_type)(node***);

	public:
		// Default constructor. Constructs an empty node.
		node();

            //virtual void write(::file::output_stream & ostream);
            //virtual void read(::file::input_stream & istream);
		// Constructs node from internal pointer
		explicit node(node_struct* p);

		// Safe bool conversion operator
		operator unspecified_bool_type() const;

		// Borland C++ workaround
		bool operator!() const;
	
		// Comparison operators (compares wrapped node pointers)
		bool operator==(const node& r) const;
		bool operator!=(const node& r) const;
		bool operator<(const node& r) const;
		bool operator>(const node& r) const;
		bool operator<=(const node& r) const;
		bool operator>=(const node& r) const;

		// Check if node is empty.
		bool empty() const;

		// Get node type
		node_type type() const;

		// Get node name, or "" if node is empty or it has no name
      const char * name() const;

		// Get node value, or "" if node is empty or it has no value
        // Note: For <node>text</node> node.value() does not return "text"! Use child_value() or text() methods to access text inside nodes.
		const char * value() const;

      string get_value() const { return value(); }
      string get_name() const { return name(); }
      ::count get_children_count() const { ::count c = 0; ::xml::node node = first_child(); while(!node.empty()) { c++; node = node.next_sibling(); } return c; }
      ::xml::node child_at(::index i) const { ::xml::node node = first_child(); while(!node.empty() && i > 0) { i--; node = node.next_sibling(); } if(i == 0 && !node.empty()) return node; else return ::xml::node(); }
      ::xml::node get_child(const char * name) const { return child(name); }
      ::xml::node get_first_child() const { return first_child();  }
      ::xml::node get_next_sibling() const { return next_sibling();  }
      node_type get_type() const { return type(); }
      ::xml::node GetChildByAttr(const char * name,const char * attr,const char * value) { return find_child_by_attribute(name,attr,value); }
      ::xml::node GetChildByAllAttr(const char * name,const stringa & attra,const stringa & stra)
      {
         ::xml::node n = first_child();
         while(!n.empty())
         {
            for(index i = 0; i < attra.get_size(); i++)
            {
               if(n.attr(attra[i]) != stra[i])
                  goto skip;
            }
            return n;
         skip:;
         }
         return node();
      }

      bool get_attr(const char_t* name,string & strName) const
      {
         ::xml::attribute attr = attribute(name);
         if(attr.empty())
            return false;
         strName = attr.get_value();
         return true;
      }

      bool get_attr(const char_t* name,int32_t  & i) const
      {
         ::xml::attribute attr = attribute(name);
         if(attr.empty())
            return false;
         i = attr.as_int(i);
         return true;
      }

      ::xml::attribute set_attr(const char * pszName,const var & var = ::var(::var::type_new))
      {
         ::xml::attribute attr = attribute(pszName);
         if(attr.empty())
            attr = append_attribute(pszName);
         if(var.is_integer())
         {
            attr.set_value(var.int32());
         }
         else
         {
            attr.set_value(var.get_string());
         }
         return attr;
      }

      ::xml::attribute add_attr(const char * pszName = NULL,const var & var = ::var(::var::type_new))
      {
         ::xml::attribute attr = append_attribute(pszName);
         if(var.is_integer())
         {
            attr.set_value(var.int32());
         }
         else
         {
            attr.set_value(var.get_string());
         }
         return attr;
      }

      bool set_value(const string & strValue);
 
      index find(node pnode);
      index find(const char * lpcszName, index iStart = 0);
      index find(const char * lpcszName,const ::array < attribute > & attr,index iStart = 0);
      bool contains(const ::array < attribute > & attributea);
      string get_child_value(const char * name)
      {
         node node = get_child(name);
         return node.empty() ? "" : (const char *)node.get_value();
      }


      index get_index() const;
      
      index_array get_indexed_path() const;
      void get_indexed_path(index_array & ia) const;


		// Get ::xml::attribute list
		::xml::attribute first_attribute() const;
		::xml::attribute last_attribute() const;

		// Get children list
		node first_child() const;
		node last_child() const;

		// Get next/previous sibling in the children list of the parent node
		node next_sibling() const;
		node previous_sibling() const;
		
		// Get parent node
		node parent() const;

		// Get root of DOM tree this node belongs to
		node root() const;

		// Get text object for the current node
		text text() const;

		// Get child, ::xml::attribute or next/previous sibling with the specified name
		node child(const char_t* name) const;
		::xml::attribute attribute(const char_t* name) const;
      var attr(const char_t* name) const { return attribute(name).value(); }
		node next_sibling(const char_t* name) const;
		node previous_sibling(const char_t* name) const;

		// Get child value of current node; that is, value of the first child node of type PCDATA/CDATA
		const char_t* child_value() const;

		// Get child value of child with specified name. Equivalent to child(name).child_value().
		const char_t* child_value(const char_t* name) const;

		// Set node name/value (returns false if node is empty, there is not enough memory, or node can not have name/value)
		bool set_name(const char_t* rhs);
		bool set_value(const char_t* rhs);
		
		// Add ::xml::attribute with specified name. Returns added ::xml::attribute, or empty ::xml::attribute on errors.
		::xml::attribute append_attribute(const char_t* name);
      ::xml::attribute prepend_attribute(const char_t* name);
      ::xml::attribute insert_attribute_after(const char_t* name,const ::xml::attribute& attr);
      ::xml::attribute insert_attribute_before(const char_t* name,const ::xml::attribute& attr);

		// Add a copy of the specified ::xml::attribute. Returns added ::xml::attribute, or empty ::xml::attribute on errors.
      ::xml::attribute append_copy(const ::xml::attribute& proto);
      ::xml::attribute prepend_copy(const ::xml::attribute& proto);
      ::xml::attribute insert_copy_after(const ::xml::attribute& proto,const ::xml::attribute& attr);
      ::xml::attribute insert_copy_before(const ::xml::attribute& proto,const ::xml::attribute& attr);

		// Add child node with specified type. Returns added node, or empty node on errors.
		node append_child(node_type type = node_element);
		node prepend_child(node_type type = node_element);
		node insert_child_after(node_type type, const node& node);
		node insert_child_before(node_type type, const node& node);

		// Add child element with specified name. Returns added node, or empty node on errors.
		node append_child(const char_t* name);
		node prepend_child(const char_t* name);
		node insert_child_after(const char_t* name, const node& node);
		node insert_child_before(const char_t* name, const node& node);

		// Add a copy of the specified node as a child. Returns added node, or empty node on errors.
		node append_copy(const node& proto);
		node prepend_copy(const node& proto);
		node insert_copy_after(const node& proto, const node& node);
		node insert_copy_before(const node& proto, const node& node);

		// Move the specified node to become a child of this node. Returns moved node, or empty node on errors.
		node append_move(const node& moved);
		node prepend_move(const node& moved);
		node insert_move_after(const node& moved, const node& node);
		node insert_move_before(const node& moved, const node& node);

		// Remove specified ::xml::attribute
		bool remove_attribute(const ::xml::attribute& a);
		bool remove_attribute(const char_t* name);

		// Remove specified child
		bool remove_child(const node& n);
		bool remove_child(const char_t* name);

		// Parses buffer as an XML document fragment and appends all nodes as children of the current node.
		// Copies/converts the buffer, so it may be deleted or changed after the function returns.
		// Note: append_buffer allocates memory that has the lifetime of the owning document; removing the appended nodes does not immediately reclaim that memory.
		parse_result append_buffer(const void* contents, size_t size, unsigned int options = parse_default, encoding encoding = encoding_auto);

		// Find ::xml::attribute using predicate. Returns first ::xml::attribute for which predicate returned true.
		template <typename Predicate> ::xml::attribute find_attribute(Predicate pred) const
		{
			if (!_root) return ::xml::attribute();
			
			for (::xml::attribute attrib = first_attribute(); attrib; attrib = attrib.next_attribute())
				if (pred(attrib))
					return attrib;
		
			return ::xml::attribute();
		}

		// Find child node using predicate. Returns first child for which predicate returned true.
		template <typename Predicate> node find_child(Predicate pred) const
		{
			if (!_root) return node();
	
			for (node node = first_child(); node; node = node.next_sibling())
				if (pred(node))
					return node;
		
			return node();
		}

		// Find node from subtree using predicate. Returns first node from subtree (depth-first), for which predicate returned true.
		template <typename Predicate> node find_node(Predicate pred) const
		{
			if (!_root) return node();

			node cur = first_child();
			
			while (cur._root && cur._root != _root)
			{
				if (pred(cur)) return cur;

				if (cur.first_child()) cur = cur.first_child();
				else if (cur.next_sibling()) cur = cur.next_sibling();
				else
				{
					while (!cur.next_sibling() && cur._root != _root) cur = cur.parent();

					if (cur._root != _root) cur = cur.next_sibling();
				}
			}

			return node();
		}

		// Find child node by ::xml::attribute name/value
		node find_child_by_attribute(const char_t* name, const char_t* attr_name, const char_t* attr_value) const;
		node find_child_by_attribute(const char_t* attr_name, const char_t* attr_value) const;

	#ifndef PUGIXML_NO_STL
		// Get the absolute node path from root as a text string.
		string_t path(char_t delimiter = '/') const;
	#endif

		// Search for a node by path consisting of node names and . or .. elements.
		node first_element_by_path(const char_t* path, char_t delimiter = '/') const;

		// Recursively traverse subtree with tree_walker
		bool traverse(tree_walker& walker);
	
	#ifndef PUGIXML_NO_XPATH
		// Select single node by evaluating XPath query. Returns first node from the resulting node set.
		xpath_node select_node(const char_t* query, xpath_variable_set* variables = 0) const;
		xpath_node select_node(const xpath_query& query) const;

		// Select node set by evaluating XPath query
		xpath_node_set select_nodes(const char_t* query, xpath_variable_set* variables = 0) const;
		xpath_node_set select_nodes(const xpath_query& query) const;

		// (deprecated: use select_node instead) Select single node by evaluating XPath query.
		xpath_node select_single_node(const char_t* query, xpath_variable_set* variables = 0) const;
		xpath_node select_single_node(const xpath_query& query) const;

	#endif
		
		// Print subtree using a writer object
		void print(writer& writer, const char_t* indent = PUGIXML_TEXT("\t"), unsigned int flags = format_default, encoding encoding = encoding_auto, unsigned int depth = 0) const;

	#ifndef PUGIXML_NO_STL
		// Print subtree to stream
      void print(::file::output_stream & os,const char_t* indent = PUGIXML_TEXT("\t"),unsigned int flags = format_default,encoding encoding = encoding_auto,unsigned int depth = 0) const;
	#endif

		// Child nodes iterators
		typedef node_iterator iterator;

		iterator begin() const;
		iterator end() const;

		// Attribute iterators
		typedef attribute_iterator attribute_iterator;

		attribute_iterator attributes_begin() const;
		attribute_iterator attributes_end() const;

		// Range-based for support
		object_range<node_iterator> children() const;
		object_range<named_node_iterator> children(const char_t* name) const;
		object_range<attribute_iterator> attributes() const;

		// Get node offset in parsed file/string (in char_t units) for debugging purposes
		ptrdiff_t offset_debug() const;

		// Get hash value (unique for handles to the same object)
		size_t hash_value() const;

		// Get internal pointer
		node_struct* internal_object() const;
	};

#ifdef __BORLANDC__
	// Borland C++ workaround
	bool PUGIXML_FUNCTION operator&&(const node& lhs, bool rhs);
	bool PUGIXML_FUNCTION operator||(const node& lhs, bool rhs);
#endif

	// A helper for working with text inside PCDATA nodes
	class PUGIXML_CLASS text
	{
		friend class node;

		node_struct* _root;

		typedef void (*unspecified_bool_type)(text***);

		explicit text(node_struct* root);

		node_struct* _data_new();
		node_struct* _data() const;

	public:
		// Default constructor. Constructs an empty object.
		text();

		// Safe bool conversion operator
		operator unspecified_bool_type() const;

		// Borland C++ workaround
		bool operator!() const;

		// Check if text object is empty
		bool empty() const;

		// Get text, or "" if object is empty
		const char_t* get() const;

		// Get text, or the default value if object is empty
		const char_t* as_string(const char_t* def = PUGIXML_TEXT("")) const;

		// Get text as a number, or the default value if conversion did not succeed or object is empty
		int as_int(int def = 0) const;
		unsigned int as_uint(unsigned int def = 0) const;
		double as_double(double def = 0) const;
		float as_float(float def = 0) const;

	#ifdef PUGIXML_HAS_LONG_LONG
		long long as_llong(long long def = 0) const;
		unsigned long long as_ullong(unsigned long long def = 0) const;
	#endif

		// Get text as bool (returns true if first character is in '1tTyY' set), or the default value if object is empty
		bool as_bool(bool def = false) const;

		// Set text (returns false if object is empty or there is not enough memory)
		bool set(const char_t* rhs);

		// Set text with type conversion (numbers are converted to strings, boolean is converted to "true"/"false")
		bool set(int rhs);
		bool set(unsigned int rhs);
		bool set(double rhs);
		bool set(bool rhs);

	#ifdef PUGIXML_HAS_LONG_LONG
		bool set(long long rhs);
		bool set(unsigned long long rhs);
	#endif

		// Set text (equivalent to set without error checking)
		text& operator=(const char_t* rhs);
		text& operator=(int rhs);
		text& operator=(unsigned int rhs);
		text& operator=(double rhs);
		text& operator=(bool rhs);

	#ifdef PUGIXML_HAS_LONG_LONG
		text& operator=(long long rhs);
		text& operator=(unsigned long long rhs);
	#endif

		// Get the data node (node_pcdata or node_cdata) for this object
		node data() const;
	};

#ifdef __BORLANDC__
	// Borland C++ workaround
	bool PUGIXML_FUNCTION operator&&(const text& lhs, bool rhs);
	bool PUGIXML_FUNCTION operator||(const text& lhs, bool rhs);
#endif

	// Child node iterator (a bidirectional iterator over a collection of node)
	class PUGIXML_CLASS node_iterator
	{
		friend class node;

	private:
		mutable node _wrap;
		node _parent;

		node_iterator(node_struct* ref, node_struct* parent);

	public:
		// Iterator traits
		typedef ptrdiff_t difference_type;
		typedef node value_type;
		typedef node* pointer;
		typedef node& reference;


		// Default constructor
		node_iterator();

		// Construct an iterator which points to the specified node
		node_iterator(const node& node);

		// Iterator operators
		bool operator==(const node_iterator& rhs) const;
		bool operator!=(const node_iterator& rhs) const;

		node& operator*() const;
		node* operator->() const;

		const node_iterator& operator++();
		node_iterator operator++(int);

		const node_iterator& operator--();
		node_iterator operator--(int);
	};

	// Attribute iterator (a bidirectional iterator over a collection of ::xml::attribute)
	class PUGIXML_CLASS attribute_iterator
	{
		friend class node;

	private:
		mutable ::xml::attribute _wrap;
		node _parent;

		attribute_iterator(attribute_struct* ref, node_struct* parent);

	public:
		// Iterator traits
		typedef ptrdiff_t difference_type;
		typedef ::xml::attribute value_type;
		typedef ::xml::attribute* pointer;
		typedef ::xml::attribute& reference;


		// Default constructor
		attribute_iterator();

		// Construct an iterator which points to the specified ::xml::attribute
		attribute_iterator(const ::xml::attribute& attr, const node& parent);

		// Iterator operators
		bool operator==(const attribute_iterator& rhs) const;
		bool operator!=(const attribute_iterator& rhs) const;

		::xml::attribute& operator*() const;
		::xml::attribute* operator->() const;

		const attribute_iterator& operator++();
		attribute_iterator operator++(int);

		const attribute_iterator& operator--();
		attribute_iterator operator--(int);
	};

	// Named node range helper
	class PUGIXML_CLASS named_node_iterator
	{
		friend class node;

	public:
		// Iterator traits
		typedef ptrdiff_t difference_type;
		typedef node value_type;
		typedef node* pointer;
		typedef node& reference;


		// Default constructor
		named_node_iterator();

		// Construct an iterator which points to the specified node
		named_node_iterator(const node& node, const char_t* name);

		// Iterator operators
		bool operator==(const named_node_iterator& rhs) const;
		bool operator!=(const named_node_iterator& rhs) const;

		node& operator*() const;
		node* operator->() const;

		const named_node_iterator& operator++();
		named_node_iterator operator++(int);

		const named_node_iterator& operator--();
		named_node_iterator operator--(int);

	private:
		mutable node _wrap;
		node _parent;
		const char_t* _name;

		named_node_iterator(node_struct* ref, node_struct* parent, const char_t* name);
	};

	// Abstract tree walker class (see node::traverse)
	class PUGIXML_CLASS tree_walker
	{
		friend class node;

	private:
		int _depth;
	
	protected:
		// Get current traversal depth
		int depth() const;
	
	public:
		tree_walker();
		virtual ~tree_walker();

		// Callback that is called when traversal begins
		virtual bool begin(node& node);

		// Callback that is called for each node traversed
		virtual bool for_each(node& node) = 0;

		// Callback that is called when traversal ends
		virtual bool end(node& node);
	};

	// Parsing status, returned as part of parse_result object
	enum parse_status
	{
		status_ok = 0,				// No error

		status_file_not_found,		// File was not found during load_file()
		status_io_error,			// Error reading from file/stream
		status_out_of_memory,		// Could not allocate memory
		status_internal_error,		// Internal error occurred

		status_unrecognized_tag,	// Parser could not determine tag type

		status_bad_pi,				// Parsing error occurred while parsing document declaration/processing instruction
		status_bad_comment,			// Parsing error occurred while parsing comment
		status_bad_cdata,			// Parsing error occurred while parsing CDATA section
		status_bad_doctype,			// Parsing error occurred while parsing document type declaration
		status_bad_pcdata,			// Parsing error occurred while parsing PCDATA section
		status_bad_start_element,	// Parsing error occurred while parsing start element tag
		status_bad_attribute,		// Parsing error occurred while parsing element ::xml::attribute
		status_bad_end_element,		// Parsing error occurred while parsing end element tag
		status_end_element_mismatch,// There was a mismatch of start-end tags (closing tag had incorrect name, some tag was not closed or there was an excessive closing tag)

		status_append_invalid_root,	// Unable to append nodes since root type is not node_element or node_document (exclusive to node::append_buffer)

		status_no_document_element	// Parsing resulted in a document without element nodes
	};

	// Parsing result
	struct PUGIXML_CLASS parse_result
	{
		// Parsing status (see parse_status)
		parse_status status;

		// Last parsed offset (in char_t units from start of input data)
		ptrdiff_t offset;

		// Source document encoding
		encoding encoding;

		// Default constructor, initializes object to failed state
		parse_result();

		// Cast to bool operator
		operator bool() const;

		// Get error description
		const char* description() const;
	};

	// Document class (DOM tree root)
	class PUGIXML_CLASS document: 
      virtual public node
	{
	private:
		char_t* _buffer;

		char _memory[192];
		
		// Non-copyable semantics
		document(const document&);
		const document& operator=(const document&);

		void create();
		void destroy();

	public:
		// Default constructor, makes empty document
		document();

      //void read(::file::input_stream & istream);
      //void write(::file::output_stream & istream);

		// Destructor, invalidates all node/::xml::attribute handles to this document
		~document();

		// Removes all nodes, leaving the empty document
		void reset();

		// Removes all nodes, then copies the entire contents of the specified document
		void reset(const document& proto);

	#ifndef PUGIXML_NO_STL
		// Load document from stream.
		parse_result load(::file::input_stream & stream, unsigned int options = parse_default, encoding encoding = encoding_auto);
	#endif

      string m_strLocation;

		// (deprecated: use load_string instead) Load document from zero-terminated string. No encoding conversions are applied.
		parse_result load(const char_t* contents, unsigned int options = parse_default);

		// Load document from zero-terminated string. No encoding conversions are applied.
		parse_result load_string(const char_t* contents, unsigned int options = parse_default);

		// Load document from file
		parse_result load_file(const char* path, unsigned int options = parse_default, encoding encoding = encoding_auto);
		parse_result load_file(const wchar_t* path, unsigned int options = parse_default, encoding encoding = encoding_auto);

		// Load document from buffer. Copies/converts the buffer, so it may be deleted or changed after the function returns.
		parse_result load_buffer(const void* contents, size_t size, unsigned int options = parse_default, encoding encoding = encoding_auto);

		// Load document from buffer, using the buffer for in-place parsing (the buffer is modified and used for storage of document data).
		// You should ensure that buffer data will persist throughout the document's lifetime, and free the buffer memory manually once document is destroyed.
		parse_result load_buffer_inplace(void* contents, size_t size, unsigned int options = parse_default, encoding encoding = encoding_auto);

		// Load document from buffer, using the buffer for in-place parsing (the buffer is modified and used for storage of document data).
		// You should allocate the buffer with pugixml allocation function; document will free the buffer when it is no longer needed (you can't use it anymore).
		parse_result load_buffer_inplace_own(void* contents, size_t size, unsigned int options = parse_default, encoding encoding = encoding_auto);

		// Save XML document to writer (semantics is slightly different from node::print, see documentation for details).
		void save(writer& writer, const char_t* indent = PUGIXML_TEXT("\t"), unsigned int flags = format_default, encoding encoding = encoding_auto) const;

	#ifndef PUGIXML_NO_STL
		// Save XML document to stream (semantics is slightly different from node::print, see documentation for details).
		void save(::file::output_stream& stream, const char_t* indent = PUGIXML_TEXT("\t"), unsigned int flags = format_default, encoding encoding = encoding_auto) const;
	#endif

		// Save XML to file
		bool save_file(const char* path, const char_t* indent = PUGIXML_TEXT("\t"), unsigned int flags = format_default, encoding encoding = encoding_auto) const;
		bool save_file(const wchar_t* path, const char_t* indent = PUGIXML_TEXT("\t"), unsigned int flags = format_default, encoding encoding = encoding_auto) const;

		// Get document element
		node document_element() const;
	};

#ifndef PUGIXML_NO_XPATH
	// XPath query return type
	enum xpath_value_type
	{
		xpath_type_none,	  // Unknown type (query failed to compile)
		xpath_type_node_set,  // Node set (xpath_node_set)
		xpath_type_number,	  // Number
		xpath_type_string,	  // String
		xpath_type_boolean	  // Boolean
	};

	// XPath parsing result
	struct PUGIXML_CLASS xpath_parse_result
	{
		// Error message (0 if no error)
		const char* error;

		// Last parsed offset (in char_t units from string start)
		ptrdiff_t offset;

		// Default constructor, initializes object to failed state
		xpath_parse_result();

		// Cast to bool operator
		operator bool() const;

		// Get error description
		const char* description() const;
	};

	// A single XPath variable
	class PUGIXML_CLASS xpath_variable
	{
		friend class xpath_variable_set;

	protected:
		xpath_value_type _type;
		xpath_variable* _next;

		xpath_variable();

		// Non-copyable semantics
		xpath_variable(const xpath_variable&);
		xpath_variable& operator=(const xpath_variable&);
		
	public:
		// Get variable name
		const char_t* name() const;

		// Get variable type
		xpath_value_type type() const;

		// Get variable value; no type conversion is performed, default value (false, NaN, empty string, empty node set) is returned on type mismatch error
		bool get_boolean() const;
		double get_number() const;
		const char_t* get_string() const;
		const xpath_node_set& get_node_set() const;

		// Set variable value; no type conversion is performed, false is returned on type mismatch error
		bool set(bool value);
		bool set(double value);
		bool set(const char_t* value);
		bool set(const xpath_node_set& value);
	};

	// A set of XPath variables
	class PUGIXML_CLASS xpath_variable_set
	{
	private:
		xpath_variable* _data[64];

		// Non-copyable semantics
		xpath_variable_set(const xpath_variable_set&);
		xpath_variable_set& operator=(const xpath_variable_set&);

		xpath_variable* find(const char_t* name) const;

	public:
		// Default constructor/destructor
		xpath_variable_set();
		~xpath_variable_set();

		// Add a new variable or get the existing one, if the types match
		xpath_variable* add(const char_t* name, xpath_value_type type);

		// Set value of an existing variable; no type conversion is performed, false is returned if there is no such variable or if types mismatch
		bool set(const char_t* name, bool value);
		bool set(const char_t* name, double value);
		bool set(const char_t* name, const char_t* value);
		bool set(const char_t* name, const xpath_node_set& value);

		// Get existing variable by name
		xpath_variable* get(const char_t* name);
		const xpath_variable* get(const char_t* name) const;
	};

	// A compiled XPath query object
	class PUGIXML_CLASS xpath_query
	{
	private:
		void* _impl;
		xpath_parse_result _result;

		typedef void (*unspecified_bool_type)(xpath_query***);

		// Non-copyable semantics
		xpath_query(const xpath_query&);
		xpath_query& operator=(const xpath_query&);

	public:
		// Construct a compiled object from XPath expression.
		// If PUGIXML_NO_EXCEPTIONS is not defined, throws xpath_exception on compilation errors.
		explicit xpath_query(const char_t* query, xpath_variable_set* variables = 0);

		// Destructor
		~xpath_query();

		// Get query expression return type
		xpath_value_type return_type() const;
		
		// Evaluate expression as boolean value in the specified context; performs type conversion if necessary.
		// If PUGIXML_NO_EXCEPTIONS is not defined, throws std::bad_alloc on out of memory errors.
		bool evaluate_boolean(const xpath_node& n) const;
		
		// Evaluate expression as double value in the specified context; performs type conversion if necessary.
		// If PUGIXML_NO_EXCEPTIONS is not defined, throws std::bad_alloc on out of memory errors.
		double evaluate_number(const xpath_node& n) const;
		
	#ifndef PUGIXML_NO_STL
		// Evaluate expression as string value in the specified context; performs type conversion if necessary.
		// If PUGIXML_NO_EXCEPTIONS is not defined, throws std::bad_alloc on out of memory errors.
		string_t evaluate_string(const xpath_node& n) const;
	#endif
		
		// Evaluate expression as string value in the specified context; performs type conversion if necessary.
		// At most capacity characters are written to the destination buffer, full result size is returned (includes terminating zero).
		// If PUGIXML_NO_EXCEPTIONS is not defined, throws std::bad_alloc on out of memory errors.
		// If PUGIXML_NO_EXCEPTIONS is defined, returns empty  set instead.
		size_t evaluate_string(char_t* buffer, size_t capacity, const xpath_node& n) const;

		// Evaluate expression as node set in the specified context.
		// If PUGIXML_NO_EXCEPTIONS is not defined, throws xpath_exception on type mismatch and std::bad_alloc on out of memory errors.
		// If PUGIXML_NO_EXCEPTIONS is defined, returns empty node set instead.
		xpath_node_set evaluate_node_set(const xpath_node& n) const;

		// Evaluate expression as node set in the specified context.
		// Return first node in document order, or empty node if node set is empty.
		// If PUGIXML_NO_EXCEPTIONS is not defined, throws xpath_exception on type mismatch and std::bad_alloc on out of memory errors.
		// If PUGIXML_NO_EXCEPTIONS is defined, returns empty node instead.
		xpath_node evaluate_node(const xpath_node& n) const;

		// Get parsing result (used to get compilation errors in PUGIXML_NO_EXCEPTIONS mode)
		const xpath_parse_result& result() const;

		// Safe bool conversion operator
		operator unspecified_bool_type() const;

		// Borland C++ workaround
		bool operator!() const;
	};
	
	#ifndef PUGIXML_NO_EXCEPTIONS
	// XPath exception class
	class PUGIXML_CLASS xpath_exception: public std::exception
	{
	private:
		xpath_parse_result _result;

	public:
		// Construct exception from parse result
		explicit xpath_exception(const xpath_parse_result& result);

		// Get error message
		virtual const char* what() const throw();

		// Get parse result
		const xpath_parse_result& result() const;
	};
	#endif
	
	// XPath node class (either node or ::xml::attribute)
	class PUGIXML_CLASS xpath_node
	{
	private:
		node _node;
		::xml::attribute _attribute;
	
		typedef void (*unspecified_bool_type)(xpath_node***);

	public:
		// Default constructor; constructs empty XPath node
		xpath_node();
		
		// Construct XPath node from XML node/::xml::attribute
		xpath_node(const node& node);
		xpath_node(const ::xml::attribute& attribute, const node& parent);

		// Get node/::xml::attribute, if any
		node node() const;
		::xml::attribute attribute() const;
		
		// Get parent of contained node/::xml::attribute
		::xml::node parent() const;

		// Safe bool conversion operator
		operator unspecified_bool_type() const;
		
		// Borland C++ workaround
		bool operator!() const;

		// Comparison operators
		bool operator==(const xpath_node& n) const;
		bool operator!=(const xpath_node& n) const;
	};

#ifdef __BORLANDC__
	// Borland C++ workaround
	bool PUGIXML_FUNCTION operator&&(const xpath_node& lhs, bool rhs);
	bool PUGIXML_FUNCTION operator||(const xpath_node& lhs, bool rhs);
#endif

	// A fixed-size collection of XPath nodes
	class PUGIXML_CLASS xpath_node_set
	{
	public:
		// Collection type
		enum type_t
		{
			type_unsorted,			// Not ordered
			type_sorted,			// Sorted by document order (ascending)
			type_sorted_reverse		// Sorted by document order (descending)
		};
		
		// Constant iterator type
		typedef const xpath_node* const_iterator;

		// We define non-constant iterator to be the same as constant iterator so that various generic algorithms (i.e. boost foreach) work
		typedef const xpath_node* iterator;
	
		// Default constructor. Constructs empty set.
		xpath_node_set();

		// Constructs a set from iterator range; data is not checked for duplicates and is not sorted according to provided type, so be careful
		xpath_node_set(const_iterator begin, const_iterator end, type_t type = type_unsorted);

		// Destructor
		~xpath_node_set();
		
		// Copy constructor/assignment operator
		xpath_node_set(const xpath_node_set& ns);
		xpath_node_set& operator=(const xpath_node_set& ns);

		// Get collection type
		type_t type() const;
		
		// Get collection size
		size_t size() const;

		// Indexing operator
		const xpath_node& operator[](size_t index) const;
		
		// Collection iterators
		const_iterator begin() const;
		const_iterator end() const;

		// Sort the collection in ascending/descending order by document order
		void sort(bool reverse = false);
		
		// Get first node in the collection by document order
		xpath_node first() const;
		
		// Check if collection is empty
		bool empty() const;
	
	private:
		type_t _type;
		
		xpath_node _storage;
		
		xpath_node* _begin;
		xpath_node* _end;

		void _assign(const_iterator begin, const_iterator end);
	};
#endif

#ifndef PUGIXML_NO_STL
	// Convert wide string to UTF8
   inline string as_utf8(const wchar_t* str) { return ::str::international::unicode_to_utf8(str);  }
   inline string as_utf8(wstring & str)  { return ::str::international::unicode_to_utf8(str); }
	
	// Convert UTF8 to wide string
   inline wstring as_wide(const char* str) { return ::str::international::utf8_to_unicode(str); }
   inline string  as_wide(string & str)  { return ::str::international::utf8_to_unicode(str); }
#endif

	// Memory allocation function interface; returns pointer to allocated memory or NULL on failure
	typedef void* (*allocation_function)(size_t size);
	
	// Memory deallocation function interface
	typedef void (*deallocation_function)(void* ptr);

	// Override default memory management functions. All subsequent allocations/deallocations will be performed via supplied functions.
	void PUGIXML_FUNCTION set_memory_management_functions(allocation_function allocate, deallocation_function deallocate);
	
	// Get current memory management functions
	allocation_function PUGIXML_FUNCTION get_memory_allocation_function();
	deallocation_function PUGIXML_FUNCTION get_memory_deallocation_function();
}

//#if !defined(PUGIXML_NO_STL) && (defined(_MSC_VER) || defined(__ICC))
//namespace std
//{
//	// Workarounds for (non-standard) iterator category detection for older versions (MSVC7/IC8 and earlier)
//	std::bidirectional_iterator_tag PUGIXML_FUNCTION _Iter_cat(const xml::node_iterator&);
//   std::bidirectional_iterator_tag PUGIXML_FUNCTION _Iter_cat(const xml::attribute_iterator&);
//   std::bidirectional_iterator_tag PUGIXML_FUNCTION _Iter_cat(const xml::named_node_iterator&);
//}
//#endif

#if !defined(PUGIXML_NO_STL) && defined(__SUNPRO_CC)
namespace std
{
	// Workarounds for (non-standard) iterator category detection
	std::bidirectional_iterator_tag PUGIXML_FUNCTION __iterator_category(const pugi::node_iterator&);
	std::bidirectional_iterator_tag PUGIXML_FUNCTION __iterator_category(const pugi::attribute_iterator&);
	std::bidirectional_iterator_tag PUGIXML_FUNCTION __iterator_category(const pugi::named_node_iterator&);
}
#endif

#endif

/**
 * Copyright (c) 2006-2014 Arseny Kapoulkine
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */


namespace xml
{


   inline bool is_equal_value(const attribute & attr1,const attribute & attr2)
   {

      return attr1.get_value() == attr2.get_value();

   }


   inline bool matches(const attribute & attr1,const attribute & attr2)
   {

      return attr1.get_name() == attr2.get_name() && is_equal_value(attr1, attr2);

   }


   inline bool contains(const object_range<attribute_iterator> & attrs, const attribute & attr)
   {

      for(attribute_iterator i = attrs.begin(); i != attrs.end(); i++)
      {

         if(matches((*i), attr))         
         {

            return true;

         }

      }

      return false;

   }

   
   inline bool contains(const object_range<attribute_iterator> & attrs, const ::array < attribute > & attra)
   {
      
      for(index i = 0; i < attra.get_count(); i++)
      {

         if(!contains(attrs,attra[i]))
         {

            return false;

         }

      }

      return true;

   }


   inline bool node::set_value(const string & strValue)
   {

      return text().set(strValue);

   }


} // namespace xml





