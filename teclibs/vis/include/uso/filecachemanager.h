#ifndef _FILE_CACHE_MANAGER_H_
#define _FILE_CACHE_MANAGER_H_

#include <cstdio>
#include <string>
#include <set>

typedef long long FileSize;

class USOFileCacheManager
{
public:

	USOFileCacheManager(bool clearOnDestruction = false);

	virtual ~USOFileCacheManager();

	std::string getDirectory(void) { return _directory; }
	
	void setDirectory(const std::string& dir) { _directory = dir; }

	FileSize getCacheSize(void) { return _cacheSize; }
	
	void setCacheSize(FileSize size) { _cacheSize = size; }

	bool cacheUsage(FileSize& usage);
	
	bool cacheUsagePercentage(double& usage);
	
	bool clearCacheDirectory(void);

	bool makeRoom(FileSize size);
	
	void printFileList(const char* str);

	void printUsage(const char* str);

protected:

	FileSize _cacheSize;
	std::string _directory;

	bool _clearOnDestruction;

	bool fileSize(const std::string& filename, FileSize& size);
	bool getFreeTotalSpace(const std::string& path, long long& fTotal, long long& fFree);

	struct file
	{
		file(FileSize psize, const std::string& filename)
		{
			size = psize;
			name = filename;
		}

		FileSize size;
		std::string name;
	};

	struct fileCmp
	{
		bool operator()(const file& f1, const file& f2);
	};

    typedef std::multiset<file, fileCmp> FileSet;
	typedef std::multiset<file, fileCmp>::iterator FileSetItr;

	bool scanFiles(FileSet& set);

	bool releaseFiles(FileSize size);

};

#endif

