#include "framework.h"

#undef _T
//#define _T(x) L##x
#define _T

static const CHAR chXMLTagOpen		= '<';
static const CHAR chXMLTagClose	= '>';
static const CHAR chXMLTagPre	= '/';
static const CHAR chXMLEscape = '\\';	// for value field escape

static const CHAR szXMLPIOpen[] = _T("<?");
static const CHAR szXMLPIClose[] = _T("?>");
static const CHAR szXMLCommentOpen[] = _T("<!--");
static const CHAR szXMLCommentClose[] = _T("-->");
static const CHAR szXMLCDATAOpen[] = _T("<![CDATA[");
static const CHAR szXMLCDATAClose[] = _T("]]>");

static const XENTITY x_EntityTable[] = {
		{ '&', _T("&amp;"), 5 } ,
		{ '\"', _T("&quot;"), 6 } ,
		{ '\'', _T("&apos;"), 6 } ,
		{ '<', _T("&lt;"), 4 } ,
		{ '>', _T("&gt;"), 4 }
	};

CLASS_DECL_ca PARSEINFO  * piDefault = NULL;
DISP_OPT * poptDefault;
XENTITYS * pentityDefault;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//========================================================
// Name   : _tcschrs
// Desc   : same with strpbrk
// Param  :
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPSTR _tcschrs( LPCSTR psz, LPCSTR pszchs )
{
	while( psz && *psz )
	{
		if( strchr_dup( pszchs, *psz ) )
			return (LPSTR)psz;
		psz++;
	}
	return NULL;
}

//========================================================
// Name   : _tcsskip
// Desc   : skip space
// Param  :
// Return : skiped vsstring
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPSTR _tcsskip( LPCSTR psz )
{
	//while( psz && *psz == ' ' && *psz == 13 && *psz == 10 ) psz++;
	while( psz && isspace_dup((BYTE) (*psz)) ) psz++;

	return (LPSTR)psz;
}

//========================================================
// Name   : _tcsechr
// Desc   : similar with strchr with escape process
// Param  : escape - will be escape character
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPSTR _tcsechr( LPCSTR psz, int32_t ch, int32_t escape )
{
	LPSTR pch = (LPSTR)psz;

	while( pch && *pch )
	{
		if( escape != 0 && *pch == escape )
			pch++;
		else
		if( *pch == ch )
			return (LPSTR)pch;
		pch++;
	}
	return pch;
}

//========================================================
// Name   : _tcselen
// Desc   : similar with strlen_dup with escape process
// Param  : escape - will be escape character
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
int32_t _tcselen( int32_t escape, LPSTR srt, LPSTR end = NULL )
{
	int32_t len = 0;
	LPSTR pch = srt;
	if( end==NULL ) end = (LPSTR)sizeof(long);
	LPSTR prev_escape = NULL;
	while( pch && *pch && pch<end )
	{
		if( escape != 0 && *pch == escape && prev_escape == NULL )
			prev_escape = pch;
		else
		{
			prev_escape = NULL;
			len++;
		}
		pch++;
	}
	return len;
}

//========================================================
// Name   : _tcsecpy
// Desc   : similar with _tcscpy with escape process
// Param  : escape - will be escape character
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
void _tcsecpy( LPSTR psz, int32_t escape, LPSTR srt, LPSTR end = NULL )
{
	LPSTR pch = srt;
	if( end==NULL ) end = (LPSTR)sizeof(long);
	LPSTR prev_escape = NULL;
	while( pch && *pch && pch<end )
	{
		if( escape != 0 && *pch == escape && prev_escape == NULL )
			prev_escape = pch;
		else
		{
			prev_escape = NULL;
			*psz++ = *pch;
		}

		pch++;
	}

	*psz = '\0';
}

//========================================================
// Name   : _tcsepbrk
// Desc   : similar with strpbrk with escape process
// Param  : escape - will be escape character
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPSTR _tcsepbrk( LPCSTR psz, LPCSTR chset, int32_t escape )
{
	LPSTR pch = (LPSTR)psz;
	LPSTR prev_escape = NULL;
	while( pch && *pch )
	{
		if( escape != 0 && *pch == escape && prev_escape == NULL )
			prev_escape = pch;
		else
		{
			prev_escape = NULL;
			if( strchr_dup( chset, *pch ) )
				return (LPSTR)pch;
		}
		pch++;
	}
	return pch;
}

//========================================================
// Name   : _tcsenicmp
// Desc   : similar with strnicmp with escape process
// Param  : escape - will be escape character
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
int32_t _tcsenicmp( LPCSTR psz, LPCSTR str, ::count len, int32_t escape )
{
	LPSTR pch = (LPSTR)psz;
	LPSTR prev_escape = NULL;
	LPSTR des = (LPSTR)str;
	int32_t i = 0;

	while( pch && *pch && i < len )
	{
		if( escape != 0 && *pch == escape && prev_escape == NULL )
			prev_escape = pch;
		else
		{
			prev_escape = NULL;
			if( to_lower(*pch) != to_lower(des[i]) )
				break;
			i++;
		}
		pch ++;
	}

	// find
	if( i == len )
		return 0;
	if( psz[i] > des[i] )
		return 1;
	return -1;
}

//========================================================
// Name   : _tcsenistr
// Desc   : similar with _tcsistr with escape process
// Param  : escape - will be escape character
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPSTR _tcsenistr( LPCSTR psz, LPCSTR str, ::count len, int32_t escape )
{
	LPSTR pch = (LPSTR)psz;
	LPSTR prev_escape = NULL;
//	LPSTR des = (LPSTR)str;
//	int32_t i = 0;

	while( pch && *pch )
	{
		if( escape != 0 && *pch == escape && prev_escape == NULL )
			prev_escape = pch;
		else
		{
			prev_escape = NULL;
			if( _tcsenicmp( pch, str, len, escape ) == 0 )
				return (LPSTR)pch;
		}
		pch++;
	}
	return pch;
}

