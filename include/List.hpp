#ifndef LIST_HPP
#define LIST_HPP

class List
{
public:
  // constructor di default
  List() = default;

  // delete del copy constructor per evitare warning del copilatore
  List(const List&) = delete;

  // distruttore (chiama clear)
  ~List();

  // delete del copy operator per evitare warning del copilatore
  List& operator=(const List&) = delete;

  // funzione di inserimento in testa
  void pushFront(int value);

  // funzione di inserimento in coda
  void pushBack(int value);

  // funzione di rimozione in testa
  void popFront();

  // funzione di rimozione in coda
  void popBack();

  // funzione di rimozione dato un indice
  void remove(int index);

  // svuota la lista
  void clear();

  // return della size
  int size() const;

  // return del valore in testa
  int front(bool* success = nullptr) const;

  // return del valore in coda
  int back(bool* success = nullptr) const;

private:
  struct Node
  {
    int val{};
    Node* next{ nullptr };
    Node* prev{ nullptr };
  };

  Node* m_head{ nullptr };
  Node* m_tail{ nullptr };
  int   m_size{ 0 };
};

#endif