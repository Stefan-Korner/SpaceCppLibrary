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
// Variable Packets - Unit Tests                                              *
//*****************************************************************************
#include "UTIL_VPP.hpp"

#include <iostream>

using namespace std;

// definition tree
//
// struct1Def[0].field1Def(0,8)
// struct1Def[1].field2Def(0,8)
// struct1Def[2].list1Def(0,8).field3Def(0,8)
// struct1Def[3].struct2Def[0].field4Def(0,8)
// struct1Def[3].struct2Def[1].field5Def(0,8)
// struct1Def[3].struct2Def[2].list2Def(0,8).struct3Def[0].field6Def(0,16)
// struct1Def[3].struct2Def[2].list2Def(0,8).struct3Def[1].list4Def(0,8).field7Def(0,16)

// node tree
//
// struct1Def[0].field1Def(INT32(0))
// struct1Def[1].field2Def(INT32(1))
// struct1Def[2].list1Def[0].field3Def(INT32(20))
// struct1Def[2].list1Def[1].field3Def(INT32(21))
// struct1Def[2].list1Def[2].field3Def(INT32(22))
// struct1Def[2].list1Def[3].field3Def(INT32(23))
// struct1Def[2].list1Def[4].field3Def(INT32(24))
// struct1Def[3].struct2Def[0].field4Def(INT32(30))
// struct1Def[3].struct2Def[1].field5Def(INT32(31))
// struct1Def[3].struct2Def[2].list2Def[0].struct3Def[0].field6Def(INT32(3200))
// struct1Def[3].struct2Def[2].list2Def[0].struct3Def[1].list4Def[0].field7Def(INT32(32010))
// struct1Def[3].struct2Def[2].list2Def[0].struct3Def[1].list4Def[1].field7Def(INT32(32011))
// struct1Def[3].struct2Def[2].list2Def[1].struct3Def[0].field6Def(INT32(3210))
// struct1Def[3].struct2Def[2].list2Def[1].struct3Def[1].list4Def[0].field7Def(INT32(32110))
// struct1Def[3].struct2Def[2].list2Def[1].struct3Def[1].list4Def[1].field7Def(INT32(32111))
// struct1Def[3].struct2Def[2].list2Def[1].struct3Def[1].list4Def[2].field7Def(INT32(32112))
// struct1Def[3].struct2Def[2].list2Def[2].struct3Def[0].field6Def(INT32(3220))
// struct1Def[3].struct2Def[2].list2Def[2].struct3Def[1].list4Def.NIL

// binary format of the node tree (instC)
//
// +--------------+
// | INT8(0)      | field1Def
// +--------------+
// | INT8(1)      | field2Def
// +--------------+
// | int8(5)      | list1Def
// +--------------+
// | INT8(20)     | field3Def
// +--------------+
// | INT8(21)     | field3Def
// +--------------+
// | INT8(22)     | field3Def
// +--------------+
// | INT8(23)     | field3Def
// +--------------+
// | INT8(24)     | field3Def
// +--------------+
// | INT8(30)     | field4Def
// +--------------+
// | INT8(31)     | field5Def
// +--------------+
// | int8(3)      | list2Def
// +--------------+
// | INT16(3200)  | field6Def
// +--------------+
// | int8(2)      | list4Def
// +--------------+
// | INT16(32010) | field7Def
// +--------------+
// | INT16(32011) | field7Def
// +--------------+
// | INT16(3210)  | field6Def
// +--------------+
// | int8(3)      | list4Def
// +--------------+
// | INT16(32110) | field7Def
// +--------------+
// | INT16(32111) | field7Def
// +--------------+
// | INT16(32112) | field7Def
// +--------------+
// | INT16(3220)  | field6Def
// +--------------+
// | int8(0)      | list4Def
// +--------------+

const size_t INST_C_DATA_SIZE = 30;
const uint8_t INST_C_DATA[INST_C_DATA_SIZE] =
{
  0x00, // field1Def
  0x01, // field2Def
  0x05, // list1Def
  0x14, // field3Def
  0x15, // field3Def
  0x16, // field3Def
  0x17, // field3Def
  0x18, // field3Def
  0x1e, // field4Def
  0x1f, // field5Def
  0x03, // list2Def
  0x0c, // field6Def
  0x80,
  0x02, // list4Def
  0x7d, // field7Def
  0x0a,
  0x7d, // field7Def
  0x0b,
  0x0c, // field6Def
  0x8a,
  0x03, // list4Def
  0x7d, // field7Def
  0x6e,
  0x7d, // field7Def
  0x6f,
  0x7d, // field7Def
  0x70,
  0x0c, // field6Def
  0x94,
  0x00  // list4Def
};

