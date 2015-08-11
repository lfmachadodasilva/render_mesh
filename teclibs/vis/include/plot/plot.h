/**
 * @file
 * @brief Biblioteca Plot
 * TeCGraf/PUC-Rio
 * Jan 2003
 */

#ifndef _PLOT_H
#define _PLOT_H

#include <float.h>
#include <limits.h>
#include "cd.h"
#include "cdps.h"

#ifdef __cplusplus
extern "C" {
#endif

#define _PLOT_FUNCTION

#define PLOT_VERSION    "2.3"
  
/** Representa��o de "Not a Number" para "double" */
#define PLOT_NAN_DOUBLE DBL_MAX  

/** Representa��o de "Not a Number" para "int" */
#define PLOT_NAN_INT    INT_MAX

  
/**
 * Eixos do gr�fico.
 */
typedef enum
{
   PLOT_X = 0,
   PLOT_Y1,
   PLOT_Y2,
   PLOT_Y3,
   PLOT_Y4,
   PLOT_MAX_AXIS
} PlotAxisId;

/**
 * Tipo de escala de um eixo. 
 */
typedef enum
{
   PLOT_DEC,      /**< Escala decimal. */
   PLOT_LOG,      /**< Escala logar�tmica. */
   PLOT_DATE      /**< Escala de datas (somente para PLOT_X) */
} PlotAxisType;

/**
 * Posi��o da legenda.
 */
typedef enum
{
   PLOT_TOP,
   PLOT_BOTTOM,
   PLOT_LEFT,
   PLOT_RIGHT,
   PLOT_NONE        /**< Sem legenda. */
} PlotLabelPos;


typedef enum
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
} PlotVar;

/**
 * Tipos de grade (grid) de um eixo.
 */ 
typedef enum
{
   PLOT_NOGRID = 0,   /**< Sem grid. */  
   PLOT_LARGE,        /**< Grid nas marcas maiores do eixo. */
   PLOT_REFINED       /**< Grid nas marcas maiores e menores do eixo. */ 
} PlotGridType;

/**
 * Formatos para exporta��o.
 */
typedef enum 
{
   PLOT_ASCII = 0,  /**< ASCII. */
   PLOT_PS,         /**< PostScript. */
   PLOT_CGM,        /**< Ainda n�o implementado. */
   PLOT_DXF         /**< Ainda n�o implementado. */
} PlotExportType;

/**
 * Tamanhos de papel para exporta��o.
 */
typedef enum PlotPaperSize
{
   PLOT_A0 = CD_A0,
   PLOT_A1 = CD_A1,
   PLOT_A2 = CD_A2,
   PLOT_A3 = CD_A3,
   PLOT_A4 = CD_A4,
   PLOT_A5 = CD_A5,
   PLOT_LETTER = CD_LETTER,
   PLOT_LEGAL = CD_LEGAL
} PlotPaperSize;

/**
 * Estilo de linha.
 */
typedef enum
{
   PLOT_CONTINUOUS   = CD_CONTINUOUS,
   PLOT_DASHED       = CD_DASHED,
   PLOT_DOTTED       = CD_DOTTED,
   PLOT_DASH_DOT     = CD_DASH_DOT,
   PLOT_DASH_DOT_DOT = CD_DASH_DOT_DOT
} PlotLineStyle;      

/**
 * Tipo de fonte.
 */
typedef enum
{
   PLOT_SYSTEM      = CD_SYSTEM,
   PLOT_COURIER     = CD_COURIER,
   PLOT_TIMES_ROMAN = CD_TIMES_ROMAN,
   PLOT_HELVETICA   = CD_HELVETICA
} PlotFontType;   

/**
 * Estilo de fonte.
 */
typedef enum
{
   PLOT_PLAIN       = CD_PLAIN,
   PLOT_BOLD        = CD_BOLD,
   PLOT_ITALIC      = CD_ITALIC,
   PLOT_BOLD_ITALIC = CD_BOLD_ITALIC
} PlotFontStyle;   

/**
 * Tipo de marca.
 */
