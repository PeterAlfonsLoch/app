#pragma once

#include "aura/aura/aura.h"


#if defined(_CA2_HTML_LITE_DLL)
#define CLASS_DECL_HTML_LITE  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_HTML_LITE  CLASS_DECL_IMPORT
#endif



class lite_html_tag;
class lite_html_reader;



#include "html_lite_html_common.h"
#include "html_lite_html_attributes.h"
#include "html_lite_html_entity_resolver.h"
#include "html_lite_html_reader.h"
#include "html_lite_html_tag.h"



#include "axis/html_lite/html/html.h"


#include "html_lite_application_interface.h"










/*


PROJECT - HTML Reader Class Library

LiteHTMLAttributes.h - Defines LiteHTMLAttributes and
LiteHTMLElemAttr

Written By Gurmeet S. Kochar <gomzygotit@hotmail.com>
Copyright (ca) 2004.

This code may be used in compiled form in any way you desire
(including commercial use). The code may be redistributed
unmodified by any means PROVIDING it is not sold for profit
without the authors written consent, and providing that this
notice and the authors name and all copyright notices remains
intact. However, this file and the accompanying source code may
not be hosted on a website or bulletin board without the authors
written permission.

This file is provided "AS IS" with no expressed or implied warranty.
The author accepts no liability for any damage/loss of business that
this product may cause.

Although it is not necessary, but if you use this code in any of
your application (commercial or non-commercial), please INFORM me
so that I may know how useful this library is. This will encourage
me to keep updating it.


*/





