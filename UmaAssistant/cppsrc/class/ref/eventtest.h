#pragma once
using namespace System;

// 定義一個委派(delegate)，它將用作回調(callback)的類型
public delegate System::String^ MyCallbackDelegate(int result);

// 定義一個類，其中包含一個函數，它接受委派(delegate)作為參數並調用該委派(delegate)
public ref class eventtest
{
public:
    // 函數接受委派(delegate)作為參數，並將其作為回調(callback)調用
    void perform(MyCallbackDelegate^ callback)
    {
        // 模擬某種操作，這裡使用一個隨機數作為結果
        Random^ rand = gcnew Random();
        int result = rand->Next(100);

        // 調用回調(callback)，將結果傳遞給回調(callback)
        callback(result);
    }
};