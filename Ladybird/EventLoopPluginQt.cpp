/*
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "EventLoopPluginQt.h"
#include "TimerQt.h"
#include <AK/Function.h>
#include <AK/NonnullRefPtr.h>
#include <QCoreApplication>
#include <QTimer>

namespace Ladybird {

EventLoopPluginQt::EventLoopPluginQt() = default;
EventLoopPluginQt::~EventLoopPluginQt() = default;

void EventLoopPluginQt::spin_until(JS::SafeFunction<bool()> goal_condition)
{
    while (!goal_condition())
        QCoreApplication::processEvents(QEventLoop::ProcessEventsFlag::AllEvents | QEventLoop::ProcessEventsFlag::WaitForMoreEvents);
}

void EventLoopPluginQt::deferred_invoke(JS::SafeFunction<void()> function)
{
    VERIFY(function);
    QTimer::singleShot(0, [function = move(function)] {
        function();
    });
}

NonnullRefPtr<Web::Platform::Timer> EventLoopPluginQt::create_timer()
{
    return TimerQt::create();
}

void EventLoopPluginQt::quit()
{
    QCoreApplication::quit();
}

}
