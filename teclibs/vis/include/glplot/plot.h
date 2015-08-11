/******************************************************************************
* @module           GLPLOT
* @file             plot.h
* @id               GLP
* @owner            Tecgraf
* @author           X 
* @author           RBL - Rodrigo Buás Lopes - rbuas@tecgraf.puc-rio.br
* @version          1.0 - 01.2003 - X
* @version          2.4 - 01.2007 - RBL
******************************************************************************/
#ifndef _PLOT_H
#define _PLOT_H
#define PLOT_API_V_25
#include <float.h>
#include <limits.h>
#include "cd.h"
#include "cdps.h"
#include <ds/defines.h>
#include <string>
using namespace std;

//#define TEST_PERFORMANCE 1
#define _PLOT_FUNCTION
#define PLOT_VERSION "2.4" 
  
/** Representação de "Not a Number" para "double" */
#define PLOT_NAN_DOUBLE DBL_MAX  
/** Representação de "Not a Number" para "int" */
#define PLOT_NAN_INT INT_MAX

#ifndef GLPLOT_DLL
# ifndef TEC_DLL
# define PLOTAPI
# else
# define PLOTAPI __declspec(dllimport)
# endif
#else
# define PLOTAPI __declspec(dllexport)
#endif

/*******************************************************************************
* @block Basic structures names
*******************************************************************************/
typedef struct Plot Plot;
class GLPlotCurve;
class GLPlot;
class Chart;
class CurveChart;
class BarChart;
class BarSeries;
class HistogramChart;
class PlotAxis;
class PlotMemo;
class AlgGLStack;
typedef GLPlotCurve PlotCurve;
#ifdef _PLOT_FUNCTION
struct PlotFunction;
typedef struct PlotFunction PlotFunction;
#endif
/* numeric core */
class PlotStrip;
class PlotStripSet;
class PlotColorScale;
/*******************************************************************************
* @endof block Basic structures names
*******************************************************************************/
/*******************************************************************************
* @block Plot options
*******************************************************************************/
/*************
* @type PLOT_NONE Option valid to allmost types, 
* equal zero.
*******/
#define PLOT_NONE 0
/*************
* @type PLOT_COORD_NULL Invalid coordinate.
*******/
#define PLOT_COORD_NULL FLT_MAX
/*************
* @type PlotDataType Type of plotting data.
*******/
enum PlotDataType
{
  PLOT_CURVE        = 1,
  PLOT_AREA         = 2,
  PLOT_BAR          = 3,
  PLOT_HISTOGRAM    = 4,
  PLOT_PIZZA        = 5  //TODO: implement it
};

enum PlotEntity
{
  PLOT_DATA = 1,
  PLOT_TITLE,
  PLOT_SUBTITLE,
  PLOT_AXIS_TITLE,
  PLOT_AXIS_LINE,
  PLOT_AXIS_LABEL,
  PLOT_GRID,
  PLOT_GRID_SEC,
  PLOT_GRID_MARK,
  PLOT_MEMO,
  PLOT_DPOINT,
  PLOT_DLINE,
  PLOT_DAREA,
  PLOT_LEGITEM,
  PLOT_STRIP,
  PLOT_STRIPMARK,
  PLOT_STRIPQUAD,
  PLOT_BOX_LEGEND,
  PLOT_BOX_TITLE,
  PLOT_BOX_DATA,
  PLOT_BOX_AXIS,
  PLOT_BOX_PLOT,
  PLOT_TIP,
  PLOT_ZOOM,
  PLOT_WATERMARK,
  PLOT_LOGO_LEFT,
  PLOT_LOGO_RIGHT,
  PLOT_CHART_BOX,
  PLOT_ALL_CHARTS_BOX,
  PLOT_COLORSCALE,
  PLOT_ALL
};

enum PlotMode
{
  PLOT_MODE_STANDARD  = 1,
  PLOT_MODE_ZOOMIN    = 2,
  PLOT_MODE_ZOOMOUT   = 3,
  PLOT_MODE_DRAG      = 4,
  PLOT_MODE_DRAGRESET = 5,
  PLOT_MODE_PAN       = 6,  //TODO
  PLOT_MODE_TRACK     = 7   //TODO
};
enum PlotFunc //TODO: change to PlotFeatures
{
  PLOT_FCN_MEMO     = 1, //PLOT_FCN_MEMO (1)Plot memo functionality
  PLOT_FCN_TIP      = 2, //PLOT_FCN_TIP (2)Plot tip functionality
  PLOT_FCN_PMOV     = 4  //PLOT_FCN_PMOV (3)Move point or edit point coordinate
};
enum PlotEvent
{
  PLOT_E_KEYPRESS,
  PLOT_E_KEYRELEASE,
  PLOT_E_BTNPRESS,
  PLOT_E_BTNRELEASE,
  PLOT_E_MMOTION,
  PLOT_E_MWHEEL,
  PLOT_E_FOCUS,
  PLOT_E_DROPFILES
};
enum PlotButton
{
  PLOT_BTN_LEFT     = 1,
  PLOT_BTN_MIDDLE   = 2,
  PLOT_BTN_RIGHT    = 3
};
enum PlotAxisId
{
   PLOT_X           = 0,
   PLOT_Y1          = 1,//left
   PLOT_Y2          = 2,//right
   PLOT_Y3          = 3,//left
   PLOT_Y4          = 4,//right
   PLOT_MAX_AXIS    = 5
};
enum PlotAxisType
{
  PLOT_DEC  = 1,  //Decimal scale.
  PLOT_LOG  = 2,  //Logarithm scale.
  PLOT_DATE = 3,  //Data scale, only valid to axis X.
  PLOT_TEXT = 4   //Text scale, only manual scale (have to set labels).
};
/*************
* @type PlotAlign Alignment opitions.
*******/
enum PlotAlign
{
  PLOT_A_LEFT   = 1,
  PLOT_A_CENTER = 2, 
  PLOT_A_RIGHT  = 3,
  PLOT_A_TOP    = 4,
  PLOT_A_BOTTOM = 5,
  PLOT_A_MIDDLE = 6 
};
/*************
* @type PlotTextDirect Text direction opitions.
*******/
enum PlotTextDirect
{
  PLOT_D_HOR      = 1, //horizontal
  PLOT_D_VER_SN   = 2, //vertical - s -> n
  PLOT_D_VER_NS   = 3, //vertical - n -> s
  PLOT_D_DIG_SWNE = 4, //diaonal - sw -> ne
  PLOT_D_DIG_NWSE = 5  //diaonal - nw -> se
};
enum PlotPosition // position options
{
  PLOT_TOP    = 1,
  PLOT_BOTTOM = 2,
  PLOT_LEFT   = 3,
  PLOT_RIGHT  = 4,
  PLOT_CENTER = 5 
};
/************** 
* @type PlotDisplay
*******/
enum PlotDisplay
{
  PLOT_DIS_HIDE     = 0,
  PLOT_DIS_BLOCK    = 1,
  PLOT_DIS_FLOAT    = 2 
};
enum PlotFontStyle
{
  PLOT_PLAIN        = CD_PLAIN,
  PLOT_BOLD         = CD_BOLD,
  PLOT_ITALIC       = CD_ITALIC,
  PLOT_BOLD_ITALIC  = CD_BOLD_ITALIC
};
/************** 
* @type PlotGridType Grid opitions.
*******/
enum PlotGridType
{
  PLOT_NOGRID  = 0, /*<@var PLOT_NOGRID int No grid. */
  PLOT_LARGE   = 1, /*<@var PLOT_LARGE int Grid in the biggest marks on axis.*/
  PLOT_REFINED = 2  /*<@var PLOT_REFINED int Grid in the lesser and biggest 
                              marks on axis.*/
};
/************** 
* @type PlotExportType Export format opitions.
*******/
enum PlotExportType
{
  PLOT_ASCII = 0, /*<@var PLOT_ASCII int ASCII text format. */
  PLOT_PS    = 1, /*<@var PLOT_PS int PostScript text format. */
  PLOT_CGM   = 2, //TODO: implement it
  PLOT_DXF   = 3, //TODO: implement it
  PLOT_XLS   = 4, //TODO: implement it
  PLOT_XML   = 5, //TODO: implement it
  PLOT_LUA   = 6  //TODO: implement it
};
/************** 
* @type PlotPaperSize Paper size opitions.
*******/
enum PlotPaperSize
{
  PLOT_A0           = CD_A0,
  PLOT_A1           = CD_A1,
  PLOT_A2           = CD_A2,
  PLOT_A3           = CD_A3,
  PLOT_A4           = CD_A4,
  PLOT_A5           = CD_A5,
  PLOT_LETTER       = CD_LETTER,
  PLOT_LEGAL        = CD_LEGAL
};
/************** 
* @type PlotLineStyle Line style opitions.
*******/
enum PlotLineStyle
{
  PLOT_CONTINUOUS   = CD_CONTINUOUS,
  PLOT_DASHED       = CD_DASHED,
  PLOT_DOTTED       = CD_DOTTED,
  PLOT_DASH_DOT     = CD_DASH_DOT,
  PLOT_DASH_DOT_DOT = CD_DASH_DOT_DOT
};   
/************** 
* @type PlotMarkType Mark type opitions.
*******/
enum PlotMarkType
{
  PLOT_PLUS           = CD_PLUS,            //TODO: start with 1, to free 0 to PLOT_NONE
  PLOT_STAR           = CD_STAR,            //TODO: rename to PLOT_MRK_HSTAR
  PLOT_CIRCLE         = CD_CIRCLE,          //TODO: rename to PLOT_MRK_HCIRCLE
  PLOT_X_MARK         = CD_X,               //TODO: rename to PLOT_MRK_HCROSS
  PLOT_BOX            = CD_BOX,             //TODO: rename to PLOT_MRK_HDIAMOND
  PLOT_DIAMOND        = CD_DIAMOND,         //TODO: remove it - redundance
  PLOT_HOLLOW_CIRCLE  = CD_HOLLOW_CIRCLE,   //TODO: remove it - redundance
  PLOT_HOLLOW_BOX     = CD_HOLLOW_BOX,      //TODO: remove it - redundance
  PLOT_HOLLOW_DIAMOND = CD_HOLLOW_DIAMOND,  //TODO: remove it - redundance
  PLOT_MRK_HPENTAGON,                       //hollow pentagon opitional
  PLOT_MRK_HTRIANGLE,                       //hollow triangle opitional
  PLOT_MRK_HFLOWER  ,                       //hollow flower opitional
  PLOT_MRK_HTIME    ,                       //hollow time opitional
  PLOT_MRK_TARGET   ,
  PLOT_MRK_PARTICLE , 
  PLOT_MRK_CUSTOM        
};      
/*************
* @type PlotStyleItem Style sheet itens.
*******/
enum PlotStyleItem
{
  PLOT_SS_CLR_BG        =  1,
  PLOT_SS_CLR_BORDER    =  2,
  PLOT_SS_CLR_FONT      =  3,
  PLOT_SS_FONT          =  4,
  PLOT_SS_PADDING       =  5,
  PLOT_SS_GAP           =  6,
  PLOT_SS_SHADOW        =  7,
  PLOT_SS_BORDER        =  8,
  PLOT_SS_BORDER_STYLE  =  9,
  PLOT_SS_TEXTDIR       = 10,
  PLOT_SS_ALIGN         = 11,
  PLOT_SS_DISPLAY       = 12,
  PLOT_SS_POSITION      = 13,
  PLOT_SS_BG_IMAGE      = 14,
  PLOT_SS_BG_TYPE       = 15,
  PLOT_SS_CLR_SHADOW    = 16,
  PLOT_SS_FONTSHADOW    = 17 
};/*@endof type PlotStyleItem */
/*************
* @type PlotBgType Style sheet itens.
*******/
enum PlotBgType
{
  PLOT_STRETCH      =  1,
  PLOT_TILE         =  2,
  PLOT_RATIO        =  3 
};/*@endof type PlotBgType */
/*************
* @type Plot
*******/
/*******************************************************************************
* @endof block Plot opitions
*******************************************************************************/
/*******************************************************************************
* @block Plot auxiliar structures
*******************************************************************************/
/************** 
* @type PlotColor Color settings.
*******/
struct PlotColor
{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  unsigned char alpha;
  long int cd_color;
};
struct PlotFont
{
  string typeface;
  int style;
  int size;
  int shadow;
};
/************** 
* @type PlotLine Line settings.
*******/
struct PlotLine
{
  int width;
  PlotLineStyle style;
};
/************** 
* @type PlotPoint Point structure.
*******/
struct PlotPoint
{
  double x;
  double y;
};
/************** 
* @type PlotDate Date structure.
*******/
struct PlotDate 
{
  int day;                                                     
  int month;                                                   
  int year;                                                    
};
/************** 
* @type PlotMark Mark settings.
* @var type int Mark type predefined on PlotMarkType.
* @var size int Mark size, a positive value.
* @var cust int Custom index. Used when type = PLOT_MRK_CUSTOM.
* @var hollow bool Hollow flag. True to hollowed mark.
*******/
struct PlotMark 
{
  int type;
  int size;
  int cust;
  bool hollow;
};
struct PlotReachObj;
/*******************************************************************************
* @endof block Plot auxiliar structures
*******************************************************************************/
enum PlotVar //TODO: review it!!!
{
   PLOT_FIELD = 0,
   PLOT_WELL,
   PLOT_COMPLETATION,
   PLOT_GROUP,
   PLOT_LAYER,
   PLOT_BLOCK,
   PLOT_GENERAL,
   PLOT_VARIABLE,
   PLOT_DAYS,
   PLOT_TIME,
   PLOT_TIME_SIMULATION
};
enum PlotFontType //TODO: remove it!!!
{
  PLOT_SYSTEM = CD_SYSTEM,
  PLOT_COURIER = CD_COURIER,
  PLOT_TIMES_ROMAN = CD_TIMES_ROMAN,
  PLOT_HELVETICA = CD_HELVETICA
};   
/*************
* @function plotFont Create a font structure.
* @param strTypeface char* Font typeface, e.g.: Arial, Courier, Verdana...
* @param intStyle int Font style, predefined on PlotFontStyle.
* @param intSize int Font size, a positive value.
* @return PlotFont New font structure.
*******/
PLOTAPI PlotFont plotFont (const char* face, int style, int size, int shadow = 0);
/*************
* @function plotGetFontSize Get font size from font object.
* @param f PlotFont Font object.
* @return int Font size.
*******/
PLOTAPI int plotGetFontSize (PlotFont f);
/*************
* @function plotGetFontTypeFace Get font typeface from font object.
* @param f PlotFont Font object.
* @return char* Font typeface name.
*******/
PLOTAPI const char* plotGetFontTypeface (PlotFont& f);
/*************
* @function plotGetFontStyle Get font style from font object.
* @param f PlotFont Font object.
* @return int Value predefined on PlotFontStyle.
*******/
PLOTAPI int plotGetFontStyle (PlotFont f);
/*************
* Set font shadow translation.
*******/
PLOTAPI void plotFontSetShadow (PlotFont f, int shadow);
/*******************************************************************************
* @block API Functions
*******************************************************************************/
/*******************************************************************************
* @block Color API
*******************************************************************************/
/*************
* @function plotColor Create a color object.
* @param r uchar Red color component. Value from 0 up to 255.
* @param g uchar Green color component. Value from 0 up to 255.
* @param r uchar Blue color component. Value from 0 up to 255.
* @param r uchar Alpha color component. Value from 0(transparent) 
* up to 255 (cloudy). Default is 255.
* @return PlotColor New color object.                                     
*******/
PLOTAPI PlotColor plotColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
/*************
* @function plotGetColorRed Return red component from plot color object.
* @param pcl PlotColor Color object. 
* @return int Value from 0 up to 255.
*******/
PLOTAPI int plotGetColorRed(PlotColor pcl);
/*************
* @function plotGetColorGreen Return red component from plot color object.
* @param pcl PlotColor Color object. 
* @return int Value from 0 up to 255.
*******/
PLOTAPI int plotGetColorGreen(PlotColor pcl);
/*************
* @function plotGetColorBlue Return green component from plot color object.
* @param pcl PlotColor Color object. 
* @return int Value from 0 up to 255.
*******/
PLOTAPI int plotGetColorBlue(PlotColor pcl);
/*************
* @function plotGetColorAlpha Return alpha component from plot color object.
* @param pcl PlotColor Color object. 
* @return int Value from 0 up to 255.
*******/
PLOTAPI int plotGetColorAlpha(PlotColor pcl);
/*************
* @function plotGetColorCD Return respective color value on cd system.
* @param pcl PlotColor Color object. 
* @return lint Long int value, @see CD color definition.
*******/
PLOTAPI long int plotGetColorCD(PlotColor pcl);
/*******************************************************************************
* @endof block Color API
*******************************************************************************/
/*******************************************************************************
* @block Line API
*******************************************************************************/
/*************
* @function plotLine Create a line object from line structure.
* @param intWidth int Width value.
* @param intStyle PlotLineStyle Line style.
* @return PlotLine New line object. 
*******/
PLOTAPI PlotLine plotLine(int intWidth, PlotLineStyle intStyle);
/*************
* @function plotGetLineWidth Get line width value.
* @param pln PlotLine Line object.
* @return int Line width value.
*******/
PLOTAPI int plotGetLineWidth(PlotLine pln);
/*************
* @function plotGetLineWidth Get line width value.
* @param pln PlotLine Line object.
* @return int Line width value.
*******/
PLOTAPI PlotLineStyle plotGetLineStyle(PlotLine pln);
/*******************************************************************************
* @endof block Line API
*******************************************************************************/
/*******************************************************************************
* @block Point API
*******************************************************************************/
/*************
* @function plotPoint Create a point object.
* @param dblX double X point value.
* @param dblY double Y point value.
* @return PlotPoint New point object.   
*******/
PLOTAPI PlotPoint plotPoint(double dblX, double dblY);
/*******************************************************************************
* @endof block Point API
*******************************************************************************/
/*******************************************************************************
* @block Date API
*******************************************************************************/
/*************
* @function plotDate Create a new date object.
* @param intDay int Day valid values from 1 up to 31.
* @param intMonth int Month valid values from 1 up to 12.
* @param intYear int Year valid values from 1900 up to 4000.
* @return PlotDate New date object. 
*******/
PLOTAPI PlotDate plotDate(int intDay, int intMonth, int intYear);
/*************
* @function plotGetDateDay Return day value from date object.
* @param dat PlotDate Date object.
* @return int Day value. 
*******/
PLOTAPI int plotGetDateDay(PlotDate dat);
/*************
* @function plotGetDateMonth Return month value from date object.
* @param dat PlotDate Date object.
* @return int Month value. 
*******/
PLOTAPI int plotGetDateMonth(PlotDate dat);
/*************
* @function plotGetDateYear Return year value from date object.
* @param dat PlotDate Date object.
* @return int Year value. 
*******/
PLOTAPI int plotGetDateYear(PlotDate dat);
/*************
* @function plotGetDateDaysInMonth Get number of days in month.
* @param dat PlotDateMonth Date object.
* @return int Number of days in month. 
* @change plotGetDateNumberOfMonthDays -> plotGetDateDaysInMonth
*******/
PLOTAPI int plotGetDateDaysInMonth(PlotDate dat);
/*************
* @function plotGetDateDaysInYear Get number of days in year
* @param dat PlotDate Year number(1900->4000).
* @return int Number of days in year. 
* @change plotGetNumberOfYearDays -> plotGetDateDaysInYear
*******/
PLOTAPI int plotGetDateDaysInYear(PlotDate dat);
/*************
* @function plotDateIncDay Increases a day in the date.
* @param dat PlotDate Date object.
* @return PlotDate New date object.  
* @change plotIncDateDay -> plotDateIncDay
*******/
PLOTAPI PlotDate plotDateIncDay(PlotDate dat);
/*************
* @function plotDateIncDay Increases a day in the date.
* @param dat PlotDate Date object.
* @return PlotDate New date object.  
* @change plotDecDateDay -> plotDateDecDay
*******/
PLOTAPI PlotDate plotDateDecDay(PlotDate dat);
/*************
* @function plotGetElapsedDays Calculate elapsed days between start date 
* and end date.
* @param datStart PlotDate Start date.
* @param datEnd PlotDate End date.
* @return int Number of elapsed days.
*******/
PLOTAPI int plotGetElapsedDays(PlotDate datStart, PlotDate datEnd);
/*************
* @function plotGetElapsedMonths Calculate elapsed months between start 
* date and end date. Considers: start and
* end day 1.
* @param datStart PlotDate Start date.
* @param datEnd PlotDate End date.
* @return int Number of elapsed months.
*******/
PLOTAPI int plotGetElapsedMonths(PlotDate datStart, PlotDate datEnd);
/*************
* @function plotGetElapsedTrimesters Calculate elapsed trimesters between
* start date and end date. Considers: start 
* and end day 1.
* @param datStart PlotDate Start date.
* @param datEnd PlotDate End date.
* @return int Number of elapsed trimesters.
*******/
PLOTAPI int plotGetElapsedTrimesters(PlotDate datStart, PlotDate datEnd);
/*************
* @function plotGetElapsedSemesters Calculate elapsed semesters between 
* start date and end date. Considers: start 
* and end day 1.
* @param datStart PlotDate Start date.
* @param datEnd PlotDate End date.
* @return int Number of elapsed semesters.
*******/
PLOTAPI int plotGetElapsedSemesters(PlotDate datStart, PlotDate datEnd);
/*************
* @function plotDateToJulian Convert date to Julian system.
* @param dat PlotDate Date object. 
* @return long Coverted date. 
*******/
PLOTAPI long plotDateToJulian(PlotDate dat);
/*************
* @function plotDateToDouble Convert a date object to a double value.
* @param dat PlotDate Date object.
* @return double Converted date in format "year"."year fraction".
* @see http://www.brokersys.com/snippets/JDN_L.C 
*******/
PLOTAPI double plotDateToDouble(PlotDate dat);
/*************
* @function plotDoubleToDate Convert a double date value to PlotDate.
* @param dblDate double Date in format "year"."year fraction".
* @return PlotDate Date object.
*******/
PLOTAPI PlotDate plotDoubleToDate(double dblDate); 
/*******************************************************************************
* @endof block Date API
*******************************************************************************/
/*******************************************************************************
* @block Mark API
*******************************************************************************/
/*************
* @function plotMark Create a mark object.
* @param intType int Pre-defined mark type in PlotMarkType.
* @param intSize int Mark size, value from 0.
* @param bolHollow bool Hollow flag. True to mark hollowed. 
* Default is false. 
* @param idxCust int Custom index. Ordinace depends  
* @return PlotMark New plot mark object.
*******/
PLOTAPI PlotMark plotMark(int intType, int intSize, bool bolHollow = false, int idxCust = 0);
/*************
* @function plotGetMarkType Get mark type from mark object.
* @param mrk PlotMark Mark object.
* @return int Mark type.
*******/
PLOTAPI int plotGetMarkType(PlotMark mrk);
/*************
* @function plotGetMarkSize Get mark size from mark object.
* @param mrk PlotMark Mark object.
* @return int Mark size.
*******/
PLOTAPI int plotGetMarkSize(PlotMark mrk);
/*************
* @function plotGetMarkCustomIdx Get mark custom index from mark object.
* @param mrk PlotMark Mark object.
* @return int Custom mark index.
*******/
PLOTAPI int plotGetMarkCustomIdx(PlotMark mrk);
/*******************************************************************************
* @endof block Mark API
*******************************************************************************/
/*************
* MEMO API
*******/
/*************
* @function plotMemo Create new memo object.
* @param fltX float X coordinate associated to a curve.
* @param fltY float Y coordinate associated to a curve.
* @param strMemo char* Memo message, short text.
* @param strDesc char* Memo description, larger text.
* @param id int Memo id given by user. Any number to 
* identify the memo, it is not a unique id.
* Default is 0.
* @param intX int X memo box position, default is 0.
* @param intY int Y memo box position, default is 0.
* @return PlotMemo Instance of memo object.
*******/
PLOTAPI PlotMemo* plotMemo (float x, 
                            float y, 
                            const char * strMemo, 
                            const char* strDesc = NULL, 
                            int intX = -1, 
                            int intY = -1, 
                            int id = 0);
