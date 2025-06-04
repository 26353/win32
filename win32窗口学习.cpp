#define _UNICODE
#define UNICODE
#include <windows.h>
#include <stdio.h>

HANDLE g_hOutput = 0; // 接收标准输出句柄

void oncreate(HWND hWnd, LPARAM IParam)
{
    CREATESTRUCT *pcs = (CREATESTRUCT *)IParam;
    TCHAR *pszText = (TCHAR *)pcs->lpCreateParams;
    MessageBox(NULL, pszText, TEXT("Infor"), MB_OK);
} // 窗口创建时弹窗提醒

void OnPaint(HWND hWnd)
{
    wchar_t *pszText = (wchar_t *)L"WM_PAINT\n";
    // 使用宽字符版本的WriteConsoleW
    if (!WriteConsoleW(g_hOutput, pszText, wcslen(pszText), NULL, NULL))
    {
        fwprintf(stderr, L"WriteConsoleW 失败，错误码：%d\n", GetLastError());
    }
} // 处理绘图的函数

void Onkeydown(HWND hWnd, WPARAM wParam)
{
    wchar_t szText[265] = {0};
    swprintf_s(szText, TEXT("WM_KEYDOWN:键码值 %d\n"), wParam);
    DWORD dwBytesWritten;

    if (!WriteConsoleW(g_hOutput, szText, wcslen(szText), &dwBytesWritten, NULL)) // 使用宽字符版本的WriteConsoleW
    {
        fwprintf(stderr, L"WriteConsoleW 失败，错误码：%d\n", GetLastError());
    }
}

void Onkeyup(HWND hWnd, WPARAM wParam)
{
    wchar_t szText[265] = {0};
    swprintf_s(szText, TEXT("WM_KEYUP:键码值 %d\n"), wParam);
    DWORD dwBytesWritten;

    if (!WriteConsoleW(g_hOutput, szText, wcslen(szText), &dwBytesWritten, NULL)) // 使用宽字符版本的WriteConsoleW
    {
        fwprintf(stderr, L"WriteConsoleW 失败，错误码：%d\n", GetLastError());
    }
}

// 窗口处理函数（自定义，处理消息）
void onsize(HWND hWnd, LPARAM IParam)
{
    short nWidth = LOWORD(IParam);
    short nHight = HIWORD(IParam);
    wchar_t szText[256] = {0};
    swprintf_s(szText, TEXT("宽: %d 高: %d\n"), nWidth, nHight); // 使用宽字符格式化函数
    DWORD dwBytesWritten;

    if (!WriteConsoleW(g_hOutput, szText, wcslen(szText), &dwBytesWritten, NULL)) // 使用宽字符版本的WriteConsoleW
    {
        fwprintf(stderr, L"WriteConsoleW 失败，错误码：%d\n", GetLastError());
    }
}

void Onchar(HWND hWnd, WPARAM wParam)
{
    wchar_t szText[265] = {0};
    swprintf_s(szText, TEXT("WM_CHAR:wParam= %d\n"), wParam);

    if (!WriteConsoleW(g_hOutput, szText, wcslen(szText), NULL, NULL)) // 使用宽字符版本的WriteConsoleW
    {
        fwprintf(stderr, L"WriteConsoleW 失败，错误码：%d\n", GetLastError());
    }
}

void OnLbuttondown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    wchar_t szText[256] = {0};
    swprintf_s(szText, TEXT("WM_LBUTTONDOWN:wParam= %d,其他按键状态：x=%d,y=%d\n"), wParam, LOWORD(lParam), HIWORD(lParam));

    if (!WriteConsoleW(g_hOutput, szText, wcslen(szText), NULL, NULL)) // 使用宽字符版本的WriteConsoleW
    {
        fwprintf(stderr, L"WriteConsoleW 失败，错误码：%d\n", GetLastError());
    }
}

void OnRbuttondown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    wchar_t szText[256] = {0};
    swprintf_s(szText, TEXT("WM_RBUTTONDOWN:wParam= %d,其他按键状态：x=%d,y=%d\n"), wParam, LOWORD(lParam), HIWORD(lParam));

    if (!WriteConsoleW(g_hOutput, szText, wcslen(szText), NULL, NULL)) // 使用宽字符版本的WriteConsoleW
    {
        fwprintf(stderr, L"WriteConsoleW 失败，错误码：%d\n", GetLastError());
    }
}

void Onmousemove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    wchar_t szText[256] = {0};
    swprintf_s(szText, TEXT("WM_MOUSEMUVE 键值= %d,其他按键状态：x=%d,y=%d\n"), wParam, LOWORD(lParam), HIWORD(lParam));

    if (!WriteConsoleW(g_hOutput, szText, wcslen(szText), NULL, NULL)) // 使用宽字符版本的WriteConsoleW
    {
        fwprintf(stderr, L"WriteConsoleW 失败，错误码：%d\n", GetLastError());
    }
}

