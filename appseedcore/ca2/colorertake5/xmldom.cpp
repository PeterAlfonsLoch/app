
#include<stdio.h>

#include<xml/xmldom.h>
#include<unicode/UnicodeTools.h>

Document *DocumentBuilder::parse(input_source *is, const char *codepage)
{
  const byte *bytes = is->openStream();
  int GetLength = is->GetLength();

  DefaultEntityResolver der(is);
  EntityResolver *old_er = er;
  Document *_doc = null;

  er = &der;
  try{
    _doc = parse(bytes, GetLength, codepage);
  }catch(ParseException &e){
    er = old_er;
    is->closeStream();
    throw e;
  }
  er = old_er;
  is->closeStream();
  return _doc;
}

Document *DocumentBuilder::parse(const byte *bytes, int GetLength, const char *codepage)
{
  entitiesHash.clear();
  extEntitiesHash.clear();

  entitiesHash.put(&string("amp"), new string("&"));
  entitiesHash.put(&string("lt"), new string("<"));
  entitiesHash.put(&string("gt"), new string(">"));
  entitiesHash.put(&string("quot"), new string("\""));
  entitiesHash.put(&string("apos"), new string("\'"));

  if (GetLength == 0){
    throw ParseException(string("Empty document"), 0, 0);
  }

  doc = newDocument();
  doc->line = 0;
  doc->pos = 0;

  ppos = opos = 0;
  src = string(bytes, GetLength, Encodings::getEncodingIndex(codepage));
  src_length = src.GetLength();
  src_overflow = null;
  if (src[0] == Encodings::ENC_UTF16_BOM){
    ppos++;
  }

  try{
    consumeDocument();
  }catch(ParseException &e){
    free(doc);
    throw ParseException(*e.getMessage(), doc->line, doc->pos);
  }

  const string* st;
  for (st = entitiesHash.enumerate(); st != null; st = entitiesHash.next()){
    delete st;
  }
  for (st = extEntitiesHash.enumerate(); st != null; st = extEntitiesHash.next()){
    delete st;
  }

  return doc;

}

void DocumentBuilder::consumeDocument(){
  consumeXmlDecl();
  consumeMisc(doc);
  consumeDTD();
  consumeMisc(doc);
  consumeElement(doc);
  consumeMisc(doc);
  if (peek() != -1){
    throw ParseException(string("Extra markup after the root element"));
  }
}

void DocumentBuilder::consumeXmlDecl(){
  wchar_t c1 = peek(0);
  wchar_t c2 = peek(1);
  if (c1 != '<' || c2 != '?') return;

  consume("<?xml", 5);
  consumeSpaces(1);

  consume("version", 7);
  consumeSpaces();
  consume("=", 1);
  consumeSpaces();
  delete consumeQoutedValue();

  consumeSpaces();

  if (peek() == 'e'){
    consume("encoding", 8);
    consumeSpaces();
    consume("=", 1);
    consumeSpaces();
    delete consumeQoutedValue();
  }

  consumeSpaces();

  if (peek() == 's'){
    consume("standalone", 10);
    consumeSpaces();
    consume("=", 1);
    consumeSpaces();
    delete consumeQoutedValue();
  }

  consumeSpaces();
  consume("?>", 2);
}

void DocumentBuilder::consumeDTD(){
  wchar_t c1 = peek(0);
  wchar_t c2 = peek(1);
  if (c1 != '<' || c2 != '!') return;

  consume("<!DOCTYPE", 9);
  consumeSpaces(1);
  delete consumeNCName();

  consumeSpaces();
  if (peek() == 'S'){
    consume("SYSTEM", 6);
    consumeSpaces(1);
    delete consumeQoutedValue();
  }else if (peek() == 'P'){
    consume("PUBLIC", 6);
    consumeSpaces(1);
    delete consumeQoutedValue();
    consumeSpaces(1);
    delete consumeQoutedValue();
  }
  consumeSpaces();

  //markup decl
  if (peek() == '['){
    consume("[", 1);

    while(peek() != ']'){
      if (peek(0) == '<' && peek(1) == '!' && peek(2) == 'E'){
        consume("<!ENTITY", 8);
        consumeSpaces(1);
        string *entityName = consumeNCName();
        consumeSpaces(1);
        string *entityValue = null;
        string *extEntityValue = null;
        if (peek() == 'S'){
          consume("SYSTEM", 6);
          consumeSpaces(1);
          extEntityValue = consumeQoutedValue();
        }else if (peek() == 'P'){
          consume("PUBLIC", 6);
          consumeSpaces(1);
          delete consumeQoutedValue();
          consumeSpaces(1);
          extEntityValue = consumeQoutedValue();
        }else{
          entityValue = consumeQoutedValue();
        }
        if (entityValue != null){
          entitiesHash.put(entityName, entityValue);
        }
        if (extEntityValue != null){
          extEntitiesHash.put(entityName, extEntityValue);
        }
        delete entityName;

      }else if (isComment()){
        consumeComment(null);
      }
      get();
    }

    consume("]", 1);
    consumeSpaces();
  }


  consume(">", 1);

}

