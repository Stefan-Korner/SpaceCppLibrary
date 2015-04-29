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
// Space Simulation - Variable Packets - Unit Tests                           *
//*****************************************************************************
#include "SPACE_VPP.hpp"

#include <iostream>
#include "SPACE_VPP.hpp"

using namespace std;

//-----------------------------------------------------------------------------
int main()
//-----------------------------------------------------------------------------
{
  // construct definition tree
  SPACE::VPP::StructDef* struct1Def = new SPACE::VPP::StructDef("struct1Def");
   SPACE::VPP::FieldDef* field1Def = new SPACE::VPP::FieldDef("field1Def");
   struct1Def->addAttributeDef(field1Def);
   SPACE::VPP::FieldDef* field2Def = new SPACE::VPP::FieldDef("field2Def");
   struct1Def->addAttributeDef(field2Def);
   SPACE::VPP::ListDef* list1Def = new SPACE::VPP::ListDef("list1Def");
    SPACE::VPP::FieldDef* field3Def = new SPACE::VPP::FieldDef("field3Def");
    list1Def->setEntryDef(field3Def);
   struct1Def->addAttributeDef(list1Def);
   SPACE::VPP::StructDef* struct2Def = new SPACE::VPP::StructDef("struct2Def");
    SPACE::VPP::FieldDef* field4Def = new SPACE::VPP::FieldDef("field4Def");
    struct2Def->addAttributeDef(field4Def);
    SPACE::VPP::FieldDef* field5Def = new SPACE::VPP::FieldDef("field5Def");
    struct2Def->addAttributeDef(field5Def);
    SPACE::VPP::ListDef* list2Def = new SPACE::VPP::ListDef("list2Def");
     SPACE::VPP::StructDef* struct3Def = new SPACE::VPP::StructDef("struct3Def");
      SPACE::VPP::FieldDef* field6Def = new SPACE::VPP::FieldDef("field6Def");
      struct3Def->addAttributeDef(field6Def);
      SPACE::VPP::ListDef* list4Def = new SPACE::VPP::ListDef("list4Def");
       SPACE::VPP::FieldDef* field7Def = new SPACE::VPP::FieldDef("field7Def");
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
    SPACE::VPP::Struct struct1(struct1Def);
    struct1[2].addNodes(5);
    struct1[3][2].addNodes(3);
    struct1[3][2][0][1].addNodes(2);
    struct1[3][2][1][1].addNodes(3);
    // dump instance tree
    struct1.dump("Inst");
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
