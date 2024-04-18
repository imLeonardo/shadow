#ifndef SHADOW_CONFIGURE_H
#define SHADOW_CONFIGURE_H

#include "define.h"
#include "singleton/singleton.h"

namespace shadow {
    class Configure final: public shadow::Singleton<Configure> {
    public:
        explicit Configure(Singleton<Configure>::Token);

        void init(const char *);

        void print();

        int getInt(const char *);

        const char* getString(const char *);
    private:

    };
} // namespace shadow

#endif // !SHADOW_CONFIGURE_H