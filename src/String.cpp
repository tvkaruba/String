#include "String.h"

String::String(const std::string &str)
{
    _chars = new char[str.size()];
    _length = static_cast<int>(str.size());

    for (int i = 0; i < _length; ++i)
        _chars[i] = str[i];
}

String::String(const char *chs, size_t size)
{
    _chars = new char[size];
    _length = static_cast<int>(size);

    for (int i = 0; i < _length; ++i)
        _chars[i] = chs[i];
}

String::String(String &&other) noexcept : _chars(nullptr), _length(0)
{
    _chars = other._chars;
    _length = other._length;

    other._chars = nullptr;
    other._length = 0;
}

String::String(const String &other)
{
    _chars = new char[other._length];
    _length = other._length;

    for (int i = 0; i < other._length; ++i)
        _chars[i] = other._chars[i];
}

String::~String()
{
    delete [] _chars;
}

String &String::operator=(String &&other)
{
    if (this != &other)
    {
        delete[] _chars;

        _chars = other._chars;
        _length = other._length;

        other._chars = nullptr;
        other._length = 0;
    }

    return *this;
}

String &String::operator=(const String &other)
{
    String temp(other);
    swap(*this, temp);

    return *this;
}

void swap(String &right, String &left)
{
    std::swap(left._length, right._length);
    std::swap(left._chars, right._chars);
}

//////////////////////////////////////////////////////////////////////////////////////////////

int String::compareTo(const String &other)
{
    bool ch1IsUpper;
    bool ch2IsUpper;
    int delta = 0;
    for (int i = 0; i < std::min((*this)._length, other._length); ++i)
    {
        ch1IsUpper = isupper((*this)[i]);
        ch2IsUpper = isupper(other[i]);

        if (ch1IsUpper && ch2IsUpper)
            delta = tolower((*this)[i]) - tolower(other[i]);
        else if (ch2IsUpper)
            delta = (*this)[i] - tolower(other[i]);
        else if (ch1IsUpper)
            delta = tolower((*this)[i]) - other[i];
        else
            delta = (*this)[i] - other[i];

        if (delta != 0)
            return delta;
    }

    return other._length - (*this)._length;
}

bool String::equals(const String &other)
{
    return (compareTo(other) == 0);
}

int String::find(char ch)
{
    for (int i = 0; i < _length; ++i)
    {
        if (_chars[i] == ch)
            return i;
    }

    return -1;
}

int String::find(const String &subString)
{
    for (int i = 0; i < _length; ++i)
    {
        if (_length - i < subString._length)
            return -1;

        int count = subString._length;
        for (int j = 0; j < subString._length; ++j)
        {
            if (_chars[i + j] == subString[j])
                count--;
            else
                break;
        }

        if (count == 0)
            return i;
    }

    return -1;
}

bool String::contains(const String &subString)
{
    return (find(subString) != -1);
}

String String::replace(char oldCh, char newCh)
{
    String str = *this;

    for (int i = 0; i < _length; ++i)
    {
        if (str[i] == oldCh)
            str._chars[i] = newCh;
    }

    return str;
}

String String::replace(const String &oldStr, const String &newStr)
{
    String str = *this;
    std::vector<int> indexes;

    for (int i = 0; i < _length; ++i)
    {
        if (_length - i < oldStr._length)
            break;

        int count = oldStr._length;
        for (int j = 0; j < oldStr._length; ++j)
        {
            if (_chars[i + j] == oldStr[j])
                count--;
            else
                break;
        }

        if (count == 0)
            indexes.push_back(i);
    }

    for (int i = static_cast<int>(indexes.size() - 1); i >= 0; --i)
    {
        str = str.remove(indexes[i], oldStr._length);
        str = str.insert(indexes[i], newStr);
    }

    return str;
}

String String::insert(int startIndex, const String &subString)
{
    if (startIndex > _length)
        throw std::runtime_error("Insert error.");

    String str;
    str._chars = new char[_length + subString._length];
    str._length = _length + subString._length;

    for (int i = 0; i < startIndex; ++i)
        str._chars[i] = _chars[i];
    for (int i = startIndex; i < startIndex + subString._length; ++i)
        str._chars[i] = subString[i - startIndex];
    for (int i = startIndex; i < _length; ++i)
        str._chars[i + subString._length] = _chars[i];

    return str;
}

String String::append(const String &subString)
{
    return insert(_length, subString);
}

String String::append(char ch)
{
    String str(&ch, 1);
    return insert(_length, str);
}

