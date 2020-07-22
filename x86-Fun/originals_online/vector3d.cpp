// _Vector.h: interface for the Vector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VECTOR_H__7A676624_C99A_4949_9B72_DD1FAF904FA4__INCLUDED_)
#define AFX__VECTOR_H__7A676624_C99A_4949_9B72_DD1FAF904FA4__INCLUDED_

#include <assert.h>
#include <xmmintrin.h>

#if _MSVER > 1000
#pragma once
#endif // _MSVER > 1000

class fVector3D  
{
protected:
   fVector3D(const __m128 &otherData) 
   {m_data = otherData;}

   __declspec(align(16)) __m128 m_data;
public:
   fVector3D() 
   {m_data = _mm_setzero_ps();}

   fVector3D(const float f[3])
   {m_data = _mm_set_ps(0.f,f[2],f[1],f[0]);}

   fVector3D(const fVector3D &otherVector) 
   {m_data = otherVector.m_data;}

   fVector3D(const float x,const float y,const float z)
   {m_data = _mm_set_ps(0.f,z,y,x);}

   float &operator [] (const int i)
   {assert(i<3 && i>=0 && "Operator[]: Out of Bounds"); return *(((float *)&m_data)+i);}

   const float &operator [] (const int i) const
   {assert(i<3 && i>=0 && "Operator[]: Out of Bounds"); return *(((float *)&m_data)+i);}

   void operator = (const float f[3])
   {m_data = _mm_set_ps(0.f,f[2],f[1],f[0]);}

   void operator = (const float f)
   {m_data = _mm_set_ps(0.f,f,f,f);}

   void operator = (const fVector3D &otherVector)
   {m_data = _mm_load_ps((float *)&otherVector.m_data);}

   void operator += (const fVector3D &otherVector)
   {m_data = _mm_add_ps(m_data , otherVector.m_data);}

   void operator -= (const fVector3D &otherVector)
   {m_data = _mm_sub_ps(m_data , otherVector.m_data);}

   void operator *= (const fVector3D &otherVector)
   {m_data = _mm_mul_ps(m_data , otherVector.m_data);}

   void operator *= (const float scalar)   
   {m_data = _mm_mul_ps(m_data,_mm_load1_ps(&scalar));}

   void operator /= (const float scalar)
   {operator *=(1.f/scalar);}

   bool operator == (const float scalar) const
   {return (*((int *)&m_data)==*((int *)&scalar) &&
         *(((int *)&m_data)+1)==*((int *)&scalar) &&
         *(((int *)&m_data)+2)==*((int *)&scalar));}

   bool operator != (const float scalar) const
   {return !operator == (scalar);}


    bool operator == (const fVector3D &otherVector) const
   {
      __asm {
//       mov ecx,[this].m_data
         mov edx,[otherVector].m_data
         movaps xmm0,[ecx]
         pcmpeqd xmm0,[edx]
         movmskps eax,xmm0
         xor eax,0x0f
         setz al
      }
   }
   //{return (!(_mm_movemask_ps(_mm_cmpeq_epi32(m_data,otherVector.m_data))^0x0f));}

   bool operator != (const fVector3D &otherVector) const
   {return (!operator ==(otherVector));}

   fVector3D operator + (const fVector3D &otherVector) const
   {return fVector3D(_mm_add_ps(m_data,otherVector.m_data));}

   fVector3D operator - (const fVector3D &otherVector) const
   {return fVector3D(_mm_sub_ps(m_data,otherVector.m_data));}

   friend fVector3D operator - (const fVector3D &vector) {
      __declspec(align(16)) __m128 r;
      __asm {
         mov edi,[vector].m_data
         pcmpeqd xmm7,xmm7
         movaps xmm0,[edi]
         pslld xmm7,31
         pxor xmm0,xmm7
         movaps r,xmm0
      }
      return fVector3D(r);
   }
   //{return fVector3D(_mm_and_si128(vector.m_data,_mm_set1_epi32(0x7fffffff)));}

   /*My compiler is a bit dated and has inline SSE2 instructions
     but no instrinsics for them.... go figure.*/