PLOTAPI void plotMemoDestroy(PlotMemo* memo);
/*************
* @function plotMemoSetMessage Change memo message.
* @param memo PlotMemo* Memo object.
* @param strMsg char* New memo message.
*******/
PLOTAPI void plotMemoSetMessage(PlotMemo* memo, const char * strMsg);
/*************
* @function plotMemoSetDesc Change memo description.
* @param memo PlotMemo* Memo object.
* @param strMsg char* New memo description.
*******/
PLOTAPI void plotMemoSetDesc(PlotMemo* memo, const char * strDesc);
/*************
* @function plotMemoGetMessage Get memo message.
* @param memo PlotMemo* Memo object.
* @return char* Memo message.
*******/
PLOTAPI const char* plotMemoGetMessage(PlotMemo* memo);
/*************
* @function plotMemoGetDesc Get memo description.
* @param memo PlotMemo* Memo object.
* @return char* Memo description.
*******/
PLOTAPI const char* plotMemoGetDesc(PlotMemo* memo);
/*************
* @function plotMemoGetBoxPosition Get memo message box position in 
* raster value.
* @param memo PlotMemo* Memo reference.
* @param* intX int* Reference to return x raster position. 
* @param* intY int* Reference to return y raster position. 
*******/
PLOTAPI void plotMemoGetBoxPosition(PlotMemo* memo, int* intX, int* intY);
/*************
* @function plotMemoSetHide Set hide/show memo.
* @param memo PlotMemo* Memo object.
* @param bolHide boolean True to hide memo and false to show.
*******/
PLOTAPI void plotMemoSetHide(PlotMemo* memo, bool bolHide);
/*************
* @function plotMemoGetHide Get hide/show memo.
* @param memo PlotMemo* Memo object.
* @return bool True to hide memo and false to show.
*******/
PLOTAPI bool plotMemoGetHide(PlotMemo* memo);
/*************
* @function plotMemoSetId Set memo id. Any number. Not uniq id.
* @param memo PlotMemo* Memo object.
* @param id int Memo id.
*******/
PLOTAPI void plotMemoSetId(PlotMemo* memo, int id);
/*************
* @function plotMemoGetId Get memo id given by user.
* @param memo PlotMemo* Memo object.
* @return int Memo id.
*******/
PLOTAPI int plotMemoGetId(PlotMemo* memo);
/*************
* @function plotMemoSetFontColor Set memo font color.
* @param memo PlotMemo* Memo object.
* @param pcl PlotColor Color settings.
*******/
PLOTAPI void plotMemoSetFontColor(PlotMemo* memo, PlotColor pcl);
/*************
* @function plotMemoSetBgColor Set memo background color.
* @param memo PlotMemo* Memo object.
* @param pcl PlotColor Color settings.
*******/
PLOTAPI void plotMemoSetBgColor(PlotMemo* memo, PlotColor pcl);
/*************
* @function plotMemoSetBorder Color Set memo border color.
* @param memo PlotMemo* Memo object.
* @param pcl PlotColor Color settings.
*******/
PLOTAPI void plotMemoSetBorderColor(PlotMemo* memo, PlotColor pcl);
/*************
* @function plotMemoSetAlpha Set memo alpha.
* @param memo PlotMemo* Memo object.
* @param uchAlpha uchar Alpha value.
*******/
PLOTAPI void plotMemoSetAlpha(PlotMemo* memo, unsigned char uchAlpha);
/*************
* @function plotMemoSetAlign Set memo text and connector alignment.
* @param memo PlotMemo* Memo object.
* @param pta PlotAlign Alignment opition.
*******/
PLOTAPI void plotMemoSetAlign(PlotMemo* memo, PlotAlign pta);
/*************
* @function plotMemoSetPadding Set memo padding size.
* @param memo PlotMemo* Memo object.
* @param intSize int Padding size.
*******/
PLOTAPI void plotMemoSetPadding(PlotMemo* memo, int intSize);
/*************
* @function plotMemoSetGap Set memo gap size.
* @param memo PlotMemo* Memo object.
* @param intSize int Gap size.
*******/
PLOTAPI void plotMemoSetGap(PlotMemo* memo, int intSize);
/*************
* @function plotMemoSetBorderSize Set memo border size.
* @param memo PlotMemo* Memo object.
* @param intSize int Border size.
* @param pls PlotLineStyle Border line style.
*******/
PLOTAPI void plotMemoSetBorder(PlotMemo* memo, int intSize, PlotLineStyle pls);
/*************
* @function plotMemoSetConnectorSize
* @param memo PlotMemo* Memo object.
* @param intSize float Connector size.
* @param pls PlotLineStyle Connector line style.
*******/
PLOTAPI void plotMemoSetConnector(PlotMemo* memo, int intSize, PlotLineStyle pls);
/*************
* @function plotMemoSetConnectorSize
* @param memo PlotMemo* Memo object.
* @param intSize float Connector size.
* @param pls PlotLineStyle Connector line style.
* @param mrkStart PlotMark Start connector mark.
* @param mrkEnd PlotMark End connector mark. 
*******/
PLOTAPI void plotMemoSetConnector(PlotMemo* memo, int intSize, PlotLineStyle pls,
                                   PlotMark mrkStart, PlotMark mrkEnd);
