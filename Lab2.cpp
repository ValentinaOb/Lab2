// Lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#if !defined(_MSC_VER)
#define VS_CODE
#endif
#include <iostream>
#include <fstream>
using namespace std;
#include <clocale>
#include <string.h>
#if !defined(VS_CODE)
#include <Windows.h>
#endif



void A();
void B();
void C();
void D();


int main()
{
    int n;
    cout << "N: ";
e: cin >> n;

    switch (n) {
    case 1: A(); break; // 1
    case 2: B(); break; // 2
    case 3: C(); break; // 3
    case 4: D(); break; // 4
    default: cout << "Error\n"; goto e;
    }

    return 0;
}


void A() {

    int x, y, a, b, c, d;
    int x1, x2, x3;
    int y1, y2, y3;

    cout << "a, b, c, d: ";
    cin >> a >> b >> c >> d;

    x = ((((a << 7) - a) + (c << 5)) >> 12) - ((d << 10) + (d << 7) + (d << 5) + (d << 4)) + ((b << 7) + (b << 1) + (b << 0));
    y = ((127 * a + 32 * c) / 4096) - d * 1200 + b * 131;

    x1 = ((((a << 7) - a) + (c << 5)) >> 12);
    y1 = (127 * a + 32 * c) / 4096;
    cout << "1: " << x1 << " " << y1 << endl;

    x2 = x1 - ((d << 10) + (d << 7) + (d << 5) + (d << 4));
    y2 = y1 - d * 1200;
    cout << "2: " << x2 << " " << y2 << endl;

    x3 = x2 + ((b << 7) + (b << 1) + (b << 0));
    y3 = y2 + b * 131;
    cout << "3: " << x3 << " " << y3 << endl;

    cout << "\nX: " << x << endl;
    cout << "Y: " << y << endl;

    return;
}


void B() {

    /*
* Задано 8 рядків тексту. У рядку до 8 символів. Доповнити пробілами рядки до 8 символів.
Шифрувати тексти таким чином, щоб кожний символ тексту записувався у два байти. Два байти
мають таку структуру:
у бітах 0-2 знаходиться номер рядка символу (3 біти),
у бітах 3-6 молодша частина ASCII - коду символу (4 біти),
7 біт – біт парності перших двох полів (1 біт)
у бітах 8-11 старша частина ASCII - коду символу (4 біти),
у бітах 12-14 позиція символу в рядку (3 біти),
15 біт - біт парності попередніх двох полів (1 біт).
    */

    setlocale(LC_ALL, "ukr");

    char s[8][9], ch;
    char so[8][9];
    unsigned short sh_dat[64], sd2[64], r, w;
    unsigned short i, p, j, l, b, k, t;
    char st[9];
    unsigned char c;

    ifstream ifs("in.txt");
    if (!ifs) {
        cout << "File in.txt not open" << endl; return;
    }

    ofstream ofs("out.txt");
    ofstream ofsb("outb.bin", ios::out | ios::binary);


    cout << "A: ";

    for (i = 0; i < 8; i++)
    {
        ifs.get(s[i], 8, '\0'); ifs.get(ch);  // 8  - 9
        int n = strlen(s[i]);
        for (int i1 = n; i1 < 8; i1++) s[i][i1] = ' ';
        s[i][8] = '\0';
        cout << s[i] << "\n";
    }


    l = 0;

    cout << endl;


    /////////////////


    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {

            //номер рядка (0-2)
            r = i;

            // (3-6)   
            c = s[i][j];
            t = c & 0b00001111;  // c & 0x0f;
            r |= t << 3;


            //біт парності 1-их 2-ох полів (7)
            b = 0; t = 1;
            for (k = 0; k < 7; k++)
            {
                if (r & t) {
                    if (b == 0) b = 1; else b = 0;
                }
                t <<= 1;
            }
            w = 1 << 7;

            if (b)  r |= w;   // 0000 1000 1000

            //(8-11)

            w = 0;
            w = s[i][j];
            t = w & 0b00000000011110000;    // c & 0f0
            r |= t << 4;

            //позиція символу у рядку (12-14)
            w = 0;
            w = j << 12;
            r |= w;

            //біт парності 3-их 4-ох полів (7)
            b = 0; t = 0b0000000100000000;   // 8 to 14
            for (k = 1; k < 7; k++)
            {
                if (r & t) {
                    if (b == 0) b = 1; else b = 0;
                }
                t <<= 1;
            }
            if (b) w = 1 << 15;

            r |= w;
            sh_dat[l] = r;
            l++;

            ofs << hex << r << ' ';
            cout << hex << r << endl;
        }
    }

    ofsb.write((char*)sh_dat, 64 * sizeof(unsigned short));
    ofsb.close();
    ifs.close();



    cout << endl;

    ifs.open("outb.bin", ios::in | ios::binary);
    ifs.read((char*)sd2, 64 * sizeof(unsigned short));

    short indi, indj;
    for (i = 0; i < 64; i++)
    {
        r = sd2[i];
        indj = r & 0b0111000000000000;
        indj >>= 12;
        indi = r & 0b0000000000000111;
        w = r & 0b0000111100000000;
        w >>= 4;
        p = r & 0b0000000001111000;
        p >>= 3;
        p |= w;
        ch = p;
        so[indi][indj] = ch;
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++)
            cout << so[i][j];
        cout << endl;

    }


    return;
}