   friend fVector3D operator * (const float scalar,const fVector3D &vector)
   {return fVector3D(_mm_mul_ps(vector.m_data,_mm_load1_ps(&scalar)));}

   fVector3D operator * (const float scalar) const
   {return fVector3D(_mm_mul_ps(m_data,_mm_load1_ps(&scalar)));}

   fVector3D operator / (const float scalar) const
   {return fVector3D(operator *(1.f/scalar));}

   float DotProduct(const fVector3D &otherVector) const {
      __m128 a;
      
      a = _mm_mul_ps(m_data,otherVector.m_data);
      return(*((float *)&a) + *(((float *)&a)+1) + *(((float *)&a)+2));
   }

   float Length(void) const {
      __m128 a;
      
      a = _mm_mul_ps(m_data,m_data);
      *((float *)&a) += *(((float *)&a)+1) + *(((float *)&a)+2);
      a = _mm_sqrt_ss(a);

      return *((float *)&a);
   }

   fVector3D CrossProduct(const fVector3D &otherVector) const {
      __m128 r;
      __asm {
//       mov ecx,[this].m_data
         mov edx,[otherVector].m_data

         pshufd xmm0,[ecx],11001001b
         pshufd xmm3,[edx],11001001b
         pshufd xmm2,xmm0,11001001b
         pshufd xmm1,xmm3,11001001b
         mulps xmm2,xmm3
         mulps xmm0,xmm1
         subps xmm0,xmm2

         movaps r,xmm0
      }
      return fVector3D(r);
   }

   void Normalize(void) {operator *=(1.0f/Length());}
};

class fVector
{
protected:
   fVector(const __m128 *otherData,int iSize);
   void memseta(__m128 *dest,float f,unsigned int uiSize);
   void memcpya(__m128 *dest, const __m128 *src,unsigned int uiElem);

   __m128 *m_pdata;
   int m_iElements;   //16-byte blocks

public:
   fVector(const fVector &otherVector);
   fVector():m_pdata(NULL), m_iElements(0) {}
   fVector(int nElements);
   fVector(const float *pfArray,int nFloats);
   ~fVector() {_aligned_free(m_pdata);}

   float &operator [] (const int i)
   {assert(i<(m_iElements<<2) && i>=0 && "fVector::Operator[]: Out of Bounds"); return *(((float *)m_pdata)+i);}

   const float &operator [] (const int i) const
   {assert(i<(m_iElements<<2) && i>=0 && "fVector::Operator[]: Out of Bounds"); return *(((float *)m_pdata)+i);}

   void Set(const float f,const int i)
   {assert(i>=0 && i<(m_iElements<<2) && "fVector::Set(): Out of Bounds"); *(((int *)m_pdata)+i) = *((int *)&f);}

   void operator = (const float f)
   {memseta(m_pdata,f,m_iElements);}

   void operator = (const fVector &otherVector) {
      if(m_iElements != otherVector.m_iElements) Resize(otherVector.m_iElements);
      memcpya(m_pdata,otherVector.m_pdata,otherVector.m_iElements);
   }

/* bool operator == (const float scalar) const;
   bool operator != (const float scalar) const
   {return !operator == (scalar);}
*/ bool operator == (const fVector &otherVector) const;
   bool operator != (const fVector &otherVector) const
   {return (!operator ==(otherVector));}

   void Add(const fVector &otherVector,fVector *result) const;
   void Subtract(const fVector &otherVector,fVector *result) const;
   void Negate(fVector *result);
   void Multiply(const float scalar,fVector *result) const;
   void Multiply(const fVector &otherVector,fVector *result) const;
   void Divide(const float scalar,fVector *result)
   {Multiply(1.f/scalar,result);}

   float DotProduct(const fVector &otherVector) const;
   float Length(void);
   void Normalize(void);

   bool Resize(int nBlocks);
   int Size(void) {return (m_iElements<<4);}
   int Count(void) {return (m_iElements<<2);}
   int Blocks(void) {return (m_iElements);}
};

#endif // !defined(AFX__VECTOR_H__7A676624_C99A_4949_9B72_DD1FAF904FA4__INCLUDED_)