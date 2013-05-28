
#include "char_codec.h"
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <string.h>
#include <wchar.h>
//#include <wfstream.h>

CharCodec::CharCodec() {
    int i = 0;
    LowerPrecomposedUnicode[ i++ ] = L'a';
    LowerPrecomposedUnicode[ i++ ] = L'b';
    LowerPrecomposedUnicode[ i++ ] = L'c';
    LowerPrecomposedUnicode[ i++ ] = L'd';
    LowerPrecomposedUnicode[ i++ ] = L'e';
    LowerPrecomposedUnicode[ i++ ] = L'f';
    LowerPrecomposedUnicode[ i++ ] = L'g';
    LowerPrecomposedUnicode[ i++ ] = L'h';
    LowerPrecomposedUnicode[ i++ ] = L'i';
    LowerPrecomposedUnicode[ i++ ] = L'j';
    LowerPrecomposedUnicode[ i++ ] = L'k';
    LowerPrecomposedUnicode[ i++ ] = L'l';
    LowerPrecomposedUnicode[ i++ ] = L'm';
    LowerPrecomposedUnicode[ i++ ] = L'n';
    LowerPrecomposedUnicode[ i++ ] = L'o';
    LowerPrecomposedUnicode[ i++ ] = L'p';
    LowerPrecomposedUnicode[ i++ ] = L'q';
    LowerPrecomposedUnicode[ i++ ] = L'r';
    LowerPrecomposedUnicode[ i++ ] = L's';
    LowerPrecomposedUnicode[ i++ ] = L't';
    LowerPrecomposedUnicode[ i++ ] = L'u';
    LowerPrecomposedUnicode[ i++ ] = L'v';
    LowerPrecomposedUnicode[ i++ ] = L'w';
    LowerPrecomposedUnicode[ i++ ] = L'x';
    LowerPrecomposedUnicode[ i++ ] = L'y';
    LowerPrecomposedUnicode[ i++ ] = L'z';

    LowerPrecomposedUnicode[ i++ ] = L'à'; //0x00E0;  // af
    LowerPrecomposedUnicode[ i++ ] = L'ả'; //0x1EA3;  // ar
    LowerPrecomposedUnicode[ i++ ] = L'ã'; //0x00E3;  // ax
    LowerPrecomposedUnicode[ i++ ] = L'á'; //0x00E1;  // as
    LowerPrecomposedUnicode[ i++ ] = L'ạ'; //0x1EA1;  // aj

    LowerPrecomposedUnicode[ i++ ] = L'ằ'; //0x1EB1;  // awf
    LowerPrecomposedUnicode[ i++ ] = L'ẳ'; //0x1EB3;  // awr
    LowerPrecomposedUnicode[ i++ ] = L'ẵ'; //0x1EB5;  // awx
    LowerPrecomposedUnicode[ i++ ] = L'ắ'; //0x1EAF;  // aws
    LowerPrecomposedUnicode[ i++ ] = L'ặ'; //0x1EB7;  // awj
    LowerPrecomposedUnicode[ i++ ] = L'ă'; //0x0103;  // aw

    LowerPrecomposedUnicode[ i++ ] = L'ầ'; //0x1EA7;  // aaf
    LowerPrecomposedUnicode[ i++ ] = L'ẩ'; //0x1EA9;  // aar
    LowerPrecomposedUnicode[ i++ ] = L'ẫ'; //0x1EAB;  // aax
    LowerPrecomposedUnicode[ i++ ] = L'ấ'; //0x1EA5;  // aas
    LowerPrecomposedUnicode[ i++ ] = L'ậ'; //0x1EAD;  // aaj
    LowerPrecomposedUnicode[ i++ ] = L'â'; //0x00E2;  // aa

    LowerPrecomposedUnicode[ i++ ] = L'è'; //0x00E8;  // ef
    LowerPrecomposedUnicode[ i++ ] = L'ẻ'; //0x1EBB;  // er
    LowerPrecomposedUnicode[ i++ ] = L'ẽ'; //0x1EBD;  // ex
    LowerPrecomposedUnicode[ i++ ] = L'é'; //0x00E9;  // es
    LowerPrecomposedUnicode[ i++ ] = L'ẹ'; //0x1EB9;  // ej

    LowerPrecomposedUnicode[ i++ ] = L'ề'; //0x1EC1;  // eef
    LowerPrecomposedUnicode[ i++ ] = L'ể'; //0x1EC3;  // eer
    LowerPrecomposedUnicode[ i++ ] = L'ễ'; //0x1EC5;  // eex
    LowerPrecomposedUnicode[ i++ ] = L'ế'; //0x1EBF;  // ees
    LowerPrecomposedUnicode[ i++ ] = L'ệ'; //0x1EC7;  // eej
    LowerPrecomposedUnicode[ i++ ] = L'ê'; //0x00EA;  // ee

    LowerPrecomposedUnicode[ i++ ] = L'ì'; //0x00EC;  // if
    LowerPrecomposedUnicode[ i++ ] = L'ỉ'; //0x1EC9;  // ir
    LowerPrecomposedUnicode[ i++ ] = L'ĩ'; //0x0129;  // ix
    LowerPrecomposedUnicode[ i++ ] = L'í'; //0x00ED;  // is
    LowerPrecomposedUnicode[ i++ ] = L'ị'; //0x1ECB;  // ij

    LowerPrecomposedUnicode[ i++ ] = L'ò'; //0x00F2;  // of
    LowerPrecomposedUnicode[ i++ ] = L'ỏ'; //0x1ECF;  // or
    LowerPrecomposedUnicode[ i++ ] = L'õ'; //0x00F5;  // ox
    LowerPrecomposedUnicode[ i++ ] = L'ó'; //0x00F3;  // os
    LowerPrecomposedUnicode[ i++ ] = L'ọ'; //0x1ECD;  // oj

    LowerPrecomposedUnicode[ i++ ] = L'ồ'; //0x1ED3;  // oof
    LowerPrecomposedUnicode[ i++ ] = L'ổ'; //0x1ED5;  // oor
    LowerPrecomposedUnicode[ i++ ] = L'ỗ'; //0x1ED7;  // oox
    LowerPrecomposedUnicode[ i++ ] = L'ố'; //0x1ED1;  // oos
    LowerPrecomposedUnicode[ i++ ] = L'ộ'; //0x1ED9;  // ooj
    LowerPrecomposedUnicode[ i++ ] = L'ô'; //0x00F4;  // oo

    LowerPrecomposedUnicode[ i++ ] = L'ờ'; //0x1EDD;  // owf
    LowerPrecomposedUnicode[ i++ ] = L'ở'; //0x1EDF;  // owr
    LowerPrecomposedUnicode[ i++ ] = L'ỡ'; //0x1EE1;  // owx
    LowerPrecomposedUnicode[ i++ ] = L'ớ'; //0x1EDB;  // ows
    LowerPrecomposedUnicode[ i++ ] = L'ợ'; //0x1EE3;  // owj
    LowerPrecomposedUnicode[ i++ ] = L'ơ'; //0x01A1;  // ow

    LowerPrecomposedUnicode[ i++ ] = L'ù'; //0x00F9;  // uf
    LowerPrecomposedUnicode[ i++ ] = L'ủ'; //0x1EE7;  // ur
    LowerPrecomposedUnicode[ i++ ] = L'ũ'; //0x0169;  // ux
    LowerPrecomposedUnicode[ i++ ] = L'ú'; //0x00FA;  // us
    LowerPrecomposedUnicode[ i++ ] = L'ụ'; //0x1EE5;  // uj

    LowerPrecomposedUnicode[ i++ ] = L'ừ'; //0x1EEB;  // uwf
    LowerPrecomposedUnicode[ i++ ] = L'ử'; //0x1EED;  // uwr
    LowerPrecomposedUnicode[ i++ ] = L'ữ'; //0x1EEF;  // uwx
    LowerPrecomposedUnicode[ i++ ] = L'ứ'; //0x1EE9;  // uws
    LowerPrecomposedUnicode[ i++ ] = L'ự'; //0x1EF1;  // uwj
    LowerPrecomposedUnicode[ i++ ] = L'ư'; //0x01B0;  // uw

    LowerPrecomposedUnicode[ i++ ] = L'ỳ'; //0x1EF3;  // yf
    LowerPrecomposedUnicode[ i++ ] = L'ỷ'; //0x1EF7;  // yr
    LowerPrecomposedUnicode[ i++ ] = L'ỹ'; //0x1EF9;  // yx
    LowerPrecomposedUnicode[ i++ ] = L'ý'; //0x00FD;  // ys
    LowerPrecomposedUnicode[ i++ ] = L'ỵ'; //0x1EF5;  // yj

    LowerPrecomposedUnicode[ i++ ] = L'đ'; //0x0111;  // dd

    i = 0;
    UpperPrecomposedUnicode[ i++ ] = L'A';
    UpperPrecomposedUnicode[ i++ ] = L'B';
    UpperPrecomposedUnicode[ i++ ] = L'C';
    UpperPrecomposedUnicode[ i++ ] = L'D';
    UpperPrecomposedUnicode[ i++ ] = L'E';
    UpperPrecomposedUnicode[ i++ ] = L'F';
    UpperPrecomposedUnicode[ i++ ] = L'G';
    UpperPrecomposedUnicode[ i++ ] = L'H';
    UpperPrecomposedUnicode[ i++ ] = L'I';
    UpperPrecomposedUnicode[ i++ ] = L'J';
    UpperPrecomposedUnicode[ i++ ] = L'K';
    UpperPrecomposedUnicode[ i++ ] = L'L';
    UpperPrecomposedUnicode[ i++ ] = L'M';
    UpperPrecomposedUnicode[ i++ ] = L'N';
    UpperPrecomposedUnicode[ i++ ] = L'O';
    UpperPrecomposedUnicode[ i++ ] = L'P';
    UpperPrecomposedUnicode[ i++ ] = L'Q';
    UpperPrecomposedUnicode[ i++ ] = L'R';
    UpperPrecomposedUnicode[ i++ ] = L'S';
    UpperPrecomposedUnicode[ i++ ] = L'T';
    UpperPrecomposedUnicode[ i++ ] = L'U';
    UpperPrecomposedUnicode[ i++ ] = L'V';
    UpperPrecomposedUnicode[ i++ ] = L'W';
    UpperPrecomposedUnicode[ i++ ] = L'X';
    UpperPrecomposedUnicode[ i++ ] = L'Y';
    UpperPrecomposedUnicode[ i++ ] = L'Z';

    UpperPrecomposedUnicode[ i++ ] = L'À'; //0x00C0;  // Af
    UpperPrecomposedUnicode[ i++ ] = L'Ả'; //0x1EA2;  // Ar
    UpperPrecomposedUnicode[ i++ ] = L'Ã'; //0x00C3;  // Ax
    UpperPrecomposedUnicode[ i++ ] = L'Á'; //0x00C1;  // As
    UpperPrecomposedUnicode[ i++ ] = L'Ạ'; //0x1EA0;  // Aj

    UpperPrecomposedUnicode[ i++ ] = L'Ằ'; //0x1EB0;  // AWf
    UpperPrecomposedUnicode[ i++ ] = L'Ẳ'; //0x1EB2;  // AWr
    UpperPrecomposedUnicode[ i++ ] = L'Ẵ'; //0x1EB4;  // AWx
    UpperPrecomposedUnicode[ i++ ] = L'Ắ'; //0x1EAE;  // AWs
    UpperPrecomposedUnicode[ i++ ] = L'Ặ'; //0x1EB6;  // AWj
    UpperPrecomposedUnicode[ i++ ] = L'Ă'; //0x0102;  // AW

    UpperPrecomposedUnicode[ i++ ] = L'Ầ'; //0x1EA6;  // AAf
    UpperPrecomposedUnicode[ i++ ] = L'Ẩ'; //0x1EA8;  // AAr
    UpperPrecomposedUnicode[ i++ ] = L'Ẫ'; //0x1EAA;  // AAx
    UpperPrecomposedUnicode[ i++ ] = L'Ấ'; //0x1EA4;  // AAs
    UpperPrecomposedUnicode[ i++ ] = L'Ậ'; //0x1EAC;  // AAj
    UpperPrecomposedUnicode[ i++ ] = L'Â'; //0x00C2;  // AA

    UpperPrecomposedUnicode[ i++ ] = L'È'; //0x00C8;  // Ef
    UpperPrecomposedUnicode[ i++ ] = L'Ẻ'; //0x1EBA;  // Er
    UpperPrecomposedUnicode[ i++ ] = L'Ẽ'; //0x1EBC;  // Ex
    UpperPrecomposedUnicode[ i++ ] = L'É'; //0x00C9;  // Es
    UpperPrecomposedUnicode[ i++ ] = L'Ẹ'; //0x1EB8;  // Ej

    UpperPrecomposedUnicode[ i++ ] = L'Ề'; //0x1EC0;  // EEf
    UpperPrecomposedUnicode[ i++ ] = L'Ể'; //0x1EC2;  // EEr
    UpperPrecomposedUnicode[ i++ ] = L'Ễ'; //0x1EC4;  // EEx
    UpperPrecomposedUnicode[ i++ ] = L'Ế'; //0x1EBE;  // EEs
    UpperPrecomposedUnicode[ i++ ] = L'Ệ'; //0x1EC6;  // EEj
    UpperPrecomposedUnicode[ i++ ] = L'Ê'; //0x00CA;  // EE

    UpperPrecomposedUnicode[ i++ ] = L'Ì'; //0x00CC;  // If
    UpperPrecomposedUnicode[ i++ ] = L'Ỉ'; //0x1EC8;  // Ir
    UpperPrecomposedUnicode[ i++ ] = L'Ĩ'; //0x0128;  // Ix
    UpperPrecomposedUnicode[ i++ ] = L'Í'; //0x00CD;  // Is
    UpperPrecomposedUnicode[ i++ ] = L'Ị'; //0x1ECA;  // Ij

    UpperPrecomposedUnicode[ i++ ] = L'Ò'; //0x00D2;  // Of
    UpperPrecomposedUnicode[ i++ ] = L'Ỏ'; //0x1ECE;  // Or
    UpperPrecomposedUnicode[ i++ ] = L'Õ'; //0x00D5;  // Ox
    UpperPrecomposedUnicode[ i++ ] = L'Ó'; //0x00D3;  // Os
    UpperPrecomposedUnicode[ i++ ] = L'Ọ'; //0x1ECC;  // Oj

    UpperPrecomposedUnicode[ i++ ] = L'Ồ'; //0x1ED2;  // OOf
    UpperPrecomposedUnicode[ i++ ] = L'Ổ'; //0x1ED4;  // OOr
    UpperPrecomposedUnicode[ i++ ] = L'Ỗ'; //0x1ED6;  // OOx
    UpperPrecomposedUnicode[ i++ ] = L'Ố'; //0x1ED0;  // OOs
    UpperPrecomposedUnicode[ i++ ] = L'Ộ'; //0x1ED8;  // OOj
    UpperPrecomposedUnicode[ i++ ] = L'Ô'; //0x00D4;  // OO

    UpperPrecomposedUnicode[ i++ ] = L'Ờ'; //0x1EDC;  // OWf
    UpperPrecomposedUnicode[ i++ ] = L'Ở'; //0x1EDE;  // OWr
    UpperPrecomposedUnicode[ i++ ] = L'Ỡ'; //0x1EE0;  // OWx
    UpperPrecomposedUnicode[ i++ ] = L'Ớ'; //0x1EDA;  // OWs
    UpperPrecomposedUnicode[ i++ ] = L'Ợ'; //0x1EE2;  // OWj
    UpperPrecomposedUnicode[ i++ ] = L'Ơ'; //0x01A0;  // OW

    UpperPrecomposedUnicode[ i++ ] = L'Ù'; //0x00D9;  // Uf
    UpperPrecomposedUnicode[ i++ ] = L'Ủ'; //0x1EE6;  // Ur
    UpperPrecomposedUnicode[ i++ ] = L'Ũ'; //0x0168;  // Ux
    UpperPrecomposedUnicode[ i++ ] = L'Ú'; //0x00DA;  // Us
    UpperPrecomposedUnicode[ i++ ] = L'Ụ'; //0x1EE4;  // Uj

    UpperPrecomposedUnicode[ i++ ] = L'Ừ'; //0x1EEA;  // UWf
    UpperPrecomposedUnicode[ i++ ] = L'Ử'; //0x1EEC;  // UWr
    UpperPrecomposedUnicode[ i++ ] = L'Ữ'; //0x1EEE;  // UWx
    UpperPrecomposedUnicode[ i++ ] = L'Ứ'; //0x1EE8;  // UWs
    UpperPrecomposedUnicode[ i++ ] = L'Ự'; //0x1EF0;  // UWj
    UpperPrecomposedUnicode[ i++ ] = L'Ư'; //0x01AF;  // UW

    UpperPrecomposedUnicode[ i++ ] = L'Ỳ'; //0x1EF2;  // Yf
    UpperPrecomposedUnicode[ i++ ] = L'Ỷ'; //0x1EF6;  // Yr
    UpperPrecomposedUnicode[ i++ ] = L'Ỹ'; //0x1EF8;  // Yx
    UpperPrecomposedUnicode[ i++ ] = L'Ý'; //0x00DD;  // Ys
    UpperPrecomposedUnicode[ i++ ] = L'Ỵ'; //0x1EF4;  // Yj

    UpperPrecomposedUnicode[ i++ ] = L'Đ'; //0x0110;  // DD

}

