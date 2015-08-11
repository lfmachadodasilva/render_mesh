/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_STRING_H_
#define _VR_STRING_H_

//! \file String.h String classes patterned after Qt.

#include "Common.h"

#include <vector>
#include <ostream>

#include "Vec3.h"
#include "Quat.h"

extern "C" {
#ifndef BSTRLIB_INCLUDE
    struct tagbstring {
        int mlen;
        int slen;
        unsigned char* bstr;
    };
#endif
}

namespace vr {
/*!
    \addtogroup text Text Processing
    @{
 */

//! Whether a String operation is case sensitive.
enum CaseSensitivity
{
    CaseInsensitive,
    CaseSensitive
};

class String;
class RegExp;

//! A list of Strings.
class VRBASE_EXPORT StringList : public std::vector<String>
{
public:
    //! Constructs an empty String list.
    StringList();

    //! Constructs a String list that contains the given String, str.
    StringList( const String& str );

    //! Constructs a copy of the <tt>other</tt> String list.
    StringList( const StringList& other );

    /*!
        Returns true if the list contains the String <tt>str</tt>; otherwise returns false.
        The search is case insensitive if <tt>cs</tt> is CaseInsensitive; the search is
        case sensitive by default.
     */
    bool contains( const String& str, CaseSensitivity cs = CaseSensitive ) const;

    /*!
        Returns a valid id if the list contains the String <tt>str</tt>; otherwise returns -1.
        The search is case insensitive if <tt>cs</tt> is CaseInsensitive; the search is
        case sensitive by default.
     */
    int indexOf( const String& str, CaseSensitivity cs = CaseSensitive ) const;

    //! Joins all the String list's Strings into a single String with each element separated by
    //! the the given separator (which can be an empty String).
    String join( const String& separator ) const;

    //! Appends the given String, <tt>str</tt>, to this String list and returns a reference
    //! to the String list.
    StringList& operator<<( const String& str );

    //! Appends the <tt>other</tt> String list to the String list and returns a reference to
    //! the latter String list. 
    StringList& operator<<( const StringList& other );
};

/*!
	Utility class to format String's in a type-safe manner (see String::format()).

	At creation, a StringFormatter receives a String (to be formatted) and a pattern that specifies
	how to format the String. The pattern may contain a variable number of numeric markers (e.g. \%1, \%2, ..., \%n),
	<b>up to \%99</b>, which are replaced by arguments passed to the StringFormatter through calls to arg().

	When all arguments have been specified, you must call done() to actually format the String.
	A call to arg() may raise a StringException if all expected arguments have already been specified.

	If you create a StringFormatter() and do not call arg() or done() on it, a StringException() will be raised.
	A call to arg() must be chained with other calls to arg(), and the chain must end with a call to done().
 */
class VRBASE_EXPORT StringFormatter
{
public:
	/*!
		Creates a StringFormatter to format the String <tt>str</tt> using the specified <tt>pattern</tt>.
		The <tt>pattern</tt> must be a String embedded with numeric markers, starting at \%1 and up to the maximum of \%99.
		Markers can appear in random order and multiple times in the String (e.g. "\%2 \%1 \%2").
		To include a plain '%' character in the pattern String, use "%%".
		\throw StringException if the pattern String contain malformed markers.
	 */
	//@{
	StringFormatter( String* str, const char* pattern );
	StringFormatter( String* str, const String* pattern );
	//@}

	//! Copy constructor
	inline StringFormatter( const StringFormatter& other )
	{
		_data = other._data;	// copy other's data
		const_cast<StringFormatter&>(other)._data = 0;		// invalidate other
	}

	//! Destructor.
	~StringFormatter();

    /*!
		Specifies a value for markers. First call is for occurrences of \%1, second call for \%2, and so on.

        The <tt>fieldWidth</tt> value specifies the minimum amount of space that a is padded to and
        filled with the character <tt>fillChar</tt>. A positive value will produce right-aligned
        text, whereas a negative value will produce left-aligned text.
     */
	//@{
    StringFormatter arg( const String& a, int fieldWidth = 0, char fillChar = ' ' );
	StringFormatter arg( const char* a, int fieldWidth = 0, char fillChar = ' ' );
    StringFormatter arg( const char* a, int len, int fieldWidth, char fillChar );
	//@}

