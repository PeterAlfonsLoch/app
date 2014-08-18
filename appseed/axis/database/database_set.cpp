#include "framework.h"

namespace database
{

   set::set()
   {

     db = NULL;
     haveError = active = false;
     frecno = 0;
     fbof = feof = true;
     autocommit = true;

     select_sql = "";

   }



   set::set(axis *newDb) {

     db = newDb;
     haveError = active = false;
     frecno = 0;
     fbof = feof = true;
     autocommit = true;

     select_sql = "";


   }


   set::~set()
   {
     update_sql.remove_all();
     insert_sql.remove_all();
     delete_sql.remove_all();



   }


   /*void set::setSqlParams(const char *sqlFrmt, sqlType t, ...) {
     va_list ap;
     char sqlCmd[DB_BUFF_MAX+1];

     va_start(ap, t);
     vprintf(sqlCmd, DB_BUFF_MAX-1, sqlFrmt, ap);
     va_end(ap);

      switch (t) {
          case sqlSelect: set_select_sql(sqlCmd);
                          break;
          case sqlUpdate: add_update_sql(sqlCmd);
                          break;
          case sqlInsert: add_insert_sql(sqlCmd);
                          break;
          case sqlDelete: add_delete_sql(sqlCmd);
                          break;
          case sqlExec: sql = sqlCmd;
                       break;

     }
   }*/



   void set::set_select_sql(const char *sel_sql)
   {
      select_sql = sel_sql;
   }

   void set::parse_sql(const char * sql)
   {
      string fpattern,by_what;
      pars.set_str(sql);
      int32_t i;
      for (i=0;i< fields_object.get_size();i++)
      {
         fpattern = ":OLD_" + fields_object[i].m_properties.name;
         by_what = "'" + fields_object[i].m_value + "'";
         //cout << "parsing " << fpattern <<by_what<<"\n\n";
         sql = pars.replace(fpattern,by_what);
      }

      for (i=0;i< edit_object.get_size();i++)
      {
         fpattern = ":NEW_" + edit_object[i].m_properties.name;
         by_what = "'" + edit_object[i].m_value + "'";
         sql = pars.replace(fpattern,by_what);
      }

   //   string_list before_array, after_array;
   //   int32_t tag = 0;
   //   bool eol_reached = false,
   //        was_changed = false,
   //        flag = false;
   //   ExtString which_before, which_after;
   //   ExtString bef, aft, prev_before, right_side, which_field, changed_field, f_value;

   //   before_array.add(":NEW_", tag);
   //   before_array.add(":OLD_", tag);

   //   after_array.add(")", tag);
   //   after_array.add(",", tag);
   //   after_array.add(" ", tag);

   //   sq.squish();
   //   bef = sq.before_arr(before_array, which_before);

   //   while (!(bef == prev_before)) {
   //    right_side = sq.after(which_before, flag);
   //    right_side.squish();

   //    aft = right_side.after_arr(after_array, which_after);
   //         aft.squish();
   //     which_field = right_side.before(which_after);

   //    // checking whather we reach end of line
   //    if ((which_field == "\0") && (which_before != "\0")) {
   //       which_field = right_side;
   //       eol_reached = true;
   //       }

   //    // If new field and is in insert or edit mode - looks in edit_object
   //    if ((which_before == ":NEW_") && (which_field != "\0")) {
   //       which_field.squish();
   //                 f_value.assign(fv(which_field.getChars()));
   //       f_value.addslashes();
   //       changed_field.assign("'");
   //       changed_field + f_value + "'";
   //    }
   //    else
   //    // else looking old value in the current result set
   //       if ((which_before == ":OLD_") && (which_field != "\0")) {
   //       which_field.squish();
   //                 f_value.assign(f_old(which_field.getChars()));
   //       f_value.addslashes();
   //       changed_field.assign("'");
   //       changed_field + f_value + "'";
   //       }

   //    if (!eol_reached)  {

   //       sq.assign(bef + changed_field + which_after + aft);
   //       }
   //    else {
   //       if (!was_changed && (which_field != "\0")) {

   //          sq.assign(bef + changed_field + which_after + aft);
   //          was_changed = true;
   //          }
   //       }


   //    prev_before = bef;
   //    bef = sq.before_arr(before_array, which_before);

   //   }

   }


   void set::close() {
     haveError  = false;
     frecno = 0;
     fbof = feof = true;
     active = false;
   }


   var set::query_item(const char *sql)
   {
      if(!query(sql))
         return ::var(::var::type_null);
      return GetSelectFieldValue(0);
   }

   bool set::seek(index pos)
   {
      frecno = (pos<num_rows()-1)? pos: num_rows()-1;
      frecno = (frecno<0)? 0: frecno;
      fbof = feof = (num_rows()==0)? true: false;
      return frecno != FALSE;
   }

   void set::refresh()
   {
      index row = frecno;
      if ((row != 0) && active)
      {
         close();
         open();
         seek(row);
      }
      else
      {
         open();
      }
   }


   void set::first() {
     if (ds_state == dsSelect) {
       frecno = 0;
       feof = fbof = (num_rows()>0)? false : true;
     }
   }

   void set::next() {
     if (ds_state == dsSelect) {
       fbof = false;
       if (frecno<num_rows()-1) {
         frecno++;
         feof = false;
       } else feof = true;
       if (num_rows()<=0) fbof = feof = true;
     }
   }

   void set::prev() {
     if (ds_state == dsSelect) {
       feof = false;
       if (frecno) {
         frecno--;
         fbof = false;
       } else fbof = true;
       if (num_rows()<=0) fbof = feof = true;
     }
   }

