//
// Created by zhanglei on 2021/5/22.
//

#include "promethean/MarsPrometheanObject.h"

using namespace function;
using namespace prometheus;

promethean::MarsPrometheanObject::MarsPrometheanObject() {
    registry = std::make_shared<Registry>();
}

prometheus::Family<prometheus::Counter> &promethean::MarsPrometheanObject::regCountPacket(const std::string& name)
{
    //下面已经是原子的了
    auto& packet_counter = (prometheus::BuildCounter()
            .Name(name)
            .Register(*registry));
    return packet_counter;
}

prometheus::Family<prometheus::Gauge> &promethean::MarsPrometheanObject::regGaugePacket(const std::string& name)
{
    //下面已经是原子的了
    auto& packet_counter = (prometheus::BuildGauge()
            .Name(name)
            .Register(*registry));
    return packet_counter;
}

prometheus::Family<prometheus::Summary> &promethean::MarsPrometheanObject::regSummaryPacket(const std::string& name)
{
    //下面已经是原子的了
    auto& packet_counter = (prometheus::BuildSummary()
            .Name(name)
            .Register(*registry));
    return packet_counter;
}

prometheus::Family<prometheus::Histogram> &promethean::MarsPrometheanObject::regHistogramPacket(const std::string& name)
{
    //下面已经是原子的了
    auto& packet_counter = (prometheus::BuildHistogram()
            .Name(name)
            .Register(*registry));
    return packet_counter;
}