typedef enum
{
   PLOT_PLUS           = CD_PLUS,
   PLOT_STAR           = CD_STAR,
   PLOT_CIRCLE         = CD_CIRCLE,
   PLOT_X_MARK         = CD_X,
   PLOT_BOX            = CD_BOX,
   PLOT_DIAMOND        = CD_DIAMOND,
   PLOT_HOLLOW_CIRCLE  = CD_HOLLOW_CIRCLE,
   PLOT_HOLLOW_BOX     = CD_HOLLOW_BOX,
   PLOT_HOLLOW_DIAMOND = CD_HOLLOW_DIAMOND
} PlotMarkType;      

/**
 * Tipo da curva a ser desenhada.
 */
typedef enum
{
   PLOT_CURVE     = 0,
   PLOT_HISTOGRAM = 1
} PlotType;


/*
 * Basic types 
 */

/** 
 * Representa��o de um ponto 2D
 */
typedef struct PlotPoint
{
   double x;
   double y;
} PlotPoint;

/** 
 * Representa��o de tipo para data.
 */
typedef struct PlotDate 
{ 
   int day;                                                     
   int month;                                                   
   int year;                                                    
} PlotDate;

/** 
 * Representa��o de uma cor.
 */
typedef struct PlotColor 
{
   unsigned char red;
   unsigned char green;
   unsigned char blue;
   long int      cd_color;
} PlotColor;

/** 
 * Fonte de um texto.
 */
typedef struct PlotFont 
{
   int typeface;
   int style;
   int size;
} PlotFont;

/** 
 * Tipo de marca.
 */
typedef struct PlotMark 
{
   int      type;
   int      size;
} PlotMark;
 
/** 
 * Representa um tipo de linha.
 */
typedef struct PlotLine 
{
   int      width;
   int      style;
} PlotLine;

/** 
 * Tipo representando uma curva.
 */
struct PlotCurve;
typedef struct PlotCurve PlotCurve;

#ifdef _PLOT_FUNCTION
struct PlotFunction;
typedef struct PlotFunction PlotFunction;
#endif


/**
 * Tipo representando um gr�fico.
 */
struct Plot;
typedef struct Plot Plot;

/* Exported functions */

/*
 * Basic structures    
 */

PlotColor  plotColor(unsigned char r, unsigned char g, unsigned char b);
PlotFont   plotFont(int typeface, int style, int size);
PlotMark   plotMark(int type, int size);
PlotLine   plotLine(int width, int style);
PlotDate   plotDate(int day,int month, int year);   
PlotPoint  plotPoint(double x, double y);

int      plotGetDateDay(PlotDate date);
int      plotGetDateMonth(PlotDate date);
int      plotGetDateYear(PlotDate date);
int      plotGetDateNumberOfMonthDays(PlotDate date);
int      plotGetNumberOfYearDays(PlotDate date);
PlotDate plotIncDateDay(PlotDate d);
PlotDate plotDecDateDay(PlotDate d);
int      plotGetElapsedDays(PlotDate sd, PlotDate ed);
int      plotGetElapsedMonths(PlotDate sd, PlotDate ed);
int      plotGetElapsedTrimesters(PlotDate sd, PlotDate ed);
int      plotGetElapsedSemesters(PlotDate sd, PlotDate ed);
int      plotGetColorRed(PlotColor color);
int      plotGetColorGreen(PlotColor color);
int      plotGetColorBlue(PlotColor color);
long int plotGetColorCD(PlotColor color);
int      plotGetFontSize(PlotFont font);
int      plotGetFontTypeface(PlotFont font);
int      plotGetFontStyle(PlotFont font);
int      plotGetMarkType(PlotMark mark);
int      plotGetMarkSize(PlotMark mark);
int      plotGetLineWidth(PlotLine line);
int      plotGetLineStyle(PlotLine line);

/**
 *    Converte uma data (m�nimo: 1900) para valor double, no 
 *  formato: 
 *  
 *      "ano"."fra��o do ano"
 */
double   plotDateToDouble( PlotDate date );

/**
 *    Converte um valor double no formato "ano"."fra��o do ano" para
 *  uma data (m�nimo: 1900).
 */
PlotDate plotDoubleToDate( double day ); 


/*
 * Plot       
 */

/**
 *   Construtor.
 * Cria um novo gr�fico.
 */
Plot*      plotCreate(void);

/**
 *   Destrutor.
 * Destr�i um gr�fico e todas as suas curvas.
 */
void       plotDestroy(Plot *plot);

/**
 *   Adiciona uma curva a um gr�fico. Uma curva deve ser associada
 * somente a um gr�fico.
 *
 * @see plotDestroy()
 */