/*************
* @function plotMemoSetFont
* @param memo PlotMemo* Memo object.
* @param pft PlotFont Font settings.
*******/
PLOTAPI void plotMemoSetFont(PlotMemo* memo, PlotFont pft);
/*************
* @function plotMemoSetAnchor Set memo anchor - mark to show when memo 
* is hide.
* @param memo PlotMemo* Memo object.
* @param mrk PlotMark Mark object.  
*******/
PLOTAPI void plotMemoSetAnchor(PlotMemo* memo, PlotMark mrk);

/******************************************************************************
* @block Curve API
******************************************************************************/
/*************
* @function plotCreateCurve Creates a new curve.
* @return PlotCurve* New curve reference.
*******/
PLOTAPI PlotCurve* plotCreateCurve(void);
/*************
* @function plotCreateCurve Creates a new curve.
* @param pai PlotAxisId Axis id.
* @param mrk PlotMark Curve mark.
* @param pln PlotLine Curve line.
* @param pclL PlotColor Curve line color.
* @param pclA PlotColor Curve area color.
* @return PlotCurve* New curve reference.
*******/
PLOTAPI PlotCurve* plotCreateCurve(PlotAxisId pai, PlotMark mrk, PlotLine pln, 
                                      PlotColor pclL, PlotColor pclA);
/*************
* @function plotDestroyCurve Destroy curve.
* @param crv PlotCurve* Curve to be destroyed.
*******/
PLOTAPI void plotDestroyCurve(PlotCurve* crv);
/*************
* @function plotAddPoint Add a point at end of curve.
* @param crv PlotCurve* Curve refernce.
* @param dblX double X point value.
* @param dblY double Y point value.
* @return int Point index in curve.
*******/
PLOTAPI int plotAddPoint(PlotCurve* crv, double dblX, double dblY);
/*************
* @function plotReplacePoint Modifies a existent point in curve.
* @param crv PlotCurve* Curve reference.
* @param idx int Target point index.
* @param dblX double X point value.
* @param dblY double Y point value.
* @return int Point index. Differs from idx when the
* point not exist.
*******/
PLOTAPI int plotReplacePoint(PlotCurve* crv, int idx, double dblX, double dblY);
/*************
* @function plotRemovePoint Removes a point from curve.
* @param crv PlotCurve* Curve reference.
* @param idx int Point index.
* @return int 1 to success or 0 otherwise.
*******/
PLOTAPI int plotRemovePoint(PlotCurve* crv, int idx);
PLOTAPI void plotRemoveAllPoints (PlotCurve* crv);
/*************
* @function plotGetNumberOfPoints Gets the number of points in curve.
* @param crv PlotCurve* Curve reference.
* @return int Number of points in curve.
*******/
PLOTAPI int plotGetNumberOfPoints(PlotCurve* crv);
/*************
* @function plotGetCurvePoint Get a point from index into the curve.
* @param crv PlotCurve* Curve reference.
* @param idxP int Point index.
* @return PlotPoint Point object.
*******/
PLOTAPI PlotPoint plotGetCurvePoint(PlotCurve* crv, int idxP);
/*************
* @function plotGetCurvePointX Gets the value of coordinate X from 
* point into the curve on index idxP.
* @param crv PlotCurve* Curve reference.
* @param idxP int Point index.
* @return double X coordinate value.
*******/
PLOTAPI double plotGetCurvePointX(PlotCurve* crv, int idxP);
/*************
* @function plotGetCurvePointY Gets the value of coordinate Y of a 
* point of the curve
* @param crv PlotCurve* Curve reference.
* @param idxP int Point index.
* @return double Y coordinate value.
*******/
PLOTAPI double plotGetCurvePointY(PlotCurve* crv, int idxP);
/*************
* @function plotSetCurveType Set curve draw type.
* @param crv PlotCurve* Curve reference.
* @param pdt PlotDataType Curve draw type.
* @return int Old curve draw type.
*******/
PLOTAPI int plotSetCurveType(PlotCurve* crv, PlotDataType pdt);
/*************
* @function plotGetCurveType Get current curve draw type.
* @param crv PlotCurve* Curve reference.
* @return int Current curve draw type.  
*******/
PLOTAPI int plotGetCurveType(PlotCurve* crv);
/*************
* @function plotSetCurveLabel Set curve label text.
* @param crv PlotCurve* Curve reference.
* @param str char* Label text.
* @return int 1 to success or 0 otherwise.
*******/
PLOTAPI int plotSetCurveLabel(PlotCurve* crv, const char* str);
/*************
* @function plotGetCurveLabel Returns the curve label text.
* @param crv PlotCurve* Curve reference.
* @return char* Label text value.
*******/
PLOTAPI const char* plotGetCurveLabel(PlotCurve* crv);
/*************
* @function plotSetCurveShowLabel Set curve label flag.
* @param crv PlotCurve* Curve reference.
* @param flag int 1 to show or 0 to hide curve label.
* @return int The old flag value.
*******/
PLOTAPI int plotSetCurveShowLabel(PlotCurve* crv, int flag);
/*************
* @function plotGetCurveShowLabel Returns curve label show flag.
* @param crv PlotCurve* Curve reference.
* @return int The flag value.
*******/
PLOTAPI int plotGetCurveShowLabel(PlotCurve* crv);
/*************
* @function plotSetCurveAxisId Change curve axis id.
* @param crv PlotCurve* Curve reference.
* @param pai int Plot axis id.
* @return int The old curve axis id.
*******/
PLOTAPI int plotSetCurveAxisId(PlotCurve* crv, int pai);
/*************
* @function plotGetCurveAxisId Returns curve axis id.
* @param crv PlotCurve* Curve reference.
* @return PlotAxisId Axis id.
*******/
PLOTAPI PlotAxisId plotGetCurveAxisId(PlotCurve* crv);
/*************
* @function plotSetCurveMark Change curve mark.
* @param crv PlotCurve* Curve reference.
* @param mrk PlotMark Mark object.
* @return PlotMark Old curve mark.
*******/
PLOTAPI PlotMark plotSetCurveMark(PlotCurve* crv, PlotMark mrk);
/*************
* @function plotGetCurveMark Get mark set in curve
* @param crv PlotCurve* Curve reference.
* @return PlotMark Mark set in curve
*******/
PLOTAPI PlotMark plotGetCurveMark(PlotCurve* crv);
/*************
* @function plotGetCurveShowMark Get flag that indicate if mark have 
* to be draw.
* @param crv PlotCurve* Curve reference.
* @return int Curve mark flag value. 1 to show or 
* 0 to hide.
*******/
PLOTAPI int plotGetCurveShowMark(PlotCurve* crv);
/*************
* @function plotSetCurveShowMark Set show curve mark flag.
* @param crv PlotCurve* Curve reference.
* @param flag int Show curve mark flag.
* @return int
*******/
PLOTAPI int plotSetCurveShowMark(PlotCurve* crv, int flag); 
/*************
* @function plotSetCurveLine Set curve line style and size.
* @param crv PlotCurve* Curve reference.
* @param pln PlotLine New line settings.
* @return PlotLine Old line settings.
*******/
PLOTAPI PlotLine plotSetCurveLine(PlotCurve* crv, PlotLine pln);
/*************
* @function plotGetCurveLine Get curve line settings.
* @param crv PlotCurve* Curve reference.
* @return PlotLine Line setting.
*******/
PLOTAPI PlotLine plotGetCurveLine(PlotCurve* crv);
/*************
* @function plotSetCurveShowLine Set curve line flag.
* @param crv PlotCurve* Curve reference.
* @param flag int 1 to show or 0 to hide curve line.
* @return int The old curve line flag.
*******/
PLOTAPI int plotSetCurveShowLine(PlotCurve* crv, int flag);
/*************
* @function plotGetCurveShowLine Get curve line flag.
* @param crv PlotCurve* Curve reference.
* @return int Curve line flag.
*******/
PLOTAPI int plotGetCurveShowLine(PlotCurve* crv);
/*************
* @function plotSetCurveColor Set curve line and area color.
* @param crv PlotCurve* Curve reference.
* @param pclL PlotColor Curve line color. 
* @param pclA PlotColor Curve area color. 
* @param pclANeg PlotColor Curve area negative color. 
*******/
PLOTAPI void plotSetCurveColor(PlotCurve* crv, PlotColor pclL, PlotColor pclA, PlotColor pclANeg);
/*************
* @function plotSetCurveColor Set curve line and area color.
* @param crv PlotCurve* Curve reference.
* @param pclL PlotColor Curve line color. 
* @param pclA PlotColor Curve area color. 
*******/
PLOTAPI void plotSetCurveColor(PlotCurve* crv, PlotColor pclL, PlotColor pclA);
/*************
* @function plotSetCurveColor Set curve color settings.
* @param crv PlotCurve* Curve reference.
* @param pclL PlotColor Curve line color.
* @return PlotColor Old color properties
*******/
PLOTAPI PlotColor plotSetCurveColor(PlotCurve* crv, PlotColor pclL);
/*************
* @function plotGetCurveColor Returns the curve line color settings.
* @param crv PlotCurve* Curve reference.
* @return PlotLine Curve line color.
*******/
PLOTAPI PlotColor plotGetCurveColor(PlotCurve* crv);
/*************
* @function plotSetCurveAreaColor Set curve area color settings. Used
* when draw bar graph, curve area...
* @param crv PlotCurve* Curve reference.
* @param pclA PlotColor Curve area color.
* @return PlotColor Old curve area color.
*******/
PLOTAPI PlotColor plotSetCurveAreaColor(PlotCurve* crv, PlotColor pclA);
/*************
* @function plotGetCurveAreaColor Returns the curve area color settings.
* @param crv PlotCurve* Curve reference.
* @return PlotLine Curve area color.
*******/
PLOTAPI PlotColor plotGetCurveAreaColor(PlotCurve* crv);
/*************
* @function plotSetCurveAreaNegColor Set the curve negative area color
* @param crv PlotCurve* Curve reference
* @param pcl PlotColor Negative area color
* @return PlotLine Curve Negative area color
*******/
PLOTAPI void plotSetCurveAreaNegColor(PlotCurve* crv, PlotColor pcl);
/*************
* @function plotGetCurveAreaNegColor Returns the curve negative area color
* @param crv PlotCurve* Curve reference
* @return PlotLine Curve negative area color
*******/
PLOTAPI PlotColor plotGetCurveAreaNegColor(PlotCurve* crv);
/*************
* @function plotSetCurveAutoscaleFlag Determines automatica curve scale
* @param crv PlotCurve* Curve reference.
* @param flag int Flag value, 1 to enable autoscale, 0 otherwise
* @return int Old flag value
*******/
PLOTAPI int plotSetCurveAutoscaleFlag(PlotCurve* crv, int flag);
/*************
* @function plotGetCurveAutoscaleFlag Returns the autoscale flag in curve
* @param crv PlotCurve* Curve reference.
* @return int The flag value
*******/
PLOTAPI int plotGetCurveAutoscaleFlag(PlotCurve* crv);
/*************
* @function plotSetCurveMarkInterval Set interval between marks to be draw.
* @param crv PlotCurve* Curve reference.
* @param intInterval int New interval value.
* @return int Old interval.
*******/
PLOTAPI int plotSetCurveMarkInterval(PlotCurve* crv, int intInterval);
/*************
* @function plotGetCurveMarkInterval Returns the interval of marks
* @param crv PlotCurve* Curve reference.
* @return int Interval value
*******/
PLOTAPI int plotGetCurveMarkInterval(PlotCurve* crv);
/*************
* @function plotSetCurvePickFlag Defines if a curve can be handle using 
* the functions of pick
* @param crv PlotCurve* Curve handle
* @param flag int 1 to enable pick, 0 otherwise
* @return int Old flag value
*******/
PLOTAPI int plotSetCurvePickFlag(PlotCurve* crv, int flag);
/*************
* @function plotGetCurvePickFlag Returns flag indicating if a curve 
* can be handle using pick functions
* @param crv PlotCurve* Curve reference.
* @return int The flag value
*******/
PLOTAPI int plotGetCurvePickFlag(PlotCurve* crv);
/*************
* @function plotSetCurveShowMemo Set curve show memo flag.
* @param crv PlotCurve* Curve reference. 
* @param flag int Curve show memo flag.
* @return int Old curve show memo flag value. 
*******/
PLOTAPI int plotSetCurveShowMemo(PlotCurve* crv, int flag);
/*************
* @function plotGetCurveShowMemo Get show flag value.
* @param crv PlotCurve* Curve reference. 
* @return int Curve show memo flag current value.
*******/
PLOTAPI int plotGetCurveShowMemo(PlotCurve* crv);
/*************
* @function plotSetCurveMemoColorFlags Set curve memo color flags.
* @param crv PlotCurve* Curve reference. 
* @param bolBrCC bool True to use curve color on memo border.
* @param bolBgCC bool True to use curve color on memo background.
* @param bolFntCC bool True to use curve color on memo font.
*******/
PLOTAPI void plotSetCurveMemoColorFlags(PlotCurve* crv, bool bolBrCC, 
                                         bool bolBgCC, bool bolFntCC);
