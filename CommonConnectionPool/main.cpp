#include "pch.h"
#include <iostream>
#include "public.h"
#include "Connection.h"
#include "CommonConnectionPool.h"
using namespace std;

//ʹ�����ӳصĲ��Ժ���
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
//��ʹ�����ӳصĲ��Ժ���
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
	//��ǰ����һ��MYSQL����������Ȼ��������ͬһ�û�ͬʱ���Ӷ�ζ�����
	Connection conn;
	if (!conn.connect("127.0.0.1", 3306, "root", "123456", "chat")) {
		//cout << (mysql_error(&mysql));//�������ԭ��
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
	//���̲߳��Դ���
	ConnectionPool* cp = ConnectionPool::getConnectionPool();
	for (int i = 0; i < 1000; ++i)
	{
		//δʹ�����ӳ�
		/*Connection conn;
		char sql[1024] = { 0 };
		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
			"zhang san", 20, "male");
		conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
		conn.update(sql);*/

		//ʹ�����ӳ�
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