//========================================================
// Name   : _tcseistr
// Desc   : similar with _tcsistr with escape process
// Param  : escape - will be escape character
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPSTR _tcseistr( LPCSTR psz, LPCSTR str, int32_t escape )
{
	size_t len = strlen_dup( str );
	return _tcsenistr( psz, str, len, escape );
}

//========================================================
// Name   : _SetString
// Desc   : put vsstring of (psz~end) on ps vsstring
// Param  : trim - will be trim?
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
void _SetString( LPSTR psz, LPSTR end, vsstring* ps, bool trim = FALSE, int32_t escape = 0 )
{
	//trim
	if( trim )
	{
		while( psz && psz < end && isspace_dup(*psz) ) psz++;
		while( (end-1) && psz < (end-1) && isspace_dup(*(end-1)) ) end--;
	}
	size_t len = end - psz;
	if( len <= 0 ) return;
	if( escape )
	{
		len = _tcselen( escape, psz, end );
		LPSTR pss = (LPSTR) _ca_alloc( len + 1);
		_tcsecpy( pss, escape, psz, end );
      *ps = pss;
      _ca_free(pss, 0);
	}
	else
	{
		LPSTR pss = (LPSTR) _ca_alloc( len + 1);
		memcpy_dup( pss, psz, len * sizeof(CHAR) );
		pss[len] = '\0';
      *ps = pss;
      _ca_free(pss, 0);
	}
}
_tagXMLNode::_tagXMLNode()
{
 { parent = NULL; doc = NULL; type = XNODE_ELEMENT; }
}

_tagXMLNode::~_tagXMLNode()
{
	Close();
}

void _tagXMLNode::Close()
{
   index ui;
	for(ui = 0 ; ui < childs.get_count(); ui++)
	{
		LPXNode p = childs[ui];
		if( p )
		{
			delete p; childs[ui] = NULL;
		}
	}
	childs.remove_all();

	for(ui = 0 ; ui < attrs.get_count(); ui++)
	{
		LPXAttr p = attrs[ui];
		if( p )
		{
			delete p; attrs[ui] = NULL;
		}
	}
	attrs.remove_all();
}

// attr1="value1" attr2='value2' attr3=value3 />
//                                            ^- return pointer
//========================================================
// Name   : LoadAttributes
// Desc   : loading attribute plain xml text
// Param  : pszAttrs - xml of attributes
//          pi = parser information
// Return : advanced vsstring pointer. (error return NULL)
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPSTR _tagXMLNode::LoadAttributes( LPCSTR pszAttrs , LPPARSEINFO pi /*= &piDefault*/)
{
	LPSTR xml = (LPSTR)pszAttrs;

   if(pi == NULL)
      pi = xmllite_get_default_parse_info();

	while( xml && *xml )
	{
		if( (xml = _tcsskip( xml )) )
		{
			// close tag
			if( *xml == chXMLTagClose || *xml == chXMLTagPre )
				// wel-formed tag
				return xml;

			// XML Attr Name
			CHAR* pEnd = strpbrk_dup( xml, " =" );
			if( pEnd == NULL )
			{
				// error
				if( pi->erorr_occur == false )
				{
					pi->erorr_occur = true;
					pi->error_pointer = xml;
					pi->error_code = PIE_ATTR_NO_VALUE;
					pi->error_string = "<";
               pi->error_string += name;
               pi->error_string += "> attribute has error ";
				}
				return NULL;
			}

			LPXAttr attr = new XAttr;
			attr->parent = this;

			// XML Attr Name
			_SetString( xml, pEnd, &attr->name );

			// add new attribute
			attrs.add( attr );
			xml = pEnd;

			// XML Attr Value
			if( (xml = _tcsskip( xml )) )
			{
				//if( xml = strchr( xml, '=' ) )
				if( *xml == '=' )
				{
					if( (xml = _tcsskip( ++xml )) )
					{
						// if " or '
						// or none quote
						int32_t quote = *xml;
						if( quote == '"' || quote == '\'' )
							pEnd = _tcsechr( ++xml, quote, chXMLEscape );
						else
						{
							//attr= value>
							// none quote mode
							//pEnd = _tcsechr( xml, ' ', '\\' );
							pEnd = _tcsepbrk( xml, _T(" >"), chXMLEscape );
						}

						bool trim = pi->trim_value;
						CHAR escape = pi->escape_value;
						//_SetString( xml, pEnd, &attr->value, trim, chXMLEscape );
						_SetString( xml, pEnd, &attr->value, trim, escape );
						xml = pEnd;
						// ATTRVALUE
						if( pi->entity_value && pi->entitys )
							attr->value = pi->entitys->Ref2Entity(attr->value);

						if( quote == '"' || quote == '\'' )
							xml++;
					}
				}
			}
		}
	}

	// not wel-formed tag
	return NULL;
}

// attr1="value1" attr2='value2' attr3=value3 />
//                                            ^- return pointer
//========================================================
// Name   : LoadAttributes
// Desc   : loading attribute plain xml text
// Param  : pszAttrs - xml of attributes
//          pszEnd - last vsstring
//          pi = parser information
// Return : advanced vsstring pointer. (error return NULL)
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2004-06-14
//========================================================
LPSTR _tagXMLNode::LoadAttributes( LPCSTR pszAttrs, LPCSTR pszEnd, LPPARSEINFO pi /*= &piDefault*/ )
{
	LPSTR xml = (LPSTR)pszAttrs;

   if(pi == NULL)
      pi = xmllite_get_default_parse_info();


	while( xml && *xml )
	{
		if( (xml = _tcsskip( xml )) )
		{
			// close tag
			if( xml >= pszEnd )
				// wel-formed tag
				return xml;

			// XML Attr Name
			CHAR* pEnd = strpbrk_dup( xml, " =" );
			if( pEnd == NULL )
			{
				// error
				if( pi->erorr_occur == false )
				{
					pi->erorr_occur = true;
					pi->error_pointer = xml;
					pi->error_code = PIE_ATTR_NO_VALUE;
					pi->error_string = "<" + name + "> attribute has error ";
				}
				return NULL;
			}

			LPXAttr attr = new XAttr;
			attr->parent = this;

			// XML Attr Name
			_SetString( xml, pEnd, &attr->name );

			// add new attribute
			attrs.add( attr );
			xml = pEnd;

			// XML Attr Value
			if( (xml = _tcsskip( xml )) )
			{
				//if( xml = strchr( xml, '=' ) )
				if( *xml == '=' )
				{
					if( (xml = _tcsskip( ++xml )) )
					{
						// if " or '
						// or none quote
						int32_t quote = *xml;
						if( quote == '"' || quote == '\'' )
							pEnd = _tcsechr( ++xml, quote, chXMLEscape );
						else
						{
							//attr= value>
							// none quote mode
							//pEnd = _tcsechr( xml, ' ', '\\' );
							pEnd = _tcsepbrk( xml, _T(" >"), chXMLEscape );
						}

						bool trim = pi->trim_value;
						CHAR escape = pi->escape_value;
						//_SetString( xml, pEnd, &attr->value, trim, chXMLEscape );
						_SetString( xml, pEnd, &attr->value, trim, escape );
						xml = pEnd;
						// ATTRVALUE
						if( pi->entity_value && pi->entitys )
							attr->value = pi->entitys->Ref2Entity(attr->value);

						if( quote == '"' || quote == '\'' )
							xml++;
					}
				}
			}
		}
	}

	// not wel-formed tag
	return NULL;
}