bool DocumentBuilder::isElement(){
  return (peek(0) == '<' && (Character::isLetter(peek(1)) ||
                             peek(1) == '_' || peek(1) == ':'));
}

void DocumentBuilder::consumeElement(xml::node *root){

  consume("<", 1);
  string *name = consumeName();
  xml::node *el = doc->createElement(name);
  root->appendChild(el);

  if (peek(0) == '/' && peek(1) == '>' || peek(0) == '>'){
    // no attributes
  }else{
    consumeSpaces(1);
    while(!(peek(0) == '/' && peek(1) == '>' || peek(0) == '>')){
      consumeSpaces();
      string *aname = consumeName();
      consumeSpaces();
      consume("=", 1);
      consumeSpaces();
      string *aval = consumeAttributeValue();
      consumeSpaces();
      el->setAttribute(aname, aval);
    }
  }

  if (peek(0) == '/' && peek(1) == '>'){
    consume("/>", 1);
  }else{
    consume(">", 1);

    consumeContent(el);

    consume("</", 2);
    consume(*name);
    consumeSpaces();
    consume(">", 1);
  }
}

void DocumentBuilder::consumeContent(xml::node *root){
  while(peek() != -1){
    consumeText(root);
    if (isElement()){
      consumeElement(root);
      continue;
    }
    if (isComment()){
      consumeComment(root);
      continue;
    }
    if (isCDataSection()){
      consumeCDataSection(root);
      continue;
    }
    if(isPI()){
      consumePI(root);
      continue;
    }
    if (isCharRef()){
      StringBuffer *sb = new StringBuffer(2);
      sb->append(consumeCharRef());
      appendToLastTextNode(root, sb);
      continue;
    }
    if (isEntityRef()){
      string *entext = consumeEntityRef(true);
      appendToLastTextNode(root, entext);
      continue;
    }
    if (peek(0) == '<') break;
  };
}

void DocumentBuilder::appendToLastTextNode(xml::node *root, string *stext){
  if (stext == null) return;
  xml::node *last = root->getLastChild();
  Text *text = null;
  if (last == null || last->getNodeType() != xml::node::TEXT_NODE){
    root->appendChild(doc->createTextNode(stext));
  }else{
    StringBuffer *sb = (StringBuffer*)((Text*)last)->getData();
    sb->append(stext);
    delete stext;
  }
}

bool DocumentBuilder::isCDataSection(){
  return (peek(0) == '<' && peek(1) == '!' && peek(2) == '[');
}

void DocumentBuilder::consumeCDataSection(xml::node *root){
  StringBuffer *sb = new StringBuffer();
  consume("<![CDATA[", 9);
  while(peek(0) != ']' || peek(1) != ']' || peek(2) != '>'){
    if (peek(0) == -1){
      get();
    }
    sb->append(get());
  }
  appendToLastTextNode(root, sb);
  consume("]]>", 3);
}

void DocumentBuilder::consumeText(xml::node *root){
  StringBuffer *sb = new StringBuffer(40);
  bool solews = true;
  while(true){
    int c = peek();
    if (c == -1 || c == '<' || c == '&'){
      break;
    }
    get();
    sb->append(c);
    if (isIgnoringElementContentWhitespace() && solews && !Character::isWhitespace(c)){
      solews = false;
    }
  };
  if (isIgnoringElementContentWhitespace() && solews){
    delete sb;
  }else{
    appendToLastTextNode(root, sb);
  };
}

bool DocumentBuilder::isCharRef(){
  return (peek(0) == '&' && peek(1) == '#');
}

wchar_t DocumentBuilder::consumeCharRef(){
  if (!(peek(0) == '&' && peek(1) == '#')){
    throw ParseException(string("&# syntax of Character Reference is required"));
  };
  consume("&#", 2);
  StringBuffer *sb = new StringBuffer("#");
  while(peek() != ';'){
    sb->append(get());
  }
  get();

  int c = -1;
  bool b = getXMLNumber(*sb, &c);
  delete sb;
  if (!b || c > 0xFFFF || c < 0){
    throw ParseException(string("Invalid Character Reference numeric value"));
  }
  return (wchar_t)c;
}

bool DocumentBuilder::isEntityRef(){
  return (peek(0) == '&' && peek(1) != '#');
}

