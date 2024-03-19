#include <iostream>
#include <napi.h>
#include <regex>
#include <vector>
#include <windows.h>

namespace win_opacity {
std::vector<HWND> windowsList;

void setWindowsOpacity(HWND hwd, BYTE alpha) {
  LONG windowLong = GetWindowLongA(hwd, GWL_EXSTYLE);
  SetWindowLongA(hwd, GWL_EXSTYLE, windowLong | WS_EX_LAYERED);
  SetLayeredWindowAttributes(hwd, 0, alpha, LWA_ALPHA);
}

BOOL CALLBACK enumWindowsProc(__in HWND hWnd, __in LPARAM lParam) {
  DWORD pid = -1;
  GetWindowThreadProcessId(hWnd, &pid);
  if (pid != -1) {
    auto process =
        OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, TRUE, pid);
    if (process != INVALID_HANDLE_VALUE) {
      std::wstring path;
      path.resize(MAX_PATH);
      DWORD len = MAX_PATH;
      if (QueryFullProcessImageNameW(process, 0, path.data(), &len) != 0) {
        path.resize(len);
        CloseHandle(process);
        std::wstring path_c;
        path_c.resize(MAX_PATH);
        DWORD len_c = MAX_PATH;
        if (QueryFullProcessImageNameW(GetCurrentProcess(), 0, path_c.data(),
                                       &len_c) != 0) {
          path_c.resize(len_c);
          if (path_c == path)
            windowsList.push_back(hWnd);
        }
      }
    }
  }
  return TRUE;
}

void applyAlpha(BYTE alpha) {
  windowsList.clear();
  EnumWindows(enumWindowsProc, 0);

  for (auto it : windowsList) {
    setWindowsOpacity(it, alpha);
  }

  windowsList.clear();
}

Napi::Value ApplyAlpha(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();

    return env.Undefined();
  }

  if (!info[0].IsNumber()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();

    return env.Undefined();
  }

  int32_t alpha = info[0].As<Napi::Number>().Int32Value();

  applyAlpha(alpha);

  return env.Undefined();
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "applyAlpha"),
              Napi::Function::New(env, ApplyAlpha));
  return exports;
}

NODE_API_MODULE(addon, Init)
} // namespace win_opacity
