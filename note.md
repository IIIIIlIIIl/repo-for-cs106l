# CS106l 

以前说实话大部分用的是 cin+cout+C+算法，补充一些学到的特性吧。

### using 创建类型别名

```cpp
std::pair<bool,std::pair<double,double>> solveQuadratic(double a,double b,double c);
// 简化
using Zeros=std::pair<double,double>;
using Solution=std::pair<bool,Zeros>;
Solution solveQuadratic(double a,double b,double c);
```

### Uniform initialization(C++11)

大括号赋初值可以自动检查类型, map,vector 等其他容器也可用大括号

```cpp
int number{1.0}; // compile erroe
int number{1};
```

### Structured Binding(C++17)

```cpp
#include <iostream>
#include <tuple>
#include <string>
std::tuple<std::string, std::string, std::string> getClassInfo() {
	std::string className = "CS106L";
	std::string buildingName = ”Thornton 110";
	std::string language = "C++";
	return {className, buildingName, language};
}
int main() {
	auto [className, buildingName, language] = getClassInfo();
	std::cout << "Come to " << buildingName << " and join us for " 		<< className << " to learn " << language << "!" << std::endl;
	return 0;
}
```

### 引用的细节问题

```cpp
void shift(std::vector<std::pair<int,int>> &nums){
    // 不会改变nums里面的值
    for(auto [num1,num2]:nums){
        num1++;
        num2++;
    }
    // 改变nums里面的值
    for(auto &[num1,num2]:nums){
        num1++;
        num2++;
    }
    for(size_t i=0;i<nums.size();i++){
        nums[i].first++;
        nums[i].second++;
    }
}
```

### 左值和右值

```cpp
void squareN(int &n){
    n=std::pow(n,2);
}

int main(){
    // 右值不能传引用
    squareN(5);
    return 0;
}
```

```cpp
void squareN(const int &n){
    n=std::pow(n,2);
}

int main(){
    // 但是如果是const引用可以传入右值
    squareN(5);
    return 0;
}
```

### 关于 cin 和 getline

最好不要一起用，对于 \n 的处理不同，cin 会把 \n 留在缓冲区，但 getline 会把 \n 也处理掉，直接到下一行，先 cin 再直接 getline 可能会让 getline 只读到一个 \n 

### 关于 auto

遍历的时候一般使用 

```cpp
for(const auto &x:v)
```

好一点，能够避免拷贝，也能防止引用产生的可能会改变数据。

### 关于 unordered_map

提供了可以查询 load factor 的函数，即每个”桶“平均挂了几个数据，也可以设置最大 load factor ，超过这个阈值会自动进行 reharsh

```cpp
std::unordered_map<std::string,int>map;

double lf=map.load_factor();
map.max_load_factor(2.0);
```

### 关于迭代器

让迭代器 $+1$ 的时候用 ++it 比 it++ 好一些，前缀 ++ 避免进行不必要的拷贝，迭代器是一个完整的对象，拷贝它更消耗更大

```cpp
// Prefix form - ++it
// Increments it and returns a reference to same object
Iterator& operator++();

// Postfix form - it++
// Increments it and returns a copy of the old value
Iterator operator++(int);
```

### 迭代器类型

**Input Iterator**:只读，单向，无法多趟遍历，例： std::istream_iterator

**Output Iterator**:只写，单向，无法多趟遍历，例： std::ostream_iterator

**Forward Iterator**:读写，单向，可以多趟遍历，例： std::forward_list 的迭代器

**Bidirectional Iterator**:读写，双向，可以多趟遍历，例： std::list,std::set 的迭代器

**Random Access Iterator**:读写，双向，可以多趟遍历，例： std::vector,std::deque 的迭代器

### 菱形继承

A -> B , A -> C , B -> D , C -> D ，从 D 直接访问 A 中元素会产生歧义，使用虚继承解决，让 B 和 C 在 D 中共享一个 A 对象

```cpp
class C:virtual public A{
    public:
    	C();
}
class B:virtual public A{
    public:
    	B();
}
```

### 虚函数

| **其他语言默认虚** | Java、C# 等为了便利性，默认使用动态绑定      |
| ------------------ | -------------------------------------------- |
| **C++ 默认非虚**   | 遵循零开销原则，不为不需要的功能付费         |
| **虚函数成本**     | 对象增大（vptr）、调用变慢（间接）、无法内联 |
| **适用场景**       | 需要运行时多态时使用虚函数                   |
| **性能敏感领域**   | 量化金融、游戏引擎、嵌入式避免使用虚函数     |
| **替代方案**       | 模板、CRTP、策略模式等编译时多态             |
