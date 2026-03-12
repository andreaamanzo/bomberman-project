#include <List.hpp>

void List::pushFront(int value)
{
    Node* foo = new Node{value} ;

    if (m_head == nullptr) // gestione lista vuota
    {
      m_head = foo ;
      m_tail = foo ;
    }
    else
    {
      m_head -> prev = foo ;
      foo -> next = m_head ;
      m_head = foo ;
    }

    m_size++ ;
}

void List::pushBack(int value)
{
    Node* foo = new Node{value} ;

    if (m_head == nullptr) // gestione lista vuota
    {
      m_head = foo ;
      m_tail = foo ;
    }
    else
    {
      m_tail -> next = foo ;
      foo -> prev = m_tail ;
      m_tail = foo ;
    }

    m_size++ ;
}

void List::popFront()
{
    if (m_head == nullptr) return ; // gestione lista vuota

    Node* deleter = m_head ;

    if (m_head == m_tail) // gestione lista con un solo elemento
    {
      m_head = nullptr ;
      m_tail = nullptr ;
    }
    else
    {
      m_head = m_head -> next ;
      m_head -> prev = nullptr ;
    }

    delete deleter ;
    m_size-- ;
}

void List::popBack()
{
    if (m_head == nullptr) return ; // gestione lista vuota

    Node* deleter = m_tail ;

    if (m_head == m_tail) // gestione lista con un solo elemento
    {
      m_head = nullptr ;
      m_tail = nullptr ;
    }
    else
    {
      m_tail = m_tail -> prev ;
      m_tail -> next = nullptr ;
    }

    delete deleter ;
    m_size-- ;
}

void List::remove(int index)
{
    if (m_head == nullptr || index >= m_size || index < 0) return ;

    // casi di lista con un solo elemento già gestiti in pop
    if (index == 0)
    {
      popFront() ;
      return ;
    }
    if (index == m_size - 1)
    {
      popBack() ;
      return ;
    }

    // l'indice da eliminare solo tra nodi interni
    int i = 1 ;
    Node* deleter = m_head -> next ;

    while (i != index)
    {
      i++ ;
      deleter = deleter -> next ;
    }

    (deleter -> next) -> prev = deleter -> prev ;
    (deleter -> prev) -> next = deleter -> next ;
    delete deleter ;

    m_size-- ;
}

void List::clear()
{
    if (m_head == nullptr) return ;

    Node* deleter = m_head ;

    while (m_head != nullptr)
    {
      m_head = m_head -> next ;
      delete deleter ;
      deleter = m_head ;
    }

    m_head = nullptr ;
    m_tail = nullptr ;
    m_size = 0 ;
}

int List::size() const
{
    return m_size ;
}

int List::front(bool* success = nullptr) const
{
    if (m_size <= 0)
    {
      *success = false ;
      return 0 ;
    }

    *success = true ;
    return m_head -> val ;
}

int List::back(bool* success = nullptr) const
{
    if (m_size <= 0)
    {
      *success = false ;
      return 0 ;
    }

    *success = true ;
    return m_tail -> val ;
}