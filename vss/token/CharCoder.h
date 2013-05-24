
#include "iostream"
#include <cstring>
#include <vector>

#define         MASKBITS                0x3F
#define         MASKBYTE                0x80
#define         MASK2BYTES              0xC0
#define         MASK3BYTES              0xE0
#define         MASK4BYTES              0xF0
#define         MASK5BYTES              0xF8
#define         MASK6BYTES              0xFC

typedef unsigned short   Unicode2Bytes;
typedef unsigned int     Unicode4Bytes;

using namespace std;
class CharCoder
{
public:
	wchar_t LowerPrecomposedUnicode[93];
	wchar_t UpperPrecomposedUnicode[93];
	wchar_t sep[100];
	CharCoder();
	void readSeparator(char * input);
	void UTF8Encode2BytesUnicode(char *output, const wchar_t *input);
	void UTF8Decode2BytesUnicode(wchar_t *output, const char *input);
	bool isLower(wchar_t input);
	bool isUpper(wchar_t input);
	int indexLower(wchar_t input);
	int indexUpper(wchar_t input);
	bool isSeparator(wchar_t input);
	vector<string> processString(string str);
};
