#include "pch.h"
#include "filesystem.h"
#include "core.h"
#include <filesystem>
#include <assert.h>

namespace fs = std::filesystem;

void FileSystem::Init()
{
	//std::cout << "FileSystem Inited\n";
}

void FileSystem::Free()
{
	//std::cout << "FileSystem Free\n";
}

bool static _exist(const char *path)
{
	fs::path fsPath = fs::u8path(path);

	if (fsPath.is_relative())
	{
		fs::path fsDataPath = fs::u8path(_core->GetDataPath());
		fsPath = fsDataPath / fsPath;
	}

	return fs::exists(fsPath);
}

bool FileSystem::FileExist(const char *path)
{
	return _exist(path);
}

bool FileSystem::DirectoryExist(const char *path)
{
	return _exist(path);
}

string FileSystem::GetWorkingPath(const char *path)
{
	if (strlen(path)==0)
		return fs::current_path().u8string();
	return canonical(fs::u8path(path)).u8string();
}

bool FileSystem::IsRelative(const char *path)
{
	fs::path fsPath = fs::u8path(path);
	return fsPath.is_relative();
}

auto DLLEXPORT FileSystem::OpenFile(const char *path, FILE_OPEN_MODE mode) -> File
{
	const bool read = (mode & FILE_OPEN_MODE::READ) == FILE_OPEN_MODE::READ;
	const bool write = (mode & FILE_OPEN_MODE::WRITE) == FILE_OPEN_MODE::WRITE;
	
	fs::path fsPath = fs::u8path(path);

	if (fsPath.is_relative())
	{
		fs::path fsDataPath = fs::u8path(_core->GetDataPath());
		fsPath = fsDataPath / fsPath;
	}

	if (read)
	{
		assert(fs::exists(fsPath));
	}

	std::ios_base::openmode cpp_mode;

	if (read)
		cpp_mode = std::ofstream::in;
	else // (write)
		cpp_mode = std::ofstream::out;

	if ((int)(FILE_OPEN_MODE::APPEND & mode))
		cpp_mode = std::ofstream::out | std::ofstream::app;

	if ((int)(mode & FILE_OPEN_MODE::BINARY))
		cpp_mode |= std::ofstream::binary;

	return File(cpp_mode, fsPath);
}

auto DLLEXPORT FileSystem::ClearFile(const char *path) -> void
{
	fs::path fsPath = fs::u8path(path);

	if (fsPath.is_relative())
	{
		fs::path fsDataPath = fs::u8path(_core->GetDataPath());
		fsPath = fsDataPath / fsPath;
	}

	if (fs::exists(fsPath))
	{
		std::ofstream ofs;
		mstring mPath = UTF8ToNative(fsPath.u8string());
		ofs.open(mPath, std::ofstream::out | std::ofstream::trunc);
		ofs.close();
	}
}

auto DLLEXPORT FileSystem::FilterPaths(const char *ext) -> std::vector<std::string>
{
	std::vector<std::string> files;
	std::string extension(ext);
	fs::path path = fs::u8path(_core->GetDataPath());
	fs::recursive_directory_iterator it(path);
	fs::recursive_directory_iterator endit;

	while (it != endit)
	{
		if(fs::is_regular_file(*it) && (extension=="") ? true : it->path().extension() == extension)
		{
			fs::path rel = fs::relative(*it, path);
			files.push_back(rel.string());
		}
		++it;
	}

	return files;
}

auto DLLEXPORT FileSystem::CreateMemoryMapedFile(const char* path) -> FileMapping
{
	FileMapping mapping;

	fs::path fsPath = fs::u8path(path);

	if (fsPath.is_relative())
	{
		fs::path fsDataPath = fs::u8path(_core->GetDataPath());
		fsPath = fsDataPath / fsPath;
	}

	std::wstring wpath = ConvertFromUtf8ToUtf16(fsPath.u8string());
	mapping.hFile = CreateFile(wpath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	assert(mapping.hFile != INVALID_HANDLE_VALUE);

	mapping.fsize = GetFileSize(mapping.hFile, nullptr);
	assert(mapping.fsize != INVALID_FILE_SIZE);

	mapping.hMapping = CreateFileMapping(mapping.hFile, nullptr, PAGE_READONLY, 0, 0, nullptr);
	assert(mapping.hMapping);

	mapping.ptr = (unsigned char*)MapViewOfFile(mapping.hMapping, FILE_MAP_READ, 0, 0, mapping.fsize);
	assert(mapping.ptr);

	return mapping;
}

File::File(const std::ios_base::openmode & fileMode, const std::filesystem::path & path)
{
	fsPath_ = path;	
	mstring mPath = UTF8ToNative(path.u8string());
	file_.open(mPath, fileMode);
}

File::~File()
{
	if (file_.is_open())
		file_.close();
}

File& File::operator=(const File && r)
{
	std::fstream tmp;
	file_.swap(tmp);
	fsPath_ = std::move(r.fsPath_);
	return *this;
}

File::File(const File && r)
{
	std::fstream tmp;
	file_.swap(tmp);
	fsPath_ = std::move(r.fsPath_);
}

auto DLLEXPORT File::Read(uint8 *pMem, size_t bytes) -> void
{
	file_.read((char *)pMem, bytes);
}

auto DLLEXPORT File::Write(const uint8 *pMem, size_t bytes) -> void
{
	file_.write((const char *)pMem, bytes);
}

auto DLLEXPORT File::WriteStr(const char *str) -> void
{
	file_.write(str, strlen(str));
}

auto DLLEXPORT File::FileSize() -> size_t
{
	return fs::file_size(fsPath_);
}

FileMapping::~FileMapping()
{
	if (ptr)
	{
		UnmapViewOfFile(ptr);
		CloseHandle(hMapping);
		CloseHandle(hFile);
		ptr = nullptr;
	}
}

FileMapping& FileMapping::operator=(FileMapping&& r)
{
	hFile = r.hFile;
	hMapping = r.hMapping;
	fsize = r.fsize;
	ptr = r.ptr;
	r.ptr = nullptr;
	return *this;
}

FileMapping::FileMapping(FileMapping&& r)
{
	hFile = r.hFile;
	hMapping = r.hMapping;
	fsize = r.fsize;
	ptr = r.ptr;
	r.ptr = nullptr;
}
