//* vglmanipulatable.h
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Feb 2004

#ifndef SGVGL_MANIPULATABLE_H
#define SGVGL_MANIPULATABLE_H

#include <vgl/hnd/manipulatable.h>
#include <sg/object.h>
#include <alg/matrix.h>
#include <sgvgl/defines.h>

/**
 * SG Object interface to VglManipulatable
 */
class SGVGLAPI SGVglManipulatable : public VglManipulatable
{
	SGObject* m_obj;
public:
	SGVglManipulatable();
	virtual ~SGVglManipulatable();

	void SetObject (SGObject* o);

	virtual bool Translate(double dx, double dy, double dz);
	virtual bool SetSize(double xi, double yi, double zi, double xf, double yf, double zf);
	virtual void GetSize(double& xi, double& yi, double& zi, double& xf, double& yf, double& zf);
	virtual bool Scale(double sx, double sy, double sz);
	virtual AlgMatrix GetToLocal(void);
	virtual bool AcceptEvent(int mode, bool dofx, bool dofy, bool dofz)
	{
		return true;
	}
};

#endif

