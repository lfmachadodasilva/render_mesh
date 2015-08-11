/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_LIBRARY_H_
#define _VR_LIBRARY_H_

#include "String.h"

//! Main namespace of this library.
namespace vr {

/*!
	\brief The Library class class loads shared libraries at runtime.

    An instance of a Library object operates on a single shared object file (which we call a "Library", but is also known as a
    "DLL"). The class Library provides access to the functionality in the library in a platform independent way. You can either
    pass a file name in the constructor, or set it explicitly with setFileName(). When loading the library, this class searches
    in all the system-specific library locations (e.g. \c LD_LIBRARY_PATH on Unix), unless the file name has an absolute path.
    If the file cannot be found, Library tries the name with different platform-specific file suffixes, like ".so" on Unix, ".dylib"
    on the Mac, or ".dll" on Windows. This makes possible to specify shared libraries that are only identified by their basename
    (i.e. without their suffix), so the same code will work on different operating systems.
 */
class VRBASE_EXPORT Library
{
public:
    enum LoadHint
    {
        ResolveAllSymbolsHint = 0x01,     //!< Relocations are performed when the object is loaded.
        ExportExternalSymbolsHint = 0x02, //!< All symbols are available for relocation processing of other modules.
        LoadArchiveMemberHint = 0x04      //!< Relocations are performed at an implementation-dependent time.
    };
    
    /*!
        Returns true if \a fileName has a valid suffix for a loadable library; otherwise returns false.

        \table
        \header \i Platform \i Valid suffixes
        \row \i Windows     \i \c .dll
        \row \i Unix/Linux  \i \c .so
        \row \i Mac OS X    \i \c .dylib, \c .bundle, \c .so
        \endtable

        Trailing versioning numbers on Unix are ignored.
     */
    static bool isLibrary( const String& fileName );

public:
    //! Constructs a Library object specified by fileName, which defaults to an empty string. If no fileName is given, you must call
    //! setFileName() prior to using other methods.
	Library( const String& fileName = "" );

    //! Unloads library if it is already loaded.
    ~Library();

    //! Returns a text string with the description of the last error that occurred. Currently, errorString will only be set if load(),
    //! unload() or resolve() for some reason fails.
    inline const String& getErrorString() const { return _errorString; }

    //! Returns last successfully loaded library file name.
    inline const String& getFileName() const { return _fileName; }

    //! Returns true if the library is loaded; otherwise returns false.
    bool isLoaded() const;

    /*!
        Loads the library and returns true if the library was loaded successfully; otherwise returns false. Since resolve() always
        calls this function before resolving any symbols it is not necessary to call it explicitly. In some situations you might want the
        library loaded in advance, in which case you would use this function. \see unload()
     */
    bool load();

    //! Returns the load Library's hints.
    LoadHint loadHints() const;

    /*!
        Returns the address of the exported symbol. The library is loaded if necessary. The function returns 0 if the symbol could not be
        resolved or if the library could not be loaded.
     */
    void* resolve( const char* symbol );

    /*!
        We recommend omitting the file's suffix in the file name, since Library will automatically look for the file with the appropriate
        suffix (\see isLibrary()).

        When loading the library, Library searches in all system-specific library locations (e.g. \c LD_LIBRARY_PATH on Unix), unless the
        file name has an absolute path. After loading the library successfully, fileName() returns the fully-qualified file name of
        the library, including the full path to the library if one was given in the constructor or passed to setFileName().

        For example, after successfully loading the "GL" library on Unix platforms, fileName() will return "libGL.so". If the file name was
        originally passed as "/usr/lib/libGL", fileName() will return "/usr/lib/libGL.so".
     */
    void setFileName( const String& fileName );

    /*!
        You can give some hints on how the symbols are resolved. Usually, the symbols are not resolved at load time, but resolved lazily,
        (that is, when resolve() is called). If you set the loadHint to ResolveAllSymbolsHint, then all symbols will be resolved at load time
        if the platform supports it. Setting ExportExternalSymbolsHint will make the external symbols in the library available for resolution
        in subsequent loaded libraries. If LoadArchiveMemberHint is set, the file name is composed of two components: A path which is a
        reference to an archive file followed by the second component which is the reference to the archive member. For instance, the fileName
        \c libGL.a(shr_64.o) will refer to the library \c shr_64.o in the archive file named \c libGL.a. This is only supported on the AIX platform.
        The interpretation of the load hints is platform dependent, and if you use it you are probably making some assumptions on which platform
        you are compiling for, so use them only if you understand the consequences of them. By default, none of these flags are set, so libraries
        will be loaded with lazy symbol resolution, and will not export external symbols for resolution in other dynamically-loaded libraries.
     */
    void setLoadHints( LoadHint hints );

    /*!
        Unloads the library and returns true if the library could be unloaded; otherwise returns false. This happens automatically on application
        termination, so you shouldn't normally need to call this function. If other instances of Library are using the same library, the call will
        fail, and unloading will only happen when every instance has called unload(). Note that on Mac OS X 10.3 (Panther), dynamic libraries cannot
        be unloaded. \see resolve(), load()
     */
    bool unload();

private:
	Library( const Library& other );
	Library& operator=( const Library& other );

    bool loadLibrary();
    bool unloadLibrary();
    void* resolveSymbol( const char* symbol );

private:
	String _fileName;
    String _errorString;

    bool _isLoaded;
    void* _handlePointer;
    unsigned char _loadHints;
};

}; // namespace vr

#endif // _VR_LIBRARY_H_
