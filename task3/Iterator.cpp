#include "stdafx.h"
#include "Iterator.h"
#include "CMyStringList.h"

CMyStringList::Iterator::Iterator()
	:m_pastEnd(true)
	, m_target(nullptr)
{}

CMyStringList::Iterator::Iterator(bool pastEnd, std::weak_ptr<Node> const& node, CMyStringList *target)
	: m_pastEnd(pastEnd)
	, m_node(node)
	, m_target(target)
{}

bool const CMyStringList::Iterator::operator==(Iterator const& other) const
{
	if (m_pastEnd != other.m_pastEnd)
	{
		return false;
	}

	if (m_pastEnd)
	{
		return (m_target == other.m_target);
	}
	else
	{
		return (m_node.lock().get() == other.m_node.lock().get());
	}
}

bool const CMyStringList::Iterator::operator!=(Iterator const& other) const
{
	return !(*this == other);
}

std::string& CMyStringList::Iterator::operator*() const
{
	return m_node.lock()->m_value;
}

std::string* CMyStringList::Iterator::operator->() const
{
	return &(*(*this));
}

CMyStringList::Iterator& CMyStringList::Iterator::operator++()
{

	if (m_node.lock()->m_next)
	{
		m_node = m_node.lock()->m_next;
	}
	else
	{
		m_pastEnd = true;
		m_node.reset();
	}

	return *this;
}


CMyStringList::Iterator& CMyStringList::Iterator::operator--()
{
	if (!m_pastEnd)
	{
		m_node = m_node.lock()->m_previous;
	}
	else
	{
		m_pastEnd = false;
		m_node = m_target->GetLastNode();
	}

	return *this;
}

std::weak_ptr<CMyStringList::Node> CMyStringList::Iterator::GetNode() const
{
	return m_node;
}

bool const CMyStringList::Iterator::IsPastEnd() const
{
	return m_pastEnd;
}