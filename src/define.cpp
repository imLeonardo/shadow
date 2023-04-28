#include <define.h>

//namespace fmt {
//    template<typename format_context>
//    auto Formatter<Color>::format(const Color &value, format_context &ctx) {
//        string_view sv;
//        switch(value) {
//            case Color::RED:
//                sv = "red";
//                break;
//            case Color::GREEN:
//                sv = "green";
//                break;
//            case Color::BLUE:
//                sv = "blue";
//                break;
//            default:
//                sv = std::to_string(int(value));
//                break;
//        }
//        return formatter<string_view>::format(sv, ctx);
//    }
//
//    template<typename format_context>
//    auto Formatter<ServerState>::format(const ServerState &value, format_context &ctx) {
//        return formatter<int>::format((int) value, ctx);
//    }
//
//    template<typename format_context>
//    auto Formatter<ErrCode>::format(const ErrCode &value, format_context &ctx) {
//        return formatter<int>::format((int) value, ctx);
//    }
//}
