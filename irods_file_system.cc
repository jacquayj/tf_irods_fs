#include "irods_file_system.h"

#include <cstdlib>

#include "tensorflow/core/platform/file_system_helper.h"
#include "tensorflow/core/platform/mutex.h"
#include "tensorflow/core/platform/path.h"
#include "tensorflow/core/platform/str_util.h"

namespace tensorflow {

namespace {
static const char* iRODSFileSystemAllocationTag = "iRODSFileSystemAllocation";
static const size_t iRODSReadAppendableFileBufferSize = 1024 * 1024;
static const int iRODSGetChildrenMaxKeys = 100;

class iRODSRandomAccessFile : public RandomAccessFile {
 public:
  iRODSRandomAccessFile(const string& bucket, const string& object,
                     std::shared_ptr<void> s3_client)
      : bucket_(bucket), object_(object), s3_client_(s3_client) {}

  Status Name(StringPiece* result) const override {
    return errors::Unimplemented("iRODSRandomAccessFile does not support Name()");
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

iRODSFileSystem::iRODSFileSystem() {}

iRODSFileSystem::~iRODSFileSystem() {}

Status iRODSFileSystem::NewRandomAccessFile(
    const string& fname, std::unique_ptr<RandomAccessFile>* result) {
  return Status::OK();
}

Status iRODSFileSystem::NewWritableFile(const string& fname,
                                     std::unique_ptr<WritableFile>* result) {
  return Status::OK();
}

Status iRODSFileSystem::NewAppendableFile(const string& fname,
                                       std::unique_ptr<WritableFile>* result) {
  return Status::OK();
}

Status iRODSFileSystem::NewReadOnlyMemoryRegionFromFile(
    const string& fname, std::unique_ptr<ReadOnlyMemoryRegion>* result) {
  return Status::OK();
}

Status iRODSFileSystem::FileExists(const string& fname) {
  return Status::OK();
}

Status iRODSFileSystem::GetChildren(const string& dir,
                                 std::vector<string>* result) {
  return Status::OK();
}

Status iRODSFileSystem::Stat(const string& fname, FileStatistics* stats) {
  return Status::OK();
}

Status iRODSFileSystem::GetMatchingPaths(const string& pattern,
                                      std::vector<string>* results) {
  return Status::OK();
}

Status iRODSFileSystem::DeleteFile(const string& fname) {
  return Status::OK();
}

Status iRODSFileSystem::CreateDir(const string& dirname) {
  return Status::OK();
}

Status iRODSFileSystem::DeleteDir(const string& dirname) {
  return Status::OK();
}

Status iRODSFileSystem::GetFileSize(const string& fname, uint64* file_size) {
  return Status::OK();
}

Status iRODSFileSystem::RenameFile(const string& src, const string& target) {
  return Status::OK();
}

REGISTER_FILE_SYSTEM("irods", iRODSFileSystem);

}  // namespace tensorflow
