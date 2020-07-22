// _Vector.cpp: implementation of the Vector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "_Vector.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


fVector::fVector(const __m128 *otherData,int nElements)
{m_iElements = nElements; memcpya(m_pdata,otherData,nElements);}

fVector::fVector(const fVector &otherVector):m_pdata(NULL) {
   Resize(otherVector.m_iElements);
   memcpya(m_pdata,otherVector.m_pdata,otherVector.m_iElements);
}

fVector::fVector(const float *pfArray,int nFloats) {
   if(nFloats&0x03)
      nFloats += 4;
   nFloats >>= 2;

   Resize(nFloats);
   memcpy(m_pdata,pfArray,nFloats);
}

fVector::fVector(int nFloats):m_pdata(NULL), m_iElements(0) {
   if(nFloats&0x03)
      nFloats += 4;
   nFloats >>= 2;

   Resize(nFloats);
   memseta(m_pdata,0.f,nFloats);
}

bool fVector::operator == (const fVector &otherVector) const {
   assert(m_iElements == otherVector.m_iElements && "fVector::operator == size mismatch");
   __asm {
      mov esi,[ebp-4]      //[this].m_pdata
      mov edi,[ecx]      //otherVector.m_pdata
      mov ecx,[ecx+4]      //otherVector.m_iElements
      mov esi,[esi]      //this is pushed on stack... normally in ECX
      mov edx,ecx         //&otherVector is now in ECX
      xor eax,eax
      xor ebx,ebx
      shl ecx,4

      test dl,1
      je _even

      movaps xmm0,[edi]
      pcmpeqd xmm0,[esi]
      add ebx,16
      movmskps eax,xmm0
      xor eax,0x0f
      setz al
      jnz _end

_even:
      cmp ecx,ebx
      je _end
      movaps xmm0,[edi+ebx]
      movaps xmm1,[edi+ebx+16]
      pcmpeqd xmm0,[esi+ebx]
      pcmpeqd xmm1,[esi+ebx+16]
      movmskps eax,xmm0
      movmskps edx,xmm1
      add ebx,32
      xor eax,0x0f
      xor edx,0x0f
      or   eax,edx
      setz al
      jnz _end
      jmp _even
_end:
   }
}

void fVector::Add(const fVector &otherVector,fVector *result) const {
   assert(m_iElements == otherVector.m_iElements && "fVector::operator += size mismatch");
   __asm {
      mov eax,result
      mov esi,[ecx]      //m_pdata
      mov edi,[eax]
      mov eax,[ecx+4]      //m_iElements
      mov ecx,[otherVector].m_pdata
      xor ebx,ebx
      mov edx,eax
      mov ecx,[ecx]
      shl eax,4

      test dl,1
      je _even

      movaps xmm0,[esi]
      addps xmm0,[edi]
      add ebx,16
      movaps [edi],xmm0

_even:
      cmp eax,ebx
      je _end
      movaps xmm0,[esi+ebx]
      movaps xmm1,[esi+ebx+16]
      addps xmm0,[edi+ebx]
      addps xmm1,[edi+ebx+16]
      movaps [edi+ebx],xmm0
      movaps [edi+ebx+16],xmm1
      add ebx,32
      jmp _even
_end:
   }
}

void fVector::Subtract(const fVector &otherVector,fVector *result) const {
   assert(m_iElements == otherVector.m_iElements && "fVector::operator -= size mismatch");
   __asm {
      mov eax,result
      mov esi,[ecx]      //m_pdata
      mov edi,[eax]
      mov eax,[ecx+4]      //m_iElements
      mov ecx,[otherVector].m_pdata
      xor ebx,ebx
      mov edx,eax
      mov ecx,[ecx]
      shl eax,4

      test dl,1
      je _even

      movaps xmm0,[esi]
      subps xmm0,[ecx]
      add ebx,16
      movaps [edi],xmm0

_even:
      cmp eax,ebx
      je _end
      movaps xmm0,[esi+ebx]
      movaps xmm1,[esi+ebx+16]
      subps xmm0,[ecx+ebx]
      subps xmm1,[ecx+ebx+16]
      movaps [edi+ebx],xmm0
      movaps [edi+ebx+16],xmm1
      add ebx,32
      jmp _even
_end:
   }
}

void fVector::Negate(fVector *result) {
   assert(result->m_iElements == this->m_iElements && "fVector::Negate() size mismatch");
   __asm {
      mov eax,result
      mov esi,[ecx]
      mov edi,[eax]
      pcmpeqd xmm7,xmm7   
      mov eax,[ecx+4]      //m_iElements
      xor ebx,ebx
      mov edx,eax
      pslld xmm7,31
      shl eax,4

      test dl,1
      je _even

      movaps xmm0,xmm7
      pxor xmm0,[esi]
      add ebx,16
      movaps [edi],xmm0

_even:
      cmp eax,ebx
      je _end
      movaps xmm0,xmm7
      movaps xmm1,xmm7
      pxor xmm0,[esi+ebx]
      pxor xmm1,[esi+ebx+16]
      movaps [edi+ebx],xmm0
      movaps [edi+ebx+16],xmm1
      add ebx,32
      jmp _even
_end:
   }
}