int        plotAddCurve(Plot *plot, PlotCurve *curve);

/**
 *   Remove uma curva do gr�fico, sem destru�-la.
 *   
 * @param curven �ndice da curva (a partir de 1).
 * @returns Se Ok: 1. Sen�o: 0.
*/
int        plotRemoveCurve(Plot *plot, int curven);

/**
 *   Remove todas as curvas do gr�fico, sem destru�-las.
*/
int  plotRemoveAllCurves(Plot *plot);


/**
 *   Obt�m a i-�sima curva do gr�fico.
 *   
 * @warning Indexado a partir de 1.
 */
PlotCurve *plotGetCurve(Plot *plot, int curven);

/**
 *   Obt�m o n�mero de curvas presentes em um gr�fico.
 */
int       plotGetNumberOfCurves(Plot *plot);

/* 
 * Atributos do gr�fico. 
 */
int          plotSetShowBorder(Plot *plot,int flag);
int          plotSetShowCurveAreaBorder(Plot* plot, int flag);
int          plotSetShowTitle(Plot *plot,int flag);
int          plotSetShowSubtitle(Plot *plot,int flag);
int          plotSetShowLabel(Plot *plot,int flag);
int          plotSetShowAxisLabel(Plot *plot, int flag);
PlotType     plotSetPlotType(Plot *plot, PlotType plot_type);
void         plotSetPickTolerance(Plot *plot, int x, int y);
PlotLabelPos plotSetLabelPos(Plot *plot,PlotLabelPos pos); 
PlotFont     plotSetLabelFont(Plot *plot, PlotFont font);
int          plotSetPlotTitleText(Plot *plot,char *text);
PlotFont     plotSetPlotTitleFont(Plot *plot,PlotFont font);
PlotColor    plotSetPlotTitleColor(Plot *plot,PlotColor color);
int          plotSetPlotSubtitleText(Plot *plot,char *text);
PlotFont     plotSetPlotSubtitleFont(Plot *plot,PlotFont font);
PlotColor    plotSetPlotSubtitleColor(Plot *plot,PlotColor color);
PlotColor    plotSetBackground(Plot *plot,PlotColor color);

/**
 * Define se uma curva deve ser desenhada ap�s todas as outras.
 */
PlotCurve*   plotSetDrawCurveLast(Plot *plot, PlotCurve *curve);


/**
 * Obt�m atributos do gr�fico.
 */
int          plotGetShowBorder(Plot *plot);
int          plotGetShowCurveAreaBorder(Plot* plot);
int          plotGetShowTitle(Plot *plot);
int          plotGetShowSubtitle(Plot *plot);
int          plotGetShowLabel(Plot *plot);
int          plotGetShowAxisLabel(Plot *plot);
PlotType     plotGetPlotType(Plot *plot);
void         plotGetPickTolerance(Plot *plot, int *x, int *y);
PlotLabelPos plotGetLabelPos(Plot *plot);
PlotFont     plotGetLabelFont(Plot *plot); 
char         *plotGetPlotTitleText(Plot *plot);
PlotFont     plotGetPlotTitleFont(Plot *plot);
PlotColor    plotGetPlotTitleColor(Plot *plot);
char         *plotGetPlotSubtitleText(Plot *plot);
PlotFont     plotGetPlotSubtitleFont(Plot *plot);
PlotColor    plotGetPlotSubtitleColor(Plot *plot);
PlotColor    plotGetBackground(Plot *plot);
PlotCurve*   plotGetDrawCurveLast(Plot *plot);

/* Var*/
PlotVar plotSetXVar(Plot *plot, PlotVar var);
PlotVar plotGetXVar(Plot *plot);
int     plotSetXVarProp(Plot *plot, int prop);
int     plotGetXVarProp(Plot *plot);

/* Utilities */

/**
 *   Altera o flag de requisi��o de atualiza��o do gr�fico.
 */
void    plotSetRecalculate( Plot* plot, int flag );

/**
 *   Obt�m flag de requisi��o de atualiza��o do gr�fico.
 */
int     plotGetRecalculate( Plot* plot );

/**
 *   Atualiza o gr�fico e desabilita quaisquer requisi��es de atualiza��o,
 * sem desenh�-lo.  
 *   � necess�rio haver um canvas cd ativo.
 */
void    plotRecalculate( Plot* plot );

