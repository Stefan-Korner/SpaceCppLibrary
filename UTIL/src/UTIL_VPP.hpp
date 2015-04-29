//*****************************************************************************
// (C) 2015, Stefan Korner, Austria                                           *
//                                                                            *
// The Space C++ Library is free software; you can redistribute it and/or     *
// modify it under the terms of the GNU Lesser General Public License as      *
// published by the Free Software Foundation; either version 2.1 of the       *
// License, or (at your option) any later version.                            *
//                                                                            *
// The Space C++ Library is distributed in the hope that it will be useful,   *
// but WITHOUT ANY WARRANTY; without even the implied warranty of             *
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser    *
// General Public License for more details.                                   *
//*****************************************************************************
// Variable Packets Definition and Instances                                  *
//*****************************************************************************
#ifndef UTIL_VPP_hpp
#define UTIL_VPP_hpp

#include <list>
#include <string>
#include "UTIL_EXCEPTION.hpp"

namespace UTIL
{
  namespace VPP
  {
    //////////////////////
    // Node Definitions //
    //////////////////////

    //-------------------------------------------------------------------------
    // Definition of a node in the data tree
    class NodeDef
    //-------------------------------------------------------------------------
    {
    public:
      NodeDef(const std::string& p_nodeName);
      virtual ~NodeDef();
      virtual std::string getNodeName() const;
      // for debugging
      virtual void dump(const std::string& p_prefix) const;
    protected:
      std::string m_nodeName;
    private:
      NodeDef();
      NodeDef(const NodeDef& p_other);
      const NodeDef& operator=(const NodeDef& p_other);
    };

    //-------------------------------------------------------------------------
    // Definition of a list in the data tree
    class ListDef: public NodeDef
    //-------------------------------------------------------------------------
    {
    public:
      ListDef(const std::string& p_nodeName);
      virtual ~ListDef();
      // takes over the ownership of p_entryDef
      virtual void setEntryDef(NodeDef* p_entryDef);
      virtual const NodeDef* getEntryDef() const;
      // for debugging
      virtual void dump(const std::string& p_prefix) const;
    protected:
      NodeDef* m_entryDef;
    private:
      ListDef();
      ListDef(const ListDef& p_other);
      const ListDef& operator=(const ListDef& p_other);
    };

    //-------------------------------------------------------------------------
    // Definition of a struct in the data tree
    class StructDef: public NodeDef
    //-------------------------------------------------------------------------
    {
    public:
      StructDef(const std::string& p_nodeName);
      virtual ~StructDef();
      // takes over the ownership of p_attributeDef
      virtual void addAttributeDef(NodeDef* p_attributeDef);
      const std::list<NodeDef*>& getAttributesDef() const;
      // for debugging
      virtual void dump(const std::string& p_prefix) const;
    protected:
      std::list<NodeDef*> m_attributesDef;
    private:
      StructDef();
      StructDef(const StructDef& p_other);
      const StructDef& operator=(const StructDef& p_other);
    };

    //-------------------------------------------------------------------------
    // Definition of a field in the data tree
    class FieldDef: public NodeDef
    //-------------------------------------------------------------------------
    {
    public:
      FieldDef(const std::string& p_nodeName);
      virtual ~FieldDef();
      // for debugging
      virtual void dump(const std::string& p_prefix) const;
    private:
      FieldDef();
      FieldDef(const FieldDef& p_other);
      const FieldDef& operator=(const FieldDef& p_other);
    };

    ////////////////////
    // Node Instances //
    ////////////////////

