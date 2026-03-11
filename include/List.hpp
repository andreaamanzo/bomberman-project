#ifndef PLAYER_HPP
#define PLAYER_HPP

class List
{
public:
  List() = default ;

  // funzione di inserimento in testa
  void pushFront(int value)
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

  // funzione di inserimento in coda
  void pushBack(int value)
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

  // funzione di rimozione in testa
  void popFront()
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

  // funzione di rimozione in coda
  void popBack()
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

  // funzione di rimozione dato un indice
  void remove(int index)
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

    deleter -> next -> prev = deleter -> prev ;
    deleter -> prev -> next = deleter -> next ;
    delete deleter ;

    m_size-- ;
  }

  int front()
  {
    return m_head -> val ;
  }

  int back()
  {
    return m_tail -> val ;
  }

private:
  struct Node
  {
    int val{} ;
    Node* next{ nullptr } ;
    Node* prev{ nullptr } ;
  };

  Node* m_head{ nullptr } ;
  Node* m_tail{ nullptr } ;
  int m_size{ 0 } ;
};

#endif