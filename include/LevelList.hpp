#ifndef LEVEL_LIST_HPP
#define LEVEL_LIST_HPP

#include "Level.hpp"

class LevelList
{
public:
  // constructor di default
  LevelList(const char* levelPaths[], int numLevels);

  // delete del copy constructor per evitare warning del copilatore
  LevelList(const LevelList&) = delete;

  // distruttore (chiama clear)
  ~LevelList();

  // delete del copy operator per evitare warning del copilatore
  LevelList& operator=(const LevelList&) = delete;

  Level* getLevel();

  // funzione per passare al livello successivo
  void goNext();

  // funzione per tornare al livello precedente
  void goBack();

  // funzione di rimozione dato un indice
  void removeCurrent();

  // svuota la lista
  void clear();

  // return della size
  int size() const;

  bool isCurrFirst() const;
  bool isCurrLast()  const;

private:
  struct Node
  {
    Level val;
    Node* prev{ nullptr };
    Node* next{ nullptr };
  };

  Node* m_currentLevel{ nullptr };
  int   m_size{ 0 };
};

#endif