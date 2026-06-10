#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;


// метод шифрования символов 
const unsigned char S_box[256] = {
    0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
    0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
    0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
    0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
    0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
    0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
    0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
    0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
    0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
    0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
    0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
    0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
    0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
    0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
    0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
    0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16
};

// метож дешифрования символов
const unsigned char Inv_S_box[256] = {
    0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb,
    0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb,
    0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e,
    0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25,
    0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92,
    0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84,
    0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06,
    0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b,
    0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73,
    0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e,
    0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b,
    0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4,
    0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f,
    0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef,
    0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61,
    0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d
};

// вывод значения в 16-ричной системе
void printHex(const unsigned char* data, int len) {
    for (int i = 0; i < len; i++) {
        cout << hex << setw(2) << setfill('0') << (int)data[i] << " "; // hex - работа с 16-ричной системой, setw(2) - ширина вывода 2, setfill('0') - заполнять пустые значения 0
    }
    cout << dec << endl; // переключение обратно в 10-ричную систему счисления
}

// вывод матрицы 4х4 (в 16-ричной системе) в каждой ячейки содержиться байт
void printMatrix(const unsigned char matrix[4][4], const string& name) {
    cout << name << ":" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << hex << setw(2) << setfill('0') << (int)matrix[i][j] << " ";  // hex - работа с 16-ричной системой, setw(2) - ширина вывода 2, setfill('0') - заполнять пустые значения 0
        }
        cout << endl;
    }
    cout << dec;  // переключение обратно в 10-ричную систему счисления
}

// вывод ключей раунда для всей матрицы
void printRoundKeys(unsigned char round_keys[11][4][4]) {
    cout << "	СГЕНЕРИРОВАННЫЕ КЛЮЧИ РАУНДОВ" << endl;
    for (int round = 0; round <= 10; round++) {
        cout << "Раундовый ключ " << round << ": ";
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cout << hex << setw(2) << setfill('0') << (int)round_keys[round][i][j] ; // hex - работа с 16-ричной системой, setw(2) - ширина вывода 2, setfill('0') - заполнять пустые значения 0
            }
        }
        cout << dec << endl;
    }
}

// Сгенерировать рандомный ключ (мастер ключ, только 1-ый ключ)
void generateRandomKey(unsigned char* key) {
    srand(time(NULL));
    for (int i = 0; i < 16; i++) {
        key[i] = rand() % 256;
    }
}

// Работа умножением Гуловых полей (лучше используй дипсик, Я хз как объяснить) 
unsigned char GF_mult(unsigned char a, unsigned char b) { 
    unsigned char result = 0;
    while (b > 0) {
        if (b % 2 == 1)
            result = result ^ a;
        if (a >= 128)
            a = (a << 1) ^ 27;
        else
            a = a << 1;

        b = b / 2;
    }
    return result;
}

// Шифруем нашу матрицу 4х4 через S_box
void SubBytes(unsigned char matrix[4][4]) { 
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            matrix[i][j] = S_box[matrix[i][j]];
}

// Дешифруем нашу матрицу 4х4 через S_box
void InvSubBytes(unsigned char matrix[4][4]) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            matrix[i][j] = Inv_S_box[matrix[i][j]];
}

//  меняем строку в зависимости от номера строку (сдвиг идет вправо)
void ShiftRows(unsigned char matrix[4][4]) {
    unsigned char temp; //  просто переменная что-бы хранить данные (метод пузырька)

    // 0-ая строчка смещаеться на 0 элементов (не изменяеться)

    // 1-ая строчка смещаеться на 1 элемент (0-ой становиться 1-ым, 1-ый становииться 2-ым, последний становиться первым)
    temp = matrix[1][0];
    matrix[1][0] = matrix[1][1];
    matrix[1][1] = matrix[1][2];
    matrix[1][2] = matrix[1][3];
    matrix[1][3] = temp;

    // 2-ая строчка смещаеться на 2 элемент (0-ой становиться 2-ым, 1-ый становииться 3-им)
    temp = matrix[2][0];
    matrix[2][0] = matrix[2][2];
    matrix[2][2] = temp;
    temp = matrix[2][1];
    matrix[2][1] = matrix[2][3];
    matrix[2][3] = temp;

    // 3-я строчка смещаеться на 3 элемент (0-ой становиться 3-ым, 1-ый становииться 0-ым)
    temp = matrix[3][3];
    matrix[3][3] = matrix[3][2];
    matrix[3][2] = matrix[3][1];
    matrix[3][1] = matrix[3][0];
    matrix[3][0] = temp;
}

