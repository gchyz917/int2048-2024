#pragma once
#ifndef SJTU_BIGINTEGER
#define SJTU_BIGINTEGER

// Integer 1:
// 实现一个有符号的大整数类，只需支持简单的加减

// Integer 2:
// 实现一个有符号的大整数类，支持加减乘除，并重载相关运算符

// 请不要使用除了以下头文件之外的其它头文件
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

// 请不要使用 using namespace std;

namespace sjtu {
class int2048 {
// todo
public:
  // 构造函数
  int2048 () {
    a. push_back ( 0 );
    sign = true ;
  }
  int2048( long long num ){
    if(num >= 0){
      sign = true;
    }else {
      sign = false;
      num = - num;
    }
    if(num == 0) a. push_back( 0 );
    while( num ){
      a. push_back ( num % 10000 );
      num /= 10000;
    }
  }
  int2048( const std::string &s ){
    read ( s );
  }
  int2048( const int2048 &other ):a(other.a),sign(other.sign){}
  // 以下给定函数的形式参数类型仅供参考，可自行选择使用常量引用或者不使用引用
  // 如果需要，可以自行增加其他所需的函数
  // ===================================
  // Integer1
  // ===================================

  // 读入一个大整数
  //压位10000进制
  std::vector< long long int > a;//存储整数
  bool sign;//正负的标记
  void read( const std::string &s ){
    a.clear();
    if(s[0] != '-' && s[0] != '+'){ //无符号不影响
      sign = true;
      int k = 0;
      if(s[0] == '0' && s.size() == 1) {
        a.push_back(0 );
      }else {
        int i;
        for(i = 0;i < s.size(); i++ ) {
          if(s[i] == '0') {
            k++;
            continue;
          }else {
            break;
          }
        }
        for(i = s.size() - 1;i >= k; i--){
          a.push_back(s[i] - '0');//倒着读入
        }

      }

    }else{ //有符号
      if(s[1] != '0') {
        if(s[0] == '-') {
          sign = false;
        }else if(s[0] == '+') {
          sign = true;
        }
        for(int i = s.size()-1;i >= 1;i--){
          a.push_back(s[i]-'0');//
        }
        //去除前缀0
      }else if(s.size() == 2){
        sign = true;
        a.push_back(0);
      }else {
        int k = 1;
        int i;
        for(i = 1;i < s.size(); i++) {
          if(s[i] == '0') {
            k++;
            continue;
          }else {
            break;
          }
        }
        if(i < s.size()) {
          if(s[0] == '+') {
            sign = true;
          }else {
            sign = false;
          }
          for(i = s.size()-1;i >= k;i--){
            a.push_back(s[i]-'0');//
          }
        }else {
          sign = true;
          a.push_back(0);
        }
      }
    }

    //将得到的vector数组全部转化为10000进制下的情形
    int k = 0;//记录当前遍历到原数组的第几位
    int len = a.size();//原数组长度
    int j;
    while(true) {
      int sum = 0;
      for(j = k;j < std::min(k+4,len); j++) {
        if(j-k == 0) {
          sum += a[j];
        }else if(j-k == 1) {
          sum += 10*a[j];
        }else if(j-k == 2) {
          sum += 100*a[j];
        }else {
          sum += 1000*a[j];
        }
      }
      a.push_back(sum);//将其存入新数组里
      if(j == len) {
        break;//工作结束
      }
      k += 4;
    }
    a.erase(a.begin(),a.begin() + len);//删除原数组中前len项元素 得到10000进制下的数组
  }
  // 输出储存的大整数，无需换行
  //TODO 输出时候需要将10000进制转变为10进制！！！
  void print(){
    if( !sign ) {
      std::cout << "-";
    }
    //将10000进制转变为10进制输出
    for(int i = a.size()-1;i >= 0;i--) {
      if(i == a. size()-1) {
        std::cout << a[i];
      }else {
        if(a[i] >= 1000) {
          std::cout << a[i];
        }else if(a[i] >= 100) {
          std::cout << 0 << a[i];
        }else if(a[i] >= 10) {
          std::cout << 0 << 0 << a[i];
        }else {
          std::cout << 0 << 0 << 0 << a[i];
        }
      }
    }
  }
  // 加上一个大整数

