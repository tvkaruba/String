#ifndef STR_STRING_H
#define STR_STRING_H

#include <cstdlib>
#include <vector>
#include <locale>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <iterator>

class String
{
public:
    /// Конструктор по умолчанию.
    String() : _length(0), _chars(nullptr) { }

    /// Конструктор из строки
    String(const std::string &str);

    ///Конструктор из массива символов
    String(const char *chs, size_t size);

    /// Move constructor
    String(String &&other) noexcept;

    /// Конструктор копирования.
    String(const String &other);

    /// Деструктор.
    ~String();

    /// Move assignment
    String &operator=(String &&other);

    /// Оператор присваивания.
    String &operator=(const String &other);

    /// Swap.
    friend void swap(String &right, String &left);

public:
    /// Сравнивает строку с переданной игнорируя регистр (для простоты), возвращает численную разницу между строками.
    /// > 0 если строка больше переданной, < 0 если строка меньше переданной, = 0, если строки равны.
    int compareTo (const String &other);

    /// Проверяет строки на равенство.
    bool equals (const String &other);

    /// Находит первое вхождение символа в строке, возвращает его индекс в строке.
    int find(char ch);

    /// Находит первое вхождение подстроки в строку, возвращает индекс начала вхождения.
    int find(const String &subString);

    /// Проверяет вхождение подстроки в строку.
    bool contains (const String &subString);

    /// Заменяет по всей строке старый символ, на новый.
    String replace (char oldCh, char newCh);

    /// Заменяет по всей строке старую подстроку на новую.
    String replace (const String &oldStr, const String &newStr);

    /// Вставляет переданную строку по индексу.
    String insert (int startIndex, const String &subString);

    /// Вставляет переданную строку по индексу.
    String append (const String &subString);

    /// Вставляет переданную строку по индексу.
    String append (char ch);

    /// Удаляет count символов начиная со стартовой позиции.
    String remove (int startIndex, int count);

    /// Разделяет строку по определенному символу
    std::vector<String> split(char ch);

    /// Разделяет строку по определенному символу
    std::vector<String> split(const char *chs, size_t size);

    /// Возвращает подстроку длинной count начиная со стартовой позиции
    String substring(int startIndex, int count);

    /// Преобразует строку в массив символов
    std::pair<char *, size_t> toCharArray();

    /// Преобразует строку в std::string
    std::string toString();

    /// Преобразует строку в c_str
    char *c_str();

    /// Приводит строку к нижнему регистру.
    String toLower();

    /// Приводит строку к верхнему регистру.
    String toUpper();

    /// Вычисляет хэш от строки.
    int hash();

    /// Пустая ли строка.
    bool empty();

    /// Длинна строки.
    int size();

public:
    // Операторы.
    char operator[](int index) const;
    char &operator[](int index);

    String operator+(const String &right);
    String operator+(char right);
    // Снизу вне класса еще сравнения перегружены.

public:
    class Iterator : public std::iterator<std::random_access_iterator_tag, char>
    {
        friend class String;
    public:
        using difference_type = typename std::iterator<std::random_access_iterator_tag, char>::difference_type ;

        Iterator() : _ptr(nullptr) {}
        Iterator(char* rhs) : _ptr(rhs) {}
        Iterator(const Iterator &rhs) : _ptr(rhs._ptr) {}

        inline char& operator*() const {return *_ptr;}
        inline char* operator->() const {return _ptr;}
        inline char& operator[](difference_type rhs) const {return _ptr[rhs];}

        inline Iterator& operator++() {++_ptr; return *this;}
        inline Iterator& operator--() {--_ptr; return *this;}

        inline Iterator& operator+=(difference_type rhs) {_ptr += rhs; return *this;}
        inline Iterator& operator-=(difference_type rhs) {_ptr -= rhs; return *this;}

        inline Iterator operator+(difference_type rhs) const {return Iterator(_ptr+rhs);}
        inline Iterator operator-(difference_type rhs) const {return Iterator(_ptr-rhs);}

        inline bool operator==(const Iterator& rhs) const {return _ptr == rhs._ptr;}
        inline bool operator!=(const Iterator& rhs) const {return _ptr != rhs._ptr;}
        inline bool operator>(const Iterator& rhs) const {return _ptr > rhs._ptr;}
        inline bool operator<(const Iterator& rhs) const {return _ptr < rhs._ptr;}
        inline bool operator>=(const Iterator& rhs) const {return _ptr >= rhs._ptr;}
        inline bool operator<=(const Iterator& rhs) const {return _ptr <= rhs._ptr;}
    private:
        char *_ptr;
    };

    Iterator begin()
    {
        return Iterator(_chars);
    }

    Iterator end()
    {
        return Iterator(_chars + sizeof(char) * _length);
    }
private:
    /// Длинна строки.
    int _length;
    /// Массив символов представляющий строку.
    char *_chars;
};

// Сравнения.
bool operator==(String &left, String &right);
bool operator!=(String &left, String &right);
bool operator>(String &left, String &right);
bool operator<(String &left, String &right);
bool operator>=(String &left, String &right);
bool operator<=(String &left, String &right);

#endif //STR_STRING_H
