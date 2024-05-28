#include "translation.h"

#include "constructions.h"
#include "types/types.h"
#include <fstream>
#include <iostream>
#include <stack>

std::unordered_map<std::string, size_t> type_sizes{
  { "char", sizeof(char) },   { "int", sizeof(int) },
  { "short", sizeof(short) }, { "long", sizeof(long) },
  { "float", sizeof(float) }, { "double", sizeof(double) }
};

const std::vector<std::string> types_keywords
    = { "char", "unsigned", "short",  "int", "char",
        "long", "float",    "double", "void" };

const std::vector<std::string> keywords = {
  "auto",   "break",  "case",    "char",  "const",    "continue", "default",
  "do",     "double", "else",    "enum",  "extern",   "float",    "for",
  "goto",   "if",     "int",     "long",  "register", "return",   "short",
  "signed", "sizeof", "static",  "(",     ")",        "{",        "}",
  "struct", "switch", "typedef", "union", "unsigned", "void",     "volatile",
  "while",  ",",      ";",       "+",     "-",        "*",        "/",
  "&&",     "||",     "&",       "|",     "=",        "[",        "]"
};

bool
isKeyword(const std::string &word)
{
  if (std::find(keywords.begin(), keywords.end(), word) == keywords.end())
    {
      for (char const &c : word)
        if (!std::isdigit(c))
          return false;
    }
  return true;
}

std::vector<std::string>
splitIntoWords(const std::string &line)
{
  std::vector<std::string> words;
  std::string word;
  for (size_t i = 0; i < line.length(); ++i)
    {
      char ch = line[i];
      if (std::isalnum(ch) || ch == '_')
        word += ch;
      else
        {
          if (!word.empty())
            {
              words.push_back(word);
              word.clear();
            }
          if (std::ispunct(ch))
            {
              if (ch == '&' || ch == '|')
                {
                  if (i + 1 < line.length() && line[i + 1] == ch)
                    {
                      words.push_back(std::string(1, ch) + ch);
                      ++i;
                    }
                  else
                    words.push_back(std::string(1, ch));
                }
              else if (ch == '=' || ch == '!' || ch == '<' || ch == '>')
                {
                  if (i + 1 < line.length() && line[i + 1] == '=')
                    {
                      words.push_back(std::string(1, ch) + '=');
                      ++i;
                    }
                  else
                    words.push_back(std::string(1, ch));
                }
              else
                words.push_back(std::string(1, ch));
            }
        }
    }
  if (!word.empty())
    words.push_back(word);
  return words;
}

Translation::
Translation(
    const std::vector<std::string> &,
    const std::vector<std::unordered_map<std::string, std::string> > &options)
    : pool(20), undefined_funcs()
{

  std::mutex mutex;

  std::string filename
      = "/home/KiberPerdun/CLionProjects/algorithm-compexity-analyzer/test.c";

  std::ifstream file(filename);
  if (!file.is_open())
    {
      std::cerr << "Не могу открыть файл " << filename
                << " для чтения, братан, жесть\n";
      return;
    }

  std::string line;
  std::vector<std::string> foundKeywords;
  std::stack<char> bracesStack;

  // читаем строки из файла
  while (std::getline(file, line))
    {
      // разбиваем строку на слова
      std::vector<std::string> words = splitIntoWords(line);

      // проверяем каждое слово, ключевое ли оно
      for (const std::string &word : words)
        {
          foundKeywords.push_back(word);
        }

      for (char ch : line)
        {
          if (ch == '{')
            bracesStack.push(ch);
          else if (ch == '}')
            {
              if (!bracesStack.empty())
                bracesStack.pop();
            }
        }
    }

  file.close();

  // выводим найденные ключевые слова
  std::cout << "Найденные ключевые слова в файле " << filename << ":\n";
  for (const std::string &keyword : foundKeywords)
    {
      if (keyword == ";")
        std::cout << keyword << "\n";
      else
        std::cout << keyword << ' ';
    }

  // выводим информацию о вложенности
  if (!bracesStack.empty())
    std::cerr << "Ошибка: несоответствие фигурных скобок в файле!\n";

  while (!bracesStack.empty())
    bracesStack.pop();

  std::stack<char> skobkaStack;
  std::vector<Func> a;
  std::vector<Branch> br;
  br.emplace_back();
  bool r = false;
  bool for_t = false;
  std::string for_tt;
  size_t type = 1;
  for (const std::string &keyword : foundKeywords)
    {
      if (!br.back().empty() && bracesStack.size() == 1)
        {
          br.back().set_name(for_tt);
          for_tt.clear();
          a.back().addContent(std::make_shared<Branch>(br.back()));
          br.emplace_back();
        }
      if (keyword == ",")
        continue;
      if (keyword == ";")
        {
          if (r)
            r = false;
          continue;
        }
      else if (for_t)
        {
          if (keyword == "(")
            skobkaStack.push('(');
          else if (keyword == ")")
            {
              skobkaStack.pop();
              /*
              a[a.size() - 1].addContent(
                      std::make_shared<Branch>(Branch(for_tt)));
                      */
              for_t = false;
            }
          for_tt += ' ' + keyword;
        }
      else if (keyword == "for")
        for_t = true;
      else if (r)
        continue;
      else if ( keyword == "return" )
        r = true;
      else if (keyword == "{")
        bracesStack.push('{');
      else if (keyword == "}")
        {
          bracesStack.pop();
        }
      else if (keyword == "(")
        skobkaStack.push('(');
      else if (keyword == ")")
        skobkaStack.pop();
      else if (std::find(types_keywords.begin(), types_keywords.end(), keyword)
               != types_keywords.end())
        {
          if (keyword == "long" && type == 4 || type == 8)
            type = 8;
          else
            type *= type_sizes[keyword];
        }
      else
        {
          if (bracesStack.empty())
            {
              if (skobkaStack.empty())
                {
                  a.emplace_back(keyword, type - 1);
                  type = 1;
                }
              else
                {
                  a[a.size() - 1].expandStack(type);
                  a[a.size() - 1].addConstant(
                      std::make_shared<Constant>(Constant(keyword, type - 1)));
                  type = 1;
                }
            }
          else
            {
              if (skobkaStack.empty())
                {
                  if (bracesStack.size() >= 2)
                    {
                      std::cerr << "goida";
                      br.back().addContent(std::make_shared<Constant>(Constant(keyword, type - 1)));
                    }
                  else
                    a.back().addContent(std::make_shared<Constant>(Constant(keyword, type - 1)));
                  type = 1;
                }
            }
        }
    }

  std::cout << std::endl;
  for (const auto & f : a)
    {
      std::cout << f;
    }
}
