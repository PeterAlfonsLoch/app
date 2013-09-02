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
typedef array<LPXAttr> XAttrs;

struct _tagXMLNode;
typedef _tagXMLNode XNode, *LPXNode;
typedef array<LPXNode> XNodes, *LPXNodes;

struct _tagXMLDocument;
typedef struct _tagXMLDocument XDoc, *LPXDoc;

// Entity Encode/Decode Support
typedef struct _tagXmlEntity
{
	char entity;					// entity ( & " ' < > )
	char ref[10];					// entity reference ( &amp; &quot; etc )
	int32_t ref_len;					// entity reference length
}XENTITY,*LPXENTITY;

typedef struct _tagXMLEntitys : public array<XENTITY>
{
	LPXENTITY GetEntity( int32_t entity );
	LPXENTITY GetEntity( LPSTR entity );
	size_t GetEntityCount( LPCSTR str );
	size_t Ref2Entity( LPCSTR estr, LPSTR str, int32_t strlen );
	int32_t Entity2Ref( LPCSTR str, LPSTR estr, int32_t estrlen );
	vsstring Ref2Entity( LPCSTR estr );
	vsstring Entity2Ref( LPCSTR str );

	_tagXMLEntitys(){};
	_tagXMLEntitys( LPXENTITY entities, int32_t count );
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
CLASS_DECL_ca PARSEINFO * xmllite_get_default_parse_info();

// display optional environment
typedef struct  _tagDispOption
{
	bool newline;			// newline when new tag
	bool reference_value;	// do convert from entity to reference ( < -> &lt; )
	char value_quotation_mark;	// val="" (default value quotation mark "
	LPXENTITYS	entitys;	// entity table for entity encode

	int32_t tab_base;			// internal usage
	_tagDispOption() { newline = true; reference_value = true; entitys = xmllite_default_entities(); tab_base = 0; value_quotation_mark = '"'; }
}DISP_OPT, *LPDISP_OPT;
CLASS_DECL_ca extern  DISP_OPT  * poptDefault;

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
	XNODE_DOC					// internal virtual root
}NODE_TYPE;

#pragma warning(push)
#pragma warning(disable : 4251)

// XMLNode structure
typedef  struct CLASS_DECL_ca _tagXMLNode
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
	LPSTR	Load( LPCSTR pszXml, LPPARSEINFO pi = xmllite_get_default_parse_info() );
	vsstring GetXML( LPDISP_OPT opt = poptDefault );
	vsstring GetText( LPDISP_OPT opt = poptDefault );

	// internal load functions
   index attr_index(LPXAttr pattr);
	LPSTR	LoadAttributes( LPCSTR pszAttrs, LPPARSEINFO pi = xmllite_get_default_parse_info() );
	LPSTR	LoadAttributes( LPCSTR pszAttrs, LPCSTR pszEnd, LPPARSEINFO pi = xmllite_get_default_parse_info() );
	LPSTR	LoadProcessingInstrunction( LPCSTR pszXml, LPPARSEINFO pi = xmllite_get_default_parse_info() );
	LPSTR	LoadComment( LPCSTR pszXml, LPPARSEINFO pi = xmllite_get_default_parse_info() );
	LPSTR	LoadCDATA( LPCSTR pszXml, LPPARSEINFO pi = xmllite_get_default_parse_info() );

	// in own attribute list
	LPXAttr	GetAttr( LPCSTR attrname );
	LPCSTR	GetAttrValue( LPCSTR attrname );
	XAttrs	GetAttrs( LPCSTR name );

	// in one level child nodes
   index child_index(LPXNode pnode);
	LPXNode	GetChild( LPCSTR name );
	LPCSTR	GetChildValue( LPCSTR name );
	vsstring	GetChildText( LPCSTR name, LPDISP_OPT opt = poptDefault );
	XNodes	GetChilds( LPCSTR name );
	XNodes	GetChilds();

   LPXNode GetChildByAttr(const char * pszName, const char * pszAttrName, const char * pszAttrValue);
   index FindChildByAttr(const char * pszName, const char * pszAttrName, const char * pszAttrValue);

	LPXAttr GetChildAttr( LPCSTR name, LPCSTR attrname );
	LPCSTR GetChildAttrValue( LPCSTR name, LPCSTR attrname );



	// search node
	LPXNode	Find( LPCSTR name );

	// modify DOM
   size_t		GetChildCount();
	LPXNode GetChild(index ui);
	LPXNode CreateNode( LPCSTR name = NULL, LPCSTR value = NULL );
	LPXNode	AppendChild( LPCSTR name = NULL, LPCSTR value = NULL );
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
	LPXAttr CreateAttr( LPCSTR anem = NULL, LPCSTR value = NULL );
	LPXAttr AppendAttr( LPCSTR name = NULL, LPCSTR value = NULL );
	LPXAttr	AppendAttr( LPXAttr attr );
	bool	RemoveAttr( LPXAttr attr );
	LPXAttr DetachAttr( LPXAttr attr );

	// operator overloads
	LPXNode operator [] ( int32_t i ) { return GetChild(i); }
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
