workspace(name = "bazelregistry_mongo_cxx_driver")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "bazel_skylib",
    urls = [
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.0.3/bazel-skylib-1.0.3.tar.gz",
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.0.3/bazel-skylib-1.0.3.tar.gz",
    ],
    sha256 = "1c531376ac7e5a180e0237938a2536de0c54d93f5c278634818e0efc952dd56c",
)
load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")
bazel_skylib_workspace()

local_repository(
    name = "bazelregistry_mongo_c_driver",
    path = "../mongo-c-driver",
)

load("@bazelregistry_mongo_c_driver//:config.bzl", "mongo_c_driver_common_config", "bson_config", "mongoc_config")

mongo_c_driver_common_config()
bson_config()
mongoc_config()

load("//:config.bzl", "bsoncxx_config", "mongocxx_config")
bsoncxx_config()
mongocxx_config()
