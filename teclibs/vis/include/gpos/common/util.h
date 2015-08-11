//* util.h
// Basic utility functions
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef ps_util_h
#define ps_util_h

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <alg/vector.h>
#include <gpos/defines.h>

#ifndef M_PI
# define M_PI  3.14159265358979323846
#endif

//* Font enumerators
enum
{
  PSFNT_BITMAP_TIMES_ROMAN_10,
  PSFNT_BITMAP_TIMES_ROMAN_24,
  PSFNT_BITMAP_HELVETICA_10,
  PSFNT_BITMAP_HELVETICA_12,
  PSFNT_BITMAP_HELVETICA_18,
  PSFNT_BITMAP_FIXED_13,
  PSFNT_BITMAP_FIXED_15
};


//* 'PSUtil' Class
// Implements general purpose utility functions
class RES_API PSUtil
{
public:
    //* A string key class for the hash structures
  struct StringKey {
    char *name;
    StringKey() : name(0) { }
    StringKey(const char *s) : name(StrDup(s)) { }
    ~StringKey() { Free(name); }
    StringKey(const StringKey &k) : name(StrDup(k.name)) { }
    StringKey& operator=(const StringKey &k) { Free(name); name = StrDup(k.name); return *this; }
    operator const char * () const { return name; }
    int operator == (const char *s) const {
      return (name==s || strcmp(name,s)==0);
    }
  };
  
  enum { // image formats
    BMP,  /* Windows Device Independent Bitmap - DIB (RGB not compressed, MAP compressed or not) */
    PCX,  /* ZSoft Picture (RGB and MAP compressed or not) */
    TIF,  /* TIFF - Tagged Image File Format (RGB and MAP compressed or not) */
    JPG,  /* JPEG - Join Photographic Experts Group (RGB and MAP always compressed, MAP as GRAY only) */
    TGA,  /* True Vision Targa */
    PNG
  };

    //* Error report
    // Reports an error message and exits.
  static void Error (const char *error, const char *details = 0);
    //* Warning report
    // Reports a warning message.
    // Returns 0.
  static int WarningOld (const char *msg, const char *details = 0);
  /**
   * printf alike Warning function
   */
  static int Warning (const char *format, ...);
    //* Message report
    // Reports a message to the user.
    // Returns 0.
  static int Msg (const char *msg, const char *details = 0);
    //* Debug message report
    // Reports a debug message.
    // Returns 0.
  static int DebugMsg (const char *msg, const char *details = 0);
    //* Memory allocation
    // Allocates a block of memory.
    // Aborts the program if the allocation fails, displaying an error message.
  static void* Malloc (int nbytes);
    //* Memory reallocation
    // Reallocates a block of memory.
    // Aborts the program if the reallocation fails, displaying an error message.
  static void* Realloc (void* a, int nbytes);
  
    //* Memory allocation and clear
    // Allocates a block of memory clearing it with 0's.
    // Aborts the program if the allocation fails, displaying an error message.
  static void* Calloc (int nbytes, int t_size);
  /**
   * Returns the substring of 'source' beggining at position 'ini' and ending
   * at position 'end'.
   * Memory should be allocated by the caller with 'free'.
   */
  static char* StrSub (const char* source, int ini, int end);
    //* String duplication
    // Duplicates the source string.
    // Returns a pointer to the duplicate.
  static char* StrDup (const char* source);

  /**
   * Substitutes string '*dest' with 'source'.
   * 'source' can be NULL, and so can '*dest' be.
   */
  static void StrSubst (char** dest, const char* source);
  
    //* String comparation
    // Compares two strings
  static bool StrComp(const char* str1,const char* str2);
    //* n-characters String comparation 
    // Compares first n characters of two strings
  static bool StrNComp(const char* str1,const char* str2,int num);
  /**
   * Copies string 'src' to destination 'dst'.
   */
  static void StrCopy(char* dst, const char* src);
    //* Memory release
  static void Free (void* a);
    //* Check string identity
    // Returns non zero if 'a' and 'b' match, zero otherwise.
  static int StrEq (const char* a, const char* b)
  {
    return (((a)==(b)) || ((a)&&(b)&&((*a)==(*b))&&(strcmp((a),(b))==0)));
  }
  
    //* Substring check
    // Returns non zero if b occurs in a, zero otherwise.
  static int StrStr (const char* a, const char* b)
  {
    return (((a)==(b)) || ((a)&&(b)&&((*a)==(*b))&&(strstr((a),(b))!=0)));
  }
  
