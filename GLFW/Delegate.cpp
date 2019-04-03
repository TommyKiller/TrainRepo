#include "Delegate.h"

Events::Delegate::Delegate()
	: _ptrobject(nullptr),
	_ptrmethod(nullptr),
	_ptrfunc(nullptr),
	member(false)
{}

bool Events::Delegate::operator!()
{
	if (member)
	{
		return (!_ptrobject || !_ptrmethod);
	}
	else
	{
		return !_ptrfunc;
	}
}

bool Events::Delegate::operator==(const Delegate& delegate)
{
	return (_ptrobject == delegate._ptrobject && _ptrmethod == delegate._ptrmethod && _ptrfunc == delegate._ptrfunc);
}

bool Events::Delegate::operator!=(const Delegate& delegate)
{
	return !(*this == delegate);
}
