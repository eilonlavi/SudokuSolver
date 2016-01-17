//
//  main.cpp
//  SudokuSolver
//
//  Created by Lavi on 2015-12-28.
//  Copyright © 2015 Lavi. All rights reserved.
//

#include <iostream>
using namespace std;
struct SudoSqr{
    bool canBe[9];
    int val;
    int choiceNum;
    SudoSqr(){
        for (int i=0;i<9;i++) canBe[i]=true;
        val=0;
        choiceNum=9;
    }
};


struct SudoBoard{
    SudoSqr sqr[9][9];
    bool removeChoice(int x, int y, int choice){
        if (sqr[x][y].canBe[choice-1]){
            sqr[x][y].canBe[choice-1]=false;
            sqr[x][y].choiceNum--;
            if (sqr[x][y].choiceNum<=0) return false;
            if (sqr[x][y].choiceNum==1){
                for (int i=1;i<=9;i++) if (sqr[x][y].canBe[i-1]){
                    cout << "Deduced " << x << " " <<y <<" "<< i << endl;
                    return putValue(x,y,i);
                }
            }
        }
        return true;
    }
    
    bool putValue(int x, int y, int value){
        bool success=true;
        sqr[x][y].val=value;
        for (int p=0;p<9;p++){
            if (p!=x)
            success&=removeChoice(p, y, value);
            if (p!=y)
            success&=removeChoice(x, p, value);
        }
        for (int _x=x-(x%3);_x<x+3-(x%3);_x++){
            for (int _y=y-(y%3);_y<y+3-(y%3);_y++){
                if (_x!=x || _y!=y)
                success&=removeChoice(_x, _y, value);
            }
        }
        return success;
    }
};

//true if board can be solved.
bool guess(SudoBoard &brd, int x, int y){
    if (y==9){
        cout << "Solved with guesses: "<<endl;
        for (int _y=0;_y<9;_y++){
            for (int _x=0;_x<9;_x++){
                cout << brd.sqr[_x][_y].val << " ";
            }
            cout << endl;
        }
        return true;
    }
    bool needToGuess=brd.sqr[x][y].val==0;
    for (int i=1;i<=9;i++){
        if (!needToGuess) i=brd.sqr[x][y].val;
        if (brd.sqr[x][y].canBe[i-1]){
            if (needToGuess) cout << "Guessing "<< x << " " << y <<" " << i << endl;
            SudoBoard playbrd(brd);
            playbrd.putValue(x, y, i);
            if (guess(playbrd, (x==8?0:x+1), (x==8?y+1:y))) return true;
        }
        if (!needToGuess) break;
    }
    return false;
}


int main(int argc, const char * argv[]) {
    SudoBoard brd;
    
    int x; int y; int v;
    while (cin >> y >> x >> v){
        x--;
        y--;
        if (!brd.putValue(x, y, v))
            cout << "Board is invalid";
            cout << endl;
            for (int _y=0;_y<9;_y++){
                for (int _x=0;_x<9;_x++){
                    cout << brd.sqr[_x][_y].val << " ";
                }
                cout << endl;
            }
    }
    cout << "starting guesswork" <<endl;
    guess(brd, 0, 0);
    
    
    
    
    return 0;
}