void CharCodec::UTF8Encode2BytesUnicode(char *output, const wchar_t *input) {
    int j = 0;
    for (int i = 0; i < (int) wcslen(input); i++) {
        if (input[i] < 0x80) {
            output[j++] = (char) input[i];
        } else if (input[i] < 0x800) {
            output[j++] = (char) (MASK2BYTES | input[i] >> 6);
            output[j++] = (char) (MASKBYTE | (input[i] & MASKBITS));
        } else if (input[i] < 0x10000) {
            output[j++] = (char) (MASK3BYTES | input[i] >> 12);
            output[j++] = (char) (MASKBYTE | (input[i] >> 6 & MASKBITS));
            output[j++] = (char) (MASKBYTE | (input[i] & MASKBITS));
        }
    }
    output[j] = 0;
}

void CharCodec::UTF8Decode2BytesUnicode(wchar_t *output, const char *input) {
    int j = 0;
    for (int i = 0; i < (int) strlen(input);) {
        wchar_t ch;
        if ((input[i] & MASK3BYTES) == MASK3BYTES) {
            ch = ((input[i] & 0x0F) << 12) | (
                    (input[i + 1] & MASKBITS) << 6)
                    | (input[i + 2] & MASKBITS);
            i += 3;
        } else if ((input[i] & MASK2BYTES) == MASK2BYTES) {
            ch = ((input[i] & 0x1F) << 6) | (input[i + 1] & MASKBITS);
            i += 2;
        } else if (input[i] < MASKBYTE) {
            ch = input[i];
            i += 1;
        }
        output[j++] = ch;
    }
    output[j] = 0;
}

