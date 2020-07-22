void Sobel(BYTE *src, BYTE *dest, int width, int height) {
    int x,y,xlim = width - 1,ylim = height - 1,iSumX,iSumY;
    BYTE *pbySrcOffset,*pbyDestOffset;

    y = 1;
    pbyDestOffset = dest + width + 1;
    pbySrcOffset = src + width + 1;

    for(;y<ylim; ++y, pbyDestOffset+=2, pbySrcOffset+=2) {
        for(x = 1; x<xlim; pbySrcOffset++, pbyDestOffset++, x++) {
            iSumX = (*(pbySrcOffset - width + 1)) - (*(pbySrcOffset - width - 1)) +
                (*(pbySrcOffset + width + 1)) - (*(pbySrcOffset + width - 1)) +
                (*(pbySrcOffset + 1) << 1) - (*(pbySrcOffset - 1) << 1);
            iSumY = (*(pbySrcOffset - width + 1)) + (*(pbySrcOffset - width - 1)) -
                (*(pbySrcOffset + width + 1)) - (*(pbySrcOffset + width - 1)) +
                (*(pbySrcOffset - width) << 1) - (*(pbySrcOffset + width) << 1);


            iSumY = (iSumX<0?-iSumX:iSumX) + (iSumY<0?-iSumY:iSumY);
            if(iSumY > 255) iSumY = 255;

            *(pbyDestOffset) = (unsigned char)iSumY;
        }
    }
}