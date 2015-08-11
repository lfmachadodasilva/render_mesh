/**
* Modulo de implementacao dos metodos inline da classe 
*/


/**
* Construtores
*/

template <class Real> inline OBB3D<Real>::OBB3D(void)
{
}


template <class Real> inline OBB3D<Real>::OBB3D(const OBB3D<Real>& Box)
{
	this->Center.Set(Box.Center);
	this->Axis_i.Set(Box.Axis_i);
	this->Axis_j.Set(Box.Axis_j);
	this->Axis_k.Set(Box.Axis_k);
	this->i_Length = Box.i_Length;
	this->j_Length = Box.j_Length;
	this->k_Length = Box.k_Length;
}


template <class Real> inline OBB3D<Real>::OBB3D(const VECTOR3<Real>& Center,const VECTOR3<Real>& Axis_i,const VECTOR3<Real>& Axis_j,const VECTOR3<Real>& Axis_k,
										 const Real i_Length,const Real j_Length,const Real k_Length)
{
	this->Center.Set(Center);
	this->Axis_i.Set(Axis_i);
	this->Axis_j.Set(Axis_j);
	this->Axis_k.Set(Axis_k);
	this->i_Length = i_Length;
	this->j_Length = j_Length;
	this->k_Length = k_Length;
}

template <class Real> inline OBB3D<Real>::OBB3D(const VECTOR3<Real>& Center,const VECTOR3<Real>* Axis,const Real i_Length,const Real j_Length,const Real k_Length)
{
	this->Center.Set(Center);
	this->Axis_i.Set(&Axis[0]);
	this->Axis_j.Set(&Axis[1]);
	this->Axis_j.Set(&Axis[2]);
	this->i_Length = i_Length;
	this->j_Length = j_Length;
	this->k_Length = k_Length;
}


template <class Real> inline OBB3D<Real>::OBB3D(const VECTOR3<Real>& Center,const Real* Axis_i,const Real* Axis_j,const Real* Axis_k,
										 const Real i_Length,const Real j_Length,const Real k_Length)
{
	this->Center.Set(Center);
	this->Axis_i.Set(Axis_i);
	this->Axis_j.Set(Axis_j);
	this->Axis_k.Set(Axis_k);
	this->i_Length = i_Length;
	this->j_Length = j_Length;
	this->k_Length = k_Length;
}

/**
* Calcula os vertices da OBB
*/

