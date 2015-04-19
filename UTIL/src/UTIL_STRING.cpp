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
// Utilities - string routines                                                *
//*****************************************************************************
#include "UTIL_STRING.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

//-----------------------------------------------------------------------------
string UTIL::STRING::str(int p_val)
//-----------------------------------------------------------------------------
{
  // -2 147 483 648 ... 2 147 483 647
  char buffer[12];
  sprintf(buffer, "%i", p_val);
  return string((const char*) buffer);
}

//-----------------------------------------------------------------------------
int UTIL::STRING::asInt(const char* p_string)
//-----------------------------------------------------------------------------
{
  return atoi(p_string);
}

//-----------------------------------------------------------------------------
int UTIL::STRING::asInt(const string& p_string)
//-----------------------------------------------------------------------------
{
  return asInt(p_string.c_str());
}

//-----------------------------------------------------------------------------
void UTIL::STRING::split(const char* p_text,
                         const char* p_seperator,
                         vector<string>& p_tokens)
//-----------------------------------------------------------------------------
{
  p_tokens.clear();
  char* text = strdup(p_text);
  char* saveptr;
  char* token = strtok_r(text, p_seperator, &saveptr);
  while(token != NULL)
  {
    p_tokens.push_back(token);
    token = strtok_r(NULL, p_seperator, &saveptr);
  }
  free(text);
}

//-----------------------------------------------------------------------------
void UTIL::STRING::split(const string& p_text,
                         const char* p_seperator,
                         vector<string>& p_tokens)
//-----------------------------------------------------------------------------
{
  split(p_text.c_str(), p_seperator, p_tokens);
}

//-----------------------------------------------------------------------------
void UTIL::STRING::readTextFile(const char* p_filePath, list<string>& p_lines)
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  FILE* fp = fopen(p_filePath, "r");
  if(fp == NULL)
  {
    string errorMessage = "cannot open ";
    errorMessage += p_filePath;
    errorMessage += " for reading";
    throw UTIL::Exception(errorMessage);
  }
  p_lines.clear();
  char* line = NULL;
  size_t len = 0; // buffer size, is bigger than the line
  ssize_t read; // this is the size of the line
  read = getline(&line, &len, fp);
  while(read != -1)
  {
    // remove the line break in the string
    if(read > 0)
    {
      line[read - 1] = '\0';
    }
    p_lines.push_back(line);
    read = getline(&line, &len, fp);
  }
  fclose(fp);
  if(line != NULL)
  {
    free(line);
  }
}
