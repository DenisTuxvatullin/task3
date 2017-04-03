#include "stdafx.h"
#include "Iterator.h"

CMyStringList::~CMyStringList()
{
	Clear();
}

void CMyStringList::Clear()
{
	while (m_first)
	{
		m_first.reset();
	}
	return;
}

CMyStringList::Iterator CMyStringList::begin()
{
	if (m_first)
	{
		return Iterator(false, m_first, this);
	}
	else
	{
		return end();
	}
}

CMyStringList::Iterator CMyStringList::end()
{
	return Iterator(true, std::weak_ptr<Node>(), this);
}

std::weak_ptr<CMyStringList::Node> CMyStringList::GetLastNode()
{
	return m_last;
}

void CMyStringList::Insert(Iterator const& it, std::string const& data)
{
	std::shared_ptr<Node> newNode(new Node);
	newNode->m_value = move(data);

	if (it.IsPastEnd())
	{
		if (m_first)
		{
			newNode->m_previous = m_last;
			m_last.lock()->m_next = newNode;
			m_last = newNode;
		}
		else
		{
			m_first = newNode;
			m_last = newNode;
		}
	}
	else
	{

		if (it.GetNode().lock().get() == m_first.get())
		{
			newNode->m_next = m_first;
			m_first->m_previous = newNode;
			m_first = newNode;
		}
		else
		{
			std::shared_ptr<Node> nextNode(it.GetNode().lock());
			std::shared_ptr<Node> prevNode(nextNode->m_previous.lock());

			newNode->m_previous = prevNode;
			newNode->m_next = nextNode;

			prevNode->m_next = newNode;
			nextNode->m_previous = newNode;
		}
	}
}

void CMyStringList::Remove(Iterator const& it)
{
	std::shared_ptr<Node> delNode(it.GetNode().lock());
	std::shared_ptr<Node> prevNode(delNode->m_previous.lock());
	std::shared_ptr<Node> nextNode(delNode->m_next);

	if (prevNode)
	{
		if (nextNode)
		{
			prevNode->m_next = nextNode;
			nextNode->m_previous = prevNode;
		}
		else
		{
			prevNode->m_next.reset();
			m_last = prevNode;
		}
	}
	else
	{
		if (nextNode)
		{
			nextNode->m_previous.reset();
			m_first = nextNode;
		}
		else
		{
			m_first.reset();
			m_last.reset();
		}
	}
}
