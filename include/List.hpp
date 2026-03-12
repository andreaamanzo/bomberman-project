#ifndef PLAYER_HPP
#define PLAYER_HPP

class List
{
public:
  List() = default ;

  // funzione di inserimento in testa
  void pushFront(int value) ;

  // funzione di inserimento in coda
  void pushBack(int value) ;

  // funzione di rimozione in testa
  void popFront() ;

  // funzione di rimozione in coda
  void popBack() ;

  // funzione di rimozione dato un indice
  void remove(int index) ;

  // distruttore
  void clear() ;

  int size() const ;

  int front(bool* success = nullptr) const ;

  int back(bool* success = nullptr) const ;

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