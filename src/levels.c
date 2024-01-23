#define MAX_LEVELS 30
struct level
{
	void (*init)(void);
	int (*check)(void);
	char *desc;
} levels[MAX_LEVELS];
void level_add(void (*init)(void),int (*check)(void),char *desc)
{
	if(count_levels>=MAX_LEVELS)
	{
		MessageBoxA(NULL,"Too many levels","Error",0);
		exit(1);
	}
	levels[count_levels].init=init;
	levels[count_levels].check=check;
	levels[count_levels].desc=desc;
	++count_levels;
}
double distance(double x1,double y1,double x2,double y2)
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
double cos_angle(double x1,double y1,double x2,double y2)
{
	return (x1*x2+y1*y2)/sqrt((x1*x1+y1*y1)*(x2*x2+y2*y2));
}
double distance_points(struct point *A,struct point *B)
{
	return distance(A->x,A->y,B->x,B->y);
}
double cos_angle_points(struct point *A1,struct point *B1,struct point *A2,struct point *B2)
{
	return cos_angle(B1->x-A1->x,B1->y-A1->y,B2->x-A2->x,B2->y-A2->y);
}
void level0001_init(void)
{
	add_point(185.327,249.992,0,'A');
	add_point(314.548,249.853,0,'B');
}
int level0001_check(void)
{
	struct point *A,*B,*C;
	A=point_by_label('A');
	B=point_by_label('B');
	C=point_by_label('C');
	if(A==NULL||B==NULL||C==NULL)
	{
		return 0;
	}
	if(!IS_ZERO(distance_points(A,B)-distance_points(B,C)))
	{
		return 0;
	}
	if(!IS_ZERO(distance_points(A,B)-distance_points(A,C)))
	{
		return 0;
	}
	return 1;
}
void level0002_init(void)
{
	add_point(185.327,249.992,0,'A');
	add_point(269.749,249.853,0,'B');
}
int level0002_check(void)
{
	struct point *A,*B,*C;
	A=point_by_label('A');
	B=point_by_label('B');
	C=point_by_label('C');
	if(A==NULL||B==NULL||C==NULL)
	{
		return 0;
	}
	if(!IS_ZERO(distance_points(A,B)-distance_points(B,C)))
	{
		return 0;
	}
	if(!IS_ZERO(cos_angle_points(B,A,B,C)+1.0))
	{
		return 0;
	}
	return 1;
}
void level0003_init(void)
{
	add_point(185.327,249.992,0,'A');
	add_point(314.548,249.853,0,'B');
}
int level0003_check(void)
{
	struct point *A,*B,*C;
	A=point_by_label('A');
	B=point_by_label('B');
	C=point_by_label('C');
	if(A==NULL||B==NULL||C==NULL)
	{
		return 0;
	}
	if(!IS_ZERO(distance_points(A,C)-distance_points(B,C)))
	{
		return 0;
	}
	if(!IS_ZERO(cos_angle_points(C,A,C,B)+1.0))
	{
		return 0;
	}
	return 1;
}
void level0004_init(void)
{
	add_point(185.327,249.992,0,'A');
	add_point(314.548,249.853,0,'B');
	add_point(230.751,210.032,0,'C');
	add_line(185.327,249.992,314.548,249.853,0);
}
int level0004_check(void)
{
	struct point *A,*B,*C,*D;
	A=point_by_label('A');
	B=point_by_label('B');
	C=point_by_label('C');
	D=point_by_label('D');
	if(A==NULL||B==NULL||C==NULL||D==NULL)
	{
		return 0;
	}
	if(!IS_ZERO(distance_points(A,C)-distance_points(A,D)))
	{
		return 0;
	}
	if(!IS_ZERO(distance_points(B,C)-distance_points(B,D)))
	{
		return 0;
	}
	return 1;
}
void level0005_init(void)
{
	add_point(185.327,249.992,0,'A');
	add_point(314.548,249.853,0,'B');
	add_point(230.751,210.032,0,'C');
	add_line(185.327,249.992,314.548,249.853,0);
}
int level0005_check(void)
{
	struct point *A,*B,*C,*D;
	double cosA;
	A=point_by_label('A');
	B=point_by_label('B');
	C=point_by_label('C');
	D=point_by_label('D');
	if(A==NULL||B==NULL||C==NULL||D==NULL)
	{
		return 0;
	}
	if(!IS_ZERO(cos_angle_points(C,D,A,B)))
	{
		return 0;
	}
	cosA=cos_angle_points(A,D,B,D);
	if(!IS_ZERO(cosA*cosA-1.0))
	{
		return 0;
	}
	return 1;
}
void level0006_init(void)
{
	add_point(185.327,249.992,0,'A');
	add_point(314.548,249.853,0,'B');
	add_point(230.751,210.032,0,'C');
	add_line(185.327,249.992,314.548,249.853,0);
}
int level0006_check(void)
{
	struct point *A,*B,*C;
	struct line *l;
	double d,cosA;
	A=point_by_label('A');
	B=point_by_label('B');
	C=point_by_label('C');	
	if(A==NULL||B==NULL||C==NULL)
	{
		return 0;
	}
	l=line_list;
	while(l)
	{
		d=distance_to_line(l,C->x,C->y);
		if(IS_ZERO(d))
		{
			cosA=cos_angle(B->x-A->x,B->y-A->y,l->x2-l->x1,l->y2-l->y1);
			if(IS_ZERO(cosA*cosA-1.0))
			{
				return 1;
			}
		}
		l=l->next;
	}
	return 0;
}
void level0007_init(void)
{
	add_point(185.327,249.992,0,'A');
	add_point(314.548,249.853,0,'B');
	add_point(230.751,180.012,0,'C');
	add_point(240.212,280.429,0,'D');
	add_line(185.327,249.992,314.548,249.853,0);
}
int level0007_check(void)
{
	struct point *A,*B,*C,*D,*E;
	double cosA,cosB;
	A=point_by_label('A');
	B=point_by_label('B');
	C=point_by_label('C');
	D=point_by_label('D');
	E=point_by_label('E');
	if(A==NULL||B==NULL||C==NULL||D==NULL||E==NULL)
	{
		return 0;
	}
	cosA=cos_angle_points(A,E,A,B);
	if(!IS_ZERO(cosA*cosA-1.0))
	{
		return 0;
	}
	cosA=cos_angle_points(E,A,E,C);
	cosB=cos_angle_points(E,A,E,D);
	if(!IS_ZERO(cosA-cosB))
	{
		return 0;
	}
	return 1;
}
void level0008_init(void)
{
	add_point(185.327,249.992,0,'A');
	add_point(314.548,249.853,0,'B');
	add_point(230.751,180.012,0,'C');
	add_point(260.153,200.105,0,'D');
	add_line(185.327,249.992,314.548,249.853,0);
}
int level0008_check(void)
{
	struct point *A,*B,*C,*D,*E;
	double cosA,cosB;
	A=point_by_label('A');
	B=point_by_label('B');
	C=point_by_label('C');
	D=point_by_label('D');
	E=point_by_label('E');
	if(A==NULL||B==NULL||C==NULL||D==NULL||E==NULL)
	{
		return 0;
	}
	cosA=cos_angle_points(A,E,A,B);
	if(!IS_ZERO(cosA*cosA-1.0))
	{
		return 0;
	}
	cosA=cos_angle_points(E,A,E,C);
	cosB=cos_angle_points(E,A,E,D);
	if(!IS_ZERO(cosA+cosB))
	{
		return 0;
	}
	return 1;
}
void level0009_init(void)
{
	add_point(190.041,250.510,0,'A');
	add_point(310.039,250.490,0,'B');
	add_point(215.316,170.210,0,'C');
	add_line(190.041,250.510,310.039,250.490,0);
	add_line(190.041,250.510,215.316,170.210,0);
}
int level0009_check(void)
{
	struct point *A,*B,*C;
	struct line *l;
	double d,cosA,cosB;
	A=point_by_label('A');
	B=point_by_label('B');
	C=point_by_label('C');	
	if(A==NULL||B==NULL||C==NULL)
	{
		return 0;
	}
	l=line_list;
	while(l)
	{
		d=distance_to_line(l,A->x,A->y);
		if(IS_ZERO(d))
		{
			cosA=cos_angle(B->x-A->x,B->y-A->y,l->x2-l->x1,l->y2-l->y1);
			cosB=cos_angle(C->x-A->x,C->y-A->y,l->x2-l->x1,l->y2-l->y1);
			if(IS_ZERO(cosA-cosB))
			{
				return 1;
			}
		}
		l=l->next;
	}
	return 0;
}
void level000a_init(void)
{
	add_point(230.149,250.312,0,'A');
	add_point(310.205,250.280,0,'B');
}
int level000a_check(void)
{
	struct point *A,*B,*C;
	double cosA,cosB,d1,d2;
	A=point_by_label('A');
	B=point_by_label('B');
	C=point_by_label('C');	
	if(A==NULL||B==NULL||C==NULL)
	{
		return 0;
	}
	cosA=cos_angle_points(A,B,A,C);
	cosB=sqrt(3.0)/2.0;
	if(!IS_ZERO(cosA-cosB))
	{
		return 0;
	}
	d1=distance_points(A,B);
	d2=distance_points(A,C);
	if(!IS_ZERO(d1-d2))
	{
		return 0;
	}
	return 1;
}
void level000b_init(void)
{
	add_point(200.264,250.102,0,'A');
	add_point(300.311,250.103,0,'B');
	add_point(230.643,176.319,0,'C');
}
int level000b_check(void)
{
	struct point *A,*B,*C,*D;
	double d1,d2,d3;
	A=point_by_label('A');
	B=point_by_label('B');
	C=point_by_label('C');
	D=point_by_label('D');
	if(A==NULL||B==NULL||C==NULL||D==NULL)
	{
		return 0;
	}
	d1=distance_points(D,A);
	d2=distance_points(D,B);
	d3=distance_points(D,C);
	if(!IS_ZERO(d1-d2)||!IS_ZERO(d1-d3))
	{
		return 0;
	}
	return 1;
}
void level000c_init(void)
{
	add_point(180.421,250.102,0,'A');
	add_point(320.195,250.103,0,'B');
	add_point(230.643,206.532,0,'C');
	add_point(280.123,215.145,0,'D');
	add_line(230.643,206.532,280.123,215.145,0);
}
int level000c_check(void)
{
	struct point *A,*B,*C,*D,*E;
	double c;
	A=point_by_label('A');
	B=point_by_label('B');
	C=point_by_label('C');
	D=point_by_label('D');
	E=point_by_label('E');
	if(A==NULL||B==NULL||C==NULL||D==NULL||E==NULL)
	{
		return 0;
	}
	c=cos_angle_points(C,D,C,E);
	if(!IS_ZERO(c*c-1.0))
	{
		return 0;
	}
	c=cos_angle_points(A,E,B,E);
	if(!IS_ZERO(c))
	{
		return 0;
	}
	return 1;
}
void level000d_init(void)
{
	add_point(200.264,250.102,0,'A');
	add_point(300.311,250.103,0,'B');
	add_point(230.643,192.319,0,'C');
	
}
int level000d_check(void)
{
	struct point *A,*B,*C,*D;
	double c,d1,d2,d3;
	A=point_by_label('A');
	B=point_by_label('B');
	C=point_by_label('C');
	D=point_by_label('D');
	if(A==NULL||B==NULL||C==NULL||D==NULL)
	{
		return 0;
	}
	c=cos_angle_points(A,B,A,D);
	if(!IS_ZERO(c-1.0))
	{
		return 0;
	}
	d1=distance_points(A,B);
	d2=distance_points(A,C);
	d3=distance_points(A,D);
	if(!IS_ZERO(d1*d3-d2*d2))
	{
		return 0;
	}
	return 1;
}
void level000e_init(void)
{
	add_point(200.264,250.102,0,'A');
	add_point(300.311,250.103,0,'B');
	add_point(222.643,187.319,0,'C');
}
int level000e_check(void)
{
	struct point *A,*B,*C,*D;
	double c1,c2;
	A=point_by_label('A');
	B=point_by_label('B');
	C=point_by_label('C');
	D=point_by_label('D');
	if(A==NULL||B==NULL||C==NULL||D==NULL)
	{
		return 0;
	}
	c1=cos_angle_points(A,B,A,D);
	c2=cos_angle_points(A,C,A,D);
	if(!IS_ZERO(c1-c2))
	{
		return 0;
	}
	c1=cos_angle_points(B,A,B,D);
	c2=cos_angle_points(D,A,D,C);
	if(!IS_ZERO(c1-c2))
	{
		return 0;
	}
	return 1;
}
void level000f_init(void)
{
	add_point(200.264,250.102,0,'A');
	add_point(300.311,250.103,0,'B');
	add_point(222.643,187.319,0,'C');
	add_point(290.042,205.626,0,'D');
	add_line(200.264,250.102,290.042,205.626,0);
}
int level000f_check(void)
{
	struct point *A,*B,*C,*D,*E;
	double c1,c2,d1,d2,d3;
	A=point_by_label('A');
	B=point_by_label('B');
	C=point_by_label('C');
	D=point_by_label('D');
	E=point_by_label('E');
	if(A==NULL||B==NULL||C==NULL||D==NULL||E==NULL)
	{
		return 0;
	}
	c1=cos_angle_points(A,D,A,E);
	if(!IS_ZERO(c1-1.0)&&!IS_ZERO(c1+1.0))
	{
		return 0;
	}
	c1=cos_angle_points(B,A,B,E);
	c2=cos_angle_points(E,A,E,C);
	if(!IS_ZERO(c1-c2))
	{
		return 0;
	}
	return 1;
}
void level0010_init(void)
{
	add_point(210.536,250.620,0,'A');
	add_point(290.295,250.622,0,'B');
	add_point(320.424,450.201,0,'C');
	add_point(380.631,450.201,0,'D');
	add_point(430.741,450.201,0,'E');
}
int level0010_check(void)
{
	struct point *A,*B,*C,*D,*E,*M,*N;
	double c,c1,c2,d1,d2,d3;
	A=point_by_label('A');
	B=point_by_label('B');
	C=point_by_label('C');
	D=point_by_label('D');
	E=point_by_label('E');
	M=point_by_label('M');
	N=point_by_label('N');
	if(A==NULL||B==NULL||C==NULL||D==NULL||E==NULL||M==NULL||N==NULL)
	{
		return 0;
	}
	c1=cos_angle_points(A,M,A,B);
	c2=cos_angle_points(B,N,B,A);
	c=c1*c2-sqrt((1.0-c1*c1)*(1.0-c2*c2));
	if(!IS_ZERO(c+1.0/2.0))
	{
		return 0;
	}
	d1=distance_points(A,M);
	d2=distance_points(B,N);
	d3=distance_points(C,D);
	if(!IS_ZERO(d1-d2)||!IS_ZERO(d1-d3))
	{
		return 0;
	}
	d1=distance_points(M,N);
	d2=distance_points(D,E);
	if(!IS_ZERO(d1-d2))
	{
		return 0;
	}
	return 1;
}
void level0011_init(void)
{
	add_point(215.536,250.620,0,'A');
	add_point(285.295,250.622,0,'B');
	add_point(320.424,410.201,0,'C');
	add_point(380.631,410.201,0,'D');
	add_point(430.741,410.201,0,'E');
}
int level0011_check(void)
{
	struct point *A,*B,*C,*D,*E,*M,*N;
	double c,c1,c2,d1,d2,d3;
	A=point_by_label('A');
	B=point_by_label('B');
	C=point_by_label('C');
	D=point_by_label('D');
	E=point_by_label('E');
	M=point_by_label('M');
	N=point_by_label('N');
	if(A==NULL||B==NULL||C==NULL||D==NULL||E==NULL||M==NULL||N==NULL)
	{
		return 0;
	}
	c1=cos_angle_points(A,M,A,B);
	c2=cos_angle_points(B,N,B,A);
	c=c1*c2-sqrt((1.0-c1*c1)*(1.0-c2*c2))+sqrt(3.0)/2.0;
	if(!IS_ZERO(c))
	{
		return 0;
	}
	d1=distance_points(A,M);
	d2=distance_points(B,N);
	d3=distance_points(C,D);
	if(!IS_ZERO(d1-d2)||!IS_ZERO(d1-d3))
	{
		return 0;
	}
	d1=distance_points(M,N);
	d2=distance_points(D,E);
	if(!IS_ZERO(d1-d2))
	{
		return 0;
	}
	return 1;
}
void level0012_init(void)
{
	add_point(180.301,250.520,0,'A');
	add_point(320.836,250.519,0,'B');
	add_point(340.314,169.420,0,'C');
	add_point(245.925,202.097,0,'D');
	add_line(180.301,250.520,320.836,250.519,0);
	add_line(180.301,250.520,340.314,169.420,0);
}
int level0012_check(void)
{
	struct point *A,*B,*C,*D,*M,*N;
	double c,d1,d2;
	A=point_by_label('A');
	B=point_by_label('B');
	C=point_by_label('C');
	D=point_by_label('D');
	M=point_by_label('M');
	N=point_by_label('N');
	if(A==NULL||B==NULL||C==NULL||D==NULL||M==NULL||N==NULL)
	{
		return 0;
	}
	c=cos_angle_points(A,B,M,N);
	if(!IS_ZERO(c))
	{
		return 0;
	}
	c=cos_angle_points(A,B,A,N);
	if(!IS_ZERO(c*c-1.0))
	{
		return 0;
	}
	c=cos_angle_points(A,C,A,M);
	if(!IS_ZERO(c*c-1.0))
	{
		return 0;
	}
	d1=distance_points(D,M);
	d2=distance_points(M,N);
	if(!IS_ZERO(d1-d2))
	{
		return 0;
	}
	return 1;
}
void level0013_init(void)
{
	add_point(130.301,250.520,0,'A');
	add_point(320.836,250.519,0,'B');
	add_point(340.314,129.420,0,'C');
	add_point(245.925,202.097,0,'D');
	add_line(130.301,250.520,320.836,250.519,0);
	add_line(130.301,250.520,340.314,129.420,0);
}
int level0013_check(void)
{
	struct point *A,*B,*C,*D,*M,*N,*P;
	double c,d1,d2,d3,d4;
	A=point_by_label('A');
	B=point_by_label('B');
	C=point_by_label('C');
	D=point_by_label('D');
	M=point_by_label('M');
	N=point_by_label('N');
	P=point_by_label('P');
	if(A==NULL||B==NULL||C==NULL||D==NULL||M==NULL||N==NULL||P==NULL)
	{
		return 0;
	}
	c=cos_angle_points(A,B,A,N);
	if(!IS_ZERO(c*c-1.0))
	{
		return 0;
	}
	c=cos_angle_points(A,B,A,P);
	if(!IS_ZERO(c*c-1.0))
	{
		return 0;
	}
	c=cos_angle_points(A,C,A,M);
	if(!IS_ZERO(c*c-1.0))
	{
		return 0;
	}
	d1=distance_points(D,M);
	d2=distance_points(M,N);
	d3=distance_points(M,P);
	d4=distance_points(N,P);
	if(!IS_ZERO(d1-d2)||!IS_ZERO(d1-d3)||!IS_ZERO(d1-d4))
	{
		return 0;
	}
	return 1;
}
void level0014_init(void)
{
	add_point(130.301,250.520,0,'A');
	add_point(320.836,250.519,0,'B');
	add_point(210.314,219.420,0,'C');
	add_point(272.925,232.097,0,'D');
	add_point(350.642,450.532,0,'M');
	add_point(435.637,450.532,0,'N');
	add_line(130.301,250.520,320.836,250.519,0);
}
int level0014_check(void)
{
	struct point *A,*B,*C,*D,*M,*N,*P;
	double c,d1,d2,d3;
	A=point_by_label('A');
	B=point_by_label('B');
	C=point_by_label('C');
	D=point_by_label('D');
	M=point_by_label('M');
	N=point_by_label('N');
	P=point_by_label('P');
	if(A==NULL||B==NULL||C==NULL||D==NULL||M==NULL||N==NULL||P==NULL)
	{
		return 0;
	}
	c=cos_angle_points(A,B,A,P);
	if(!IS_ZERO(c*c-1.0))
	{
		return 0;
	}
	d1=distance_points(M,N);
	d2=distance_points(C,P);
	d3=distance_points(D,P);
	if(!IS_ZERO(d2+d3-d1))
	{
		return 0;
	}
	return 1;
}
void levels_init(void)
{
	level_add(level0002_init,level0002_check,"Find a point C such\nthat AB = BC and angle\nABC = 180 degrees.");
	level_add(level0001_init,level0001_check,"Find a point C such\nthat AB = AC = BC.");
	level_add(level0004_init,level0004_check,"Find a point D such\nthat C, D are symmetric\nabout the line AB.");
	level_add(level0005_init,level0005_check,"Find a point D on the\nline AB such that CD\nis perpendicular to the\nline AB.");
	level_add(level0003_init,level0003_check,"Find a point C such\nthat C is the midpoint\nof the segment AB.");
	level_add(level0006_init,level0006_check,"Construct a line\nthrough the point C\nthat is parallel to the\nline AB.");
	level_add(level0007_init,level0007_check,"Find a point E on the\nline AB such that angle\nAEC = angle AED");
	level_add(level0008_init,level0008_check,"Find a point E on the\nline AB such that angle\nAEC + angle AED = 180\ndegrees.");
	level_add(level0009_init,level0009_check,"Construct the bisector\nof angle BAC.");
	level_add(level000a_init,level000a_check,"Find a point C such\nthat AC = AB and angle\nBAC = 30 degrees.");
	level_add(level000b_init,level000b_check,"Find a point D such\nthat AD = BD = CD.");
	level_add(level000c_init,level000c_check,"Find a point E on the\nline CD such that angle\nAEB = 90 degrees.");
	level_add(level000d_init,level000d_check,"Find a point D on the\nsegment AB such that\nAB * AD = AC * AC.");
	level_add(level000e_init,level000e_check,"Find a point D such\nthat angle BAD = angle\nCAD and angle ABD =\nangle ADC.");
	level_add(level000f_init,level000f_check,"Find a point E on the\nline AD such that angle\nABE = angle AEC.");
	level_add(level0010_init,level0010_check,"Find points M, N such\nthat AM = BN = CD, MN =\nDE, and angle BAM +\nangle ABN = 120 degrees.");
	level_add(level0011_init,level0011_check,"Find points M, N such\nthat AM = BN = CD, MN =\nDE, and angle BAM +\nangle ABN = 150 degrees.");
	level_add(level0012_init,level0012_check,"Find a point M on the\nline AC and a point N\non the line AB such that\nMN, AB are perpendicular\nand MD = MN.");
	level_add(level0013_init,level0013_check,"Find a point M on the\nline AC and points N,\nP on the line AB such\nthat MD = MN = MP = NP.");
	level_add(level0014_init,level0014_check,"Find a point P on the\nline AB such that\nCP + DP = MN.");
}