    /*!
		Specifies a value for markers. First call is for occurrences of \%1, second call for \%2, and so on.

		The pointer <tt>a</tt> is formatted in uppercase hexadecimal.

        The <tt>fieldWidth</tt> value specifies the minimum amount of space that a is padded to and
        filled with the character <tt>fillChar</tt>. A positive value will produce right-aligned
        text, whereas a negative value will produce left-aligned text.
     */
    StringFormatter arg( void* a, int fieldWidth = 0, char fillChar = ' ' );

    /*!
		Specifies a value for markers. First call is for occurrences of \%1, second call for \%2, and so on.

        The <tt>fieldWidth</tt> value specifies the minimum amount of space that a is padded to and
        filled with the character <tt>fillChar</tt>. A positive value will produce right-aligned
        text, whereas a negative value will produce left-aligned text.
   
        The a argument is expressed in base base, which is 10 by default and must be between 2 and 36.
		For bases other than 10, a is treated as an unsigned integer.
     */
    StringFormatter arg( int32 a, int base = 10, int fieldWidth = 0, char fillChar = ' ' );

    /*!
		Specifies a value for markers. First call is for occurrences of \%1, second call for \%2, and so on.

        The <tt>fieldWidth</tt> value specifies the minimum amount of space that a is padded to and
        filled with the character <tt>fillChar</tt>. A positive value will produce right-aligned
        text, whereas a negative value will produce left-aligned text.
   
        The base argument specifies the base to use when converting the integer a into a String.
        The base must be between 2 and 36.
     */
    StringFormatter arg( uint32 a, int base = 10, int fieldWidth = 0, char fillChar = ' ' );

    /*!
		Specifies a value for markers. First call is for occurrences of \%1, second call for \%2, and so on.

        The <tt>fieldWidth</tt> value specifies the minimum amount of space that a is padded to and
        filled with the character <tt>fillChar</tt>. A positive value will produce right-aligned
        text, whereas a negative value will produce left-aligned text.
   
        The a argument is expressed in the given base, which is 10 by default and must be between 2 and 36. 
     */
    StringFormatter arg( int64 a, int base = 10, int fieldWidth = 0, char fillChar = ' ' );
    
    /*!
		Specifies a value for markers. First call is for occurrences of \%1, second call for \%2, and so on.

        The <tt>fieldWidth</tt> value specifies the minimum amount of space that a is padded to and
        filled with the character <tt>fillChar</tt>. A positive value will produce right-aligned
        text, whereas a negative value will produce left-aligned text.
   
        The base argument specifies the base to use when converting the integer a into a String.
        The base must be between 2 and 36, with 8 giving octal, 10 decimal, and 16 hexadecimal numbers.
     */
    StringFormatter arg( uint64 a, int base = 10, int fieldWidth = 0, char fillChar = ' ' );

    /*!
		Specifies a value for markers. First call is for occurrences of \%1, second call for \%2, and so on.

        The <tt>fieldWidth</tt> value specifies the minimum amount of space that a is padded to and
        filled with the character <tt>fillChar</tt>. A positive value will produce right-aligned
        text, whereas a negative value will produce left-aligned text.
   
        The a argument is interpreted as a Latin-1 character.
     */
    StringFormatter arg( char a, int fieldWidth = 0, char fillChar = ' ' );
    
    /*!
		Specifies a value for markers. First call is for occurrences of \%1, second call for \%2, and so on.

        The <tt>fieldWidth</tt> value specifies the minimum amount of space that a is padded to and
        filled with the character <tt>fillChar</tt>. A positive value will produce right-aligned
        text, whereas a negative value will produce left-aligned text.
   
        Argument a is formatted according to the specified format, which is 'g' by default and can be
		any of the following:
            - e : format as [-]9.9e[+|-]999
            - E : format as [-]9.9E[+|-]999
            - f : format as [-]9.9
            - g : use e or f format, whichever is the most concise
            - G : use E or f format, whichever is the most concise
        
        With 'e', 'E', and 'f', precision is the number of digits after the decimal point. With 'g' and 'G',
		precision is the maximum number of significant digits (trailing zeroes are omitted). 
     */
    StringFormatter arg( double a, int fieldWidth = 0, char format = 'g', int precision = 6, char fillChar = ' ' );