  int2048 &add(const int2048 &other){
    int len1 = a.size();
    int len2 = other.a.size();
    bool flag = false;
    int2048 result;
    result.a.clear();
    if(sign != other.sign) {
      //todo 压位高精度减法
      if(sign && !other.sign) {
        if(*this^other) { //比较绝对值大小
          result.sign = false;
        }else {
          result.sign = true;
        }
      }else {
        if(*this^other || other == -*this) { //比较绝对值大小
          result.sign = true;
        }else {
          result.sign = false;
        }
      }
      bool carry = false;//初始时不借位
      if(*this^other) {
        //a的绝对值严格小于b
        //进行b-a的操作
        for(int i = 0;i < len1;i++) {
          result.a.push_back((other.a[i] - a[i] - carry + 10000) % 10000);
          if(other.a[i]-a[i]-carry < 0) {
            carry = true;//设置进位
          }else {
            carry = false;
          }
        }
        if(len1 < len2) { //处理前面部分的操作
          for(int i = len1;i < len2; i++){
            result.a.push_back((other.a[i] - carry + 10000)%10000);
            if(other.a[i]-carry < 0) {
              carry = true;//需要借位
            }else {
              carry = false;
            }
          }
        }
      }else {
        //仍然进行a-b的操作 a大于等于b
        for(int i = 0;i < len2; i++) {
          result.a.push_back((a[i] - other.a[i] - carry + 10000)%10000);
          if(a[i]-other.a[i]-carry < 0) {
            carry = true;
          }else {
            carry = false;
          }
        }
        if(len2 < len1) {
          for(int i = len2;i < len1;i++) {
            result.a.push_back((a[i] - carry + 10000) % 10000);
            if(a[i]-carry < 0) {
              carry = true;
            }else {
              carry = false;
            }
          }
        }
      }
      //去除前置0操作
      int i;
      for(i = result.a.size() - 1;i >= 0;i--) {
        if(result.a[i] == 0) {
          result.a.pop_back();
        }else {
          break;
        }
      }
      if(i == -1) {
        result.a.push_back(0);
      }
    }else {
      if(sign && other.sign) {
        result.sign = true;
      }else {
        result.sign = false;
      }
      int carry = 0;
      for(int i = 0;i < std::min(len1,len2); i++) {
        result.a.push_back((a[i] + other.a[i] + carry) % 10000);
        carry = (a[i] + other.a[i] + carry) / 10000;
      }
      if(len1 < len2) {
        for(int i = len1;i < len2; i++) {
          result.a.push_back((other.a[i] + carry) % 10000);
          carry = (other.a[i] + carry) / 10000;
        }
      }else if(len1 > len2) {
        for(int i = len2;i < len1; i++) {
          result.a.push_back((a[i] + carry) % 10000);
          carry = (a[i] + carry) / 10000;
        }
      }else {
        if(carry > 0) {
          result.a.push_back(carry);
        }
      }
    }
    return *this = result;
  }
  // 返回两个大整数之和
  friend int2048 add(int2048 n1, const int2048 &n2){
    return n1.add(n2);
  }
  // 减去一个大整数
  int2048 &minus(const int2048 &other){

    int len1 = a.size();
    int len2 = other.a.size();
    bool flag = false;
    int2048 result ;
    result.a.clear();
    if(sign != other.sign) {
      //高精度加法
      if(sign && !other.sign) {
        result.sign = true;
      }else {
        result.sign = false;
      }
      int carry = 0;
      for(int i = 0;i < std::min(len1,len2); i++) {
        result.a.push_back((a[i] + other.a[i] + carry) % 10000);
        carry = (a[i] + other.a[i] + carry) / 10000;
      }
      if(len1 < len2) {
        for(int i = len1;i < len2; i++) {
          result.a.push_back((other.a[i] + carry) % 10000);
          carry = (other.a[i] + carry) / 10000;
        }
        if(carry > 0) {
          result.a.push_back(1);
        }
      }else if(len1 > len2) {
        for(int i = len2;i < len1; i++) {
          result.a.push_back((a[i] + carry) % 10000);
          carry = (a[i] + carry) / 10000;
        }
        if(carry > 0) {
          result.a.push_back(1);
        }
      }else {
        if(carry > 0) {
          result.a.push_back(1);
        }
      }
    }else {
      //TODO 压位高精度减法实现
      //先进行结果符号判断
      if(sign && other.sign) {
        if(*this^other) { //比较绝对值大小
          result.sign = false;
        }else {
          result.sign = true;
        }
      }else {
        if(*this^other || *this == other) {
          result.sign = true;
        }else {
          result.sign = false;
        }
      }
      bool carry = false;//初始时不借位
      if(*this^other) {
        //a的绝对值严格小于b
        //进行b-a的操作
        for(int i = 0;i < len1; i++) {
          result.a.push_back((other.a[i] - a[i] - carry + 10000) % 10000);
          if(other.a[i] - a[i] - carry < 0) {
            carry = true;//设置进位
          }else {
            carry = false;
          }
        }
        if(len1 < len2) { //处理前面部分的操作
          for(int i = len1;i < len2; i++){
            result.a.push_back((other.a[i] - carry + 10000) % 10000);
            if(other.a[i] - carry < 0) {
              carry = true;//需要借位
            }else {
              carry = false;
            }
          }
        }
      }else {
        //仍然进行a-b的操作 a大于等于b
        for(int i = 0;i < len2; i++) {
          result.a.push_back((a[i] - other.a[i] - carry + 10000) % 10000);
          if(a[i] - other.a[i] - carry < 0) {
            carry = true;
          }else {
            carry = false;
          }
        }
        if(len2 < len1) {
          for(int i = len2;i < len1; i++) {
            result.a.push_back((a[i] - carry + 10000) % 10000);
            if(a[i]-carry < 0) {
              carry = true;
            }else {
              carry = false;
            }
          }
        }
      }
      //去除前置0操作
      int i;
      for(i = result.a.size()-1;i >= 0; i--) {
        if(result.a[i] == 0) {
          result.a.pop_back();
        }else {
          break;
        }
      }

      if(i == -1) {
        result.a.push_back(0);
      }
    }
    return *this = result;
  }

