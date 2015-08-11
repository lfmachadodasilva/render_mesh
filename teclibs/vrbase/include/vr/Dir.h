/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_DIR_H_
#define _VR_DIR_H_

#include "String.h"
#include "RegExp.h"

//! Main namespace of this library.
namespace vr {

/*!
	\brief The Dir class provides access to directory structures and their contents.

	A Dir is used to manipulate path names, access information regarding paths and files,
	and manipulate the underlying file system. This class uses "/" as a universal directory
	separator in the same way that "/" is used as a path separator in URLs. If a path is
	given with "\" separator, it will be automatically converted to a path containing
	only "/" separators. A Dir can point to a file using either a relative or an absolute
	path. Absolute paths begin with the directory separator (optionally preceded by a drive
	specification under Windows). Relative file names begin with a directory name or a file
	name and specify a path relative to the current directory.
 */
class VRBASE_EXPORT Dir
{
public:
	/*!
		Returns the absolute path of the application's current directory.
		In some operating systems an error can occur if the current path exceeds 255 chars.
		If any error occurs, and empty string is returned.
	 */
	static String currentPath();

	/*!
		Normalizes and cleans the given path. The function converts all
		separators "\" to "/" and removes all multiple directory separators
		"/" and resolves any "."s or ".."s found in the path.
		Symbolic links are kept. This function does not return the canonical
		path, but rather the simplest version of the input.
		For example, "./local" becomes "local", "local/../bin" becomes "bin"
		and "/local/usr/../bin" becomes "/local/bin".
	 */
	static String cleanPath( const String& path );

	/*!
		Takes two absolute paths, and returns the path to filePath relative from basePath.

		Example:
			For basePath "C:/project/target" and filePath "C:/teste.txt", the relative file path is
			"../../teste.txt.
			For basePath "C:/" and fileName "C:/project/teste.txt", the relative file path is
			"project/teste.txt"
	 */
	static String relativePath( const vr::String& basePath, const vr::String& filePath );

	/*!
		Returns true if path is absolute; returns false if it is relative.
		\see isAbsolute(), isRelativePath(), makeAbsolute(), and cleanPath().
	 */
	static bool isAbsolutePath( const String& path );

	/*!
		Returns true if path is relative; returns false if it is absolute.
		\see isAbsolute(), isAbsolutePath(), makeAbsolute(), and cleanPath().
	 */
	inline static bool isRelativePath( const String& path ) { return !isAbsolutePath( path ); }

	/*!
		Creates a directory defined by a specific path. If any directory component in dirPath
		does not exist or is a dangling symbolic link, no new directory is created and the
		function returns false. If the new directory is successfully created, the function returns
		true.
		\see makeSubDir().
	 */
	static bool makeDir( const String& dirPath );

	/*!
		Creates the directory path dirPath. The function will create all parent directories
		necessary to create the directory. Returns true if successful; otherwise returns false.
		If any of the subpaths of the given path exists, it will not be altered and this
		function will try to create all other subpaths. If all subpaths already exists this
		function also returns true.
		\see removePath(), makeDir(), makeSubDir().
	 */
	static bool makePath( const String& dirPath );

	/*!
		Removes the directory specified by dirName. The directory must be empty for removeDir()
		to succeed. Returns true if successful; otherwise returns false.
		\see makeDir(), makeSubDir().
	 */
	static bool removeDir( const String& dirName );

	/*!
		Removes the directory path dirPath. The function will remove all parent directories
		in dirPath, provided that they are empty. This is the opposite of makePath( dirPath ).
		Returns true if successful; otherwise returns false.
		Differently from makePath, this function will return false if any subpath of the
		given path do not exist.
		\see makePath().
	 */
	static bool removePath( const String& dirPath );

public:
	//! Constructs a Dir pointing to the program's working directory (".").
	Dir();

	//! Constructs a Dir pointing to the given directory path.
	Dir( const String& path );

	//! Destroys the Dir object.
	~Dir();

