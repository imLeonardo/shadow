#include "jsmanager/jsmanager.h"

#include "log/interface.h"

namespace shadow {
    namespace js {
        Context::Context(uint64_t id): mID(id) {
            shadow::log::Info("create js context id:{}", this->mID);
            this->ptrJsRuntime = JS_NewRuntime();
            if(!this->ptrJsRuntime) throw JS_EXCEPTION;
            this->ptrJsContext = JS_NewContext(this->ptrJsRuntime);
            if(!this->ptrJsContext) throw JS_EXCEPTION;
        }

        Context::~Context() noexcept {
            JS_FreeContext(this->ptrJsContext);
            this->ptrJsContext = nullptr;

            JS_FreeRuntime(this->ptrJsRuntime);
            this->ptrJsRuntime = nullptr;
        }

        std::string Context::LoadFile(std::string filename) {
            FILE *fp = nullptr;
            errno_t err = fopen_s(&fp, filename.c_str(), "r");
            fseek(fp, 0, SEEK_END);
            long filesize = ftell(fp);
            fseek(fp, 0, SEEK_SET);
            char *buffer = static_cast<char*>(malloc(filesize + 1));
            fread(buffer, filesize, 1, fp);
            fclose(fp);
            buffer[filesize] = '\0';
            return std::string{buffer};
        }

        JSContext *Context::GetContext() {
            return this->ptrJsContext;
        }

        JSValue Context::EvalFile(const std::string filename, unsigned int evalFlag) {
            std::string jsFile = LoadFile(filename);
            return JS_Eval(this->ptrJsContext, jsFile.c_str(), jsFile.length(), "<eval>", JS_EVAL_TYPE_GLOBAL);
        }

        Manager::Manager(Singleton<Manager>::Token) {
            shadow::log::Info("construct jsmanager");
        }

        shadow::js::Context Manager::CreateContext() {
            this->mNowID++;
            this->jsContextPoolMap.emplace(this->mNowID, Context(this->mNowID));

            return this->jsContextPoolMap.find(this->mNowID)->second;
        }

        ErrCode Manager::DelContext(uint64_t id) {
            this->jsContextPoolMap.erase(id);

            return ErrCode::SUCCESS;
        }

        shadow::js::Context Manager::GetContext(uint64_t id) {
            return this->jsContextPoolMap.find(id)->second;
        }
    } // namespace js
} // namespace shadow
