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

    //////////////////////
    // Node Definitions //
    //////////////////////

    //-------------------------------------------------------------------------
    // Definition of a list in the data tree
    class ListDef: public UTIL::VPP::ListDef
    //-------------------------------------------------------------------------
    {
    public:
      ListDef(const std::string& p_nodeName,
              size_t p_counterBitOffset,
              size_t p_counterBitLength);
      virtual ~ListDef();
      virtual size_t getCounterBitOffset() const;
      virtual size_t getCounterBitLength() const;
      // for debugging
      virtual void dump(const std::string& p_prefix) const;
    protected:
      size_t m_counterBitOffset;
      size_t m_counterBitLength;
    private:
      ListDef();
      ListDef(const ListDef& p_other);
      const ListDef& operator=(const ListDef& p_other);
    };

    //-------------------------------------------------------------------------
    // Definition of a struct in the data tree
    class StructDef: public UTIL::VPP::StructDef
    //-------------------------------------------------------------------------
    {
    public:
      StructDef(const std::string& p_nodeName);
      virtual ~StructDef();
    private:
      StructDef();
      StructDef(const StructDef& p_other);
      const StructDef& operator=(const StructDef& p_other);
    };

    //-------------------------------------------------------------------------
    // Definition of a field in the data tree
    class FieldDef: public UTIL::VPP::FieldDef
    //-------------------------------------------------------------------------
    {
    public:
      enum FieldType
      {
        BIT_FIELD,
        BYTE_FIELD,
        UNSIGNED_FIELD,
        STRING_FIELD,
        ABS_TIME_FIELD
      };
      FieldDef(const std::string& p_nodeName,
               FieldType p_fieldType,
               size_t p_bitOffset,
               size_t p_bitLength);
      virtual ~FieldDef();
      virtual FieldType getFieldType() const;
      virtual size_t getBitOffset() const;
      virtual size_t getBitLength() const;
      // for debugging
      virtual void dump(const std::string& p_prefix) const;
    protected:
      FieldType m_fieldType;
      size_t m_bitOffset;
      size_t m_bitLength;
    private:
      FieldDef();
      FieldDef(const FieldDef& p_other);
      const FieldDef& operator=(const FieldDef& p_other);
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
      // recursive walk through all nodes, returns nextPos
      virtual size_t alignFromPacket(const UTIL::DU& p_du, size_t p_pos)
        throws(UTIL::EXCEPTION) = 0;
      virtual size_t alignFromNodes(size_t p_pos)
        throws(UTIL::EXCEPTION) = 0;
    };

    //-------------------------------------------------------------------------
    // Instance of a list in the data tree
    class List: public UTIL::VPP::List, public Node
    //-------------------------------------------------------------------------
    {
      friend class NodeFactory;
    public:
      virtual ~List();
      // recursive walk through all nodes, returns nextPos
      virtual size_t alignFromPacket(const UTIL::DU& p_du, size_t p_pos)
        throws(UTIL::EXCEPTION);
      virtual size_t alignFromNodes(size_t p_pos) throws(UTIL::EXCEPTION);
    protected:
      List(const UTIL::VPP::ListDef* p_listDef);
      size_t m_pos;
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
      // recursive walk through all nodes, returns nextPos
      virtual size_t alignFromPacket(const UTIL::DU& p_du, size_t p_pos)
        throws(UTIL::EXCEPTION);
      virtual size_t alignFromNodes(size_t p_pos) throws(UTIL::EXCEPTION);
    protected:
      Struct(const UTIL::VPP::StructDef* p_structDef);
      std::list<Node*> m_attributes;
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
      // recursive walk through all nodes, returns nextPos
      virtual size_t alignFromPacket(const UTIL::DU& p_du, size_t p_pos)
        throws(UTIL::EXCEPTION);
      virtual size_t alignFromNodes(size_t p_pos) throws(UTIL::EXCEPTION);

      // data access, only acess of the proper type is possible
      virtual uint32_t getBits() const throw(UTIL::Exception);
      virtual void setBits(uint32_t p_value) throw(UTIL::Exception);

      virtual size_t getByteLength() const throw(UTIL::Exception);
      virtual const uint8_t* getBytes(size_t p_byteLength) const
        throw(UTIL::Exception);
      virtual void setBytes(const void* p_bytes, size_t p_byteLength)
        throw(UTIL::Exception);

      virtual uint32_t getUnsigned() const throw(UTIL::Exception);
      virtual void setUnsigned(uint32_t p_value) throw(UTIL::Exception);

      virtual uint64_t getBigUnsigned() const throw(UTIL::Exception);
      virtual void setBigUnsigned(uint64_t p_value) throw(UTIL::Exception);

      virtual std::string getString() const throw(UTIL::Exception);
      virtual void setString(const std::string& p_string)
        throw(UTIL::Exception);

      virtual UTIL::AbsTime getAbsTime(uint32_t p_timeCode) const
        throw(UTIL::Exception);
      virtual void setAbsTime(uint32_t p_timeCode,
                              const UTIL::AbsTime& p_time)
        throw(UTIL::Exception);

    protected:
      Field(const UTIL::VPP::FieldDef* p_fieldDef);
      size_t m_pos;

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
