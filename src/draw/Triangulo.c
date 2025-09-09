#include "draw.h"



void draw_trian(int *xs,int *ys,uint32_t color)
{
	int i;
	for( i = 0; i < 3 ; i++)
	{
		draw_line(xs[i%3],ys[i%3],xs[(i+1)%3],ys[(i+1)%3],color);
	}
}

void ordenar_puntos(Triangulo *trian)
{
	Vec2 aux,ps[3] = {trian->p0,trian->p1,trian->p2};
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=i;j<3;j++)
		{
			if( ps[j].unpack.y < ps[i].unpack.y)
			{
				aux = ps[j];
				ps[j] = ps[i];
				ps[i] = aux;
			}
		}
	}
	trian->p0 = ps[0];
	trian->p1 = ps[1];
	trian->p2 = ps[2];	
}

void fill_flat_bottom(Vec2 p1,Vec2 p2, Vec2 c, uint32_t color)
{
		float mi = (p2.unpack.x-p1.unpack.x)/(p2.unpack.y-p1.unpack.y);
		float mf = (c.unpack.x-p1.unpack.x)/(c.unpack.y-p1.unpack.y);
		float xi = p1.unpack.x;
		float xf = p1.unpack.x;
		float y;
		//p1.y hasta c.y
		for(y = p1.unpack.y ; y <= c.unpack.y ; y++)
		{				
			draw_line(xi,y ,xf, y,color);
			xi += mi;
			xf += mf;
		}
}

void fill_flat_top(Vec2 p0,Vec2 p1, Vec2 p2, uint32_t color)
{
		float mi = (p2.unpack.x-p0.unpack.x)/(p2.unpack.y-p0.unpack.y);
		float mf = (p2.unpack.x-p1.unpack.x)/(p2.unpack.y-p1.unpack.y);
		float xi = p2.unpack.x;
		float xf = p2.unpack.x;
		float y;
		//p2.y hasta p1.y
		for(y = p2.unpack.y ; y >= p1.unpack.y ; y--)
		{				
			draw_line(xi,y ,xf, y,color);
			xi -= mi;
			xf -= mf;
		}
}

void fill_trian(Triangulo trian,uint32_t color)
{
	ordenar_puntos(&trian);
	if( trian.p1.unpack.y == trian.p2.unpack.y)
		fill_flat_bottom(trian.p0,trian.p1,trian.p2,color);		
	else if( trian.p0.unpack.y == trian.p1.unpack.y)
		fill_flat_top(trian.p0,trian.p1,trian.p2,color);
	else	
	{
		Vec2 c;
		c.unpack.y = trian.p1.unpack.y;
		c.unpack.x = trian.p1.unpack.y-trian.p0.unpack.y;
		c.unpack.x *= (trian.p2.unpack.x-trian.p0.unpack.x);
		c.unpack.x /= (trian.p2.unpack.y-trian.p0.unpack.y);
		c.unpack.x += trian.p0.unpack.x;
		fill_flat_bottom(trian.p0,trian.p1,c,color);
		fill_flat_top(trian.p1,c,trian.p2,color);
	}
}