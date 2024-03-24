//
// Created by leo on 2024/1/6.
//

#include <cstdio>
#include <unordered_map>
//#include <google/protobuf/util/json_util.h>

#include "define.h"
#include "echo_service.pb.h"
#include "test.h"
#include <vector>

int main(int argc, char *argv[]) {
//    ::google::protobuf::util::JsonParseOptions stOption;
//    stOption.ignore_unknown_fields = true;
//
//    test::GMCSMsgReq gmcsMsgReq;
//    std::string jsonReq = R"({"role_id":1408259647936361,"msg_body":"eyJtc2dfaGVhZCI6eyJtc2dJZCI6MTA1MX0sIm1zZ19ib2R5IjoiZXlKeWIyeGxYMmxrSWpvaU1UUXdPREkxT1RZME56a3pOak0yTVNJc0ltMXpaMmxrSWpvaU1UQTFNU0o5In0="})";
//    ::google::protobuf::util::JsonStringToMessage(jsonReq, &gmcsMsgReq, stOption);
//    std::cout << "gmcsMsgReq: " << gmcsMsgReq.DebugString();
//
//    test::CSMsgReq csMsgReq;
//    ::google::protobuf::util::JsonStringToMessage(gmcsMsgReq.msg_body(), &csMsgReq, stOption);
//    std::cout << "csMsgReq: " << csMsgReq.DebugString();
//    std::unordered_map<int64_t, std::shared_ptr<test::ClassA>> poolMap;
//    auto ptrClassA = std::make_shared<test::ClassA>();
//    printf("1: %p\n", ptrClassA.get());
//    poolMap.emplace(1, ptrClassA);
//    auto ptrClassA2 = poolMap.find(1)->second;
//    ptrClassA = nullptr;
//    ptrClassA->print();
//    printf("2: %p, %p\n", &ptrClassA, &ptrClassA2);
    std::map<std::tuple<int32_t>, int32_t> map1;
    std::tuple<int32_t> tuple{std::move(1)};
    auto i = map1.find(tuple);
    if(i != map1.end()){
        printf("%d", i->second);
    }
}