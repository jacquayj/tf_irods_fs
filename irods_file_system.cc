/* Copyright 2015 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#include "irods_file_system.h"

#include <cstdlib>

#include "tensorflow/core/platform/file_system_helper.h"
#include "tensorflow/core/platform/mutex.h"
#include "tensorflow/core/platform/path.h"
#include "tensorflow/core/platform/str_util.h"

namespace tensorflow {

namespace {
static const char* kS3FileSystemAllocationTag = "S3FileSystemAllocation";
static const size_t kS3ReadAppendableFileBufferSize = 1024 * 1024;
static const int kS3GetChildrenMaxKeys = 100;

class S3RandomAccessFile : public RandomAccessFile {
 public:
  S3RandomAccessFile(const string& bucket, const string& object,
                     std::shared_ptr<void> s3_client)
      : bucket_(bucket), object_(object), s3_client_(s3_client) {}

  Status Name(StringPiece* result) const override {
    return errors::Unimplemented("S3RandomAccessFile does not support Name()");
  }

  Status Read(uint64 offset, size_t n, StringPiece* result,
              char* scratch) const override {

    return Status::OK();
  }

 private:
  string bucket_;
  string object_;
  std::shared_ptr<void> s3_client_;
};

class S3WritableFile : public WritableFile {
 public:
  S3WritableFile(const string& bucket, const string& object,
                 std::shared_ptr<void> s3_client) {}

  Status Append(StringPiece data) override {
    return Status::OK();
  }

  Status Close() override {
    return Status::OK();
  }

  Status Flush() override { return Sync(); }

  Status Name(StringPiece* result) const override {
    return errors::Unimplemented("S3WritableFile does not support Name()");
  }

  Status Sync() override {
    return Status::OK();
  }

};

}  // namespace

S3FileSystem::S3FileSystem() {}

S3FileSystem::~S3FileSystem() {}

Status S3FileSystem::NewRandomAccessFile(
    const string& fname, std::unique_ptr<RandomAccessFile>* result) {
  return Status::OK();
}

Status S3FileSystem::NewWritableFile(const string& fname,
                                     std::unique_ptr<WritableFile>* result) {
  return Status::OK();
}

Status S3FileSystem::NewAppendableFile(const string& fname,
                                       std::unique_ptr<WritableFile>* result) {
  return Status::OK();
}

Status S3FileSystem::NewReadOnlyMemoryRegionFromFile(
    const string& fname, std::unique_ptr<ReadOnlyMemoryRegion>* result) {
  return Status::OK();
}

Status S3FileSystem::FileExists(const string& fname) {
  return Status::OK();
}

Status S3FileSystem::GetChildren(const string& dir,
                                 std::vector<string>* result) {
  return Status::OK();
}

Status S3FileSystem::Stat(const string& fname, FileStatistics* stats) {
  return Status::OK();
}

Status S3FileSystem::GetMatchingPaths(const string& pattern,
                                      std::vector<string>* results) {
  return Status::OK();
}

Status S3FileSystem::DeleteFile(const string& fname) {
  return Status::OK();
}

Status S3FileSystem::CreateDir(const string& dirname) {
  return Status::OK();
}

Status S3FileSystem::DeleteDir(const string& dirname) {
  return Status::OK();
}

Status S3FileSystem::GetFileSize(const string& fname, uint64* file_size) {
  return Status::OK();
}

Status S3FileSystem::RenameFile(const string& src, const string& target) {
  return Status::OK();
}

REGISTER_FILE_SYSTEM("s3", S3FileSystem);

}  // namespace tensorflow
