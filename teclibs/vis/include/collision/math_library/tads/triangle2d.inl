/**
* Modulo de implementacao dos metodos inline da classe TRIANGLE2D
*/


/**
* Construtores
*/
template <class Real> inline TRIANGLE2D<Real>::TRIANGLE2D(void)
{
}


template <class Real> inline TRIANGLE2D<Real>::TRIANGLE2D(const VECTOR2<Real>& v1,const VECTOR2<Real>& v2,const VECTOR2<Real>& v3):
V1(v1),V2(v2),V3(v3)

{	
}

template <class Real> inline TRIANGLE2D<Real>::TRIANGLE2D(const VECTOR2<Real>* Vertex ):
V1(Vertex[0]),V2(Vertex[1]),V3(Vertex[2])
{	
}

template <class Real> inline TRIANGLE2D<Real>::TRIANGLE2D(const Real* Vertex ):
V1(&Vertex[0]),V2(&Vertex[2]),V3(&Vertex[4])
{	
}

template <class Real> inline void TRIANGLE2D<Real>::Set_Triangle(const VECTOR2<Real>& v1,const VECTOR2<Real>& v2,const VECTOR2<Real>& v3)
{
	this->V1.Set(v1);
	this->V2.Set(v2);
	this->V3.Set(v3);
	return;
}

template <class Real> inline void TRIANGLE2D<Real>::Set_Triangle(const TRIANGLE2D<Real>& Triangle)
{
	this->V1.Set(Triangle.V1);
	this->V2.Set(Triangle.V2);
	this->V3.Set(Triangle.V3);
	return;
}
template <class Real> inline bool TRIANGLE2D<Real>::Is_Colinear(void)
{
	Real Area = this->Area();
	if(fabs(Area) < EPSILON)
		return(true);
	else
		return(false);
}

template <class Real> inline Real TRIANGLE2D<Real>::Area(void)
{
	Real Area = (this->V2.x - this->V1.x)*(this->V3.y - this->V1.y) - 
				(this->V3.x - this->V1.x)*(this->V2.y - this->V1.y);
    
	return(Area*(Real)0.5);
}

	

