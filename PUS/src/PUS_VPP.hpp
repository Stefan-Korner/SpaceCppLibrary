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
// PUS Services - Variable Packet Module                                      *
//*****************************************************************************
#ifndef PUS_VPP_hpp
#define PUS_VPP_hpp

#include "PUS_PACKET.hpp"
#include "UTIL_VPP.hpp"

namespace PUS
{
  namespace VPP
  {
    /////////////
    // Packets //
    /////////////

    //-------------------------------------------------------------------------
    class TMpacket: public PUS::PACKET::TMpacket
    //-------------------------------------------------------------------------
    {
    public:
      // constructors and destructur
      TMpacket();
      TMpacket(size_t p_bufferSize);
      TMpacket(void* p_buffer, size_t p_bufferSize);
      TMpacket(const void* p_buffer, size_t p_bufferSize, bool p_copyBuffer);
      TMpacket(const TMpacket& p_du);
      const TMpacket& operator=(const TMpacket& p_du);
      virtual ~TMpacket();

      virtual void setParameterRootType(const UTIL::VPP::NodeDef* p_rootType);

    protected:
      UTIL::VPP::Node* m_parameters;
    };

    //-------------------------------------------------------------------------
    class TCpacket: public PUS::PACKET::TCpacket
    //-------------------------------------------------------------------------
    {
    public:
      // constructors and destructur
      TCpacket();
      TCpacket(size_t p_bufferSize);
      TCpacket(void* p_buffer, size_t p_bufferSize);
      TCpacket(const void* p_buffer, size_t p_bufferSize, bool p_copyBuffer);
      TCpacket(const TCpacket& p_du);
      const TCpacket& operator=(const TCpacket& p_du);
      virtual ~TCpacket();

      virtual void setParameterRootType(const UTIL::VPP::NodeDef* p_rootType);

    protected:
      UTIL::VPP::Node* m_parameters;
    };

    ////////////////////
    // Node Instances //
    ////////////////////

    //-------------------------------------------------------------------------
    // Abstract interface
    class Node
    //-------------------------------------------------------------------------
    {
    public:
      Node() {}
      virtual ~Node() {}
/*
      // recursive walk through all nodes, returns nextPos
      virtual size_t alignFromPacket(const UTIL::DU& p_du, size_t p_pos)
        throws(UTIL::EXCEPTION) = 0;
      virtual size_t alignFromNodes(size_t p_pos)
        throws(UTIL::EXCEPTION) = 0;
*/
    };

    //-------------------------------------------------------------------------
    // Instance of a list in the data tree
    class List: public UTIL::VPP::List, public Node
    //-------------------------------------------------------------------------
    {
      friend class NodeFactory;
    public:
      virtual ~List();
/*
      // recursive walk through all nodes, returns nextPos
      virtual size_t alignFromPacket(const UTIL::DU& p_du, size_t p_pos)
        throws(UTIL::EXCEPTION);
      virtual size_t alignFromNodes(size_t p_pos) throws(UTIL::EXCEPTION);
*/
    protected:
      List(const UTIL::VPP::ListDef* p_listDef);
//      size_t m_pos;
    private:
      List();
      List(const List& p_other);
      const List& operator=(const List& p_other);
    };

    //-------------------------------------------------------------------------
    // Instance of a struct in the data tree
    class Struct: public UTIL::VPP::Struct, public Node
    //-------------------------------------------------------------------------
    {
      friend class NodeFactory;
    public:
      virtual ~Struct();
/*
      // recursive walk through all nodes, returns nextPos
      virtual size_t alignFromPacket(const UTIL::DU& p_du, size_t p_pos)
        throws(UTIL::EXCEPTION);
      virtual size_t alignFromNodes(size_t p_pos) throws(UTIL::EXCEPTION);
*/
    protected:
      Struct(const UTIL::VPP::StructDef* p_structDef);
    private:
      Struct();
      Struct(const Struct& p_other);
      const Struct& operator=(const Struct& p_other);
    };

    //-------------------------------------------------------------------------
    // Instance of a field in the data tree
    class Field: public UTIL::VPP::Field, public Node
    //-------------------------------------------------------------------------
    {
      friend class NodeFactory;
    public:
      virtual ~Field();
/*
      // recursive walk through all nodes, returns nextPos
      virtual size_t alignFromPacket(const UTIL::DU& p_du, size_t p_pos)
        throws(UTIL::EXCEPTION);
      virtual size_t alignFromNodes(size_t p_pos) throws(UTIL::EXCEPTION);
*/
    protected:
      Field(const UTIL::VPP::FieldDef* p_fieldDef);
//      size_t m_pos;

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
    class NodeFactory: public UTIL::VPP::NodeFactory
    //-------------------------------------------------------------------------
    {
    public:
      // an instance of this class (or a derived class) shall
      // be created and destroyed in main()
      NodeFactory();
      virtual ~NodeFactory();

      // factory method
      virtual UTIL::VPP::Node*
      createNode(const UTIL::VPP::NodeDef* p_nodeDef);

    private:
      NodeFactory(const NodeFactory& p_service);
      const NodeFactory& operator=(const NodeFactory& p_task);
    };
  }
}

#endif