//  меняем строку в зависимости от номера строку (только в обратном(сдвиг идет влево) пордке для дешифровки)
void InvShiftRows(unsigned char matrix[4][4]) {
    unsigned char temp;
    temp = matrix[1][3];
    matrix[1][3] = matrix[1][2];
    matrix[1][2] = matrix[1][1];
    matrix[1][1] = matrix[1][0];
    matrix[1][0] = temp;

    temp = matrix[2][0];
    matrix[2][0] = matrix[2][2];
    matrix[2][2] = temp;
    temp = matrix[2][1];
    matrix[2][1] = matrix[2][3];
    matrix[2][3] = temp;

    temp = matrix[3][0];
    matrix[3][0] = matrix[3][1];
    matrix[3][1] = matrix[3][2];
    matrix[3][2] = matrix[3][3];
    matrix[3][3] = temp;
}

//  тут тоже сложно объяснить так как работа с Гуловыми полями (дипсик)
void MixColumns(unsigned char matrix[4][4]) {
    unsigned char s[4];
    for (int c = 0; c < 4; c++) {

        s[0] = matrix[0][c];
        s[1] = matrix[1][c];
        s[2] = matrix[2][c];
        s[3] = matrix[3][c];

        matrix[0][c] = GF_mult(0x02, s[0]) ^ GF_mult(0x03, s[1]) ^ s[2] ^ s[3];
        matrix[1][c] = s[0] ^ GF_mult(0x02, s[1]) ^ GF_mult(0x03, s[2]) ^ s[3];
        matrix[2][c] = s[0] ^ s[1] ^ GF_mult(0x02, s[2]) ^ GF_mult(0x03, s[3]);
        matrix[3][c] = GF_mult(0x03, s[0]) ^ s[1] ^ s[2] ^ GF_mult(0x02, s[3]);
    }
}

//  тут тоже сложно объяснить так как работа с Гуловыми полями (дипсик)
void InvMixColumns(unsigned char matrix[4][4]) {
    unsigned char s[4];
    for (int c = 0; c < 4; c++) {
        s[0] = matrix[0][c];
        s[1] = matrix[1][c];
        s[2] = matrix[2][c];
        s[3] = matrix[3][c];

        matrix[0][c] = GF_mult(0x0e, s[0]) ^ GF_mult(0x0b, s[1]) ^ GF_mult(0x0d, s[2]) ^ GF_mult(0x09, s[3]);
        matrix[1][c] = GF_mult(0x09, s[0]) ^ GF_mult(0x0e, s[1]) ^ GF_mult(0x0b, s[2]) ^ GF_mult(0x0d, s[3]);
        matrix[2][c] = GF_mult(0x0d, s[0]) ^ GF_mult(0x09, s[1]) ^ GF_mult(0x0e, s[2]) ^ GF_mult(0x0b, s[3]);
        matrix[3][c] = GF_mult(0x0b, s[0]) ^ GF_mult(0x0d, s[1]) ^ GF_mult(0x09, s[2]) ^ GF_mult(0x0e, s[3]);
    }
}

//  поэлементно Xor'им  (операция исключающего или) нашу матрицу по ключу
void AddRoundKey(unsigned char matrix[4][4], unsigned char key[4][4]) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            matrix[i][j] ^= key[i][j];
}

//  просто константы чтобы гарантировать нелинейность шифрования, можно сказать что это по ТЗ
const unsigned char Rcon[10] = { 0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36 }; 

