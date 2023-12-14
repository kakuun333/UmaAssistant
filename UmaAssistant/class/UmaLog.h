#pragma once

#include <iostream>
#include <fstream>
#include <utility>

class UmaLog
{
private:
	UmaLog() {}

	static UmaLog* _instance;

	static std::fstream _file;

	// パラメータパックが空になったら終了
	void print()
	{
		// 換行
		std::cout << std::endl;

		// 寫入換行
		_file << std::endl;

		// 刷新寫入的內容
		_file.flush();
	}

public:
	static UmaLog* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new UmaLog();
		}

		return _instance;
	}

	static void init(std::string logFilePath)
	{
		if (_file.is_open()) return;

		// 先刪除之前的 UmaLog.txt
		std::ifstream file(logFilePath);
		if (file.good())
		{
			file.close();
			std::remove(logFilePath.c_str());
		}


		// 設置成　out | append
		_file = std::fstream(logFilePath, std::ios::out | std::ios::app);
	}

	static void close()
	{
		if (_file.is_open())
			_file.close();
	}

	// https://cpprefjp.github.io/lang/cpp11/variadic_templates.html
	// ひとつ以上のパラメータを受け取るようにし、
	// 可変引数を先頭とそれ以外に分割する
	template<typename Head, typename... Tail>
	void print(Head&& head, Tail&&... tail)
	{
		// 輸出 head
		std::cout << std::forward<Head>(head) << ' ';

		// 把 head 寫入到 _file 裡面。
		_file << std::forward<Head>(head) << ' ';

		// パラメータパックtailをさらにheadとtailに分割する
		print(std::forward<Tail>(tail)...);
	}


	// 利用可變參數模板接收任意數量的參數並將其輸出到 std::ostream
	//template<typename... Args>
	//void print(const Args&&... args)
	//{
	//	//std::ostringstream oss;
	//	//printArgs(oss, args...);

	//	//// 輸出到標準輸出
	//	//std::cout << oss.str() << std::endl;

	//	//// 寫入到文件
	//	//_file << oss.str() << std::endl;

	//	//// 刷新
	//	//_file.flush();
	//}

};