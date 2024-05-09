//
// Created by leo on 2024/1/6.
//

// #include <cstdio>
// #include <iostream>
//
// #include <vector>
// #include <unordered_map>

// #include <google/protobuf/util/json_util.h>

// #include "define.h"
// #include "test.h"
// #include "echo_service.pb.h"
// #include "javascript/quickjs/quickjs-libc.h"

import <cstdio>;

int main(int argc, char **argv) {
    //    // 创建一个新的js环境
    //    JSRuntime *rt = JS_NewRuntime();
    //    if(!rt) {
    //        std::cerr << "Failed to create a QuickJS runtime." << std::endl;
    //        return 1;
    //    }
    //
    //    JSContext *ctx = JS_NewContext(rt);
    //    if(!ctx) {
    //        std::cerr << "Failed to create a QuickJS context." << std::endl;
    //        JS_FreeRuntime(rt);
    //        return 1;
    //    }
    //
    //    // 读取js文件
    //    uint8_t *ptrJSBuf;
    //    size_t nBufLen;
    //    const char *ptrJSFile = "./script/main.js";
    //    ptrJSBuf = js_load_file(ctx, &nBufLen, ptrJSFile);
    //    // 执行一个简单的js代码
    //    JSValue jsRes = JS_Eval(ctx, reinterpret_cast<char *>(ptrJSBuf), nBufLen, ptrJSFile, JS_EVAL_TYPE_GLOBAL);
    //    if(JS_IsException(jsRes)) {
    //        js_std_dump_error(ctx);
    //        return -1;
    //    }
    //
    //    // 清理js环境
    //    JS_FreeValue(ctx, jsRes);
    //    JS_FreeContext(ctx);
    //    JS_FreeRuntime(rt);

    std::cout << "1111111111111111" << std::endl;

    return 0;
}
