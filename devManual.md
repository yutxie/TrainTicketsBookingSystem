# 开发手册

## 模版文件相关规范

1. 文件名与类名相同与规范相同
2. 规范代码风格: 
	1. 除常量全大写外其余均按大小驼峰命名法(小写开头)
	2. 二元运算符两侧加空格
	3. 大括号与函数头同行
3. 使用sjtu名字空间
4. 使用头文件保护符号

*myClass.hpp*
```cpp
#ifndef SJTU_MYCLASS_HPP
#define SJTU_MYCLASS_HPP
namespace sjtu {

class myClass {
private:
public:
};

}
#endif
```

## Git管理相关规范

1. 所有代码相关的工作均在 dev 中完成
2. 代码文件保存在 source 文件夹中
3. source/ 文件夹下的直接文件应"保证"已经全部完成并被调试好
4. 每个人都请分别在 source/ 中创建一个名为 dev-myClass 的文件夹, 完成代码前在里面工作
5. 完成后请转移 myClass.hpp 到 source/ 下并删除该文件夹
6. 若需要调试则建立一 source/debug-myClass 文件夹, 请复制文件到文件夹中而非剪切
7. 调试完毕后无需删除文件夹 将文件夹名改为 "debug-myClass done" 即可, 但请尽量删除里面的可运行文件(如".exe", 比较占空间)

## 调试相关规范

1. 通用的错误类模版保存在 exceptions.hpp 中, 需要 include
2. 若其中不包含你所需要的特殊错误类, 则自行在 myClass 中继承 exception 类声明内嵌类 myExcepiton
3. 输出信息遵循以下格式

```
member_name1: value1
member_name2:
    value211 value212 ...
    value221 ...
```


```cpp
class myClass {
    class myException : public exception {
    public:
        myException() : exception(
	    "myException",
	    "description"
	    ) {}
    };
};
```

