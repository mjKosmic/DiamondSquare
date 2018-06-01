//
//  main.cpp
//
//  Created by Mike Mello on 5/30/18.
//  Copyright © 2018 Mike Mello. All rights reserved.
//

#include <iostream>
#include "DiamondSquare.hpp"

int main(int argc, const char * argv[]) {
    int** heightmap = (new DiamondSquare())->generateHeightmap(17, 100, 10, [](int &random){random--;});
    
    for(int i = 0; i < 17; i++) {
        printf("\n");
        for(int j = 0; j < 17; j++) {
            printf("%i\t", heightmap[i][j]);
        }
    }
    
    return 0;
}