template <class Real> inline void OBB3D<Real>::Compute_Vextex(VECTOR3<Real> Vertex[8])const
{
	VECTOR3<Real> Ext_Axis_i(this->Axis_i.x*this->i_Length,this->Axis_i.y*this->i_Length,this->Axis_i.z*this->i_Length);
	VECTOR3<Real> Ext_Axis_j(this->Axis_j.x*this->j_Length,this->Axis_j.y*this->j_Length,this->Axis_j.z*this->j_Length);
	VECTOR3<Real> Ext_Axis_k(this->Axis_k.x*this->k_Length,this->Axis_k.y*this->k_Length,this->Axis_k.z*this->k_Length);

	// 1 vertice
	Vertex[0].x = this->Center.x - Ext_Axis_i.x - Ext_Axis_j.x + Ext_Axis_k.x;
	Vertex[0].y = this->Center.y - Ext_Axis_i.y - Ext_Axis_j.y + Ext_Axis_k.y;
	Vertex[0].z = this->Center.z - Ext_Axis_i.z - Ext_Axis_j.z + Ext_Axis_k.z;

	// 2 Vertice
	Vertex[1].x = this->Center.x + Ext_Axis_i.x - Ext_Axis_j.x + Ext_Axis_k.x;
	Vertex[1].y = this->Center.y + Ext_Axis_i.y - Ext_Axis_j.y + Ext_Axis_k.y;
	Vertex[1].z = this->Center.z + Ext_Axis_i.z - Ext_Axis_j.z + Ext_Axis_k.z;
	
	// 3 Vertice
	Vertex[2].x = this->Center.x + Ext_Axis_i.x + Ext_Axis_j.x + Ext_Axis_k.x;
	Vertex[2].y = this->Center.y + Ext_Axis_i.y + Ext_Axis_j.y + Ext_Axis_k.y;
	Vertex[2].z = this->Center.z + Ext_Axis_i.z + Ext_Axis_j.z + Ext_Axis_k.z;
	
	// 4 Vertice
	Vertex[3].x = this->Center.x - Ext_Axis_i.x + Ext_Axis_j.x + Ext_Axis_k.x;
	Vertex[3].y = this->Center.y - Ext_Axis_i.y + Ext_Axis_j.y + Ext_Axis_k.y;
	Vertex[3].z = this->Center.z - Ext_Axis_i.z + Ext_Axis_j.z + Ext_Axis_k.z;

	// 5 vertice
	Vertex[4].x = this->Center.x - Ext_Axis_i.x - Ext_Axis_j.x - Ext_Axis_k.x;
	Vertex[4].y = this->Center.y - Ext_Axis_i.y - Ext_Axis_j.y - Ext_Axis_k.y;
	Vertex[4].z = this->Center.z - Ext_Axis_i.z - Ext_Axis_j.z - Ext_Axis_k.z;

	// 6 Vertice
	Vertex[5].x = this->Center.x + Ext_Axis_i.x - Ext_Axis_j.x - Ext_Axis_k.x;
	Vertex[5].y = this->Center.y + Ext_Axis_i.y - Ext_Axis_j.y - Ext_Axis_k.y;
	Vertex[5].z = this->Center.z + Ext_Axis_i.z - Ext_Axis_j.z - Ext_Axis_k.z;
	
	// 7 Vertice
	Vertex[6].x = this->Center.x + Ext_Axis_i.x + Ext_Axis_j.x - Ext_Axis_k.x;
	Vertex[6].y = this->Center.y + Ext_Axis_i.y + Ext_Axis_j.y - Ext_Axis_k.y;
	Vertex[6].z = this->Center.z + Ext_Axis_i.z + Ext_Axis_j.z - Ext_Axis_k.z;
	
	// 8 Vertice
	Vertex[7].x = this->Center.x - Ext_Axis_i.x + Ext_Axis_j.x - Ext_Axis_k.x;
	Vertex[7].y = this->Center.y - Ext_Axis_i.y + Ext_Axis_j.y - Ext_Axis_k.y;
	Vertex[7].z = this->Center.z - Ext_Axis_i.z + Ext_Axis_j.z - Ext_Axis_k.z;

	return;
}


template <class Real> inline void OBB3D<Real>::Compute_Vextex(Real* Vertex)const
{
	VECTOR3<Real> Ext_Axis_i(this->Axis_i.x*this->i_Length,this->Axis_i.y*this->i_Length,this->Axis_i.z*this->i_Length);
	VECTOR3<Real> Ext_Axis_j(this->Axis_j.x*this->j_Length,this->Axis_j.y*this->j_Length,this->Axis_j.z*this->j_Length);
	VECTOR3<Real> Ext_Axis_k(this->Axis_k.x*this->k_Length,this->Axis_k.y*this->k_Length,this->Axis_k.z*this->k_Length);

	// 1 vertice
	Vertex[0] = this->Center.x - Ext_Axis_i.x - Ext_Axis_j.x + Ext_Axis_k.x;
	Vertex[1] = this->Center.y - Ext_Axis_i.y - Ext_Axis_j.y + Ext_Axis_k.y;
	Vertex[2] = this->Center.z - Ext_Axis_i.z - Ext_Axis_j.z + Ext_Axis_k.z;

	// 2 Vertice
	Vertex[3] = this->Center.x + Ext_Axis_i.x - Ext_Axis_j.x + Ext_Axis_k.x;
	Vertex[4] = this->Center.y + Ext_Axis_i.y - Ext_Axis_j.y + Ext_Axis_k.y;
	Vertex[5] = this->Center.z + Ext_Axis_i.z - Ext_Axis_j.z + Ext_Axis_k.z;
	
	// 3 Vertice
	Vertex[6] = this->Center.x + Ext_Axis_i.x + Ext_Axis_j.x + Ext_Axis_k.x;
	Vertex[7] = this->Center.y + Ext_Axis_i.y + Ext_Axis_j.y + Ext_Axis_k.y;
	Vertex[8] = this->Center.z + Ext_Axis_i.z + Ext_Axis_j.z + Ext_Axis_k.z;
	
	// 4 Vertice
	Vertex[9] = this->Center.x - Ext_Axis_i.x + Ext_Axis_j.x + Ext_Axis_k.x;
	Vertex[10] = this->Center.y - Ext_Axis_i.y + Ext_Axis_j.y + Ext_Axis_k.y;
	Vertex[11] = this->Center.z - Ext_Axis_i.z + Ext_Axis_j.z + Ext_Axis_k.z;

	// 5 vertice
	Vertex[12] = this->Center.x - Ext_Axis_i.x - Ext_Axis_j.x - Ext_Axis_k.x;
	Vertex[13] = this->Center.y - Ext_Axis_i.y - Ext_Axis_j.y - Ext_Axis_k.y;
	Vertex[14] = this->Center.z - Ext_Axis_i.z - Ext_Axis_j.z - Ext_Axis_k.z;

	// 6 Vertice
	Vertex[15] = this->Center.x + Ext_Axis_i.x - Ext_Axis_j.x - Ext_Axis_k.x;
	Vertex[16] = this->Center.y + Ext_Axis_i.y - Ext_Axis_j.y - Ext_Axis_k.y;
	Vertex[17] = this->Center.z + Ext_Axis_i.z - Ext_Axis_j.z - Ext_Axis_k.z;
	
	// 7 Vertice
	Vertex[18] = this->Center.x + Ext_Axis_i.x + Ext_Axis_j.x - Ext_Axis_k.x;
	Vertex[19] = this->Center.y + Ext_Axis_i.y + Ext_Axis_j.y - Ext_Axis_k.y;
	Vertex[20] = this->Center.z + Ext_Axis_i.z + Ext_Axis_j.z - Ext_Axis_k.z;
	
	// 8 Vertice
	Vertex[21] = this->Center.x - Ext_Axis_i.x + Ext_Axis_j.x - Ext_Axis_k.x;
	Vertex[22] = this->Center.y - Ext_Axis_i.y + Ext_Axis_j.y - Ext_Axis_k.y;
	Vertex[23] = this->Center.z - Ext_Axis_i.z + Ext_Axis_j.z - Ext_Axis_k.z;

	return;
	
}


