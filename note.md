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

