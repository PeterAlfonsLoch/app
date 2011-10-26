// XMLite.h: interface for the XMLite class.
//
// XMLite : XML Lite Parser Library
// by bro ( Cho,Kyung Min: bro@shinbiro.com ) 2002-10-30
// Microsoft MVP (Visual C++) bro@msmvp.com
//
// History.
// 2002-10-29 : First Coded. Parsing XMLElelement and Attributes.
//              get xml parsed vsstring ( looks good )
// 2002-10-30 : Get Node Functions, error handling ( not completed )
// 2002-12-06 : Helper Funtion vsstring to long
// 2002-12-12 : Entity Helper Support
// 2003-04-08 : Close,
// 2003-07-23 : add property escape_value. (now no escape on default)
// 2003-10-24 : bugfix) attribute parsing <tag a='1' \r\n/> is now ok
// 2004-03-05 : add branch copy functions
// 2004-06-14 : add _tcseistr/_tcsenistr/_tcsenicmp functions
// 2004-06-14 : now support, XML Document and PI, Comment, CDATA node
// 2004-06-15 : add GetText()/ Find() functions
// 2004-06-15 : add force_parse : now can parse HTML (not-welformed xml)
//
//////////////////////////////////////////////////////////////////////

#pragma once

struct _tagXMLAttr;
typedef _tagXMLAttr XAttr, *LPXAttr;
typedef simple_array<LPXAttr> XAttrs;

struct _tagXMLNode;
typedef _tagXMLNode XNode, *LPXNode;
typedef simple_array<LPXNode> XNodes, *LPXNodes;

struct _tagXMLDocument;
typedef struct _tagXMLDocument XDoc, *LPXDoc;

// Entity Encode/Decode Support
typedef struct _tagXmlEntity
{
	char entity;					// entity ( & " ' < > )
	char ref[10];					// entity reference ( &amp; &quot; etc )
	int ref_len;					// entity reference length
}XENTITY,*LPXENTITY;

typedef struct _tagXMLEntitys : public simple_array<XENTITY>
{
	LPXENTITY GetEntity( int entity );
	LPXENTITY GetEntity( LPSTR entity );
	size_t GetEntityCount( LPCSTR str );
	size_t Ref2Entity( LPCSTR estr, LPSTR str, int strlen );
	int Entity2Ref( LPCSTR str, LPSTR estr, int estrlen );
	vsstring Ref2Entity( LPCSTR estr );
	vsstring Entity2Ref( LPCSTR str );

	_tagXMLEntitys(){};
	_tagXMLEntitys( LPXENTITY entities, int count );
}XENTITYS,*LPXENTITYS;
XENTITYS * xmllite_default_entities();
vsstring XRef2Entity( LPCSTR estr );
vsstring XEntity2Ref( LPCSTR str );

typedef enum
{
	PIE_PARSE_WELFORMED	= 0,
	PIE_ALONE_NOT_CLOSED,
	PIE_NOT_CLOSED,
	PIE_NOT_NESTED,
	PIE_ATTR_NO_VALUE
}PCODE;

// Parse info.
typedef struct _tagParseInfo
{
	bool		trim_value;			// [set] do trim when parse?
	bool		entity_value;		// [set] do convert from reference to entity? ( &lt; -> < )
	LPXENTITYS	entitys;			// [set] entity table for entity decode
	char		escape_value;		// [set] escape value (default '\\')
	bool		force_parse;		// [set] force parse even if xml is not welformed

	LPSTR		xml;				// [get] xml source
	bool		erorr_occur;		// [get] is occurance of error?
	LPSTR		error_pointer;		// [get] error position of xml source
	PCODE		error_code;			// [get] error code
	vsstring		error_string;		// [get] error vsstring

	LPXDoc		doc;
	_tagParseInfo() { trim_value = false; entity_value = true; force_parse = false; entitys = xmllite_default_entities(); xml = NULL; erorr_occur = false; error_pointer = NULL; error_code = PIE_PARSE_WELFORMED; escape_value = '\\'; }
}PARSEINFO,*LPPARSEINFO;
CLASS_DECL_____ PARSEINFO * xmllite_get_default_parse_info();

// display optional environment
typedef struct  _tagDispOption
{
	bool newline;			// newline when new tag
	bool reference_value;	// do convert from entity to reference ( < -> &lt; )
	char value_quotation_mark;	// val="" (default value quotation mark "
	LPXENTITYS	entitys;	// entity table for entity encode

	int tab_base;			// internal usage
	_tagDispOption() { newline = true; reference_value = true; entitys = xmllite_default_entities(); tab_base = 0; value_quotation_mark = '"'; }
}DISP_OPT, *LPDISP_OPT;
CLASS_DECL_____ extern  DISP_OPT  * poptDefault;

// XAttr : Attribute Implementation
typedef struct _tagXMLAttr
{
	vsstring name;
	vsstring	value;

	_tagXMLNode*	parent;

	vsstring GetXML( LPDISP_OPT opt = poptDefault );
}XAttr, *LPXAttr;