## 思路图解
[![思路图解](https://github.com/xxxxxyt/TrainTicketsBookingSystem/blob/master/TrainMind.png "思路图解")](https://github.com/xxxxxyt/TrainTicketsBookingSystem/blob/master/TrainMind.png "思路图解")

## 文件汇总
| file name | description |
|:---:|:----:|
| system.hpp | 订票系统 |
| train.hpp | 车次 |
| plan.hpp | 运行计划 |
| station.hpp | 车站 |
| ticket.hpp | 车票 |
| user.hpp | 管理员或用户 |
| vector.hpp | vector容器 |
| map.hpp | map容器 |
| list.hpp | list容器 |
| timer.hpp | 时间 |
| log.hpp | 系统日志 |
| getPath.hpp | 提取路径 |

## 类接口

### 第9周

注意:
1. 加粗的method暂缓实现
2. 若xxx不存在 throw no_such_xxx();
3. 若xxx已存在 throw existed_xxx();
4. 错误类若在exceptions.hpp中没有则需要自己定义为内嵌类
2. 可能有一些细节错误, 有觉得不对劲的地方请及时反馈!

#### user

用户类, 保存用户信息及已订车票列表

| return type | method | description |
|:----------:|:---------------:|:----------:|
| / | user() | 默认构造 |
| / | user(const std::string &_id, const std::string &_name, const std::string &_password = "000000") | 构造函数 |
| / | user(const user &other) | 拷贝构造 |
| user & | operator=(const user &other) | 赋值函数 |
| const std::string & | getId() const | 返回用户id |
| const std::string & | getName() const | 返回用户名 |
| const std::string & | getPassword() const | 返回用户密码 |
| void | getTicketList(std::ostream &os) | 输出车票列表 只需输出车票id即可 |
| const ticket & | getTicket(const std::string &ticketId) const | 返回用户所订的某张车票 若该用户未订此车票 |
| void | modifyName(const std::string &newName) | 修改用户名 |
| void | modifyPassword(const std::string &newPassword) | 修改用户密码 |
| void | orderTicket(const ticket &tk) | 订票 若该票已存在于用户已订票清单 |
| void | disorderTicket(const std::string &ticketId) | 退票 若该用户未订此车票 |
| friend std::ostream & | operator<<(std::ostream &os, user &obj) | 输出用户id, 用户名, 密码, 已订票清单 |
| void | readIn(std::ifstream &file) | 从file读入数据 |
| void | writeOut(std::ofstream &file) | 向file写入数据 |

注意:
1. 已订车票清单要求用map存储, <string ticketId, ticket tk>

#### system

订票系统类, 系统功能的主要承担者

| return type | method | description |
|:----------:|:---------------:|:----------:|
| / | train() | 默认构造 |
| const std::string & | getPassword() const | 返回系统密码 |
| void | getTrainList(std::ostream &os) | 输出车次列表 |
| train & | getTrain(const std::string &trainId) | 返回编号为trainId的车次 |
| void | getUserList(std::ostream &os) | 输出用户列表 |
| user & | getUser(const std::string &userId) | 返回用户id为userId的用户 |
| void | modifyPassword(const std::string &newPassword) | 修改系统密码 |
| void | inserTrain(const train &tr) | 添加车次 |
| void | deleteTrain(const std::string &trainId) | 删除车次 |
| void | insertUser(const user &us) | 添加用户 |
| void | deleteUser(const std::string &userId) | 删除用户 |
| void | readIn(std::ifstream &file) | 从file读入数据 |
| void | writeOut(std::ofstream &file) | 向file写入数据 |

注意:
1. 函数尚不完全, 还需更新!
2. 订票时要求生成一唯一的8位车票id, 可用字符: 'A'-'Z', '0'-'9'

#### train

车次类, 保存车次信息, 运行线路车站信息及运行计划信息

| return type | method | description |
|:----------:|:---------------:|:----------:|
| / | train() | 默认构造 |
| / | train(const std::string &_id) | 构造函数 |
| / | train(const train &other) | 拷贝构造 |
| train & | operator=(const train &other) | 赋值函数 |
| void | getStationList(std::ostream &os) const | 输出车站列表 |
| station & | getStation(int index) | 返回运行线路上的第index个车站 |
| void | getPlanList(std::ostream &os) | 输出运行计划列表 |
| plan & | getPlan(const timer &startTime) | 返回始发时间为startTime的运行计划 |
| void | pushStation(const station &st) | 添加站点到运行线路末尾 若该站点信息不合法 throw invalid_station(); |
| void | popStation() | 删除运行线路末尾的站点 |
| void | insertPlan(const plan &pl) | 添加运行计划 |
| void | deletePlan(const timer &startTime) | 删除运行计划 |
| friend std::ostream & | operator<<(std::ostream &os, train &obj) | 输出车次编号, 车站列表及车站信息, 运行计划列表及运行计划信息 |
| void | readIn(std::ifstream &file) | 从file读入数据 |
| void | writeOut(std::ofstream &file) const | 向file写入数据 |

注意:
1. 运行线路上的车站从0开始编号, 即起点站对于当前车次来说是第0个车站

### 第8周

#### station

车站类, train的一个"内嵌类", 某个具体车次运行路线中的某个车站
如A次列车和与其不同B次列车均会经过的上海站, 在这里认为是不同的

| return type | method | description |
|:----------:|:---------------:|:----------:|
| / | station() | 默认构造 |
| / | station(const std::string &_name, int _id, const std::string &_train, const timer &_stopTime, const timer &_departTIme, int _length, int _price[]) |  构造函数 |
| / | station(const station &other) | 拷贝构造 |
| station & | operator=(const station &other) | 赋值 |
| const std::string & | getName() const | 返回该车站的名字 |
| int | getId() const | 返回该车站的编号 |
| const std::string & | getTrain() const | 返回所属的车次 |
| const timer & | getStopTime() const | 返回在该车次从出发到停靠在该站的时间差 |
| const timer & | getDepartTime() const | 返回该车次从出发到离开该站的时间差 |
| int | getLength() const | 返回该车次从出发到停靠在该站的行驶里程数 |
| int | getPrice(int type) const | 返回该车次的type类型座位从出发到该站的票价 其中type=1,2,3分别表示一等座,二等座,三等座 |
| void | modifyPrice(int type, int newPrice) | 修改票价 |
| friend std::ostream & | operator<<(std::ostream &os, const station &obj) | 输出站名, 编号, 所属车次, 到达/出发时间, 里程数, 各类型票价 |
| void | readIn(std::ifstream &file) | 从file读入数据 |
| void | writeOut(std::ofstream &file) | 向file写入数据 |

#### plan

目前读入写出尚待增加, 请暂缓调用!
运行计划类, train的一个"内嵌类", 由所属车次与始发时间唯一确定

| return type | method | description |
|:----------:|:---------------:|:----------:|
| / | plan() | 默认构造 |
| / | plan(const std::string &_train, const timer &_startTime, int stationNumber, bool _status) | 构造函数 |
| / | plan(const plan &other) | 拷贝构造 |
| plan & | operator=(const &other) | 赋值 |
| const std::string & | getTrain() const | 返回所属的车次 |
| const timer & | getStartTime() const | 返回始发时间 |
| int | getStationNumber() const | 返回所属车次包含的车站总数 |
| bool | getStatus() const | 返回发售状态 |
| int | getLeftTickets(int type, int u, int v) const | 返回从该车次uth站点到vth站点type类型座位剩余票数 特殊地若传入不合法则返回0 |
| void | orderTicket(int type, int u, int v) | 订票 修改余票信息 |
| void | disorderTicket(int type, int u, int v) | 退票 修改余票信息 |
| void | modifyStartTime() | 修改始发时间 |
| void | modifyStatus(bool newStatus) | 修改售票状态 |
| friend std::ostream & | operator<<(std::ostream &os, const station &obj) | 输出所属车次, 始发时间, 表格形式的余票信息, 发售状态 |
| void | readIn(std::ifstream &file) | 从file读入数据 |
| void | writeOut(std::ofstream &file) | 向file写入数据 |

注意:
1. 所有修改均需要检查发售状态为 false
2. 订票后记得修改余票信息
3. 余票信息的修改与查询要求用树状数组实现
4. 修改余票信息操作前需检验是否合法, 若不合法则 throw invalid_order_operation();

#### ticket

车票类, 记录一张车票的相关信息

| return type | method | description |
|:----------:|:---------------:|:----------:|
| / | ticket() | 默认构造 |
| / | ticket(const std::string &_id, const std::string &_train, const std::string &_userId, const std::string &_userName, const std::string &_departStation, const std::string &_stopStation, const timer &_departTime, const timer &_stopTime, int _type, int _price) | 构造函数 |
| / | ticket(const ticket &other) | 拷贝构造 |
| ticket & | operator=(const ticket &other) | 赋值 |
| const std::string & | getId() | 返回车票id |
| const std::string & | getTrain() const | 返回所属车次 |
| const std::string & | getUserId() const | 返回用户id |
| const std::string & | getUserName() const | 返回用户名 |
| const std::string & | getDepartStation() const | 返回起点站 |
| const std::string & | getStopStation() const | 返回终点站 |
| const timer & | getDepartTime() const | 返回出发时间 |
| const timer & | getStopTime() const | 返回到达时间 |
| int | getType() const | 返回座位类型 |
| int | getPrice() const | 返回票价 |
| friend std::ostream & | operator<<(std::ostream &os, const ticket &obj) | 输出所属车次, 始发时间, 用户信息, 座位类型, 票价, 起点站与终点站 |
| void | readIn(std::ifstream &file) | 从file读入数据 |
| void | writeOut(std::ofstream &file) | 向file写入数据 |

### 第7周

注意:
1. 文件打开失败时均会 throw no_such_file();

#### list

list容器, 基本同STLite标准要求, 文件操作相关接口如下

| return type | method | description |
|:----------:|:---------------:|:----------:|
| void | readIn(std::ifstream &file) | 从file读入数据 |
| void | writeOut(std::ofstream &file) | 向file写入数据 |

相关代码参考:
```cpp
#include <fstream>

void readIn(std::ifstream &file) {
	if(!empty()) throw container_is_not_empty();
	int _currentlength;
	file.read(reinterpret_cast<char *> (&_currentlength), sizeof(int));
	T x;
	for(int i = 0; i < _currentlength; ++i) {
		file.read(reinterpret_cast<char *> (&x), sizeof(T));
		push_back(x);
	}
}
void writeOut(std::ofstream &file) {
	file.write(reinterpret_cast<const char *> (&currentlength), sizeof(int));
	node *ptr = head -> next;
	while(ptr != tail) {
		file.write(reinterpret_cast<const char*> (&(ptr -> value)), sizeof(T));
		ptr = ptr -> next;
	}
}

```

#### map

目前尚未完成, 请暂缓调用!
map容器, 基本同STLite标准要求, 文件操作相关接口如下

| return type | method | description |
|:----------:|:---------------:|:----------:|
| void | readIn(std::ifstream &file) | 从file读入数据 |
| void | writeOut(std::ofstream &file) | 向file写入数据 |


#### log

系统日志类, 针对系统日志文件进行操作

| return type | method | description |
|:----------:|:---------------:|:----------:|
| / | log() | 默认构造 |
| void | open(const std::string &_fileName) | 打开_fileName且不清除内容 |
| void | close() | 关闭文件且不清除内容 |
| void | clear() | 清除文件内容 |
| friend std::ostream & | operator<<(std::ostream &os, log &lg) | 输出日志内容 |
| void | add(const std::string &str) | 向日志末尾新行添加语句str |

#### timer

时间类, 用于处理时间相关的问题

| return type | method | description |
|:----------:|:---------------:|:----------:|
| / | timer(int _yy = 0, int _mm = 0, int _dd = 0, int _hh = 0, int _ss = 0) | 构造函数 其中ss表示分 |
| friend std::istream & | operator>>(std::istream &is, timer &obj) | 输入时间信息 有输入提示 |
| friend std::ostream & | operator<<(std::ostream &os, const timer &obj) | 按 yy/mm/dd hh:ss 的格式输出时间信息 |
| timer | operator-(const timer &other) const | 输出两时间差 若差不为正则 throw invalid_time_interval() 且通常只能在差的范围为天数级别时得到正确答案 |
| bool | operator==(const timer &other) const | 比较函数 |
| bool | operator<(const timer &other) const | 比较函数 |
| bool | operator>(const timer &other) const | 比较函数 |
| bool | operator<=(const timer &other) const | 比较函数 |
| bool | operator>=(const timer &other) const | 比较函数 |

#### vector

目前尚未完成, 请暂缓调用!
vector容器, 基本同STLite标准要求, 文件操作相关接口如下

| return type | method | description |
|:----------:|:---------------:|:----------:|
| void | readIn(std::ifstream &file) | 从file读入数据 |
| void | writeOut(std::ofstream &file) | 向file写入数据 |


## 模版函数

#### rwString

从或向文件流读入或写出string类变量

| return type | method |
|:----------:|:---------------:|
| void | readString(std::ifstream &file, std::string &str) |
| void | writeString(std::ofstream &file, const std::string &str) |

#### getPath

提取某运行程序所在文件夹路径

| return type | method |
|:----------:|:---------------:|
| std::string | getPath(const std::string &fileName) |

使用方法:
```cpp
#include <string>
#include "getPath.hpp"

int main(int argc, char *argv[]) {
	std::string fileName = sjtu::getPath(argv[0]) + "fileName";
	// 假若该程序路径为 D:\ab\test.exe 则 fileName 为 "D:\ab\fileName" 即同目录下文件
}
```
