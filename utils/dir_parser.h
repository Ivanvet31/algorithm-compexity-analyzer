#include <string>
#include <vector>

/* возвращает вектор директорий и файлов, находящихся по абсолютному пути 'path'*/
std::vector<std::string> getDirs(const std::string &path);

/* возвращает директорию, из которой была запущена программа */
std::string getPath();

/* вывод директорий */
void printVec(const std::vector<std::string> &vec);