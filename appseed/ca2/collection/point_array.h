#pragma once




class CLASS_DECL_ca2 point_array :
   public raw_array < point >
{
public:
   __inline point_array() : raw_array < point >() {}
   __inline point_array(const point_array & pointset) { operator=(pointset); }
   virtual ~point_array(void);

   void offset(int x, int y);
   void offset(class point point);

   void rotate(double dAngle);

   void get_bounding_rect(LPRECT lprect) const;

   static void get_bounding_rect(LPRECT lprect, const POINT * lppoint, count count);

   bool bounding_rect_contains_pt(point pt);

   __inline index add(int x, int y) {return raw_array < point >::add(point(x, y)); }
   __inline index add(POINT point) {return add(point.x, point.y); }
   __inline point_array & operator =(const point_array & pointset) { copy(pointset); return *this; }

};

class CLASS_DECL_ca2 point64_array :
   public raw_array < point64 >
{
public:
   virtual ~point64_array(void);

   void offset(__int64 x, __int64 y);
   void offset(class point64 point);
};


class CLASS_DECL_ca2 double_point_array :
   public raw_array < double_point >
{
public:
   __inline double_point_array() : raw_array < double_point >() {}
   __inline double_point_array(const double_point_array & pointset) { operator=(pointset); }
   virtual ~double_point_array(void);

   void offset(double x, double y);
   void offset(class point point);

   __inline index add(double x, double y) {return raw_array < double_point >::add(double_point(x, y)); }
   __inline index add(double_point point) {return add(point.x, point.y); }
   __inline double_point_array & operator =(const double_point_array & pointset) { copy(pointset); return *this; }

};
