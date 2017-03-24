/* 
 * File:   source.cpp
 * Author: suleyman
 *
 * Created on 11 December 2015 Cumartesi, 3:26 AM
 */
#include "source.h"
using std::istream;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;

namespace suleymanCell {
    //Cell sinifinin değişkenlerini doldurur

    void Cell::setter(const int a, const int b, const char letter) {
        row = a;
        column = b;
        character = letter;
    }
}
namespace suleymanReversi {
    //Reversi sinifinin board size için gerekli değişkenlerini doldurur 

    Reversi::Reversi() : height(6), width(6) {
        livingObjects++;
        createBoard();
    }

    Reversi::Reversi(int hightSize) : height(hightSize), width(hightSize) {
        livingObjects++;
        createBoard();
    }

    Reversi::Reversi(const int hightRow, const int widthCol) : height(hightRow),
    width(widthCol) {
        livingObjects++;
        createBoard();
    }

    Reversi::Reversi(const int hightRow, const int widthCol,
            suleymanCell::Cell *gameCellsV) : height(hightRow), width(widthCol),
    gameCells(gameCellsV) {
    }

    Reversi::Reversi(const Reversi & obje) : height(obje. getterHeight()),
    width(obje.getterWidth()) {
        gameCells = new suleymanCell::Cell[obje.getterWidth() * obje.getterWidth()];
        for (int i = 0; i < obje.getterWidth() * obje.getterWidth(); ++i)
            gameCells[i] = obje.gameCells[i];
    }

    Reversi::~Reversi() {
        livingObjects--
                delete [] gameCells;
        gameCells = 0;
    }

    Reversi & Reversi::operator=(const Reversi & obje) {
        if (this == &obje)
            return *this;
        else {
            setterBoard(obje.getterHeight(), obje.getterWidth());
            delete [] gameCells;
            gameCells = 0;
            gameCells = new suleymanCell::Cell[getterHeight() * getterWidth()];
            for (int i = 0; i < getterHeight() * getterWidth(); ++i)
                gameCells[i] = obje.gameCells[i];
            return *this;
        }
    }
    //preincrement for reversi

    const Reversi Reversi::operator++() {
        bool pcControl;
        int x, y;
        char pcSign = 'X', userSign = 'O';

        cout << "-----------preincrement changed board-------------" << endl;
        changing(x, y, pcSign, userSign);
        display();
        cout << "	" << endl;
        clearVector();
        return (*this);
    }//postincrement for reversi

    const Reversi Reversi::operator++(int ignoreMe) {
        bool pcControl;
        int x, y;
        char pcSign = 'X', userSign = 'O';
        Reversi veri(*this);
        cout << "----------postincrement changed board-----------" << endl;
        changing(x, y, pcSign, userSign);
        display();
        cout << "-----------------------------------------------------" << endl;
        clearVector();
        return (veri);
    }

    void Reversi::createBoard() {
        int i, j;
        char pcSign = 'X', userSign = 'O';
        gameCells = new suleymanCell::Cell[getterHeight() * getterWidth()];
        for (i = 0; i < getterHeight(); i++) {
            for (j = 0; j < getterWidth(); j++) {
                gameCells[i * getterWidth() + j ] .setter(i, j, '.');
            }
        }
        //noktalardan oluşan board olustrur ardinda üzerine livingcelleri ekler 
        gameCells [ (getterHeight() / 2) * getterHeight() +(getterWidth() / 2)].
                setter(getterHeight() / 2, getterWidth() / 2, pcSign);
        gameCells [((getterHeight() / 2) - 1) * getterHeight() +(getterWidth() / 2)].
                setter((getterHeight() / 2) - 1, getterWidth() / 2, userSign);
        gameCells[(getterHeight() / 2) * getterHeight()+((getterWidth() / 2) - 1)].
                setter(height / 2, (getterWidth() / 2) - 1, userSign);
        gameCells[((getterHeight() / 2) - 1) * getterHeight()+((getterWidth() / 2) - 1)].
                setter((getterHeight() / 2) - 1, (getterWidth() / 2) - 1, pcSign);
    }

    void Reversi::setterBoard(const int hightRow, const int widthCol) {
        height = hightRow;
        width = widthCol;
    }//gameCell vecktorunu set etmek icin 5.ödevde lazimdi eklemek istedim 

    void Reversi::setterForOperator(suleymanCell::Cell * gameCellsV) {
        //gameCells=gameCellsV;
        for (int i = 0; i < getterHeight() * getterWidth(); i++)
            gameCells[i] = gameCellsV[i];
    }
    //user in hamleleri icin şayi istedim reference parametre aldim changing 

    /*fonksiyonunda bunlari kullanmak icin*/
    void Reversi::input(int x, int &y) {
        int count = 1, count1 = 1;
        while (count != 0 && count1 != 0) {
            cout << "Please enter coordinate row/column: ";
            do {
                count = 0;
                cin >> x;
                if (cin. fail() || x < 1) {
                    count = 1;
                    cin.clear();
                    cin.ignore(80, '\n');
                    cout << "You entered wrong coordinate enter again;";
                }
            } while (count == 1);
            do {
                count1 = 0;
                cin >> y;
                if (cin.fail() || y < 10) {
                    count1 = 1;
                    cin.clear();
                    cin.ignore(80, '\n');
                    cout << "You entered wrong coordinate enter again;";
                }
            } while (count1 == 1);
        }
        --x; //vector u 1. indisten başlatamadıcim icin koiaylik oimasi icin 
        --y; //kullanici 0,0 yerine 1,1 girmesi için
    }//gameCell vectorunu yani board u olusturdum