// <?xml version="1.0"?>
//                      ^- return pointer
//========================================================
// Name   : LoadProcessingInstrunction
// Desc   : loading processing instruction
// Param  : pszXml - PI vsstring
//          pi - parser information
// Return : advanced vsstring pointer. (error return NULL)
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2004-06-14
//========================================================
LPSTR _tagXMLNode::LoadProcessingInstrunction( LPCSTR pszXml, LPPARSEINFO pi /*= &piDefault*/ )
{

   if(pi == NULL)
      pi = xmllite_get_default_parse_info();

	// find the end of pi
	LPSTR end = _tcsenistr( pszXml, szXMLPIClose, sizeof(szXMLPIClose)-1, pi ? pi->escape_value : 0 );
	if( end == NULL || *end == '\0')
		return NULL;

	// process pi
	if( doc )
	{
		LPSTR xml = (LPSTR)pszXml;

		LPXNode node = new XNode;
		node->parent = this;
		node->doc = doc;
		node->type = XNODE_PI;

		xml += sizeof(szXMLPIOpen)-1;
		CHAR* pTagEnd = strpbrk_dup( xml, " ?>" );
		_SetString( xml, pTagEnd, &node->name );
		xml = pTagEnd;

		node->LoadAttributes( xml, end, pi );

		doc->childs.add( node );
	}

	end += sizeof(szXMLPIClose)-1;
	return end;
}

// <!-- comment -->
//                 ^- return pointer
//========================================================
// Name   : LoadComment
// Desc   : loading comment
// Param  : pszXml - comment vsstring
//          pi - parser information
// Return : advanced vsstring pointer. (error return NULL)
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2004-06-14
//========================================================
LPSTR _tagXMLNode::LoadComment( LPCSTR pszXml, LPPARSEINFO pi /*= &piDefault*/ )
{
   if(pi == NULL)
      pi = xmllite_get_default_parse_info();

	// find the end of comment
	LPSTR end = _tcsenistr( pszXml, szXMLCommentClose, sizeof(szXMLCommentClose)-1, pi ? pi->escape_value : 0 );
	if( end == NULL )
		return NULL;

	// process comment
	LPXNode par = parent;
	if( parent == NULL && doc )
		par = (LPXNode)&doc;
	if( par )
	{
		LPSTR xml = (LPSTR)pszXml;
		xml += sizeof(szXMLCommentOpen)-1;

		LPXNode node = new XNode;
		node->parent = this;
		node->doc = doc;
		node->type = XNODE_COMMENT;
		node->name = _T("#COMMENT");
		_SetString( xml, end, &node->value, FALSE );

		par->childs.add( node );
	}

	end += sizeof(szXMLCommentClose)-1;
	return end;
}

// <![CDATA[ cdata ]]>
//                    ^- return pointer
//========================================================
// Name   : LoadCDATA
// Desc   : loading CDATA
// Param  : pszXml - CDATA vsstring
//          pi - parser information
// Return : advanced vsstring pointer. (error return NULL)
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2004-06-14
//========================================================
LPSTR _tagXMLNode::LoadCDATA( LPCSTR pszXml, LPPARSEINFO pi /*= &piDefault*/ )
{
   if(pi == NULL)
      pi = xmllite_get_default_parse_info();

	// find the end of CDATA
	LPSTR end = _tcsenistr( pszXml, szXMLCDATAClose, sizeof(szXMLCDATAClose)-1, pi ? pi->escape_value : 0 );
	if( end == NULL )
		return NULL;

	// process CDATA
	LPXNode par = parent;
	if( parent == NULL && doc )
		par = (LPXNode)&doc;
	if( par )
	{
		LPSTR xml = (LPSTR)pszXml;
		xml += sizeof(szXMLCDATAOpen)-1;

		LPXNode node = new XNode;
		node->parent = this;
		node->doc = doc;
		node->type = XNODE_CDATA;
		node->name = _T("#CDATA");
		_SetString( xml, end, &node->value, FALSE );

		par->childs.add( node );
	}

	end += sizeof(szXMLCDATAClose)-1;
	return end;
}

