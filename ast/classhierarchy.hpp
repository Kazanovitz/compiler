#ifndef CLASSHIERARCHY_HPP
#define CLASSHIERARCHY_HPP

#include "ast.hpp"
#include "attribute.hpp"
#include <unordered_map>
#include <cstddef>
#include <cstring>

class ClassName {
  char* m_spelling; // "name" of the symbol
  
  public:
  
  ClassName(const ClassName &);
  ClassName &operator=(const ClassName &);
  ClassName(char* const x);
  ~ClassName();
  virtual void accept(Visitor *v);
  virtual ClassName *clone() const;
  void swap(ClassName &);
  
  const char* spelling();
  
  Attribute* m_parent_attribute;
};

class ClassNode {
  public:
  
  ClassName *name;
  ClassName *superClass;
  
  ClassImpl *p;  
};

typedef std::unordered_map< char*, ClassNode*, std::hash<char*> > ClassMap;

class ClassTable {
  ClassMap nameMap;
  ClassNode* topClass;
  
  public:
  
  bool exist( char* name );
  ClassNode* insert( char* name, ClassNode * s); 
  ClassNode* lookup( const char * name );
  
  ClassNode* getParentOf(const char* name);
};

#endif //CLASSHIERARCHY_HPP
