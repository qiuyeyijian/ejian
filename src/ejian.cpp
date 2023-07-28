#include "ejian/ejian.h"
#include<sys/stat.h>
#if EJIAN_API_WINDOWS
#include<direct.h>
#endif

namespace ejian {
namespace utils {
int mkdir(const char* path, mode_t mode) {
  int res = 0;
#if EJIAN_API_WINDOWS
  res = _mkdir(path);
#else
  res = mkdir(path, mode);
#endif
  return res;
}
int mkdirs(const char* path, mode_t mode) {
  char* p = NULL;
  char* tmp = strdup(path);
  int res = 0;

  if (NULL == tmp) {
    return -1;
  }

  p = tmp;
  while (*p && res == 0) {
    if (*p == '/' || *p == '\\') {
      *p = '\0';
      res = ejian::utils::mkdir(tmp, mode);
      *p = '/';
    }
    p++;
  }

  if (res == 0) {
    res = ejian::utils::mkdir(tmp, mode);
  }

  free(tmp);
  return res;
}

}
}  // namespace ejian