/**
 *   Redesenha gr�fico, dado um canvas cd ativo.
 *
 *   O procedimento para desenhar o gr�fico � o seguinte:
 *
 *   cdActivate(cd_canvas);
 *   plotRedraw(plot);
 *   cdFlush();   --> Importante se estiver usando double buffer.
 *
 *   Quando o gr�fico � redesenhado, a fun��o plotRecalculate() � 
 * chamada automaticamente (quando necess�rio).
 */
void    plotRedraw(Plot *plot);

/*void    plotRedrawHistogram(cdCanvas *canvas,Plot *plot);*/


/**
 *   Dada uma posi��o em raster, retorna o valor correspondente relativo
 * a um eixo.
 *
 * @warning O valor retornado sempre possui uma pequena imprecis�o.
 */
int plotUnmapPoint(Plot* plot, PlotAxisId y_axisid, int raster_x, int raster_y,
                   double *x, double *y);


/**
 *   Dado o valor de um ponto, relativo a um eixo, retorna a posi��o
 * correspondente em raster.
 * 
 * @warning plotMapPoint, ao receber o valor de um ponto retornado 
 * por plotUnmapPoint, pode retornar uma posi��o raster 
 * ligeiramente diferente da posi��o usada na chamada de 
 * plotUnmapPoint, devido a erros de precis�o das opera��es
 * de ponto flutuante. 
 */
int plotMapPoint( Plot* plot, PlotAxisId y_axisid, double x, double y,
                  int* raster_x, int* raster_y );


/**
 *   Pega (Pick) um ponto de uma curva.
 *
 * @param raster_x Coordenada x em raster.
 * @param raster_y Coordenada y em raster.
 * @param x End. onde ser� retornada a coordenada x do ponto pego.
 * @param y End. onde ser� retornada a coordenada y do ponto pego.
 * @param pos End. de retorno para a posi��o do ponto pego.
 * @returns �ndice da curva ou 0, se n�o pegou nenhuma curva.
 */
int plotPickCurvePoint( Plot* plot, int raster_x, int raster_y, 
                        double *x, double *y, int *pos);

/**
    Retorna se o ponto est� dentro da �rea de desenho de curva.
*/
int plotIsInCurveArea(Plot* plot, int raster_x, int raster_y);

/**
 *   Pega (Pick) um segmento de uma curva, ignorando os pontos da fronteira
 * do segmento. Para pegar um desses pontos, deve ser chamada 
 * plotPickCurvePoint.
 *
 * @param raster_x Coordenada x em raster.
 * @param raster_y Coordenada y em raster.
 * @param x End. onde ser� retornada a coordenada x do ponto pego no seg.
 * @param y end. onde ser� retornada a coordenada y do ponto pego no seg.
 * @param pos End. de retorno para a posi��o do primeiro ponto do segmento. 
 * @returns �ndice da curva ou 0, se n�o pegou nenhuma curva.
 */
int plotPickCurveSegment( Plot* plot, int xpr, int ypr, 
                          double *picked_x, double *picked_y, int* pos );


/**
 *   Pega legenda de uma curva, na �rea de legenda do gr�fico,
 * se esta estiver sendo exibida.
 * S� deve ser chamada ap�s desenhar o gr�fico j� ter sido desenhado. 
 * 
 * @param  xr Coordenada x em raster.
 * @param  yr Coordenada y em raster.
 * @returns �ndice da curva ou 0, se n�o pegou nenhuma curva.
 */
int plotPickCurveLabel( Plot* plot, int xr, int yr );
  


/** I/O functions */

/**
 *   L� arquivo no formato (.plot).
 */
int plotRead (char* filename, Plot *plot);

/** 
 *   Salva arquivo no formato (.plot).
 *
 * @warning Desatualizado!!!!! Algumas fun��es indispon�veis!!!
 */
int plotWrite (char* filename, Plot *plot);


/**
 *   Exporta��o de gr�fico.
 *
 * @param type Tipo da exporta��o.
 * @param data 
 *       PLOT_ASCII: nome de arquivo.
 *       PLOT_PS: String com os mesmos par�metros usados
 *    para a cria��o de um canvas para o driver PS no CD. O tipo
 *    de papel fornecido pode ser PLOT_papel, al�m de CD_papel. As
 *    duas formas s�o equivalentes.
 * @returns Se OK: 1. Sen�o: 0. 
 */ 
