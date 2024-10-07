#include "des.h"
vector<int> globalKey;
string generateRandomstring(int length) {//得到自定长度的随机字符串
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string result;
    result.reserve(length);

    for (int i = 0; i < length; ++i) {
        result += charset[rand() % (sizeof(charset) - 1)];
    }
    return result;
}
vector<int> P10Box(vector<int> input) {//P10box
    vector<int> output(10);
    int grid[] = { 3,5,2,7,4,10,1,9,8,6 };
    for (int i = 0; i < 10; i++) {
        output[i] = input[grid[i]-1];//原位置的数据转移位置
    }
    return output;
}
vector<int> P8Box(vector<int> input) {//P8box
    vector<int> output(8);
    int grid[] = { 6,3,7,4,8,5,10,9 };
    for (int i = 0; i < 8; i++) {
        output[i] = input[grid[i] - 1];//原位置的数据转移位置
    }
    return output;
}
vector<vector<int>> split(vector<int> input) {//对于输入的一维容器分割转换为二维容器
    vector<vector<int>> output(2);
    int n = input.size(), i = 0;
    int mid = n >> 1;
    vector<int> left;
    vector<int> right;
    while (i < n) {
        if (i < mid) {
            left.push_back(input[i++]);
        }
        else {
            right.push_back(input[i++]);
        }
    }
    output[0] = left;
    output[1] = right;
    return output;
}
vector<int> merge(vector<vector<int>> input) {//合并一个二维容器为一维容器
    int m = input.size();
    int n = input[0].size();
    vector<int> output;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            output.push_back(input[i][j]);
        }
    }
    return output;
}
vector<int> leftShift1(vector<int> input) {//移位box
    vector<int> output(5);
    int grid[] = { 2,3,4,5,1 };
    for (int i = 0; i < 5; i++) {
        output[i] = input[grid[i] - 1];
    }
    return output;
}
vector<int> leftShift2(vector<int> input) {//移位box
    vector<int> output(5);
    int grid[] = { 3,4,5,1,2 };
    for (int i = 0; i < 5; i++) {
        output[i] = input[grid[i] - 1];
    }
    return output;
}
vector<vector<int>> subKey(vector<int> input) {//生成子key
    vector<vector<int>> output(2);
    input = P10Box(input);
    vector<vector<int>> splitInput = split(input);
    splitInput[0] = leftShift1(splitInput[0]);
    splitInput[1] = leftShift1(splitInput[1]);
    vector<int> temp = merge(splitInput);
    output[0] = P8Box(temp);
    splitInput[0] = leftShift2(splitInput[0]);
    splitInput[1] = leftShift2(splitInput[1]);
    temp = merge(splitInput);
    output[1] = P8Box(temp);
    return output;
}
vector<int> IP(vector<int> input) {//IPbox
    vector<int> output(8);
    int grid[] = { 2,6,3,1,4,8,5,7 };
    for (int i = 0; i < 8; i++) {
        output[i] = input[grid[i] - 1];
    }
    return output;
}
vector<int> IPReverse(vector<int> input) {//IP逆box
    vector<int> output(8);
    int grid[] = { 4,1,3,5,7,2,8,6 };
    for (int i = 0; i < 8; i++) {
        output[i] = input[grid[i] - 1];
    }
    return output;
}
vector<int> EPBox(vector<int> input) {//EPbox
    vector<int> output(8);
    int grid[] = { 4,1,2,3,2,3,4,1 };
    for (int i = 0; i < 8; i++) {
        output[i] = input[grid[i] - 1];
    }
    return output;
}
vector<int> SPBox(vector<int> input) {//SPbox
    vector<int> output(4);
    int grid[] = { 2,4,3,1 };
    for (int i = 0; i < 4; i++) {
        output[i] = input[grid[i] - 1];
    }
    return output;
}
vector<int> char2Binary(char input) {//转换字符为二进制串并补位
    int asciiCode = input;
    //cout << asciiCode << endl;
    vector<int> output(8,0);
    int index = 7;
    while (index>=0&&asciiCode != 0) {
        output[index]=(asciiCode % 2);
        asciiCode /= 2;
        index--;
    }
    return output;
}
vector<int> int2Binary(int input) {//转换数字为二进制串并补位
    vector<int> output;
    int index;
    if (input <= 3) {
        output.assign(2, 0);
        index = 1;
    }
    else{
        output.assign(8, 0);
        index = 7;
    }
    while (index >= 0 && input != 0) {
        output[index] = (input % 2);
        input /= 2;
        index--;
    }
    return output;
}
vector<int> forceInt2Binary(int input) {//针对暴力破解的数值转换为二进制串
    vector<int> output(10, 0);
    int index=9;
    while (index >= 0 && input != 0) {
        output[index] = (input % 2);
        input /= 2;
        index--;
    }
    return output;
}
vector<int> sboxSubstitution(const vector<int>& input) {//sbox转换
    int row1 = (input[0] << 1) + input[3]; // 取 S1 的行
    int col1 = (input[1] << 1) + input[2]; // 取 S1 的列
    int row2 = (input[4] << 1) + input[7]; // 取 S2 的行
    int col2 = (input[5] << 1) + input[6]; // 取 S2 的列
    vector<vector<int>> temp(2);
    temp[0] = int2Binary(S1[row1][col1]);
    temp[1] = int2Binary(S2[row2][col2]);
    return merge(temp);
}
vector<vector<int>> strToBinary(string plainText) {//字符串转换为二进制串数组
    int len = plainText.length();
    vector<vector<int>> outPut(len);
    for (int i = 0; i < len; i++) {
        outPut[i] = char2Binary(plainText[i]);
    }
    return outPut;
}
vector<int> getKey(string input) {//通过输入字符串得到对应的key，不过key只有10位，超过10位的无效输入
    vector<vector<int>> temp = strToBinary(input);
    vector<int> output(10, 0);
    int m = temp.size();
    int n = temp[0].size();
    int index = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            output[index++] = temp[i][j];
            if (index == 10)break;
        }
        if (index == 10)break;
    }
    return output;
}
vector<int> F(vector<int> input,int turn) {//轮转函数中的关键
    input = EPBox(input);
    vector<int> subKeyi = subKey(globalKey)[turn];
    for (int i = 0; i < 8; i++) {
        input[i] = input[i] ^ subKeyi[i];
    }
    input = sboxSubstitution(input);
    input = SPBox(input);
    return input;
}
vector<int> splitedP(vector<int> input,int turn,bool flag) {//左右key做运算的模块
    vector<vector<int>> temp = split(input);
    vector<int> left = temp[0], right = temp[1];
    if ((turn == 1&&flag)||(turn==0&&!flag)) {
        swap(left, right);
    }
    vector<int> fRight = F(right, turn);
    int len = left.size();
    for (int i = 0; i < len; i++) {
        left[i] = left[i] ^ fRight[i];
    }
    temp[0] = left;
    temp[1] = right;
    return merge(temp);
}
char binary2Cha(vector<int> input) {//二进制串转换成字符
    int base = 1;
    int sum = 0;
    for (int i = 7; i >= 0; i--) {
        sum = sum + base * input[i];
        base *= 2;
    }
    char res = sum;
    return res;
}
string encryptionAPI(string s,string key) {//加密接口
    string res = "";
    globalKey = getKey(key);
    vector<vector<int>> plainText = strToBinary(s);
    int len = plainText.size();
    //cout << len << endl;
    for (int i = 0; i < len; i++) {
        vector<int> temp = IP(plainText[i]);
        temp = splitedP(temp, 0, true);
        temp = splitedP(temp, 1, true);
        temp = IPReverse(temp);
        for (int i = 0; i < 8; i++) {
            res.push_back(temp[i]+'0');
        }
        //char word = binary2Cha(temp);
    }
    return res;
}
string forceEncryptionAPI(string s, vector<int> key) {//暴力加密的接口
    string res = "";
    globalKey = key;
    vector<vector<int>> plainText = strToBinary(s);
    int len = plainText.size();
    //cout << len << endl;
    for (int i = 0; i < len; i++) {
        vector<int> temp = IP(plainText[i]);
        temp = splitedP(temp, 0, true);
        temp = splitedP(temp, 1, true);
        temp = IPReverse(temp);
        for (int i = 0; i < 8; i++) {
            res.push_back(temp[i] + '0');
        }
        //char word = binary2Cha(temp);
    }
    return res;
}
vector<vector<int>> strSplit(string s) {//分割密文字符串
    int len = s.length();
    int count = len / 8;
    vector<vector<int>> output(count, vector<int>(8, 0));
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < 8; j++) {
            output[i][j] = s[i * 8 + j] - '0';
        }
    }
    return output;
}
string decryptionAPI(string s, string key) {//解密字符串接口
    string res = "";
    globalKey = getKey(key);
    vector<vector<int>> plainText = strSplit(s);
    int len = plainText.size();
    for (int i = 0; i < len; i++) {
        vector<int> temp = IP(plainText[i]);
        temp = splitedP(temp, 1,false);
        temp = splitedP(temp, 0,false);
        temp = IPReverse(temp);
        char word = binary2Cha(temp);
        res.push_back(word);
    }
    return res;
}
string forceDecryptionAPI(string s, vector<int> key) {//暴力解密接口
    string res = "";
    globalKey = key;
    vector<vector<int>> plainText = strSplit(s);
    int len = plainText.size();
    for (int i = 0; i < len; i++) {
        vector<int> temp = IP(plainText[i]);
        temp = splitedP(temp, 1, false);
        temp = splitedP(temp, 0, false);
        temp = IPReverse(temp);
        char word = binary2Cha(temp);
        res.push_back(word);
    }
    return res;
}