/*************
* @function plotSetCurveShow Set show curve flag.
* @param crv PlotCurve* Curve reference. 
* @param bolShow bool True to show or false to hide curve. 
* @return bool Old falg value. 
*******/
PLOTAPI bool plotSetCurveShow(PlotCurve* crv, bool bolShow);
/*************
* @function plotGetCurveShow Get show curve flag value.
* @param crv PlotCurve* Curve reference. 
* @return bool True if show or false if hide curve.  
*******/
PLOTAPI bool plotGetCurveShow(PlotCurve* crv);
/*************
* @function plotSetCurveShadow Set curve shadow shift
* @param crv PlotCurve* Curve reference
* @param int intShiftX Shadow x shift
* @param int intShiftY Shadow y shift
*******/
PLOTAPI void plotSetCurveShadow(PlotCurve* crv, int intShiftX, int intShiftY);
/*************
* @function plotSetCurveInteraction Set curve enable/disable to interaction
*           on plot event (pick and tip).
* @param crv PlotCurve* Curve reference
* @param bool enable
*******/
PLOTAPI void plotSetCurveInteraction (PlotCurve* crv, bool enable);
/*************
* @function plotCurveAddMemo Add a memo in curve.
* @param crv PlotCurve* Curve reference.
* @param memo PlotMemo Memo object.
*******/
PLOTAPI void plotCurveAddMemo(PlotCurve* crv, PlotMemo* memo);
/*************
* @function plotCurveRemMemo Remove a memo by memo index. This
* function not destroy memo.
* @param crv PlotCurve* Curve reference.
* @param idx int Memo index.
* @return PlotMemo* Removed memo object.
*******/
PLOTAPI PlotMemo* plotCurveRemMemo(PlotCurve* crv, int idx);
/*************
* @function plotCurveRemAllMemos Remove all memos from curve.
* @param crv PlotCurve* Curve reference.
*******/
PLOTAPI void plotCurveRemAllMemos(PlotCurve* crv);
/*************
* @function plotCurveGetMemo Get memo from curve by index.
* @param crv PlotCurve* Curve reference.
* @param idx int Memo index.
* @return PlotMemo Required memo object.
*******/
PLOTAPI PlotMemo* plotCurveGetMemo(PlotCurve* crv, int idx);
/*************
* @function plotCurveSearchMemo Search for a memo by memo id into curve.
* @param crv PlotCurve* Curve reference.
* @param id int Memo id.  
* @return PlotMemo* Required memo instance. 
*******/
PLOTAPI PlotMemo* plotCurveSearchMemo(PlotCurve* crv, int id);
/*************
* @function SetHistogramColor 
* @deprecated Use plotSetCurveAreaColor(PlotCurve, PlotColor)
*******/
DS_DEPRECATED PLOTAPI PlotColor plotSetHistogramColor(Plot* plot, PlotCurve* crv, PlotColor pcl);
/*************
* @function plotSetDrawHistogram
* @deprecated Use plotSetCurveType(PlotCurve, PLOT_BAR)
*******/
DS_DEPRECATED PLOTAPI void plotSetDrawHistogram(Plot* plot, PlotCurve* crv, int intFlag);
/*******************************************************************************
* @endof block Curve API
*******************************************************************************/
/*************
* PLOT API
***/
/*************
* @function plotCreate Create a new instance of glplot.
* @param multichart_mode true if multiple charts can be used. If 'false',
*        will automatically create one chart (enabling the deprecated one-chart API).
* @return Plot* A reference to new glPlot instance.
*******/
PLOTAPI Plot* plotCreate (bool multichart_mode=false);
/*************
* @function plotSetImagePath Set path of images and textures.
* @param plot Plot* Plot reference.
* @param strPath char* Path string.
*******/
PLOTAPI void plotSetImagePath(Plot* plot, const char* strPath);
/*************
* @function plotGetImagePath Get path of images and textures.
* @param plot Plot* Plot reference.
* @return char* Path string reference.  
*******/
PLOTAPI const char* plotGetImagePath(Plot* plot);
/*************
* @function plotInit Initialize glplot module. Should be called
* once a program before the first graph is created.
* @return int 1 if success or 0 otherwise.     
*******/
PLOTAPI int plotInit(void);
/*************
* @function plotClose Finalize glplot module. Should be called before 
* the program ends to release the resources 
* allocated by function plotInit for this module.
* @return int 1 if success or 0 otherwise.     
*******/
PLOTAPI int plotClose(void);
/*************
* @function plotDestroy Destroy a plot instance.
* @param plot Plot* Plot instance reference to be destroyed. 
*******/
PLOTAPI void plotDestroy(Plot* plot);
/*************
* plotSetMode Set plot operation mode.
* @param plot Plot* Plot reference.
* @param PlotMode Any predefined mode on PlotMode.
*******/
PLOTAPI void plotSetMode (Plot* plot, PlotMode mode);
/*************
* plotGetMode Get plot operation mode.
* @param plot Plot* Plot reference.
* @return PlotMode Current operation mode predefined mode on PlotMode.
*******/
PLOTAPI PlotMode plotGetMode (Plot* plot);
PLOTAPI void plotSetProjectionStack (Plot* plot, AlgGLStack* pstack);

/*************
* CHART API
*******/
PLOTAPI Chart* plotGetChart (Plot* plot, int chartid);
PLOTAPI CurveChart* plotGetCurveChart (Plot* plot, int chartid);
PLOTAPI BarChart* plotGetBarChart (Plot* plot, int chartid);
PLOTAPI HistogramChart* plotGetHistogramChart (Plot* plot, int chartid);

/**
* Export data from chart on csv format.
* Only implemented to CurveChart. 
* //TODO: implement it to other charts.
*/
PLOTAPI bool plotChartExportDataCSV (Chart* chart, const char* outfile);
PLOTAPI bool plotExportCurvesCSV (int curvecount, PlotCurve** curves, const char* outfile);

/*
* Destroy all data (curve/bar) in chart
*/
PLOTAPI void plotChartDestroyData (Chart* chart);
PLOTAPI PlotAxis* plotChartGetAxis (Chart* chart, PlotAxisId axisid);
PLOTAPI void plotChartSetMatrixPosition (Chart* chart, int line, int column);
/***
* Set chart feature active.
* @param features Any of chart features @see PlotFunc.
* @param active True to set active or false otherwise.
*/
PLOTAPI void plotChartSetActive (Chart* chart, int features, bool active);
/***
* Get active flag value. You can get only one 
* functionality active flag value.
* @param feature Any of chart features @see PlotFunc.
* @return bool Active flag value. 
*/
PLOTAPI bool plotChartGetActive (Chart* chart, PlotFunc feature);
/***
* plotChartSetShowGridMarks Show or hide grid marks of chart.
* Returns the old value.
*/
PLOTAPI int plotChartSetShowGridMarks (Chart* chart, int intFlag);
/***
* plotChartGetShowGridMarks Returns 1 if grid marks of chart are being shown, 0 otherwise.
*/
PLOTAPI int plotChartGetShowGridMarks (Chart* chart);
/***
* Set shadow color to main grid.
* @param char Object reference.
* @param color Shadow color.
*/
PLOTAPI void plotChartSetGridShadowColor (Chart* chart, PlotColor color);
/***
* plotGetGridShadowColor Get main grid shadow color
* @return PlotColor Shadow color
*/
PLOTAPI PlotColor plotChartGetGridShadowColor (Chart* chart);
PLOTAPI void plotChartSetTitleText (Chart* chart, const char* str);
PLOTAPI const char* plotChartGetTitleText (Chart* chart);
PLOTAPI void plotChartSetSubtitleText (Chart* chart, const char* str);
PLOTAPI const char* plotChartGetSubtitleText (Chart* chart);
PLOTAPI void plotChartSetBgImage (Chart* chart, PlotEntity entity, const char* image, int i = 0);
PLOTAPI const char* plotChartGetBgImage (Chart* chart, PlotEntity entity, int i = 0);
PLOTAPI bool plotChartSetWatermark (Chart* chart, const char* image, PlotBgType type);
PLOTAPI bool plotChartSetBgImageDrawArea (Chart* chart, const char* image, PlotBgType type);
PLOTAPI bool plotChartSetBgImageLegendBox (Chart* chart, const char* image, PlotBgType type);
/***
* Set text to point format.
* Use one or two %s, e.g.: "X=%s/nY=%s".
* @param plot Plot* Plot instance. 
* @param strPattern const char* Use one or two %s, e.g.: "X=%s/nY=%s".
* @param strXFormat const char* X value format. Not used when value is a date.
* @param strYFormat const char* Y value format. Not used when value is a date.
* @ps strXFormat and strYFormat always receive a double value. This parameters
* set how the double value has to be show. E.g.: "%.3f", "%f", "%.0f"...
* @param str const char* Point format text.
*/
PLOTAPI void plotChartSetTipPointPattern (Chart* chart, 
                                          const char* pattern, 
                                          const char* xformat = NULL, 
                                          const char* yformat = NULL);

PLOTAPI void plotChartSetShowAxisZeros (Chart* chart, bool show);
PLOTAPI bool plotChartGetShowAxisZeros (Chart* chart);
PLOTAPI int plotChartSetStyle (Chart* chart, PlotEntity pet, PlotStyleItem psi, int intVal, int idxAux = 0);
PLOTAPI PlotColor plotChartSetStyle (Chart* chart, PlotEntity pet, PlotStyleItem psi, PlotColor pcl, int idxAux = 0);
PLOTAPI PlotFont plotChartSetStyle (Chart* chart, PlotEntity pet, PlotStyleItem psi, PlotFont pft, int idxAux = 0);
PLOTAPI int plotChartGetStyleValue (Chart* chart, PlotEntity pet, PlotStyleItem psi, int idxAux = 0);
PLOTAPI PlotColor plotChartGetStyleColor (Chart* chart, PlotEntity pet, PlotStyleItem psi, int idxAux = 0);
PLOTAPI PlotFont plotChartGetStyleFont (Chart* chart, PlotEntity pet, PlotStyleItem psi, int idxAux = 0);
/**
* Desenha cursor em cruz com XOR, em raster. Pode ser usado para desenhar
* barras horizontais ou verticais.
* 
* Para converter das coordenadas de um eixo do gráfico para raster,
* utilize a função plotMapPoint().
* As seguintes situações são possíveis:
* - Se xr_new (xr_old) e yr_new (yr_old) forem iguais a PLOT_NAN_INT, 
* não desenha (apaga) cursor. 
* - Se xr_new e yr_new forem iguais a PLOT_NAN_INT, não desenha novo.
* - Se xr_new (xr_old) for PLOT_NAN_INT, desenha (apaga) uma barra 
* horizontal.
* - Se yr_new (yr_old) for PLOT_NAN_INT, desenha (apaga) uma barra 
* vertical.
* 
* @param axisid Eixo do gráfico.
* @param xr_new Nova posição x, em raster, do cursor.
* @param yr_new Nova posição y, em raster, do cursor.
* @param xr_old Posição anterior x, em raster, do cursor.
* @param yr_old Posição anterior y, em raster, do cursor.
*/ 
PLOTAPI void plotDrawCursor (Plot *plot, Chart* chart, 
                             PlotAxisId axisid, 
                             int xr_new, int yr_new, 
                             int xr_old, int yr_old);

/*************
* CHART ZOOM API
*******/
/***
* Set zoom selection into draw state. 
* To bring plot up to date, call plotRedraw.
* @param plot Plot* Plot reference.
* @param intRX0 int Raster initial x zoom area position.  
* @param intRY0 int Raster initial y zoom area position. 
* @param intRX1 int Raster end x zoom area position.
* @param intRY1 int Raster end y zoom area position.  
*/
PLOTAPI void plotChartZoomArea (Plot* plot, Chart* chart, int intRX0, int intRY0, int intRX1, int intRY1);
/***
* Set zoom selection without hold aspect ratio.
* To bring plot up to date, call plotRedraw.
* @param intRX0 int Raster initial x zoom area position.  
* @param intRY0 int Raster initial y zoom area position. 
* @param intRX1 int Raster end x zoom area position.
* @param intRY1 int Raster end y zoom area position.  
*/
PLOTAPI void plotChartZoomAreaNoAspectRatio (Plot* plot, Chart* chart, int intRX0, int intRY0, int intRX1, int intRY1);
PLOTAPI bool plotChartUndoZoom (Chart* chart);
/***
* Set next zoom state. Only works if there is any stored state.
* @return Indication if has to redraw or not. 
*/
PLOTAPI bool plotChartRedoZoom (Chart* chart);
PLOTAPI void plotChartClearZoom (Chart* chart);
/***
* Get current zoom stack level.
* @return Zoom stack level. 
*/
PLOTAPI int plotChartGetZoomLevel (Chart* chart);
/***
* Get number of zoom stack levels.
* @return Number of levels in zoom stack. 
*/
PLOTAPI int plotChartGetZoomLevels (Chart* chart);

/*************
* CURVECHART API
*******/
PLOTAPI CurveChart* plotCreateCurveChart (Plot* plot);
/***
* Insert a Curve to CurveChart.
* @param curve Curve to add in curvechart.
*/
PLOTAPI int plotChartAddCurve (CurveChart* curvechart, PlotCurve* curve);
/***
* Remove curve reference from CurveChart.
* Warning: This function not destroy the curve.
* @param curven Curve index (index start on 1).
*/
PLOTAPI int plotChartRemoveCurve (CurveChart* curvechart, int curven);
/***
* Remove all curve references from curvechart.
* Warning: This function not destroy the curves.
*/
PLOTAPI int plotChartRemoveAllCurves (CurveChart* curvechart);
/***
* Get curve reference by index in chartcurve.
* @param curven Curve index (index start on 1).
*/
PLOTAPI PlotCurve* plotChartGetCurve (CurveChart* curvechart, int curven);
/***
* Return the number of curves in curvechart.
* @return Number of curves in curvechart. 
*/
PLOTAPI int plotChartGetNumberOfCurves (CurveChart* curvechart);
/***
* Call delete to every curve into curvechart instance.
*/
PLOTAPI void plotChartDestroyCurves (CurveChart* curvechart);
/***
* Set last curve to be draw.
* @return PlotCurve* Old last curve reference.
*/
PLOTAPI PlotCurve* plotChartSetDrawCurveLast (CurveChart* curvechart, PlotCurve* curve);
PLOTAPI PlotCurve* plotChartGetDrawCurveLast (CurveChart* curvechart);
/***
* Set last curve to be draw.
* @return int Old last curve index.
*/
PLOTAPI int plotChartSetDrawCurveLastIndex (CurveChart* curvechart, int curven);
/***
* Get curve reference to last draw curve.
* @return Last curve index in curvechart. 
*/
PLOTAPI int plotChartGetDrawCurveLastIndex (CurveChart* curvechart);
/***
* Search for memo by id. Try to find in all curves associated to plot.
* @param id Memo id.
* @return First occurence of memo id.
*/
PLOTAPI PlotMemo* plotChartSearchMemo (CurveChart* curvechart, int id);

