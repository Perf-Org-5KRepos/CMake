#include "cmTestConfigure.h"
#include "ExtraSources/file1.h"
#include "file2.h"
#include "sharedFile.h"
#include "cmStandardIncludes.h"

int passed = 0;
int failed = 0;

void Failed(const char* Message, const char* m2= "")
{
  std::cerr << "Failed: " << Message << m2 << "\n"; 
  failed++;
}

void Passed(const char* Message, const char* m2="")
{
  std::cout << "Passed: " << Message << m2 << "\n"; 
  passed++;
}

int main()
{
  if(sharedFunction() != 1)
    {
    Failed("Call to sharedFunction from shared library failed.");
    }
  else
    {
    Passed("Call to sharedFunction from shared library worked.");
    }
  
  if(file1() != 1)
    {
    Failed("Call to file1 function from library failed.");
    }
  else
    {
    Passed("Call to file1 function returned 1.");
    }
  if(file2() != 1)
    {
    Failed("Call to file2 function from library failed.");
    }
  else
    {
    Passed("Call to file2 function returned 1.");
    }
#ifndef CMAKE_IS_FUN
  Failed("CMake is not fun, so it is broken and should be fixed.");
#else
  Passed("CMAKE_IS_FUN is defined.");
#endif
  
#ifdef SHOULD_NOT_BE_DEFINED
  Failed("IF or SET is broken, SHOULD_NOT_BE_DEFINED is defined.");
#else
  Passed("SHOULD_NOT_BE_DEFINED is not defined.");
#endif
  
#ifndef SHOULD_BE_DEFINED
  Failed("IF or SET is broken, SHOULD_BE_DEFINED is not defined.\n");
#else
  Passed("SHOULD_BE_DEFINED is defined.");
#endif
  
#ifndef ONE_VAR
  Failed("cmakedefine is broken, ONE_VAR is not defined.");
#else
  Passed("ONE_VAR is defined.");
#endif
  
#ifdef ZERO_VAR
  Failed("cmakedefine is broken, ZERO_VAR is defined.");
#else
  Passed("ZERO_VAR is not defined.");
#endif
  

  
#ifndef STRING_VAR
  Failed("configureFile is broken, STRING_VAR is not defined.");
#else
  if(strcmp(STRING_VAR, "CMake is great") != 0)
    {
    Failed("CMake is not great, so the SET command,"
           "or the configurefile comand is broken.  STRING_VAR== ", 
           STRING_VAR);
    }
  else
    {
    Passed("STRING_VAR == ", STRING_VAR);
    }
#endif
  std::cout << "Passed:" << passed << "\n";
  if(failed)
    {
    std::cout << "Failed: " << failed << "\n";
    return failed;
    }
  return 0;
}

  
