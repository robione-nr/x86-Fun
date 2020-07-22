void GreyScale(BYTE *src, BYTE *dest, int nPixels) {
	int i = 0;
	nPixels<<=2;

	for(;i<nPixels;i+=4) 
		dest[i>>2] = (src[i] * 117 + src[i+1] * 601 + src[i+2] * 306) >> 10;
}