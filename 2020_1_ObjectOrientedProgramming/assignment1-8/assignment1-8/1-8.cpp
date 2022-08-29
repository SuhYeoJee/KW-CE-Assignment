#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//�������Լ�
void print_str(int* ptr, int length, int key) {
    std::cout << "key(" << key << "): ";
    for (int i = length; i > 0; i--) {
        int a = ptr[length - i] + key;
        while (a > 128) a -= 128;
        std::cout << (unsigned char)a << ' ';
    }
    std::cout << std::endl;
    return;
}

int main() {
    //.txt ���� ����
    std::ifstream txt_file("ciphertext.txt");
    if (!txt_file.is_open()) {
        std::cout << "FILE OPEN ERROR" << std::endl;
        return 0;
    }

    std::string str;
    getline(txt_file, str);

    std::string a;
    std::stringstream ss(str);

    //txt������ ������ �ϳ��� 16������ ��ȯ
    int* ptr = new int[str.length() * sizeof(int)];
    int length = 0;
    while (ss >> a) {
        int t = 0;
        t = std::stoi(a, nullptr, 16);
        ptr[length++] = t;
    }

    //������
    std::cout << "ciphertext: ";
    for (int i = length; i > 0; i--)
        std::cout << ptr[length - i] << ' ';
    std::cout << std::endl;
    
    for (int key = 0; key < 128; key++)
        print_str(ptr, length, key);

    return 0;
}