int plotExport(PlotExportType type, char* data, Plot *plot);


/*
 * PlotCurve  
 */

/**
 *   Construtor.
 * Cria um curva que pode ser associada a um gr�fico.
 */
PlotCurve* plotCreateCurve(void);

/**
 *   Destrutor.
 * Destr�i um curva.
 *
 * @see plotDestroy()
 */
void plotDestroyCurve(PlotCurve *curve);

/**
 *   Adiciona um ponto ao final de uma curva.
 */
int  plotAddPoint( PlotCurve *curve, double x, double y );

/**
 *   Altera um ponto da curva sem atualizar o gr�fico ou recalcular
 * a autoescala, no caso da curva estar inserida em um gr�fico.
 * Os c�lculos ser�o realizados quando ocorrer algum evento que necessite
 * de atualiza��o (ex.: inser��o de nova curva), ou chamando a fun��o
 * "plotSetRecalculate".
 *
 * @param pos Posi��o do ponto na curva (indexado a partir de 1).
 * @param x  Valor novo para x.
 * @param y  Valor novo para y.
 * @see plotSetRecalculate()
 */
int  plotReplacePoint( PlotCurve *curve, int pos, double x, double y );

/**
 *   Remove um ponto de uma curva sem atualizar o gr�fico ou recalcular
 * a autoescala, no caso da curva estar inserida em um gr�fico.
 * Os c�lculos ser�o realizados quando ocorrer algum evento que necessite
 * de atualiza��o (ex.: inser��o de nova curva), ou chamando a fun��o
 * "plotSetRecalculate".
 *
 * @param pos Posi��o do ponto na curva (indexado a partir de 1).
 * @see plotSetRecalculate()
 */ 
int  plotRemovePoint( PlotCurve *curve, int pos );

/**
 *   Obt�m o n�mero de pontos de uma curva.
 */
int  plotGetNumberOfPoints(PlotCurve *curve);

/* 
 * Set Curve attributes 
 */
int        plotSetCurveShowMark(PlotCurve *curve, int flag); 
int        plotSetCurveShowLine(PlotCurve *curve, int flag);
int        plotSetCurveLabel(PlotCurve *curve, char *text);
int        plotSetCurveShowLabel(PlotCurve *curve, int flag);
PlotAxisId plotSetCurveAxisId(PlotCurve *curve, PlotAxisId axisid);
PlotMark   plotSetCurveMark(PlotCurve *curve, PlotMark mark);
/**
    Altera o intervalo das marcas que ser�o mostradas.
*/
int plotSetCurveMarkInterval(PlotCurve* curve, int interval);
PlotLine   plotSetCurveLine(PlotCurve *curve, PlotLine line);
PlotColor  plotSetCurveColor(PlotCurve *curve, PlotColor color);


/**
 * Define se uma curva pode ser pega utilizando as fun��es de pick de curva.
 *
 * @param flag Se 1 (default): curva pode se pega. Caso contr�rio: 0.
 */
int        plotSetCurvePickFlag(PlotCurve *curve, int flag);

/*
 * Get Curve attributes 
 */
int        plotGetCurveShowMark(PlotCurve *curve); 
int        plotGetCurveShowLine(PlotCurve *curve);
char       *plotGetCurveLabel(PlotCurve *curve);
int       plotGetCurveShowLabel(PlotCurve *curve);
PlotAxisId plotGetCurveAxisId(PlotCurve *curve);
PlotMark   plotGetCurveMark(PlotCurve *curve);
/**
    Retorna o intervalo das marcas que ser�o mostradas.
*/
int        plotGetCurveMarkInterval(PlotCurve* curve);
PlotLine   plotGetCurveLine(PlotCurve *curve);
PlotColor  plotGetCurveColor(PlotCurve *curve);


/**
 *   Obt�m o valor da coordenada x de um ponto da curva.
 *
 * @param pointn �ndice do ponto na curva (a partir de 1).
 */
double     plotGetCurvePointX(PlotCurve *curve, int pointn);

/**
 *   Obt�m o valor da coordenada y de um ponto da curva.
 * 
 * @param pointn �ndice do ponto na curva (a partir de 1).
 */
double     plotGetCurvePointY(PlotCurve *curve, int pointn);

/**
 *   Retorna o flag indicando se uma curva pode ser pega utilizando 
 * as fun��es de pick de curva.
 */
