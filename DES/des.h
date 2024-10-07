#ifndef DES_H
#define DES_H
#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
extern vector<int> globalKey;//全局key
const int S1[4][4] = {//S1box
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {3, 1, 0, 2}
};

const int S2[4][4] = {//S2box
    {0, 1, 2, 3},
    {2, 3, 1, 0},
    {3, 0, 1, 2},
    {2, 1, 0, 3}
};
string generateRandomstring(int length);//得到自定长度的随机字符串
vector<int> P10Box(vector<int> input) ;//P10box
vector<int> P8Box(vector<int> input);//P8box
vector<vector<int>> split(vector<int> input);//对于输入的一维容器分割转换为二维容器
vector<int> merge(vector<vector<int>> input);//合并一个二维容器为一维容器
vector<int> leftShift1(vector<int> input);//移位box
vector<int> leftShift2(vector<int> input);//移位box
vector<vector<int>> subKey(vector<int> input);//生成子key
vector<int> IP(vector<int> input);//IPbox
vector<int> IPReverse(vector<int> input);//IP逆box
vector<int> EPBox(vector<int> input);//EPbox
vector<int> SPBox(vector<int> input);//SPbox
vector<int> char2Binary(char input);//转换字符为二进制串并补位
vector<int> int2Binary(int input);//转换数字为二进制串并补位
vector<int> forceInt2Binary(int input);//针对暴力破解的数值转换为二进制串
vector<int> sboxSubstitution(const vector<int>& input);//sbox转换
vector<vector<int>> strToBinary(string plainText);//字符串转换为二进制串数组
vector<int> getKey(string input);//通过输入字符串得到对应的key，不过key只有10位，超过10位的无效输入
vector<int> F(vector<int> input,int turn);//轮转函数中的关键
vector<int> splitedP(vector<int> input,int turn,bool flag);//左右key做运算的模块
char binary2Cha(vector<int> input);//二进制串转换成字符
string encryptionAPI(string s,string key);//加密接口
string forceEncryptionAPI(string s, vector<int> key);//暴力加密的接口
vector<vector<int>> strSplit(string s);//分割密文字符串
string decryptionAPI(string s, string key);//解密字符串接口
string forceDecryptionAPI(string s, vector<int> key);//暴力解密接口


#endif // DES_H
