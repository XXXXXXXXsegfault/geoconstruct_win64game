int current_y;
void p_num_with_square(int n,int x,int y)
{
	char buf[20];
	int digits,size,len;
	rect(pbuf,WINW,WINH,x,y,120,120,0xffff50);
	buf[0]=0;
	sprinti(buf,n,1);
	digits=strlen(buf);
	if(digits==1)
	{
		size=7;
	}
	else
	{
		size=12/digits;
	}
	len=size*8*digits;
	p_str_large(size,buf,digits,x+(120-len)/2,y+(120-16*size)/2,0x0000ff,pbuf,WINW,WINH);
}
void mode1_paint(void)
{
	int l,x,y;
	p_str("Select the level you want to play (press <UP> <DOWN> to scroll)",63,(WINW-504)/2,4,0xc040,pbuf,WINW,WINH);
	l=current_y*12+1;
	y=40;
	while(y<490)
	{
		x=40;
		while(x<800)
		{
			if(l>count_levels)
			{
				return;
			}
			p_num_with_square(l,x,y);
			++l;
			x+=200;
		}
		y+=150;
	}
}
void mode2_init(void);
void mode1_click(int X,int Y)
{
	int x,y,l;
	l=current_y*12+1;
	y=40;
	while(y<490)
	{
		x=40;
		while(x<800)
		{
			if(l>count_levels)
			{
				
				return;
			}
			if(X>=x&&X<x+120&&Y>=y&&Y<y+120)
			{
				current_level=l;
				mode=2;
				mode2_init();
				InvalidateRect(hwnd,NULL,0);
				return;
			}
			++l;
			x+=200;
		}
		y+=150;
	}
}
void mode1_key(int keycode)
{
	if(keycode==38) // UP
	{
		if(current_y)
		{
			--current_y;
			InvalidateRect(hwnd,NULL,0);
		}
	}
	else if(keycode==40) // DOWN
	{
		if(current_y*12+13<=count_levels)
		{
			++current_y;
			InvalidateRect(hwnd,NULL,0);
		}
	}
	else if(keycode==27) // ESC
	{
		mode=0;
		InvalidateRect(hwnd,NULL,0);
	}
}