//========================================================
// Name   : LoadOtherNodes
// Desc   : internal function for loading PI/CDATA/Comment
// Param  : node - current xml node
//          pbRet - error occur
//          pszXml - CDATA vsstring
//          pi - parser information
// Return : advanced vsstring pointer. (error return NULL)
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2004-06-14
//========================================================
LPSTR LoadOtherNodes( LPXNode node, bool* pbRet, LPCSTR pszXml, LPPARSEINFO pi /*= &piDefault*/ )
{
   if(pi == NULL)
      pi = xmllite_get_default_parse_info();

	LPSTR xml = (LPSTR)pszXml;
	bool do_other_type = true;
	*pbRet = false;

	while( xml && do_other_type )
	{
		do_other_type = false;

		xml = _tcsskip( xml );
		LPSTR prev = xml;
		// is PI( Processing Instruction ) Node?
		if( strnicmp_dup( xml, szXMLPIOpen, sizeof(szXMLPIOpen)-1 ) == 0 )
		{
			// processing instrunction parse
			// return pointer is next node of pi
			xml = node->LoadProcessingInstrunction( xml, pi );
			//if( xml == NULL )
			//	return NULL;
			// restart xml parse
		}

		if( xml != prev )
			do_other_type = true;
		xml = _tcsskip( xml );
		prev = xml;

		// is comment Node?
		if( strnicmp_dup( xml, szXMLCommentOpen, sizeof(szXMLCommentOpen)-1 ) == 0 )
		{
			// processing comment parse
			// return pointer is next node of comment
			xml = node->LoadComment( xml, pi );
			// comment node is terminal node
			if( node->parent && node->parent->type != XNODE_DOC
				&& xml != prev )
			{
				*pbRet = true;
				return xml;
			}
			// restart xml parse when this node is root doc node
		}

		if( xml != prev )
			do_other_type = true;

		xml = _tcsskip( xml );
		prev = xml;
		// is CDATA Node?
		if( strnicmp_dup( xml, szXMLCDATAOpen, sizeof(szXMLCDATAOpen)-1 ) == 0 )
		{
			// processing CDATA parse
			// return pointer is next node of CDATA
			xml = node->LoadCDATA( xml, pi );
			// CDATA node is terminal node
			if( node->parent && node->parent->type != XNODE_DOC
				&& xml != prev )
			{
				*pbRet = true;
				return xml;
			}
			// restart xml parse when this node is root doc node
		}

		if( xml != prev )
			do_other_type = true;
	}

	return xml;
}

// <TAG attr1="value1" attr2='value2' attr3=value3 >
// </TAG>
// or
// <TAG />
//        ^- return pointer
//========================================================
// Name   : Load
// Desc   : load xml plain text
// Param  : pszXml - plain xml text
//          pi = parser information
// Return : advanced vsstring pointer  (error return NULL)
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPSTR _tagXMLNode::Load( LPCSTR pszXml, LPPARSEINFO pi /*= &piDefault*/ )
{
   if(pi == NULL)
      pi = xmllite_get_default_parse_info();
	// Close it
	Close();

	LPSTR xml = (LPSTR)pszXml;

	xml = strchr_dup( xml, chXMLTagOpen );
	if( xml == NULL )
		return NULL;

	// Close Tag
	if( *(xml+1) == chXMLTagPre ) // </Close
		return xml;

	// Load Other Node before <Tag>(pi, comment, CDATA etc)
	bool bRet = false;
	LPSTR ret = NULL;
	ret = LoadOtherNodes( this, &bRet, xml, pi );
	if( ret != NULL )
		xml = ret;
	if( bRet )
		return xml;

	// XML Node Tag Name Open
	xml++;
	CHAR* pTagEnd = strpbrk_dup( xml, " />\t\r\n" );
	_SetString( xml, pTagEnd, &name );
	xml = pTagEnd;
	// Generate XML Attributte List
	if( (xml = LoadAttributes( xml, pi )) )
	{
		// alone tag <TAG ... />
		if( *xml == chXMLTagPre )
		{
			xml++;
			if( *xml == chXMLTagClose )
				// wel-formed tag
				return ++xml;
			else
			{
				// error: <TAG ... / >
				if( pi->erorr_occur == false )
				{
					pi->erorr_occur = true;
					pi->error_pointer = xml;
					pi->error_code = PIE_ALONE_NOT_CLOSED;
					pi->error_string = _T("Element must be closed.");
				}
				// not wel-formed tag
				return NULL;
			}
		}
		else
		// open/close tag <TAG ..> ... </TAG>
		//                        ^- current pointer
		{
			// if text value is not exist, then assign value
			//if( this->value.is_empty() || this->value == _T("") )
			if( XIsEmptyString( value ) )
			{
				// Text Value
				CHAR* pEnd = _tcsechr( ++xml, chXMLTagOpen, chXMLEscape );
				if( pEnd == NULL )
				{
					if( pi->erorr_occur == false )
					{
						pi->erorr_occur = true;
						pi->error_pointer = xml;
						pi->error_code = PIE_NOT_CLOSED;
   					pi->error_string = "'" + name + "' must be closed with </"+name+">";
					}
					// error cos not exist CloseTag </TAG>
					return NULL;
				}

				bool trim = pi->trim_value;
				CHAR escape = pi->escape_value;
				//_SetString( xml, pEnd, &value, trim, chXMLEscape );
				_SetString( xml, pEnd, &value, trim, escape );

				xml = pEnd;
				// TEXTVALUE reference
				if( pi->entity_value && pi->entitys )
					value = pi->entitys->Ref2Entity(value);
			}

			// generate child nodes
			while( xml && *xml )
			{
				LPXNode node = new XNode;
				node->parent = this;
				node->doc = doc;
				node->type = type;

				xml = node->Load( xml,pi );
				if( node->name.length() != 0 )
				{
					childs.add( node );

				}
				else
				{
					delete node;
				}

				// open/close tag <TAG ..> ... </TAG>
				//                             ^- current pointer
				// CloseTag case
				if( xml && *xml && *(xml+1) && *xml == chXMLTagOpen && *(xml+1) == chXMLTagPre )
				{
					// </Close>
					xml+=2; // C

					if( (xml = _tcsskip( xml )) )
					{
						vsstring closename;
						CHAR* pEnd = strpbrk_dup( xml, " >" );
						if( pEnd == NULL )
						{
							if( pi->erorr_occur == false )
							{
								pi->erorr_occur = true;
								pi->error_pointer = xml;
								pi->error_code = PIE_NOT_CLOSED;
								pi->error_string = "it must be closed with </" + name + ">";
							}
							// error
							return NULL;
						}
						_SetString( xml, pEnd, &closename );
						if( closename == this->name )
						{
							// wel-formed open/close
							xml = pEnd+1;
							// return '>' or ' ' after pointer
							return xml;
						}
						else
						{
							xml = pEnd+1;
							// 2004.6.15 - example <B> alone tag
							// now it can parse with attribute 'force_arse'
							if( pi->force_parse == false )
							{
								// not welformed open/close
								if( pi->erorr_occur == false )
								{
									pi->erorr_occur = true;
									pi->error_pointer = xml;
									pi->error_code = PIE_NOT_NESTED;
									pi->error_string = "'<" + name + "> ... </" + closename + ">' is not wel-formed.";
								}
								return NULL;
							}
						}
					}
				}
				else	// Alone child Tag Loaded
						// else ﾇﾘｾﾟﾇﾏｴﾂﾁ・ｸｻｾﾆｾﾟﾇﾏｴﾂﾁ・ﾀﾇｽﾉｰ｣ｴﾙ.
				{

					//if( xml && this->value.is_empty() && *xml !=chXMLTagOpen )
					if( xml && XIsEmptyString( value ) && *xml !=chXMLTagOpen )
					{
						// Text Value
						CHAR* pEnd = _tcsechr( xml, chXMLTagOpen, chXMLEscape );
						if( pEnd == NULL )
						{
							// error cos not exist CloseTag </TAG>
							if( pi->erorr_occur == false )
							{
								pi->erorr_occur = true;
								pi->error_pointer = xml;
								pi->error_code = PIE_NOT_CLOSED;
								pi->error_string = "it must be closed with </" + name + ">";
							}
							return NULL;
						}

						bool trim = pi->trim_value;
						CHAR escape = pi->escape_value;
						//_SetString( xml, pEnd, &value, trim, chXMLEscape );
						_SetString( xml, pEnd, &value, trim, escape );

						xml = pEnd;
						//TEXTVALUE
						if( pi->entity_value && pi->entitys )
							value = pi->entitys->Ref2Entity(value);
					}
				}
			}
		}
	}

	return xml;
}