	StringFormatter arg( const Vec3f& a, int fieldWidth = 0, char format = 'g', int precision = 6, char fillChar = ' ' );

	StringFormatter arg( const Vec3d& a, int fieldWidth = 0, char format = 'g', int precision = 6, char fillChar = ' ' );

	StringFormatter arg( const Quatf& a, int fieldWidth = 0, char format = 'g', int precision = 6, char fillChar = ' ' );

	StringFormatter arg( const Quatd& a, int fieldWidth = 0, char format = 'g', int precision = 6, char fillChar = ' ' );

	/*!
		Specifies a value for markers. First call is for occurrences of \%1, second call for \%2, and so on.

        The <tt>fieldWidth</tt> value specifies the minimum amount of space that a is padded to and
        filled with the character <tt>fillChar</tt>. A positive value will produce right-aligned
        text, whereas a negative value will produce left-aligned text.
   
        The boolean value is converted to "true" or "false".
     */
	StringFormatter arg( bool a, int fieldWidth = 0, char fillChar = ' ' );

	/*!
		Efficiently formats the input String, using the input pattern and the specified arguments, in a single pass.
		Must be called after all arguments have been passed to the StringFormatter (through calls to arg()).
		This call also frees all memory and invalidates the StringFormatter.
	 */
	const String& done();

private:
	struct Data;

	void initialize();

private:
	Data* _data;	// internal state of the StringFormatter; if NULL the StringFormatter is considered invalid.
};

/*!
    A feature-rich String class, patterned after Qt's QString.
	The implementation is 8-bit clean, but does not provide Unicode functions. It is optimized for Latin-1.
 */
class VRBASE_EXPORT String : private tagbstring
{
	friend class StringFormatter;

public:
    //! This enum specifies how the split() function should behave with respect to empty strings.
    enum SplitBehavior
    {
        KeepEmptyParts, //!< If a field is empty, keep it in the result.
        SkipEmptyParts  //!< If a field is empty, don't include it in the result.
    };

    /*! 
        Compares s1 with s2 and returns an integer less than, equal to, or greater than zero if s1 is less than, 
        equal to, or greater than s2. If cs is <tt>CaseSensitive</tt>, the comparison is case sensitive; otherwise 
        the comparison is case insensitive. 
     */
    static int compare( const String& s1, const String& s2, CaseSensitivity cs = CaseInsensitive );

    /*!
        Returns a String equivalent of the number n according to the specified base. The base is 10 by default 
        and must be between 2 and 36. For bases other than 10, n is treated as an unsigned integer. 
     */
    //@{
    static String number( int32 n, int base = 10 );
    static String number( uint32 n, int base = 10 );
    static String number( int64 n, int base = 10 );
    static String number( uint64 n, int base = 10 );
    //@}

    //! Returns a String equivalent of the number n, formatted according to the specified format and precision. 
    //! The format can be 'f', 'F', 'e', 'E', 'g' or 'G'.
    static String number( double n, char format = 'g', int precision = 6 );

public:
    //! Constructs a null String. Null String's are also empty. 
    String();

    //! Constructs a String initialized with the Latin1 String str.
    String( const char* str );

    //! Constructs a String initialized with the first <tt>len</tt> characters of the char array <tt>str</tt>. 
    String( const char* str, int len );

    //! Constructs a String of size 1 containing the character <tt>ch</tt>. 
    String( char ch );

    //! Constructs a String of the given size with every character set to <tt>ch</tt>.
    String( int size, char ch );

    //! Constructs a copy of other String.
    String( const String& other );
     
    //! Destroys the String.
    ~String();

    //! Returns the character at the given index <tt>position</tt> in the String.
    //! \throw StringException if position is out of range (i.e. position < 0 or position >= length()).
    //@{
    char& at( int position );
    char  at( int position ) const;
    //@}

    //! Returns a substring that contains the n leftmost characters of the String. 
    //! The entire String is returned if n is greater than size() or less than zero.
    String left( int n ) const;

