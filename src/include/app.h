// server.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件.

#ifndef SHADOW_APP_H
#define SHADOW_APP_H

#include "define.h"
#include "singleton/singleton.h"
#include "quickjs.h"

namespace shadow {
    class App final : public Singleton<App> {
    public:
        explicit App(Token);

        ~App() override = default;

        /*
        * 初始化
        * @return errcode
        */
        ErrCode Init();

        /*
        * 启动
        * @return errcode
        */
        ErrCode Start();

        /*
        * 运行
        * @return errcode
        */
        ErrCode Run();

        /*pause
        * 暂停
        * @return errcode
        */
        ErrCode pause();

        /*resume
        * 恢复
        * @return errcode
        */
        ErrCode resume();

        /*
        * 停止
        * @return errcode
        */
        ErrCode Stop();

        /*
        * 退出
        * @return errcode
        */
        ErrCode Exit() noexcept;

        /*
        * 获取服务器状态
        * @return server_state
        */
        AppState getState();

    protected:

    private:
        std::atomic<AppState> mState;

        /*
        * 设置服务器状态
        * @return errcode
        */
        ErrCode setState(const AppState &state);

        bool isRunning();
    };
} // namespace shadow

#endif // !SHADOW_APP_H