// <?xml version='1.0'?>
// <TAG attr1="value1" attr2='value2' attr3=value3 >
// </TAG>
// or
// <TAG />
//        ^- return pointer
//========================================================
// Name   : Load
// Desc   : load xml plain text for xml document
// Param  : pszXml - plain xml text
//          pi = parser information
// Return : advanced vsstring pointer  (error return NULL)
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPSTR _tagXMLDocument::Load( LPCSTR pszXml, LPPARSEINFO pi /*= NULL*/ )
{
	LPXNode node = new XNode;
	node->parent = (LPXNode)this;
	node->type = XNODE_ELEMENT;
	node->doc = this;
	LPSTR end;

	if( pi == NULL )
		pi = &parse_info;

	if( (end = node->Load( pszXml, pi )) == NULL )
	{
		delete node;
		return NULL;
	}

	childs.add( node );

	// Load Other Node after </Tag>(pi, comment, CDATA etc)
	LPSTR ret;
	bool bRet = false;
	ret = LoadOtherNodes( node, &bRet, end, pi );
	if( ret != NULL )
		end = ret;

	return end;
}

LPXNode	_tagXMLDocument::GetRoot()
{
	for(int32_t i = 0; i < childs.get_count() ; i++)
	{
		LPXNode node = childs[i];
		if( node->type == XNODE_ELEMENT )
			return node;
	}
	return NULL;
}

//========================================================
// Name   : GetXML
// Desc   : convert plain xml text from parsed xml attirbute
// Param  :
// Return : converted plain vsstring
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
vsstring _tagXMLAttr::GetXML( LPDISP_OPT opt /*= poptDefault*/ )
{
   if(opt == NULL)
      opt = poptDefault;
//	std::ostringstream os;
//	//os << (LPCSTR)name << "='" << (LPCSTR)value << "' ";

//	os << (LPCSTR)name << L"=" << (CHAR)opt->value_quotation_mark
//		<< (LPCSTR)(opt->reference_value&&opt->entitys?opt->entitys->Entity2Ref(value):value)
//		<< (CHAR)opt->value_quotation_mark << L" ";
//	return os.str();
   vsstring wstr;

   wstr = name;
   wstr += "=";
   wstr += opt->value_quotation_mark;
   wstr += (opt->reference_value&&opt->entitys?opt->entitys->Entity2Ref(value):value);
   wstr += opt->value_quotation_mark;
   wstr += " ";

   return wstr;
}

//========================================================
// Name   : GetXML
// Desc   : convert plain xml text from parsed xml node
// Param  :
// Return : converted plain vsstring
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
vsstring _tagXMLNode::GetXML( LPDISP_OPT opt /*= poptDefault*/ )
{
      if(opt == NULL)
      opt = poptDefault;

	vsstring os;

	// tab
	if( opt && opt->newline )
	{
		if( opt && opt->newline )
			os += "\r\n";
		for( int32_t i = 0 ; i < opt->tab_base ; i++)
			os += '\t';
	}

	if( type == XNODE_DOC )
	{
		for(index ui = 0 ; ui < childs.get_count(); ui++ )
			os += (LPCSTR)childs[ui]->GetXML( opt );
		return os;
	}
	else
	if( type == XNODE_PI )
	{
		// <?TAG
		os += szXMLPIOpen + name;
		// <?TAG Attr1="Val1"
		if( attrs.get_count() > 0 ) os += ' ';
		for(index ui = 0 ; ui < attrs.get_count(); ui++ )
		{
			os += attrs[ui]->GetXML(opt);
		}
		//?>
		os += szXMLPIClose;
		return os;
	}
	else
	if( type == XNODE_COMMENT )
	{
		// <--comment
		os += szXMLCommentOpen + value;
		//-->
		os += szXMLCommentClose;
		return os;
	}
	else
	if( type == XNODE_CDATA )
	{
		// <--comment
		os += szXMLCDATAOpen + value;
		//-->
		os += szXMLCDATAClose;
		return os;
	}

	// <TAG
	os += '<' + name;

	// <TAG Attr1="Val1"
	if( attrs.get_count() > 0  ) os += ' ';
	for(index ui = 0 ; ui < attrs.get_count(); ui++ )
	{
		os += attrs[ui]->GetXML(opt);
	}

	if( childs.get_count() <= 0 && value.length() == 0 )
	{
		// <TAG Attr1="Val1"/> alone tag
		os += "/>";
	}
	else
	{
		// <TAG Attr1="Val1"> and get child
		os += ">";
		if( opt && opt->newline && childs.get_count() > 0 )
		{
			opt->tab_base++;
		}

		for(index ui = 0 ; ui < childs.get_count(); ui++ )
			os += childs[ui]->GetXML( opt );

		// Text Value
		if( value != _T("") )
		{
			if( opt && opt->newline && childs.get_count() > 0 )
			{
				if( opt && opt->newline )
					os += "\r\n";
				for( int32_t i = 0 ; i < opt->tab_base ; i++)
					os += '\t';
			}
			os += (opt->reference_value&&opt->entitys?opt->entitys->Entity2Ref(value):value);
		}

		// </TAG> CloseTag
		if( opt && opt->newline && childs.get_count() > 0 )
		{
			os += "\r\n";
			for( int32_t i = 0 ; i < opt->tab_base-1 ; i++)
				os += '\t';
		}
		os += "</" + name + '>';

		if( opt && opt->newline )
		{
			if( childs.get_count() > 0 )
				opt->tab_base--;
		}
	}

	return os;
}

