#ifndef SHADOW_DEFINED_H
#define SHADOW_DEFINED_H

#include <cstdint>

//#include "spdlog/fmt/bundled/core.h"

typedef uint32_t ThreadNum_t;

const ThreadNum_t WORK_THREAD_NUM = 3;

enum class Color {
    RED,
    BLUE,
    GREEN,
};

enum class AppState {
    UNDEFINED = 0,
    INIT,
    START,
    RUN,
    PAUSE,
    STOP,
};

enum class ErrCode {
    FAIL = -1,
    SUCCESS,
    INVALID_PARAM,
    BAD_ALLOC,
};

//namespace fmt {
//    template<>
//    struct Formatter<Color> : formatter<string_view> {
//        // parse is inherited from formatter<string_view>.
//        template<typename format_context>
//        auto format(const Color &, format_context &);
//    };
//
//    template<>
//    struct Formatter<ServerState> : formatter<int> {
//        // parse is inherited from formatter<string_view>.
//        template<typename format_context>
//        auto format(const server_state &, format_context &);
//    };
//
//    template<>
//    struct Formatter<ErrCode> : formatter<int> {
//        // parse is inherited from formatter<string_view>.
//        template<typename format_context>
//        auto format(const errcode &, format_context &);
//    };
//}

#endif // !SHADOW_DEFINED_H