//  генерация ключей по мастер ключу (который мы делали через рандом)
void ExpandKey(unsigned char* master_key, unsigned char round_keys[11][4][4]) {

    for (int i = 0; i < 4; i++) //  0-ой раунд для шифрования равен мастер ключу
        for (int j = 0; j < 4; j++)
            round_keys[0][i][j] = master_key[i * 4 + j];

    for (int round = 1; round <= 10; round++) { //  тут создаються ключи для следующих раундов чтобы их создать нужен ключ предыдущего раунда
        unsigned char temp[4];
        for (int i = 0; i < 4; i++)
            temp[i] = round_keys[round - 1][i][3];

        unsigned char t = temp[0];
        temp[0] = temp[1];
        temp[1] = temp[2];
        temp[2] = temp[3];
        temp[3] = t;
        for (int i = 0; i < 4; i++)
            temp[i] = S_box[temp[i]];

        temp[0] ^= Rcon[round - 1];

        for (int i = 0; i < 4; i++)
            round_keys[round][i][0] = round_keys[round - 1][i][0] ^ temp[i];

        for (int col = 1; col < 4; col++) {
            for (int i = 0; i < 4; i++) {
                round_keys[round][i][col] = round_keys[round][i][col - 1] ^ round_keys[round - 1][i][col];
            }
        }
    }
}


//  само шифрование только 1-го блока, с использованием всех нужных операций и промежуточных выводов (просто можно сказать такая структура шифрования)
void EncryptBlock(unsigned char matrix[4][4], unsigned char round_keys[11][4][4], bool printState = false) {
    static int blockNum = 0;

    AddRoundKey(matrix, round_keys[0]);
    if (printState)
        printMatrix(matrix, "  После AddRoundKey 0");

    for (int round = 1; round <= 9; round++) {
        SubBytes(matrix);
        if (printState) printMatrix(matrix, "  После SubBytes " + to_string(round));

        ShiftRows(matrix);
        if (printState) printMatrix(matrix, "  После ShiftRows " + to_string(round));

        MixColumns(matrix);
        if (printState) printMatrix(matrix, "  После MixColumns " + to_string(round));

        AddRoundKey(matrix, round_keys[round]);
        if (printState) printMatrix(matrix, "  После AddRoundKey " + to_string(round));
    }

    SubBytes(matrix);
    if (printState) printMatrix(matrix, "  После SubBytes (финал)");

    ShiftRows(matrix);
    if (printState) printMatrix(matrix, "  После ShiftRows (финал)");

    AddRoundKey(matrix, round_keys[10]);
    if (printState) printMatrix(matrix, "  После AddRoundKey (финал)");
}

//  Дешифровка только 1-го блока, с использованием всех нужных операций и промежуточных выводов (просто можно сказать такая структура дешифровки)
void DecryptBlock(unsigned char matrix[4][4], unsigned char round_keys[11][4][4]) {
    AddRoundKey(matrix, round_keys[10]);

    for (int round = 9; round >= 1; round--) {
        InvShiftRows(matrix);
        InvSubBytes(matrix);
        AddRoundKey(matrix, round_keys[round]);
        InvMixColumns(matrix);
    }

    InvShiftRows(matrix);
    InvSubBytes(matrix);
    AddRoundKey(matrix, round_keys[0]);
}


