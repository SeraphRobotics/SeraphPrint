#ifndef UTIL_H
#define UTIL_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "nmccom.h"
#include <math.h>
#include <map>
#include <vector>
#include <time.h>
#include <algorithm>
#include <QMessageBox>
#include "tinyxml.h"
using namespace std;


#define PROJECT_NAMESPACE FabAtHome

namespace PROJECT_NAMESPACE
{
    /**
      This class contains various functions related to casting and error checking
      @todo Get rid of this class
     */
    class Util
    {

        //STRINGS//////////////////////////////////////////////////////////////////
        /**
          Prefer string since it can be initialized with both string and const char*.
          Cannot initialize const char* with string.
          <string object>.c_str() converts to const char* from string
          string varName(const char* text) converts to string from const char*
          stringstream ss; ss << "A" << 2; ss << 'a' << 4.5f; ss.str(); returns the string "A2a4.5".
          ss.str(string text) sets data in stream to text, use "" to clear stream
          string object a>.compare(<string object b>) returns negative iff a < b, 0 iff a = b,
          or positive iff a > b.
          strcmp(const char* a, const char* b) returns negative iff a < b, 0 iff a = b, or positive iff a > b
          strol interprets string as an integer in a specified base
          Requires: T is a datatype that the >> operator of istringstream supports.
          @return true iff text can be interpreted as a value with datatype T
         */
    public: template<typename T> static bool isType(const string& text)
        {
            istringstream iss(text);
            T stringAsT;
            iss >> noskipws >> stringAsT;
            return !iss.fail() && iss.eof();
     	}
        
        /**
          Casts a string into type T
          Requires: isType(text)
          @return text interpreted as a value with datatype T
         */
    public: template<typename T> static T toType(const string& text)
        {
            istringstream iss(text);
            T stringAsT;
            iss >> noskipws >> stringAsT;
            return stringAsT;
     	}
        

        /**
          Checks to see if text is of type T
         */
    public: template<typename T> static T assertType(const string& text)
        {
            Util::assertTrue(Util::isType<T>(text),text+" cannot be interpreted as the required datatype.",__LINE__,__FILE__);
            return toType<T>(text);
        }
        
        /**
          Converts t of type T to a string
         */
    public: template<typename T> static string toString(const T& t)
        {
            stringstream ss;
            ss.setf(ios::fixed,ios::floatfield);
            ss.precision(6);
            ss << t;
            return ss.str();
        }
        
        /**
          Splits two strings and puts them in "result"
         */
            public: static void split(string text, const string& delim, vector<string>& result)
                {
                    for(int cutAt = text.find(delim); cutAt != text.npos; cutAt = text.find(delim))
                    {
                        if(cutAt > 0)
                        {
                            result.push_back(text.substr(0,cutAt));
                        }
                        text = text.substr(cutAt+delim.length());
                    }
                    if(text.length() > 0)
                    {
                        result.push_back(text);
                    }
                }
                //EXECUTION CONTROL////////////////////////////////////////////////////////
                //MessageBox(NULL, const char* text, const char* title, MB_OK); pauses execution of thread until a button is pressed.  Button codes can be found at http://msdn.microsoft.com/en-us/library/ms645505(VS.85).aspx
                //Sleep(int milliseconds) pauses execution of thread for specified time
                //exit(int status) terminates program, status is EXIT_SUCCESS or EXIT_FAILURE
                //system(string code) executes code as windows command script, sometimes wont work when run from ide but will work when run from executable
                
            /**
              Calls a message box to pop up
             */
            public: static void messageBox(const string& message)
                {
                    //QMessageBox::warning(0, "", message.c_str());
                    printf(message.c_str());
                    printf("\n");
                }
                
            /**
              Exits the program with a fatal error
             */
            public: static void handleFatalError(const string& errorMessage)
                {
                    Util::messageBox("A fatal error occured.\n"+errorMessage+"\nPress OK to terminate program.");
                    exit(EXIT_FAILURE);
                }
                
                //MISCELLANEOUS////////////////////////////////////////////////////////////

            /**
              Assert that some conidition is true, otherwise treat is as a fatal error
             */
            public: static void assertTrue(const bool& condition, const string& errorMessage, const int& lineNumber, const string& fileName)
                {
                    if(!condition)
                    {
                        stringstream ss;
                        ss << "Argument on line " << lineNumber << " of file " << fileName << " was false but expected to be true." << "\n" << errorMessage;
                        handleFatalError(ss.str());
                    }
                }
                