//========================================================
// ﾇﾔｼ・: GetText
// ｼｳ  ｸ・: ｳ・・ﾇﾏｳｪｸｦ ﾅﾘｽｺﾆｮ ｹｮﾀﾚｿｭｷﾎ ｹﾝﾈｯ
// ﾀﾎ  ﾀﾚ :
// ｸｮﾅﾏｰｪ : ｺｯﾈｯｵﾈ ｹｮﾀﾚｿｭ
//--------------------------------------------------------
// ﾀﾛｼｺﾀﾚ   ﾀﾛｼｺﾀﾏ                 ﾀﾛｼｺﾀﾌﾀｯ
// ﾁｶｰ貉ﾎ   2004-06-15
//========================================================
vsstring _tagXMLNode::GetText( LPDISP_OPT opt /*= poptDefault*/ )
{
   if(opt == NULL)
      opt = poptDefault;

	vsstring os;

	if( type == XNODE_DOC )
	{
		for(index ui = 0 ; ui < childs.get_count(); ui++ )
			os += childs[ui]->GetText( opt );
	}
	else
	if( type == XNODE_PI )
	{
		// no text
	}
	else
	if( type == XNODE_COMMENT )
	{
		// no text
	}
	else
	if( type == XNODE_CDATA )
	{
		os += value;
	}
	else
	if( type == XNODE_ELEMENT )
	{
		if( childs.get_count() <= 0 && value.length() == 0 )
		{
			// no text
		}
		else
		{
			// childs text
			for(index ui = 0 ; ui < childs.get_count(); ui++ )
				os += childs[ui]->GetText();

			// Text Value
			os += (opt->reference_value&&opt->entitys?opt->entitys->Entity2Ref(value):value);
		}
	}

	return os;
}

//========================================================
// Name   : GetAttr
// Desc   : get attribute with attribute name
// Param  :
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPXAttr	_tagXMLNode::GetAttr( LPCSTR attrname )
{
	for(index ui = 0 ; ui < attrs.get_count(); ui++ )
	{
		LPXAttr attr = attrs[ui];
		if( attr )
		{
			if( attr->name == attrname )
				return attr;
		}
	}
	return NULL;
}

//========================================================
// Name   : GetAttrs
// Desc   : find attributes with attribute name, return its list
// Param  :
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
XAttrs _tagXMLNode::GetAttrs( LPCSTR name )
{
	XAttrs attrs;
	for(index ui = 0 ; ui < attrs.get_count(); ui++ )
	{
		LPXAttr attr = attrs[ui];
		if( attr )
		{
			if( attr->name == name )
				attrs.add( attr );
		}
	}
	return attrs;
}

//========================================================
// Name   : GetAttrValue
// Desc   : get attribute with attribute name, return its value
// Param  :
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPCSTR	_tagXMLNode::GetAttrValue( LPCSTR attrname )
{
	LPXAttr attr = GetAttr( attrname );
	return attr ? (LPCSTR)attr->value : NULL;
}

XNodes _tagXMLNode::GetChilds()
{
	return childs;
}

//========================================================
// Name   : GetChilds
// Desc   : Find childs with name and return childs list
// Param  :
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
XNodes _tagXMLNode::GetChilds( LPCSTR name )
{
	XNodes nodes;
	for(index ui = 0 ; ui < childs.get_count(); ui++ )
	{
		LPXNode node = childs[ui];
		if( node )
		{
			if( node->name == name )
				nodes.add( node );
		}
	}
	return nodes;
}

//========================================================
// Name   : GetChild
// Desc   : get child node with index
// Param  :
// Return : NULL return if no child.
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPXNode _tagXMLNode::GetChild(index ui)
{
	if(ui >= 0 && ui < childs.get_count() )
		return childs[ui];
	return NULL;
}

//========================================================
// Name   : GetChildCount
// Desc   : get child node count
// Param  :
// Return : 0 return if no child
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-12-26
//========================================================
size_t	_tagXMLNode::GetChildCount()
{
	return childs.get_count();
}

//========================================================
// Name   : GetChild
// Desc   : Find child with name and return child
// Param  :
// Return : NULL return if no child.
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPXNode	_tagXMLNode::GetChild( LPCSTR name )
{
	for(index ui = 0 ; ui < childs.get_count(); ui++ )
	{
		LPXNode node = childs[ui];
		if( node )
		{
			if( node->name == name )
				return node;
		}
	}
	return NULL;
}

//========================================================
// Name   : GetChildValue
// Desc   : Find child with name and return child's value
// Param  :
// Return : NULL return if no child.
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPCSTR	_tagXMLNode::GetChildValue( LPCSTR name )
{
	LPXNode node = GetChild( name );
	return (node != NULL)? (LPCSTR)node->value : NULL;
}

