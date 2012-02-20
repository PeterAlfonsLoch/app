#pragma once

namespace xml
{

   class document;

   class CLASS_DECL_ca node :
      virtual public ::radix::object,
      virtual public ex1::byte_serializable
   {
   public:

      class CLASS_DECL_ca base_array :
         virtual public array_app_alloc < node >
      {
      public:


         base_array(::ca::application * papp);


      };

      node(::ca::application * papp);
      node(const node & node);
      virtual ~node();

   /*   virtual void SetName(const char * lpcszName);
      virtual void SetValue(const char * lpcszValue);

      virtual void GetName(string & lpcszName);
      virtual void get_value(string & strValue);


      virtual node & AddChildNode(const char * lpcszName);
      virtual node & AddChildNode(const char * lpcszName, const char * lpcszValue);
      virtual node & AddChildNode(node & node);
      virtual void AddAttribute(const char * lpcszName, int_array & strValue);
      virtual void AddAttribute(const char * lpcszName, int  bValue);
      virtual void AddAttribute(const char * lpcszName, const char * bstrValue);
      virtual void RemoveAllNodes();

      virtual bool GetAttributeValue(const char * lpcszName, string & strValue);
      virtual bool GetAttributeValue(const char * lpcszName, int & iValue);
      */
      virtual index find(node * pnode);
      virtual index find(const char * lpcszName, index iStart = 0);
      virtual index find(const char * lpcszName, attr_array & attr, index iStart = 0);
      virtual bool contains(attr_array & attributea);
      virtual node * get_next_sibling();

      virtual node * first_child();



      // name and value
      string               m_strName;
      string               m_strValue;

      // internal variables
      node *               m_pnodeParent;      // parent node
      node::base_array          m_nodea;            // children pointer node base_array
      attr_array          m_attra;            // attr pointer base_array
      e_node               m_etype;            // node type
      document *            m_pdoc;            // document

      // Load/Save XML
      char *   load(const char * pszXml, parse_info * pi = NULL);
      char *   load(::ex1::file * pfile, parse_info * pi = NULL);

      string get_xml(disp_option * opt = NULL);
      string get_text(disp_option * opt = NULL);

      bool consume(const char * & pszXml, const char * psz);
      bool consume_whitespaces(const char * & pszXml, int iMinimumCount = 1);

      char * LoadOtherNodes(bool* pbRet, const char * pszXml, parse_info * pparseinfo = NULL);

      // internal load functions
      char *   LoadAttributes( const char * pszAttrs, parse_info * pi = NULL);
      char *   LoadAttributes( const char * pszAttrs, const char * pszEnd, parse_info * pi = NULL);
      char *   LoadProcessingInstruction( const char * pszXml, parse_info * pi = NULL);
      char *   LoadDocType( const char * pszXml, parse_info * pi = NULL);
      char *   LoadComment( const char * pszXml, parse_info * pi = NULL);
      char *   LoadCDATA( const char * pszXml, parse_info * pi = NULL);



      // in own attr list
      ::xml::attr *           find_attr(const char * attrname );
      var                     attr(const char * attrname);
      virtual bool            get_attr(const char * attrname, string & strValue);
      virtual bool            get_attr(const char * lpcszName, int & iValue);
      virtual bool            get_attr(const char * lpcszName, bool & bValue);
      attr_array              attrs(const char * name);
      attr_array  &           attrs();

      // in one level child nodes
      node *                  get_child( const char * name);
      node *                  get_child_with_attr(const char * lpcszName, const char * pszAttr, var value, index iStart = 0);
      node *                  get_node_from_path(const char * path);
      node *                  get_node_from_attr_path(const char * path, const char * pszName, const char * pszAttr);
      string                  get_child_simple_path(node * pnode);
      string                  get_child_simple_attr_path(node * pnode, const char * pszAttr);
      node *                  get_child(const char * name, index & iStartPosition);
      string                  get_child_value(const char * name);
      string                  get_child_text(const char * name, disp_option * opt = NULL);
      node::base_array        children(const char * name);
      node::base_array &      children();

      ::xml::attr *           GetChildAttr(const char * name, const char * attrname);
      string                  GetChildAttrValue(const char * name, const char * attrname);
      node *                  GetChildByAttr(const char * pszName, const char * pszAttrName, const char * pszAttrValue);

      node *                  get_child_at(const char * pszName, index iIndex, index iDepth);
      count                   get_child_attr_value(stringa & stra, const char * pszName, const char * pszAttrName, index iDepth = 1);
      count                   remove_child_with_attr(const char * pszName, const char * pszAttrName, index iIndex, count iCount = 1, index iDepth = 1);

      // search node
      node *                  rfind( const char * name, int iDepth = -1);

      // modify DOM
      count                   get_children_count();
      count                   get_children_count(const char * pszName);
      count                   get_children_count(const char * pszName, index iDepth);
      node *                  child_at(index i);
      //node *                create_node( const char * name = NULL, const char * value = NULL );
      node *                  add_child( const char * name = NULL, const char * value = NULL );
      node *                  add_child( node * node );
      bool                    remove_child( node * node );
      node *                  detach_child( node * node );

      // node/branch copy
      void                    CopyNode( node * node );
      void                    CopyBranch( node * branch );
      void                    _CopyBranch( node * node );
      node *                  AppendChildBranch( node * node );

      // modify attr
      ::xml::attr *           attr_at( index i );
      //attr * CreateAttr( const char * anem = NULL, const char * value = NULL );
      ::xml::attr *           add_attr(const char * pszName = NULL, const char * value = NULL);
      ::xml::attr *           add_attr(const char * pszName, int iValue);
      ::xml::attr *           add_attr(const char * pszName, int64_t iValue);
      ::xml::attr *           add_attr(const ::xml::attr & attr);
      ::xml::attr *           set_attr(const char * pszName, const char * value);
      ::xml::attr *           set_attr(const char * pszName, int iValue);
      ::xml::attr *           set_attr(const char * pszName, int64_t iValue);
      ::xml::attr *           set_attr(const char * pszName, bool bValue);
      bool                    remove_attr(::xml::attr * attr);
      ::xml::attr *        detach_attr(::xml::attr * attr);


      bool from_row_column_v2(const string2a & str2a);
      bool to_row_column_v2(string2a & str2a);

      // operator overloads
      node * operator [] ( int i ) { return child_at(i); }
      node& operator = (const node& node);


      void close();


      virtual void write(ex1::byte_output_stream & ostream);
      virtual void read(ex1::byte_input_stream & istream);


   };

} // namespace xml