    //* Change string to upper case
  static const char* UpperCase (const char *s);
  
    //* Float to string conversion
    // Converts the value to string.
    // Precision is given in number of decimal digits.
  static void FToA(char *result, float value, int precision);
    //* Pointer indirecion change
    // Swaps the contents of pointers a and b.
  static void ChangeIndirection (void** a, void **b);

    //* Packs 3 bytes inside a 4-byte integer.
    // 'data' contains 0x00IIJJKK after the process.
  static void Pack(unsigned char i, unsigned char j, unsigned char k, int *data)
  {
    *data = 0;
    *data |= ((int)(i) << 16);
    *data |= ((int)(j) << 8);
    *data |= (int)k;
 }

    //* Unpacks the 3 least significant bytes of a 4 byte integer.
    // 'data' is assumed to contain 0x00IIJJKK.
 static void Unpack(unsigned char *i, unsigned char *j, unsigned char *k, int data)
 {
   *i = ((data & 0x00FF0000) >> 16);
   *j = ((data & 0x0000FF00) >> 8);
   *k = (data & 0x000000FF);
 }

    //* Date to double and vice-versa
    // Converts a date to a double representation and vice-versa
  static double DateToDouble(int day, int month, int year);
  static void   DoubleToDate(double day, int *dd, int *mm, int *yy);
  static int GetDateNumberOfMonthDays(int month,int year);
  static int GetNumberOfYearDays(int year);
  static void IncDateDay(int *day,int *month,int *year);
  static void DecDateDay(int *day,int *month,int *year);
  static int GetElapsedDays(int day1,int month1,int year1,int day2,int month2,int year2);
  static int GetDiffDays (int d1,int m1,int y1,int d2,int m2,int y2);
    //* Linear index
    // Computes a linear index given the number of dimensions, a coordinate and size of each dimension
 static int Index(int ndims, int coord[], int size[])
 {
   int i;
   int ind = coord[0];
   for (i=1;i<ndims;i++)
     ind = ind*size[i] + coord[i];
   return ind;
 }

    //* File access time compare
    // Returns -1 if 'f1' is newer than 'f2', 0 if they have the same time or 1 if 'f2' is newer than 'f1'
    // Returns any other value in case of errors
 static int FileTimeCmp(const char *f1, const char *f2);
  /**
   * Reads the first float value of an open file.
   * It must be at least 100 characters ahead of the beggining of the file.
   * Returns true and the value in *ret if successful.
   */
  static bool ReadFirstFloat (FILE *f, float *ret)
  {
    assert(f);
    assert(ret);
    int r;
    // eat all until the first float (max of 100 characters)
    for (int i=0; i<100; i++)
    {
      r = fscanf(f,"%f",ret);
      if (r == 1)
        return true; // ok, found first float
      else if (r == EOF)
        return false;
      else
        fgetc(f); // eat a character and try again
    }
    return false;
  }
  /**
   * Skips end of line characters in an open file.
   */
  static void SkipEndOfLine (FILE *f)
  {
    assert(f);
    int c = fgetc(f);
    if (c != '\r' && c != '\n' && c != EOF)
      ungetc(c,f);
    if (c == '\r')
    {
      c = fgetc(f);
      if (c != '\n' && c != EOF)
        ungetc(c,f);
    }
  }
  /**
   * Skips a float in an open file.
   * Returns true on success, false otherwise.
   */
  static bool SkipFloat (FILE *f);

  static float AngleBetween(const AlgVector& v1,const AlgVector& v2)
  {
    float cos_theta = v1.Dot(v2) / ( v1.Length() * v2.Length());
  
    // converts to degrees
    return (float)((acos(cos_theta)*180.0)/M_PI);
  }

    
  /** 
   * Removes left and rigth blanks 
   * Returns string without blanks
   */
  static char *TrimStr(char *s);
    
  /**
   * Returns maximum between n1 and n2
   */
  static int Max(int n1,int n2);
  
  /**
   * Calculate a date given an initial date and a number of days. 
   */
  static void CalcDate(int dd,int mm,int yy,float days,
                int *ddf,int *mmf,int *yyf);
                
  static char *SystemDate(int *dd,int *mm,int *yy);
  static char* StrDate (int dd,int mm,int yy);
  static void GetDate (const char *date, int *day, int *month, int *year);
};

RES_API char *gpos_getrootname (const char *filename);

#endif

