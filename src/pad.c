void paint_point(double x,double y,double r,unsigned int color)
{
	int x_,y_,r_;
	int x1,y1,x2,y2;
	double x1_,y1_;
	x_=(int)x;
	y_=(int)y;
	r_=(int)r+2;
	y1=-r_;
	while(y1<=r_)
	{
		x1=-r_;
		while(x1<=r_)
		{
			x1_=(double)(x1+x_)-x;
			y1_=(double)(y1+y_)-y;
			x2=x_+x1;
			y2=y_+y1;
			if(x1_*x1_+y1_*y1_<=r*r&&x2>=0&&x2<WINW&&y2>=0&&y2<WINH)
			{
				pbuf[WINW*y2+x2]=color;
			}
			++x1;
		}
		++y1;
	}
}
void paint_line(double x1,double y1,double x2,double y2,double r,unsigned int color)
{
	double distance;
	double vx,vy;
	double x,y;
	vx=x2-x1;
	vy=y2-y1;
	distance=sqrt(vx*vx+vy*vy)*2.0;
	if(IS_ZERO(distance))
	{
		return;
	}
	vx/=distance;
	vy/=distance;
	x=x1;
	y=y1;
	while(x>=0.0&&x<=(double)WINW&&y>=0.0&&y<=(double)WINH)
	{
		paint_point(x,y,r,color);
		x+=vx;
		y+=vy;
	}
	x=x1-vx;
	y=y1-vx;
	while(x>=0.0&&x<=(double)WINW&&y>=0.0&&y<=(double)WINH)
	{
		paint_point(x,y,r,color);
		x-=vx;
		y-=vy;
	}
}
void paint_circle(double x,double y,double radius,double r,unsigned int color)
{
	double angle,a;
	angle=0.5/radius;
	a=0.0;
	while(a<=2.0*PI+0.1)
	{
		paint_point(x+radius*cos(a),y+radius*sin(a),r,color);
		a+=angle;
	}
}
struct point
{
	double x;
	double y;
	short label;
	short can_erase;
	int color;
	struct point *next;
} *point_list;
struct line
{
	double x1;
	double y1;
	double x2;
	double y2;
	long can_erase;
	struct line *next;
} *line_list;
struct circle
{
	double x;
	double y;
	double r;
	long can_erase;
	struct circle *next;
} *circle_list;
void paint_pad(void)
{
	struct point *p;
	struct line *l;
	struct circle *c;
	l=line_list;
	while(l)
	{
		paint_line(l->x1,l->y1,l->x2,l->y2,2.0,0x0000ff);
		l=l->next;
	}
	c=circle_list;
	while(c)
	{
		paint_circle(c->x,c->y,c->r,2.0,0x0000ff);
		c=c->next;
	}
	p=point_list;
	while(p)
	{
		if(p->color==0xff0000)
		{
			paint_point(p->x,p->y,4.0,p->color);
		}
		p=p->next;
	}
	p=point_list;
	while(p)
	{
		if(p->color!=0xff0000)
		{
			paint_point(p->x,p->y,4.0,p->color);
		}
		p=p->next;
	}
	p=point_list;
	while(p)
	{
		if(p->label)
		{
			p_char(p->label,(int)p->x-4,(int)p->y-20,0x00c040,pbuf,WINW,WINH);
		}
		p=p->next;
	}
}
double distance_to_line(struct line *l,double x,double y)
{
	double vx1,vy1;
	double vx2,vy2;
	double cross;
	vx1=x-l->x1;
	vy1=y-l->y1;
	vx2=l->x2-l->x1;
	vy2=l->y2-l->y1;
	cross=vx1*vy2-vx2*vy1;
	if(cross<0.0)
	{
		cross=-cross;
	}
	return cross/sqrt(vx2*vx2+vy2*vy2);
}
double distance_to_circle(struct circle *c,double x,double y)
{
	double vx,vy,d;
	vx=x-c->x;
	vy=y-c->y;
	d=sqrt(vx*vx+vy*vy)-c->r;
	if(d<0.0)
	{
		d=-d;
	}
	return d;
}
void add_point(double x,double y,int can_erase,int label)
{
	struct point *p;
	if(x<0.0||y<0.0||x>(double)WINH||y>(double)WINH)
	{
		return;
	}
	p=point_list;
	while(p)
	{
		if(IS_ZERO(p->x-x)&&IS_ZERO(p->y-y))
		{
			return;
		}
		p=p->next;
	}
	p=xmalloc(sizeof(*p));
	p->x=x;
	p->y=y;
	p->can_erase=can_erase;
	p->label=label;
	p->color=0xff0000;
	p->next=point_list;
	point_list=p;
}
void add_line(double x1,double y1,double x2,double y2,int can_erase)
{
	struct line *l;
	l=line_list;
	if(IS_ZERO(x1-x2)&&IS_ZERO(y1-y2))
	{
		return;
	}
	while(l)
	{
		if(IS_ZERO(distance_to_line(l,x1,y1))&&IS_ZERO(distance_to_line(l,x2,y2)))
		{
			return;
		}
		l=l->next;
	}
	l=xmalloc(sizeof(*l));
	l->x1=x1;
	l->y1=y1;
	l->x2=x2;
	l->y2=y2;
	l->can_erase=can_erase;
	l->next=line_list;
	line_list=l;
}
void add_circle(double x,double y,double r,int can_erase)
{
	struct circle *c;
	c=circle_list;
	if(r<0.0||IS_ZERO(r))
	{
		return;
	}
	while(c)
	{
		if(IS_ZERO(c->x-x)&&IS_ZERO(c->y-y)&&IS_ZERO(c->r-r))
		{
			return;
		}
		c=c->next;
	}
	c=xmalloc(sizeof(*c));
	c->x=x;
	c->y=y;
	c->r=r;
	c->can_erase=can_erase;
	c->next=circle_list;
	circle_list=c;
}
struct point *point_by_label(int label)
{
	struct point *p;
	p=point_list;
	while(p)
	{
		if(p->label==label)
		{
			return p;
		}
		p=p->next;
	}
	return NULL;
}
void clear_pad(void)
{
	struct point *p;
	struct line *l;
	struct circle *c;
	while(p=point_list)
	{
		point_list=p->next;
		free(p);
	}
	while(l=line_list)
	{
		line_list=l->next;
		free(l);
	}
	while(c=circle_list)
	{
		circle_list=c->next;
		free(c);
	}
}

