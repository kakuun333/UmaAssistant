#pragma once
class Scanner
{
private:
	Scanner();

	static Scanner* _instance;
public:
	static Scanner& GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new Scanner();
		}
		return *_instance;
	}

	System::String^ Scan(const char* imgPath, const char* language = "jpn");
};