void fVector::Multiply(const float scalar,fVector *result) const {
   assert(result->m_iElements == this->m_iElements && "fVector::Multiply(scalar) size mismatch");
   __asm {
      mov eax,result
      mov esi,[ecx]      //m_pdata
      mov edi,[eax]
      mov eax,[ecx+4]      //m_iElements
      movss xmm7,scalar
      xor ebx,ebx
      mov edx,eax
      mov ecx,[ecx]
      pshufd xmm7,xmm7,0
      shl eax,4      

      test dl,1
      je _even

      movaps xmm0,[esi]
      mulps xmm0,xmm7
      add ebx,16
      movaps [edi],xmm0

_even:
      cmp eax,ebx
      je _end
      movaps xmm0,[esi+ebx]
      movaps xmm1,[esi+ebx+16]
      mulps xmm0,xmm7
      mulps xmm1,xmm7
      movaps [edi+ebx],xmm0
      movaps [edi+ebx+16],xmm1
      add ebx,32
      jmp _even
_end:
   }
}

void fVector::Multiply(const fVector &otherVector,fVector *result) const {
   assert(result->m_iElements == this->m_iElements && "fVector::Multiply(vec) size mismatch");
   __asm {
      mov eax,result
      mov esi,[ecx]      //m_pdata
      mov edi,[eax]
      mov eax,[ecx+4]      //m_iElements
      mov ecx,[otherVector].m_pdata
      xor ebx,ebx
      mov edx,eax
      mov ecx,[ecx]
      shl eax,4

      test dl,1
      je _even

      movaps xmm0,[edi]
      mulps xmm0,[esi]
      add ebx,16
      movaps [edi],xmm0

_even:
      cmp eax,ebx
      je _end
      movaps xmm0,[edi+ebx]
      movaps xmm1,[edi+ebx+16]
      mulps xmm0,[esi+ebx]
      mulps xmm1,[esi+ebx+16]
      movaps [edi+ebx],xmm0
      movaps [edi+ebx+16],xmm1
      add ebx,32
      jmp _even
_end:
   }
}

float fVector::DotProduct(const fVector &otherVector) const   {
   __m128 sqr,sum;
   int i;

   sum = _mm_setzero_ps();
   for(i=0;i<m_iElements;++i) {
      sqr = _mm_mul_ps(*(m_pdata+i),*(otherVector.m_pdata+i));
      sum = _mm_add_ps(sum,sqr);
   }
   
   *((float *)&sum) += *(((float *)&sum)+1) + *(((float *)&sum)+2) + *(((float *)&sum)+3);
   return *((float *)&sum);
}

float fVector::Length(void) {
   __m128 sqr,sum;
   int i;

   sum = _mm_setzero_ps();
   for(i=0;i<m_iElements;++i) {
      sqr = _mm_mul_ps(*(m_pdata+i),*(m_pdata+i));
      sum = _mm_add_ps(sum,sqr);
   }
   
   *((float *)&sum) += *(((float *)&sum)+1) + *(((float *)&sum)+2) + *(((float *)&sum)+3);
   sum = _mm_sqrt_ss(sum);

   return *((float *)&sum);
}

void fVector::Normalize(void) {
   Multiply(1.f/Length(),this);
}

bool fVector::Resize(int nBlocks) {
   __m128 *p = (__m128*) _aligned_malloc(nBlocks<<4,16);
   int delta;

   if(!p) return false;

   delta = nBlocks - this->m_iElements;

   if(m_pdata) {
      memcpya(p,m_pdata,nBlocks);
      _aligned_free(m_pdata);
   }
   if(delta > 0)
      memseta(p+m_iElements,0.f,delta);
   this->m_iElements = nBlocks;

   m_pdata = p;
   return true;
}

void fVector::memcpya(__m128 *dest, const __m128 *src,unsigned int uiElem) {
   __asm {
      mov ecx,uiElem
      mov edi,dest
      shl ecx,4
      mov esi,src
      sub ecx,16

_loop:
      movaps xmm0,[esi+ecx]
      movaps [edi+ecx],xmm0
      sub ecx,16
      jns _loop
   }
}

void fVector::memseta(__m128 *dest,float f,unsigned int uiSize) {
   __asm {
      movss xmm0,f
      mov ecx,uiSize
      mov edi,dest
      shl ecx,4
      pshufd xmm0,xmm0,0
      sub ecx,16

_loop:
      movaps [edi+ecx],xmm0
      sub ecx,16
      jns _loop
   }
}