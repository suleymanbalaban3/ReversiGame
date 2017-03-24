/* 
 * File:   source.h
 * Author: suleyman
 *
 * Created on 11 December 2015 Cumartesi, 3:26 AM
 */

#ifndef SOURCE_H
#define SOURCE_H


#include <iostream> 
#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;
using::istream; 
using::ostream;  
using::cout; 
using::cin;  
using::endl; 

namespace suleymanCell {
    class Cell {
    public:
        Cell(): row(0), column(0), character('.') {    }
        Cell(const int a, const int b): row(a), column(b), character('.') {    }
        inline Cell(const int a, const int b, const char character): 
                    row(a), column(b), character(character) {    }
        void setter(const int a, const int b, const char character);
        int getterRow()const {return row;}
        int getterColumn()const {return column;}
        char getterCharacter()const {return character;}
    private:
        int row;
        int column;
        char character;
    };
}
namespace suleymanReversi {
    class Reversi {
    public:
        Reversi();
        explicit Reversi(const int hightSize);
        inline Reversi(const int hightRow, const int widthCol, 
                        suleymanCell::Cell * gameCellsV);
        Reversi(const Reversi & obje);
        virtual ~Reversi();
        void setterForOperator(suleymanCell::Cell * gameCellsV);
        int getterHeight()const{return height;}
        int getterWidth()const{return width;}
        void setterBoard(const int hightRow,const int widthCol);
        void start(const char pcSign,const char userSign,const char *fileName);
        bool playGame(const char pcSign,const char userSign,
                    const char *fileName,Reversi & game); 
        static int livingObjectNumber (); 
        static void decrementLivingObjects(); 
        bool isBetter(const Reversi & otherObject); 
        void display();
        friend ostream & operator << (ostream Soutput, const Reversi veri);
        Reversi & operator =(const Reversi & obje); 
    private:
        const Reversi operator ++();
        const Reversi operator ++(int ignoreMe);
        void input(int fix,int &y);
        void createBoard();
        bool play () ;
        bool play(const int rowX,const int columnY); 
        void readFile(const char *fileName); 
        void writeFile(const char *fileName); 
        void playUp(const char sabit,const char değişken);  
        void playDown(const char sabit,const char değişken);  
        void playRight(const char sabit,const char değişken);  
        void playLeft(const char sabit,const char değişken);  
        void playRightUp(const char sabit,const char değişken);  
        void playRightDown(const char sabit,const char değişken);  
        void playLeftUp(const char sabit,const char değişken);  
        void playLeftDown(const char sabit,const char değişken);  
        bool trueOrNot(const int rowX,const int columnY); 
        void changing(const int rowX,const int columnY,const char sabit,
                    const char değisken); 
        bool endGame(const bool controlUser,const bool controlPc); 
        void clearVector(); int height; int width;
        static int livingObjects; 
        suleymanCell::Cell *gameCells;
        //yeni board resize yapmak icin
        vector<vector<suleymanCell::Cell> >currentBoard; 
        vector<vector<int> possibilities ; 
        //kullanici ve pc icin oynanacak hamleleri tutuyor
    };
}//test namespace
namespace tester { 
    void testGame();
    void testCallByValue(suleymanReversi::Reversi object); 
    void testCallByReference(suleymanReversi::Reversi & object);
}

#endif /* SOURCE_H */

