//
//  DiamondSquare.hpp
//
//  Created by Mike Mello on 5/30/18.
//  Copyright © 2018 Mike Mello. All rights reserved.
//

#ifndef DiamondSquare_hpp
#define DiamondSquare_hpp

#include <stdio.h>
#include <functional>

//template<int> std::function smoothFunction;
class DiamondSquare {
    
public:
    DiamondSquare();
    ~DiamondSquare();
    
    int** generateHeightmap(int size, int maxHeight, int randomFactor, void(*smoothFunc)(int&));
};

#endif /* DiamondSquare_hpp */