string *DocumentBuilder::consumeEntityRef(bool useExtEnt){
  consume("&", 1);
  StringBuffer *sb = new StringBuffer(10);
  while(peek() != ';'){
    sb->append(get());
  }
  get();

  const string *ent = entitiesHash.get(sb);
  const string *extEnt = null;
  if (useExtEnt){
    extEnt = extEntitiesHash.get(sb);
  };
  delete sb;

  if (ent == null && extEnt == null){
    throw ParseException(string("Undefined Entity Reference"));
  }
  if (ent != null){
    return new StringBuffer(ent);
  }
  if (extEnt != null){
    if (er == null) return null;
    input_source *is = er->resolveEntity(null, extEnt);
    const byte *bytes = is->openStream();
    int GetLength = is->GetLength();
    src_overflow = new string(string(bytes, GetLength));
    delete is;
    return null;
  }
  return null;
}

void DocumentBuilder::consumeSpaces(int mins){
  while(Character::isWhitespace(peek())){
    get();
    mins--;
  }
  if (mins > 0){
    throw ParseException(string("Space is required"));
  }
}

string *DocumentBuilder::consumeAttributeValue(){
  wchar_t qc = get();
  if (qc != '"' && qc != '\''){
    throw ParseException(string("Qoute character is required here"));
  }
  StringBuffer *sb = new StringBuffer();
  while(true){
    if (isCharRef()){
      sb->append(consumeCharRef());
      continue;
    }
    if (isEntityRef()){
      string *entext = consumeEntityRef(false);
      if (entext){
        sb->append(entext);
        delete entext;
      }
      continue;
    }
    wchar_t qc2 = peek();
    if (qc2 == -1){
      delete sb;
    }
    get();
    if (qc2 == qc) return sb;
    sb->append(qc2);
  }
}

string *DocumentBuilder::consumeQoutedValue(){
  wchar_t qc = get();
  if (qc != '"' && qc != '\''){
    throw ParseException(string("Qoute character is required here"));
  }
  StringBuffer *sb = new StringBuffer();
  while(true){
    wchar_t qc2 = peek();
    if (qc2 == -1){
      delete sb;
    }
    get();
    if (qc2 == qc) return sb;
    sb->append(qc2);
  }
}

string *DocumentBuilder::consumeName(){
  StringBuffer *sb = new StringBuffer(10);
  bool start = true;
  while(true){
    int c = peek();
    // first char
    if ((start && !Character::isLetter(c) && c != '_' && c != ':') || c == -1){
      delete sb;
      throw ParseException(string("Name is required here"));
    }
    start = false;
    if (!Character::isLetterOrDigit(c) &&
         c != '_' && c != ':' && c != '.' && c != '-'){
      break;
    }
    get();
    sb->append(c);
  }
  return sb;
}

string *DocumentBuilder::consumeNCName(){
  StringBuffer *sb = new StringBuffer(10);
  bool start = true;
  while(true){
    int c = peek();
    // first char
    if ((start && !Character::isLetter(c)) || c == -1){
      delete sb;
      throw ParseException(string("NCName required here"));
    }
    start = false;
    if (!Character::isLetterOrDigit(c) && c != '_' && c != '-'){
      break;
    }
    get();
    sb->append(c);
  }
  return sb;
}

bool DocumentBuilder::isPI(){
  return (peek(0) == '<' && peek(1) == '?');
}

void DocumentBuilder::consumePI(xml::node *root){
  StringBuffer *sb = sb = new StringBuffer(40);
  consume("<?", 2);
  string * target = consumeNCName();
  consumeSpaces(1);
  while(peek(0) != '?' || peek(1) != '>'){
    if (peek(0) == -1){
      delete sb;
      get();
    }
    sb->append(get());
  }
  consume("?>", 2);
  root->appendChild(doc->createProcessingInstruction(target, sb));
}

bool DocumentBuilder::isComment(){
  return (peek(0) == '<' && peek(1) == '!' && peek(2) == '-');
}

void DocumentBuilder::consumeComment(xml::node *root){
  StringBuffer *sb = null;
  if (root != null && !isIgnoringComments()){
    sb = new StringBuffer();
  }
  consume("<!--", 4);
  while(peek(0) != '-' || peek(1) != '-' || peek(2) != '>'){
    if (peek(0) == -1){
      delete sb;
      get();
    }
    if (root && !isIgnoringComments()){
      sb->append(get());
    }else{
      get();
    }
  }
  consume("-->", 3);
  if (root != null && !isIgnoringComments()){
    root->appendChild(doc->createComment(sb));
  }
}

void DocumentBuilder::consumeMisc(xml::node *root){
  consumeSpaces();
  bool hasTokens = true;
  while(hasTokens){
    if(isComment()){
      consumeComment(root);
      consumeSpaces();
    }else if(isPI()){
      consumePI(root);
      consumeSpaces();
    }else{
      hasTokens = false;
    }
  }
}