/*************
* BARCHART API
*******/
PLOTAPI BarChart* plotCreateBarChart (Plot* plot);
PLOTAPI void plotBarSetShadow (BarChart* b, int dx, int dy);
PLOTAPI void plotBarGetShadow (BarChart* b, int* dx, int* dy);
PLOTAPI void plotBarSetCategoryCount (BarChart* b, int nbars);
PLOTAPI int plotBarGetCategoryCount (BarChart* b);
PLOTAPI bool plotBarSetCategoryLabel (BarChart* b, int bar, const char* label);
PLOTAPI const char* plotBarGetCategoryLabel (BarChart* b, int bar);
PLOTAPI BarSeries* plotBarAddSeries (BarChart* b);
PLOTAPI BarSeries* plotBarGetSeries (BarChart* b, int series);
PLOTAPI bool plotBarRemoveSeries (BarChart* b, BarSeries* bseries);
PLOTAPI void plotBarDestroySeries (BarChart* b);
PLOTAPI int plotBarGetSeriesCount (BarChart* b);
PLOTAPI void plotBarSetBarLimit (BarChart* b, int size);
PLOTAPI int plotBarGetBarLimit (BarChart* b);

/*************
* BARSERIES API
*******/
PLOTAPI bool plotBarSeriesSetName (BarSeries* bseries, const char* name);
PLOTAPI const char* plotBarSeriesGetName (BarSeries* bseries);
PLOTAPI void plotBarSeriesSetValue (BarSeries* bseries, int bar, double value);
PLOTAPI double plotBarSeriesGetValue (BarSeries* bseries, int bar);
PLOTAPI void plotBarSeriesSetLineColor (BarSeries* bseries, PlotColor color);
PLOTAPI PlotColor plotBarSeriesGetLineColor (BarSeries* bseries);
PLOTAPI void plotBarSeriesSetLine (BarSeries* bseries, PlotLine line);
PLOTAPI PlotLine plotBarSeriesGetLine (BarSeries* bseries);
PLOTAPI void plotBarSeriesSetAreaColor (BarSeries* bseries, PlotColor color);
PLOTAPI PlotColor plotBarSeriesGetAreaColor (BarSeries* bseries);
PLOTAPI void plotBarSeriesSetAreaColorNegative (BarSeries* bseries, PlotColor color);
PLOTAPI PlotColor plotBarSeriesGetAreaColorNegative (BarSeries* bseries);

/*************
* HISTOGRAM CHART
*******/
PLOTAPI HistogramChart* plotCreateHistogramChart (Plot* plot);//, axisx_type -> INTERVAL | MEDIA
PLOTAPI void plotHistogramSetShadow (HistogramChart* h, int dx, int dy);
PLOTAPI void plotHistogramGetShadow (HistogramChart* h, int* dx, int* dy);
PLOTAPI BarSeries* plotHistogramAddSeries (HistogramChart* h);
PLOTAPI BarSeries* plotHistogramGetSeries (HistogramChart* h, int series);
PLOTAPI bool plotHistogramRemoveSeries (HistogramChart* h, BarSeries* series);
PLOTAPI void plotHistogramSetClasses (HistogramChart* h, 
                                      double min, double max, int intervals);
PLOTAPI void plotHistogramSetClassIntervals (HistogramChart* h, int intervals);
PLOTAPI int plotHistogramGetClassIntervals (HistogramChart* h);
PLOTAPI void plotHistogramSetClass (HistogramChart* h, 
                                    int iclass, 
                                    double istart, 
                                    double iend);
PLOTAPI int plotHistogramGetSeriesCount (HistogramChart* h);
PLOTAPI void plotHistogramSetBarLimit (HistogramChart* h, int size);
PLOTAPI int plotHistogramGetBarLimit (HistogramChart* h);

/***
* Move ponto da curva desenhada para outra posição somente no gráfico, 
* sem modificar a curva original, 
* e usando XOR sobre um canvas CD ativado anteriormente 
* à chamada de plotChartMoveCurvePoint.
* Se xr_old ou yr_old for PLOT_NAN_INT, não redesenha com XOR sobre esse
* ponto. O mesmo vale para xr_new e yr_new.
* @param curven Índice da curva (a partir de 1).
* @param xr_new Nova posição x, em raster, do ponto.
* @param yr_new Nova posição y, em raster, do ponto.
* @param xr_old Posição anterior x, em raster, do ponto.
* @param yr_old Posição anterior y, em raster, do ponto.
*/
PLOTAPI void plotChartMoveCurvePoint (Plot* plot, CurveChart* curvechart, 
                                      int curven, int pointn, 
                                      int xr_new, int yr_new, 
                                      int xr_old, int yr_old);
/***
* @function SetRecalculate Set recalculate flag to entity.
* @param plot Plot* Plot reference.
* @param intEntities int Plot predefined entity.
*/
PLOTAPI void plotSetRecalculate (Plot* plot, PlotEntity e);
/***
* @function GetRecalculate Return true if any recalc flag is set.
* @param plot Plot* Plot reference.
* @return int 1 if has to recalc or 0 otherwise. 
*/
PLOTAPI int plotGetRecalculate(Plot* plot);
/***
* @function Recalculate Brings up to date the graph calculations
* and cleans recalc flag. Does not call 
* the redraw function automatically. It is
* necessary active canvas.
* @param plot Plot* Plot handle.
*/
DS_DEPRECATED PLOTAPI void plotRecalculate(Plot* plot);
/*************
* @function plotRedraw Call (re)draw from plot instance. Every time
* that the plot is redraw, calculations are
* automatically remade according to the entity 
* flags.
*******/
PLOTAPI void plotRedraw(Plot* plot);

PLOTAPI int plotSetPlotTitleText(Plot* plot, const char* str);
/*************
* @function plotGetPlotTitleText Get title text reference in plot instance.
* @param plot Plot* Plot instance. 
* @return str const char* Subtitle text reference.
*******/
PLOTAPI const char* plotGetPlotTitleText(Plot* plot);
/*************
* @function plotSetPlotSubtitleText Set subtitle text in plot instance.
* @param plot Plot* Plot instance. 
* @param str const char* Subtitle text.
* @return int 1 if success or 0 otherwise.
*******/
PLOTAPI int plotSetPlotSubtitleText(Plot* plot, const char* str);
/*************
* @function plotGetPlotSubtitleText Get subtitle text reference in plot instance.
* @param plot Plot* Plot instance. 
* @return str const char* Subtitle text reference.
*******/
PLOTAPI const char* plotGetPlotSubtitleText(Plot* plot);
/*************
* @function plotSetStyle Set plot style sheet item. This function
* can be called to set any number item on 
* style sheet, e.g.: border size, margin,
* gap, or any enumered item, e.g.: PlotAlign, 
* PlotLineStyle, PlotTextDirect,
* PlotLineStyle or PlotDisplay opitions.
* @param plot Plot* Plot reference.
* @param pet PlotEntity Predefined plot entity in PlotEntity.
* @param psi PlotStyleItem Predefined plot style item. 
* @param intValue int Style sheet number item value.
* @param* idxAux int Opitional parameter. Auxiliar index value.
* @return int Old style sheet number item value.
*******/
PLOTAPI int plotSetStyle(Plot* plot, PlotEntity pet, PlotStyleItem psi, int intVal, int idxAux = 0);
/*************
* @function plotSetStyle Set plot style sheet item.
* @param plot Plot* Plot reference.
* @param pet PlotEntity Predefined plot entity in PlotEntity.
* @param psi PlotStyleItem Predefined plot style item.
* @param pcl PlotColor Style sheet color item value. 
* @param* idxAux int Opitional parameter. Auxiliar index value.
* @return PlotColor Old style sheet color item value.
*******/
PLOTAPI PlotColor plotSetStyle(Plot* plot, PlotEntity pet, PlotStyleItem psi, PlotColor pcl, int idxAux = 0);
/*************
* @function plotSetStyle Set plot style sheet item.
* @param plot Plot* Plot reference.
* @param pet PlotEntity Predefined plot entity in PlotEntity.
* @param psi PlotStyleItem Predefined plot style item.
* @param pft PlotFont Style sheet font item value. 
* @param* idxAux int Opitional parameter. Auxiliar index value.
* @return PlotFont Old style sheet font item value.
*******/
PLOTAPI PlotFont plotSetStyle(Plot* plot, PlotEntity pet, PlotStyleItem psi, PlotFont pft, int idxAux = 0);

PLOTAPI void plotSetBgImage (Plot* plot, PlotEntity entity, const char* image, int i = 0);
PLOTAPI const char* plotGetBgImage (Plot* plot, PlotEntity entity, int i = 0);
/*************
* @function plotGetStyleValue Get plot style sheet item. This function
* can be called to get any number item on 
* style sheet, e.g.: border size, margin,
* gap, or any enumered item, e.g.: PlotAlign, 
* PlotLineStyle, PlotTextDirect or 
* PlotDisplay opitions.
* @param plot Plot* Plot reference.
* @param pet PlotEntity Predefined plot entity in PlotEntity.
* @param psi PlotStyleItem Predefined plot style item.
* @return int Style sheet number item value.
*******/
PLOTAPI int plotGetStyleValue(Plot* plot, PlotEntity pet, PlotStyleItem psi, int idxAux = 0);
/*************
* @function plotGetStyleColor Get plot style sheet item.
* @param plot Plot* Plot reference.
* @param pet PlotEntity Predefined plot entity in PlotEntity.
* @param psi PlotStyleItem Predefined plot style item.
* @return PlotColor Style sheet color item value. 
*******/
PLOTAPI PlotColor plotGetStyleColor(Plot* plot, PlotEntity pet, PlotStyleItem psi, int idxAux = 0);
/*************
* @function plotGetStyleFont Get plot style sheet item.
* @param plot Plot* Plot reference.
* @param pet PlotEntity Predefined plot entity in PlotEntity.
* @param psi PlotStyleItem Predefined plot style item.
* @return PlotFont Style sheet font item value.
*******/
PLOTAPI PlotFont plotGetStyleFont(Plot* plot, PlotEntity pet, PlotStyleItem psi, int idxAux = 0);
/*************
* @function plotSetAlpha Set alpha value to all plot object. This value
* will be add to all color values into plot.
* @param plot Plot* Plot reference.
* @param uchAlpha uchar Alpha value.
*******/
PLOTAPI void plotSetAlpha(Plot* plot, unsigned char uchAlpha);
/*************
* @function plotEnableAlpha Enable alpha values set to all elements 
* into plot.
* @param plot Plot* Plot handle.
* @param intFlag int 0(false) to disable or 1(true) to enable.
*******/
PLOTAPI void plotEnableAlpha(Plot * plot, int intFlag);
/*************
* @function plotSetFontTransparency Enable text alpha. The alpha value 
* is set for each plot internal object.
* @param plot Plot* Plot reference.
* @param flag int 0 - false or 1 - true.
*******/
PLOTAPI void plotSetFontTransparency(Plot* plot, int intFlag);
PLOTAPI void plotSetSize (Plot* plot, int w, int h);
PLOTAPI void plotGetSize (Plot* plot, int* w, int* h);
/*************
* @function plotEnableSmooth Enable smooth to all plot.
* @param plot Plot* Plot reference.
* @param intFlag int 0(false) to disable or 1(true) to enable.
* @deprecated Opition removed.
*******/
DS_DEPRECATED PLOTAPI void plotEnableSmooth(Plot * plot, int intFlag);
/*************
* @function plotSetShowOutterBorder Set plot canvas outter border.
* @param plot Plot* Plot reference.
* @param intSize int Outter border size.
* @return int Old outter border size.
* @deprecated Change to plotSetStyle(plot, PLOT_BOX_PLOT, PLOT_SS_BORDER, intSize)
*******/
DS_DEPRECATED PLOTAPI int plotSetShowOutterBorder(Plot* plot, int intSize);
/*************
* @function plotGetOutterBorder Get plot canvas outter border.
* @param plot Plot* Plot reference.
* @return int Outter border size.
* @deprecated Change to plotGetStyleValue(plot, PLOT_BOX_PLOT, PLOT_SS_BORDER)
*******/
DS_DEPRECATED PLOTAPI int plotGetOutterBorder(Plot* plot);
/*************
* @function plotSetOutterBorderWidth 
* @see SetShowOutterBorder
* @deprecated Change to plotSetStyleValue(plot, PLOT_BOX_PLOT, PLOT_SS_BORDER, intWidth)
*******/
DS_DEPRECATED PLOTAPI int plotSetOutterBorderWidth(Plot* plot, int intWidth);
/*************
* @function plotSetBorderColor Set border to plot outter border.
* @param plot Plot* Plot reference.
* @param pcl PlotColor Border color.
* @deprecated Change to plotSetStyle(plot, PLOT_BOX_PLOT, PLOT_SS_CLR_BORDER, pcl)
*******/
DS_DEPRECATED PLOTAPI PlotColor plotSetBorderColor(Plot* plot, PlotColor pcl);
/*************
* @function plotSetBackground Set background color to plot box.
* @param plot Plot* Plot reference.
* @param pcl PlotColor Backround color.
* @deprecated Change to plotSetStyle(plot, PLOT_BOX_PLOT, PLOT_SS_CLR_BG, pcl)
*******/
DS_DEPRECATED PLOTAPI PlotColor plotSetBackground(Plot* plot, PlotColor pcl);
/*************
* @function plotGetBackground Get background plot box color.
* @param plot Plot* Plot reference.
* @return PlotColor Background color.
* @deprecated Change to plotGetStyleColor(plot, PLOT_BOX_PLOT, PLOT_SS_CLR_BG)
*******/
DS_DEPRECATED PLOTAPI PlotColor plotGetBackground(Plot* plot);
/*************
* @function plotSetShowTitle Set plot title display opition.
* @param plot Plot* Plot reference.
* @param intFlag int 0/false - to hide, 1/true - to show title. 
* @return int Old flag value.
* @deprecated Change to plotSetStyle(plot, PLOT_TITLE, PLOT_SS_DISPLAY, intFlag)
*******/
DS_DEPRECATED PLOTAPI int plotSetShowTitle(Plot* plot, int intFlag);
/*************
* @function plotGetShowTitle Get show title flag value.
* @param plot Plot* Plot reference.
* @return int Flag value.  
* @deprecated Change to plotGetStyleValue(plot, PLOT_TITLE, PLOT_SS_DISPLAY)
*******/
DS_DEPRECATED PLOTAPI int plotGetShowTitle(Plot* plot);
/*************
* @function plotSetPlotTitleFont Change plot title font.
* @param plot Plot* Plot reference. 
* @param pft PlotFont Title font.
* @return PlotFont Old title font.
* @deprecated Change to plotSetStyle(plot, PLOT_TITLE, PLOT_SS_FONT, pft)
*******/
DS_DEPRECATED PLOTAPI PlotFont plotSetPlotTitleFont(Plot* plot, PlotFont pft);
/*************
* @function plotGetPlotTitleFont Get current title font.
* @param plot Plot* Plot reference.
* @return PlotFont Title font.
* @deprecated Change to plotGetStyleFont(plot, PLOT_TITLE, PLOT_SS_FONT)
*******/
DS_DEPRECATED PLOTAPI PlotFont plotGetPlotTitleFont(Plot* plot);
/*************
* @function plotSetPlotTitleColor Change plot title color.
* @param plot Plot* Plot referece.
* @param pcl PlotColor New title color.
* @return PlotColor Old title color. 
* @deprecated Change to plotSetStyle(plot, PLOT_TITLE, PLOT_SS_CLR_FONT, pcl)
*******/
DS_DEPRECATED PLOTAPI PlotColor plotSetPlotTitleColor(Plot* plot, PlotColor pcl);
/*************
* @function plotGetPlotTitleColor Get current title color.
* @param plot Plot* Plot reference.
* @return PlotColor Title color. 
* @deprecated Change to plotGetStyleColor(plot, PLOT_TITLE, PLOT_SS_CLR_FONT)
*******/
PLOTAPI PlotColor plotGetPlotTitleColor(Plot* plot);
/*************
* @function plotSetPlotSubtitleFont Change plot subtitle font.
* @param plot Plot* Plot reference.
* @param pft PlotFont New subtitle font.
* @return PlotFont Old subtitle font. 
* @deprecated Change to plotSetStyle(plot, PLOT_TITLE, PLOT_SS_FONT, pft)
*******/
DS_DEPRECATED PLOTAPI PlotFont plotSetPlotSubtitleFont(Plot* plot, PlotFont pft);
/*************
* @function plotGetPlotSubtitleFont Get current plot subtitle font style.
* @param plot Plot* Plot reference.
* @return PlotFont Subtitle font.
* @deprecated Change to plotGetStyleFont(plot, PLOT_SUBTITLE, PLOT_SS_FONT)
*******/
DS_DEPRECATED PLOTAPI PlotFont plotGetPlotSubtitleFont(Plot* plot);
/*************
* @function plotSetPlotSubtitleColor Change subtitle color.
* @param plot Plot* Plot reference.
* @param pcl PlotColor New subtitle color.
* @return PlotColor Old subtitle color. 
* @deprecated Change to plotSetStyle(plot, PLOT_SUBTITLE, PLOT_SS_CLR_FONT, pcl)
*******/
DS_DEPRECATED PLOTAPI PlotColor plotSetPlotSubtitleColor(Plot* plot, PlotColor pcl);
/*************
* @function plotGetPlotSubtitleColor Get current subtitle font color.
* @param plot Plot* Plot reference.
* @return PlotColor Subtitle color.
* @deprecated Change to plotGetStyleColor(plot, PLOT_SUBTITLE, PLOT_SS_CLR_FONT)
*******/
DS_DEPRECATED PLOTAPI PlotColor plotGetPlotSubtitleColor(Plot* plot);
/*************
* @function plotSetShowSubtitle Set show or hide subtitle.
* @param plot Plot* Plot reference.
* @param intFlag int 1/true - to show or 0/false to hide. 
* @return int Old flag value. 
* @deprecated Change to plotSetStyle(plot, PLOT_SUBTITLE, PLOT_SS_DISPLAY, intFlag)
*******/
DS_DEPRECATED PLOTAPI int plotSetShowSubtitle(Plot* plot, int intFlag);
/*************
* @function plotGetShowTitle Get title flag value.
* @param plot Plot* Plot reference.
* @return int Title flag value. 
* @deprecated Change to plotGetStyleValue(plot, PLOT_SUBTITLE, PLOT_SS_DISPLAY)
*******/
DS_DEPRECATED PLOTAPI int plotGetShowSubtitle(Plot* plot);
PLOTAPI bool plotSetImageAfterTitle(Plot* plot, const char* strImage);
PLOTAPI bool plotSetImageBeforeTitle(Plot* plot, const char* strImage);
PLOTAPI bool plotSetBgImageTitle(Plot* plot, const char* strImage, PlotBgType type);
PLOTAPI bool plotSetBgImagePlot(Plot* plot, const char* strImage, PlotBgType type);

