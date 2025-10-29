#include "screenshot.h"
#include <windows.h>
#include <gdiplus.h>
#include <thread>
#include <chrono>

void TakeScreenshot() {
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    HDC hdcScreen = GetDC(NULL);
    HDC hdcMem = CreateCompatibleDC(hdcScreen);
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, width, height);
    SelectObject(hdcMem, hBitmap);
    BitBlt(hdcMem, 0, 0, width, height, hdcScreen, 0, 0, SRCCOPY);

    CLSID pngClsid;
    GetEncoderClsid(L"image/png", &pngClsid);
    Gdiplus::Bitmap bitmap(hBitmap, NULL);
    bitmap.Save(L"C:\\Users\\Public\\screenshot.png", &pngClsid, NULL);

    DeleteObject(hBitmap);
    DeleteDC(hdcMem);
    ReleaseDC(NULL, hdcScreen);
    Gdiplus::GdiplusShutdown(gdiplusToken);
}

void StartScreenshotThread() {
    std::thread([]() {
        while (true) {
            TakeScreenshot();
            std::this_thread::sleep_for(std::chrono::minutes(5));
        }
    }).detach();
}
