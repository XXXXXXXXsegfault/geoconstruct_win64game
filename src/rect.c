#ifndef _RECT_C_
#define _RECT_C_

void w4_sse(unsigned int *buf,unsigned int val,unsigned long blocks);
asm "@w4_sse"
asm "mov 8(%rsp),%rax"
asm "mov 24(%rsp),%rcx"
asm "movss 16(%rsp),%xmm0"
asm "shufps $0,%xmm0,%xmm0"
asm "@_w4_sse_loop"
asm "movups %xmm0,(%rax)"
asm "movups %xmm0,16(%rax)"
asm "movups %xmm0,32(%rax)"
asm "movups %xmm0,48(%rax)"
asm "movups %xmm0,64(%rax)"
asm "movups %xmm0,80(%rax)"
asm "movups %xmm0,96(%rax)"
asm "movups %xmm0,112(%rax)"
asm "add $128,%rax"
asm "dec %rcx"
asm "jne @_w4_sse_loop"
asm "ret"
void w4(unsigned int *buf,unsigned int val,unsigned long n)
{
	unsigned long xval,n1;
	xval=val;
	xval=xval<<32|val;
	if(n>=32)
	{
		w4_sse(buf,val,n>>5);
		buf+=n&0xffffffffffffffe0;
		n&=31;
	}
	while(n>=8)
	{
		((unsigned long *)buf)[0]=xval;
		((unsigned long *)buf)[1]=xval;
		((unsigned long *)buf)[2]=xval;
		((unsigned long *)buf)[3]=xval;
		buf+=8;
		n-=8;
	}
	if(n&4)
	{
		buf[0]=val;
		buf[1]=val;
		buf[2]=val;
		buf[3]=val;
		buf+=4;
	}
	if(n&2)
	{
		buf[0]=val;
		buf[1]=val;
		buf+=2;
	}
	if(n&1)
	{
		buf[0]=val;
	}
}
void rect(unsigned int *dst,int dstw,int dsth,int rect_x,int rect_y,int rect_w,int rect_h,unsigned int color)
{
	int off;
	if(rect_x<0)
	{
		rect_w+=rect_x;
		rect_x=0;
	}
	if(rect_y<0)
	{
		rect_h+=rect_y;
		rect_y=0;
	}
	if(rect_x+rect_w>dstw)
	{
		rect_w=dstw-rect_x;
	}
	if(rect_y+rect_h>dsth)
	{
		rect_h=dsth-rect_y;
	}
	if(rect_w<=0||rect_h<=0)
	{
		return;
	}
	off=rect_y*dstw+rect_x;
	do
	{
		w4(dst+off,color,rect_w);
		off+=dstw;
		--rect_h;
	}
	while(rect_h);
}
#endif
