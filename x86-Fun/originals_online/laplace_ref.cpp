void Laplace(BYTE *src, BYTE *dest, int width, int height) {
	int X,Y,I,J,SUM;
	int MASK[5][5] = {{-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1},
		{-1,-1,24,-1,-1},
		{-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1}};

 	for(Y=0; Y<=(height-1); Y++)  {
		for(X=0; X<=(width-1); X++)  {
			SUM = 0;

			if(Y==0 || Y==1 || Y==height-2 || Y==height-1)
				SUM = 0;
			else if(X==0 || X==1 || X==width-2 || X==width-1)
				SUM = 0;
			else   {
				for(I=-2; I<=2; I++)  {
				for(J=-2; J<=2; J++)  {
					SUM = SUM + (int)( (*(src + X + I + (Y + J)*width)) * MASK[I+2][J+2]);

				}
				}
			}
			if(SUM>255)  SUM=255;
			if(SUM<0)    SUM=0;

			*(dest + X + Y*width) = 255 - (unsigned char)(SUM);
		}
	}
}