int        plotGetCurvePickFlag(PlotCurve *curve);

/**
  Determina se a curva sera utilizada para o calculo da escala automatica.
*/
int        plotSetCurveAutoscaleFlag(PlotCurve* curve, int flag);
int        plotGetCurveAutoscaleFlag(PlotCurve* curve);

#ifdef _PLOT_FUNCTION
int  plotAddFunction(Plot *plot, PlotFunction *func);
/* 1-indexed.*/
PlotFunction* plotGetFunction(Plot *plot, int i);
int plotGetNumberOfFunctions(Plot *plot);
int  plotRemoveFunction(Plot *plot, int id);
int  plotRemoveAllFunctions(Plot *plot);

PlotFunction* plotCreateFunction();
void plotDestroyFunction(PlotFunction* f);
PlotFunction* plotCreateLinearFunction(double a, double b);
PlotFunction* plotCreateExpFunction(double a, double b);
PlotFunction* plotCreateLogFunction(double a, double b);
PlotFunction* plotCreatePowFunction(double a, double b);
double plotFunctionGetY(PlotFunction* f, double x);
double plotFunctionSetParam(PlotFunction *f, int id, double val);
double plotFunctionGetParam(PlotFunction *f, int id);
int plotFunctionSetNumberOfParams(PlotFunction *f, int n);
int plotFunctionGetNumberOfParams(PlotFunction *f);
void plotFunctionSetRange(PlotFunction *f, double v0, double v1);
void plotFunctionGetRange(PlotFunction *f, double *v0, double *v1);
int plotFunctionSetAutoscaleFlag(PlotFunction *f, int flag);
int plotFunctionGetAutoscaleFlag(PlotFunction *f);
int plotFunctionSetNumberOfSamples(PlotFunction *f, int n);
int plotFunctionGetNumberOfSamples(PlotFunction *f);

int        plotFunctionSetLabel(PlotFunction* func, char *text);
char*      plotFunctionGetLabel(PlotFunction* func);
int        plotFunctionSetShowLabel(PlotFunction* func, int flag);
int        plotFunctionGetShowLabel(PlotFunction* func);
PlotAxisId plotFunctionSetAxisId(PlotFunction* func, PlotAxisId axisid);
PlotAxisId plotFunctionGetAxisId(PlotFunction* func);
PlotLine   plotFunctionSetLine(PlotFunction* func, PlotLine line);
PlotLine   plotFunctionGetLine(PlotFunction* func);
PlotColor  plotFunctionSetColor(PlotFunction* func, PlotColor color);
PlotColor  plotFunctionGetColor(PlotFunction* func);
#endif



/*
 * PlotAxis  
 */

/**
 *   Define a dist�ncia entre duas linhas da grade (grid) de um eixo, 
 * em n�mero de marcas menores do eixo. S� tem efeito para grid do tipo 
 * REFINED.
 *
 * @see PlotGridType
 */ 
int          plotSetAxisGridValue(Plot *plot,PlotAxisId axisid, int value);

/**
 *   Altera o tipo da grade (grid) de um eixo.
 *
 * @see PlotGridType
 */
PlotGridType plotSetAxisGridType(Plot *plot,PlotAxisId axisid, 
                                 PlotGridType type);

/**
 *  Define a cor do grid nas marcas maiores do eixo.
 */
PlotColor    plotSetAxisGridColor(Plot *plot, PlotAxisId axisid, 
                                  PlotColor color);

/**
 *   Define se cor do grid nas marcas menores est� habilitada.
 * Se n�o estiver habilitada, a cor ser� a do grid nas marcas maiores.
 */
int          plotSetAxisRefinedGridColorFlag(Plot *plot, PlotAxisId axisid,
                                             int flag);

/**
 *   Define a cor do grid nas marcas menores do eixo.
 */
PlotColor    plotSetAxisRefinedGridColor(Plot *plot, PlotAxisId axisid,
                                           PlotColor color);

/** 
 *   Altera valor do intervalo entre as marcas menores de um eixo.
 */
double       plotSetAxisInterval(Plot *plot,PlotAxisId axisid, double interval);

/**
 *   Altera n�mero de marcas menores de um eixo.
 */ 
int          plotSetAxisNumberOfMarks(Plot *plot,PlotAxisId axisid, int n);

/**
 *   Altera o t�tulo de um eixo.
 */
