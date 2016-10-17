// Copyright 2016 MongoDB Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "catch.hpp"

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/document/value.hpp>
#include <bsoncxx/document/view.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/types/value.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/options/create_view.hpp>

using namespace bsoncxx;
using namespace mongocxx;

TEST_CASE("create_view", "[create_view]") {
    instance::current();

    options::create_view cv;

    SECTION("Can be exported to a document") {
        auto collation_en_US = builder::stream::document{} << "locale"
                                                           << "en_US" << builder::stream::finalize;

        cv.collation(collation_en_US.view());
        cv.pipeline(std::move(pipeline{}.limit(1)));

        auto doc = cv.to_document();
        document::view doc_view{doc.view()};

        // "collation" field is set correctly.
        document::element collation{doc_view["collation"]};
        REQUIRE(collation);
        REQUIRE(collation.type() == type::k_document);
        REQUIRE(collation.get_document().value == collation_en_US);

        // "pipeline" field is set correctly.
        document::element pipeline_ele{doc_view["pipeline"]};
        REQUIRE(pipeline_ele);
        REQUIRE(pipeline_ele.type() == type::k_array);
        REQUIRE(pipeline_ele.get_array().value == pipeline{}.limit(1).view_array());
    }
}