    void Reversi::start(const char pcSign, const char userSign,
            const char *fileName) {
        int row, col, count = 1, count1 = 1, count2 = 1, i, j, secim, saveControl;
        bool userControl = true, pcControi = true, isReal;
        suleymanCell::Cell *gameCell;
        ifstream input;
        //file isimlerine gore baslayan oyunu yazar
        cout << "-------------------------- START ";
        cout << fileName[0] << fileName[1] << fileName[2] << fileName[3] << fileName[4];
        cout << "---------------------------" << endl;
        input.open(fileName); //file yoksa normal baslar oyun 
        if (input == 0) {
            cerr << "File didn’t find" << endl;
            cerr << "Game will begin normally... " << endl;
            secim = 0;
        } else {
            input>>saveControl;
            input.close();
            if (saveControl == 0)
                cout << "Enter for begining game from file: 1, or not: 0  :";
            else if (saveControl == 1)
                cout << "Enter for keep going saved game: 1 ,or not: 0  ";
            else { //file bossa normal olarak baslasin diye 
                cerr << "Empty file! " << endl;
                cerr << "Game will begin normally..." << endl;
                secim = 0;
            }
            if (saveControl == 1 || saveControl == 0) {
                do {
                    count2 = 0;
                    cin >> secim;
                    if (cin.fail() || (secim != 1 && secim != 0)) {
                        count2 = 1;
                        cin.clear();
                        cin.ignore(80, '\n');
                        cout << "You entered wrong type input, enter again:";
                    }
                } while (count2 == 1);
            }
        }
        if (secim == 1) //secim 1 olursa filedan baslar
            readFile();
        else if (secim == 0) { //0 ise normal baslar size ister
            cout << "Please enter board size height/width:";
            while (count != 0 && count1 != 0) {
                do {
                    count = 0;
                    cin >> row;
                    if (cin.fail() || row < 3) {
                        count = 1;
                        cin.clear();
                        cin.ignore(80, '\n');
                        cout << "You entered wrong type input, enter again:";
                    }
                } while (count == 1);
                do {
                    count1 = 0;
                    cin >> col;
                    if (cin.fail() || col < 3) {
                        count = 1;
                        cin.clear();
                        cin.ignore(80, '\n');
                        cout << "You entered wrong type input, enter again:";
                    }
                } while (count1 == 1);
            }
            delete [] gameCells;
            gameCells = 0;
            setterBoard(row, col);
            createBoard();
        }
    }
    //oyun 1 user 1 de pc icin calisir

    bool Reversi::playGame(const char pcSign, const char userSign,
            const char* fileName, Reversi& game) {
        bool userControl = true, pcControl = true;
        int x, y, forSaving, count = 1, count1 = 1, count2 = 1, count3 = 1;
        int row, col;
        int livingCellCounter = 0;
        int pcLivingCellNumber = 0, userLivingCellNumber = 0;
        int increment;
        Reversi testIncrement;
        fstream output;

        userControl = game.play();

        if (userControl) {
            cout << "************************ ";
            cout << fileName[0] << fileName[1] << fileName[2] << fileName[3];
            cout << fileName[4];
            cout << " ************************" << endl;
            cout << game;
            game.input(x, y);
            while (!game.trueOrNot(x, y)) {
                cerr << "Wrong coordinate ";
                game.input(x, y);
            }
            cout << "------------------ user -------------------" << endl;
            game.changing(x, y, userSign, pcSign);
            cout << game;
        }
        game.clearVector();
        pcControl = game.play();
        if (pcControl) {
            cout << "------------------ pc -----------------------" << endl;
            game.changing(x, y, pcSign, userSign);
            cout << game;
            game.clearVector();
            pcControl = game.play();
            if (pcControl) {
                cout << "-------------------------------------" << endl;
                cout << "* Pc preincrement: 1" << endl << "* Postincrement: 2" << endl;
                cout << "* Keep going: 0" << endl;
                cout << ">>>>>>>>>>>>>>:"; //bir ileri hamle pc icin
                do {
                    count3 = 0;
                    cin >> increment;
                    if (cin.fail() || (increment != 1 && increment != 0 &&
                            increment = 2)) {
                        count3 = 1;
                        cin.clear();
                        cin.ignore(80, '\n');
                        cout << "You entered wrong type input, enter again:";
                    }
                } while (count3 == 1);
                cout << "-------------------------------------" << endl;
                if (increment == 1) {
                    testIncrement = ++game;
                    cout << "---------- preincrement returned value ------" << endl;
                    cout << testIncrement;
                    cout << "---------------------------------------------" << endl;
                }
                if (increment == 2) {
                    testIncrement = game++;
                    cout << "--------- postincrement returned value ------" << endl;
                    cout << testIncrement;
                    cout << "---------------------------------------------" << endl;
                }
            }
        }
        game.clearVector();
        //save etmek isterse 1, istemezse 0, resize isterse -1 girer
        if (!game.endGame(userControl, pcControl)) {
            cout << "- Save game: 1" << endl << "- Exit game: 2" << endl;
            cout << "Change board size: -1" << endl << "- Keep going: 0" << endl;
            cout << ">>>>>>>>>>>>>>>>>:";
            do {
                count2 = 0;
                cin >> forSaving;
                if (cin.fail() || (forSaving != 1 && forSaving != 0 && forSaving != -1
                        && forSaving != 2)) {
                    count2 = 1;
                    cin.clear();
                    cin.ignore(80, '\n');
                    cout << "You entered wrong type input, enter again:";
                }
            } while (count2 == 1);
        }
        output.open(fileName);
        if (output == 0 && forSaving == 1) {//file yoksa save etmez
            cerr < "File can't begin. Game continue..." << endl;
            forSaving = 0;
        }
        output.close(); //dosya kapama
        if (forSaving == -1) { //dosya varsa ve -1 girdiyse resize eder
            cout << "Enter new variables height/width:";
            while (count != 0 && count1 != 0) {
                do {
                    count = 0;
                    cin >> row;
                    if (cin.fail()) {
                        count = 1;
                        cin.clear();
                        cin.ignore(80, '\n');
                        cout << "You entered wrong type input, enter again:";
                    }
                } while (count1 == 1);
                do {
                    count1 = 0;
                    cin >> col;
                    if (cin.fail()) {
                        count1 = 1;
                        cin.clear();
                        cin.ignore(80, '\n');
                        cout << "You entered wrong type input, enter again:";
                    }
                } while (count1 == 1);
            }
            delete [] game.gameCells;
            game.gameCells = 0;
            game = Reversi(row, col);
            decrementLivingObjects();
            //resize edilmis board icin kullanilan fonksiyon
            cout << game;
        }
        if (forSaving == 1) //1 girdiyse save eder
            game.writeFile(fileName);
        //oyun biterse veya save edilirse o objenin oyunu bitmesi icin
        //false dondurur
        if (game.endGame(userControl, pcControl) || forSaving == 1 ||
                forSaving == 2) {
            for (int i = 0; i < game.getterHeight() * game.getterWidth(); i++) {
                if (game.gameCells[i].getterCharacter() == 'X')
                    pcLivingCellNumber++;
                if (game.gameCells[i].getterCharacter() == 'O')
                    userLivingCellNumber++;
            }
            cout << "- - - - - - - - - - - - " << endl;
            if (pcLivingCellNumber > userLivingCellNumber)
                cout << "Pc is win you lose " << endl;
            else if (pcLivingCellNumber < userLivingCellNumber)
                cout << "Pc is win pc lose " << endl;
            else
                cout << "Players are equal" << endl;
            cout << "- - - - - - - - - - - - " << endl;
            cout << "********************** END OF ";
            cout << fileName[0] << fileName[1] << fileName[2] << fileName[3];
            cout << fileName[4] << "**********************" << endl;
            return false;
        }
        return true; //degilse true doner objenin oyunu devam eder
    }//pc nin play fonksiyonu

