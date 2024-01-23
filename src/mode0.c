void mode0_paint(void)
{
	double example_radius;
	example_radius=(double)(WINH/4);
	paint_circle((double)(WINW/2),(double)(WINH/2),example_radius,2.0,0x0000ff);
	paint_line((double)(WINW/2)-example_radius*0.6,(double)(WINH/2)+example_radius*0.8,
	(double)(WINW/2)-example_radius*2.2,(double)(WINH/2)-example_radius*0.4,2.0,0x0000ff);
	paint_line((double)(WINW/2)-example_radius*0.8,(double)(WINH/2)-example_radius*0.6,
	(double)(WINW/2)+example_radius*0.6,(double)(WINH/2)-example_radius*0.8,2.0,0x0000ff);

	paint_point((double)(WINW/2),(double)(WINH/2),4.0,0xff0000);
	paint_point((double)(WINW/2)-example_radius*0.6,(double)(WINH/2)+example_radius*0.8,4.0,0xff0000);
	paint_point((double)(WINW/2)-example_radius*0.8,(double)(WINH/2)-example_radius*0.6,4.0,0xff0000);
	paint_point((double)(WINW/2)+example_radius*0.6,(double)(WINH/2)-example_radius*0.8,4.0,0xff0000);
	paint_point((double)(WINW/2)-example_radius*2.2,(double)(WINH/2)-example_radius*0.4,4.0,0xff0000);
	p_str_large(4,"Geoconstruct",12,(WINW-384)/2,WINH/8-32,0x909000,pbuf,WINW,WINH);
	rect(pbuf,WINW,WINH,(WINW-80)/2,WINH-64-8,80,48,0xff0000);
	p_str_large(2,"Play",4,(WINW-64)/2,WINH-64,0xffffff,pbuf,WINW,WINH);
}
void mode0_click(int x,int y)
{
	int x1,y1;
	x1=x-(WINW-80)/2;
	y1=y-(WINH-64-8);
	if(x1>=0&&x1<80&&y1>=0&&y1<48)
	{
		mode=1;
		InvalidateRect(hwnd,NULL,0);
	}
}