void Onlbuttondblclk(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    wchar_t szText[256] = {0};
    swprintf_s(szText, TEXT("WM_LBUTTONDBLCLK 键值= %d,其他按键状态：x=%d,y=%d\n"), wParam, LOWORD(lParam), HIWORD(lParam));

    if (!WriteConsoleW(g_hOutput, szText, wcslen(szText), NULL, NULL)) // 使用宽字符版本的WriteConsoleW
    {
        fwprintf(stderr, L"WriteConsoleW 失败，错误码：%d\n", GetLastError());
    }
}

void Onmousewheel(HWND hWnd, WPARAM wParam)
{
    short nDelta = HIWORD(wParam); // 偏移量低位是按键
    wchar_t szText[256] = {0};
    swprintf_s(szText, TEXT("WM_MOUSEWHEEL:nDetal=%d\n"), nDelta);
    if (!WriteConsoleW(g_hOutput, szText, wcslen(szText), NULL, NULL)) // 使用宽字符版本的WriteConsoleW
    {
        fwprintf(stderr, L"WriteConsoleW 失败，错误码：%d\n", GetLastError());
    }
}

void Ontimer(HWND hWnd, WPARAM wParam)
{
    wchar_t szText[256] = {0};
    swprintf_s(szText, TEXT("WM_TIMER wParam=%d\n"), wParam);
    if (!WriteConsoleW(g_hOutput, szText, wcslen(szText), NULL, NULL)) // 使用宽字符版本的WriteConsoleW
    {
        fwprintf(stderr, L"WriteConsoleW 失败，错误码：%d\n", GetLastError());
    }
}

// 消息和队列的关系
// 1.当鼠标、键盘产生消息时，会将消息存放到系统消息队列
// 2.系统会根据存放的消息，找到对应的消息队列。
// 将消息投递到程序的消息队列中
// 根据消息和消息队列之间使用关系，将消息分成两类：
// 队列消息-消息的发送和获取，都是通过消息队列完成。
// 非队列消息-消息的发送和获取，是直接调用消息的窗口处理完成。

LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
    switch (msgID)
    {
    case WM_KEYDOWN:
        Onkeydown(hWnd, wParam);
        return 3;
        // 键盘按下消息
    case WM_KEYUP:
        Onkeyup(hWnd, wParam);
        return 4;
        // 键盘松开消息
    case WM_CHAR:
        Onchar(hWnd, wParam);
        return 5;
    // 字符串消息（可见字符）
    //  普通键盘按键按下
    //   case WM_SYSKEYDOWN:
    //   case WM_SYSKEYUP:
    //  系统按键按下（如alt、F10）
    case WM_LBUTTONDOWN:
        OnLbuttondown(hWnd, wParam, lParam);
        return 6;
    // 鼠标左键按下消息
    case WM_RBUTTONDOWN:
        OnRbuttondown(hWnd, wParam, lParam);
        return 7;
    // 鼠标右键按下消息
    // case WM_MOUSEMOVE:
    //     Onmousemove(hWnd, wParam, lParam);
    //     return 8;
    // 鼠标移动时产生的消息（移动的慢产生的多）
    case WM_LBUTTONDBLCLK:
        Onlbuttondblclk(hWnd, wParam, lParam);
        return 9;
    // 左键双击消息
    //  消息产生顺序（以左键双击为例）
    //  WM_BUTTONDOWN
    //  WM_BUTTONUP
    //  WM_BUTTONDBLCLK
    //  WM_BUTTONUP
    //  使用时需要在注册窗口类的时候添加CS_DBLCLKS风格
    case WM_MOUSEWHEEL:
        Onmousewheel(hWnd, wParam);
        return 10;
    // 鼠标滚动时产生的消息
    case WM_TIMER:
        Ontimer(hWnd, wParam);
    case WM_SIZE: // 当窗口大小发生变换时产生的消息
        onsize(hWnd, lParam);
        return 0;
    case WM_PAINT:
        OnPaint(hWnd);
        return DefWindowProc(hWnd, msgID, wParam, lParam);
    // 当窗口需要绘制时产生的消息（size消息也会产生paint消息）
    // case WM_LBUTTONDOWN:
    //     InvalidateRect(hWnd, NULL, TRUE);
    //     return 2;
    // 鼠标左键被按下时的消息
    case WM_CREATE:
        oncreate(hWnd, lParam);
        SetTimer(hWnd, 1, 1000, NULL);
        SetTimer(hWnd, 2, 2000, NULL);
        return 1;
    // 窗口创建成功但未显示时的消息
    case WM_DESTROY:
        // PostQuitMessage(0); // 可以使GetMessage函数返回0
        PostMessage(hWnd, WM_QUIT, 0, 0);
        // SendMessage-发送消息（不进入消息队列，所以不能被GetMessage抓到），会等候消息处理结果。（阻塞函数，直接调用消息处理函数）
        // PostMessage-投递消息，消息发出后立刻返回，不等候消息执行结果。（进入消息队列）
        return -1;
    case WM_SYSCOMMAND:         // 最大、最小、关闭窗口消息
        if (wParam == SC_CLOSE) // 如果是关闭窗口消息
        {
            int nRet = MessageBox(hWnd, TEXT("是否退出"), TEXT("Infor"), MB_YESNO); // 询问用户是否退出
            if (nRet == IDYES)
            {
                KillTimer(hWnd, 1);
                KillTimer(hWnd, 2);
            }
            else
            {
                return 0;
            }
        }
        return DefWindowProc(hWnd, msgID, wParam, lParam);
    default:
        return DefWindowProc(hWnd, msgID, wParam, lParam); // 给各种消息默认处理
    }
}

