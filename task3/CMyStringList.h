#pragma once
class CMyStringList
{
public:
	virtual ~CMyStringList();
	struct Node
	{
		std::string m_value;
		std::weak_ptr<Node>  m_previous;
		std::shared_ptr<Node> m_next;
	};
	class Iterator;
	Iterator begin();
	Iterator end();
	std::weak_ptr<Node> GetLastNode();
	void Insert(Iterator const& it, std::string const& data);
	void Remove(Iterator const& it);
	void Clear();

private:
	std::weak_ptr<Node> m_last;
	std::shared_ptr<Node> m_first;	
};

