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
#include "UTIL_VPP.hpp"

using namespace std;

//-----------------------------------------------------------------------------
int main()
//-----------------------------------------------------------------------------
{
  UTIL::VPP::NodeFactory nodeFactory;

  // construct definition tree
  UTIL::VPP::StructDef* struct1Def = new UTIL::VPP::StructDef("struct1Def");
   UTIL::VPP::FieldDef* field1Def = new UTIL::VPP::FieldDef("field1Def");
   struct1Def->addAttributeDef(field1Def);
   UTIL::VPP::FieldDef* field2Def = new UTIL::VPP::FieldDef("field2Def");
   struct1Def->addAttributeDef(field2Def);
   UTIL::VPP::ListDef* list1Def = new UTIL::VPP::ListDef("list1Def");
    UTIL::VPP::FieldDef* field3Def = new UTIL::VPP::FieldDef("field3Def");
    list1Def->setEntryDef(field3Def);
   struct1Def->addAttributeDef(list1Def);
   UTIL::VPP::StructDef* struct2Def = new UTIL::VPP::StructDef("struct2Def");
    UTIL::VPP::FieldDef* field4Def = new UTIL::VPP::FieldDef("field4Def");
    struct2Def->addAttributeDef(field4Def);
    UTIL::VPP::FieldDef* field5Def = new UTIL::VPP::FieldDef("field5Def");
    struct2Def->addAttributeDef(field5Def);
    UTIL::VPP::ListDef* list2Def = new UTIL::VPP::ListDef("list2Def");
     UTIL::VPP::StructDef* struct3Def = new UTIL::VPP::StructDef("struct3Def");
      UTIL::VPP::FieldDef* field6Def = new UTIL::VPP::FieldDef("field6Def");
      struct3Def->addAttributeDef(field6Def);
      UTIL::VPP::ListDef* list4Def = new UTIL::VPP::ListDef("list4Def");
       UTIL::VPP::FieldDef* field7Def = new UTIL::VPP::FieldDef("field7Def");
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
    // construct instance tree
    // this code creates a memory leak (but no problem for functional tests)
    UTIL::VPP::Node& instA =
      *(UTIL::VPP::NodeFactory::instance()->createNode(struct1Def));
    instA[2].addNodes(5);
    instA[3][2].addNodes(3);
    instA[3][2][0][1].addNodes(2);
    instA[3][2][1][1].addNodes(3);
    // dump instance tree
    instA.dump("instA");
    cout << endl;

    // this code creates a memory leak (but no problem for functional tests)
    UTIL::VPP::Node& instB =
      *(UTIL::VPP::NodeFactory::instance()->createNode(struct1Def));
    instB[2].addNodes(5);
    instB[3][2].addNodes(3);
    instB[3][2][0][1].addNodes(2);
    instB[3][2][1][1].addNodes(3);
    // dump instance tree
    instB.dump("instB");
    cout << endl;

    cout << "--- move ---" << endl;
    instA.moveNodes(instB);
    cout << endl;

    // dump instance tree
    instA.dump("InstA");
    cout << endl;

    // dump instance tree
    instB.dump("instB");
    cout << endl;
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