  // 返回两个大整数之差
  friend int2048 minus(int2048 n1, const int2048 &n2){
    return n1.minus(n2);
  }
  // ===================================
  // Integer2
  // ===================================

  int2048 operator+() const { //不变
    return *this;
  }
  int2048 operator-() const { //转化成相反数
    int2048 result = *this;
    if(!sign) {
      result.sign = true;
    }else {
      result.sign = false;
    }
    return result;
  }

  int2048 &operator=(const int2048 &other) { //赋值
    a = other.a;
    sign = other.sign;
    return *this;
  }

  int2048 &operator+=(const int2048 &other) { //高精度加法
    if(sign != other.sign) { //符号不同转化为减法
      return *this -=- other; //-other将other转化为相反数
    }
    int len1 = a.size();
    int len2 = other.a.size();
    bool flag = false;
    int2048 result;
    result.a.clear();
    if(sign && other.sign) {
      result.sign = true;
    }else {
      result.sign = false;
    }
    int carry = 0;
    for(int i = 0;i < std::min(len1,len2);i++) {
      result.a.push_back((a[i] + other.a[i] + carry) % 10000);
      carry=(a[i] + other.a[i] + carry)/ 10000;
    }
    if(len1 < len2) {
      for(int i = len1;i < len2; i++) {
        result.a.push_back((other.a[i] + carry) % 10000);
        carry = (other.a[i] + carry) / 10000;
      }
      if(carry > 0) {
        result.a.push_back(carry);
      }
    }else if(len1 > len2) {
      for(int i = len2;i < len1;i++) {
        result.a.push_back((a[i] + carry) % 10000);
        carry = (a[i] + carry) / 10000;
      }
      if(carry > 0) {
        result.a.push_back(carry);
      }
    }else {
      if(carry > 0) {
        result.a.push_back(carry);
      }
    }
    return *this = result;
  }
  friend int2048 operator+(int2048 n1, const int2048 &other) {
    return n1 += other;
  }