vsstring	_tagXMLNode::GetChildText( LPCSTR name, LPDISP_OPT opt /*= poptDefault*/ )
{
   if(opt == NULL)
      opt = poptDefault;

	LPXNode node = GetChild( name );
	return (node != NULL)? node->GetText(opt) : _T("");
}

LPXAttr _tagXMLNode::GetChildAttr( LPCSTR name, LPCSTR attrname )
{
	LPXNode node = GetChild(name);
	return node ? node->GetAttr(attrname) : NULL;
}

LPCSTR _tagXMLNode::GetChildAttrValue( LPCSTR name, LPCSTR attrname )
{
	LPXAttr attr = GetChildAttr( name, attrname );
	return attr ? (LPCSTR)attr->value : NULL;
}

//========================================================
// Name   : Find
// Desc   : find node with tag name from it's all childs
// Param  :
// Return : NULL return if no found node.
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPXNode	_tagXMLNode::Find( LPCSTR name )
{
	for(int32_t i = 0; i < childs.get_count(); i++)
	{
		LPXNode child = childs[i];
		if(child->name == name)
			return child;

		LPXNode find = child->Find( name );
		if( find != NULL )
			return find;
	}

	return NULL;
}


//========================================================
// Name   : AppendChild
// Desc   : add node
// Param  :
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPXNode	_tagXMLNode::AppendChild( LPCSTR name /*= NULL*/, LPCSTR value /*= NULL*/ )
{
	return AppendChild( CreateNode( name, value ) );
}

//========================================================
// Name   : AppendChild
// Desc   : add node
// Param  :
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPXNode _tagXMLNode::AppendChild( LPXNode node )
{
	node->parent = this;
	node->doc = doc;
	childs.add( node );
	return node;
}

index _tagXMLNode::child_index( LPXNode child )
{

	for(int32_t i = 0; i < childs.get_count() ; i++)
	{
		if(childs[i] == child)
			return i;
	}
	return -1;
}

//========================================================
// Name   : RemoveChild
// Desc   : detach node and delete object
// Param  :
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
bool _tagXMLNode::RemoveChild( LPXNode node )
{
	index i = child_index(node);
	if(i >= 0)
	{
		delete node;
      childs.remove_at(i);
		return true;
	}
	return false;
}

//========================================================
// Name   : GetAttr
// Desc   : get attribute with index in attribute list
// Param  :
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPXAttr _tagXMLNode::GetAttr(index ui)
{
	if(ui >= 0 && ui < attrs.get_count() )
		return attrs[ui];
	return NULL;
}

//========================================================
// Name   : GetAttrIterator
// Desc   : get attribute iterator
// Param  :
// Return : std::vector<LPXAttr>::iterator
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
index _tagXMLNode::attr_index( LPXAttr attr )
{

	for(int32_t i = 0; i < attrs.get_count() ; i++)
	{
		if(attrs[i] == attr)
			return i;
	}
	return -1;
}

//========================================================
// Name   : AppendAttr
// Desc   : add attribute
// Param  :
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPXAttr _tagXMLNode::AppendAttr( LPXAttr attr )
{
	attr->parent = this;
	attrs.add( attr );
	return attr;
}

//========================================================
// Name   : RemoveAttr
// Desc   : detach attribute and delete object
// Param  :
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
bool _tagXMLNode::RemoveAttr( LPXAttr attr )
{
	index i = attr_index( attr );
	if(i >= 0)
	{
		delete attr;
		attrs.remove_at(i);
		return true;
	}
	return false;
}

//========================================================
// Name   : CreateNode
// Desc   : Create node object and return it
// Param  :
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPXNode _tagXMLNode::CreateNode( LPCSTR name /*= NULL*/, LPCSTR value /*= NULL*/ )
{
	LPXNode node = new XNode;
   if(name != NULL)
   {
	   node->name = name;
   }
   if(value != NULL)
   {
	   node->value = value;
   }
	return node;
}

//========================================================
// Name   : CreateAttr
// Desc   : create Attribute object and return it
// Param  :
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPXAttr _tagXMLNode::CreateAttr( LPCSTR name /*= NULL*/, LPCSTR value /*= NULL*/ )
{
	LPXAttr attr = new XAttr;
	attr->name = name;
	attr->value = value;
	return attr;
}

//========================================================
// Name   : AppendAttr
// Desc   : add attribute
// Param  :
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPXAttr _tagXMLNode::AppendAttr( LPCSTR name /*= NULL*/, LPCSTR value /*= NULL*/ )
{
	return AppendAttr( CreateAttr( name, value ) );
}

//========================================================
// Name   : DetachChild
// Desc   : no delete object, just detach in list
// Param  :
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPXNode _tagXMLNode::DetachChild( LPXNode node )
{
	index i = child_index( node );
	if(i >= 0)
	{
		childs.remove_at(i);
		return node;
	}
	return NULL;
}

//========================================================
// Name   : DetachAttr
// Desc   : no delete object, just detach in list
// Param  :
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPXAttr _tagXMLNode::DetachAttr( LPXAttr attr )
{
	index i = attr_index( attr );
	if(i >= 0)
	{
		attrs.remove_at( i );
		return attr;
	}
	return NULL;
}

//========================================================
// Name   : CopyNode
// Desc   : copy current level node with own attributes
// Param  :
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
void _tagXMLNode::CopyNode( LPXNode node )
{
	Close();

	doc = node->doc;
	parent = node->parent;
	name = node->name;
	value = node->value;
	type = node->type;

	// copy attributes
	for(index ui = 0 ; ui < node->attrs.get_count(); ui++)
	{
		LPXAttr attr = node->attrs[ui];
		if( attr )
         AppendAttr( attr->name, attr->value );
	}
}