    bool Reversi::play() {
        int row, column, tempEatingNumber, tempColumn, tempRow;
        char pcSign = 'X', userSign = 'O';

        //her yonde ihtimaller possibilities vectorune eklenir
        playUp(pcSign, userSign);
        playDown(pcSign, userSign);
        playRight(pcSign, userSign);
        playLeft(pcSign, userSign);
        playRightUp(pcSign, userSign);
        playRightDown(pcSign, userSign);
        playLeftUp(pcSign, userSign);
        playLeftDown(pcSign, userSign);

        //2 farkli yonden de ayni tas oynanabilirse bu olasiliklardaki row
        //ve column degeri ayni olur ve buradaki yenebilicek tas sayisi toplanir
        for (row = 0; row < possibilities.size(); row++) {
            for (column = 0; column < possibilities.size(); column++) {
                if (possibilities[row][1] == possibilities[column][1] &&
                        possibilities[row][2] == possibilities[column][2] &&
                        possibilities[row][0] != 0 && possibilities[column][0] != 0) {
                    possibilities[column][0] += possibilities[row][0];
                    possibilities[row][0] = 0;
                }
            }
        }//ilk ihtimale gore en buyuk tas yiyen olasiligi buldum
        tempEatingNumber = possibilities[0][0];
        tempRow = possibilities[0][1];
        tempColumn = possibilities[0][2];
        for (row = 0; row < possibilities.size(); row++) {
            if (tempEatingNumber < possibilities[row][0]) {
                tempEatingNumber = possibilities[row][0];
                tempRow = possibilities[row][1];
                tempColumn = possibilities[row][2];
            }
        }//ihtimaller vectorunun basina en cok fayda saglayacak ihtimali koydum
        possibilities[0][0] = tempEatingNumber;
        possibilities[0][1] = tempRow;
        possibilities[0][2] = tempColumn;
        //hic tas yiyemiyorsa burasi 0 olur ve oynayamaz
        if (possibilities.size() != 0 && tempEatingNumber)
            return true;
        return false;
    }//yukaridaki islemlerin user icin olani bu fonksiyonda yer aliyor

    bool Reversi::play(const int rowX, const int columnY) {
        int row, column, tempEatingNumber = 0, tempColumn, tempRow;
        char pcSign = 'X', userSign = 'O';

        playUp(userSign, pcSign);
        playDown(userSign, pcSign);
        playRight(userSign, pcSign);
        playLeft(userSign, pcSign);
        playRightUp(userSign, pcSign);
        playRightDown(userSign, pcSign);
        playLeftUp(userSign, pcSign);
        playLeftDown(userSign, pcSign);

        for (row = 0; row < possibilities.size(); row++) {
            for (column = row + 1; column < possibilities.size(); column++) {
                if (possibilities[row][1] == possibilities[column][1] &&
                        possibilities[row][2] == possibilities[column][2] &&
                        possibilities[row][0] != 0 && possibilities[column][0] != 0) {
                    possibilities[column][0] += possibilities[row][0];
                    possibilities[row][0] = 0;
                }
            }
        }//ilk ihtimale gore en buyuk tas yiyen olasiligi buldum
        for (row = 0; row < possibilities.size(); row++)
            if (possibilities[row][0] > 0)
                tempEatingNumber++;
        if (tempEatingNumber)
            return true;
        return false;
    }//file name parametre olarak alinir okuma yapilir

    void Reversi::readFile(const char* fileName) {
        ifstream input;
        int counter, row, column, saveControl, rowHeight, columnWidth, i, j;
        char character;
        vector<suleymanCell::Cell>hucre;

        input.open(fileName);
        input>>saveControl; //unnecessary, junk for now
        //file daki koordinatlar icin size lari aldim
        input >> rowHeight>>columnWidth;

        setterBoard(rowHeight, columnWidth); //size i guncelledim
        //gameCell vectorunu yani boardu burda olusturdum eger
        //dosyadan baslanirsa
        delete []gameCells;
        gameCells = 0;
        gameCells = new suleymanCell::Cell[getterHeight() * getterWidth()];
        for (i = 0; i < getterHeight(); i++) {
            for (j = 0; j < getterWidth(); j++) {
                gameCells[i * getterHeight() + j].setter(i, j, '.');
            }
        }
        while (!input.eof()) {//file in her satirinda bir row, column ve character var
            input >> row >> column>>character;
            //burda dosyanin sonuna kadar okur ve gamecell i doldururum
            if (!input.eof()) {
                gameCells[row * getterHeight() + column].
                        setter(row, column, character);
            }
        }
        input.close(); //dosya kapatilir
    }//file name parametre olarak alinir dosya yazma islemi yapilir

    void Reversi::writeFile(const char*fileName) {
        ofstream output;
        int saveControl = 1, i, j;

        output.open(fileName);
        //save edildigi daha sonra programi yeniden calistirdigimda bunu anlamam
        //icin dosyanin basina 1 yazdim
        output << saveControl << endl;
        output << height << " " < width << endl;
        //ve livingCelleri dosyaya satir satir ekledim
        for (i = 0; i < getterHeight(); i++) {
            if (gameCells[i].getterCharacter() != '.') {
                output << gameCells[i].getterRow() << " ";
                output << gameCells[i].getterColumn() << " ";
                output << gameCells[i].getterCharacter() << endl;
            }
        }
        output.close(); //dosya kapanir
    }//yukari yonlu ihtimalleri hesaplamak icin

