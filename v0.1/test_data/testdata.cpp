#include "testdata.h"

std::wstring nullstr = L"nullptr";

// char utilities
#include <unordered_set>

std::unordered_set<wchar_t> space_symbols = {L' ', L'\t'};
std::unordered_set<wchar_t> delim_symbols = {L'=', L'-', L'+', L':', L';', L'.', L',', L'/', L'\\', L'|', L'_', L'#', L'!', L'%'};
std::unordered_set<wchar_t> serve_symbols = {L'\n', L'\r'};

bool is_part_symb(wchar_t c, std::unordered_set<wchar_t>& s){
    return (s.find(c) != s.end());
}
bool is_wspace(wchar_t c) {return is_part_symb(c, space_symbols);}
bool is_wdelim(wchar_t c) {return is_part_symb(c, delim_symbols);}
bool is_wserve(wchar_t c) {return is_part_symb(c, serve_symbols);}
//

#include <vector>
#include <regex>
TestDataBox extract_regex(std::wstring cleanRawData){
    std::wstring delim_str;
    for (auto& c : delim_symbols) { delim_str += (L"\\" + std::wstring(1, c)); }

    std::wregex reg_expression(L"([а-яА-Я]+)(?:[" + delim_str + L"][a-zA-Z]+){3}");
    std::wsmatch match;

    if (std::regex_search(cleanRawData, match, reg_expression))
        return {match[1].str(), match[2].str(), match[3].str(), match[4].str()};
    else
        return {L"", L"", L"", L""};
}
TestDataBox extract_standart(std::wstring cleanRawData){
    std::vector<std::wstring> words;
    std::wstring buff_word;
    for (auto& wc : cleanRawData) {
        if (is_wdelim(wc) || wc == L'\n') {
            words.push_back(buff_word);
            buff_word = L"";
        } else if (!is_wserve(wc)) {
            buff_word += wc;
        }
    }
    if (!buff_word.empty())
        words.push_back(buff_word);
    if (words.size() >= 4) {
        return {words[0], words[1], words[2], words[3], true};
    } else {
        return {L"None", L"None", L"None", L"None", false};
    }
}

TestData::TestData(std::wstring rawData) {
    std::wstring cleanRawData;
    for (auto& wc : rawData)
        if (!is_wspace(wc))
            cleanRawData += wc;
    this->move_data(std::move(extract_standart(cleanRawData)));
}
TestData::TestData(std::wstring r, std::wstring ef, std::wstring es, std::wstring et)
    : rusWord(r), engFirstForm(ef), engSecondForm(es), engThirdForm(et) {
}
TestData::TestData(TestDataBox data){
    this->move_data(std::move(data));
}

void TestData::move_data(TestDataBox data){
    this->rusWord = std::move(data.r);
    this->engFirstForm = std::move(data.ef);
    this->engSecondForm = std::move(data.es);
    this->engThirdForm = std::move(data.et);
    this->isValid = data.isValid;
}

bool TestData::is_valid(){
    return isValid;
}

std::wostream& operator<< (std::wostream &wout, const TestData& data){
    std::wstring lBracket(L"{"), rBracket(L"}"), delimStr(L" - ");
    wout << lBracket << data.rusWord << delimStr << data.engFirstForm << delimStr << data.engSecondForm << delimStr << data.engThirdForm << rBracket;
    return wout;
}
std::wostream& operator<< (std::wostream& wout, const std::shared_ptr<TestData> data){
    if (data)
        wout << *data;
    else
        wout << nullstr;
    return wout;
}


