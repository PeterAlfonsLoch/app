#pragma once

#include "x/x_charcategory.h"

/** Character information class.
    \par Basic features:
    - All Unicode information is generated into tables by scripts
      xcharsets.pl  and  xtables_gen.pl
      They are using UnicodeData.txt file and some codepage files, available
      from <a href="http://www.unicode.org/">http://www.unicode.org/</a>
    - Character class supports most Unicode character properties, except for
      Bidirectional char class, and Decomposition information.
      Most of these methods works like Java Character class methods.

    \par Todo:
    - retrieving of bidirectional class information,
    - retrieving of character decomposition mappings (and normalization
      process information),
    - character 'Digit', 'Decimal Digit' properties. You can retrieve
      only 'Number' value property from digit characters.
    - No explicit surrogate characters support. Surrogate pairs are treated as distinct characters.

    @ingroup unicode
*/
namespace gen
{
   namespace ch
   {
      CLASS_DECL_ca string to_lower_case(const char * pszUtf8Char);
      CLASS_DECL_ca string to_upper_case(const char * pszUtf8Char);
      CLASS_DECL_ca string to_title_case(const char * pszUtf8Char);

      CLASS_DECL_ca bool is_lower_case(const char * pszUtf8Char);
      CLASS_DECL_ca bool is_upper_case(const char * pszUtf8Char);
      CLASS_DECL_ca bool is_title_case(const char * pszUtf8Char);
      CLASS_DECL_ca bool is_letter(const char * pszUtf8Char);
      CLASS_DECL_ca bool is_letter_or_digit(const char * pszUtf8Char);
      CLASS_DECL_ca bool is_digit(const char * pszUtf8Char);
      CLASS_DECL_ca bool is_assigned(const char * pszUtf8Char);
      CLASS_DECL_ca bool is_space_char(const char * pszUtf8Char);
      CLASS_DECL_ca bool is_whitespace(const char * pszUtf8Char);
      CLASS_DECL_ca bool is_whitespace(const char * pszUtf8Char, const char * pszEnd);

      CLASS_DECL_ca bool is_number(const char * pszUtf8Char);
      CLASS_DECL_ca bool to_numeric_value(const char * pszUtf8Char, float *f);

      CLASS_DECL_ca string get_category_name(const char * pszUtf8Char);
      ECharCategory get_category(const char * pszUtf8Char);

      CLASS_DECL_ca int get_combining_class(const char * pszUtf8Char);
      CLASS_DECL_ca bool is_mirrored(const char * pszUtf8Char);

      /** @deprecated For debug purposes only. */
      CLASS_DECL_ca int size_of_tables();

      CLASS_DECL_ca  __int64 uni_index(const char * pszUtf8);
      CLASS_DECL_ca  __int64 uni_index(const char * pszUtf8, const char * pszEnd);

   }

} // namespace gen

/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is the Colorer Library.
 *
 * The Initial Developer of the Original Code is
 * Cail Lomecb <cail@nm.ru>.
 * Portions created by the Initial Developer are Copyright (C) 1999-2005
 * the Initial Developer. 
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
