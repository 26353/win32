#define _UNICODE
#define UNICODE
#include <windows.h>
#include <stdio.h>

HANDLE g_hOutput = 0; // 接收标准输出句柄

// 窗口处理函数（自定义，处理消息）
void oncreate(HWND hWnd, LPARAM IParam)
{
    CREATESTRUCT *pcs = (CREATESTRUCT *)IParam;
    TCHAR *pszText = (TCHAR *)pcs->lpCreateParams;
    MessageBox(NULL, pszText, TEXT("Infor"), MB_OK);
}
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM IParam)
{
    switch (msgID)
    {
    case WM_SIZE: // 当窗口大小发生变换时产生的消息
        onsize(hWnd, IParam);
        break;
    // case WM_CREATE: // 窗口创建成功但未显示时的消息
    //     oncreate(hWnd, IParam);
    //     break;
    case WM_DESTROY:
        // PostQuitMessage(0); // 可以使GetMessage函数返回0
        PostMessage(hWnd, WM_QUIT, 0, 0);
        break;
    case WM_SYSCOMMAND:         // 最大、最小、关闭窗口消息
        if (wParam == SC_CLOSE) // 如果是关闭窗口消息
        {
            int nRet = MessageBox(hWnd, TEXT("是否退出"), TEXT("Infor"), MB_YESNO); // 询问用户是否退出
            if (nRet == IDYES)
            {
            }
            else
            {
                return 0;
            }
        }
        return DefWindowProc(hWnd, msgID, wParam, IParam);
        break;
    default:
        return DefWindowProc(hWnd, msgID, wParam, IParam); // 给各种消息默认处理
    }
}
// WM_QUIT消息不进入消息处理函数，不需要程序员处理，消息循环一旦接收到这个消息，返回值为零，结束消息循环（由程序员发送）

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR ipcmdline, int nCmdShow)
{
    AllocConsole(); // 增加DOS
    g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    WNDCLASS wc = {0};
    wc.cbClsExtra = 0;                             // 类的附加缓冲区
    wc.cbWndExtra = 0;                             // 窗口的附加缓冲区
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 绘制窗口的画刷句柄
    wc.hCursor = NULL;                             // 鼠标的句柄
    wc.hIcon = NULL;                               // 窗口图标句柄
    wc.hInstance = hInstance;                      // 当前模块的实例句柄
    wc.lpfnWndProc = WndProc;                      // 窗口处理函数
    wc.lpszClassName = TEXT("test");               // 窗口类的名称
    wc.lpszMenuName = NULL;                        // 窗口菜单的资源ID字符串
    wc.style = CS_HREDRAW | CS_VREDRAW;            // 窗口类风格
    RegisterClass(&wc);                            // 将以上所有赋值写入操作系统。（注册窗口）

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