// Функция которая осуществляет шифрование всего текста
void EncryptCFB(const vector<unsigned char>& textOrig,
    vector<unsigned char>& textCript,
    unsigned char* key,
    unsigned char* iv) {

    unsigned char round_keys[11][4][4];
    ExpandKey(key, round_keys);

    printRoundKeys(round_keys);

    cout << "	ВЕКТОР ИНИЦИАЛИЗАЦИИ (IV) " << endl;
    printHex(iv, 16);

    textCript.clear();

    for (int i = 0; i < 16; i++)
        textCript.push_back(iv[i]);

    unsigned char feedback[16];
    for (int i = 0; i < 16; i++)
        feedback[i] = iv[i];

    int blockCounter = 0;
    for (size_t block = 0; block < textOrig.size(); block += 16) {
        unsigned char matrix[4][4];

        cout << "	ОБРАБОТКА БЛОКА " << blockCounter++ << endl;
        cout << "Feedback до шифрования: ";
        printHex(feedback, 16);

        for (int i = 0; i < 16; i++)
            matrix[i / 4][i % 4] = feedback[i];

        cout << "Matrix (State) до шифрования:" << endl;
        printMatrix(matrix, "  State");

        EncryptBlock(matrix, round_keys, true);

        cout << "Matrix (State) после шифрования:" << endl;
        printMatrix(matrix, "  State");

        for (int i = 0; i < 16 && block + i < textOrig.size(); i++) {
            unsigned char encrypted_byte = matrix[i / 4][i % 4];
            textCript.push_back(encrypted_byte ^ textOrig[block + i]);
            feedback[i] = textCript.back();
        }

        cout << "Получен шифротекст блока: ";
        for (size_t i = textCript.size() - (block + 16 < textOrig.size() ? 16 : textOrig.size() % 16);
            i < textCript.size(); i++) {
            cout << hex << setw(2) << setfill('0') << (int)textCript[i];
        }
        cout << dec << endl;
    }
}
// Функция которая осуществляет дешифровку всего текста
void DecryptCFB(const vector<unsigned char>& textCript,
    vector<unsigned char>& textOrig,
    unsigned char* key) {

    textOrig.clear();

    if (textCript.size() < 16)
        return;

    unsigned char round_keys[11][4][4];
    ExpandKey(key, round_keys);

    unsigned char iv[16];
    for (int i = 0; i < 16; i++)
        iv[i] = textCript[i];

    unsigned char feedback[16];
    for (int i = 0; i < 16; i++)
        feedback[i] = iv[i];

    for (size_t block = 16; block < textCript.size(); block += 16) {
        unsigned char matrix[4][4];

        for (int i = 0; i < 16; i++)
            matrix[i / 4][i % 4] = feedback[i];

        EncryptBlock(matrix, round_keys, false);

        for (int i = 0; i < 16 && block + i < textCript.size(); i++) {
            textOrig.push_back(matrix[i / 4][i % 4] ^ textCript[block + i]);
            feedback[i] = textCript[block + i];
        }
    }
}

// преобразует строку в байт
void StringToBytes(const string& str, vector<unsigned char>& bytes) {
    bytes.clear();
    for (size_t i = 0; i < str.length(); i++)
        bytes.push_back((unsigned char)str[i]);
}

// преобразует байт в строку 
void BytesToString(const vector<unsigned char>& bytes, string& str) {
    str.clear();
    for (size_t i = 0; i < bytes.size(); i++)
        str += (char)bytes[i];
}

// генерирует случайные значения IV (Idenfication vector)
void GenerateIV(unsigned char* iv) {
    srand(time(NULL));
    for (int i = 0; i < 16; i++)
        iv[i] = rand() % 256;
}

// получение текста, генерация ключей и iv, шифрование и дешифрование
int main() {
    setlocale(LC_ALL, "Russian");

    cout << "AES-128 CFB ШИФРОВАНИЕ" << endl;


    unsigned char key[16];
    generateRandomKey(key);

    cout << "Сгенерированный случайный ключ: ";
    printHex(key, 16);

    cout << "Введите текст для шифрования: ";
    string original;
    getline(cin, original);

    vector<unsigned char> plain;
    StringToBytes(original, plain);

    unsigned char iv[16];
    GenerateIV(iv);

    cout << "Сгенерированный IV: ";
    printHex(iv, 16);

    vector<unsigned char> textCript;
    EncryptCFB(plain, textCript, key, iv);

    cout << "ПОЛНЫЙ ШИФРОТЕКСТ" << endl;
    cout << "Размер: " << textCript.size() << " байт" << endl;
    cout << "Данные: ";
    for (size_t i = 0; i < textCript.size(); i++) {
        cout << hex << setw(2) << setfill('0') << (int)textCript[i];
        if ((i + 1) % 32 == 0 && i + 1 < textCript.size()) cout << endl << "        ";
    }
    cout << dec << endl;

    vector<unsigned char> decrypted;
    DecryptCFB(textCript, decrypted, key);

    string result;
    BytesToString(decrypted, result);

    cout << "РЕЗУЛЬТАТ" << endl;
    cout << "Расшифрованный текст: " << result << endl;

    return 0;
}
