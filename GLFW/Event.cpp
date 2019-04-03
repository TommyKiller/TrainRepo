#include "Event.h"

Events::Event::Node::Node(Delegate data, Node* next) :
	_data(data),
	_next(next)
{}

Events::Event::NodeIterator::NodeIterator(Node* node)
	: _node(node)
{}

bool Events::Event::NodeIterator::HasNext() const
{
	return (_node) ? true : false;
}

Events::Delegate& Events::Event::NodeIterator::GetNext()
{
	Delegate& delegate = _node->_data;
	_node = _node->_next;

	return delegate;
}

Events::Event::Event()
	: _first_node(nullptr),
	_last_node(nullptr)
{}

Events::Event& Events::Event::operator+=(const Delegate& delegate)
{
	Push(delegate);
	return*this;
}

Events::Event& Events::Event::operator-=(const Delegate& delegate)
{
	Remove(delegate);
	return*this;
}

Events::Event::~Event()
{
	Node* current_node = _first_node;

	while (current_node)
	{
		Node* temp_node = current_node->_next;
		delete current_node;
		current_node = temp_node;
	}
}

void Events::Event::Push(const Delegate& data)
{
	if (_last_node)
	{
		bool subscribed = false;
		NodeIterator iterator(_first_node);

		while (iterator.HasNext())
		{
			if (iterator.GetNext() == data)
			{
				subscribed = true;
			}
		}

		if (!subscribed)
		{
			Node* temp_node = new Node(data, nullptr);
			_last_node->_next = temp_node;
			_last_node = temp_node;
		}
	}
	else
	{
		Node* temp_node = new Node(data, nullptr);
		_first_node = temp_node;
		_last_node = temp_node;
	}
}

void Events::Event::Remove(const Delegate& data)
{
	Node* current_node = _first_node;
	Node* previous_node = _first_node;

	while (current_node)
	{
		if (current_node->_data == data)
		{
			if (current_node == _first_node)
			{
				_first_node = current_node->_next;
				previous_node = current_node->_next;
			}
			else
			{
				previous_node->_next = current_node->_next;
			}

			Node* temp_node = current_node->_next;
			delete current_node;
			current_node = temp_node;
		}
		else
		{
			previous_node = current_node;
			current_node = current_node->_next;
		}
	}

	_last_node = previous_node;
}