typedef enum
{
	XNODE_ELEMENT,				// general node '<element>...</element>' or <element/>
	XNODE_PI,					// <?xml version="1.0" ?>
	XNODE_COMMENT,				// <!-- comment -->
	XNODE_CDATA,				// <![CDATA[ cdata ]]>
	XNODE_DOC,					// internal virtual root
}NODE_TYPE;

#pragma warning(push)
#pragma warning(disable : 4251)

// XMLNode structure
typedef  struct CLASS_DECL_____ _tagXMLNode
{
	// name and value
	vsstring name;
	vsstring	value;

	// internal variables
	LPXNode	parent;		// parent node
	XNodes	childs;		// child node
	XAttrs	attrs;		// attributes
	NODE_TYPE type;		// node type
	LPXDoc	doc;		// document

	// Load/Save XML
	LPSTR	Load( LPCTSTR pszXml, LPPARSEINFO pi = xmllite_get_default_parse_info() );
	vsstring GetXML( LPDISP_OPT opt = poptDefault );
	vsstring GetText( LPDISP_OPT opt = poptDefault );

	// internal load functions
   index attr_index(LPXAttr pattr);
	LPSTR	LoadAttributes( LPCTSTR pszAttrs, LPPARSEINFO pi = xmllite_get_default_parse_info() );
	LPSTR	LoadAttributes( LPCTSTR pszAttrs, LPCTSTR pszEnd, LPPARSEINFO pi = xmllite_get_default_parse_info() );
	LPSTR	LoadProcessingInstrunction( LPCTSTR pszXml, LPPARSEINFO pi = xmllite_get_default_parse_info() );
	LPSTR	LoadComment( LPCSTR pszXml, LPPARSEINFO pi = xmllite_get_default_parse_info() );
	LPSTR	LoadCDATA( LPCSTR pszXml, LPPARSEINFO pi = xmllite_get_default_parse_info() );

	// in own attribute list
	LPXAttr	GetAttr( LPCTSTR attrname );
	LPCSTR	GetAttrValue( LPCTSTR attrname );
	XAttrs	GetAttrs( LPCTSTR name );

	// in one level child nodes
   index child_index(LPXNode pnode);
	LPXNode	GetChild( LPCTSTR name );
	LPCSTR	GetChildValue( LPCTSTR name );
	vsstring	GetChildText( LPCTSTR name, LPDISP_OPT opt = poptDefault );
	XNodes	GetChilds( LPCTSTR name );
	XNodes	GetChilds();

   LPXNode GetChildByAttr(const char * pszName, const char * pszAttrName, const char * pszAttrValue);
   index FindChildByAttr(const char * pszName, const char * pszAttrName, const char * pszAttrValue);

	LPXAttr GetChildAttr( LPCTSTR name, LPCTSTR attrname );
	LPCSTR GetChildAttrValue( LPCTSTR name, LPCTSTR attrname );



	// search node
	LPXNode	Find( LPCSTR name );

	// modify DOM
   size_t		GetChildCount();
	LPXNode GetChild(index ui);
	LPXNode CreateNode( LPCTSTR name = NULL, LPCTSTR value = NULL );
	LPXNode	AppendChild( LPCTSTR name = NULL, LPCTSTR value = NULL );
	LPXNode	AppendChild( LPXNode node );
	bool	RemoveChild( LPXNode node );
	LPXNode DetachChild( LPXNode node );

	// node/branch copy
	void	CopyNode( LPXNode node );
	void	CopyBranch( LPXNode branch );
	void	_CopyBranch( LPXNode node );
	LPXNode	AppendChildBranch( LPXNode node );

	// modify attribute
	LPXAttr GetAttr(index i );
	LPXAttr CreateAttr( LPCTSTR anem = NULL, LPCTSTR value = NULL );
	LPXAttr AppendAttr( LPCTSTR name = NULL, LPCTSTR value = NULL );
	LPXAttr	AppendAttr( LPXAttr attr );
	bool	RemoveAttr( LPXAttr attr );
	LPXAttr DetachAttr( LPXAttr attr );

	// operator overloads
	LPXNode operator [] ( int i ) { return GetChild(i); }
	XNode& operator = ( XNode& node ) { CopyBranch(&node); return *this; }

	_tagXMLNode();
	~_tagXMLNode();

	void Close();
}XNode, *LPXNode;

#pragma warning(pop)

// XMLDocument structure
typedef struct _tagXMLDocument : public XNode
{
	PARSEINFO	parse_info;

	_tagXMLDocument() { parent = NULL; doc = this; type = XNODE_DOC; }

	LPSTR	Load( LPCSTR pszXml, LPPARSEINFO pi = NULL );
	LPXNode	GetRoot();

}XDoc, *LPXDoc;

// Helper Funtion
inline long XStr2Int( LPCSTR str, long default_value = 0 )
{
	return ( str && *str ) ? atoi(str) : default_value;
}

inline bool XIsEmptyString( LPCSTR str )
{
	vsstring s(str);
	s.trim_left();
	s.trim_right();

	return s.length() == 0;
}
