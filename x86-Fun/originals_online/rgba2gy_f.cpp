void GreyScale(BYTE *src, BYTE *dest, int nPixels) {
	int i = 0;
	nPixels<<=2;

	for(;i<nPixels;i+=4) 
		dest[i>>2] = src[i] * 0.11f + src[i+1] * 0.59f + src[i+2] * 0.30f;
}