int          plotSetAxisTitle(Plot *plot,PlotAxisId axisid,char *text);

/**
 *   Altera a cor do t�tulo de um eixo.
 */
PlotColor    plotSetAxisTitleColor(Plot *plot, PlotAxisId axisid, 
                                   PlotColor color);

/**
 *   Altera o tipo de escala de um eixo.
 * @warning O eixo x � o �nico que aceita escala de datas.
 *
 * @see PlotAxisType
 */
PlotAxisType plotSetAxisType(Plot *plot,PlotAxisId axisid,PlotAxisType type);

/**
 *   Altera o valor m�nimo do eixo, utilizado quando a escala autom�tica
 * est� desligada.
 */
double       plotSetAxisMinValue(Plot *plot,PlotAxisId axisid,double min);

/**
 *   Altera o valor m�ximo do eixo, utilizado quando a escala autom�tica
 * est� desligada.
 */
double       plotSetAxisMaxValue(Plot *plot,PlotAxisId axisid,double max);

/**
 *   Altera a data m�nima de um eixo de datas, 
 * utilizado quando a escala autom�tica est� desligada.
 */
PlotDate     plotSetAxisMinDate(Plot *plot,PlotAxisId axisid,PlotDate min);

/**
 *   Altera a data m�xima de um eixo de datas, 
 * utilizado quando a escala autom�tica est� desligada.
 */
PlotDate     plotSetAxisMaxDate(Plot *plot,PlotAxisId axisid,PlotDate max);
/*int          plotSetAxisShowGrid(Plot *plot,PlotAxisId axisid,int grid_flag);
*/

/**
 *   Habilita/desabilita escala autm�tica.
 */
int          plotSetAxisAutoscaleFlag(Plot *plot,PlotAxisId axisid,
                                      int autoscale_flag);
void         plotSetAxisMinRange(Plot *plot, PlotAxisId axisid, double v0, double v1);
void         plotSetAxisMaxRange(Plot *plot, PlotAxisId axisid, double v0, double v1);


PlotFont     plotSetAxisFont(Plot *plot, PlotAxisId axisid, PlotFont font);
PlotColor    plotSetAxisColor(Plot *plot, PlotAxisId axisid, PlotColor color);
PlotFont     plotSetAxisValueFont(Plot *plot, PlotAxisId axisid, PlotFont font);


/* Get Axis attributes*/
int          plotGetAxisGridValue(Plot *plot,PlotAxisId axisid);
PlotGridType plotGetAxisGridType(Plot *plot,PlotAxisId axisid);
PlotColor    plotGetAxisGridColor(Plot *plot,PlotAxisId axisid);
int          plotGetAxisRefinedGridColorFlag(Plot *plot, PlotAxisId axisid);
PlotColor    plotGetAxisRefinedGridColor(Plot *plot, PlotAxisId axisid);

double       plotGetAxisInterval(Plot *plot,PlotAxisId axisid);
int          plotGetAxisNumberOfMarks(Plot *plot,PlotAxisId axisid);
char         *plotGetAxisTitle(Plot *plot,PlotAxisId axisid);
PlotColor    plotGetAxisTitleColor(Plot *plot,PlotAxisId axisid);
PlotAxisType plotGetAxisType(Plot *plot,PlotAxisId axisid);
double       plotGetAxisMinValue(Plot *plot,PlotAxisId axisid);
double       plotGetAxisMaxValue(Plot *plot,PlotAxisId axisid);
PlotDate     plotGetAxisMinDate(Plot *plot,PlotAxisId axisid);
PlotDate     plotGetAxisMaxDate(Plot *plot,PlotAxisId axisid);
/*int          plotGetAxisShowGrid(Plot *plot,PlotAxisId axisid);
*/
int          plotGetAxisAutoscaleFlag(Plot *plot,PlotAxisId axisid);
void         plotGetAxisMinRange(Plot *plot, PlotAxisId axisid, double* v0, double* v1);
void         plotGetAxisMaxRange(Plot *plot, PlotAxisId axisid, double* v0, double* v1);
void         plotGetAxisComputedRange(Plot *plot, PlotAxisId axisid, double *v0, double *v1);
PlotFont     plotGetAxisFont(Plot *plot,PlotAxisId axisid);
PlotFont     plotGetAxisValueFont(Plot *plot,PlotAxisId axisid);
PlotColor    plotGetAxisColor(Plot *plot,PlotAxisId axisid);


