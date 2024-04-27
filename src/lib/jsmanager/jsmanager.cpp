#include "jsmanager/jsmanager.h"

#include "log/interface.h"

namespace shadow {
    namespace js {
        Context::Context(uint64_t id): mID(id) {
            shadow::log::Info("create js context id:{}", this->mID);
            this->jsRuntime = JS_NewRuntime();
            if(!this->jsRuntime) throw JS_EXCEPTION;
            this->jsContext = JS_NewContext(this->jsRuntime);
            if(!this->jsContext) throw JS_EXCEPTION;
        }

        Context::~Context() noexcept {
            JS_FreeContext(this->jsContext);
            this->jsContext = nullptr;

            JS_FreeRuntime(this->jsRuntime);
            this->jsRuntime = nullptr;
        }

        std::string Context::LoadFile(std::string filename) {
            FILE  *fp = nullptr;
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
            return this->jsContext;
        }

        JSValue Context::EvalFile(const std::string filename, unsigned int evalflag) {
            std::string jsFile = LoadFile(filename);
            return JS_Eval(this->jsContext, jsFile.c_str(), jsFile.length(), "<eval>", JS_EVAL_TYPE_GLOBAL);
        }

        Manager::Manager(Singleton<Manager>::Token) {
            shadow::log::Info("construct jsmanager");
        }

        shadow::js::Context Manager::CreateContext() {
            this->mNowID++;
            this->jsContextPool.emplace(this->mNowID, Context(this->mNowID));

            return this->jsContextPool.find(this->mNowID)->second;
        }

        ErrCode Manager::DelContext(uint64_t id) {
            this->jsContextPool.erase(id);

            return ErrCode::SUCCESS;
        }

        shadow::js::Context Manager::GetContext(uint64_t id) {
            return this->jsContextPool.find(id)->second;
        }
    } // namespace js
} // namespace shadow