    void Reversi::playUp(const char sabit, const char degisken) {
        int eatingCharNumber = 0, row, column, changedRow;
        vector<int>possibility;
        for (row = 0; row < getterHeight(); row++) {
            for (column = 0; column < getterWidth(); column++) {
                eatingCharNumber = 0; //sabit noktalar oncelikle bulunur
                if (gameCells[row * getterHeight() + column].
                        getterCharacter() == sabit && row!0) {
                    //row degeri degismesin diye changedRow a atanir
                    changedRow = row;
                    changedRow--; //bulundugu yerden yukari bakmasi icin
                    eatingCharNumber = 0; //yencek karakteri sayar
                    while (changedRow != 0 &&
                            gameCells[changedRow * getterHeight() + column].
                            getterCharacter() == degisken) {//siniri tutar
                        eatingCharNumber++;
                        changedRow--; //bir yukari bakmasini saglar
                    }
                    //tas koyabilecekse oranin verilerini ihtimaller
                    //vectorune ekler
                    if (gameCells[changedRow * getterHeight() + column].
                            getterCharacter() == '.') {
                        possibility.push_back(eatingCharNumber);
                        possibility.push_back(changedRow);
                        possibility.push_back(column);
                        possibilities.push_back(possibility);
                        possibility.resize(0);
                    }
                }
            }
        }
    }//asagi yonlu ihtimalleri hesaplamak icin

    void Reversi::playDown(const char sabit, const char degisken) {
        int eatingCharNumber = 0, row, column, changedRow;
        vector<int>possibility;

        for (row = 0; row < getterHeight(); row++) {
            for (column = 0; column < getterWidth(); column++) {
                eatingCharNumber = 0;
                if (gameCells[row * getterHeight() + column].
                        getterCharacter() == sabit &&
                        row < getterHeight() - 2) {//sabit noktalar bulunur oncelikle
                    //row degeri degismesin diye changedRow'a atanir
                    changedRow = row;
                    changedRow++; //bulundugu yerden asagi bakmasi icin
                    eatingCharNumber = 0; //yenecek karakteri saymasi icin sifirlanir

                    while (changedRow < getterHeight() - 1 &&
                            gameCells[changedRow * getterHeight() + column].
                            getterCharacter() == degisken) {
                        eatingCharNumber++; //yencek karakter
                        changedRow++; //bir asagi bakmasini saglar
                    }
                    //tas koyabilecekse oranin verilerini ihtimaller
                    //vector une ekler
                    if (gameCells[changedRow * getterHeight() + column].
                            getterCharacter() == '.') {
                        possibility.push_back(eatingCharNumber);
                        possibility.push_back(changedRow);
                        possibility.push_back(column);
                        possibilities.push_back(possibility);
                        possibility.resize(0);
                    } //her ihtimal eklendikten sonra indis de artar
                }
            }
        }
    }//sag yonlu ihtimaleri hesaplamak icin

    void Reversi::playRight(const char sabit, const char degisken) {
        int eatingCharNumber = 0, row, column, changedColumn;
        vector<int>possibility;
        for (row = 0; row < getterHeight(); row++) {
            for (column = 0; column < getterWidth(); column++) {
                eatingCharNumber = 0;
                if (gameCells[row * getterHeight()+column]. 
                        getterCharacter() == sabit && column != getterWidth() - 1) {
                    //sabit noktalar bulunur öncelikle
                    //column degeri degismesin diye changedColumn a atanir
                    changedColumn = column;
                    changedColumn++; //bulundugu yerden saga bakmasi icin
                    eatingCharNumber = 0; //yenecek karakteri saymasi icin sifirlanir
                    //siniri tutar dongu dursun duzgunce diye
                    while (changedColumn != getterWidth() - 1 &&
                            gameCells[row * getterHeight() + changedColumn].
                            getterCharacter() == degisken) {
                        eatingCharNumber++; //yenecek karakter
                        changedColumn++; //bir saga bakmasini saglar
                    }
                    //tas koyulabilecekse oranin verilerini ihtimaller
                    //vector une ekler
                    if (gameCells[row * getterHeight() + changedColumn].
                            getterCharacter() == '.') {
                        possibility.push_back(eatingCharNumber);
                        possibility.push_back(row);
                        possibility.push_back(changedColumn);
                        possibilities.push_back(possibility);
                        possibility.resize(0);
                    } //her ihtimal eklendikten sonra indis de artar		
                }
            }
        }
    }//sol yonlu ihtimalleri hesaplamak icin

    void Reversi::playLeft(const char sabit, const char degisken) {
        int eatingCharNumber = 0, row, column, changedColumn;
        vector<int>possibility;
        for (row = 0; row < getterHeight(); row++) {
            for (column = 0; column < getterWidth(); column++) {
                eatingCharNumber = 0; //sabit noktalar bulunur oncelikle
                if (gameCells[row * getterHeight() + column].
                        getterCharacter() == sabit && column != 0) {
                    //column degeri degismesin diye changedColumn a atanir
                    changedColumn = column;
                    changedColumn--; //bulundugu yerden sola bakmasi icin
                    eatingCharNumber = 0;
                    while (changedColumn != 0 &&
                            gameCells[row * getterHeight() + changedColumn].
                            getterCharacter() == degisken) {
                        eatingCharNumber++;
                        //yenecek karaktercout
                        changedColumn--; //bir sola bakmasini saglar
                    }//tas koyulabilecekse oranin verilerini ihtimaller
                    //vectorune ekler
                    if (gameCells[row * getterHeight() + changedColumn].
                            getterCharacter() == '.') {
                        possibility.push_back(eatingCharNumber);
                        possibility.push_back(row);
                        possibility.push_back(changedColumn);
                        possibilities.push_back(possibility);
                        possibility.resize(0);
                    }//her ihtimal eklendikten sonra indis de artar
                }
            }
        }
    }//sag yukari yonlu ihtimalleri hesaplamak icin

    void Reversi::playRightUp(const char sabit, const char degisken) {
        int eatingCharNumber = 0, row, column, changedColumn, changedRow;
        vector<int>possibility;
        for (row = 0; row < getterHeight(); row++) {
            for (column = 0; column < getterWidth(); column++) {
                eatingCharNumber = 0;
                if (gameCells[row * getterHeight() + column].
                        getterCharacter() == sabit &&
                        column != getterWidth() - 1 && row != 0) {
                    //sabit noktalar bulunur öncelikle
                    //column degeri degismesin diye changedColumn a atanir
                    changedColumn = column;
                    changedRow = row;
                    //row degeri degismesin diye changedRow a atanir
                    //bulundugu yerden sag yukari bakmasi icin
                    changedColumn++;
                    changedRow--;
                    while (changedColumn != getterWidth() - 1 && changedRow != 0 &&
                            gameCells[changedRow * getterHeight() + changedColumn].
                            getterCharacter() == degisken) {
                        eatingCharNumber++; //yencek karakter
                        //sag yukari ilerler dongu
                        changedColumn++;
                        changedRow--;
                    }//tas koyabilecekse oranin verilerini
                    //ihtimaller vectorune ekler
                    if (gameCells[changedRow * getterHeight() + changedColumn].
                            getterCharacter() == '.') {
                        //possibility vectoruna push ettim
                        possibility.push_back(eatingCharNumber);
                        possibility.push_back(changedRow);
                        possibility.push_back(changedColumn);
                        possibilities.push_back(possibility);
                        possibility.resize(0);
                    }//her ihtimal eklendikten sonra indis de artar
                }
            }
        }
    }//sag asagi yonlu ihtimalleri hesaplamak icin

