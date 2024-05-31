#include <string>
#include <vector>

class dir_parser
{
public:
  /* возвращает вектор директорий и файлов, находящихся по абсолютному пути 'path'*/
  static std::vector<std::string> getDirs(const std::string &path);
  /* возвращает директорию, из которой была запущена программа */
  static std::string getPath();

  /* вывод директорий */
  static void printVec(const std::vector<std::string> &vec);

  /* файловый поисковик */
  static std::string browseFiles(const std::string &path);
};
