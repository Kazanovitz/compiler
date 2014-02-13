#include "classhierarchy.hpp"

/****** ClassName Implemenation **************************************/

ClassName::ClassName(char* const x)
{
  m_spelling = x;
  m_parent_attribute = NULL;
}

ClassName::ClassName(const ClassName & other)
{
  m_spelling = strdup(other.m_spelling);
  m_parent_attribute = other.m_parent_attribute;
}

ClassName& ClassName::operator=(const ClassName & other)
{
  delete m_spelling;
  ClassName tmp(other);
  swap(tmp);
  return *this;
}

void ClassName::swap(ClassName & other)
{
  std::swap(m_spelling, other.m_spelling);
}

ClassName::~ClassName()
{
  delete( m_spelling );
}

void ClassName::accept(Visitor *v)
{ 
  v->visitClassName(this); 
}

ClassName* ClassName::clone() const
{
  return new ClassName(*this);
}

const char* ClassName::spelling()
{
  return m_spelling;
}

/****** ClassTable Implemenation **************************************/

bool ClassTable::exist( char* name ) {
  return (this->lookup(name) != NULL);
}

ClassNode* ClassTable::insert( char* name, ClassNode * s) {
  pair<ClassMap::iterator,bool> iret;
  typedef pair< char*, ClassNode* > classPair;
  iret = nameMap.insert( classPair(name, s) );
  if( iret.second == true ) {
    //insert was successful
    return NULL;
  } else {
    //cannot insert, there was a duplicate entry
    //return a pointer to the conflicting symbol
    return iret.first->second;
  }	

}

ClassNode* ClassTable::lookup( const char * name ) {
  ClassMap::const_iterator i;
  i = nameMap.find( (char*) name );
  if ( i != nameMap.end() ) {
    return i->second;
  } else {
    return NULL;
  }
}

ClassNode* ClassTable::getParentOf(const char* name) {
  ClassNode *node = this->lookup(name);
  if (node) {
    ClassNode *parent = this->lookup(node->superClass->spelling());
    return parent;
  } else {
    return NULL;
  }
}