    /*!
        Returns a String that contains n characters of this String, starting at the specified position index. 
        Returns an empty String if the position index exceeds the length of the String. If there are less than 
        n characters available in the String starting at the given position, or if n is -1 (the default), the 
        function returns all characters that are available from the specified position.
     */
    String mid( int position, int n = -1 ) const;

    //! Returns a substring that contains the n rightmost characters of the String.
    //! The entire String is returned if n is greater than size() or less than zero.
    String right( int n ) const;

    //! Returns a pointer to the char data stored in the String. 
    //! For convenience, the data is always '\\0'-terminated.
    //@{
    inline char* data() { return reinterpret_cast<char*>( bstr ); }
    inline const char* data() const { return reinterpret_cast<const char*>( bstr ); }
    //@}

	//! Returns a pointer to the unsigned char data stored in the String. 
	//! For convenience, the data is always '\\0'-terminated.
	//@{
	inline unsigned char* udata() { return bstr; }
	inline const unsigned char* udata() const { return bstr; }
	//@}

    //! Clears the contents of the String and makes it empty.
    void clear();

    //! Returns true if the String has no characters; otherwise returns false.
    inline bool isEmpty() const { return slen == 0; }

    //! Returns the number of characters in this String.
    inline int length() const { return slen; }

    /*!
        Returns the maximum number of characters that can be stored in the String without
        forcing a reallocation. 
        
        The sole purpose of this function is to provide a means of fine tuning String's memory usage.
        In general, you will rarely ever need to call this function.
        If you want to know how many characters are in the String, call length(). 

        See also reserve() and squeeze().
     */
    inline int capacity() const { return mlen; }

    /*!
        Attempts to allocate memory for at least size characters. If you know in advance how large the
        String will be, you can call this function, and if you resize the String often you are likely to
        get better performance. If size is an underestimate, the worst that will happen is that the
        String will be a bit slower.

        The sole purpose of this function is to provide a means of fine tuning String's memory usage.
        In general, you will rarely ever need to call this function.
        If you want to change the size of the String, call resize().

        This function is useful for code that needs to build up a long String and wants to avoid
        repeated reallocation. In this example, we want to add to the String until some condition
        is true, and we're fairly sure that size is large enough to make a call to reserve() worthwhile:
        \code
            String result;
            int maxSize;
            bool condition;
            char nextChar;

            result.reserve( maxSize );

            while( condition )
                result.append( nextChar );
            result.squeeze();
        \endcode
        See also squeeze() and capacity().
     */
    void reserve( int size );

    /*!
        Releases any memory not required to store the character data. 
        
        The sole purpose of this function is to provide a means of fine tuning String's memory usage.
        In general, you will rarely ever need to call this function. 
     */
    void squeeze();

    /*!
        Sets the size of the String to size characters.

        If size is greater than the current size, the String is extended to make it size characters
        long with the extra characters added to the end. The new characters are uninitialized. 

        If size is less than the current size, characters are removed from the end.
     */
    void resize( int size );

    /*! 
        Lexically compares this String with the other String and returns an integer less than, equal to, 
        or greater than zero if this String is less than, equal to, or greater than the other String. 
     */
    int compare( const String& other, CaseSensitivity cs = CaseSensitive ) const;

    //! Returns true if the String starts with s; otherwise returns false. If cs is CaseSensitive
    //! (the default), the search is case sensitive; otherwise the search is case insensitive. 
    bool startsWith( const String& s, CaseSensitivity cs = CaseSensitive ) const;

    //! Returns true if the String starts with c; otherwise returns false.
    bool startsWith( char c, CaseSensitivity cs = CaseSensitive ) const;

    //! Returns true if the String ends with s; otherwise returns false. If cs is CaseSensitive 
    //! (the default), the search is case sensitive; otherwise the search is case insensitive.
    bool endsWith( const String& s, CaseSensitivity cs = CaseSensitive ) const;

    //! Returns true if the String ends with c; otherwise returns false.
    bool endsWith( char c, CaseSensitivity cs = CaseSensitive ) const;

    //! Returns the index position of the first occurrence of the String str in this String, searching 
    //! forward from index position from. Returns -1 if str is not found. 
    int indexOf( const String& str, int from = 0, CaseSensitivity cs = CaseSensitive ) const; 

