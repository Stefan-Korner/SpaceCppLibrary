//*****************************************************************************
// (C) 2014, Stefan Korner, Austria                                           *
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
// Utilities - Data Unit - Unit Tests                                         *
//*****************************************************************************
#include "UTIL_DU.hpp"

#include <iostream>
#include <string.h>

using namespace std;

static const UTIL::DU::UnsignedAccessor UINT_ACC1 = {0, 1};
static const UTIL::DU::UnsignedAccessor UINT_ACC2 = {0, 2};
static const UTIL::DU::UnsignedAccessor UINT_ACC3 = {0, 3};
static const UTIL::DU::UnsignedAccessor UINT_ACC4 = {0, 4};

static const UTIL::DU::BigUnsignedAccessor BUINT_ACC1 = {0, 1};
static const UTIL::DU::BigUnsignedAccessor BUINT_ACC2 = {0, 2};
static const UTIL::DU::BigUnsignedAccessor BUINT_ACC3 = {0, 3};
static const UTIL::DU::BigUnsignedAccessor BUINT_ACC4 = {0, 4};
static const UTIL::DU::BigUnsignedAccessor BUINT_ACC5 = {0, 5};
static const UTIL::DU::BigUnsignedAccessor BUINT_ACC6 = {0, 6};
static const UTIL::DU::BigUnsignedAccessor BUINT_ACC7 = {0, 7};
static const UTIL::DU::BigUnsignedAccessor BUINT_ACC8 = {0, 8};

static const UTIL::DU::BitAccessor BIT_ACC1 = { 4,  1};
static const UTIL::DU::BitAccessor BIT_ACC2 = { 5,  3};
static const UTIL::DU::BitAccessor BIT_ACC3 = {12,  8};
static const UTIL::DU::BitAccessor BIT_ACC4 = {20, 16};

static const UTIL::DU::ByteAccessor BYTE_ACC1 = {5, 4};

static const UTIL::DU::StringAccessor STRING_ACC1 = {0, 8};

