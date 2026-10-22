#include "xml_format.h"
#include <iomanip>
#include <sstream>

static std::string GetNow(
    const char* fmt = "%Y-%m-%d %H:%M:%S",
    int time_zone = 8)
{
    std::time_t unix_sec = std::time(nullptr);
    std::tm tm;
    static const int kHoursInDay = 24;
    static const int kMinutesInHour = 60;
    static const int kDaysFromUnixTime = 2472632;
    static const int kDaysFromYear = 153;
    static const int kMagicUnkonwnFirst = 146097;
    static const int kMagicUnkonwnSec = 1461;
    tm.tm_sec = unix_sec % kMinutesInHour;
    int i = (unix_sec / kMinutesInHour);
    tm.tm_min = i % kMinutesInHour; //nn
    i /= kMinutesInHour;
    tm.tm_hour = (i + time_zone) % kHoursInDay; // hh
    tm.tm_mday = (i + time_zone) / kHoursInDay;
    int a = tm.tm_mday + kDaysFromUnixTime;
    int b = (a * 4 + 3) / kMagicUnkonwnFirst;
    int c = (-b * kMagicUnkonwnFirst) / 4 + a;
    int d = ((c * 4 + 3) / kMagicUnkonwnSec);
    int e = -d * kMagicUnkonwnSec;
    e = e / 4 + c;
    int m = (5 * e + 2) / kDaysFromYear;
    tm.tm_mday = -(kDaysFromYear * m + 2) / 5 + e + 1;
    tm.tm_mon = (-m / 10) * 12 + m + 2;
    tm.tm_year = b * 100 + d - 6700 + (m / 10);
    std::stringstream ss;
    ss << std::put_time(&tm, fmt); //#include <iomanip>
    return ss.str();
}

// 转义 XML 属性值中不允许出现的字符
// 规则参考 XML 1.0 规范：& < > " ' 必须转义
static std::string EscapeAttr(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (char c : s) {
        switch (c) {
        case '&':  out += "&amp;";  break;
        case '<':  out += "&lt;";   break;
        case '>':  out += "&gt;";   break;
        case '"':  out += "&quot;"; break;
        case '\'': out += "&apos;"; break;
        default:   out += c;        break;
        }
    }
    return out;
}

// CDATA 段中不能出现 "]]>"，否则会提前结束 CDATA。
// 标准做法是把它拆成 "]]" + "]]><![CDATA[" + ">"，即：
//   ]]>  -->  ]]]]><![CDATA[>
static std::string EscapeCData(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (size_t i = 0; i < s.size(); ++i) {
        if (i + 2 < s.size() && s[i] == ']' && s[i + 1] == ']' && s[i + 2] == '>') {
            out += "]]]]><![CDATA[>";
            i += 2; // 跳过 "]>"
        }
        else {
            out += s[i];
        }
    }
    return out;
}

std::string XmlFormat::Format(
    const std::string& level,
    const std::string& log,
    const std::string& file,
    int line)
{
    std::stringstream ss;
    // 缩进：日志条目在 <logs> 下缩进一级
    ss << "  <log"
        << " time=\"" << EscapeAttr(GetNow()) << "\""
        << " level=\"" << EscapeAttr(level) << "\""
        << " file=\"" << EscapeAttr(file) << "\""
        << " line=\"" << line << "\">\n";
    ss << "    <message><![CDATA[" << EscapeCData(log) << "]]></message>\n";
    ss << "  </log>\n";
    return ss.str();
}