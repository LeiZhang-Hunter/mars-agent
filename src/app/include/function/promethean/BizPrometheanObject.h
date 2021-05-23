//
// Created by zhanglei on 2021/5/22.
//

#ifndef MARS_AGENT_BIZPROMETHEANOBJECT_H
#define MARS_AGENT_BIZPROMETHEANOBJECT_H

#include <utility>

#include "common/MarsJson.h"
#include "promethean/MarsPrometheanObject.h"

namespace function {
    namespace promethean {
        class BizPrometheanObject {
        public:
            BizPrometheanObject(std::shared_ptr<promethean::MarsPrometheanObject>  object) : jsonParser(std::make_shared<common::MarsJson>()),
                                    prometheanObject (std::move(object)){

            }
            void parser(const std::string& content);

        private:
            void dispatch(const std::string& name,
                          const std::string& type,
                          const std::map<std::string,
                                  std::string>& labels, double value);
            std::shared_ptr<common::MarsJson> jsonParser;
            std::shared_ptr<promethean::MarsPrometheanObject> prometheanObject;
        };
    }
}


#endif //MARS_AGENT_BIZPROMETHEANOBJECT_H
