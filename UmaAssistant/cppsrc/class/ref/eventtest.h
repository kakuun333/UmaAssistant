#pragma once
using namespace System;

// �w�q�@�өe��(delegate)�A���N�Χ@�^��(callback)������
public delegate System::String^ MyCallbackDelegate(int result);

// �w�q�@�����A�䤤�]�t�@�Ө�ơA�������e��(delegate)�@���Ѽƨýեθөe��(delegate)
public ref class eventtest
{
public:
    // ��Ʊ����e��(delegate)�@���ѼơA�ñN��@���^��(callback)�ե�
    void perform(MyCallbackDelegate^ callback)
    {
        // �����Y�ؾާ@�A�o�̨ϥΤ@���H���Ƨ@�����G
        Random^ rand = gcnew Random();
        int result = rand->Next(100);

        // �եΦ^��(callback)�A�N���G�ǻ����^��(callback)
        callback(result);
    }
};