void MyEncryption(char s[8][9], unsigned short sh_dat[64]) {

    char ch;
    unsigned char c;
    unsigned short w, b, p, k;

    unsigned short r, t, i, l = 0;
    short j;

    ifstream ifs("in.txt");
    if (!ifs) {
        cout << "File in.txt not open" << endl; return;
    }

    cout << "A: ";

    for (i = 0; i < 8; i++)
    {
        ifs.get(s[i], 8, '\0'); ifs.get(ch);  // 8  - 9
        int n = strlen(s[i]);
        for (int i1 = n; i1 < 8; i1++) s[i][i1] = ' ';
        s[i][8] = '\0';
        cout << s[i] << "\n";
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {

            //номер рядка (0-2)
            r = i;

            // (3-6)   
            c = s[i][j];
            t = c & 0b00001111;  // c & 0x0f;
            r |= t << 3;


            //біт парності 1-их 2-ох полів (7)
            b = 0; t = 1;
            for (k = 0; k < 7; k++)
            {
                if (r & t) {
                    if (b == 0) b = 1; else b = 0;
                }
                t <<= 1;
            }
            w = 1 << 7;

            if (b)  r |= w;   // 0000 1000 1000

            //(8-11)

            w = 0;
            w = s[i][j];
            t = w & 0b00000000011110000;    // c & 0f0
            r |= t << 4;

            //позиція символу у рядку (12-14)
            w = 0;   // !!!
            w = j << 12;
            r |= w;

            //біт парності 3-их 4-ох полів (7)
            b = 0; t = 0b0000000100000000;   // 8 to 14
            for (k = 1; k < 7; k++)
            {
                if (r & t) {
                    if (b == 0) b = 1; else b = 0;
                }
                t <<= 1;
            }
            if (b) w = 1 << 15;

            r |= w;
            sh_dat[l] = r;
            l++;

            cout << hex << r << endl;
        }
    }


}

struct T {
    unsigned short a : 3; // row number
    unsigned short b : 4; // mchkb	
    unsigned short c : 1; // bitp		
    unsigned short d : 4; // schkb
    unsigned short e : 3; // posrow	
    unsigned short f : 1; // bitp		
};

unsigned char pbit(unsigned char r) {
    unsigned char b, t;
    short j;
    b = 0; t = 1;
    for (j = 0; j < 7; j++)
    {
        if (r & t) {
            if (b == 0) b = 1; else b = 0;
        }
        t <<= 1;
    }
    return b;
}

void MyEncryptionS(char InS[64]) {
    T sh_dat[64];
    unsigned char c;
    unsigned short r, t, i;
    short j;
    for (i = 0; i < 64; i++)
    {
        c = InS[i];
        sh_dat[i].d = c >> 3;
        sh_dat[i].b = c & 0b0001111000000000;
        sh_dat[i].e = c << 12;
        sh_dat[i].a = i;

        r = pbit(c);
        t = pbit(static_cast<unsigned char>(i));
        sh_dat[i].c = r ^ t;
        sh_dat[i].f = r ^ t;

    }
}

int MyDecryption(char OutS[64], unsigned short InCoding[64]) {
    unsigned char c;
    unsigned short r, t, i, b, p, w;
    short j;
    for (i = 0; i < 64; i++)
    {
        // Перевірка парності
        r = InCoding[i];
        t = r & 0b1111111101111111;      //  		1111 1111 0111 1111
        p = r & 0b0000000010000000;      //			0000 0000 1000 0000
        w = 1;
        b = 0;
        for (j = 0; j < 16; j++)         // обчислення біта парності
        {
            if (t & w) {
                if (b == 0) b = 1; else b = 0;
            }
            w <<= 1;
        }

        r = i;

        p >>= 15;
        if (p != b)  return -i;
        t = r & 0b0000000001111000;
        t >>= 3;
        w = r & 0b0000111100000000;
        w <<= 4;
        t |= w;
        p = r & 0b0111000000000000;
        p >>= 12;
        OutS[p] = (unsigned char)t;
    }

    return 1;
}

void C() {
    cout << "C: \n";
    char s[8][9];
    unsigned short sh_dat[64];
    unsigned char r = 0;
    char so[8][9];
    char InS[64], OutS[64];
    unsigned short InCoding[64];

    MyEncryption(s, sh_dat);
    pbit(r);
    MyEncryptionS(InS);
    MyDecryption(OutS, InCoding);
}


void D() {
    setlocale(LC_ALL, "ukr");

    char a[30];
    int i, n;

    cout << "A: ";
    cin >> a;

    for (i = 0; i < strlen(a) - 1; i++) {
        a[i] = a[i] ^ (255 - (i % 256));
    }

    cout << "Result: ";
    for (i = 0; i < strlen(a); i++) {
        cout << a[i];
    }

    return;
}




// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