int intersection_ll(struct line *l1,struct line *l2,double *x,double *y)
{
	double vx1,vy1;
	double vx2,vy2;
	double vx3,vy3;
	double a,s1;
	vx1=l1->x2-l1->x1;
	vy1=l1->y2-l1->y1;
	vx2=l2->x1-l2->x2;
	vy2=l2->y1-l2->y2;
	vx3=l2->x1-l1->x1;
	vy3=l2->y1-l1->y1;
	a=vx1*vy2-vx2*vy1;
	if(IS_ZERO(a))
	{
		return 0;
	}
	s1=(vx3*vy2-vx2*vy3)/a;
	*x=l1->x1+vx1*s1;
	*y=l1->y1+vy1*s1;
	return 1;
}
int intersection_lc(struct line *l,struct circle *c,double *x,double *y)
{
	double vx1,vy1,vx2,vy2;
	double A,B,C,delta,n1,n2;
	int ret;
	vx1=l->x1-c->x;
	vy1=l->y1-c->y;
	vx2=l->x2-l->x1;
	vy2=l->y2-l->y1;
	A=vx2*vx2+vy2*vy2;
	B=2.0*(vx1*vx2+vy1*vy2);
	C=vx1*vx1+vy1*vy1-c->r*c->r;
	delta=B*B-4.0*A*C;
	if(IS_ZERO(delta))
	{
		n1=-B/(2.0*A);
		ret=1;
	}
	else if(delta<0.0)
	{
		return 0;
	}
	else
	{
		n1=-(B+sqrt(delta))/(2.0*A);
		n2=-(B-sqrt(delta))/(2.0*A);
		ret=2;
	}
	*x=l->x1+vx2*n1;
	*y=l->y1+vy2*n1;
	if(ret==2)
	{
		x[1]=l->x1+vx2*n2;
		y[1]=l->y1+vy2*n2;
	}
	return ret;
}
int intersection_cc(struct circle *c1,struct circle *c2,double *x,double *y)
{
	double d,cosA,cosB,sinA,sinB;
	double S1,C1,S2,C2;
	d=sqrt((c2->x-c1->x)*(c2->x-c1->x)+(c2->y-c1->y)*(c2->y-c1->y));
	if(IS_ZERO(d))
	{
		return 0;
	}
	cosA=(d*d+c1->r*c1->r-c2->r*c2->r)/(2.0*d*c1->r);
	if(IS_ZERO(cosA-1.0))
	{
		*x=c1->x+(c2->x-c1->x)*c1->r/d;
		*y=c1->y+(c2->y-c1->y)*c1->r/d;
		return 1;
	}
	else if(IS_ZERO(cosA+1.0))
	{
		*x=c1->x-(c2->x-c1->x)*c1->r/d;
		*y=c1->y-(c2->y-c1->y)*c1->r/d;
		return 1;
	}
	else if(cosA>1.0||cosA<-1.0)
	{
		return 0;
	}
	else
	{
		sinA=sqrt(1.0-cosA*cosA);
		cosB=(c2->x-c1->x)/d;
		sinB=(c2->y-c1->y)/d;
		S1=sinB*cosA+sinA*cosB;
		C1=cosB*cosA-sinA*sinB;
		S2=sinB*cosA-sinA*cosB;
		C2=cosB*cosA+sinA*sinB;
		x[0]=c1->x+c1->r*C1;
		y[0]=c1->y+c1->r*S1;
		x[1]=c1->x+c1->r*C2;
		y[1]=c1->y+c1->r*S2;
		return 2;
	}
}