/*************
* AXIS API - TODO: trocar assinaturas para receber axis em vez de chart + axisid
*******/
PLOTAPI bool plotAxisGetShow (PlotAxis* axis);
PLOTAPI int plotAxisSetShowId (Chart* chart, PlotAxisId axisid, int iFlag);
PLOTAPI int plotAxisGetShowId (Chart* chart, PlotAxisId axisid);
/***
* Define a distância entre duas linhas da grade (grid) de um eixo, 
* em número de marcas menores do eixo. Só tem efeito para grid do tipo 
* REFINED.
* @see PlotGridType
*/ 
//PLOTAPI int plotAxisSetGridValue (Chart* chart, PlotAxisId axisid, int value);
//PLOTAPI int plotAxisGetGridValue (Chart* chart, PlotAxisId axisid);
/***
* Set axis grid type.
* @param chart Object reference.
* @param intAxisId Axis id.
* @param pgt Predefined grid type(@see PlotGridType).   
* @return Old axis grid type value.
*/
PLOTAPI PlotGridType plotAxisSetGridType (Chart* chart, PlotAxisId axisid, PlotGridType type);
PLOTAPI PlotGridType plotAxisGetGridType (Chart* chart, PlotAxisId pai);
/***
* Altera valor do intervalo entre as marcas menores de um eixo.
*/
PLOTAPI double plotAxisSetInterval (Chart* chart, PlotAxisId axisid, double interval);
PLOTAPI double plotAxisGetInterval (Chart* chart, PlotAxisId axisid);
/***
* Altera número de marcas menores de um eixo.
*/ 
PLOTAPI int plotAxisSetNumberOfMarks (Chart* chart, PlotAxisId axisid, int n);
PLOTAPI int plotAxisGetNumberOfMarks (Chart* chart, PlotAxisId axisid);
/***
* Altera o tipo de escala de um eixo.
* Warning: O eixo x é o único que aceita escala de datas.
* @see PlotAxisType
*/
PLOTAPI PlotAxisType plotAxisSetType (Chart* chart, PlotAxisId axisid, PlotAxisType type);
PLOTAPI PlotAxisType plotAxisGetType (Chart* chart, PlotAxisId axisid);
PLOTAPI bool plotAxisSetLabelPattern (Chart* chart, PlotAxisId axisid, const char* labelpattern);
PLOTAPI const char* plotAxisGetLabelPattern (Chart* chart, PlotAxisId axisid);
PLOTAPI int plotAxisSetTitle (Chart* chart, PlotAxisId axisid, const char *text);
PLOTAPI const char* plotAxisGetTitle (Chart* chart, PlotAxisId axisid);
PLOTAPI int plotAxisSetAutoscaleFlag (Chart* chart, PlotAxisId axisid, int autoscale_flag);
PLOTAPI int plotAxisGetAutoscaleFlag (Chart* chart, PlotAxisId axisid);
/***
* Set an axis to draw identity curve.
* @param chart Object reference.
* @param axisid Axis id.  
* @param flag 1 - to draw or 0.
*/
PLOTAPI void plotAxisSetDrawIdentityCurve (Chart* chart, PlotAxisId axisid, int flag);
PLOTAPI void plotAxisSetZero (Chart* chart, PlotAxisId axisid, double origen);
PLOTAPI double plotAxisGetZero (Chart* chart, PlotAxisId axisid);
/***
* Altera o valor mínimo do eixo, utilizado quando a escala automática
* está desligada.
*/
PLOTAPI double plotAxisSetMinValue (Chart* chart, PlotAxisId axisid, double min);
PLOTAPI double plotAxisGetMinValue (Chart* chart, PlotAxisId axisid);
/***
* Altera o valor máximo do eixo, utilizado quando a escala automática
* está desligada.
*/
PLOTAPI double plotAxisSetMaxValue (Chart* chart, PlotAxisId axisid, double max);
PLOTAPI double plotAxisGetMaxValue (Chart* chart, PlotAxisId axisid);
/***
* Altera a data mínima de um eixo de datas, 
* utilizado quando a escala automática está desligada.
*/
PLOTAPI PlotDate plotAxisSetMinDate (Chart* chart, PlotAxisId axisid, PlotDate min);
PLOTAPI PlotDate plotAxisGetMinDate (Chart* chart, PlotAxisId axisid);
/***
* Altera a data máxima de um eixo de datas, 
* utilizado quando a escala automática está desligada.
*/
PLOTAPI PlotDate plotAxisSetMaxDate (Chart* chart, PlotAxisId axisid, PlotDate max);
PLOTAPI PlotDate plotAxisGetMaxDate (Chart* chart, PlotAxisId axisid);
PLOTAPI void plotAxisSetMinRange (Chart* chart, PlotAxisId axisid, double v0, double v1);
PLOTAPI void plotAxisGetMinRange (Chart* chart, PlotAxisId axisid, double* v0, double* v1);
PLOTAPI void plotAxisSetMaxRange (Chart* chart, PlotAxisId axisid, double v0, double v1);
PLOTAPI void plotAxisGetMaxRange (Chart* chart, PlotAxisId axisid, double* v0, double* v1);
PLOTAPI void plotAxisGetComputedRange (Chart* chart, PlotAxisId axisid, double *v0, double *v1);
PLOTAPI void plotAxisGetDataLimits (CurveChart* curvechart, PlotAxisId axisid, double* min, double* max);
PLOTAPI void plotAxisGetLimits (Plot* plot, CurveChart* curvechart, PlotAxisId axisid, double* min, double* max);
PLOTAPI void plotAxisGetExpo (Chart* chart, PlotAxisId axisid, int* exp);
/***
* Set axis background color (@old plotSetAxisColor|plotSetAxisBgColor)
* @param bgcolor New background color.
* @return Old axis background color.
*/
PLOTAPI PlotColor plotAxisSetBgColor (Chart* chart, PlotAxisId axisid, PlotColor bgcolor);
/***
* Get current axis background color (@old plotGetAxisColor|plotGetAxisBgColor).
* @return Current axis background color.
*/
PLOTAPI PlotColor plotAxisGetBgColor (Chart* chart, PlotAxisId axisid);
PLOTAPI bool plotAxisSetBgImage (Chart* chart, PlotAxisId axisid, const char* image, PlotBgType type);
/***
* Set axis line, axis marks, axis id and axis expoent color.
* @param color New elems color.
* @return Old axis elems color.
*/
PLOTAPI PlotColor plotAxisSetElemsColor (Chart* chart, PlotAxisId axisid, PlotColor color);
PLOTAPI PlotColor plotAxisSetRulerColor (Chart* chart, PlotAxisId axisid, PlotColor color);
/***
* Get axis line, axis mark, axis id and axis expoent color.
* @return Current axis elems color.
*/
PLOTAPI PlotColor plotAxisGetElemsColor (Chart* chart, PlotAxisId axisid);
PLOTAPI PlotColor plotAxisGetRulerColor (Chart* chart, PlotAxisId axisid);
/***
* Set axis expoent and axis id font.
* @param font New axis title font.
* @return Old axis elems font.
*/
PLOTAPI PlotFont plotAxisSetElemsFont (Chart* chart, PlotAxisId axisid, PlotFont font);
/***
* Get axis expoent and axis id font.
* @param intAxisId int Predefined plot axis id.  
* @return pft PlotFont Current axis title font.
*/
PLOTAPI PlotFont plotAxisGetElemsFont (Chart* chart, PlotAxisId axisid);
/***
* Set axis title font.
* @param font New axis title font.
* @return Old axis title font.
*/
PLOTAPI PlotFont plotAxisSetTitleFont (Chart* chart, PlotAxisId axisid, PlotFont font);
/***
* Get axis title font
* @return Current axis title font
*/
PLOTAPI PlotFont plotAxisGetTitleFont (Chart* chart, PlotAxisId axisid);
/***
* Set axis title font color.
* @param color New axis title font color.
* @return Old axis font title color.
*/
PLOTAPI PlotColor plotAxisSetTitleColor (Chart* chart, PlotAxisId axisid, PlotColor color);
/***
* Get axis font title color.
* @return Current axis title font color.
*/
PLOTAPI PlotColor plotAxisGetTitleColor (Chart* chart, PlotAxisId axisid);
/***
* Set axis labels font.
* @param font New axis labels font.
* @return Old axis labels font.
*/
PLOTAPI PlotFont plotAxisSetValueFont (Chart* chart, PlotAxisId axisid, PlotFont font);
/***
* Get axis labels font.
* @return Current axis label font.
*/
PLOTAPI PlotFont plotAxisGetValueFont (Chart* chart, PlotAxisId axisid);
/***
* Set axis labels color.
* @param color New axis labels color.
* @return Old axis labels color.
*/
PLOTAPI PlotColor plotAxisSetValueColor (Chart* chart, PlotAxisId axisid, PlotColor color);
/***
* Get axis labels color.
* @return Current axis label color.
*******/
PLOTAPI PlotColor plotAxisGetValueColor (Chart* chart, PlotAxisId axisid);
/***
* @param chart Object reference.
* @param axisid Axis id.
* @param flag int 1 to show.
* @return Old flag value.    
*/
PLOTAPI int plotAxisSetRefinedGridColorFlag (Chart* chart, PlotAxisId axisid, int flag);
/***
* @param chart Object reference.
* @param axisid Axis id.
* @return Current flag value.    
*/
PLOTAPI int plotAxisGetRefinedGridColorFlag (Chart* chart, PlotAxisId axisid);
/***
* Convert a raster position to an axis coordinate point values. 
* The axis values always have an inaccuracy.
* @param chart Object reference.
* @param aixsid Y axis id predefined on PlotAxisId. 
* @param intRX int Raster x position.
* @param intRY int Raster y position.
* @param* dblX double Reference to return the X axis coordinate.
* @param* dblY double Reference to return the Y axis coordinate.
*/
PLOTAPI int plotUnmapPoint (Plot* plot, Chart* chart, PlotAxisId axisid,
                            int intRX, int intRY,
                            double* dblX, double* dblY);
