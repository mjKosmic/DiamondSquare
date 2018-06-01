//
//  DiamondSquare.cpp
//
//  Created by Mike Mello on 5/30/18.
//  Copyright © 2018 Mike Mello. All rights reserved.
//

#include <cstdlib>
#include "DiamondSquare.hpp"

DiamondSquare::DiamondSquare() {}
DiamondSquare::~DiamondSquare(){}

/**
 *  Allocate the map on the heap and initialize the values to 0
 */
int** initializeHeightmap(int size) {
    int** map = (int **)malloc(size * sizeof(int *));
    for(int i = 0; i < size; i++) {
        map[i] = (int *)malloc(size * sizeof(int));
    }
    
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            map[i][j] = 0;
        }
    }
    
    return map;
}

/**
 *  Seed the 4 corners of the map with a random value between 0 and the given max value
 */
void seedCorners(int** map, int size, int maxHeight) {
    map[0][0] = rand() % maxHeight;
    map[size - 1][0] = rand() % maxHeight;
    map[0][size - 1] = rand() % maxHeight;
    map[size - 1][size - 1] = rand() % maxHeight;
}

/**
 *  assign the values of the center points along each side of the current 'unit' square we are calculating
 */
void diamond(int** map, int x, int y, int length, int size) {
    //top
    if(y > 0) {
        //if we are not on the edge of the map, we have 4 points to average
        map[y][x + (length >> 1)] = (map[y][x] + map[y][x + length] + map[y - (length >> 1)][x + (length >> 1)] + map[y + (length >> 1)][x + (length >> 1)]) >> 2;
    } else {
        //else we only have 3 points to average
        //NOTE: we could actually take the value on the opposite edge as our 4th point and create a heightmap that could be seamlessly tiled, but thats not what we are going for here
        map[y][x + (length >> 1)] = (map[y][x] + map[y][x + length] + map[y + (length >> 1)][x + (length >> 1)]) / 3;
    }
    
    //left
    if(x > 0) {
        map[y + (length >> 1)][x] = (map[y][x] + map[y + length][x] + map[y + (length >> 1)][x - (length >> 1)] + map[y + (length >> 1)][x + (length >> 1)]) >> 2;
    } else {
        map[y + (length >> 1)][x] = (map[y][x] + map[y + length][x] + map[y + (length >> 1)][x + (length >> 1)]) / 3;
    }
    
    //right
    if(x + length < size) {
        map[y + (length >> 1)][x + length] = (map[y][x + length] + map[y + length][x + length] + map[y + (length >> 1)][x + (length >> 1)] + map[y + (length >> 1)][x + length + (length >> 1)]) >> 2;
    } else {
        map[y + (length >> 1)][x + length] = (map[y][x + length] + map[y + length][x + length] + map[y + (length >> 1)][x + (length >> 1)]) / 3;
    }
    
    //bottom
    if(y + length < size) {
        map[y + length][x + (length >> 1)] = (map[y + length][x] + map[y + length][x + length] + map[y + (length >> 1)][x + (length >> 1)] + map[y + length + (length >> 1)][x + (length >> 1)]) >> 2;
    } else {
        map[y + length][x + (length >> 1)] = (map[y + length][x] + map[y + length][x + length] + map[y + (length >> 1)][x + (length >> 1)]) / 3;
    }
}

/**
 * Take the 4 corners and average them and apply a random to find the center value
 */
void square(int** map,int x, int y, int length, int randomFactor) {
    int value = ((map[y][x] + map[y][x + length] + map[y + length][x] + map[y + length][x + length]) >> 2);
    if(rand() % 2){
        value += rand() % randomFactor;
    } else {
        value -= rand() % randomFactor;
    }
    map[y + (length >> 1)][x + (length >> 1)] = value;
}

/**
 * Generate the heightmap of 2^n+1 size, given max height, the given randomness factor, and the smoothnes function
 */
int** DiamondSquare::generateHeightmap(int size, int maxHeight, int randomFactor, void(*smoothFunc)(int&)) {
    //make sure we have a 2^n+1 size
    int check = size - 1;
    if((check >> 1) << 1 != check) {
        return NULL;
    }
    
    int **map = initializeHeightmap(size);
    seedCorners(map, size, maxHeight);
    
    int length = size - 1;
    while(length > 0) {
        for(int i = 0; i < size - 1; i += length) {
            for(int j = 0; j < size - 1; j += length) {
                square(map, j, i, length, randomFactor);
                diamond(map, j, i, length, size - 1);
            }
        }
        
        //the smoothness function is applied to the random factor to change the
        //max amount of randomness applied to the map as our length decreases.
        //Generally its a decrementing function used to decrease randomness
        //as we get more granular as to avoid unnatural spikes and valleys
        smoothFunc(randomFactor);
        
        length >>= 1;
    }
    
    return map;
}
