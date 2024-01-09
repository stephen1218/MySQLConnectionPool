#include "pch.h"
#include <iostream>
#include "public.h"
#include "Connection.h"
#include "CommonConnectionPool.h"
using namespace std;

//使用连接池的测试函数
void test01(int connNum) {
	ConnectionPool *cp = ConnectionPool::getConnectionPool();
	for (int i = 0; i < connNum; ++i)
	{
		char sql[1024] = { 0 };
		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
			"zhang san", 20, "male");
		shared_ptr<Connection> sp = cp->getConnection();
		sp->update(sql);
	}
}
//不使用连接池的测试函数
void test02(int connNum) {
	for (int i = 0; i < connNum; ++i)
	{
		Connection conn;
		char sql[1024] = { 0 };
		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
			"zhang san", 20, "male");
		conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
		conn.update(sql);
	}
}

int main()
{
	//提前连接一下MYSQL服务器，不然可能由于同一用户同时连接多次而报错
	Connection conn;
	if (!conn.connect("127.0.0.1", 3306, "root", "123456", "chat")) {
		//cout << (mysql_error(&mysql));//输出错误原因
		return -1;
	}
	
	clock_t begin = clock();

	thread t1(test01, 250);
	thread t2(test01, 250);
	thread t3(test01, 250);
	thread t4(test01, 250);
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();

	clock_t end = clock();
	cout << (end - begin) << "ms" << endl;


#if 0
	//单线程测试代码
	ConnectionPool* cp = ConnectionPool::getConnectionPool();
	for (int i = 0; i < 1000; ++i)
	{
		//未使用连接池
		/*Connection conn;
		char sql[1024] = { 0 };
		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
			"zhang san", 20, "male");
		conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
		conn.update(sql);*/

		//使用连接池
		shared_ptr<Connection> sp = cp->getConnection();
		char sql[1024] = { 0 };
		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
			"zhang san", 20, "male");
		sp->update(sql);
	}
	clock_t end = clock();
	cout << (end - begin) << "ms" << endl;
#endif
	return 0;
}
