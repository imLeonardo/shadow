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
        * @return ErrCode
        */
        ErrCode Init();

        /*
        * 启动
        * @return ErrCode
        */
        ErrCode Start();

        /*
        * 运行
        * @return ErrCode
        */
        ErrCode Run();

        /*pause
        * 暂停
        * @return ErrCode
        */
        ErrCode Pause();

        /*resume
        * 恢复
        * @return ErrCode
        */
        ErrCode Resume();

        /*
        * 停止
        * @return ErrCode
        */
        ErrCode Stop();

        /*
        * 退出
        * @return ErrCode
        */
        ErrCode Exit() noexcept;

        /*
        * 获取状态
        * @return AppState
        */
        AppState GetAppState();

    protected:

    private:
        std::atomic<AppState> mAppState;

        /*
        * 设置服务器状态
        * @return ErrCode
        */
        ErrCode SetAppState(const AppState &);

        bool IsRunning();
    };
} // namespace shadow

#endif // !SHADOW_APP_H