    //-------------------------------------------------------------------------
    // Instance of a node in the data tree
    class Node
    //-------------------------------------------------------------------------
    {
      friend class NodeFactory;
    public:
      virtual ~Node();
      const NodeDef* getNodeDef() const;
      virtual std::string getNodeName() const;
      // generic access to sub-nodes, only provided by List and Struct
      virtual Node& operator[](size_t p_pos) throw(UTIL::Exception);
      // only provided by List
      virtual Node& addNode() throw(UTIL::Exception);
      virtual void addNodes(size_t p_nr) throw(UTIL::Exception);
      // only provided by List, takes over the ownership of p_node
      virtual void appendNode(Node* p_node) throw(UTIL::Exception);
      // only provided by List, ownership passed to caller
      virtual Node* popNode() throw(UTIL::Exception);
      // moves the childs from p_node to this
      virtual void moveNodes(Node& p_node) throw(UTIL::Exception);
      // for debugging
      virtual void dump(const std::string& p_prefix) const;
    protected:
      Node(const NodeDef* p_nodeDef);
      const NodeDef* m_nodeDef;
    private:
      Node();
      Node(const Node& p_other);
      const Node& operator=(const Node& p_other);
    };

    //-------------------------------------------------------------------------
    // Instance of a list in the data tree
    class List: public Node
    //-------------------------------------------------------------------------
    {
      friend class NodeFactory;
    public:
      virtual ~List();
      const ListDef* getListDef() const;
      std::list<Node*>& getEntries();
      // overloaded from Node
      virtual Node& operator[](size_t p_pos) throw(UTIL::Exception);
      // overloaded from Node
      virtual Node& addNode() throw(UTIL::Exception);
      // overloaded from Node, takes over the ownership of p_node
      virtual void appendNode(Node* p_node) throw(UTIL::Exception);
      // overloaded from Node, ownership passed to caller
      virtual Node* popNode() throw(UTIL::Exception);
      // moves the childs from p_node to this
      virtual void moveNodes(Node& p_node) throw(UTIL::Exception);
      // for debugging
      virtual void dump(const std::string& p_prefix) const;
    protected:
      List(const ListDef* p_listDef);
      std::list<Node*> m_entries;
    private:
      List();
      List(const List& p_other);
      const List& operator=(const List& p_other);
    };

    //-------------------------------------------------------------------------
    // Instance of a struct in the data tree
    class Struct: public Node
    //-------------------------------------------------------------------------
    {
      friend class NodeFactory;
    public:
      virtual ~Struct();
      const StructDef* getStructDef() const;
      std::list<Node*>& getAttributes();
      // overloaded from Node
      virtual Node& operator[](size_t p_pos) throw(UTIL::Exception);
      // moves the childs from p_node to this
      virtual void moveNodes(Node& p_node) throw(UTIL::Exception);
      // for debugging
      virtual void dump(const std::string& p_prefix) const;
    protected:
      Struct(const StructDef* p_structDef);
      std::list<Node*> m_attributes;
    private:
      Struct();
      Struct(const Struct& p_other);
      const Struct& operator=(const Struct& p_other);
    };

    //-------------------------------------------------------------------------
    // Instance of a field in the data tree
    class Field: public Node
    //-------------------------------------------------------------------------
    {
      friend class NodeFactory;
    public:
      virtual ~Field();
      const FieldDef* getFieldDef() const;
      // for debugging
      virtual void dump(const std::string& p_prefix) const;
    protected:
      Field(const FieldDef* p_fieldDef);
    private:
      Field();
      Field(const Field& p_other);
      const Field& operator=(const Field& p_other);
    };

    //////////////////
    // Node Factory //
    //////////////////

    //-------------------------------------------------------------------------
    // Supports specialization
    class NodeFactory
    //-------------------------------------------------------------------------
    {
    public:
      // an instance of this class (or a derived class) shall
      // be created and destroyed in main()
      NodeFactory();
      virtual ~NodeFactory();

      // NodeFactory is a singleton
      static NodeFactory* instance();

      // factory method
      virtual Node* createNode(const NodeDef* p_nodeDef);

    private:
      NodeFactory(const NodeFactory& p_service);
      const NodeFactory& operator=(const NodeFactory& p_task);

      static NodeFactory* s_instance;
    };
  }
}

#endif
