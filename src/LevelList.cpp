#include <LevelList.hpp>

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
  }
  else if (m_currentLevel -> next == nullptr)
  {
    deleter = m_currentLevel;
    m_currentLevel = m_currentLevel -> prev;
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
  if (m_currentLevel == nullptr) return nullptr;

  return &(m_currentLevel->val);
}