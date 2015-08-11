// Interceptor Strategy
// fabraham@tecgraf.puc-rio.br
// Jul 2003

#ifndef SG_INTERCEPTOR
#define SG_INTERCEPTOR

#include <sg/strategy.h>
#include <assert.h>

/**
 * Interceptor traversal strategy.
 * This strategy will intercept all the calls to a strategy.
 * Override the methods that perform additional operations.
 */
class SG_API SGInterceptor : public SGStrategy
{
	SGStrategy* m_strategy;
public:
	/**
	 * Constructor. Receives the intercepted strategy.
	 */
	SGInterceptor (SGStrategy* strategy = 0)
	{
		SetStrategy(strategy);
	}
	/**
	 * Destructor.
	 */
	virtual ~SGInterceptor ()
	{
	}
	/**
	 * Obtains the intercepted strategy.
	 */
	SGStrategy* GetStrategy () const
	{
		return m_strategy;
	}
	/**
	 * Sets the intercepted strategy.
	 */
	virtual void SetStrategy (SGStrategy* strategy)
	{
		m_strategy = strategy;
	}
	virtual void Load (SGItem* i)
	{
		assert(m_strategy!=0);
		GetStrategy()->Load(i);
	}
	virtual void Unload (SGItem* i)
	{
		assert(m_strategy!=0);
		GetStrategy()->Unload(i);
	}
	virtual void Load (SGState* s)
	{
		assert(m_strategy!=0);
		GetStrategy()->Load(s);
	}
	virtual void Unload (SGState* s)
	{
		assert(m_strategy!=0);
		GetStrategy()->Unload(s);
	}
	virtual void Load (SGBackground* b)
	{
		assert(m_strategy!=0);
		GetStrategy()->Load(b);
	}
	virtual void Unload (SGBackground* b)
	{
		assert(m_strategy!=0);
		GetStrategy()->Unload(b);
	}
	virtual void Load (SGShape* s)
	{
		assert(m_strategy!=0);
		GetStrategy()->Load(s);
	}
	virtual int Load (SGColLight * l)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Load(l);
	}
	virtual int Load (SGColScene * s)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Load(s);
	}
	virtual int Unload (SGColLight * l)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Unload(l);
	}
	virtual int Unload (SGColScene * s)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Unload(s);
	}
	virtual int Load (SGBin* b)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Load(b);
	}
	virtual int Unload (SGBin* b)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Unload(b);
	}
	virtual int Load (SGLight* l)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Load(l);
	}
	virtual int Load (SGEntity* e)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Load(e);
	}
	virtual int Load (SGObject* o)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Load(o);
	}
	virtual int Load (SGGroup* g)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Load(g);
	}
	virtual int Load (SGSwitch* s)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Load(s);
	}
	virtual int Load (SGSpace* s)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Load(s);
	}
	virtual int Unload (SGLight* l)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Unload(l);
	}
	virtual int Unload (SGSpace* s)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Unload(s);
	}
	virtual int Unload (SGEntity* e)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Unload(e);
	}
	virtual int Unload (SGObject* o)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Unload(o);
	}
	virtual int Unload (SGGroup* g)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Unload(g);
	}
	virtual int Unload (SGSwitch* s)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Unload(s);
	}
	virtual int Load (SGScene* s)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Load(s);
	}
	virtual int Unload (SGScene* s)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Unload(s);
	}
	virtual int Load (SGNode* n)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Load(n);
	}
	virtual int Unload (SGNode* n)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Unload(n);
	}
	virtual int Load (SGColObject* o)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Load(o);
	}
	virtual int Unload (SGColObject* o)
	{
		assert(m_strategy!=0);
		return GetStrategy()->Unload(o);
	}
};

#endif
