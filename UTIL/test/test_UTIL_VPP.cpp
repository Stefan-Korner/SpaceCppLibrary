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
// struct1[0].field1(0,8)
// struct1[1].field2(0,8)
// struct1[2].list1(0,8).field3(0,8)
// struct1[3].struct2[0].field4(0,8)
// struct1[3].struct2[1].field5(0,8)
// struct1[3].struct2[2].list2(0,8).struct3[0].field6(0,16)
// struct1[3].struct2[2].list2(0,8).struct3[1].list3(0,8).field7(0,16)
//
// -struct1
//   |
//   +-[0]field1
//   |
//   +-[1]field2
//   |
//   +-[2]list1
//   |     |
//   |     +-field3
//   |
//   +-[3]struct2
//         |
//         +-[0]field4
//         |
//         +-[1]field5
//         |
//         +-[2]list2
//               |
//               +-struct3
//                  |
//                  +-[0]field6
//                  |
//                  +-[1]list3
//                        |
//                        +-field7

// node tree
//
// struct1[0].field1(INT32(0))
// struct1[1].field2(INT32(1))
// struct1[2].list1[0].field3(INT32(20))
// struct1[2].list1[1].field3(INT32(21))
// struct1[2].list1[2].field3(INT32(22))
// struct1[2].list1[3].field3(INT32(23))
// struct1[2].list1[4].field3(INT32(24))
// struct1[3].struct2[0].field4(INT32(30))
// struct1[3].struct2[1].field5(INT32(31))
// struct1[3].struct2[2].list2[0].struct3[0].field6(INT32(3200))
// struct1[3].struct2[2].list2[0].struct3[1].list3[0].field7(INT32(32010))
// struct1[3].struct2[2].list2[0].struct3[1].list3[1].field7(INT32(32011))
// struct1[3].struct2[2].list2[1].struct3[0].field6(INT32(3210))
// struct1[3].struct2[2].list2[1].struct3[1].list3[0].field7(INT32(32110))
// struct1[3].struct2[2].list2[1].struct3[1].list3[1].field7(INT32(32111))
// struct1[3].struct2[2].list2[1].struct3[1].list3[2].field7(INT32(32112))
// struct1[3].struct2[2].list2[2].struct3[0].field6(INT32(3220))
// struct1[3].struct2[2].list2[2].struct3[1].list3.NIL
//
// -struct1
//   |
//   +-[0]field1 = 0
//   |
//   +-[1]field2 = 1
//   |
//   +-[2]list1 size = 5
//   |     |
//   |     +-[0]field3 = 20
//   |     |
//   |     +-[1]field3 = 21
//   |     |
//   |     +-[2]field3 = 22
//   |     |
//   |     +-[3]field3 = 23
//   |     |
//   |     +-[4]field3 = 24
//   |
//   +-[3]struct2
//         |
//         +-[0]field4 = 30
//         |
//         +-[1]field5 = 31
//         |
//         +-[2]list2 size = 3
//               |
//               +-[0]struct3
//               |     |
//               |     +-[0]field6 = 3200
//               |     |
//               |     +-[1]list3 size = 2
//               |           |
//               |           +-field7 = 32010
//               |           |
//               |           +-field7 = 32011
//               |
//               +-[1]struct3
//               |     |
//               |     +-[0]field6 = 3210
//               |     |
//               |     +-[1]list3 size = 3
//               |           |
//               |           +-field7 = 32110
//               |           |
//               |           +-field7 = 32111
//               |           |
//               |           +-field7 = 32112
//               |
//               +-[2]struct3
//                     |
//                     +-[0]field6 = 3220
//                     |
//                     +-[1]list3 size = 0

// binary format of the node tree (instC)
//
// +--------------+
// | INT8(0)      | field1
// +--------------+
// | INT8(1)      | field2
// +--------------+
// | INT8(5)      | list1 size
// +--------------+
// | INT8(20)     | field3
// +--------------+
// | INT8(21)     | field3
// +--------------+
// | INT8(22)     | field3
// +--------------+
// | INT8(23)     | field3
// +--------------+
// | INT8(24)     | field3
// +--------------+
// | INT8(30)     | field4
// +--------------+
// | INT8(31)     | field5
// +--------------+
// | INT8(3)      | list2 size
// +--------------+
// | INT16(3200)  | field6
// +--------------+
// | INT8(2)      | list3
// +--------------+
// | INT16(32010) | field7
// +--------------+
// | INT16(32011) | field7
// +--------------+
// | INT16(3210)  | field6
// +--------------+
// | INT8(3)      | list3 size
// +--------------+
// | INT16(32110) | field7
// +--------------+
// | INT16(32111) | field7
// +--------------+
// | INT16(32112) | field7
// +--------------+
// | INT16(3220)  | field6
// +--------------+
// | INT8(0)      | list3 size
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
  0x02, // list3Def
  0x7d, // field7Def
  0x0a,
  0x7d, // field7Def
  0x0b,
  0x0c, // field6Def
  0x8a,
  0x03, // list3Def
  0x7d, // field7Def
  0x6e,
  0x7d, // field7Def
  0x6f,
  0x7d, // field7Def
  0x70,
  0x0c, // field6Def
  0x94,
  0x00  // list3Def
};