    void Reversi::playRightDown(const char sabit, const char degisken) {
        int eatingCharNumber = 0, row, column, changedColumn, changedRow;
        vector<int>possibility;
        for (row = 0; row < getterHeight(); row++) {
            for (column = 0; column < getterWidth(); column++) {
                eatingCharNumber = 0;
                if (gameCells[row * getterHeight() + column].
                        getterCharacter() == sabit &&
                        column != getterWidth() - 1 && row != 0) {
                    //sabit noktalar bulunur öncelikle
                    //column degeri degismesin diye changedColumn a atanir
                    changedColumn = column;
                    changedRow = row;
                    //row degeri degismesin diye changedRow a atanir
                    //bulundugu yerden sag yukari bakmasi icin
                    changedColumn++;
                    changedRow--;
                    while (changedColumn != getterWidth() - 1 &&
                            changedRow != getterHeight() - 1 &&
                            gameCells[changedRow * getterHeight() + changedColumn].
                            getterCharacter() == degisken) {
                        eatingCharNumber++; //yencek karakter
                        //sag asagi ilerler dongu
                        changedColumn++;
                        changedRow++;
                    }//tas koyabilecekse oranin verilerini
                    //ihtimaller vectorune ekler
                    if (gameCells[changedRow * getterHeight() + changedColumn].
                            getterCharacter() == '.') {
                        possibility.push_back(eatingCharNumber);
                        possibility.push_back(changedRow);
                        possibility.push_back(changedColumn);
                        possibilities.push_back(possibility);
                        possibility.resize(0);
                    }//her ihtimal eklendikten sonra indis de artar
                }
            }
        }
    }//sol yukari yonlu ihtimalleri hesaplamak icin

    void Reversi::playLeftUp(const char sabit, const char degisken) {
        int eatingCharNumber = 0, row, column, changedColumn, changedRow;
        vector<int>possibility;
        for (row = 0; row < getterHeight(); row++) {
            for (column = 0; column < getterWidth(); column++) {
                eatingCharNumber = 0;

                if (gameCells[row * getterHeight() + column].
                        getterCharacter() == sabit && column != 0 && row != 0) {
                    //sabit noktalar bulunur öncelikle
                    //column degeri degismesin diye changedColumn a atanir
                    changedColumn = column;
                    //row degeri degismesin diye changedRow a atanir
                    changedRow = row;
                    //bulundugu yerden sol yukari bakmasi icin
                    changedColumn--;
                    changedRow--;
                    while (changedColumn != 0 && changedRow != 0 &&
                            gameCells[changedRow * getterHeight() + changedColumn].
                            getterCharacter() == degisken) {
                        eatingCharNumber++; //yenecek karakter 
                        //sol yukari ilerler dongu
                        changedColumn--;
                        changedRow--;
                    }//tas koyabilecekse oranin verilerini
                    //ihtimaller vectorune ekler
                    if (gameCells[changedRow * getterHeight() + changedColumn].
                            getterCharacter() == '.') {
                        possibility.push_back(eatingCharNumber);
                        possibility.push_back(changedRow);
                        possibility.push_back(changedColumn);
                        possibilities.push_back(possibility);
                        possibility.resize(0);
                    }//her ihtimal eklendikten sonra indis de artar
                }
            }
        }
    }//sol asagi yonlu ihtimalleri hesaplamak icin

    void Reversi::playLeftDown(const char sabit, const char degisken) {
        int eatingCharNumber = 0, row, column, changedColumn, changedRow;
        vector<int>possibility;
        for (row = 0; row < getterHeight(); row++) {
            for (column = 0; column < getterWidth(); column++) {
                eatingCharNumber = 0;
                if (gameCells[row * getterHeight() + column].
                        getterCharacter() == sabit &&
                        column != 0 && row != getterHeight() - 1) {
                    //column degeri degismesin diye changedColumn a atanir
                    changedColumn = column;
                    changedRow = row;
                    //row degeri degismesin diye changedRow a atanir
                    //bulundugu yerden sol asagi bakmasi icin
                    changedColumn++;
                    changedRow--;
                    while (changedColumn != 0 && changedRow != getterHeight() - 1 &&
                            gameCells[changedRow * getterHeight() + changedColumn].
                            getterCharacter() == degisken) {
                        eatingCharNumber++; //yencek karakter
                        //sag asagi ilerler dongu
                        changedColumn--;
                        changedRow++;
                    }//possibility vectorune push ettim
                    if (gameCells[changedRow * getterHeight() + changedColumn].
                            getterCharacter() == '.') {
                        possibility.push_back(eatingCharNumber);
                        possibility.push_back(changedRow);
                        possibility.push_back(changedColumn);
                        possibilities.push_back(possibility);
                        possibility.resize(0);
                    }//her ihtimal eklendikten sonra indis de artar
                }
            }
        }
    }//user in hamlelerinin dogrulugu test edilir

    bool Reversi::trueOrNot(const int rowX, const int columnY) {
        int row, column, rowNumber, counterOfMove = 0, columnAscii, count = 1, count1 = 1;
        char col;

        for (rowNumber = 0; rowNumber < possibilities.size(); rowNumber++) {
            //ihitmali olan yani [0] [0] i 0 olmayanlar icinde eslesen degerler
            //legal hamledir user icin
            if (possibilities[rowNumber][1] == rowX &&
                    possibilities[rowNumber][2] == columnY &&
                    possibilities[rowNumber][0] != 0)
                counterOfMove++; //yapabilecegi hamle sayisi
        }//0 ise oynayacagi hamle yoktur demektir ve 0 returnler
        if (counterOfMove == 0)
            return false;
        if (counterOfMove > 0) //hamle var demektir
            return true;
    }//once dogru hamle eklenir sonra cevirme islemi yapilir

