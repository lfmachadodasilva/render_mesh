/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_REGEXP_H_
#define _VR_REGEXP_H_

#include "String.h"
#include "Exception.h"

extern "C" {
    struct real_pcre;
}

namespace vr {
/*!
    \addtogroup text
    @{
 */

/*!
    This is the only kind of exception raised by RegExp methods.
    \see RegExp
 */
class RegExpException : public Exception
{
public:
    RegExpException( const String& message ) : Exception( message )
    {;}
};

/*!
    \brief This class provides pattern matching using regular expressions.
    Regular expressions, or "regexps", provide a way to find patterns within text.
    This class uses the Perl RE syntax and it is a wrap to PCRE (Perl Compatible
    Regular Expressions) Library.
    For Perl 5 regular expression syntax, see http://perldoc.perl.org/perlre.html .

    Sample Usage:
    \code
        RegExp re( pattern );
        re.compile(); // may throw an exception
        if( re.matches( aString ) )
        {
            String str;
            re.getMatch( 1, str );
            printf( "First capture: %s\n", str.data() );
        }
    \endcode
 */
class VRBASE_EXPORT RegExp
{
public:
    /*!
        Returns the string str with every regexp special character escaped with a backslash. 
        The special characters are $, (,), *, +, ., ?, [, ,], ^, {, | and }. 
        Example: 
        s1 = RegExp::escape("bingo");   // s1 == "bingo"
        s2 = RegExp::escape("f(x)");    // s2 == "f\\(x\\)" 
     */
    static String escape( const String& str );

    static const unsigned char* createCharTable( const char* locale );
    
public:
    //! Constructs an empty RegExp.
    RegExp();

    /*! 
        Constructs a regular expression object for the given pattern string. 
        The pattern is case sensitive, unless cs is Qt::CaseInsensitive (which corresponds to /i in Perl RE Syntax).
        Matching is greedy (maximal), but can be changed by calling setMinimal().
     */
    RegExp( const String& pattern, CaseSensitivity cs = CaseSensitive );

    //! Constructs a regular expression as a copy of rx. 
    RegExp( const RegExp& rx );

    //! Destroys the regular expression and cleans up its internal data.
    ~RegExp();
    //@}

	/*!
		Returns the pattern string of the regular expression. 
		\see setPattern() and caseSensitivity().
	 */
    const String& getPattern() const { return _pattern; }

	//! Sets the pattern string to pattern. The case sensitivity and minimal matching options are not changed. 
	//! \sa pattern() and setCaseSensitivity().
    void setPattern( const String& pattern ) { _pattern = pattern; }

    //! Sets case sensitive matching to cs. 
    void setCaseSensitivity( CaseSensitivity cs ) { _sensitivity = cs; }

    //! Returns CaseSensitive if the regexp is matched case sensitively; otherwise returns CaseInsensitive. 
    //! \see setCaseSensitivity() and isMinimal().
    CaseSensitivity caseSensitivity() const { return _sensitivity; }

    //! Enables or disables minimal matching. If minimal is false, matching is greedy (maximal) which is the default. 
    void setMinimal( bool minimal ) { _isGreedy = !minimal; }

    //! Returns true if minimal (non-greedy) matching is enabled; otherwise returns false. 
    //! \see caseSensitivity(). 
    bool isMinimal() const { return _isGreedy == false; }

    /*!
        Returns true if the regular expression is valid; otherwise returns false. An invalid regular expression 
        never matches. The pattern [a-z is an example of an invalid pattern, since it lacks a closing square bracket. 
        \see errorString().
     */
	inline bool isValid() const { return _pcreRegExp != 0; }

    /*!
        Recompiles the current pattern using the current "greediness" and sensitivity settings.
        \throw RegExpException if the pattern contains errors.
     */
    void compile();

	/*!
		Attempts to match the subject string. Returns true if matches were found or false otherwise. 
	*/
	bool matches( const String& subject, int startOffset = 0 );