//-----------------------------------------------------------------------------
int main()
//-----------------------------------------------------------------------------
{
  UTIL::VPP::NodeFactory nodeFactory;

  // construct definition tree
  cout << "--- definition tree ---" << endl;
  UTIL::VPP::StructDef* struct1Def = new UTIL::VPP::StructDef("struct1");
   UTIL::VPP::FieldDef* field1Def =
     new UTIL::VPP::FieldDef("field1", UTIL::VPP::FieldDef::UNSIGNED_FIELD, 0, 8);
   struct1Def->addAttributeDef(field1Def);
   UTIL::VPP::FieldDef* field2Def =
     new UTIL::VPP::FieldDef("field2", UTIL::VPP::FieldDef::UNSIGNED_FIELD, 0, 8);
   struct1Def->addAttributeDef(field2Def);
   UTIL::VPP::ListDef* list1Def = new UTIL::VPP::ListDef("list1", 0, 8);
    UTIL::VPP::FieldDef* field3Def =
      new UTIL::VPP::FieldDef("field3", UTIL::VPP::FieldDef::UNSIGNED_FIELD, 0, 8);
    list1Def->setEntryDef(field3Def);
   struct1Def->addAttributeDef(list1Def);
   UTIL::VPP::StructDef* struct2Def = new UTIL::VPP::StructDef("struct2");
    UTIL::VPP::FieldDef* field4Def =
      new UTIL::VPP::FieldDef("field4", UTIL::VPP::FieldDef::UNSIGNED_FIELD, 0, 8);
    struct2Def->addAttributeDef(field4Def);
    UTIL::VPP::FieldDef* field5Def =
      new UTIL::VPP::FieldDef("field5", UTIL::VPP::FieldDef::UNSIGNED_FIELD, 0, 8);
    struct2Def->addAttributeDef(field5Def);
    UTIL::VPP::ListDef* list2Def = new UTIL::VPP::ListDef("list2", 0, 8);
     UTIL::VPP::StructDef* struct3Def = new UTIL::VPP::StructDef("struct3Def");
      UTIL::VPP::FieldDef* field6Def =
        new UTIL::VPP::FieldDef("field6", UTIL::VPP::FieldDef::UNSIGNED_FIELD, 0, 16);
      struct3Def->addAttributeDef(field6Def);
      UTIL::VPP::ListDef* list3Def = new UTIL::VPP::ListDef("list3", 0, 8);
       UTIL::VPP::FieldDef* field7Def =
         new UTIL::VPP::FieldDef("field7", UTIL::VPP::FieldDef::UNSIGNED_FIELD, 0, 16);
       list3Def->setEntryDef(field7Def);
      struct3Def->addAttributeDef(list3Def);
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
    instC[0].setValue(UTIL::Value(uint32_t(0)));
    instC[1].setValue(UTIL::Value(uint32_t(1)));
    instC[2][0].setValue(UTIL::Value(uint32_t(20)));
    instC[2][1].setValue(UTIL::Value(uint32_t(21)));
    instC[2][2].setValue(UTIL::Value(uint32_t(22)));
    instC[2][3].setValue(UTIL::Value(uint32_t(23)));
    instC[2][4].setValue(UTIL::Value(uint32_t(24)));
    instC[3][0].setValue(UTIL::Value(uint32_t(30)));
    instC[3][1].setValue(UTIL::Value(uint32_t(31)));
    instC[3][2][0][0].setValue(UTIL::Value(uint32_t(3200)));
    instC[3][2][0][1][0].setValue(UTIL::Value(uint32_t(32010)));
    instC[3][2][0][1][1].setValue(UTIL::Value(uint32_t(32011)));
    instC[3][2][1][0].setValue(UTIL::Value(uint32_t(3210)));
    instC[3][2][1][1][0].setValue(UTIL::Value(uint32_t(32110)));
    instC[3][2][1][1][1].setValue(UTIL::Value(uint32_t(32111)));
    instC[3][2][1][1][2].setValue(UTIL::Value(uint32_t(32112)));
    instC[3][2][2][0].setValue(UTIL::Value(uint32_t(3220)));
    // dump instance tree
    instC.dump("instC");
    size_t instCbitSize = UTIL::VPP::getBinarySize(&instC);
    size_t instCbyteSize = instCbitSize / 8;
    cout << "instCbitSize = " << instCbitSize << endl;
    cout << "instCbyteSize = " << instCbyteSize << endl;
    cout << endl;
    if(instCbyteSize != INST_C_DATA_SIZE)
    {
      cout << "Invalid data [bytes] size: "
           << instCbyteSize
           << ", expected: "
           << INST_C_DATA_SIZE
           << endl;
      return -1;
    }
    // write instance tree to data unit
    UTIL::DU du(instCbyteSize);
    size_t writtenBits = UTIL::VPP::writeToDataUnit(&instC, &du);
    size_t writtenBytes = writtenBits / 8;
    du.dump("du");
    cout << "writtenBits = " << writtenBits << endl;
    cout << "writtenBytes = " << writtenBytes << endl;
    cout << endl;
    if(writtenBits != instCbitSize)
    {
      cout << "Invalid amount of data [bits] written: "
           << writtenBits
           << ", expected: "
           << instCbitSize
           << endl;
      return -1;
    }
    UTIL::DU tstDU(INST_C_DATA, INST_C_DATA_SIZE, false);
    if(du != tstDU)
    {
      cout << "Invalid data written" << endl;
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