    //! Returns the index position of the first occurrence of the character ch in the String, searching
    //! forward from index position from. Returns -1 if ch could not be found.
    int indexOf( char ch, int from = 0, CaseSensitivity cs = CaseSensitive ) const; 

    /*!
        Returns the index position of the first match of the regular expression rx in the String, searching 
        forward from index position from. Returns -1 if rx didn't match anywhere. 

        Example: 
        String str = "the minimum";
        str.indexOf( RegExp( "m[aeiou]" ), 0 );       // returns 4        
     */
    int indexOf( const RegExp& rx, int from = 0 ) const;

    /*!
        Returns the index position of the last occurrence of the String str in this String, searching backward 
        from index position from. If from is -1 (the default), the search starts at the last character; if from 
        is -2, at the next to last character and so on. Returns -1 if str is not found. 
     */
    int lastIndexOf( const String& str, int from = -1, CaseSensitivity cs = CaseSensitive ) const;

    //! Returns the index position of the last occurrence of the character ch, searching backward from position from. 
    int lastIndexOf( char ch, int from = -1, CaseSensitivity cs = CaseSensitive ) const;

    /*! 
        Returns the index position of the last match of the regular expression rx in the String, searching backward from 
        index position from. Returns -1 if rx didn't match anywhere. 
     */
    int lastIndexOf( const RegExp& rx, int from = -1 ) const;

	//! Returns true if this String contains an occurrence of the String str; otherwise returns false.
	//@{
	inline bool contains( const String& str, CaseSensitivity cs = CaseSensitive ) const { return indexOf( str, 0, cs ) != -1; }
    inline bool contains( char ch, CaseSensitivity cs = CaseSensitive ) const { return indexOf( ch, 0, cs ) != -1; }
	//@}

    //! Returns true if the regular expression rx matches somewhere in this String; otherwise returns false. 
    bool contains( const RegExp& rx  ) const;

	//! Returns the number of (potentially overlapping) occurrences of the String str in this String.
    int count( const String& str, CaseSensitivity cs = CaseSensitive ) const;

	//! Returns the number of occurrences of character ch in the String.
    int count( char ch, CaseSensitivity cs = CaseSensitive ) const;

    /*!
        Returns the number of times the regular expression rx matches in the String. This function counts 
        overlapping matches, so in the example below, there are four instances of "ana" or "ama": 
        String str = "banana and panama";
        str.count( RegExp("a[nm]a" ) );    // returns 4 
     */
    int count( const RegExp& rx ) const;

    //! Sets every character in the String to character ch. If size is different from -1 (the default), 
    //! the String is resized to size beforehand. 
    String& fill( char ch, int size = -1 );

    //! Prepends the String str to the beginning of this String and returns a reference to this String.
    String& prepend( const String& str );

    //! Prepends the String str to this String.
    String& prepend( const char* str );

    //! Prepends the character ch to this String. 
    String& prepend( char ch );

    //! Appends the String str onto the end of this String. 
    String& append( const String& str ); 

    //! Appends the String str to this String.
    String& append( const char* str );

    //! Appends the character <tt>ch</tt> to this String. 
    String& append( char ch );

    //! Inserts the String str at the given index position.
    String& insert( int position, const String& str );

    //! Inserts the first size characters of the char array str at the given index position in the String.
    String& insert( int position, const char* str, int len );

    //! Inserts ch at the given index position in the String. 
    String& insert( int position, char ch );

    //! Removes <tt>n</tt> characters from the end of the String.
    void chop( int n );

    //! Truncates the String at the given <tt>position</tt> index. 
    //! If the specified <tt>position</tt> index is beyond the end of the String, nothing happens. 
    void truncate( int position );

    //! Removes n characters from the String, starting at the given position index, and returns a reference 
    //! to the String. 
    String& remove( int position, int n );

    //! Removes every occurrence of the given str String in this String, and returns a reference to this String.
    //! If cs is CaseSensitive (the default), the search is case sensitive; otherwise the search is case insensitive.  
    //@{
    String& remove( const String& str, CaseSensitivity cs = CaseSensitive );
    String& remove( char ch, CaseSensitivity cs = CaseSensitive );
    //@}