/**
 *   Move ponto da curva desenhada para outra posi��o somente no gr�fico, sem 
 * modificar a curva original, e usando XOR sobre um canvas CD ativado 
 * anteriormente � chamada de plotMoveCurvePoint.
 * Se xr_old ou yr_old for PLOT_NAN_INT, n�o redesenha com XOR sobre esse
 * ponto. O mesmo vale para xr_new e yr_new.
 *
 * @param curven �ndice da curva (a partir de 1).
 * @param xr_new Nova posi��o x, em raster, do ponto.
 * @param yr_new Nova posi��o y, em raster, do ponto.
 * @param xr_old Posi��o anterior x, em raster, do ponto.
 * @param yr_old Posi��o anterior y, em raster, do ponto.
 */
void plotMoveCurvePoint( Plot *plot, int curven, 
                  int pointn, int xr_new, int yr_new, int xr_old, int yr_old );

/**
 *   Desenha um ret�ngulo com linha pontilhada utilizando XOR. �til para 
 * desenhar uma janela de Zoom.
 *
 * @param xr_min Posi��o x inicial do ret�ngulo, em raster.
 * @param yr_min Posi��o y inicial do ret�ngulo, em raster.
 * @param xr_max Posi��o x final do ret�ngulo, em raster.
 * @param yr_max Posi��o y final do ret�ngulo, em raster.
 */
int plotDrawRect( Plot* plot, int xr_min, int yr_min, int xr_max, int yr_max );

/**
 *   Desenha uma linha utilizando XOR. 
 */
int plotDrawLine(Plot* plot, int x0_raster, int y0_raster, int x1_raster, int y1_raster);

/**
 *   Desenha cursor em cruz com XOR, em raster. Pode ser usado para desenhar
 * barras horizontais ou verticais.
 * 
 *  Para converter das coordenadas de um eixo do gr�fico para raster,
 * utilize a fun��o plotMapPoint().
 *  As seguintes situa��es s�o poss�veis:
 *    - Se xr_new (xr_old) e yr_new (yr_old) forem iguais a PLOT_NAN_INT, 
 *  n�o desenha (apaga) cursor. 
 *    - Se xr_new e yr_new forem iguais a PLOT_NAN_INT, n�o desenha novo.
 *    - Se xr_new (xr_old) for PLOT_NAN_INT, desenha (apaga) uma barra 
 *  horizontal.
 *    - Se yr_new (yr_old) for PLOT_NAN_INT, desenha (apaga) uma barra 
 *  vertical.
 * 
 * @param axisid Eixo do gr�fico.
 * @param xr_new Nova posi��o x, em raster, do cursor.
 * @param yr_new Nova posi��o y, em raster, do cursor.
 * @param xr_old Posi��o anterior x, em raster, do cursor.
 * @param yr_old Posi��o anterior y, em raster, do cursor.
 */ 
void plotDrawCursor( Plot *plot, PlotAxisId axisid, 
                     int xr_new,int yr_new,int xr_old,int yr_old );
/**
 * Desenha uma linha dentro dos limites da �rea de desenho do gr�fico.
 */
//void plotDrawLine( Plot *plot, PlotLine line, int x0, int y0, int x1, int y1); 

/**
 *   Faz zoom de uma �rea do gr�fico.
 * Desliga a escala autom�tica de todos os eixos.
 * Para atualizar o gr�fico, deve ser chamada plotRedraw.
 * 
 * @param xr_0 Posi��o x inicial do ret�ngulo, em raster.
 * @param yr_0 Posi��o y inicial do ret�ngulo, em raster.
 * @param xr_1 Posi��o x final do ret�ngulo, em raster.
 * @param yr_1 Posi��o y final do ret�ngulo, em raster.
 */
void plotZoomArea( Plot *plot, int xr_0, int yr_0, int xr_1, int yr_1 );

/**
  Faz zoom de uma �rea do gr�fico, mas n�o mant�m o aspect ratio.
*/
void plotZoomAreaNoAspectRatio( Plot *plot, int xr_0, int yr_0, int xr_1, int yr_1 );

void plotUndoZoom(Plot* plot);
int plotGetZoomLevel(Plot* plot);
void plotClearZoom(Plot* plot);


#ifdef __cplusplus
}
#endif

#endif
