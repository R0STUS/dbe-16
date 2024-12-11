# Dual-Byte Encoding 16x
# Functions:
## convert:
```cpp
std::string DBE16::convert(std::vector<Sym>& s, const std::string& input, bool isSensable, bool isHex)
```
Using inside.
## decode:
```cpp
std::string DBE16::decode(const std::string& input)
```
Using for decode HEX-string.
## converttohex:
```cpp
std::string DBE16::converttohex(const std::string& input)
```
Using for encode string.
## writefile:
```cpp
void DBE16::writefile(const std::string& filePath, const std::string& hexValues)
```
Using for saving binary values to file.
## readfile:
```cpp
std::string DBE16::readfile(const std::string& filePath)
```
Using for reading and decoding HEX-values from file.
