#pragma once

#include "value_holder_node.h"

#include <utility>


namespace core::actors {

    struct IActor;

    struct IMsg {
        using EventHandler = void (*)(IActor*);

        IMsg(EventHandler handler)
            : Handler(handler)
        {}

        IMsg(const IMsg&) = delete;
        IMsg(IMsg&) = delete;
        IMsg(IMsg&&) = delete;

        virtual ~IMsg() = default;

    protected:
        EventHandler Handler;
    };

    using IMsgHolderNode = ValueHolderNode<IMsg*>;

}