/* 
 * File:   main.cpp
 * Author: Suleyman Balaban
 *
 * Created on December 11, 2015, 3:26 AM
 */

#include "source.h"  

int suleymanReversi::Reversi::livingObjects = 0;

//start of main
int main(int argc, char** argv) {
    suleymanReversi::Reversi rev;
    int count = 1, choice;
    
    cout<<"########################## WELCOME ##########################"<<endl;
    cout<<"--------------------------------------------"<<endl;
    cout<<"- Test Call By Value : 1"<<endl<<"- Test Call By Reference: 2"<<endl;
    cout<<"- Test these functions at same time :12"<<endl;
    cout<<"- Play Reversi Game: 3"<<endl;
    cout<<">>>>>>>>>>>>>>:";
    
    do{
        count = 0;
        cin>>choice;
        if(cin.fail()||(choice!=1 && choice!=3 && choice!=2 && choice!=12)) {
            count = 1;
            cin.clear();
            cin.ignore(80,'\n');
            cout<<"You entered wrong type input, enter again:";
        }
        
    }while(count ==1);
    if(choice == 1) {
        cout<<"------------------ TEST CALL BY VALUE -------------------"<<endl;
        tester::testCallByValue(rev);
        cout<<"---------- After Call By Value object in main -----------"<<endl;
        cout<<rev;
        cout<<"---------------------------------------------------------"<<endl;
    }else if(choice == 1) {
        cout<<"---------------- TEST CALL BY REFERENCE -----------------"<<endl;
        tester::testCallByReference(rev);
        cout<<"-------- After Call By Reference object in main ---------"<<endl;
        cout<<rev;
        cout<<"---------------------------------------------------------"<<endl;
    }else if(choice == 1) {
        cout<<"------------------ TEST CALL BY VALUE -------------------"<<endl;
        tester::testCallByValue(rev);
        cout<<"---------- After Call By Value object in main -----------"<<endl;
        cout<<rev;        
        cout<<"---------------- TEST CALL BY REFERENCE -----------------"<<endl;
        tester::testCallByReference(rev);
        cout<<"-------- After Call By Reference object in main ---------"<<endl;
        cout<<rev;
        cout<<"---------------------------------------------------------"<<endl;
    }else if(choice == 3) 
        tester::testGame();             //play game
    cout<<"---------------------------------------------------------"<<endl;
    cout<<"########################## THE END ##########################"<<endl;
    return 0;
}

