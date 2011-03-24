#pragma once


namespace gen
{
	enum Alignment
	{
		AlignH				      = 3,
		AlignHorizontalCenter   = 1,
		AlignLeft			      = 2,
		AlignRight              = 3,
		AlignV				      = 12,
		AlignVerticalCenter     = 4,
		AlignTop                = 8,
		AlignBottom             = 12,
	};
} // namespace gen

class CLASS_DECL_ca base_rect :
   public rect  
{
public:
   base_rect();
   base_rect(const RECT& srcRect);
   base_rect(int l, int t, int r, int b);

   bool ContainRect(LPCRECT lpcrect) const;
   bool IsRectInside(LPCRECT lpcrect);
   void ConstraintV5(LPCRECT lpcrect, const size sizeMin);
   void Align(int align, LPCRECT lpcrect);
   void ScaleHeightAspect(int iNewHeight, int iCenterX, int iCenterY);
   void ScaleRect(double dx, double dy, int ix, int iy);
   void ExtendOnCenter(LPCRECT lpcrect);
   void FitOnCenterOf(LPCRECT lpcrect);
	void DeflateBottomRightSizeByRate(double dRate);
   void SetBottomRightSize(int iWidth, int iHeight);
   ~base_rect();
   inline point TopRight();
   inline point BottomLeft();
   void operator=(const RECT& srcRect);

   void SubtractRectMajor(LPCRECT lpcrectMajor, LPCRECT lpcrectMinor);
   void SubtractRectMinor(LPCRECT lpcrectMajor, LPCRECT lpcrectMinor);

   point center();


   bool is_null();
   bool is_empty();
};

inline point base_rect::TopRight()
{
   return point(right, top);
}

inline point base_rect::BottomLeft()
{ 
   return point(left, bottom); 
}

inline point base_rect::center()
{ 
   return point((left + right) / 2, (top + bottom) / 2); 
}

inline bool base_rect::is_null()
{ 
   return left == 0 && top == 0 && right == 0 && bottom == 0; 
}

inline bool base_rect::is_empty()
{
   return width() == 0 && height() == 0;
}









class CLASS_DECL_ca base_rect64 :
   public rect64  
{
public:
   base_rect64();
   base_rect64(const __rect64& srcRect);
   base_rect64(__int64 l, __int64 t, __int64 r, __int64 b);
   ~base_rect64();

   bool ContainRect(const __rect64 * lpcrect) const;
   bool IsRectInside(const __rect64 * lpcrect);
   void ConstraintV5(const __rect64 * lpcrect, const size sizeMin);
   void Align(__int64 align, const __rect64 * lpcrect);
   void ScaleHeightAspect(__int64 iNewHeight, __int64 iCenterX, __int64 iCenterY);
   void ScaleRect(double dx, double dy, __int64 ix, __int64 iy);
   void ExtendOnCenter(const __rect64 * lpcrect);
   void FitOnCenterOf(const __rect64 * lpcrect);
	void DeflateBottomRightSizeByRate(double dRate);
   void SetBottomRightSize(__int64 iWidth, __int64 iHeight);
   
   inline point64 TopRight();
   inline point64 BottomLeft();
   void operator=(const __rect64& srcRect);

   void SubtractRectMajor(const __rect64 * lpcrectMajor, const __rect64 * lpcrectMinor);
   void SubtractRectMinor(const __rect64 * lpcrectMajor, const __rect64 * lpcrectMinor);

   point64 center();


   bool is_null();
   bool is_empty();
};

inline point64 base_rect64::TopRight()
{
   return point64(right, top);
}

inline point64 base_rect64::BottomLeft()
{ 
   return point64(left, bottom); 
}

inline point64 base_rect64::center()
{ 
   return point64((left + right) / 2, (top + bottom) / 2); 
}

inline bool base_rect64::is_null()
{ 
   return left == 0 && top == 0 && right == 0 && bottom == 0; 
}

inline bool base_rect64::is_empty()
{
   return width() == 0 && height() == 0;
}
