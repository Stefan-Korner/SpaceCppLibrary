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
      std::string m_nodeName;
    public:
      NodeDef(const std::string& p_nodeName);
      virtual ~NodeDef();
      virtual std::string getNodeName() const;
      // for debugging
      virtual void dump(const std::string& p_prefix) const;
    };

    //-------------------------------------------------------------------------
    // Definition of a list in the data tree
    class ListDef: public NodeDef
    //-------------------------------------------------------------------------
    {
      NodeDef* m_entryDef;
    public:
      ListDef(const std::string& p_nodeName);
      virtual ~ListDef();
      // takes over the ownership of p_entryDef
      virtual void setEntryDef(NodeDef* p_entryDef);
      virtual const NodeDef* getEntryDef() const;
      // for debugging
      virtual void dump(const std::string& p_prefix) const;
    private:
      ListDef();
    };

    //-------------------------------------------------------------------------
    // Definition of a struct in the data tree
    class StructDef: public NodeDef
    //-------------------------------------------------------------------------
    {
      std::list<NodeDef*> m_attributesDef;
    public:
      StructDef(const std::string& p_nodeName);
      virtual ~StructDef();
      // takes over the ownership of p_attributeDef
      virtual void addAttributeDef(NodeDef* p_attributeDef);
      const std::list<NodeDef*>& getAttributesDef() const;
      // for debugging
      virtual void dump(const std::string& p_prefix) const;
    private:
      StructDef();
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
    };

    ////////////////////
    // Node Instances //
    ////////////////////

    //-------------------------------------------------------------------------
    // Instance of a node in the data tree
    class Node
    //-------------------------------------------------------------------------
    {
      const NodeDef* m_nodeDef;
    public:
      Node(const NodeDef* p_nodeDef);
      virtual ~Node();
      const NodeDef* getNodeDef() const;
      virtual std::string getNodeName() const;
      // generic access to sub-nodes, only provided by List and Struct
      virtual Node& operator[](size_t p_pos) throw(UTIL::Exception);
      // only provided by List
      virtual Node& addNode() throw(UTIL::Exception);
      virtual void addNodes(size_t p_nr) throw(UTIL::Exception);
      // for debugging
      virtual void dump(const std::string& p_prefix) const;
    private:
      Node();
    };

    //-------------------------------------------------------------------------
    // Instance of a list in the data tree
    class List: public Node
    //-------------------------------------------------------------------------
    {
      std::list<Node*> m_entries;
    public:
      List(const ListDef* p_listDef);
      virtual ~List();
      const ListDef* getListDef() const;
      std::list<Node*>& getEntries();
      // overloaded from Node
      virtual Node& operator[](size_t p_pos) throw(UTIL::Exception);
      // overloaded from Node
      virtual Node& addNode() throw(UTIL::Exception);
      // for debugging
      virtual void dump(const std::string& p_prefix) const;
    private:
      List();
    };

    //-------------------------------------------------------------------------
    // Instance of a struct in the data tree
    class Struct: public Node
    //-------------------------------------------------------------------------
    {
      std::list<Node*> m_attributes;
    public:
      Struct(const StructDef* p_structDef);
      virtual ~Struct();
      const StructDef* getStructDef() const;
      std::list<Node*>& getAttributes();
      // overloaded from Node
      virtual Node& operator[](size_t p_pos) throw(UTIL::Exception);
      // for debugging
      virtual void dump(const std::string& p_prefix) const;
    private:
      Struct();
    };

    //-------------------------------------------------------------------------
    // Instance of a field in the data tree
    class Field: public Node
    //-------------------------------------------------------------------------
    {
    public:
      Field(const FieldDef* p_fieldDef);
      virtual ~Field();
      const FieldDef* getFieldDef() const;
      // for debugging
      virtual void dump(const std::string& p_prefix) const;
    private:
      Field();
    };

    ///////////////////////////
    // Node Instance Factory //
    ///////////////////////////
    Node* createNode(const NodeDef* p_nodeDef);
  }
}

#endif
