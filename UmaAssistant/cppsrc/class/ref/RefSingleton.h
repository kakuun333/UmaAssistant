#pragma once

generic<typename T>
ref class RefSingleton
{
public:
	static property T Instance { T get() { return _instance; } }
protected:
	RefSingleton() {}
	RefSingleton(const RefSingleton%) { throw gcnew System::InvalidOperationException("singleton cannot be copy-constructed"); }
private:
	static T _instance;
};