/***
* @function plotMapPoint Convert an axis coordinate point value to
* a raster position. The axis values 
* always have an inaccuracy, plotMapPoint(plotUnmapPoint)
* @param plot Plot* Plot reference.
* @param intYAxisId int Y axis id predefined on PlotAxisId. 
* @param* dblX double X axis coordinate.
* @param* dblY double Y axis coordinate.
* @param intRX int Reference to return the raster x position.
* @param intRY int Reference to return the raster y position.
*/
PLOTAPI int plotMapPoint (Plot* plot, Chart* chart, 
                          PlotAxisId intYAxisId, 
                          double dblX, double dblY,
                          int* intRX, int* intRY);
PLOTAPI int plotMapValue (Plot* plot, Chart* chart, 
                          PlotAxisId axisid, 
                          double val, int* raster_val);
/***
* @param intX int X raster position.
* @param intY int Y raster position. 
* @return int 1 if success or 0 otherwise.
*/
PLOTAPI int plotSetPlotTipTool (Plot* plot, const char* str, int x, int y);
/***
* @function plotGetPlotTipToolText Get tip tool text reference in plot instance.
* @param plot Plot* Plot instance. 
* @return str const char* Tip tool text reference.
*/
PLOTAPI const char* plotGetPlotTipToolText (Plot* plot);
/***
* @function plotTipToolHide Set tip tool to hide.
* @param plot Plot* Plot instance. 
*/
PLOTAPI void plotTipToolHide (Plot* plot);

/*
 * Get reach entity from pick processing.
 * index: if 0 return entity id from last selected entity, 
 *  otherwise return entity id from specific index in selected list.
 */
PLOTAPI int plotGetReachEntity (Plot* plot, int index = 0);
PLOTAPI int plotGetReachEntityChartId  (Plot* plot, int index = 0);
PLOTAPI int plotGetReachEntityIndex (Plot* plot, int index = 0);
PLOTAPI int plotGetReachEntityParent (Plot* plot, int index = 0);

/*************
* @function plotSetPickTolerance Set pick size tolerance.
* @param plot Plot* Plot reference.
* @param intW int Pick width.
* @param intH int Pick height.   
*******/
PLOTAPI void plotSetPickTolerance(Plot* plot, int intW, int intH);
/*************
* @function plotGetPickTolerance Get pick size.
* @param plot Plot* Plot reference.
* @param* intW int* Reference to return pick width value.
* @param* intH int* Reference to return pick height value.
*******/
PLOTAPI void plotGetPickTolerance(Plot* plot, int* intW, int* intH);
/*************
* @function plotEventProcess Process plot predefined events.
* @param plot Plot* Plot reference.
* @param intX int X raster position.
* @param intY int Y raster position.
* @param pev PlotEvent Predefined event.
* @param intOp int Special parameter, can be a button value
* when pev is any button event or mouse motion,
* or the velocity and direction when pev 
* is PLOT_E_MWHEEL.
* @return int Entities affectd by event process.
*******/
PLOTAPI int plotEventProcess(Plot* plot, int intX, int intY, PlotEvent pev, int intOp);
/*************
* @function plotIsInCurveArea Indicate if point is into curve area.
* @param plot Plot* Plot reference. 
* @param intRX int Raster x position.
* @param intRY int Raster y position.
* @return int True if raster point is in curve area. 
*******/
PLOTAPI int plotIsInCurveArea(Plot* plot, int intRX, int intRY);
/*************
* @function plotPickCurvePoint Try to pick a point in any curve on plot.
* @param plot Plot* Plot reference. 
* @param intRX int Raster x position.
* @param intRY int Raster y position. 
* @param* dblX double* Reference to return the point x coordinate.
* @param* dblY double* Reference to return the point y coordinate.
* @param* intPos int* Reference to return the point index on curve.
* @return int Curve index or 0 if can not pick any curve point.
*******/
PLOTAPI int plotPickCurvePoint(Plot* plot, int intRX, int intRY, 
                                double* dblX, double* dblY, int* intPos);
/*************
* @function plotPickCurveSegment Try to pick any curve segment on plot.
* @param plot Plot* Plot reference. 
* @param intRX int Raster x position.
* @param intRY int Raster y position. 
* @param* dblX double* Reference to return the point x coordinate.
* @param* dblY double* Reference to return the point y coordinate.
* @param* intPos int* Reference to return the first segment point 
* index on curve.
* @return int Curve index or 0 if can not pick any curve point.
*******/
PLOTAPI int plotPickCurveSegment(Plot* plot, int intRX, int intRY, 
                                  double* dblX, double* dblY, int* intPos);
/*************
* @function plotPickCurveLabel Try to pick a curve legend.
* @param plot Plot* Plot reference. 
* @param intRX int Raster x position.
* @param intRY int Raster y position. 
* @return int Curve index or 0 if can not pick any curve legend.
*******/
PLOTAPI int plotPickCurveLabel(Plot* plot, int intRX, int intRY);
/*************
* plotZoomIn Make zoom on point focus.
* @param plot Plot* Plot reference. 
* @param int intRXCenter Raster x zoom focus.
* @param int intRYCenter Raster y zoom focus.
*******/
PLOTAPI void plotZoomIn (Plot* plot, int intRXCenter, int intRYCenter);
PLOTAPI bool plotCopyImage(Plot* plot, int width = -1, int height = -1);
PLOTAPI bool plotSaveImage(Plot* plot, 
                           const char* label, const char* filename, const char* format,
                           int width = -1, int height = -1);
PLOTAPI bool plotPrintImage(Plot* plot, int intWidth = -1, int intHeight = -1);
/*******************************************************************************
* @endof block API Functions
*******************************************************************************/

/******************************************************************************
* @block            STRIP API
******************************************************************************/
// Create a new strip set
PLOTAPI PlotStripSet* plotStripCreateSet ();

//Defines crossed intervals
PLOTAPI void plotStripAddCrossedIntervals (PlotStripSet* set, 
                                           int num_int, 
                                           const int* cells_ids,
                                           const float* tmin, 
                                           const float* tmax);

// Add a new strip to a strip set
// x: absciss coordinate
// n_values: number of values
// value: values associated to each interval (value of property)
PLOTAPI void plotStripAddValues (PlotStripSet* set, 
                                 double x, 
                                 int n_values, 
                                 const float* values);

// set marks positions
PLOTAPI void plotStripSetMarks (PlotStripSet* set, 
                                int marks_count, 
                                const float* marks_pos);

// Set the width of strips
// width: value in raster coordinate
PLOTAPI void plotStripSetWidth (PlotStripSet* set, float width);

// Set the height of strips
// height: value in normalized [0,1] coordinate
PLOTAPI void plotStripSetHeight (PlotStripSet* set, float height);

// Set strip border color
PLOTAPI void plotStripSetBorderColor (PlotStripSet* set, 
                                      float r, 
                                      float g, 
                                      float b);

// Set mark radius size
// radius: value in raster coordinate
PLOTAPI void plotStripSetMarkSize (PlotStripSet* set, float radius);

// Set strip mark color - for all marks.
//Must be called after plotStripSetMarks
PLOTAPI void plotStripSetMarkColor (PlotStripSet* set, 
                                    float r, 
                                    float g, 
                                    float b);

//Set strip mark highlight color.
//Must be called after plotStripSetMarks
PLOTAPI void plotStripSetMarkHighlight (PlotStripSet* set, 
                                        int id, 
                                        float r, 
                                        float g, 
                                        float b);

//Set strip mark visibility (default is true)
PLOTAPI void plotStripSetMarkVisibility (PlotStripSet* set,
                                         bool value);

// Attach strip set to a plot
PLOTAPI void plotStripAddSet (Plot* plot, PlotStripSet* set);

PLOTAPI PlotStripSet* plotStripGetSet (Plot* plot);

// Detach strip set from the plot
PLOTAPI void plotStripRemoveSet (Plot* plot);

/**
 * Create a Color Scale
 */
PLOTAPI PlotColorScale* plotCreateColorScale ();

/**
 * Attach color scale to a plot
 */
PLOTAPI void plotSetColorScale (Plot* plot, PlotColorScale* cs);

/**
 * Access to plot color scale.
 * @param plot plot instance.
 * @return reference to plot color scale.
 */
PLOTAPI PlotColorScale* plotGetColorScale (Plot* plot);

/**
 * Setup limits for color scale used when drawing stripsets.
 * @param cs reference to color scale.
 * @param min_value.
 * @param max_value.
 */
PLOTAPI void plotColorScaleSetLimits (PlotColorScale* cs,
                                      float min_value, 
                                      float max_value);

PLOTAPI void plotColorScaleSetTitle (PlotColorScale* cs, const char* title);
PLOTAPI bool plotColorScaleSetTitleFont (PlotColorScale* cs, PlotFont font);
PLOTAPI bool plotColorScaleSetValuesFont (PlotColorScale* cs, PlotFont font);
PLOTAPI void plotColorScaleSetBgColor (PlotColorScale* cs, PlotColor c);

/******************************************************************************
* @endof block            STRIP API
******************************************************************************/

//TODO: review it
PLOTAPI int plotStoreCustomMark(Plot* plot, const char * strTexFile, const char * strAlphaFile);
PLOTAPI int plotSetXVar(Plot *plot, int var);
PLOTAPI int plotGetXVar(Plot *plot);
PLOTAPI int plotSetXVarProp(Plot *plot, int prop);
PLOTAPI int plotGetXVarProp(Plot *plot);
/** I/O functions */
/**
 * Lê arquivo no formato (.plot).
 */
PLOTAPI int plotRead (const char* filename, Plot *plot);
/** 
 * Salva arquivo no formato (.plot).
 *
 * @warning Desatualizado!!!!! Algumas funções indisponíveis!!!
 */
PLOTAPI int plotWrite (const char* filename, Plot *plot);
/**
 * Exportação de gráfico.
 *
 * @param type Tipo da exportação.
 * @param data 
 * PLOT_ASCII: nome de arquivo.
 * PLOT_PS: String com os mesmos parâmetros usados
 * para a criação de um canvas para o driver PS no CD. O tipo
 * de papel fornecido pode ser PLOT_papel, além de CD_papel. As
 * duas formas são equivalentes.
 * @returns Se OK: 1. Senão: 0. 
 */ 
PLOTAPI int plotExport(PlotExportType type, const char* data, Plot *plot);
PLOTAPI const char* plotGetEntityString (PlotEntity e);
#ifdef _PLOT_FUNCTION
PLOTAPI int plotAddFunction(Plot *plot, PlotFunction *func);
/* 1-indexed.*/
PLOTAPI PlotFunction* plotGetFunction(Plot *plot, int i);
PLOTAPI int plotGetNumberOfFunctions(Plot *plot);
PLOTAPI int plotRemoveFunction(Plot *plot, int id);
PLOTAPI int plotRemoveAllFunctions(Plot *plot);
PLOTAPI PlotFunction* plotCreateFunction();
PLOTAPI void plotDestroyFunction(PlotFunction* f);
PLOTAPI PlotFunction* plotCreateLinearFunction(double a, double b);
PLOTAPI PlotFunction* plotCreateExpFunction(double a, double b);
PLOTAPI PlotFunction* plotCreateLogFunction(double a, double b);
PLOTAPI PlotFunction* plotCreatePowFunction(double a, double b);
PLOTAPI double plotFunctionGetY(PlotFunction* f, double x);
PLOTAPI double plotFunctionSetParam(PlotFunction *f, int id, double val);
PLOTAPI double plotFunctionGetParam(PlotFunction *f, int id);
PLOTAPI int plotFunctionSetNumberOfParams(PlotFunction *f, int n);
PLOTAPI int plotFunctionGetNumberOfParams(PlotFunction *f);
PLOTAPI void plotFunctionSetRange(PlotFunction *f, double v0, double v1);
PLOTAPI void plotFunctionGetRange(PlotFunction *f, double *v0, double *v1);
PLOTAPI int plotFunctionSetAutoscaleFlag(PlotFunction *f, int flag);
PLOTAPI int plotFunctionGetAutoscaleFlag(PlotFunction *f);
PLOTAPI int plotFunctionSetNumberOfSamples(PlotFunction *f, int n);
PLOTAPI int plotFunctionGetNumberOfSamples(PlotFunction *f);
PLOTAPI int plotFunctionSetLabel(PlotFunction* func, char *text);
PLOTAPI const char* plotFunctionGetLabel(PlotFunction* func);
PLOTAPI int plotFunctionSetShowLabel(PlotFunction* func, int flag);
PLOTAPI int plotFunctionGetShowLabel(PlotFunction* func);
PLOTAPI int plotFunctionSetAxisId(PlotFunction* func, PlotAxisId axisid);
PLOTAPI PlotAxisId plotFunctionGetAxisId(PlotFunction* func);
PLOTAPI PlotLine plotFunctionSetLine(PlotFunction* func, PlotLine line);
PLOTAPI PlotLine plotFunctionGetLine(PlotFunction* func);
PLOTAPI PlotColor plotFunctionSetColor(PlotFunction* func, PlotColor color);
PLOTAPI PlotColor plotFunctionGetColor(PlotFunction* func);
#endif
/**
 * Desenha um retângulo com linha pontilhada utilizando XOR. Útil para 
 * desenhar uma janela de Zoom.
 *
 * @param xr_min Posição x inicial do retângulo, em raster.
 * @param yr_min Posição y inicial do retângulo, em raster.
 * @param xr_max Posição x final do retângulo, em raster.
 * @param yr_max Posição y final do retângulo, em raster.
 */
PLOTAPI int plotDrawRect(Plot* plot, int xr_min, int yr_min, int xr_max, int yr_max);
/**
 * Desenha uma linha utilizando XOR. 
 */
PLOTAPI int plotDrawLine(Plot* plot, int x0_raster, int y0_raster, int x1_raster, int y1_raster);

/**
 * Old API (calls redirected to default chart 0).
 */