  int2048 &operator -= (const int2048 &other) { //高精度减法
    if(sign != other.sign) {
      return *this +=- other;//转化为加法
    }
    int len1 = a.size();
    int len2 = other.a.size();
    bool flag = false;
    int2048 result ;
    result.a.clear();
    if(sign && other.sign) {
      if(*this^other) { //比较绝对值大小(^表示绝对值严格小于）
        result.sign = false;
      }else {
        result.sign = true;
      }
    }else {
      if(*this^other || *this == other) {
        result.sign = true;
      }else {
        result.sign = false;
      }
    }
    bool carry = false;//初始时不借位
    if(*this^other) {
      //a的绝对值严格小于b
      //进行b-a的操作
      for(int i = 0;i < len1;i++) {
        result.a.push_back((other.a[i]-a[i]-carry+10000)%10000);
        if(other.a[i]-a[i]-carry<0) {
          carry = true;//设置进位
        }else {
          carry = false;
        }
      }
      if(len1 < len2) { //处理前面部分的操作
        for(int i = len1;i < len2; i++){
          result.a.push_back((other.a[i] - carry + 10000) % 10000);
          if(other.a[i] - carry < 0) {
            carry = true;//需要借位
          }else {
            carry = false;
          }
        }
      }
    }else {
      //仍然进行a-b的操作 a大于等于b
      for(int i = 0;i < len2;i++) {
        result.a.push_back((a[i] - other.a[i] - carry + 10000) % 10000);
        if(a[i] - other.a[i] - carry < 0) {
          carry = true;
        }else {
          carry = false;
        }
      }
      if(len2 < len1) {
        for(int i = len2;i < len1; i++) {
          result.a.push_back((a[i] - carry + 10000) % 10000);
          if(a[i] - carry < 0) {
            carry = true;
          }else {
            carry = false;
          }
        }
      }
    }
    //去除前置0操作
    int length = result.a.size();
    for(int i = length - 1;i >= 0; i--) {
      if(result.a[i] == 0) {
        result.a.pop_back();
      }else {
        break;
      }
    }
    if(result.a.empty()) {
      result.sign = true;
      result.a.push_back(0);
    }
    return *this = result;
  }
  friend int2048 operator-(int2048 n1, const int2048 &other) {
    return n1 -= other;
  }
  //高精度乘法
  int2048 &operator*=(const int2048 &other) {
    int2048 result;
    result.a.clear();
    int len1 = a.size();
    int len2 = other.a.size();
    int carry = 0;
    if((a.size() == 1&&a[0] == 0) || (other.a.size() == 1&&other.a[0] == 0)) { //单独处理0的情况
      result.sign = true;
      result.a.push_back(0);
    }else {
      if(sign != other.sign) {
        result.sign = false;
      }else {
        result.sign = true;
      }
      for(int i = 0;i < len1; i++) {
        for(int j = 0;j < len2; j++) {
          if(i + j < result.a.size()) {
            result.a[i+j] += a[i] * other.a[j];
          }else {
            result.a.push_back(a[i] * other.a[j]);
          }
        }
      }
      long long int carry = 0;
      for(int i = 0;i < result.a.size(); i++) {
        if(result.a[i] + carry >= 10000) {
          long long int tmp = result.a[i];
          result.a[i] = (tmp + carry) % 10000;
          carry = (tmp + carry) / 10000;
        }else {
          result.a[i] = (result.a[i] + carry) % 10000;
          carry = 0;
        }
      }
      if(carry > 0) {
        result.a.push_back(carry);
      }
      for(int i = result.a.size() - 1;i >= 0; i--) {
        if(result.a[i] == 0) {
          result.a.pop_back();
        }else {
          break;
        }
      }
    }

    return *this = result;
  }

  friend int2048 operator*(int2048 n1, const int2048 &other) {
    return n1 *= other;
  }
  //高精度除法
  int2048 &operator/=(const int2048 &other) {
    int len1 = a.size();
    int len2 = other.a.size();
    for(int i = len1-1;i >= 0;i--) {
      if(a[i] == 0) {
        a.pop_back();
      }else {
        break;
      }
    }
    if(a.empty()) {
      a.push_back(0);
      sign = true;
    }
    len1 = a.size();
    int2048 result;
    result.a.clear();

    if(len1 == 1 && a[0] == 0) {
      result.sign = true;
      result.a.push_back(0);
    }else {
      if(sign != other.sign) {
        result.sign = false;
      }else {
        result.sign = true;
      }
      //全部转化为绝对值
      if(*this^other) {
        if(sign == other.sign) {
          result.sign = true;
          result.a.push_back(0);
        }else {
          result.sign = false;
          result.a.push_back(1);
        }
      }else {
        result.a.resize(len1 - len2 + 1);
        int2048 sub;
        sub.a.clear();
        sub.a.resize(len2);
        int2048 remain;
        remain.a.clear();
        for(int i = len1-len2;i < len1; i++) {
          sub.a[i - len1 + len2] = a[i];
        }
        for(int i = len1 - len2;i >= 0; i--) {
          if(i < len1 - len2) {
            sub = remain* 10000 + a[i];
          }
          int l = 0;
          int r = 9999;
          int ans = 0;
          int2048 other1 = other;
          if(!other.sign) {
            other1.sign = true;
          }
          if(sub < other) {
            result.a[i] = 0;
            remain = sub;
          }else {
            while(l <= r) {
              int mid = (l + r) / 2;
              if(sub >= mid*other1) {
                ans = mid;
                l = mid + 1;
              }else {
                r = mid - 1;
              }
            }
            result.a[i] = ans;
            remain = sub- ans* other1;
          }
        }
        //处理溢出base的商 进位
        int borrow = 0;
        for(int i = 0;i < result.a.size(); i++) {
          if(result.a[i] + borrow >= 10000) {
            int tmp = borrow;
            borrow = (result.a[i] + tmp) / 10000;
            result.a[i] = (result.a[i] + tmp) % 10000;
          }else {
            borrow = 0;
          }
        }
        if(borrow > 0) {
          result.a.push_back(borrow);
        }
        //去除前缀0
        int length = result.a.size();
        for(int i = length - 1;i >= 0; i--) {
          if(result.a[i] == 0) {
            result.a.pop_back();
          }else {
            break;
          }
        }
        if(result.a.empty()) {
          result.sign = true;
          result.a.push_back(0);
        }
        if(result*other != *this&&!result.sign) {
          result-= 1;
        }
      }
    }
    return *this = result;
  }
  friend int2048 operator/(int2048 n1, const int2048 &other) {
    return n1/=other;
  }