template <class Real> inline void OBB3D<Real>::Set_New_Center(const VECTOR3<Real>& New_Center)
{
	this->Center.Set(New_Center);
	return;
}

template <class Real> inline void OBB3D<Real>::Set_New_Center(const Real* New_Center)
{
	this->Center.Set(New_Center);
	return;
}

template <class Real> inline void OBB3D<Real>::Set_New_Center(const Real New_Center_x,const Real New_Center_y,const Real New_Center_z)
{
	this->Center.Set(New_Center_x,New_Center_y,New_Center_z);
	return;
}

template <class Real> inline void OBB3D<Real>::Set_New_Extensions(const Real i_Length,const Real j_Length,const Real k_Length)
{
	this->i_Length = i_Length;
	this->j_Length = j_Length;
	this->k_Length = k_Length;
	return;
}


template <class Real> inline void OBB3D<Real>::Set_New_Basis(const VECTOR3<Real>& New_Axis_i,const VECTOR3<Real>& New_Axis_j,const VECTOR3<Real>& New_Axis_k)
{
	this->Axis_i.Set(New_Axis_i);
	this->Axis_j.Set(New_Axis_j);
	this->Axis_k.Set(New_Axis_k);
	return;
}

template <class Real> inline void OBB3D<Real>::Set_New_Basis(const Real* New_Axis_i,const Real* New_Axis_j,const Real* New_Axis_k)
{
	this->Axis_i.Set(New_Axis_i);
	this->Axis_j.Set(New_Axis_j);
	this->Axis_k.Set(New_Axis_k);
	return;
}

template <class Real> inline void OBB3D<Real>::Set_New_Basis(const Real New_Axis_i_x,const Real New_Axis_i_y,const Real New_Axis_i_k,
													  const Real New_Axis_j_x,const Real New_Axis_j_y,const Real New_Axis_j_k,
													  const Real New_Axis_k_x,const Real New_Axis_k_y,const Real New_Axis_k_k)
{
	this->Axis_i.Set(New_Axis_i_x,New_Axis_i_y,New_Axis_i_k);
	this->Axis_j.Set(New_Axis_j_x,New_Axis_j_y,New_Axis_j_k);
	this->Axis_k.Set(New_Axis_k_x,New_Axis_k_y,New_Axis_k_k);
	return;
}