            /**
              A tester method for the functions in this file
             */
            public: static void runTestCases()
                {
                    Util::assertTrue(Util::isType<int>("-1000"),"An error occured while testing utility functions.",__LINE__,__FILE__);
                    Util::assertTrue(Util::toType<int>("-1000") == -1000,"An error occured while testing utility functions.",__LINE__,__FILE__);
                    Util::assertTrue(Util::isType<double>("-1000.5"),"An error occured while testing utility functions.",__LINE__,__FILE__);
                    Util::assertTrue(Util::toType<double>("-1000.5") == -1000.5,"An error occured while testing utility functions.",__LINE__,__FILE__);
                    Util::assertTrue(Util::isType<int>("001"),"An error occured while testing utility functions.",__LINE__,__FILE__);
                    Util::assertTrue(!Util::isType<int>(""),"An error occured while testing utility functions.",__LINE__,__FILE__);
                    Util::assertTrue(!Util::isType<int>("0 "),"An error occured while testing utility functions.",__LINE__,__FILE__);
                    Util::assertTrue(!Util::isType<int>(" 0"),"An error occured while testing utility functions.",__LINE__,__FILE__);
                    Util::assertTrue(!Util::isType<int>("zero"),"An error occured while testing utility functions.",__LINE__,__FILE__);
                    Util::assertTrue(!Util::isType<int>("1 5"),"An error occured while testing utility functions.",__LINE__,__FILE__);
                }
                
                //MATH//////////////////////////////////////////////////////////////////////
                //pow(double base, double exp) returns base^exp
                //abs(arg) returns absolute value of arg
                

            /**
              @pre a <= b
              @return A random number in [a,b].
             */
            public: static double randomDouble(const double& a, const double& b)
                {
                    static bool seeded = false;
                    if(!seeded)
                    {
                        srand((unsigned int)time(NULL));
                        seeded = true;
                    }
                    double uniform = (1.0*rand())/RAND_MAX;
                    return a+(b-a)*uniform;
                }
                
            /**
              @pre a <= b
              @return A random number in {a,a+1,a+2,...,b}
             */
            public: static int randomInt(const int& a, const int& b)
                {
                    return (int)floor(randomDouble(a,b+0.999999));
                }
            };
    //STRINGS///////////////////////////////////////////////////////////////////////
    class LessThanString
    {
    public:
        //Returns: true iff a comes before b lexicographically.
        bool operator()(const string& a, const string& b) const
        {
            return (a.compare(b) < 0);
        }
    };
    //XML/////////////////////////////////////////////////////////////////////////////
    class XMLParser
    {
        /**
          ex. "a 0\\b 3\\c 2" is a path to an element interpreted as follows:
          the root is named a, the 4th element child of a named b, the 3rd element child of b named c
         */
        
    private:
        map<string,int> counts;
        map<string,string> texts;
        string filePath;
        TiXmlDocument file;
        
        /**
          Recursive helper function that uses Tiny XML object
         */
        void loadHelper(TiXmlElement* elem, const string& elemPath)
        {
            string base = elemPath+" "+Util::toString(count(elemPath));
            counts[elemPath] = count(elemPath)+1;
            if(elem->FirstChild() != NULL && elem->FirstChild()->ToText() != NULL)
            {
                //Base case
                texts[base] = elem->FirstChild()->ToText()->Value();
            }
            else
            {
                //Recursive case
                for(TiXmlElement* child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
                {
                    loadHelper(child,base+"\\"+child->Value());
                }
            }
        }
        /**
          Loads in XML file if it is a valid file name with a valid root
         */
          public: string load(const string& filePath)
              {
                  if(!file.LoadFile(filePath.c_str()))
                  {
                      return "Could not open "+filePath+".";
                  }
                  else
                  {
                      TiXmlElement* root(file.RootElement());
                      if(root == NULL)
                      {
                          return "Could not find root element.";
                      }
                      counts.clear();
                      texts.clear();
                      this->filePath = filePath;
                      loadHelper(root,root->Value());
                      return "";
                  }
              }

        /**
          @param elemPath The path to search for
          @return The text of elemPath or "" if elemPath is not text.
         */
              string text(const string& elemPath)
              {
                  map<string,string>::iterator i = texts.find(elemPath);
                  if(i == texts.end())
                  {
                      return "";
                  }
                  else
                  {
                      return i->second;
                  }
              }

              /**
                @return the number of element children named elemPath
               */
              unsigned int count(const string& elemPath)
              {
                  map<string,int>::iterator i = counts.find(elemPath);
                  if(i == counts.end())
                  {
                      return 0;
                  }
                  else
                  {
                      return i->second;
                  }
              }

          };
    
}

using namespace PROJECT_NAMESPACE;

#endif //ndef UTIL_H
