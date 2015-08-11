/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_FILEINFO_H_
#define _VR_FILEINFO_H_

#include "Common.h"
#include "String.h"
#include "DateTime.h"

//! Main namespace of this library.
namespace vr {

/*!
  	\brief The FileInfo class provides system-independent file information.

	FileInfo provides information about a file's name and position (path) in the file system,
	its access rights and whether it is a directory or symbolic link, etc. The file's size and
	last modified/read times are also available. A FileInfo can point to a file with either a
	relative or an absolute file path. Absolute file paths begin with the directory separator "/"
	(or with a drive specification on Windows). All "\" separators are automatically converted
	to the normal "/" separator when a new path is set (at construction time or later). Multiple
	consecutive separators are also removed automatically. Relative file names begin with a directory
	name or a file name and specify a path relative to the current working directory.
 */
class VRBASE_EXPORT FileInfo
{
public:
	/*!
		Constructs an empty FileInfo object.
	 */
    FileInfo();

	/*!
		Constructs a new FileInfo that gives information about the given file. The file can include
		an absolute or relative path.
	 */
    FileInfo( const String& file );

	/*!
		Sets the file that the FileInfo provides information about to file.	The file can also include
		an absolute or relative file path. Absolute paths begin with the directory separator (e.g. "/"
		under Unix) or a drive specification (under Windows). Relative file names begin with a directory
		name or a file name and specify a path relative to the current directory.
	 */
	void setFile( const String& file );

	/*!
		Returns the name of the file, excluding the path.
		Example:
			FileInfo fileTest( "/mydir/myfile.txt" );
			String name = fileTest.getFileName();		// name = "myfile.txt"

			FileInfo fileTest( "/mydir/mysubdir" );
			String name = fileTest.getFileName();		// name = "mysubdir"
	 */
	String getFileName() const;

	//! Returns the file name, including the path (which may be absolute or relative).
    inline const String& getFilePath() const { return _file; }

	//! Returns the file's path. This doesn't include the file name.
	String getPath() const;

	/*!
        Returns an absolute path including the file name.
        The absolute path name consists of the full path and the file name. On Windows this
        will always begin 'D:/' where D is a drive letter.
        This function returns the same as getFilePath(), unless the path is relative.
     */
    String getAbsoluteFilePath() const;

	//! Returns a file's path absolute path. This doesn't include the file name.
	//! \see getAbsoluteFilePath().
	String getAbsolutePath() const;

	/*!
		Returns the base name of the file without the path.

		Example:
			FileInfo fileTest( "/mydir/myfile.txt" );
			String name = fileTest.getFileName();		// name = "myfile"
	 */
    String getBaseName() const;

	/*!
		Returns the complete base name of the file without the path.
		The complete base name consists of all characters in the file up to (but not
		including) the last '.' character.

		Example:
			FileInfo fileTest("/mydir/myfile.tar.gz");
			QString name = fileTest.getFileName();		// name = "myfile.tar"
	 */
    String getCompleteBaseName() const;

	/*!
		Returns the suffix of the file.
		The suffix consists of all characters in the file after (but not including) the last '.'.
	 */
	String getSuffix() const;

	/*!
		Returns the complete suffix of the file. The complete suffix consists of all characters
		in the file after (but not including) the first '.'.

		Example:

		FileInfo fi("/tmp/archive.tar.gz");
		String ext = fi.completeSuffix();  // ext = "tar.gz"
	 */
	String getCompleteSuffix() const;

	//! Returns the date and time when the file was last modified.
	//! If the file does not exist, the function return a null DateTime.
	DateTime getLastModified() const;

	//! Returns the date and time when the file was created.
	//! If the file does not exist, the function return a null DateTime.
	DateTime getCreated() const;

	/*!
		Returns the id of the group the file belongs to. On Windows and on systems where files do
		not have groups this function always returns ((uint32) -2). \see getOwnerId().
	 */
	uint32 getGroupId() const;

	/*!
		Returns the id of the owner of the file. On Windows and on systems where files do not have
		owners this function returns ((uint32) -2).
		\see getGroupId().
	 */
	uint32 getOwnerId() const;

	//! Returns true if the file exists; otherwise returns false.
	bool exists() const;

	//! Returns true if this object points to a directory; otherwise returns false.
	bool isDir() const;

	//! Returns true if this object points to a file. Returns false if the object points
	// to something which isn't a file, such as a directory.
	bool isFile() const;

	/*!
		Returns true if the directory's path is absolute; otherwise returns false.
		\see isAbsolutePath(), isRelative(), makeAbsolute(), and cleanPath().
	 */
	bool isAbsolute() const;

private:
	String _file;
};

} // namespace vr

#endif // _VR_FILEINFO_H_