void DocumentBuilder::consume(string &s){
  int idx;
  for(idx = 0; idx < s.GetLength() && peek() == s[idx]; idx++){
    get();
  }
  if (idx < s.GetLength()){
    throw ParseException(StringBuffer("Invalid sequence. waiting for '")+s+"'");
  }
}

void DocumentBuilder::consume(char *s, int len){
  int idx;
  if (len == -1){
    len = (int)strlen(s);
  }
  for(idx = 0; idx < len && peek() == s[idx]; idx++){
    get();
  }
  if (idx < len){
    throw ParseException(StringBuffer("Invalid sequence. waiting for '")+s+"'");
  }
}
void DocumentBuilder::incDocumentLine(){
  doc->line++;
}
void DocumentBuilder::setDocumentPos(int pos){
  doc->pos = pos;
}
void DocumentBuilder::incDocumentPos(){
  doc->pos++;
}

Document *DocumentBuilder::newDocument()
{
  return new Document();
}

void DocumentBuilder::free(Document *doc)
{
  bool skip_childred = false;

  xml::node *rmnext = doc->getFirstChild();
  while(rmnext != doc && rmnext != null)
  {
    if (!skip_childred){
      while(rmnext->getFirstChild() != null){
        rmnext = rmnext->getFirstChild();
      }
    };
    skip_childred = false;

    xml::node *el = rmnext->getNextSibling();
    if(el == null){
      el = rmnext->getParent();
      skip_childred = true;
    }
    delete rmnext;
    rmnext = el;
  }
  delete doc;
}

/**  #123  #xABCD */
bool DocumentBuilder::getXMLNumber(const string &str, int *res)
{
int type, num;
int s, e, i, j, k;
long r;

  e = str.GetLength();
  if (!e) return false;

  if (str[0] != '#') return false;

  s = 1;
  type = 0;

  if(str[1] == 'x'){
    s = 2;
    type = 1;
  };

  switch(type){
    case 0:
      num = 0;
      i = e-1;
      while(i >= s){
        j = str[i];
        if((j < '0') || (j > '9'))
          return false;
        j &= 15;
        k = e-i-1;
        r = (long)j;
        while(k){
          k--;
          r *= 10;
        };
        num += r;
        i--;
      };
      *res = num;
      break;
    case 1:
      num = 0;
      i = e-1;
      while(i >= s){
        j = str[i];
        if(((j < 0x30) || (j > 0x39)) &&
          ((j < 'a') || (j > 'f')) &&
          ((j < 'A') || (j > 'F')))
            return false;
        if (j > 0x60) j -= 0x27;
        if (j > 0x40) j -= 0x7;
        j &= 15;
        if(i > e-9)
          num |= (j << ((e-i-1)*4) );
        i--;
      };
      *res = num;
      break;
  };
  return true;
};

const short xml::node::COMMENT_NODE = 0;
const short xml::node::DOCUMENT_NODE = 1;
const short xml::node::ELEMENT_NODE = 2;
const short xml::node::PROCESSING_INSTRUCTION_NODE = 3;
const short xml::node::TEXT_NODE = 4;

xml::node *xml::node::appendChild(xml::node *newChild)
{
  newChild->parent = this;

  if (firstChild == null)
  {
    firstChild = newChild;
    firstChild->prev = firstChild->next = newChild;
    return firstChild;
  }
  newChild->prev = firstChild->prev->next;
  firstChild->prev->next = newChild;
  firstChild->prev = newChild;
  newChild->next = firstChild;
  newChild->parent = this;
  return newChild;
}

void xml::node::setAttribute(const string *name, const string *value)
{
  if (attributesHash.get(name) != null){
    for(int idx = 0; idx < attributes.get_size(); idx++){
      if (attributes.element_at(idx)->equals(name)){
        delete attributes.element_at(idx);
        delete attributesHash.get(name);
        attributes.removeElementAt(idx);
        break;
      }
    }
  }
  attributes.addElement(name);
  attributesHash.put(name, value);
}

ProcessingInstruction *Document::createProcessingInstruction(const string *target, const string *data)
{
  ProcessingInstruction *pi = new ProcessingInstruction(target, data);
  pi->ownerDocument = this;
  return pi;
}

xml::node *Document::createElement(const string *tagName)
{
  xml::node *elem = new xml::node(tagName);
  elem->ownerDocument = this;
  return elem;
}

Comment *Document::createComment(const string *data)
{
  Comment *comment = new Comment(data);
  comment->ownerDocument = this;
  return comment;
}

Text *Document::createTextNode(const string *data)
{
  Text *text = new Text(data);
  text->ownerDocument = this;
  return text;
}
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
 * the Initial Developer. All Rights Reserved.
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
