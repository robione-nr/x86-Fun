void Sobel(BYTE *src, BYTE *dest, int width, int height) {
	int Y,X,J,I,sumY,sumX,SUM;
	int GX[3][3] = {{-1,-0,1},{-2,0,2},{-1,0,1}},
		GY[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};

	for(Y=0; Y<=(height-1); Y++)  {
	for(X=0; X<=(width-1); X++)  {
		sumX = 0;
		sumY = 0;

		if(Y==0 || Y==height-1)
			SUM = 0;
		else if(X==0 || X==width-1)
			SUM = 0;
		else {
			for(I=-1; I<=1; I++)  {
			for(J=-1; J<=1; J++)  {
				sumX = sumX + (int)( (*(src + X + I + (Y + J)*width)) * GX[I+1][J+1]);
			}
			}

			for(I=-1; I<=1; I++)  {
			for(J=-1; J<=1; J++)  {
				sumY = sumY + (int)( (*(src + X + I + (Y + J)*width)) * GY[I+1][J+1]);
			}
			}

			SUM = abs(sumX) + abs(sumY);
		}

		if(SUM>255) SUM=255;
		if(SUM<0) SUM=0;

		*(dest + X + Y*width) = 255 - (unsigned char)(SUM);
	}
	}
}