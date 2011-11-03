#ifndef MODEL_H
#define MODEL_H

#include "Util.h"
#include "InterpreterPath.h"

namespace PROJECT_NAMESPACE
{
    /**
      Contains an array of paths that are executed during a print job
     */
     class Model
     {          
          public:
               vector<Path> paths; //Paths that are currently loaded.
     };
}
     
#endif //ndef MODEL_H
