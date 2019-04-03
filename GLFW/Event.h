#ifndef EVENT_H
#define EVENT_H
#include "Delegate.h"


namespace Events
{
	class Event
	{
	public:
		Event();

		Event& operator+= (const Delegate& delegate);

		Event& operator-= (const Delegate& delegate);

		template <class ...Args>
		void operator()(Args...)
		{
			NodeIterator iterator(_first_node);
			Delegate delegate;

			while (iterator.HasNext())
			{
				delegate = iterator.GetNext();
				delegate(Args...);
			}
		}

		~Event();

	private:
		struct Node
		{
			Delegate _data;
			Node* _next;

			Node(Delegate data, Node* next);
		};

		class NodeIterator
		{
		public:
			NodeIterator(Node* node);

			bool HasNext() const;

			Delegate& GetNext();

		private:
			Node* _node;
		};

		Node* _first_node;
		Node* _last_node;

		Event(const Event&) = delete;

		void operator=(const Event&) = delete;

		void Push(const Delegate& data);

		void Remove(const Delegate& data);
	};
}


#endif
