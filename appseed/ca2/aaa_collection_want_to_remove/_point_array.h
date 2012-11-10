#pragma once

class CLASS_DECL_ca point_array :
   public raw_array < point >
{
public:
   __inline point_array() : raw_array < point >() {}
   __inline point_array(const point_array & pointset) { operator=(pointset); }
   virtual ~point_array(void);

   void offset(int x, int y);
   void offset(class point point);

   __inline index add(int x, int y) {return raw_array < point >::add(point(x, y)); }
   __inline index add(POINT point) {return add(point.x, point.y); }
   __inline point_array & operator =(const point_array & pointset) { copy(pointset); return *this; }

};

class CLASS_DECL_ca point64_array :
   public raw_array < point64 >
{
public:
   virtual ~point64_array(void);

   void offset(__int64 x, __int64 y);
   void offset(class point64 point);
};
