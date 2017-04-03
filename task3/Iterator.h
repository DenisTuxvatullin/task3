#pragma once
#include "CMyStringList.h"

class CMyStringList::Iterator
	:public std::iterator<std::bidirectional_iterator_tag, std::string>
{
public:
	Iterator();
	Iterator(bool pastEnd, std::weak_ptr<Node> const& node, CMyStringList *target);
	bool const operator==(Iterator const& other) const;
	bool const operator!=(Iterator const& other) const;

	std::string& operator*() const;
	std::string* operator->() const;
	Iterator& operator++();
	Iterator& operator--();

	std::weak_ptr<Node> GetNode() const;
	bool const IsPastEnd() const;

private:
	bool m_pastEnd;
	std::weak_ptr<Node> m_node;
	CMyStringList *m_target;
};
