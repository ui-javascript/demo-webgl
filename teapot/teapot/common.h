#ifndef COMMON_H
#define COMMON_H

/*线条类型*/
#define SOLID_LINE	0xffff//实线 1111 1111 1111 1111
#define DASH_LINE	0xf8f8//虚线 1111 1000 1111 1000
#define DOT_LINE	0x8888//点线 1000 1000 1000 1000

#define ROUND(a) ((int)(a+0.5))

typedef struct{
	int x,y; 
}wcPt2D;

typedef struct{
	float x,y,z;
}wcPt3D;

/*两数互换*/
inline void swap(int &ia,int &ib)
{
	ia=ia^ib;
	ib=ib^ia;
	ia=ia^ib;
}

inline void swap(float &fa, float &fb)
{
	float fc = fa;
	fa = fb;
	fb = fc;
}

#endif
