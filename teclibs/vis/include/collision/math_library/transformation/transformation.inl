/**
* Modulo de implementacao dos metodos inline da classe TRANSFORMATION
*/


template <class Real> inline 
TRANSFORMATION<Real>::TRANSFORMATION(void):
Rotation((Real)1.0,(Real)0.0,(Real)0.0,(Real)0.0,(Real)1.0,(Real)0.0,(Real)0.0,(Real)0.0,(Real)1.0),
Translation((Real)0.0,(Real)0.0,(Real)0.0),Scale((Real)1.0)

{	
	this->Is_Identity = true;
	
}


template <class Real> inline 
TRANSFORMATION<Real>::TRANSFORMATION(const TRANSFORMATION<Real>& Transformation):
Rotation(Transformation.Rotation),
Translation(Transformation.Translation),
Scale(Transformation.Scale)
{	
	this->Is_Identity = Transformation.Is_Identity;
}


template <class Real> inline 
TRANSFORMATION<Real>::TRANSFORMATION(const MATRIX3<Real>& New_Rotation,const Real New_Scale,
														   const VECTOR3<Real>& New_Translation):
Rotation(New_Rotation),Scale(New_Scale),Translation(New_Translation)
{
	this->Is_Identity = false;
}



template <class Real> inline 
 bool TRANSFORMATION<Real>::Is_Identity_Matrix(void)const
{
	return(this->Is_Identity);
}

template <class Real> inline 
void TRANSFORMATION<Real>::Make_Identity(void)
{
	this->Rotation.Set_Identity();
	this->Translation.Set((Real)0.0,(Real)0.0,(Real)0.0);
	this->Scale = (Real)1.0;
	this->Is_Identity = true;
	
}

template <class Real> inline 
const MATRIX3<Real>& TRANSFORMATION<Real>::Get_Rotate(void)const
{
	return(this->Rotation);
}

template <class Real> inline 
void TRANSFORMATION<Real>::Set_Rotate(const VECTOR3<Real>& Axis,Real Angle)
{
	this->Rotation.Set_Rotate(Axis,Angle);
	this->Is_Identity = false;
	return;
}

template <class Real> inline 
void TRANSFORMATION<Real>::Set_Rotate(const MATRIX3<Real>& Rotation)
{
	this->Rotation.Set(Rotation);
	this->Is_Identity = false;
	return;
}

template <class Real> inline 
void TRANSFORMATION<Real>::Set_Rotate(const VECTOR3<Real>& Axis_X,const VECTOR3<Real>& Axis_Y,const VECTOR3<Real>& Axis_Z)
{
	this->Rotation.Set_Basis(Axis_X,Axis_Y,Axis_Z);
	this->Is_Identity = false;
	return;
}

template <class Real> inline 
const VECTOR3<Real>& TRANSFORMATION<Real>::Get_Translate(void)const
{
	return(this->Translation);
}

template <class Real> inline 
void TRANSFORMATION<Real>::Set_Translate(const Real tx,const Real ty,const Real tz)
{
	this->Translation.Set(tx,ty,tz);
	this->Is_Identity = false;
	return;
}

template <class Real> inline 
void TRANSFORMATION<Real>::Set_Translate(const VECTOR3<Real>& Translation)
{
	this->Translation.Set(Translation);
	this->Is_Identity = false;
	return;
}

template <class Real> inline 
const Real TRANSFORMATION<Real>::Get_Uniform_Scale(void)const
{
	return(this->Scale);
}

template <class Real> inline 
void TRANSFORMATION<Real>::Set_Uniform_Scale(const Real Scale)
{
	this->Scale = Scale;
	this->Is_Identity = false;
	return;
}

template <class Real> inline 
MATRIX4<Real> TRANSFORMATION<Real>::Get_4x4_Matrix(void)const
{
	return(MATRIX4<Real>(this->Rotation.Elements[0]*this->Scale,this->Rotation.Elements[3]*this->Scale,this->Rotation.Elements[6]*this->Scale,this->Translation.x,
						 this->Rotation.Elements[1]*this->Scale,this->Rotation.Elements[4]*this->Scale,this->Rotation.Elements[7]*this->Scale,this->Translation.y,
						 this->Rotation.Elements[2]*this->Scale,this->Rotation.Elements[5]*this->Scale,this->Rotation.Elements[8]*this->Scale,this->Translation.z,
						 (Real)0.0,(Real)0.0,(Real)0.0,(Real)1.0));
}


template <class Real> inline
void TRANSFORMATION<Real>::Set_Transformation(const TRANSFORMATION<Real>& Trans)
{
	this->Scale = Trans.Scale;
	this->Translation.Set(Trans.Translation);
	this->Rotation.Set(Trans.Rotation);
	this->Is_Identity = Trans.Is_Identity;
	return;
}