// 消息处理函数要写return,否则可能导致未定义行为
//  WM_QUIT消息不进入消息处理函数，不需要程序员处理，消息循环一旦接收到这个消息，返回值为零，结束消息循环（由程序员发送）
// 鼠标类消息：
// 基本鼠标消息
// WM_LBUTTONDONWN-鼠标左键按下
// WM_LBUTTONUP-鼠标左键抬起
// WM_RBUTTONDOWN-鼠标右键按下
// WM_RBUTTONUP-鼠标右键抬起
// WM_MOUSEMOVE-鼠标移动消息
// 双击消息
// WM_LBUTTONBLCLK-鼠标左键双击
// WM_RBUTTONBLCLK-鼠标右键双击
// 滚轮消息
// WM_MOUSEWHEEL-鼠标滚轮消息

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR ipcmdline, int nCmdShow)
{
    AllocConsole(); // 增加DOS
    g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    WNDCLASS wc = {0};
    wc.cbClsExtra = 0;                               // 类的附加缓冲区
    wc.cbWndExtra = 0;                               // 窗口的附加缓冲区
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);   // 绘制窗口的画刷句柄
    wc.hCursor = NULL;                               // 鼠标的句柄
    wc.hIcon = NULL;                                 // 窗口图标句柄
    wc.hInstance = hInstance;                        // 当前模块的实例句柄
    wc.lpfnWndProc = WndProc;                        // 窗口处理函数
    wc.lpszClassName = TEXT("test");                 // 窗口类的名称
    wc.lpszMenuName = NULL;                          // 窗口菜单的资源ID字符串
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; // 窗口类风格
    RegisterClass(&wc);                              // 将以上所有赋值写入操作系统。（注册窗口）

    TCHAR *pszText = TEXT("hello data");
    // 创建窗口
    HWND hWnd = CreateWindowEx(0, TEXT("test"), TEXT("window"), WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hInstance, pszText);

    // /**
    //  * @brief 子窗口
    //  *
    //  */
    // wc.cbClsExtra = 0;                             // 类的附加缓冲区
    // wc.cbWndExtra = 0;                             // 窗口的附加缓冲区
    // wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 绘制窗口的画刷句柄
    // wc.hCursor = NULL;                             // 鼠标的句柄
    // wc.hIcon = NULL;                               // 窗口图标句柄
    // wc.hInstance = hInstance;                      // 当前模块的实例句柄
    // wc.lpfnWndProc = DefWindowProc;                // 窗口处理函数,丢给windows默认程序处理
    // wc.lpszClassName = TEXT("Child");              // 窗口类的名称
    // wc.lpszMenuName = NULL;                        // 窗口菜单的资源ID字符串
    // wc.style = CS_HREDRAW | CS_VREDRAW;            // 窗口类风格
    // RegisterClass(&wc);                            // 将以上所有赋值写入操作系统。（注册窗口）

    // HWND hChild1 = CreateWindowEx(0, TEXT("Child"), TEXT("c1"), WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, 0, 0, 200, 200, hWnd, NULL, hInstance, NULL);
    // HWND hChild2 = CreateWindowEx(0, TEXT("Child"), TEXT("c2"), WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, 0, 0, 200, 200, hWnd, NULL, hInstance, NULL);

    // 显示窗口
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    MSG nMsg = {0};
    // 消息循环
    // while (GetMessage(&nMsg, NULL, 0, 0))
    // {
    //     TranslateMessage(&nMsg);
    //     DispatchMessage(&nMsg); // 将消息交给窗口处理函数来处理
    // }

    while (1)
    {
        if (PeekMessage(&nMsg, NULL, 0, 0, PM_NOREMOVE))
        {
            if (GetMessage(&nMsg, NULL, 0, 0))
            {
                TranslateMessage(&nMsg);
                DispatchMessage(&nMsg);
            }
            else
            {
                break;
            }
        }
    }
    // GetMessage-从系统获取消息，将消息从系统中移除，阻塞函数。当系统无消息时，会等候下一条消息。
    // PeekMessage-以查看的方式从系统获取消息，可以不将消息从系统移除，非阻塞函数。当系统无消息时，返回FALSE，继续执行后续代码。
    /*BOOL PeekMessage(){
    LPMSG lpMsg,//message information
    HWND hWnd,//handle to window
    UINT wMsgFilterMin,//first message
    UINT wMsgFilterMax,//last message
    UINT wRemoveMsg//移除标识
    PM_REMOVE/PM_NOREMOVE
    }
    */
    return 0;
}
// 菜单分类
// 窗口的顶部菜单
// 弹出式菜单
// 系统菜单
// HMENU类型表示菜单，ID表示菜单项