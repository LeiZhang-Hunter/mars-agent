//
// Created by zhanglei on 2021/5/22.
//

#ifndef MARS_AGENT_MARSPROMETHEANOBJECT_H
#define MARS_AGENT_MARSPROMETHEANOBJECT_H

#include <prometheus/counter.h>
#include <prometheus/summary.h>
#include <prometheus/histogram.h>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>
#include <prometheus/text_serializer.h>

#define GET_PROMETHEAN_OBJECT(object, function) object->reg##function##Packet


namespace function {
    namespace promethean {
        class MarsPrometheanObject {
        public:
            //初始化对象
            MarsPrometheanObject();

            //获取packCounter
//            prometheus::Family<prometheus::Counter> &getPacketCounter(const std::string& name);

            //注册packCounter
            prometheus::Family<prometheus::Counter> &regCountPacket(const std::string& name);

            prometheus::Family<prometheus::Gauge> &regGaugePacket(const std::string& name);

            prometheus::Family<prometheus::Summary> &regSummaryPacket(const std::string& name);

            prometheus::Family<prometheus::Histogram> &regHistogramPacket(const std::string& name);

            std::string serialize()
            {
                return serializer.Serialize(registry->Collect());
            }

            ~MarsPrometheanObject() {

            }
        private:
            std::shared_ptr<prometheus::Registry> registry;
            prometheus::TextSerializer serializer;
            std::map<std::string, prometheus::Family<prometheus::Counter> &> metrics;
        };
    }
}

#endif //MARS_AGENT_MARSPROMETHEANOBJECT_H