	/*!
		Sets the path of the directory to path. The path is cleaned of redundant
		".", ".." and of multiple separators. No check is made to see whether a
		directory with this path actually exists; but you can check for yourself
		using exists(). The path can be either absolute or relative. Absolute paths
		begin with the directory separator "/" (optionally preceded by a drive
		specification under Windows). Relative file names begin with a directory
		name or a file name and specify a path relative to the current directory.
		An example of an absolute path is the string "/tmp/quartz", a relative path
		might look like "src/fatlib".
	    \see getPath(), getAbsolutePath(), getExists(), cleanPath(), getDirName(),
		getAbsoluteFilePath(), isRelative(), and makeAbsolute().
	 */
	void setPath( const String& path );

	/*!
		Returns the path. This may contain symbolic links, but never contains
		redundant ".", ".." or multiple separators.

		The returned path can be either absolute or relative. \see setPath().
	 */
	const String& getPath() const;

	/*!
		Returns the name of the directory; this is not the same as the path, e.g.
		a directory with the name "mail", might have the path "/var/spool/mail".
		If the directory has no name (e.g. it is the root directory) an empty string is
		returned. No check is made to ensure that a directory with this name actually exists.
		\see exists(), getPath(), getFilePath(), getAbsolutePath(), and getAbsoluteFilePath().
     */
	String getDirName() const;

	/*!
		Returns the absolute path (a path that starts with "/" or with a drive specification),
		which may contain symbolic links, but never contains redundant ".", ".." or multiple
		separators.
	 */
	String getAbsolutePath() const;

	/*!
		Returns true if the directory exists; otherwise returns false.
		(If a file with the same name is found this function will return false).
	 */
	bool exists() const;

	//! Returns true if the directory is the root directory; otherwise returns false.
	bool isRoot() const;

	/*!
		Returns true if the directory's path is absolute; otherwise returns false.
		\see isAbsolutePath(), isRelative(), makeAbsolute(), and cleanPath().
	 */
	bool isAbsolute() const;

	/*!
		Returns true if the directory's path is relative; otherwise returns false.
		\see isAbsolutePath(), isAbsolute(), makeAbsolute(), and cleanPath().
	 */
	inline bool isRelative() const { return !isAbsolute(); }

	/*!
		Returns a list of the names of all the files and directories in the directory,
		filtered by the given filter patterns. Returns an empty list if the
		directory is unreadable, does not exist, an invalid RegExp pattern is given,
		or if nothing matches the valid filter specification. The filterPattern must
		be in the form of vr::RegExp class pattern. Depending on the operating system,
		this method can throw an IOException if the Dir's path exceeds 256 chars.
		\see RegExp.
	*/
	void getEntryList( const String& filterPattern, StringList& result );

	/*!
		Returns all entries of the Dir directory. Returns an empty list if the
		directory is unreadable, does not exist. Note that this is the same as
		calling getEntryList with a filter pattern of "*", except that it is
		more efficient because it uses no regular expression matching.
	 */
	void getEntryList( StringList& result );

	/*!
		Changes the Dir's directory to dirName.

		Returns true if the new directory exists; otherwise
		returns false. Note that the logical cd() operation is not performed if the
		new directory does not exist.

		Calling cd( ".." ) is equivalent to calling cdUp().

		\see cdUp(), exists(), and getPath().
	 */
	bool cd( const String& dirName );

	/*!
		Changes directory by moving one directory up from the Dir's current directory.
		Returns true if the new directory exists and is readable; otherwise returns false.
		Note that the logical cdUp() operation is not performed if the new directory does
		not exist.
		\see cd(), exists(), and getPath().
	 */
	bool cdUp();

	/*!
		Converts the directory path to an absolute path. If it is already absolute
		nothing happens. Returns true if the conversion succeeded; otherwise returns false.
		\see isAbsolute(), isAbsolutePath(), isRelative(), and cleanPath().
	 */
	bool makeAbsolute();

private:
	String _path;
};

}; // namespace vr


#endif
