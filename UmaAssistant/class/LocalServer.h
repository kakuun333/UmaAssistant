#pragma once
public ref class LocalServer
{

private:
	LocalServer() {}
	LocalServer(const LocalServer%) { throw gcnew System::InvalidOperationException(u8"��@�Ҧ����i�H���ƻs�غc�l�Csingleton cannot be copy-constructed"); }
	static LocalServer _instance;


	void StartLocalServer(Object^ port);


	void HandleUmaWebRequest(Object^ obj);
public:
	static property LocalServer^ Instance { LocalServer^ get() { return % _instance; } }

	void Start(System::String^ port);
};
