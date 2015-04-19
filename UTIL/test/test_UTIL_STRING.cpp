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
// Utilities - STRING - Unit Tests                                            *
//*****************************************************************************
#include "UTIL_STRING.hpp"

#include <iostream>

using namespace std;

const char* TEST_TOKENS[] =
{
  "This",
  "is",
  "a",
  "test",
  "string."
};

const char* TEST_FILE_CONTENTS[] =
{
  "This is line 1 of the test file.",
  "This is line 2 of the test file.",
  "This is line 3 of the test file.",
  "",
  "0123456789",
  "01234567890123456789",
  "012345678901234567890123456789",
  "0123456789012345678901234567890123456789",
  "01234567890123456789012345678901234567890123456789",
  "012345678901234567890123456789012345678901234567890123456789",
  "0123456789012345678901234567890123456789012345678901234567890123456789"
};

const char* TABLE_TOKENS[] =
{
  "Name1.1", "Name1.2", "1234", "5678",
  "Name2.1", "Name2.2", "8765", "4321",
  "Name3.1", "Name3.2", "1212", "2121"
};

//-----------------------------------------------------------------------------
bool test_splitOperation()
//-----------------------------------------------------------------------------
{
  string testString = "This is a test string.";
  vector<string> tokens;
  UTIL::STRING::split(testString, " ", tokens);
  size_t i = 0;
  for(vector<string>::iterator iter = tokens.begin();
      iter != tokens.end();
      iter++)
  {
    cout << (*iter) << endl;
    if((*iter) != TEST_TOKENS[i])
    {
      cout << "Parsed token different to expected token." << endl;
      cout << "Parsed token: " << (*iter) << endl;
      cout << "Expect token: " << TEST_TOKENS[i] << endl;
      return false;
    }
    i++;
  }
  return true;
}

//-----------------------------------------------------------------------------
bool test_readTestFile()
//-----------------------------------------------------------------------------
{
  list<string> fileLines;
  try
  {
    UTIL::STRING::readTextFile("NonExistingFile", fileLines);
    cout << "This statement should not be reached" << endl;
    return false;
  }
  catch(const UTIL::Exception& ex)
  {
    cout << "Expected exception: " << ex.what() << endl;
  }
  try
  {
    UTIL::STRING::readTextFile("TestFile.txt", fileLines);
  }
  catch(const UTIL::Exception& ex)
  {
    cout << "Exception: " << ex.what() << endl;
    return false;
  }
  size_t i = 0;
  for(list<string>::iterator iter = fileLines.begin();
      iter != fileLines.end();
      iter++)
  {
    cout << (*iter) << endl;
    if((*iter) != TEST_FILE_CONTENTS[i])
    {
      cout << "Read line different to expected line." << endl;
      cout << "Read line: " << (*iter) << endl;
      cout << "Exp. line: " << TEST_FILE_CONTENTS[i] << endl;
      return false;
    }
    i++;
  }
  return true;
}

//-----------------------------------------------------------------------------
bool test_readTestTable()
//-----------------------------------------------------------------------------
{
  list<string> fileLines;
  try
  {
    UTIL::STRING::readTextFile("TestTable.txt", fileLines);
  }
  catch(const UTIL::Exception& ex)
  {
    cout << "Exception: " << ex.what() << endl;
    return false;
  }
  size_t i = 0;
  for(list<string>::iterator iter = fileLines.begin();
      iter != fileLines.end();
      iter++)
  {
    cout << (*iter) << endl;
    vector<string> tokens;
    UTIL::STRING::split((*iter), "\t", tokens);
    for(vector<string>::iterator iter = tokens.begin();
        iter != tokens.end();
        iter++)
    {
      cout << (*iter) << endl;
      if((*iter) != TABLE_TOKENS[i])
      {
        cout << "Parsed token different to expected token." << endl;
        cout << "Parsed token: " << (*iter) << endl;
        cout << "Expect token: " << TABLE_TOKENS[i] << endl;
        return false;
      }
      i++;
    }
  }
  return true;
}

//-----------------------------------------------------------------------------
int main()
//-----------------------------------------------------------------------------
{
  printf("***** test_splitOperation() start\n");
  bool retVal = test_splitOperation();
  printf("***** test_splitOperation() done: %d\n", retVal);
  if(retVal == false)
  {
    return -1;
  }
  printf("***** test_readTestFile() start\n");
  retVal = test_readTestFile();
  printf("***** test_readTestFile() done: %d\n", retVal);
  if(retVal == false)
  {
    return -1;
  }
  printf("***** test_readTestTable() start\n");
  retVal = test_readTestTable();
  printf("***** test_readTestTable() done: %d\n", retVal);
  if(retVal == false)
  {
    return -1;
  }
  return 0;
}
