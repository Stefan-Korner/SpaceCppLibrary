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
string UTIL::STRING::str(unsigned int p_val)
//-----------------------------------------------------------------------------
{
  // 0 ... 4 294 967 295
  char buffer[11];
  sprintf(buffer, "%u", p_val);
  return string((const char*) buffer);
}

//-----------------------------------------------------------------------------
int UTIL::STRING::asInt(const char* p_string)
//-----------------------------------------------------------------------------
{
  return strtol(p_string, NULL, 10);
}

//-----------------------------------------------------------------------------
int UTIL::STRING::asInt(const string& p_string)
//-----------------------------------------------------------------------------
{
  return asInt(p_string.c_str());
}

//-----------------------------------------------------------------------------
unsigned int UTIL::STRING::asUInt(const char* p_string)
//-----------------------------------------------------------------------------
{
  return strtoul(p_string, NULL, 10);
}

//-----------------------------------------------------------------------------
unsigned int UTIL::STRING::asUInt(const string& p_string)
//-----------------------------------------------------------------------------
{
  return asUInt(p_string.c_str());
}

//-----------------------------------------------------------------------------
void UTIL::STRING::split(const char* p_text,
                         const char* p_separator,
                         vector<string>& p_tokens)
//-----------------------------------------------------------------------------
{
  p_tokens.clear();
  size_t sepLength = strlen(p_separator);
  char* text = strdup(p_text);
  char* token = text;
  while(true)
  {
    char* nextSeparator = strstr(token, p_separator);
    if(nextSeparator == NULL)
    {
      // no separator found --> this must be the last token
      p_tokens.push_back(token);
      break;
    }
    // separator found: extract token
    *nextSeparator = '\0';
    p_tokens.push_back(token);
    token = nextSeparator;
    token += sepLength;
  }
  free(text);
}

//-----------------------------------------------------------------------------
void UTIL::STRING::split(const string& p_text,
                         const char* p_separator,
                         vector<string>& p_tokens)
//-----------------------------------------------------------------------------
{
  split(p_text.c_str(), p_separator, p_tokens);
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
