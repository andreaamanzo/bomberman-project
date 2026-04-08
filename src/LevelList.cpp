#include "LevelList.hpp"
#include <iostream>

LevelList::LevelList(const char* levelPaths[], int numLevels)
{
  if ( numLevels <= 0)
  {
    m_currentLevel = nullptr;
    m_size = 0;

    return;
  }

  Node* current{ new Node{Level(1, levelPaths[0]), nullptr, nullptr} };
  m_currentLevel = current;

  for (int i{ 1 } ; i < numLevels ; i++)
  {
    Node* next{ new Node{Level(i + 1, levelPaths[i]), current, nullptr} };
    current -> next = next;
    current = next;
  }

  m_size = numLevels;
}

LevelList::~LevelList()
{
  clear();
}

void LevelList::goNext()
{
  if (m_currentLevel == nullptr || m_currentLevel -> next == nullptr) return;

  m_currentLevel = m_currentLevel -> next;
}

void LevelList::goBack()
{
  if (m_currentLevel == nullptr || m_currentLevel -> prev == nullptr) return;

  m_currentLevel = m_currentLevel -> prev;
}

void LevelList::removeCurrent()
{
  if (m_currentLevel == nullptr) return;

  Node* deleter = nullptr;

  if (m_currentLevel -> prev == nullptr)
  {
    deleter = m_currentLevel;
    m_currentLevel = m_currentLevel -> next;
    if(m_currentLevel != nullptr) m_currentLevel -> prev = nullptr;
  }
  else if (m_currentLevel -> next == nullptr)
  {
    deleter = m_currentLevel;
    m_currentLevel = m_currentLevel -> prev;
    if(m_currentLevel != nullptr) m_currentLevel -> next = nullptr;
  }
  else 
  {
    deleter = m_currentLevel;
    m_currentLevel = m_currentLevel -> next;

    (deleter -> prev) -> next = m_currentLevel;
    m_currentLevel -> prev = deleter -> prev;
  }
  delete deleter;

  m_size--;
}

void LevelList::clear()
{
  while (m_currentLevel != nullptr)
  {
    removeCurrent();
  }
}

int LevelList::size() const
{
  return m_size;
}

Level* LevelList::getLevel()
{
  if (m_currentLevel == nullptr)
  {
    std::cerr << "null ptr\n";
    return nullptr;
  }
  

  return &(m_currentLevel->val);
}