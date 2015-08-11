/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_REFCOUNTING_H_
#define _VR_REFCOUNTING_H_

#include "Common.h"

#include <ostream>

namespace vr {

/*!
    This class represents a pointer to reference-counted objects.
 */
template<class T>
class ref_ptr
{
public:
	ref_ptr()
		: _ptr( NULL )
	{;}

	ref_ptr( T* t )
		: _ptr( t )
	{
		if( _ptr )
			_ptr->incRef();
	}

	ref_ptr( const ref_ptr& rp )
		: _ptr( rp._ptr )
	{
		if( _ptr )
			_ptr->incRef();
	}

	~ref_ptr()                           
	{
		if( _ptr )
			_ptr->decRef();
		_ptr = NULL;
	}

	inline ref_ptr& operator= ( const ref_ptr& rp )
	{
		if( _ptr == rp._ptr )
			return *this;
		T* tmp_ptr = _ptr;
		_ptr = rp._ptr;
		if( _ptr )
			_ptr->incRef();

		// unref second to prevent any deletion of any object which might
		// be referenced by the other object. i.e rp is child of the
		// original _ptr.
		if( tmp_ptr )
			tmp_ptr->decRef();

		return *this;
	}

	inline ref_ptr& operator= ( T* ptr )
	{
		if( _ptr == ptr )
			return *this;
		T* tmp_ptr = _ptr;
		_ptr = ptr;
		if (_ptr)
			_ptr->incRef();
		// unref second to prevent any deletion of any object which might
		// be referenced by the other object. i.e rp is child of the
		// original _ptr.
		if( tmp_ptr )
			tmp_ptr->decRef();
		return *this;
	}

	// comparison operators for ref.
	inline bool operator == (const ref_ptr& rp) const { return (_ptr==rp._ptr); }
	inline bool operator != (const ref_ptr& rp) const { return (_ptr!=rp._ptr); }
	inline bool operator < (const ref_ptr& rp) const { return (_ptr<rp._ptr); }
	inline bool operator > (const ref_ptr& rp) const { return (_ptr>rp._ptr); }

	// comparison operator for const T*.
	inline bool operator == (const T* ptr) const { return (_ptr==ptr); }
	inline bool operator != (const T* ptr) const { return (_ptr!=ptr); }
	inline bool operator < (const T* ptr) const { return (_ptr<ptr); }
	inline bool operator > (const T* ptr) const { return (_ptr>ptr); }

	inline T& operator*()  { return *_ptr; }

	inline const T& operator*() const { return *_ptr; }

	inline T* operator->() { return _ptr; }

	inline const T* operator->() const   { return _ptr; }

	inline bool operator!() const	{ return _ptr == NULL; }

	inline bool valid() const	{ return _ptr != NULL; }

	inline T* get() { return _ptr; }

	inline const T* get() const { return _ptr; }

private:
	T* _ptr;
};


/**
 *  This class stores how many ref's of a class are valid. All classes
 *  that are to be reference counted must inherit this.
 */
class VRBASE_EXPORT RefCounted
{
public:
	RefCounted()
	{
		_refCount = 0;
	}

	RefCounted( const RefCounted& )
	{
		_refCount = 0;
	}

	inline RefCounted & operator=( const RefCounted& )
	{
		return *this;
	}

	inline void incRef() const
	{
		++_refCount;
	}

	inline void decRef() const
	{
		if( --_refCount <= 0 )
			delete this;
	}

	inline int32 getRefCount() const
	{
		return _refCount;
	}

protected:
	virtual ~RefCounted();

private:
	mutable int32 _refCount;
};

} // namespace vr

template<typename T>
inline std::ostream& operator<<( std::ostream& stream, const vr::ref_ptr<T>& rp )
{
	stream << "vr.ref_ptr: ";
	if( rp.valid() )
		stream << "<invalid>";
	else
		stream << "refCount=" << rp->getRefCount() << ", ptr={" << rp.get() << "}";
	return stream;
}

#endif
