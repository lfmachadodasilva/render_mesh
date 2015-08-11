/**
* Modulo de implementacao dos metodos inline da classe SEGMENT2D
*/

template <class Real> inline SEGMENT2D<Real>::SEGMENT2D(void)
{
}

template <class Real> inline SEGMENT2D<Real>::SEGMENT2D(const VECTOR2<Real>& A,const VECTOR2<Real>& B):
m_A(A),m_B(B)
{	
}


template <class Real> inline void SEGMENT2D<Real>::Set_New_Segment(const VECTOR2<Real>& A,const VECTOR2<Real>& B)
{
	this->m_A.Set(A);
	this->m_B.Set(B);
	return;
}