//-----------------------------------------------------------------------------
int main()
//-----------------------------------------------------------------------------
{
  UTIL::VPP::NodeFactory nodeFactory;

  // construct definition tree
  cout << "--- definition tree ---" << endl;
  UTIL::VPP::StructDef* struct1Def = new UTIL::VPP::StructDef("struct1Def");
   UTIL::VPP::FieldDef* field1Def =
     new UTIL::VPP::FieldDef("field1Def", UTIL::VPP::FieldDef::BIT_FIELD, 0, 8);
   struct1Def->addAttributeDef(field1Def);
   UTIL::VPP::FieldDef* field2Def =
     new UTIL::VPP::FieldDef("field2Def", UTIL::VPP::FieldDef::BYTE_FIELD, 0, 8);
   struct1Def->addAttributeDef(field2Def);
   UTIL::VPP::ListDef* list1Def = new UTIL::VPP::ListDef("list1Def", 0, 8);
    UTIL::VPP::FieldDef* field3Def =
      new UTIL::VPP::FieldDef("field3Def", UTIL::VPP::FieldDef::UNSIGNED_FIELD, 0, 8);
    list1Def->setEntryDef(field3Def);
   struct1Def->addAttributeDef(list1Def);
   UTIL::VPP::StructDef* struct2Def = new UTIL::VPP::StructDef("struct2Def");
    UTIL::VPP::FieldDef* field4Def =
      new UTIL::VPP::FieldDef("field4Def", UTIL::VPP::FieldDef::STRING_FIELD, 0, 8);
    struct2Def->addAttributeDef(field4Def);
    UTIL::VPP::FieldDef* field5Def =
      new UTIL::VPP::FieldDef("field5Def", UTIL::VPP::FieldDef::ABS_TIME_FIELD, 0, 8);
    struct2Def->addAttributeDef(field5Def);
    UTIL::VPP::ListDef* list2Def = new UTIL::VPP::ListDef("list2Def", 0, 8);
     UTIL::VPP::StructDef* struct3Def = new UTIL::VPP::StructDef("struct3Def");
      UTIL::VPP::FieldDef* field6Def =
        new UTIL::VPP::FieldDef("field6Def", UTIL::VPP::FieldDef::BIT_FIELD, 0, 16);
      struct3Def->addAttributeDef(field6Def);
      UTIL::VPP::ListDef* list4Def = new UTIL::VPP::ListDef("list4Def", 0, 8);
       UTIL::VPP::FieldDef* field7Def =
         new UTIL::VPP::FieldDef("field7Def", UTIL::VPP::FieldDef::BYTE_FIELD, 0, 16);
       list4Def->setEntryDef(field7Def);
      struct3Def->addAttributeDef(list4Def);
     list2Def->setEntryDef(struct3Def);
    struct2Def->addAttributeDef(list2Def);
   struct1Def->addAttributeDef(struct2Def);
  // dump definition tree
  struct1Def->dump("Def");
  cout << endl;

  try
  {
    // construct instance trees
    cout << "--- instance trees ---" << endl;
    // this code creates a memory leak (but no problem for functional tests)
    UTIL::VPP::Node& instA =
      *(UTIL::VPP::NodeFactory::instance()->createNode(struct1Def));
    instA[2].addNodes(5);
    instA[3][2].addNodes(3);
    instA[3][2][0][1].addNodes(2);
    instA[3][2][1][1].addNodes(3);
    instA[0].setValue(UTIL::Value(1234));
    instA[2][0].setValue(UTIL::Value(11.22));
    // dump instance tree
    instA.dump("instA");
    cout << endl;

    UTIL::VPP::Node& instB =
      *(UTIL::VPP::NodeFactory::instance()->createNode(struct1Def));
    instB[2].addNodes(5);
    instB[3][2].addNodes(3);
    instB[3][2][0][1].addNodes(2);
    instB[3][2][1][1].addNodes(3);
    instB[1].setValue("this is a text");
    instB[2][0].setValue(UTIL::Value(33.44));
    instB[2][1].setValue(UTIL::Value("funny text"));
    instB[2][3].setValue(UTIL::Value(false));
    // dump instance tree
    instB.dump("instB");
    cout << endl;

    cout << "--- move ---" << endl;
    instA.moveNodes(instB);

    // dump instance tree
    instA.dump("InstA");
    cout << endl;

    // dump instance tree
    instB.dump("instB");
    cout << endl;

    cout << "--- tree with full data ---" << endl;
    UTIL::VPP::Node& instC =
      *(UTIL::VPP::NodeFactory::instance()->createNode(struct1Def));
    instC[2].addNodes(5);
    instC[3][2].addNodes(3);
    instC[3][2][0][1].addNodes(2);
    instC[3][2][1][1].addNodes(3);
    instC[0].setValue(UTIL::Value(0));
    instC[1].setValue(UTIL::Value(1));
    instC[2][0].setValue(UTIL::Value(20));
    instC[2][1].setValue(UTIL::Value(21));
    instC[2][2].setValue(UTIL::Value(22));
    instC[2][3].setValue(UTIL::Value(23));
    instC[2][4].setValue(UTIL::Value(24));
    instC[3][0].setValue(UTIL::Value(30));
    instC[3][1].setValue(UTIL::Value(31));
    instC[3][2][0][0].setValue(UTIL::Value(3200));
    instC[3][2][0][1][0].setValue(UTIL::Value(32010));
    instC[3][2][0][1][1].setValue(UTIL::Value(32011));
    instC[3][2][1][0].setValue(UTIL::Value(3210));
    instC[3][2][1][1][0].setValue(UTIL::Value(32110));
    instC[3][2][1][1][1].setValue(UTIL::Value(32111));
    instC[3][2][1][1][2].setValue(UTIL::Value(32112));
    instC[3][2][2][0].setValue(UTIL::Value(3220));
    // dump instance tree
    instC.dump("instC");
    size_t instCsize = UTIL::VPP::getBinarySize(&instC);
    cout << "instCsize = " << (instCsize / 8) << endl;
    cout << endl;
    if(instCsize != INST_C_DATA_SIZE)
    {
      cout << "Invalid data size: "
           << (instCsize / 8)
           << ", expected: "
           << INST_C_DATA_SIZE
           << endl;
      return -1;
    }
  }
  catch(const UTIL::Exception& ex)
  {
    cout << "Exception: " << ex.what() << endl;
    return -1;
  }

  // delete definition tree
  delete struct1Def;
  return 0;
}
