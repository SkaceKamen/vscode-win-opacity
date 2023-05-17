#include <napi.h>
#include <windows.h>
#include <vector>
#include <iostream>

namespace win_opacity
{
  std::vector<HWND> windowsList;

  void setWindowsOpacity(HWND hwd, BYTE alpha)
  {
    LONG windowLong = GetWindowLongA(hwd, GWL_EXSTYLE);
    SetWindowLongA(hwd, GWL_EXSTYLE, windowLong | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hwd, 0, alpha, LWA_ALPHA);
  }

  BOOL CALLBACK enumWindowsProc(
      __in HWND hWnd,
      __in LPARAM lParam)
  {
    int len = GetWindowTextLengthA(hWnd);
    char *title = (char *)malloc((len + 1) * sizeof(char));
    GetWindowTextA(hWnd, title, len + 1);

    if (strstr(title, " - Visual Studio Code") != NULL)
    {
      windowsList.push_back(hWnd);
    }

    free(title);

    return TRUE;
  }

  void applyAlpha(BYTE alpha)
  {
    windowsList.clear();
    EnumWindows(enumWindowsProc, 0);

    for (auto it : windowsList)
    {
      setWindowsOpacity(it, alpha);
    }

    windowsList.clear();
  }

  Napi::Value ApplyAlpha(const Napi::CallbackInfo &info)
  {
    Napi::Env env = info.Env();

    if (info.Length() < 1)
    {
      Napi::TypeError::New(env, "Wrong number of arguments")
          .ThrowAsJavaScriptException();

      return env.Undefined();
    }

    if (!info[0].IsNumber())
    {
      Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();

      return env.Undefined();
    }

    int32_t alpha = info[0].As<Napi::Number>().Int32Value();

    applyAlpha(alpha);

    return env.Undefined();
  }

  Napi::Object Init(Napi::Env env, Napi::Object exports)
  {
    exports.Set(Napi::String::New(env, "applyAlpha"), Napi::Function::New(env, ApplyAlpha));
    return exports;
  }

  NODE_API_MODULE(addon, Init)
}