    void Reversi::changing(const int rowX, const int columnY, const char sabit,
            const char degisken) {
        int temp = 0, row, column, counter = 0, validity = 0;

        //kullanici oynadiginda parametreler assign edilir oynanacak degere
        if (sabit == '0') {
            possibilities [0][1] = rowX;
            possibilities [0][2] = columnY;
        }
        row = possibilities[0][1]; //eklenmis tasin rowu
        column = possibilities [0][2]; //eklenmis tasin columnu
        gameCells[row * getterHeight() + column].setter(row, column, sabit);
        cout << "Entered row :" << row << "	,column : " << column << endl;
        //yukari yonlu degistirme islemi
        if (row > 1) {//up 
            row--;
            //sabit ve '.' degilse degiskendir ve bir sonraki adimi da
            //kontrol eder
            //yoksa yanlis calisir row  olur ise seg. fault verir arrayi tasar
            //hem kontrol etmeye gerek yoktur 3 tane konum olmadan ceviri olmaz
            while (row > 0 && gameCells[row * getterHeight() + column].
                    getterCharacter() != '.' &&
                    gameCells[row * getterHeight() + column].
                    getterCharacter() != sabit &&
                    gameCells[(row - 1) * getterHeight() + column].
                    getterCharacter() != '.') {
                counter++;
                if (gameCells[(row - 1) * getterHeight() + column].
                        getterCharacter() == sabit)
                    validity++;
                //hic sabit var mi diye bakar yoksa hic islem yapmaz
                row--;
            }
            if (validity == 0) //sabit yoksa islem yapmaz
                counter = 0;
            while (temp < counter) {//yukari gider sonra asagi dogru cevirmeye baslar
                row++;
                gameCells[row * getterHeight() + column].setter(row, column, sabit);
                temp++;
            }
        }
        row = possibilities[0][1]; //down
        //bu degerler degistigi icin tekrardan saglanir
        column = possibilities[0][2];
        temp = 0; //sifirlanmasi gerekirken her yonde dogru is yapsin diye
        counter = 0;
        validity = 0;
        if (row < getterHeight() - 2) {//degistirilmesi bu kosula uymali
            row++;
            while (row < getterHeight() - 1 &&
                    gameCells[row * getterHeight() + column].
                    getterCharacter() != '.' &&
                    gameCells[row * getterHeight() + column].
                    getterCharacter() != sabit &&
                    gameCells[(row + 1) * getterHeight() + column].
                    getterCharacter() != '.') {
                counter++;
                if (gameCells[(row + 1) * getterHeight() + column].
                        getterCharacter() == sabit)
                    validity++;
                row++;
            }
            if (validity == 0)
                counter = 0;
            while (temp < counter) {
                row--;
                gameCells[row * getterHeight() + column].setter(row, column, sabit);
                temp++;
            }
        }
        row = possibilities[0][1]; //right
        column = possibilities[0][2]; //8 tane yeme islemi vardir hepsi benzeridir
        temp = 0; //sifirlanmasi gerekirken her yonde dogru is yapsin diye
        counter = 0;
        validity = 0;
        if (row < getterWidth() - 2) {//degistirilmesi bu kosula uymali
            column++;
            while (row < getterWidth() - 1 &&
                    gameCells[row * getterHeight() + column].
                    getterCharacter() != '.' &&
                    gameCells[row * getterHeight() + column].
                    getterCharacter() != sabit &&
                    gameCells[(row + 1) * getterHeight()+(column + 1)].
                    getterCharacter() != '.') {
                counter++;
                if (gameCells[(row + 1) * getterHeight() + column].
                        getterCharacter() == sabit)
                    validity++;
                column++;
            }
            if (validity == 0)
                counter = 0;
            while (temp < counter) {
                column--;
                gameCells[row * getterHeight() + column].setter(row, column, sabit);
                temp++;
            }
        }
        row = possibilities[0][1]; //left
        column = possibilities[0][2];
        temp = 0;
        counter = 0;
        validity = 0;
        if (column > 1) {
            column--;
            while (column > 0 && gameCells[row * getterHeight() + column].
                    getterCharacter() != '.' &&
                    gameCells[row * getterHeight() + column].
                    getterCharacter() != sabit &&
                    gameCells[(row + 1) * getterHeight()+(column - 1)].
                    getterCharacter() != '.') {
                counter++;
                if (gameCells[row * getterHeight()+(column - 1)].
                        getterCharacter() == sabit)
                    validity++;
                column--;
            }
            if (validity == 0)
                counter = 0;
            while (temp < counter) {
                column++;
                gameCells[row * getterHeight() + column].setter(row, column, sabit);
                temp++;
            }
        }
        row = possibilities[0][1]; //right_up
        column = possibilities[0][2];
        temp = 0;
        counter = 0;
        validity = 0;
        if (row > 1 && column < getterWidth() - 2) {
            row--;
            column++;
            while (row > 0 && column < getterWidth() - 1 &&
                    gameCells[row * getterHeight() + column].
                    getterCharacter() != '.' &&
                    gameCells[row * getterHeight() + column].
                    getterCharacter() != sabit &&
                    gameCells[(row - 1) * getterHeight()+(column + 1)].
                    getterCharacter() != '.') {
                counter++;
                if (gameCells[(row - 1) * getterHeight()+(column + 1)].
                        getterCharacter() == sabit)
                    validity++;
                row--;
                column++;
            }
            if (validity == 0)
                counter = 0;
            while (temp < counter) {
                row++;
                column--;
                gameCells[row * getterHeight() + column].setter(row, column, sabit);
                temp++;
            }
        }
        row = possibilities[0][1]; //right_down
        column = possibilities[0][2];
        temp = 0;
        counter = 0;
        validity = 0;
        if (row < getterHeight() - 2 && column < getterWidth() - 2) {
            row++;
            column++;
            while (row < 0 && getterHeight() - 1 && column < width - 1 &&
                    gameCells[row * getterHeight() + column].
                    getterCharacter() != '.' &&
                    gameCells[row * getterHeight() + column].
                    getterCharacter() != sabit &&
                    gameCells[(row + 1) * getterHeight()+(column + 1)].
                    getterCharacter() != '.') {
                counter++;
                if (gameCells[(row + 1) * getterHeight()+(column + 1)].
                        getterCharacter() == sabit)
                    validity++;
                row++;
                column++;
            }
            if (validity == 0)
                counter = 0;
            while (temp < counter) {
                row--;
                column--;
                gameCells[row * getterHeight() + column].setter(row, column, sabit);
                temp++;
            }
        }
        row = possibilities[0][1]; //left_up
        column = possibilities[0][2];
        temp = 0;
        counter = 0;
        validity = 0;
        if (row > 1 && column > 1) {
            row--;
            column--;
            while (row > 0 && column > 0 && gameCells[row * getterHeight() + column].
                    getterCharacter() != '.' &&
                    gameCells[row * getterHeight() + column].
                    getterCharacter() != sabit &&
                    gameCells[(row - 1) * getterHeight()+(column - 1)].
                    getterCharacter() != '.') {
                counter++;
                if (gameCells[(row - 1) * getterHeight()+(column - 1)].
                        getterCharacter() == sabit)
                    validity++;
                row--;
                column--;
            }
            if (validity == 0)
                counter = 0;
            while (temp < counter) {
                row++;
                column++;
                gameCells[row * getterHeight() + column].setter(row, column, sabit);
                temp++;
            }
        }
        row = possibilities[0][1]; //left_down
        column = possibilities[0][2];
        temp = 0;
        counter = 0;
        validity = 0;
        if (row < getterHeight() - 2 && column > 1) {
            row++;
            column--;
            while (row < getterHeight() - 1 && column > 0 &&
                    gameCells[row * getterHeight() + column].
                    getterCharacter() != '.' &&
                    gameCells[row * getterHeight() + column].
                    getterCharacter() != sabit &&
                    gameCells[(row + 1) * getterHeight()+(column - 1)].
                    getterCharacter() != '.') {
                counter++;
                if (gameCells[(row + 1) * getterHeight()+(column - 1)].
                        getterCharacter() == sabit)
                    validity++;
                row++;
                column--;
            }
            if (validity == 0)
                counter = 0;
            while (temp < counter) {
                row--;
                column++;
                gameCells[row * getterHeight() + column].setter(row, column, sabit);
                temp++;
            }
        }
    }//oyunun 1 obje icin bitip bitmedigini kontrol eder

