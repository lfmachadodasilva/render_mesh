/**
* Modulo de implementacao dos metodos inline da classe AABB2.
*/

/**
* Construtores
*/

template <class Real> inline AABB3D<Real>::AABB3D(void)
{
}

template <class Real> inline AABB3D<Real>::AABB3D(const VECTOR3<Real>& Min_Point,const VECTOR3<Real>& Max_Point)
{
	this->Min_Point.Set(Min_Point);
	this->Max_Point.Set(Max_Point);
}

template <class Real>inline  AABB3D<Real>::AABB3D(const Real Min_x,const Real Max_x,const Real Min_y,const Real Max_y,const Real Min_z,const Real Max_z)
{
	this->Min_Point.Set(Min_x,Min_y,Min_z);
	this->Max_Point.Set(Max_x,Max_y,Max_z);
}

template <class Real> inline AABB3D<Real>::AABB3D(const Real* Min_Point,const Real* Max_Point)
{
	this->Min_Point.Set(Min_Point);
	this->Max_Point.Set(Max_Point);
}

template <class Real> inline AABB3D<Real>::AABB3D(const AABB3D<Real>& Box)
{
	this->Min_Point.Set(Box.Min_Point);
	this->Max_Point.Set(Box.Max_Point);
}



/**
* Metodos de Get
*/

template <class Real> inline  VECTOR3<Real> AABB3D<Real>::Get_Center(void)const
{
	return(VECTOR3<Real>( (this->Min_Point.x + this->Max_Point.x)*(Real)0.5,
						  (this->Min_Point.y + this->Max_Point.y)*(Real)0.5,
						  (this->Min_Point.z + this->Max_Point.z)*(Real)0.5));
}

template <class Real> inline void AABB3D<Real>::Get_Extensions(Real& Extension_x,Real& Extension_y,Real& Extension_z)const
{
	Extension_x = (this->Max_Point.x - this->Min_Point.x)*(Real)0.5;
	Extension_y = (this->Max_Point.y - this->Min_Point.y)*(Real)0.5;
	Extension_z = (this->Max_Point.z - this->Min_Point.z)*(Real)0.5;
	return;
}

template <class Real> inline void AABB3D<Real>::Get_Extensions(VECTOR3<Real>& Extensions)const
{
	Extensions.x = (this->Max_Point.x - this->Min_Point.x)*(Real)0.5;
	Extensions.y = (this->Max_Point.y - this->Min_Point.y)*(Real)0.5;
	Extensions.z = (this->Max_Point.z - this->Min_Point.z)*(Real)0.5;
	return;
}


template <class Real> inline void AABB3D<Real>::Set_New_Max_Point(const Real New_Max_Point_x,const Real New_Max_Point_y,const Real New_Max_Point_z)
{
	this->Max_Point.Set(New_Max_Point_x,New_Max_Point_y,New_Max_Point_z);
	return;
}
	
template <class Real> inline void AABB3D<Real>::Set_New_Max_Point(const VECTOR3<Real>& New_Max_Point)
{
	this->Max_Point.Set(New_Max_Point);
	return;
}
	
template <class Real> inline void AABB3D<Real>::Set_New_Max_Point(const Real* New_Max_Point)
{
	this->Max_Point.Set(New_Max_Point);
	return;
}

template <class Real> inline void AABB3D<Real>::Set_New_Min_Point(const Real New_Min_Point_x,const Real New_Min_Point_y,const Real New_Min_Point_z)
{
	this->Min_Point.Set(New_Min_Point_x,New_Min_Point_y,New_Min_Point_z);
	return;
}
	
template <class Real> inline void AABB3D<Real>::Set_New_Min_Point(const VECTOR3<Real>& New_Min_Point)
{
	this->Min_Point.Set(New_Min_Point);
	return;
}
	
template <class Real> inline void AABB3D<Real>::Set_New_Min_Point(const Real* New_Min_Point)
{
	this->Min_Point.Set(New_Min_Point);
	return;
}

template <class Real> inline void AABB3D<Real>::Compute_Vextex(VECTOR3<Real> Vertex[8])const
{
	// Os vertices sao dados da seguinte forma:
	// centro +- extensao em 1.0,0.0,0.0 e 0.0,1.0,0.0 0.0,0.0f,1.0f
	//
	
	Vertex[0].x = this->Min_Point.x;
	Vertex[0].y = this->Min_Point.y;
	Vertex[0].z = this->Max_Point.z;
	
	Vertex[1].x = this->Max_Point.x;
    Vertex[1].y = this->Min_Point.y;
	Vertex[1].z = this->Max_Point.z;

	Vertex[2].x = this->Max_Point.x;
    Vertex[2].y = this->Max_Point.y;
	Vertex[2].z = this->Max_Point.z;

	Vertex[3].x = this->Min_Point.x;
    Vertex[3].y = this->Max_Point.y;
	Vertex[3].z = this->Max_Point.z;

	Vertex[4].x = this->Min_Point.x;
	Vertex[4].y = this->Min_Point.y;
	Vertex[4].z = this->Min_Point.z;
	
	Vertex[5].x = this->Max_Point.x;
    Vertex[5].y = this->Min_Point.y;
	Vertex[5].z = this->Min_Point.z;

	Vertex[6].x = this->Max_Point.x;
    Vertex[6].y = this->Max_Point.y;
	Vertex[6].z = this->Min_Point.z;

	Vertex[7].x = this->Min_Point.x;
    Vertex[7].y = this->Max_Point.y;
	Vertex[7].z = this->Min_Point.z;

	return;
}

template <class Real> inline void AABB3D<Real>::Compute_Vextex(Real* Vertex)const
{
	Vertex[0] = this->Min_Point.x;
	Vertex[1] = this->Min_Point.y;
	Vertex[2] = this->Max_Point.z;
	
	Vertex[3] = this->Max_Point.x;
    Vertex[4] = this->Min_Point.y;
	Vertex[5] = this->Max_Point.z;

	Vertex[6] = this->Max_Point.x;
    Vertex[7] = this->Max_Point.y;
	Vertex[8] = this->Max_Point.z;

	Vertex[9] = this->Min_Point.x;
    Vertex[10] = this->Max_Point.y;
	Vertex[11] = this->Max_Point.z;

	Vertex[12] = this->Min_Point.x;
	Vertex[13] = this->Min_Point.y;
	Vertex[14] = this->Min_Point.z;
	
	Vertex[15] = this->Max_Point.x;
    Vertex[16] = this->Min_Point.y;
	Vertex[17] = this->Min_Point.z;

	Vertex[18] = this->Max_Point.x;
    Vertex[19] = this->Max_Point.y;
	Vertex[20] = this->Min_Point.z;

	Vertex[21] = this->Min_Point.x;
    Vertex[22] = this->Max_Point.y;
	Vertex[23] = this->Min_Point.z;

	return;
}


