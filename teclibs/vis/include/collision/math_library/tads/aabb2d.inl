/**
* Modulo de implementacao dos metodos inline da classe AABB2.
*/

/**
* Construtores
*/

template <class Real> inline AABB2D<Real>::AABB2D(void)
{
}

template <class Real> inline AABB2D<Real>::AABB2D(const VECTOR2<Real>& Min_Point,const VECTOR2<Real>& Max_Point)
{
	this->Min_Point.Set(Min_Point);
	this->Max_Point.Set(Max_Point);
}

template <class Real> inline AABB2D<Real>::AABB2D(const Real Min_x,const Real Max_x,const Real Min_y,const Real Max_y)
{
	this->Min_Point.Set(Min_x,Min_y);
	this->Max_Point.Set(Max_x,Max_y);
}

template <class Real> inline AABB2D<Real>::AABB2D(const Real* Min_Point,const Real* Max_Point)
{
	this->Min_Point.Set(Min_Point);
	this->Max_Point.Set(Max_Point);
}

template <class Real> inline AABB2D<Real>::AABB2D(const AABB2D<Real>& Box)
{
	this->Min_Point.Set(Box.Min_Point);
	this->Max_Point.Set(Box.Max_Point);
}


/**
* Metodos de Get
*/


template <class Real> inline VECTOR2<Real> AABB2D<Real>::Get_Center(void)const
{
	return(VECTOR2<Real>( (this->Min_Point.x + this->Max_Point.x)*0.5f,
						  (this->Min_Point.y + this->Max_Point.y)*0.5f));
}

template <class Real> inline  void AABB2D<Real>::Get_Extensions(Real& Extension_x,Real& Extension_y)const
{
	Extension_x = (this->Max_Point.x - this->Min_Point.x)*(Real)0.5;
	Extension_y = (this->Max_Point.y - this->Min_Point.y)*(Real)0.5;
	return;
}

template <class Real> inline void AABB2D<Real>::Get_Extensions(VECTOR2<Real>& Extensions)const
{
	Extensions.x = (this->Max_Point.x - this->Min_Point.x)*(Real)0.5;
	Extensions.y = (this->Max_Point.y - this->Min_Point.y)*(Real)0.5;
	return;
}


template <class Real> inline void AABB2D<Real>::Set_New_Max_Point(const Real New_Max_Point_x,const Real New_Max_Point_y)
{
	this->Max_Point.Set(New_Max_Point_x,New_Max_Point_y);
	return;
}
	
template <class Real> inline void AABB2D<Real>::Set_New_Max_Point(const VECTOR2<Real>& New_Max_Point)
{
	this->Max_Point.Set(New_Max_Point);
	return;
}
	
template <class Real> inline void AABB2D<Real>::Set_New_Max_Point(const Real* New_Max_Point)
{
	this->Max_Point.Set(New_Max_Point);
	return;
}

template <class Real> inline void AABB2D<Real>::Set_New_Min_Point(const Real New_Min_Point_x,const Real New_Min_Point_y)
{
	this->Min_Point.Set(New_Min_Point_x,New_Min_Point_y);
	return;
}
	
template <class Real> inline void AABB2D<Real>::Set_New_Min_Point(const VECTOR2<Real>& New_Min_Point)
{
	this->Min_Point.Set(New_Min_Point);
	return;
}
	
template <class Real> inline void AABB2D<Real>::Set_New_Min_Point(const Real* New_Min_Point)
{
	this->Min_Point.Set(New_Min_Point);
	return;
}


template <class Real> inline void AABB2D<Real>::Compute_Vextex(VECTOR2<Real> Vertex[4])const
{
	// Os vertices sao dados da seguinte forma:
	// centro +- extensao em 1.0,0.0 e 0.0,1.0
	//
	
	Vertex[0].x = this->Min_Point.x;
	Vertex[0].y = this->Min_Point.y;
	
	Vertex[1].x = this->Max_Point.x;
    Vertex[1].y = this->Min_Point.y;

	Vertex[2].x = this->Max_Point.x;
    Vertex[2].y = this->Max_Point.y;

	Vertex[3].x = this->Min_Point.x;
    Vertex[3].y = this->Max_Point.y;

	return;
}

template <class Real> inline void AABB2D<Real>::Compute_Vextex(Real* Vertex)const
{
	Vertex[0] = this->Min_Point.x;
	Vertex[1] = this->Min_Point.y;
	
	Vertex[2] = this->Max_Point.x;
    Vertex[3] = this->Min_Point.y;

	Vertex[4] = this->Max_Point.x;
    Vertex[5] = this->Max_Point.y;

	Vertex[6] = this->Min_Point.x;
    Vertex[7] = this->Max_Point.y;

	return;
}