    /*!
        Removes every occurrence of the regular expression rx in the String, and returns a reference to the String. 
        For example: 
        String r = "Telephone";
        r.remove( RegExp( "[aeiou]." ) );
        // r == "The" 
     */
    String& remove( const RegExp& rx );

    //! Replaces n characters from the specified index position with the String after, and returns a reference to 
    //! this String.
    //@{
    String& replace( int position, int n, const String& after );
    String& replace( int position, int n, const char* str, int len );
    String& replace( int position, int n, char after );
    //@}

    //! Replaces every occurrence of the String before with the String after. If cs is CaseSensitive
    //! (the default), the search is case sensitive; otherwise the search is case insensitive.
    //@{
    String& replace( const String& before, const String& after, CaseSensitivity cs = CaseSensitive );
    String& replace( char ch, const String& after, CaseSensitivity cs = CaseSensitive );
    String& replace( char before, char after, CaseSensitivity cs = CaseSensitive );
    //@}

    //! Replaces every occurrence of the regular expression rx in the String with after. 
    //! Returns a reference to the String.
    String& replace( const RegExp& rx, const String& after );

    /*!
        Splits the String into subStrings wherever <tt>sep</tt> occurs, and set the list of those String's into 
        <tt>result</tt> StringList. 
        If <tt>sep</tt> does not match anywhere in the String, split() puts a single-element containing 
        this String into <tt>result</tt> list.

        cs specifies whether sep should be matched case sensitively or case insensitively. 

        If behavior is String::SkipEmptyParts, empty entries don't appear in the result. By default, empty entries are kept.
     */
    //@{
    void split( StringList& result, const String& sep, SplitBehavior behavior = KeepEmptyParts ) const;
    void split( StringList& result, char sep, SplitBehavior behavior = KeepEmptyParts, CaseSensitivity cs = CaseSensitive ) const;
    //@}

    void split( StringList& result, const RegExp& rx, SplitBehavior behavior = KeepEmptyParts ) const;

    /*!
        Returns a FormatString that can be used to format the String, based on a <tt>pattern</tt> and
        a set of arguments. For example:
        \code
            String i;           // current file's number
            String total;       // number of files to process
            String fileName;    // current file's name

            String status;
            status.format( "Processing file %1 of %2: %3" )
                .arg( i ).arg( total ).arg( fileName ).done();
        \endcode

		\warning The String <tt>pattern</tt> must remain constant from the start of the call to format() until
			the call to StringFormatter::done(). Also, the lvalue and the pattern cannot be the same String.

        \see StringFormatter
     */
    //@{
    StringFormatter format( const char* pattern );
    StringFormatter format( const String* pattern );
    //@}

    /*!
        Safely builds a formatted String from the format String cformat and an arbitrary list of arguments.
        The format String uses the same specifiers provided by printf() in the standard C++ library.
        \warning Using this function in new code is NOT recommended. Use the format() API instead.
     */
    String& sprintf( const char* cformat, ... );

    /*!
        Sets the String to the printed value of n in the specified base, and returns a reference to the String. 
        The base is 10 by default and must be between 2 and 36. For bases other than 10, n is treated as an unsigned
        integer.
     */
    //@{
    String& setNum( int32 n, int base = 10 );
    String& setNum( uint32 n, int base = 10 );
    String& setNum( int64 n, int base = 10 );
    String& setNum( uint64 n, int base = 10 );
	//@}

	//! Sets the String to the printed value of n using the specified format and precision.
	//! The format can be 'f', 'F', 'e', 'E', 'g' or 'G'.
	String& setNum( double n, char format = 'g', int precision = 6 );

    //! Returns the String converted to a float value. If a conversion error occurs, *ok is set to
    //! false; otherwise *ok is set to true. Returns 0.0f if the conversion fails. 
    float toFloat( bool* ok = 0 ) const;

    //! Returns the String converted to a double value. If a conversion error occurs, *ok is set to
    //! false; otherwise *ok is set to true. Returns 0.0 if the conversion fails.
    double toDouble( bool* ok = 0 ) const;

    /*!
        Returns the String converted to an int16 using base base, which is 10 by default and must be
        between 2 and 36, or 0. Returns 0 if the conversion fails. 
        
        If a conversion error occurs, *ok is set to false; otherwise *ok is set to true. 
        
        If base is 0, the C language convention is used: If the String begins with "0x", base 16 is
        used; if the String begins with "0", base 8 is used; otherwise, base 10 is used.
     */
    int16 toInt16( bool* ok = 0, int base = 10 ) const;

