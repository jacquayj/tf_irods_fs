#include "irods_file_system.h"

#include <cstdlib>

#include "tensorflow/core/platform/file_system_helper.h"
#include "tensorflow/core/platform/mutex.h"
#include "tensorflow/core/platform/str_util.h"

#include <irods/rodsErrorTable.h>
#include <irods/connection_pool.hpp>
#include <irods/filesystem.hpp>


namespace tensorflow {

namespace {
static const char* iRODSFileSystemAllocationTag = "iRODSFileSystemAllocation";
static const size_t iRODSReadAppendableFileBufferSize = 1024 * 1024;
static const int iRODSGetChildrenMaxKeys = 100;

class iRODSRandomAccessFile : public RandomAccessFile {
 public:
  iRODSRandomAccessFile() {}

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

class iRODSWritableFile : public WritableFile {
 public:
  iRODSWritableFile() {}

  Status Append(StringPiece data) override {
    rodsEnv env;

    if (getRodsEnv(&env) < 0) {
      std::cout << "lolx";
      return Status::OK();
    }
    rErrMsg_t errMsg;

    std::string host = "192.168.1.100";  
    std::string user = "rods";  
    std::string zone = "tempZone"; 

    const int connection_pool_size = 4;
    const int refresh_time_in_secs = 600;

    // Creates a connection pool that manages 4 rcComm_t connections
    // and refreshes each connection every 600 seconds.
    irods::connection_pool pool{connection_pool_size,
                                env.rodsHost,
                                env.rodsPort,
                                env.rodsUserName,
                                env.rodsZone,
                                refresh_time_in_secs};

    auto conn = pool.get_connection();

    return Status::OK();
  }

  Status Close() override {
    return Status::OK();
  }

  Status Flush() override { return Sync(); }

  Status Name(StringPiece* result) const override {
    return errors::Unimplemented("iRODSWritableFile does not support Name()");
  }

  Status Sync() override {
    return Status::OK();
  }

};

class iRODSReadOnlyMemoryRegion : public ReadOnlyMemoryRegion {
 public:
  iRODSReadOnlyMemoryRegion(std::unique_ptr<char[]> data, uint64 length)
      : data_(std::move(data)), length_(length) {}
  const void* data() override { return reinterpret_cast<void*>(data_.get()); }
  uint64 length() override { return length_; }

 private:
  std::unique_ptr<char[]> data_;
  uint64 length_;
};

}  // namespace

iRODSFileSystem::iRODSFileSystem() {}

iRODSFileSystem::~iRODSFileSystem() {}

Status iRODSFileSystem::NewRandomAccessFile(
    const string& fname, std::unique_ptr<RandomAccessFile>* result) {
  result->reset(new iRODSRandomAccessFile());

  return Status::OK();
}

Status iRODSFileSystem::NewWritableFile(const string& fname,
                                     std::unique_ptr<WritableFile>* result) {
  result->reset(new iRODSWritableFile());

  return Status::OK();
}

Status iRODSFileSystem::NewAppendableFile(const string& fname,
                                       std::unique_ptr<WritableFile>* result) {
  result->reset(new iRODSWritableFile());

  
  return Status::OK();
}

Status iRODSFileSystem::NewReadOnlyMemoryRegionFromFile(
    const string& fname, std::unique_ptr<ReadOnlyMemoryRegion>* result) {
  uint64 size;
  TF_RETURN_IF_ERROR(GetFileSize(fname, &size));
  std::unique_ptr<char[]> data(new char[size]);
  result->reset(new iRODSReadOnlyMemoryRegion(std::move(data), size));

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