   void set::last() {
     if (ds_state == dsSelect) {
       frecno = (num_rows()>0)? num_rows()-1: 0;
       feof = fbof = (num_rows()>0)? false : true;
     }
   }

   bool set::goto_rec(index pos)
   {
     if (ds_state == dsSelect)
     {
       return seek(pos - 1);
     }
     return false;
   }


   void set::insert() {
     //cout << "insert\n\n";
      for (int32_t i=0; i<field_count(); i++) {
        fields_object[i].m_value = "";
        edit_object[i].m_value = "";
        //cout <<"Insert:"<<i<<"\n\n";
      }
     ds_state = dsInsert;
   }


   void set::edit() {
     if (ds_state != dsSelect) {
   //    cerr<<"Editing is possible only when query exists!";
       return;
     }
     for (int32_t i=0; i<fields_object.get_size(); i++) {
          edit_object[i].m_value = fields_object[i].m_value;
     }
     ds_state = dsEdit;
   }


   void set::post() {
     if (ds_state == dsInsert) make_insert();
     else if (ds_state == dsEdit) make_edit();
   }


   void set::deletion() {
     if (ds_state == dsSelect) make_deletion();
   }


   bool set::SetFieldValue(const char *f_name, const var &value)
   {
      bool found = false;
      if ((ds_state == dsInsert) || (ds_state == dsEdit))
      {
         for (int32_t i=0; i < fields_object.get_size(); i++)
         {
            if (edit_object[i].m_properties.name == f_name)
            {
               edit_object[i].m_value = value;
               found = true;
            }
         }
         if (!found)
         {
            throw DbErrors("Field not found: %s",f_name);
         }
         return true;
      }
      throw DbErrors("Not in Insert or Edit state");
      //  return false;
   }


   var set::GetFieldValue(const char *f_name)
   {
      if (ds_state != dsInactive)
      {
         if (ds_state == dsEdit || ds_state == dsInsert)
         {
            for (int32_t i=0; i < edit_object.get_size(); i++)
            {
               if (edit_object[i].m_properties.name == f_name)
               {
                  return edit_object[i].m_value;
               }
            }
            throw DbErrors("Field not found: %s",f_name);
         }
         else
         {
            for (int32_t i=0; i < fields_object.get_size(); i++)
            {
               if (fields_object[i].m_properties.name == f_name)
               {
                  return fields_object[i].m_value;
               }
            }
            throw DbErrors("Field not found: %s",f_name);
         }
      }
      throw DbErrors("set state is Inactive");
   }

   var set::GetSelectFieldValue(index iField)
   {
      if (ds_state != dsInactive)
      {
         if(iField < 0 || iField >= fields_object.get_size())
         {
            throw DbErrors("Field not found: index = %d", iField);
         }
         else
         {
            return fields_object[iField].m_value;
         }
      }
      throw DbErrors("set state is Inactive");
   }



   const var set::f_old(const char *f_name)
   {
      if (ds_state != dsInactive)
      {
         for (int32_t i=0; i < fields_object.get_size(); i++)
         {
            if (fields_object[i].m_properties.name == f_name)
            {
               return fields_object[i].m_value;
            }
         }
      }
     return var();
   }



   void set::setParamList(const parameter_list &params)
   {
      m_parameterlist = params;
   }


   bool set::locate()
   {
     bool result;
     if (m_parameterlist.is_empty()) return false;

     first();
     while (!eof()) {
       result = true;
       for (int32_t i=0;i < m_parameterlist.get_size();i++)
         if (fv(m_parameterlist.GetKey(i)).get_string() == m_parameterlist.GetFieldValue(i).get_string()) {
      continue;
         }
         else {result = false; break;}
       if (result) { return result;}
       next();
     }
     return false;
   }

   bool set::locate(const parameter_list &params) {
     m_parameterlist = params;
     return locate();
   }

   bool set::findNext() {
     bool result;
     if (m_parameterlist.is_empty()) return false;

     while (!eof()) {
       result = true;
       for (int32_t i=0;i< m_parameterlist.get_size();i++)
         if (fv(m_parameterlist.GetKey(i)).get_string() == m_parameterlist.GetFieldValue(i).get_string()) {
      continue;
         }
         else {result = false; break;}
       if (result) { return result;}
       next();
     }
     return false;
   }


   void set::add_update_sql(const char *upd_sql){
     string s = upd_sql;
     update_sql.add(s);
   }

   void set::add_insert_sql(const char *ins_sql){
     string s = ins_sql;
     insert_sql.add(s);
   }

   void set::add_delete_sql(const char *del_sql){
     string s = del_sql;
     delete_sql.add(s);
   }

   void set::clear_update_sql(){
     update_sql.remove_all();
   }

   void set::clear_insert_sql(){
     insert_sql.remove_all();
   }

   void set::clear_delete_sql()
   {
     delete_sql.remove_all();
   }

   ::count set::field_count()
   {
      return fields_object.get_size();
   }

   ::count set::fieldCount()
   {
      return fields_object.get_size();
   }

   const char *set::fieldName(index n)
   {
     if ( n < field_count() && n >= 0)
       return fields_object[n].m_properties.name;
     else
       return NULL;
   }

   ::count set::fieldSize(index n)
   {
     if ( n < field_count() && n >= 0)
       return fields_object[n].m_properties.field_len;
     else
       return 0;
   }

   int32_t set::fieldIndex(const char *fn)
   {
      for (int32_t i=0; i < fields_object.get_size(); i++)
      {
         if(fields_object[i].m_properties.name == fn)
            return i;
      }
      return -1;
   }

} // namespace vmssqlite