bool CharCodec::isLower(wchar_t input) {
    for (int i = 0; i < 93; i++) {
        if (input == LowerPrecomposedUnicode[i])
            return true;

    }
    return false;
}

bool CharCodec::isUpper(wchar_t input) {
    for (int i = 0; i < 93; i++) {
        if (input == UpperPrecomposedUnicode[i])
            return true;

    }
    return false;
}

int CharCodec::indexLower(wchar_t input) {
    for (int i = 0; i < 93; i++) {
        if (input == LowerPrecomposedUnicode[i])
            return i;
    }
    return -1;
}

int CharCodec::indexUpper(wchar_t input) {
    for (int i = 0; i < 93; i++) {
        if (input == UpperPrecomposedUnicode[i])
            return i;
    }
    return -1;
}

void CharCodec::readSeparator(char * input) {
    UTF8Decode2BytesUnicode(sep, input);
}

bool CharCodec::isSeparator(wchar_t input) {
    for (int i = 0; i < (int) wcslen(sep); i++) if (input == sep[i])
            return true;
    return false;
}

vector<string> CharCodec::processString(string str) {
    vector<string> res;
    wchar_t wc[10005], temp[10005];
    char c[10005];
    UTF8Decode2BytesUnicode(wc, str.c_str());
    for (int i = 0; i < (int) wcslen(wc); i++) if (isUpper(wc[i])) {
            wc[i] = LowerPrecomposedUnicode[indexUpper(wc[i])];
        }

    int run = 0;
    for (int i = 0; i < (int) wcslen(wc); i++) {
        if (isSeparator(wc[i])) {
            if (run > 0) {
                temp[run] = 0;
                UTF8Encode2BytesUnicode(c, temp);
                res.push_back(string(c));
            }
            temp[0] = wc[i];
            temp[1] = 0;
            UTF8Encode2BytesUnicode(c, temp);
            res.push_back(string(c));
            run = 0;
        } else temp[run++] = wc[i];
    }
    if (run > 0) {
        temp[run] = 0;
        UTF8Encode2BytesUnicode(c, temp);
        res.push_back(string(c));
    }

    return res;
}