    /*!
        Returns the String converted to an uint16 using base base, which is 10 by default and
        must be between 2 and 36, or 0. Returns 0 if the conversion fails. 
        
        If a conversion error occurs, *ok is set to false; otherwise *ok is set to true. 
        
        If base is 0, the C language convention is used: If the String begins with "0x", base 16 is
        used; if the String begins with "0", base 8 is used; otherwise, base 10 is used. 
     */
    uint16 toUInt16( bool* ok = 0, int base = 10 ) const;

    /*!
        Returns the String converted to an int using base base, which is 10 by default and
        must be between 2 and 36, or 0. Returns 0 if the conversion fails. 
        
        If a conversion error occurs, *ok is set to false; otherwise *ok is set to true. 
        
        If base is 0, the C language convention is used: If the String begins with "0x", base 16 is
        used; if the String begins with "0", base 8 is used; otherwise, base 10 is used. 
     */
    int32 toInt32( bool* ok = 0, int base = 10 ) const;

    /*!
        Returns the String converted to an uint32 using base base, which is 10 by default
        and must be between 2 and 36, or 0. Returns 0 if the conversion fails.

        If a conversion error occurs, *ok is set to false; otherwise *ok is set to true. 
    
        If base is 0, the C language convention is used: If the String begins with "0x", base 16 is
        used; if the String begins with "0", base 8 is used; otherwise, base 10 is used.
     */
    uint32 toUInt32( bool* ok = 0, int base = 10 ) const;

    /*!
        Returns the String converted to an int64 using base base, which is 10 by default and
        must be between 2 and 36, or 0. Returns 0 if the conversion fails. 
        
        If a conversion error occurs, *ok is set to false; otherwise *ok is set to true. 
        
        If base is 0, the C language convention is used: If the String begins with "0x", base 16 is
        used; if the String begins with "0", base 8 is used; otherwise, base 10 is used.
     */
    int64 toInt64( bool* ok = 0, int base = 10 ) const;

    /*!
        Returns the String converted to an unsigned long using base base, which is 10 by default
        and must be between 2 and 36, or 0. Returns 0 if the conversion fails.

        If a conversion error occurs, *ok is set to false; otherwise *ok is set to true.

        If base is 0, the C language convention is used: If the String begins with "0x", base 16 is
        used; if the String begins with "0", base 8 is used; otherwise, base 10 is used. 
     */
    uint64 toUInt64( bool* ok = 0, int base = 10 ) const;

    //! Converts all String characters to lowercase.
    void makeLower();

    //! Converts all String characters to uppercase.
    void makeUpper();

    //! Removes whitespaces from the start and the end of the String.
    //! Whitespace includes the ASCII characters '\\t', '\\n', '\\v', '\\f', '\\r', and ' '. 
    void trim();

    //! Returns true if this String is not equal to String other; otherwise returns false.
    bool operator!=( const String& other ) const;

    //! Returns true if this String is not equal to String other; otherwise returns false.
    bool operator!=( const char* other ) const;

    //! Appends the String other onto the end of this String and returns a reference to this String.
    inline String& operator+=( const String& other ) { return append( other ); }

    //! Appends the String str to this String.
    inline String& operator+=( const char* str ) { return append( str ); }

    //! Appends the character ch to this String.
    inline String& operator+=( char ch ) { return append( ch ); }

    //! Returns true if this String is lexically less than String other; otherwise returns false.
    bool operator<( const String& other ) const { return compare( other ) < 0; }

    //! Returns true if this String is lexically less than String other; otherwise returns false.
    bool operator<( const char* other ) const { return compare( other ) < 0; }

    //! Returns true if this String is lexically less than or equal to String other; otherwise returns false.
    bool operator<=( const String& other ) const { return compare( other ) <= 0; }

    //! Returns true if this String is lexically less than or equal to String <tt>other</tt>; otherwise returns false.
    bool operator<=( const char* other ) const { return compare( other ) <= 0; }

    //! Assigns <tt>other</tt> to this String and returns a reference to this String.
    String& operator=( const String& other );