    bool Reversi::endGame(const bool controlUser, const bool controlPc) {
        if (controlUser == false && controlPc == false)
            return true;
        else
            return false;
    }//static fonksiyomdur static private degiskeni return
    //eder mainde kullanmak icin

    int Reversi::livingObjectNumber() {
        return livingObjects;
    }//statictir.livingcelleri guncel tutmak icin main de while dongusu her
    //dondugunde sifirlansin diye

    void Reversi::decrementLivingObjects() {
        livingObjects--;
    }

    bool Reversi::isBetter(const Reversi & otherObject) {
        int userLivingCellNumber = 0, pcLivingCellNumber = 0, count1 = 0, count2 = 0;

        //parametre olarak alinmayan objenin user ve pc nin
        //livingcelleri hesaplanşr
        for (int i = 0; i < getterHeight(); i++) {
            for (int j = 0; j < getterWidth(); j++) {
                if (gameCells[i * getterHeight() + j].getterCharacter() == 'X')
                    pcLivingCellNumber++;
                if (gameCells[i * getterHeight() + j].getterCharacter() == 'O')
                    userLivingCellNumber++;
            }
        }
        count1 = userLivingCellNumber - pcLivingCellNumber; //farki bulunur

        userLivingCellNumber = 0; //sifirlanir livingcell countlari
        pcLivingCellNumber = 0;
        //parametre olarak alinan objenin user ve pc nin
        //livingcelleri hesaplanir
        for (int i = 0; i < otherObject.getterHeight(); i++) {
            for (int j = 0; j < otherObject.getterWidth(); j++) {
                if (gameCells[i * getterHeight() + j].getterCharacter() == 'X')
                    pcLivingCellNumber++;
                if (gameCells[i * getterHeight() + j].getterCharacter() == 'O')
                    userLivingCellNumber++;
            }
        }
        count2 = userLivingCellNumber - pcLivingCellNumber; //farki bulunur
        //parametre olarak alinmayan objedeki user daha basarali ise true
        //dondurur
        if (count1 > count2)
            return true;
        else//degilse false dondurur.bunu oyunlari karsilastirmada kullaniyorum
            return false;
    }//ihtimaller vectorunu sifirlamak icin.yapmazsam tum boyunca tum
    //ihtimalleri biriktiririm ve yanlis olur oyun hic bitmez segmentation fault
    //vermezse tabii

    void Reversi::clearVector() {
        possibilities.clear();
    }//tabloyu bastirmak icin tablo kaymasi icin bu kadar uzun surdu

    void Reversi::display() {
        int i, j, pcNumber = 0, userNumber = 0;

        if (getterWidth() > 9) {
            cout << " ";
            for (i = 1; i <= getterWidth(); i++) {
                if (i > 8)
                    cout << i << " ";
                else
                    cout << i << " ";
            }
            cout << endl;
        } else {
            cout << " ";
            for (i = 1; i <= getterHeight(); i++) {
                if (getterHeight() > 9) {
                    if (i < 9)
                        cout << " " << i + 1 << " ";
                    else
                        cout << i + 1 << " ";
                } else
                    cout << i + 1 << " ";
                cout << " ";
            }
            for (j = 0; j < getterWidth(); j++) {
                if (gameCells[i * getterHeight() + j].getterCharacter() == 'X')
                    pcNumber++;
                if (gameCells[i * getterHeight() + j].getterCharacter() == 'O')
                    userNumber++;
                if (getterWidth() > 9) {
                    cout << gameCells[i * getterHeight() + j].
                            getterCharacter() << " ";
                } else
                    cout << gameCells[i * getterHeight() + j].getterCharacter() << " ";
            }
            cout << endl;
        }//oyucularin guncel livingcell sayilari
        cout << "PC : " << pcNumber << "USER: " << userNumber << endl;
    }

