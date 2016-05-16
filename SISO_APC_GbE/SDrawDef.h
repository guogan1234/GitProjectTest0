#ifndef SDRAWDEF_H
#define SDRAWDEF_H
typedef struct s_control{
	DWORD	ID;
	DWORD	AN;
	DWORD	AM;
	DWORD	AK;
	UINT	PN;
	UINT	PM;
	UINT	PK;
	struct s_control* next;
}SCtl;

typedef struct CDABP{
	int		width;
	int		height;
	CDC		*dc;
	CBitmap	*bmp;
}CDBP;
typedef struct scolor{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}SDColor;

#endif