DS_DEPRECATED PLOTAPI void plotSetActive(Plot* plot, int intFuncs, bool bolActive);
DS_DEPRECATED PLOTAPI bool plotGetActive(Plot* plot, PlotFunc pfc);
DS_DEPRECATED PLOTAPI int plotAddCurve(Plot* plot, PlotCurve *crv);
DS_DEPRECATED PLOTAPI int plotRemoveCurve(Plot* plot, int idxCrv);
DS_DEPRECATED PLOTAPI int plotRemoveAllCurves(Plot* plot);
DS_DEPRECATED PLOTAPI PlotCurve* plotGetCurve(Plot* plot, int idxCrv);
DS_DEPRECATED PLOTAPI int plotGetNumberOfCurves(Plot* plot);
DS_DEPRECATED PLOTAPI void plotDestroyCurves(Plot* plot);
DS_DEPRECATED PLOTAPI PlotMemo* plotSearchMemo(Plot* plot, int id);
DS_DEPRECATED PLOTAPI PlotCurve* plotSetDrawCurveLast(Plot* plot, PlotCurve* crv);
DS_DEPRECATED PLOTAPI PlotCurve* plotGetDrawCurveLast(Plot* plot);
DS_DEPRECATED PLOTAPI int plotSetDrawCurveLastIndex(Plot* plot, int iCurve);
DS_DEPRECATED PLOTAPI int plotGetDrawCurveLastIndex(Plot* plot);
DS_DEPRECATED PLOTAPI int plotSetShowCurveAreaBorder(Plot* plot, int intFlag);
DS_DEPRECATED PLOTAPI int plotSetShowGridMarks(Plot* plot, int intFlag);
DS_DEPRECATED PLOTAPI int plotGetShowCurveAreaBorder(Plot* plot);
DS_DEPRECATED PLOTAPI int plotGetShowGridMarks(Plot* plot);
DS_DEPRECATED PLOTAPI int plotSetShowBorder(Plot* plot, int intSize);
DS_DEPRECATED PLOTAPI int plotGetShowBorder(Plot* plot);
DS_DEPRECATED PLOTAPI PlotColor plotSetGraphBgColor(Plot* plot, PlotColor pcl);
DS_DEPRECATED PLOTAPI PlotAxis* plotGetAxis (Plot* plot, PlotAxisId aid);
DS_DEPRECATED PLOTAPI int plotSetShowAxisLabel (Plot* plot, int intLFlag);
DS_DEPRECATED PLOTAPI int plotSetShowAxisId (Plot* plot, PlotAxisId iAxisId, int iFlag);
DS_DEPRECATED PLOTAPI int plotGetShowAxisId (Plot* plot, PlotAxisId iAxisId);
DS_DEPRECATED PLOTAPI int plotGetShowAxisLabel (Plot* plot);
DS_DEPRECATED PLOTAPI PlotFont plotSetLabelFont (Plot* plot, PlotFont pft);
DS_DEPRECATED PLOTAPI PlotFont plotGetLabelFont (Plot* plot); 
DS_DEPRECATED PLOTAPI int plotSetShowLabel (Plot* plot, int intFlag);
DS_DEPRECATED PLOTAPI int plotGetShowLabel (Plot* plot);
DS_DEPRECATED PLOTAPI PlotPosition plotSetLabelPos (Plot* plot, PlotPosition pos); 
DS_DEPRECATED PLOTAPI PlotPosition plotGetLabelPos(Plot* plot);
DS_DEPRECATED PLOTAPI PlotAlign plotSetLabelAlign(Plot *plot, PlotAlign pta);
DS_DEPRECATED PLOTAPI PlotAlign plotGetLabelAlign(Plot* plot);
DS_DEPRECATED PLOTAPI PlotColor plotSetAxisColor(Plot* plot, PlotAxisId pai, PlotColor pcl);
DS_DEPRECATED PLOTAPI PlotColor plotGetAxisColor(Plot* plot, PlotAxisId pai);
DS_DEPRECATED PLOTAPI PlotColor plotSetAxisElemsColor(Plot* plot, PlotAxisId pai, PlotColor pcl);
DS_DEPRECATED PLOTAPI PlotColor plotGetAxisElemsColor(Plot* plot, PlotAxisId pai);
DS_DEPRECATED PLOTAPI PlotColor plotSetAxisRulerColor(Plot* plot, PlotAxisId pai, PlotColor pcl);
DS_DEPRECATED PLOTAPI PlotColor plotGetAxisRulerColor(Plot* plot, PlotAxisId pai);
DS_DEPRECATED PLOTAPI PlotColor plotSetAxisGridColor(Plot* plot, PlotAxisId pai, PlotColor pcl);
DS_DEPRECATED PLOTAPI PlotColor plotGetAxisGridColor(Plot* plot, PlotAxisId pai);
DS_DEPRECATED PLOTAPI PlotFont plotSetAxisTitleFont(Plot* plot, PlotAxisId pai, PlotFont pft);
DS_DEPRECATED PLOTAPI PlotFont plotGetAxisTitleFont(Plot* plot, PlotAxisId pai);
DS_DEPRECATED PLOTAPI PlotColor plotSetAxisTitleColor(Plot* plot, PlotAxisId pai, PlotColor pcl);
DS_DEPRECATED PLOTAPI PlotColor plotGetAxisTitleColor(Plot* plot, PlotAxisId pai);
DS_DEPRECATED PLOTAPI PlotColor plotSetAxisBgColor(Plot* plot, PlotAxisId pai, PlotColor pcl);
DS_DEPRECATED PLOTAPI PlotColor plotGetAxisBgColor(Plot* plot, PlotAxisId pai);
DS_DEPRECATED PLOTAPI PlotColor plotSetAxisRefinedGridColor(Plot* plot, PlotAxisId pai, PlotColor pcl);
DS_DEPRECATED PLOTAPI PlotColor plotGetAxisRefinedGridColor(Plot* plot, PlotAxisId pai);
DS_DEPRECATED PLOTAPI void plotSetGridShadowColor(Plot* plot, PlotColor pcl);
DS_DEPRECATED PLOTAPI PlotColor plotGetGridShadowColor(Plot* plot);
DS_DEPRECATED PLOTAPI PlotFont plotSetAxisFont(Plot* plot, PlotAxisId pai, PlotFont pft);
DS_DEPRECATED PLOTAPI PlotFont plotGetAxisFont(Plot* plot, PlotAxisId pai);
DS_DEPRECATED PLOTAPI PlotFont plotSetAxisElemsFont(Plot* plot, PlotAxisId pai, PlotFont pft);
DS_DEPRECATED PLOTAPI PlotFont plotGetAxisElemsFont(Plot* plot, PlotAxisId pai);
DS_DEPRECATED PLOTAPI PlotFont plotSetAxisValueFont(Plot* plot, PlotAxisId pai, PlotFont pft);
DS_DEPRECATED PLOTAPI PlotFont plotGetAxisValueFont(Plot* plot, PlotAxisId pai);
DS_DEPRECATED PLOTAPI PlotColor plotSetAxisValueColor(Plot* plot, PlotAxisId pai, PlotColor pcl);
DS_DEPRECATED PLOTAPI PlotColor plotGetAxisValueColor(Plot* plot, PlotAxisId pai);
DS_DEPRECATED PLOTAPI PlotColor plotSetIdentityCurveColor(Plot* plot, PlotAxisId pai, PlotColor pcl);
DS_DEPRECATED PLOTAPI int plotSetAxisRefinedGridColorFlag(Plot* plot, PlotAxisId pai, int intFlag);
DS_DEPRECATED PLOTAPI int plotGetAxisRefinedGridColorFlag(Plot* plot, PlotAxisId pai);
DS_DEPRECATED PLOTAPI PlotGridType plotSetAxisGridType(Plot* plot, PlotAxisId axisid, PlotGridType type);
DS_DEPRECATED PLOTAPI PlotGridType plotGetAxisGridType(Plot* plot, PlotAxisId pai);
DS_DEPRECATED PLOTAPI bool plotSetWatermark(Plot* plot, const char* strImage, PlotBgType type);
DS_DEPRECATED PLOTAPI bool plotSetBgImageDrawArea(Plot* plot, const char* strImage, PlotBgType type);
DS_DEPRECATED PLOTAPI bool plotSetBgImageAxis(Plot* plot, PlotAxisId pai, const char* strImage, PlotBgType type);
DS_DEPRECATED PLOTAPI bool plotSetBgImageLegendBox(Plot* plot, const char* strImage, PlotBgType type);
DS_DEPRECATED PLOTAPI void plotSetDrawIdentityCurve(Plot* plot, PlotAxisId pai, int intFlag);
DS_DEPRECATED PLOTAPI int plotSetAxisGridValue(Plot *plot, PlotAxisId axisid, int value);
DS_DEPRECATED PLOTAPI double plotSetAxisInterval(Plot *plot, PlotAxisId axisid, double interval);
DS_DEPRECATED PLOTAPI int plotSetAxisNumberOfMarks(Plot *plot, PlotAxisId axisid, int n);
DS_DEPRECATED PLOTAPI int plotSetAxisTitle(Plot *plot, PlotAxisId axisid, const char *text);
DS_DEPRECATED PLOTAPI PlotAxisType plotSetAxisType(Plot *plot, PlotAxisId axisid, PlotAxisType type);
DS_DEPRECATED PLOTAPI double plotSetAxisMinValue(Plot *plot, PlotAxisId axisid, double min);
DS_DEPRECATED PLOTAPI double plotSetAxisMaxValue(Plot *plot, PlotAxisId axisid, double max);
DS_DEPRECATED PLOTAPI PlotDate plotSetAxisMinDate(Plot *plot, PlotAxisId axisid, PlotDate min);
DS_DEPRECATED PLOTAPI PlotDate plotSetAxisMaxDate(Plot *plot, PlotAxisId axisid, PlotDate max);
DS_DEPRECATED PLOTAPI void plotGetAxisDataLimits (Plot* plot, PlotAxisId axisid, double* min, double* max);
DS_DEPRECATED PLOTAPI void plotGetAxisLimits (Plot* plot, PlotAxisId axisid, double* min, double* max);
DS_DEPRECATED PLOTAPI int plotSetAxisAutoscaleFlag(Plot *plot, PlotAxisId axisid, int autoscale_flag);
DS_DEPRECATED PLOTAPI void plotSetAxisMinRange(Plot *plot, PlotAxisId axisid, double v0, double v1);
DS_DEPRECATED PLOTAPI void plotSetAxisMaxRange(Plot *plot, PlotAxisId axisid, double v0, double v1);
DS_DEPRECATED PLOTAPI int plotGetAxisGridValue(Plot *plot, PlotAxisId axisid);
DS_DEPRECATED PLOTAPI double plotGetAxisInterval(Plot *plot, PlotAxisId axisid);
DS_DEPRECATED PLOTAPI int plotGetAxisNumberOfMarks(Plot *plot, PlotAxisId axisid);
DS_DEPRECATED PLOTAPI const char* plotGetAxisTitle(Plot *plot, PlotAxisId axisid);
DS_DEPRECATED PLOTAPI PlotAxisType plotGetAxisType(Plot *plot, PlotAxisId axisid);
DS_DEPRECATED PLOTAPI double plotGetAxisMinValue(Plot *plot, PlotAxisId axisid);
DS_DEPRECATED PLOTAPI double plotGetAxisMaxValue(Plot *plot, PlotAxisId axisid);
DS_DEPRECATED PLOTAPI PlotDate plotGetAxisMinDate(Plot *plot, PlotAxisId axisid);
DS_DEPRECATED PLOTAPI PlotDate plotGetAxisMaxDate(Plot *plot, PlotAxisId axisid);
DS_DEPRECATED PLOTAPI int plotGetAxisAutoscaleFlag(Plot *plot, PlotAxisId axisid);
DS_DEPRECATED PLOTAPI void plotGetAxisMinRange(Plot *plot, PlotAxisId axisid, double* v0, double* v1);
DS_DEPRECATED PLOTAPI void plotGetAxisMaxRange(Plot *plot, PlotAxisId axisid, double* v0, double* v1);
DS_DEPRECATED PLOTAPI void plotGetAxisComputedRange(Plot *plot, PlotAxisId axisid, double *v0, double *v1);
DS_DEPRECATED PLOTAPI void plotGetAxisExpo(Plot *plot, PlotAxisId pai, int* intExp);
DS_DEPRECATED PLOTAPI double plotGetPositionInAxis(Plot *plot, PlotAxisId axisid, double val);//TODO: rename it to: plotGetAxisPosition
DS_DEPRECATED PLOTAPI void plotSetTipPointPattern(Plot* plot, const char* strPattern, const char* strXFormat = NULL, const char* strYFormat = NULL);
DS_DEPRECATED PLOTAPI int plotUnmapPoint(Plot* plot, PlotAxisId intYAxisId, int intRX, int intRY, double* dblX, double* dblY);
DS_DEPRECATED PLOTAPI int plotMapPoint(Plot* plot, PlotAxisId intYAxisId, double dblX, double dblY, int* intRX, int* intRY);
DS_DEPRECATED PLOTAPI int plotMapValue(Plot* plot, PlotAxisId axisid, double val, int* raster_val);
DS_DEPRECATED PLOTAPI void plotSetShowAxisZeros(Plot* plot, bool bolShow);
DS_DEPRECATED PLOTAPI bool plotGetShowAxisZeros(Plot* plot);
DS_DEPRECATED PLOTAPI void plotSetAxisZero(Plot* plot, PlotAxisId pai, double dblZero);
DS_DEPRECATED PLOTAPI double plotGetAxisZero(Plot* plot, PlotAxisId pai);
DS_DEPRECATED PLOTAPI void plotZoomArea(Plot* plot, int intRX0, int intRY0, int intRX1, int intRY1);
DS_DEPRECATED PLOTAPI void plotZoomAreaNoAspectRatio(Plot* plot, int intRX0, int intRY0, int intRX1, int intRY1);
DS_DEPRECATED PLOTAPI bool plotUndoZoom(Plot* plot);
DS_DEPRECATED PLOTAPI bool plotRedoZoom(Plot* plot);
DS_DEPRECATED PLOTAPI void plotClearZoom(Plot* plot);
DS_DEPRECATED PLOTAPI int plotGetZoomLevel(Plot* plot);
DS_DEPRECATED PLOTAPI int plotGetZoomLevels(Plot* plot);
DS_DEPRECATED PLOTAPI void plotMoveCurvePoint(Plot *plot, int curven, int pointn, int xr_new, int yr_new, int xr_old, int yr_old);
DS_DEPRECATED PLOTAPI void plotDrawCursor(Plot *plot, PlotAxisId axisid, int xr_new, int yr_new, int xr_old, int yr_old);
#endif
/*******************************************************************************
* @endof file plot.h
*******************************************************************************/