    ostream & operator<<(ostream&output, const Reversi &veri) {
        int i, j, pcNumber = 0, userNumber = 0;

        if (veri.getterWidth() > 9) {
            output << " ";
            for (i = 1; i <= veri.getterWidth(); i++) {
                if (i > 8)
                    output << i << " ";
                else
                    output << i << " ";
            }
            output << endl;
        } else {
            output << " ";
            for (i = 1; i <= veri.getterWidth(); i++)
                output << i << " ";
            output << endl;
        }
        for (i = 0; i < veri.getterHeight(); i++) {
            if (veri.getterHeight() > 9) {
                if (i < 9)
                    output << " " << i + 1 << " ";
                else
                    output << i + 1 << " ";
            } else
                output << i + 1 << " ";
            output << " ";
            for (j = 0; j < veri.getterWidth(); j++) {
                if (veri.gameCells[i * veri.getterHeight() + j].
                        getterCharacter() == 'X')
                    pcNumber++;
                if (veri.gameCells[i * veri.getterHeight() + j].
                        getterCharacter() == 'O')
                    userNumber++;
                if (veri.getterWidth() > 9) {
                    output << veri.gameCells[i * veri.getterHeight() + j].
                            getterCharacter() << " ";
                }
            }
            output << endl;
        }//oyuncularin guncel livingcell sayilari
        output << "PC: " << pcNumber << " USER: " << userNumber << endl;

        return output;
    }
}
namespace tester {

    void testGame() {
        const char pc = 'X';
        const char user = 'O'; //oyuncularin bitip bitmedigini kontrol etmek icin
        bool isReal = true, controller1 = true, controller2 = true, controller3 = true,
                controller4 = true, controller5 = true;
        int count = 0, cellLivingObject = 0;
        const char *str1 = "OYUN1.txt", *str2 = "OYUN2.txt", *str3 = "OYUN3.txt",
                *str4 = "OYUN4.txt", *str5 = "OYUN5.txt"; //file names
        suleymanReversi::Reversi game1, game2, game3, game4, game5, junk; //objeler

        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        cout << "!!!!!!!Oyun 5 farkli obje icin sirayla 1 kez calisiyor boyutu!!!!!!!" << endl;
        cout << "!!!!!!!!4 gibi kucuk degerler girmenizi tavsiye ederim.Oyuna!!!!!!!!" << endl;
        cout << "!!!!!!!!!!!!!!!!!!!Benim dosyalarimdan baslanabiliyor.!!!!!!!!!!!!!!" << endl;
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

        //bir oyun kaydedilirse veya biterse false dondurur ve controller bunu
        //ayarlar devam ettirmez biten oyunu.dongu her dondugunde karsilastirma yapar
        while (controller1 == true | | controller2 == true | | controller3 == true | |
                controller4 == true | | controller5 == true) {
            //living cell leri dondurur
            cellLivingObject = suleymanReversi::Reversi::livingObjectNumber();
            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
            //-2 cıkartirim cunku mainde rev burda junk diye obje var oynamadigim
            cout << "Living object number:" << cellLivingObject - 2 << endl; //ekrana basar

            if (count == 0) {//start fonksiyonu bir kez calissin diye
                game1.start(pc, user, str1);
            }
            if (controller1 == true) {//oyun kaydedilirse veya biterse false dondurur
                controller1 = junk.playGame(pc, user, str1, game1);
                if (controller1 == false)
                    suleymanReversi::Reversi::decrementLivingObjects();
            }
            if (count == 0) {
                game2.start(pc, user, str2);
            }
            if (controller2 == true) {
                controller2 = junk.playGame(pc, user, str2, game2);
                if (controller2 == false)
                    suleymanReversi::Reversi::decrementLivingObjects();
            }
            if (count == 0) {
                game3.start(pc, user, str3);
            }
            if (controller3 == true) {
                controller3 = junk.playGame(pc, user, str3, game3);
                if (controller3 == false)
                    suleymanReversi::Reversi::decrementLivingObjects();
            }
            if (count == 0) {
                game4.start(pc, user, str4);
            }
            if (controller4 == true) {
                controller4 = junk.playGame(pc, user, str4, game4);
                if (controller4 == false)
                    suleymanReversi::Reversi::decrementLivingObjects();
            }
            if (count == 0) {
                game5.start(pc, user, str5);
            }
            if (controller5 == true) {
                controller5 = junk.playGame(pc, user, str5, game5);
                if (controller5 == false)
                    suleymanReversi::Reversi::decrementLivingObjects();
            }
            count++; //start fonk. her obje icin 1 kez calissin diye

            //en basarili user i bulmak icin
            if (game1.isBetter(game2) && game1.isBetter(game3) &&
                    game1.isBetter(game4) && game1.isBetter(game5))
                cout << "OYUN1 deki oyuncu en basarili " << endl;
            else if (game2.isBetter(game1) && game2.isBetter(game3) &&
                    game2.isBetter(game4) && game2.isBetter(game5))
                cout << "OYUN2 deki oyuncu en basarili " << endl;
            else if (game3.isBetter(game1) && game3.isBetter(game2) &&
                    game3.isBetter(game4) && game3.isBetter(game5))
                cout << "OYUN3 deki oyuncu en basarili " << endl;
            else if (game4.isBetter(game1) && game4.isBetter(game2) &&
                    game4.isBetter(game3) && game4.isBetter(game5))
                cout << "OYUN4 deki oyuncu en basarili " << endl;
            else if (game5.isBetter(game1) && game5.isBetter(game2) &&
                    game5.isBetter(game3) && game5.isBetter(game4))
                cout << "OYUN5 deki oyuncu en basarili " << endl;
            else
                cout << " En basarili oyuncu yok " << endl;
            cout << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< " << endl;
        } //while dongusu bittiginde oyun biter
        //living objeleri dondurur
        cellLivingObject = suleymanReversi::Reversi::livingObjectNumber();
        cout << " >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
        cout << "Living cell number: " << cellLivingObject << endl; //ekrana basar
        cout << "!!!!!!!!!!!!!!!!!!!!! END OF GAME!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    }

    void testCallByValue(suleymanReversi::Reversi object) {
        suleymanReversi::Reversi temp;
        const char pcSign = 'X', userSign = 'O';
        const char *strTest1 = "TEST1.txt";
        object.start(pcSign, userSign, strTest1);
        temp.playGame(pcSign, userSign, strTest1);
        temp.playGame(pcSign, userSign, strTest1, object);
    }

    void testCallByValue(suleymanReversi::Reversi object) {
        suleymanReversi::Reversi temp;
        const char pcSign = 'X', userSign = 'O';
        const char *strTest2 = "TEST2.txt";
        object.start(pcSign, userSign, strTest2);
        temp.playGame(pcSign, userSign, strTest2);
        temp.playGame(pcSign, userSign, strTest2, object);
    }
}
//							End of source.cpp