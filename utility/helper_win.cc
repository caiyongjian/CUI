// utf-8 encodings.

#include "../utility/helper.h"

#include <Windows.h>

HMODULE GetModuleFromAddress(void* address) {
  HMODULE instance = NULL;
  if (!::GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                            static_cast<char*>(address),
                            &instance)) {
    NOREACHED();
  }
  return instance;
}
