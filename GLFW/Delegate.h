#ifndef DELEGATE_H
#define DELEGATE_H


namespace Events
{
	class Delegate
	{
	public:
		Delegate();

		template <class Owner, class ...Args>
		Delegate(Owner* owner, void (Owner::* method)(Args...))
		{
			_ptrobject = reinterpret_cast<Object*>(owner);
			_ptrmethod = reinterpret_cast<Method>(method);
			member = true;
		}

		template <class ...Args>
		Delegate(void (*func)(Args...))
			: _ptrobject(nullptr),
			_ptrmethod(nullptr)
		{
			_ptrfunc = reinterpret_cast<Func>(func);
			member = false;
		}

		template<class ...Args>
		void operator()(Args...)
		{
			if (member && _ptrobject && _ptrmethod)
			{
				(_ptrobject->*_ptrmethod)(Args...);
			}
			else if (_ptrfunc)
			{
				_ptrfunc(Args...);
			}
		}

		bool operator!();

		bool operator==(const Delegate& delegate);

		bool operator!=(const Delegate& delegate);

	private:
		struct Object {};
		typedef void (Object::*Method)();
		typedef void (*Func)();

		Object* _ptrobject;
		Method _ptrmethod;
		Func _ptrfunc;

		bool member;
	};
}


#endif