//========================================================
// Name   : _CopyBranch
// Desc   : recursive internal copy branch
// Param  :
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
void _tagXMLNode::_CopyBranch( LPXNode node )
{
	CopyNode( node );

	for(index ui = 0 ; ui < node->childs.get_count(); ui++)
	{
		LPXNode child = node->childs[ui];
		if( child )
		{
			LPXNode mychild = new XNode;
			mychild->CopyNode( child );
			AppendChild( mychild );

			mychild->_CopyBranch( child );
		}
	}
}

//========================================================
// Name   : AppendChildBranch
// Desc   : add child branch ( deep-copy )
// Param  :
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
LPXNode	_tagXMLNode::AppendChildBranch( LPXNode node )
{
	LPXNode child = new XNode;
	child->CopyBranch( node );

	return AppendChild( child );
}

//========================================================
// Name   : CopyBranch
// Desc   : copy branch ( deep-copy )
// Param  :
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
void _tagXMLNode::CopyBranch( LPXNode branch )
{
	Close();

	_CopyBranch( branch );
}


_tagXMLEntitys::_tagXMLEntitys( LPXENTITY entities, int32_t count )
{
	for( int32_t i = 0; i < count; i++)
		add( entities[i] );
}

LPXENTITY _tagXMLEntitys::GetEntity( int32_t entity )
{
	for(index ui = 0 ; ui < this->get_count(); ui ++ )
	{
		if( this->element_at(ui).entity == entity )
			return LPXENTITY(&this->element_at(ui));
	}
	return NULL;
}

LPXENTITY _tagXMLEntitys::GetEntity( LPSTR entity )
{
	for(index ui = 0 ; ui < this->get_count(); ui++ )
	{
		LPSTR ref = (LPSTR)this->element_at(ui).ref;
		LPSTR ps = entity;
		while( ref && *ref )
			if( *ref++ != *ps++ )
				break;
		if( ref && !*ref )	// found!
			return LPXENTITY(&this->element_at(ui));
	}
	return NULL;
}

size_t _tagXMLEntitys::GetEntityCount( LPCSTR str )
{
	size_t nCount = 0;
	LPSTR ps = (LPSTR)str;
	while( ps && *ps )
		if( GetEntity( *ps++ ) ) nCount ++;
	return nCount;
}

size_t _tagXMLEntitys::Ref2Entity( LPCSTR estr, LPSTR str, int32_t strlen_dup )
{
	LPSTR pes = (LPSTR)estr;
	LPSTR ps = str;
	LPSTR ps_end = ps+strlen_dup;
	while( pes && *pes && ps < ps_end )
	{
		LPXENTITY ent = GetEntity( pes );
		if( ent )
		{
			// copy entity meanning char
			*ps = ent->entity;
			pes += ent->ref_len;
		}
		else
			*ps = *pes++;	// default character copy
		ps++;
	}
	*ps = '\0';

	// total copied characters
	return ps-str;
}

int32_t _tagXMLEntitys::Entity2Ref( LPCSTR str, LPSTR estr, int32_t estrlen )
{
	LPSTR ps = (LPSTR)str;
	LPSTR pes = (LPSTR)estr;
	LPSTR pes_end = pes+estrlen;
	while( ps && *ps && pes < pes_end )
	{
		LPXENTITY ent = GetEntity( *ps );
		if( ent )
		{
			// copy entity vsstring
			LPSTR ref = (LPSTR)ent->ref;
			while( ref && *ref )
				*pes++ = *ref++;
		}
		else
			*pes++ = *ps;	// default character copy
		ps++;
	}
	*pes = '\0';

	// total copied characters
	return (int32_t) (pes-estr);
}

vsstring _tagXMLEntitys::Ref2Entity( LPCSTR estr )
{
	
   vsstring es;

	if( estr )
	{
      
      ::count len = strlen_dup(estr);

		LPSTR esbuf = (LPSTR) _ca_alloc(len+1);

		if( esbuf )
			Ref2Entity( estr, esbuf, (int32_t) len );

      es = esbuf;

      _ca_free(esbuf, 0);

	}
	
   return es;

}

vsstring _tagXMLEntitys::Entity2Ref( LPCSTR str )
{
	
   vsstring s;

	if( str )
	{
		
      ::count nEntityCount = GetEntityCount(str);

		if( nEntityCount == 0 )
			return vsstring(str);

		::count len = strlen_dup(str) + nEntityCount*10 ;

		LPSTR sbuf = (LPSTR) _ca_alloc(len+1 );

		if( sbuf )
			Entity2Ref( str, sbuf, (int32_t) len );

      s = sbuf;

      _ca_free(sbuf, 0);

	}

	return s;

}

vsstring XRef2Entity( LPCSTR estr )
{
	return xmllite_default_entities()->Ref2Entity( estr );
}

vsstring XEntity2Ref( LPCSTR str )
{
	return xmllite_default_entities()->Entity2Ref( str );
}

index XNode::FindChildByAttr(const char * pszName, const char * pszAttrName, const char * pszAttrValue)
{
   for(index ui = 0; ui < childs.get_count(); ui++)
   {
      if(childs[ui]->name == pszName)
      {
         if(childs[ui]->GetAttr(pszAttrName) != NULL)
         {
            if(stricmp_dup(childs[ui]->GetAttrValue(pszAttrName), pszAttrValue) == 0)
            {
               return ui;
            }
         }
      }
   }
   // 0xffffffff
   return -1;
}


LPXNode XNode::GetChildByAttr(const char * pszName, const char * pszAttrName, const char * pszAttrValue)
{
   index ui = FindChildByAttr(pszName, pszAttrName, pszAttrValue);
   if(ui == ((index) -1))
   {
      return NULL;
   }
   else
   {
      return childs[ui];
   }
}


PARSEINFO * xmllite_get_default_parse_info()
{
   if(piDefault != NULL)
      return piDefault;
   piDefault = new PARSEINFO;
   return piDefault;
}

XENTITYS * xmllite_default_entities()
{
   if(pentityDefault != NULL)
      return pentityDefault;
   pentityDefault = new XENTITYS((LPXENTITY)x_EntityTable, sizeof(x_EntityTable)/sizeof(x_EntityTable[0]));
   return pentityDefault;
}
