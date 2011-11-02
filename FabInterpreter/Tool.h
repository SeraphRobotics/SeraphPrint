#ifndef TOOL_H
#define TOOL_H

#include "Util.h"
#include "Bay.h"

namespace PROJECT_NAMESPACE
{
    /**
      Contains an array of bay objects
     */
     class Tool
     {
	     public:
		     map<string, Bay, LessThanString> bays; //A map from bay names to bays.
     };
}

#endif //ndef TOOL_H