    //! Assigns str to this String.
    String& operator=( const char* str );

    //! Assigns character ch to this String.
    String& operator=( char ch );

    //! Returns true if String <tt>other</tt> is equal to this String; otherwise returns false.
    bool operator==( const String& other ) const;

    //! Returns true if String <tt>other</tt> is equal to this String; otherwise returns false.
    bool operator==( const char* other ) const;

    //! Returns true if this String is lexically greater than String <tt>other</tt>; otherwise returns false.
    bool operator>( const String& other ) const { return compare( other ) > 0; }

    //! Returns true if this String is lexically greater than String <tt>other</tt>; otherwise returns false.
    bool operator>( const char* other ) const { return compare( other ) > 0; }

    //! Returns true if this String is lexically greater than or equal to String <tt>other</tt>; otherwise returns false. 
    bool operator>=( const String& other ) const { return compare( other ) >= 0; }

    //! Returns true if this String is lexically greater than or equal to String <tt>other</tt>; otherwise returns false. 
    bool operator>=( const char* other ) const { return compare( other ) >= 0; }

    //! Returns the character at the specified position in the String. 
    //! The position must be a valid index position in the String (i.e., 0 <= position < length()).
    //! Bounds are NOT checked. Use at() for a safer API.
    //@{
    char& operator[]( int position ) { return reinterpret_cast<char*>( bstr )[position]; }
    char  operator[]( int position ) const { return reinterpret_cast<const char*>( bstr )[position]; }
    char& operator[]( unsigned int position ) { return reinterpret_cast<char*>( bstr )[position]; }
    char  operator[]( unsigned int position ) const { return reinterpret_cast<const char*>( bstr )[position]; }
    //@}
};

//! Returns true if s1 is not equal to s2; otherwise returns false.
//! For s1 != 0, this is equivalent to compare(\a s1, \a s2) != 0. Note that no String is equal to s1 being 0. 
inline bool operator!=( const char* s1, const String& s2 ) { return s2 != s1; }

//! Returns true if s1 is lexically less than s2; otherwise returns false.
//! For s1 != 0, this is equivalent to compare(s1, s2) < 0.
inline bool operator<( const char* s1, const String& s2 ) { return s2 > s1; }

//! Returns true if s1 is lexically less than or equal to s2; otherwise returns false.
//! For s1 != 0, this is equivalent to compare(s1, s2) <= 0.
inline bool operator<=( const char* s1, const String& s2 ) { return s2 >= s1; }

//! Returns true if s1 is equal to s2; otherwise returns false. Note that no String is equal to s1 being 0.
//! Equivalent to s1 != 0 && compare(s1, s2) == 0. 
inline bool operator==( const char* s1, const String& s2 ) { return s2 == s1; }

//! Returns true if s1 is lexically greater than s2; otherwise returns false.
//! Equivalent to compare(s1, s2) > 0.
inline bool operator>( const char* s1, const String& s2 ) { return s2 < s1; }

//! Returns true if s1 is lexically greater than or equal to s2; otherwise returns false.
//! For s1 != 0, this is equivalent to compare(s1, s2) >= 0.
inline bool operator>=( const char* s1, const String& s2 ) { return s2 <= s1; }

//! Returns a String which is the result of concatenating s1 and s2. 
inline String operator+( const String& s1, const String& s2 ) { return String( s1 ).append( s2 ); }

//! Returns a String which is the result of concatenating s1 and s2.
inline String operator+( const String& s1, const char* s2 ) { return String( s1 ).append( s2 ); }

//! Returns a String which is the result of concatenating s1 and s2.
inline String operator+( const char* s1, const String& s2 ) { return String( s1 ).append( s2 ); }

//! Returns a String which is the result of concatenating the String s and the character ch.
inline String operator+( const String& s, char ch ) { return String( s ).append( ch ); }

//! Returns a String which is the result of concatenating the character ch and the String s.
inline String operator+( char ch, const String& s ) { return String( ch ).append( s ); }

//! Print the String.
inline std::ostream& operator <<( std::ostream& sout, const String& b ) { return sout.write( b.data(), b.length() ); }

/*! @} */ // end of group text

} // namespace vr

#endif // _VR_STRING_H_