	/*! 
        Returns the text captured by the nth subexpression through the String 'str'. 
        The full match (composed by the entire pattern including all subexpressions) has index 0 and the parenthesized 
		subexpressions have indexes starting from 1 (excluding non-capturing parentheses). 
        This methods throws a RegExpException if the given index is out of bounds, i.e. the given index is
        bigger than the max number of captures available.
        
        It is possible for capturing subpattern number n+1 to match some part of the subject when subpattern 
        n has not been used at all. For example, if the string "abc"  is  matched against the pattern (a|(z))(bc) 
        the return from the function is 4, and subpatterns 1 and 3 are matched, but 2 is not. 
        When this happens and the user tries to access the captured string 2, the method will return false (no match
		for the given subexpression). If the subexpression has a valid match the method returns true.
		Notice that calling match() with nth = 0 (the index of the full match) will indicate whether there are any matches found at all,
		(the same value matches() has returned for the first time).

        \throw RegExpException if the RegExp was not compiled.
     */
    //@{
    inline bool getMatch( String& str ) const { return getMatch( 0, str ); }
    bool getMatch( int nth, String& str ) const;

	/*!
		Returns the start position of the nth captured text in the searched string. If nth is 0 (the default), matchStart() 
		returns the start position of the whole match. For zero-length matches, matchStart() always returns -1. 
		(For example, if match( 4 ) would return an empty string, matchStart( 4 ) returns -1).
        \throw RegExpException if the RegExp was not compiled. 
        \see match(), matchEnd() and matchList().
	*/
	int getMatchStart( int nth = 0 ) const;

	/*!
		Returns the end position of the nth captured text in the searched string.
        \throw RegExpException if the RegExp was not compiled.
        \see matchStart().
	*/
	int getMatchEnd( int nth = 0 ) const;

	/*!
        Returns the length of the match given by the nth subexpression, or -1 if there was no match for the given subexpression index.
	    Calling matchLength with nth = 0 yields the length of the whole match found (including all subexpressions).
        \throw RegExpException if the RegExp was not compiled.
        \see match().\
     */
	int getMatchLength( int nth = 0 ) const;

    /*! 
		Returns the number of captures contained in the regular expression.
		Important: notice that the number of captures returned by this function is actually one more than the number of captures
		marked by the ()'s within the pattern. It is because the whole expression counts as a capture too. If the pattern contains
		n captures represented by ()'s, the total number returned by numCaptures() is n+1.
     */
    int getNumCaptures() const;

	/*! 
		Returns a list of the captured text strings. 
		The first string in the list is the entire matched string. Each subsequent list element contains a 
		string that matched a (capturing) subexpression of the regexp. 
		Notice that the number of elements within the resultant StringList is always the same as numCaptures(),
		but any inner subexpression that may not yield matches will have an empty string at its correspondent
		position within the StringList.
	 */
	void getMatchList( StringList& strings ) const;

    //! Copies the regular expression rx and returns a reference to the copy. The case sensitivity and minimal 
    //! matching options are also copied. 
    RegExp& operator=( const RegExp& rx );

    //! Returns true if this regular expression is equal to rx; otherwise returns false. Two QRegExp objects are 
    //! equal if they have the same pattern strings and the same settings for case sensitivity and minimal matching. 
    bool operator==( const RegExp& rx ) const;

    inline bool operator!=( const RegExp& rx ) const { return !(*this == rx); }

private:
    // Initializes all states.
    void init();

    // throws an Exception if the RegExp is invalid
    void checkValidity() const;

    // Executes a match over the given subject using the current pattern (_pattern)
    // offset marks an offset from the beginning of the subject string.
    void executeRegex( int offset = 0 );
    
    // Builds and returns all controlled pcre options.
    int pcreOptions();

private:
    static const int MAX_CAPTURES = 90;

private:
    // RegExp state
    bool _isGreedy;
    String _pattern;
    String _currentSubject;
    int _capturesFound;
    CaseSensitivity _sensitivity;

    // PCRE control
    real_pcre* _pcreRegExp;
    int _ovector[ 3 * ( MAX_CAPTURES + 1 ) ];
};

/*! @} */ // end of group text

} // namespace vr

#endif
