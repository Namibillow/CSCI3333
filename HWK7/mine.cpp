//
//  mine.cpp
//  CS3333
//
//  Created by 赤澤那美 on 10/18/18.
//  Copyright © 2018 Nami. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include "mine.h"
#include "batcoin.h"

BlockHeader mine(BlockHeader prev, int difficulty){
    BlockHeader b;
    bathash(prev, b.prev);

    for(int i=0; i< 8; i++){
        b.nonce[i] =  '0' + (rand() % 255);
    }
    bool zeros;
    while(true){
        zeros = false;
        BlockHeader temp;
        temp = b;
        bathash(b, temp.prev);
        
        for(int j=0; j< difficulty; j++){
            if(temp.prev[j]== 0){
                zeros = true;
            }
            else{
                zeros = false;
                break;
            }
        }
        if(zeros){
            return b;
        }
        else{
            for(int i=0; i< 8; i++){
                b.nonce[i] =  '0' + (rand() % 255);
            }
        }
    }
}
