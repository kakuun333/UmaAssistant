//#include "DesktopDuplication.h"
//
//HRESULT DesktopDuplication::GetFrame()
//{
//    IDXGIOutputDuplication* pDesktopDuplication = nullptr;
//
//    // 初始化 DXGI 介面
//    IDXGIFactory2* pFactory = nullptr;
//    CreateDXGIFactory1(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&pFactory));
//
//    // 獲取主顯示器
//    IDXGIOutput1* pOutput = nullptr;
//    pFactory->EnumAdapters1(0, &pAdapter);
//    pAdapter->EnumOutputs(0, &pOutput);
//
//    // 使用 DXGI 1.2
//    IDXGIOutputDuplication* pDuplication = nullptr;
//    pOutput->DuplicateOutput(pDevice, &pDuplication);
//
//
//
//    return hr;
//}