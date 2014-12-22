#pragma once


namespace database
{


   class base;


   class CLASS_DECL_AXIS set :
      virtual public ::object
   {
   protected:
   /*  char *Host     = ""; //WORK_HOST;
     char *database = ""; //WORK_DATAAXIS;
     char *User     = ""; //WORK_USER;
     char *Password = ""; //WORK_PASSWORD;
   */

     base *db;      // info about db connection
     dsStates ds_state;           // current state
     CFields fields_object, edit_object;
         

     bool            active;         // Is Query Opened?
     bool            haveError;
     index             frecno;          // number of current row bei bewegung
     string          sql;
     int32_t             m_iLastResult;
     string          m_strQueryErrorMessage;
     string          m_strDatabaseErrorMessage;

     str_helper      pars;

     parameter_list  m_parameterlist;              // Paramlist for locate
     bool            fbof, feof;
     bool            autocommit;      // for transactions


   /* Variables to store SQL statements */
     string empty_sql;       // Executed when result set is is_empty
     string select_sql;       // May be only single string var

     stringa update_sql;       // May be an array in complex queries
   /* Field values for updating must has prefix :NEW_ and :OLD_ and field name
      Example:
      update  wt_story set idobject set idobject=:NEW_idobject,body=:NEW_body
      where idobject=:OLD_idobject
      Essentually fields idobject and body must present in the
      result set (select_sql statement) */

     stringa insert_sql;       // May be an array in complex queries
   /* Field values for inserting must has prefix :NEW_ and field name
      Example:
      insert into wt_story (idobject, body) values (:NEW_idobject, :NEW_body)
      Essentually fields idobject and body must present in the
      result set (select_sql statement) */

     stringa delete_sql;       // May be an array in complex queries
   /* Field values for deleing must has prefix :OLD_ and field name
      Example:
      delete from wt_story where idobject=:OLD_idobject
      Essentually field idobject must present in the
      result set (select_sql statement) */




   /* Arrays for searching */
   //  string_list names, values;


   /* Makes direct inserts into database via mysql_query function */
     virtual void make_insert() = 0;
   /* Edit SQL */
     virtual void make_edit() = 0;
   /* Delete SQL */
     virtual void make_deletion() = 0;

   /* This function works only with MySQL database
      Filling the fields information from select statement */
     virtual void fill_fields()=0;

   /* Parse Sql - replacing fields with prefixes :OLD_ and :NEW_ with current values of OLD or NEW field. */
     void parse_sql(const char * sql);

   /* Returns old field value (for :OLD) */
     virtual const var f_old(const char *f);

   public:

   /* constructor */
     set();
     set(base *newDb);

   /* destructor */
     ~set();

   /* sets a new value of connection to database */
     void setDatabase(base *newDb) { db = newDb; }
   /* retrieves  a database which connected */
     base *getDatabase() { return db; }

   /* sets a new query string to database server */
     void setExecSql(const char *newSql) { sql = newSql; }
   /* retrieves a query string */
     const char *getExecSql() { return sql; }

   /* status active is OK query */
     virtual bool isActive() { return active; }

   //  virtual void setSqlParams(const char *sqlFrmt, sqlType t, ...); 


   /* error handling */
   //  virtual void halt(const char *msg);
   /* sequence numbers */
     virtual long nextid(const char *seq_name)=0;
   /* sequence numbers */
     virtual ::count num_rows()= 0;

   /* open SQL query */
     virtual void open(const char * sql) = 0;
     virtual void open() = 0;
   /* func. executes a query without results to return */
     virtual bool exec(const char * sql) = 0;
     virtual bool exec() = 0;
     virtual const void * getExecRes()=0;
   /* as open, but with our query exept Sql */
     virtual bool query(const char *sql) = 0;

     virtual var query_item(const char *sql);
   /* close SQL Query*/
     virtual void close();
   /* This function looks for field Field_name with value equal Field_value
      Returns true if found (position of set is set to founded position)
      and false another way (position is not changed). */
   //  virtual bool lookup(char *field_name, char*var);
   /* Refresh set (reopen it and set the same cursor position) */
     virtual void refresh();

   /* Go to record No (starting with 0) */
     virtual bool seek(index pos=0);
   /* Go to record No (starting with 1) */
     virtual bool goto_rec(index pos=1);
   /* Go to the first record in set */
     virtual void first();
   /* Go to next record in set */
     virtual void next();
   /* Go to porevious record */
     virtual void prev();
   /* Go to last record in set */
     virtual void last();

   /* Check for Ending set */
     virtual bool eof() { return feof; }
   /* Check for Begining set */
     virtual bool bof() { return fbof; }

   /* Start the insert mode */
     virtual void insert();
   /* Start the insert mode (alias for insert() function) */
     virtual void append() { insert(); }
   /* Start the edit mode */
     virtual void edit();

   /* add changes, that were made during insert or edit states of set into the database */
     virtual void post();
   /* Delete statements from database */
     virtual void deletion();
   /* Cancel changes, made in insert or edit states of set */
     virtual void cancel() {};

     virtual void setParamList(const parameter_list &params);
     virtual bool locate();
     virtual bool locate(const parameter_list &params);
     virtual bool findNext();

   /* func. retrieves a number of fields */
   /* Number of fields in a record */
     virtual ::count field_count();                      
     virtual ::count fieldCount();
   /* func. retrieves a field name with 'n' index */
     virtual const char *fieldName(index n);
   /* func. retrieves a field index with 'fn' field name,return -1 when field name not found */
     virtual int32_t  fieldIndex(const char *fn);
   /* func. retrieves a field size */
     virtual ::count fieldSize(index n);


   /* set field value */
     virtual bool SetFieldValue(const char *f_name, const var &value);
   /* alias for set_CFieldValue */
     virtual bool sf(const char *f, const var &v) { return SetFieldValue(f,v); }



   /* Return field name by it index */
   //  virtual char *field_name(int32_t f_index) { return field_by_index(f_index)->get_field_name(); };

   /* Getting value of field for current record */
      virtual var GetFieldValue(const char *f_name);
      virtual var GetSelectFieldValue(index iField);
   /* Alias to get_CFieldValue */
      var fv(const char *f) { return GetFieldValue(f); }

   /* ------------ for transaction ------------------- */
     void set_autocommit(bool v) { autocommit = v; }
     bool get_autocommit() { return autocommit; }

   /* ----------------- for debug -------------------- */
     CFields & get_fields_object() {return fields_object;};
     CFields & get_edit_object() {return edit_object;};

    private:
     void set_ds_state(dsStates new_state) {ds_state = new_state;};   
    public:
   /* return ds_state value */
     dsStates get_state() {return ds_state;};

   /*add a new value to select_sql*/
     void set_select_sql(const char *sel_sql);
   /*add a new value to update_sql*/
     void add_update_sql(const char *upd_sql);
   /*add a new value to insert_sql*/
     void add_insert_sql(const char *ins_sql);
   /*add a new value to delete_sql*/
     void add_delete_sql(const char *del_sql);

   /*clear update_sql*/
     void clear_update_sql();
   /*clear insert_sql*/
     void clear_insert_sql();
   /*clear delete_sql*/
     void clear_delete_sql();

   /*get value of select_sql*/
    const char *get_select_sql();

   };


} // namespace vmssqlite