//-----------------------------------------------------------------------------
int main()
//-----------------------------------------------------------------------------
{
  try
  {
    uint32_t val;
    uint64_t bval;
    const uint8_t* bytes;
    const char* txt1 = "0123456789 hihihi huhuhu";
    UTIL::DU du1(txt1, strlen(txt1), true);
    du1.dump("du1", true);
    cout << "du1[0] = " << ((int) du1[0]) << endl;
    du1[0] = 64;
    du1.dump("du1", true);
    du1.resize((size_t) 0x20);
    du1.dump("du1", true);

    val = du1.get(UINT_ACC1);
    // 64
    cout << "val = " << val << endl;
    val = du1.get(UINT_ACC2);
    // 16433
    cout << "val = " << val << endl;
    val = du1.get(UINT_ACC3);
    // 4206898
    cout << "val = " << val << endl;
    val = du1.get(UINT_ACC4);
    // 1076965939
    cout << "val = " << val << endl;

    du1.set(UINT_ACC1, 1);
    du1.dump("du1", true);
    du1.set(UINT_ACC2, 513);
    du1.dump("du1", true);
    du1.set(UINT_ACC3, 197121);
    du1.dump("du1", true);
    du1.set(UINT_ACC4, 67305985);
    du1.dump("du1", true);
    // du1 = 04 03 02 01 ...

    bval = du1.get(BUINT_ACC1);
    // 4
    cout << "bval = " << bval << endl;
    bval = du1.get(BUINT_ACC2);
    // 1027
    cout << "bval = " << bval << endl;
    bval = du1.get(BUINT_ACC3);
    // 262914
    cout << "bval = " << bval << endl;
    bval = du1.get(BUINT_ACC4);
    // 67305985
    cout << "bval = " << bval << endl;
    bval = du1.get(BUINT_ACC5);
    // 17230332212
    cout << "bval = " << bval << endl;
    bval = du1.get(BUINT_ACC6);
    // 4410965046325
    cout << "bval = " << bval << endl;
    bval = du1.get(BUINT_ACC7);
    // 1129207051859254
    cout << "bval = " << bval << endl;
    bval = du1.get(BUINT_ACC8);
    // 289077005275969079
    cout << "bval = " << bval << endl;

    du1.set(BUINT_ACC1, 1);
    du1.dump("du1", true);
    du1.set(BUINT_ACC2, 513);
    du1.dump("du1", true);
    du1.set(BUINT_ACC3, 197121);
    du1.dump("du1", true);
    du1.set(BUINT_ACC4, 67305985);
    du1.dump("du1", true);
    du1.set(BUINT_ACC5, 21542142465);
    du1.dump("du1", true);
    du1.set(BUINT_ACC6, 6618611909121);
    du1.dump("du1", true);
    du1.set(BUINT_ACC7, 1976943448883713);
    du1.dump("du1", true);
    du1.set(BUINT_ACC8, 578437695752307201);
    du1.dump("du1", true);
    // du1 = 08 07 06 05 04 03 02 01 ...

    du1.set(STRING_ACC1, "\x04\x03\x02\x01" "4567");
    du1.dump("du1", true);
    // du1 = 04 03 02 01 34 35 36 37 ...

    val = du1.get(BIT_ACC1);
    // 0
    cout << "val = " << val << endl;
    val = du1.get(BIT_ACC2);
    // 4
    cout << "val = " << val << endl;
    val = du1.get(BIT_ACC3);
    // 48
    cout << "val = " << val << endl;
    val = du1.get(BIT_ACC4);
    // 8211
    cout << "val = " << val << endl;

    du1.set(BIT_ACC1, 1);
    du1.dump("du1", true);
    du1.set(BIT_ACC2, 3);
    du1.dump("du1", true);
    du1.set(BIT_ACC3, 171);
    du1.dump("du1", true);
    du1.set(BIT_ACC4, 39030);
    du1.dump("du1", true);
    // du1 = 0b 0a b9 87 64 ...

    UTIL::DU du2(du1);
    du2.dump("du2", true);
    bytes = du2.get(BYTE_ACC1);
    UTIL::DU du3(bytes, BYTE_ACC1.byteLength, false);
    du3.dump("du3", true);
    // du3 = 35 36 37 38
    du2.set(BYTE_ACC1, "ABCD");
    du2.dump("du2", true);
    bytes = du2.get(BYTE_ACC1);
    du3.init(bytes, BYTE_ACC1.byteLength, false);
    du3.dump("du3", true);
    cout << endl;
    // du3 = 41 42 43 44

    cout << "share same buffer" << endl;
    du1.init("1234", 4, false);
    du2.init(du1);
    cout << "(du1 == du2) " << (du1 == du2) << endl;
    cout << "(du1 != du2) " << (du1 != du2) << endl;
    cout << "(du1 <  du2) " << (du1 <  du2) << endl;
    cout << "(du1 >  du2) " << (du1 >  du2) << endl;
    cout << "(du1 <= du2) " << (du1 <= du2) << endl;
    cout << "(du1 >= du2) " << (du1 >= du2) << endl;
    cout << endl;

    cout << "share same buffer but different size (du1 > du2)" << endl;
    du1.init("1234", 4, false);
    du2.resize(3);
    cout << "(du1 == du2) " << (du1 == du2) << endl;
    cout << "(du1 != du2) " << (du1 != du2) << endl;
    cout << "(du1 <  du2) " << (du1 <  du2) << endl;
    cout << "(du1 >  du2) " << (du1 >  du2) << endl;
    cout << "(du1 <= du2) " << (du1 <= du2) << endl;
    cout << "(du1 >= du2) " << (du1 >= du2) << endl;
    cout << endl;

    cout << "same contents but different buffers" << endl;
    du2.init("1234", 4, true);
    cout << "(du1 == du2) " << (du1 == du2) << endl;
    cout << "(du1 != du2) " << (du1 != du2) << endl;
    cout << "(du1 <  du2) " << (du1 <  du2) << endl;
    cout << "(du1 >  du2) " << (du1 >  du2) << endl;
    cout << "(du1 <= du2) " << (du1 <= du2) << endl;
    cout << "(du1 >= du2) " << (du1 >= du2) << endl;
    cout << endl;

    cout << "different buffers, different length (du1 < du2)" << endl;
    du2.init("12345", 5, false);
    cout << "(du1 == du2) " << (du1 == du2) << endl;
    cout << "(du1 != du2) " << (du1 != du2) << endl;
    cout << "(du1 <  du2) " << (du1 <  du2) << endl;
    cout << "(du1 >  du2) " << (du1 >  du2) << endl;
    cout << "(du1 <= du2) " << (du1 <= du2) << endl;
    cout << "(du1 >= du2) " << (du1 >= du2) << endl;
    cout << endl;

    cout << "different contents (du1 < du2)" << endl;
    du2.init("1284", 4, false);
    cout << "(du1 == du2) " << (du1 == du2) << endl;
    cout << "(du1 != du2) " << (du1 != du2) << endl;
    cout << "(du1 <  du2) " << (du1 <  du2) << endl;
    cout << "(du1 >  du2) " << (du1 >  du2) << endl;
    cout << "(du1 <= du2) " << (du1 <= du2) << endl;
    cout << "(du1 >= du2) " << (du1 >= du2) << endl;
    cout << endl;

    du3 = du1 + du2;
    du3.dump("du3", true);
  }
  catch(const UTIL::Exception& ex)
  {
    cout << "Exception: " << ex.what() << endl;
  }
  return 0;
}