  friend bool operator^(const int2048 &n1,const int2048 &other) {   //绝对值严格小于
    int len1=n1.a.size();
    int len2=other.a.size();
    if(len1<len2) {
      return true;
    }else if(len1>len2) {
      return false;
    }else {
      for(int i=len1-1;i>=0;i--) {
        if(n1.a[i]<other.a[i]) {
          return true;
        }else if(n1.a[i]>other.a[i]) {
          return false;
        }
      }
      return false;
    }
  }

  int2048 &operator%=(const int2048 &other) {
    int2048 result;
    result=*this-(*this/other)*other;
    if(result==0) {
      result.sign=true;
    }
    return *this=result;
  }
  friend int2048 operator%(int2048 n1, const int2048 &other) {
    return n1%=other;
  }

  friend std::istream &operator>>(std::istream &input, int2048 &n1) { //输入流
    std::string s;
    input>>s;
    n1.read(s);
    return input;
  }
  friend std::ostream &operator<<(std::ostream &output, const int2048 &n1) {//输出流
    if(!n1.sign) {
      if(n1!=0) {
        output<<"-";
      }
    }
    if(n1.a.size()==1) {
      output<<n1.a[0];
    }else {
      for(int i=n1.a.size()-1;i>=0;i--) {
        if(i==n1.a.size()-1) {
          output<<n1.a[i];
        }else {
          if(n1.a[i]>=1000) {
            output<<n1.a[i];
          }else if(n1.a[i]>=100) {
            output<<0<<n1.a[i];
          }else if(n1.a[i]>=10) {
            output<<0<<0<<n1.a[i];
          }else {
            output<<0<<0<<0<<n1.a[i];
          }
        }
      }
    }
    return output;
  }
  friend bool operator==(const int2048 &n1, const int2048 &other) {
    if(n1.a.size()!=other.a.size()) {
      return false;
    }else if(n1.sign!=other.sign){
      if((n1.a.size()==1&&n1.a[0]==0)&&(other.a.size()==1&&other.a[0]==0)) {
        return true;
      }
      return false;
    }else {
      for(int i=0;i<n1.a.size();i++) {
        if(n1.a[i]!=other.a[i]) {
          return false;
        }
      }
      return true;
    }
  }
  friend bool operator!=(const int2048 &n1, const int2048 &other) {
    if(n1==other) {
      return false;
    }else {
      return true;
    }
  }
  friend bool operator<(const int2048 &n1, const int2048 &other) {
    if(n1==other) {
      return false;
    }
    if(!n1.sign&&other.sign) {
      return true;
    }else if(n1.sign&&!other.sign){

      return false;
    }else if(n1.sign&&other.sign){
      if(n1.a.size()>other.a.size()) {
        return false;
      }else if(n1.a.size()<other.a.size()) {
        return true;
      }else {
        if(n1==other) {
          return false;
        }else {
          for(int i=n1.a.size()-1;i>=0;i--) {
            if(n1.a[i]>other.a[i]) {
              return false;
            }else if(n1.a[i]<other.a[i]) {
              return true;
            }
          }
        }
      }
    }else  {
      if(n1.a.size()>other.a.size()) {
        return true;
      }else if(n1.a.size()<other.a.size()) {
        return false;
      }else {
        if(n1==other) {
          return false;
        }else {
          for(int i=n1.a.size()-1;i>=0;i--) {
            if(n1.a[i]>other.a[i]) {
              return true;
            }else if(n1.a[i]<other.a[i]) {
              return false;
            }
          }
        }
      }
    }
  }
  friend bool operator>(const int2048 &n1, const int2048 &other) {
    if(n1==other) {
      return false;
    }else if(n1<other) {
      return false;
    }
    return true;
  }
  friend bool operator<=(const int2048 &n1, const int2048 &other) {
    if(n1==other||n1<other) {
      return true;
    }else {
      return false;
    }
  }
  friend bool operator>=(const int2048 &n1, const int2048 &other) {
    if(n1==other||n1>other) {
      return true;
    }else {
      return false;
    }
  }
};
} // namespace sjtu

#endif
