#ifndef CLASSHIERARCHY_HPP
#define CLASSHIERARCHY_HPP

#include "ast.hpp"
#include "attribute.hpp"
#include "symtab.hpp"
#include <unordered_map>
#include <cstddef>
#include <cstring>
#include <string>

class ClassName {
    char* m_spelling; // "name" of the class
    
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
    SymScope* scope;    
};

typedef std::unordered_map<const std::string, ClassNode*, std::hash<std::string> > ClassMap;

class ClassTable {
    ClassMap nameMap;
    ClassNode * topClass;
    
    public:
    ClassTable();
    ~ClassTable();

    bool exist( char* const name );
    ClassNode* insert( char* const name, ClassNode * node );
    ClassNode* insert( char* const name, char* const superClass, ClassImpl * astNode, SymScope * classScope );
    ClassNode* lookup( char* const name );
    
    ClassNode* getParentOf( char* const name );
     
    bool exist( ClassName* name );
    ClassNode* insert( ClassName * name, ClassNode * node );
    ClassNode* insert( ClassName * name, ClassName * superClass, ClassImpl * astNode, SymScope * classScope );
    ClassNode* lookup( ClassName * name );
    
    ClassNode* getParentOf( ClassName * name );
};

#endif //CLASSHIERARCHY_HPP