String String::remove(int startIndex, int count)
{
    if (startIndex > _length - 1 && count != 0)
        throw std::runtime_error("Remove error.");

    String str;
    count = (_length - startIndex > count) ? count : _length - startIndex;
    str._chars = new char[_length - count];
    str._length = _length - count;

    for (int i = 0; i < startIndex; ++i)
        str._chars[i] = _chars[i];
    for (int i = startIndex + count; i < _length; ++i)
        str._chars[i - count] = _chars[i];

    return str;
}

std::vector<String> String::split(char ch)
{
    String str = *this;
    std::vector<String> strs;
    std::vector<int> indexes;

    if (str.find(ch) != -1)
    {
        for (int j = 0; j < str._length; ++j)
        {
            if (str[j] == ch)
                indexes.push_back(j);
        }
    }
    std::sort(indexes.begin(), indexes.end());

    for (int i = static_cast<int>(indexes.size() - 1); i >= 0; --i)
    {
        if (indexes[i] < str._length - 1)
        {
            int tmp1 = indexes[i] + 1;
            int tmp2 = str._length - indexes[i] - 1;
            auto tmp3 = str.substring(tmp1, tmp2);
            strs.push_back(tmp3);
        }
        str = str.remove(indexes[i], str._length - indexes[i]);
    }
    strs.push_back(str);

    return strs;
}

std::vector<String> String::split(const char *chs, size_t size)
{
    if (size == 0)
        throw std::runtime_error("Split error");

    String str = *this;
    String temp = *this;
    std::vector<String> strs;
    std::vector<int> indexes;
    for (int i = 0; i < size; ++i)
    {
        if (str.find(chs[i]) != -1)
        {
            for (int j = 0; j < str._length; ++j)
            {
                if (str[j] == chs[i])
                    indexes.push_back(j);
            }
        }
    }
    std::sort(indexes.begin(), indexes.end());

    for (int i = static_cast<int>(indexes.size() - 1); i >= 0; --i)
    {
        if (indexes[i] < str._length - 1)
        {
            int tmp1 = indexes[i] + 1;
            int tmp2 = str._length - indexes[i] - 1;
            auto tmp3 = str.substring(tmp1, tmp2);
            strs.push_back(tmp3);
        }
        str = str.remove(indexes[i], str._length - indexes[i]);
    }
    strs.push_back(str);

    return strs;
}

String String::substring(int startIndex, int count)
{
    if (startIndex > _length - 1)
        throw std::runtime_error("Substring error.");

    String str = *this;
    str = str.remove(0, startIndex);
    str = str.remove(count, str._length - count);

    return str;
}

std::pair<char *, size_t> String::toCharArray()
{
    return std::make_pair(_chars, _length);
}

std::string String::toString()
{
    return std::string(_chars, static_cast<unsigned long long int>(_length));
}

char *String::c_str()
{
    return const_cast<char *>(toString().c_str());
}

String String::toLower()
{
    String str = *this;

    for (int i = 0; i < str._length; ++i)
        str._chars[i] = static_cast<char>(tolower(str._chars[i]));

    return str;
}

String String::toUpper()
{
    String str = (*this);

    for (int i = 0; i < str._length; ++i)
        str._chars[i] = static_cast<char>(toupper(str._chars[i]));

    return str;
}

int String::hash()
{
    // jenkins_one_at_a_time_hash
    uint32_t hash, i;

    for (hash = i = 0; i < _length; ++i)
    {
        hash += _chars[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

bool String::empty()
{
    return (_length == 0);
}

int String::size()
{
    return _length;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

char String::operator[](int index) const
{
//    if (index > _length - 1 || index < 0)
//        throw std::out_of_range("Out of range error.");
    return _chars[index];
}

char &String::operator[](int index)
{
//    if (index > _length - 1 || index < 0)
//        throw std::out_of_range("Out of range error.");
    return _chars[index];
}

String String::operator+(const String &right)
{
    String str = *this;
    return str.append(right);
}

String String::operator+(const char right)
{
    String str = *this;
    return str.append(right);
}

bool operator==(String &left, String &right)
{
    return left.equals(right);
}

bool operator!=(String &left, String &right)
{
    return !left.equals(right);
}

bool operator>(String &left, String &right)
{
    return left.compareTo(right) > 0;
}

bool operator<(String &left, String &right)
{
    return left.compareTo(right) < 0;
}

bool operator>=(String &left, String &right)
{
    return left.compareTo(right) >= 0;
}

bool operator<=(String &left, String &right)
{
    return left.compareTo(right) <= 0;
}
