//
//  VisuClass.cpp
//  MurMur d'Ombre
//
//  Created by Tinmar on 14/01/14.
//  Copyright 2014 __MyCompanyName__. All rights reserved.
//

#include "VisuClass.h"




VisuClass::VisuClass(VisuHandler * vh){
    
    dad=vh;
    MYPARAM(isActive,false,false,true);
    MYPARAM(isPiping,false,false,true);
    MYPARAM(screenN,0,0,234);
    
    MYPARAM(recopy,true,false,true);
    isHighFPS = false;
    MYPARAM(isMapping,true,false,true);
    
    
    MYPARAM(isMasking,false,false,true);
    
}



