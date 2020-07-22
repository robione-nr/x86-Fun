void Laplace(BYTE *src, BYTE *dest, int width, int height) {
   int iSum,iFinal,x,y,xlim,ylim,width_2x;
   BYTE *pbySrcOffset,*pbyDestOffset,*bySrcI;
   int i;

   width_2x = width << 1;
   xlim = width - 2;
   ylim = height - 2;

   for(y = 2,pbyDestOffset = dest + (width<<1)+2,pbySrcOffset = src + (width<<1)+2;
      y<ylim;
      ++y,pbyDestOffset+=4,pbySrcOffset+=4) {

      iSum = 0;
      iSum -= *(pbySrcOffset-2) + *(pbySrcOffset-1) + *(pbySrcOffset+2) + *(pbySrcOffset+1) - (24 * (*pbySrcOffset));

      for(i=-2; i<=2; i++) {
         bySrcI = pbySrcOffset + i;
         iSum -= (*(bySrcI - width_2x)) + (*(bySrcI - width))
             + (*(bySrcI + width)) + (*(bySrcI + width_2x));
      }

      iFinal = iSum;
      if(iFinal > 255) iFinal = 255;
      if(iFinal < 0) iFinal = 0;

      *(pbyDestOffset) = (unsigned char)iFinal;
      pbyDestOffset++;
      pbySrcOffset++;

      for(x = 3;x<xlim;pbySrcOffset++,pbyDestOffset++,x++) {
         pbySrcOffset -= 3;
         iSum += *(pbySrcOffset - width_2x) - *(pbySrcOffset - width_2x + 5)
               + *(pbySrcOffset - width) - *(pbySrcOffset - width + 5)
               + *(pbySrcOffset) - *(pbySrcOffset + 5)
               + *(pbySrcOffset + width) - *(pbySrcOffset + width + 5)
               + *(pbySrcOffset + width_2x) - *(pbySrcOffset + width_2x + 5);

         pbySrcOffset += 3;
         iSum += (25 * (*pbySrcOffset)) - (25 * (*(pbySrcOffset-1)));

         iFinal = iSum;
         if(iFinal > 255) iFinal = 255;
         if(iFinal < 0) iFinal = 0;

         *(pbyDestOffset) = (unsigned char)iFinal;
      }
   }
}