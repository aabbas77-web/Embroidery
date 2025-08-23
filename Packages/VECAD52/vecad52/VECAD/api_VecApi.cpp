/********************************************************************
* VeCAD version 5.2.10
* Copyright (c) 1999-2001 by Oleg Kolbaskin.
* All rights reserved.
*
* This file must be included in C++ project 
* that used library VeCad.dll
* This file makes dynamic linking with VeCAD functions.
*
* Visual C++ applications can not include this file,
* but use Vecad.lib file instead
********************************************************************/
#include <windows.h>
//AliSoft #include "vecapi.h"
#include "api_VecApi.h"


//*******************************************************************
// define type "pointer to function"
//*******************************************************************
typedef int  (VC_API *tfGetVersion    )();
typedef BOOL (VC_API *tfRegistration  )(int RegCode);
typedef BOOL (VC_API *tfSetMsgHandler )(DWGPROC pfDwgProc);
typedef HWND (VC_API *tfWndCreate     )(HWND hParent, int Style, int X, int Y, int W, int H);
typedef BOOL (VC_API *tfWndResize     )(HWND hVecWnd, int X, int Y, int W, int H);
typedef BOOL (VC_API *tfWndSetTitle   )(HWND hVecWnd, LPCTSTR pTitle);
typedef BOOL (VC_API *tfWndSetMaxRect )(HWND hVecWnd, const RECT* pRect);
typedef BOOL (VC_API *tfWndSetCursor  )(HWND hVecWnd, HCURSOR hCursor);
typedef HWND (VC_API *tfToolBarCreate )(HWND hwParent, int Id, int X, int Y, int W, int H, int* pW, int* pH);
typedef BOOL (VC_API *tfToolBarButton )(int Id);
typedef HWND (VC_API *tfStatBarCreate )(HWND hwParent, int* pH);
typedef BOOL (VC_API *tfStatBarResize )();
typedef BOOL (VC_API *tfStatBarSetText)(int iPart, LPCTSTR szText);
typedef BOOL (VC_API *tfIndicCreate   )(HWND Parent, LPCTSTR szTitle);
typedef BOOL (VC_API *tfIndicDestroy  )();
typedef BOOL (VC_API *tfIndicSetRange )(int nFrom,int nTo);
typedef BOOL (VC_API *tfIndicSetPos   )(int iPos);
typedef BOOL (VC_API *tfIndicSetText  )(LPCTSTR szText);
typedef BOOL (VC_API *tfIndicStep     )();
typedef int  (VC_API *tfDocCreate     )(HWND hwVec);
typedef BOOL (VC_API *tfDocDelete     )(int iDwg);
typedef int  (VC_API *tfDocSetActive  )(int iDwg);
typedef int  (VC_API *tfDocGetActive  )();
typedef BOOL (VC_API *tfDocCopy       )(int iDwgSrc,int iDwgDest,int Mode);
typedef int  (VC_API *tfPageAdd       )(LPCTSTR szName, int Size, int Orient, int W, int H);
typedef BOOL (VC_API *tfPageDelete    )(int Index);
typedef int  (VC_API *tfPageActive    )(int Mode, int Index);
typedef int  (VC_API *tfPageCount     )();
typedef int  (VC_API *tfPageIndex     )(LPCTSTR szName, int ID);
typedef int  (VC_API *tfLayerAdd      )(LPCTSTR szName, double LineWidth, COLORREF LineColor, COLORREF FillColor);
typedef BOOL (VC_API *tfLayerDelete   )(int Index);
typedef int  (VC_API *tfLayerActive   )(int Index);
typedef int  (VC_API *tfLayerCount    )();
typedef int  (VC_API *tfLayerIndex    )(LPCTSTR szName, int ID);
typedef int  (VC_API *tfStLineAdd     )(LPCTSTR szName, LPCTSTR szDesc);
typedef BOOL (VC_API *tfStLineDelete  )(int Index);
typedef int  (VC_API *tfStLineActive  )(int Index);
typedef int  (VC_API *tfStLineCount   )();
typedef int  (VC_API *tfStLineIndex   )(LPCTSTR szName, int ID);
typedef int  (VC_API *tfStTextAdd     )(LPCTSTR szName, LPCTSTR szFont, double Width, double Oblique, int Prec, BOOL Filled, BOOL Bold);
typedef BOOL (VC_API *tfStTextDelete  )(int Index);
typedef int  (VC_API *tfStTextActive  )(int Index);
typedef int  (VC_API *tfStTextCount   )();
typedef int  (VC_API *tfStTextIndex   )(LPCTSTR szName, int ID);
typedef BOOL (VC_API *tfStTextReload  )();
typedef int  (VC_API *tfStHatchAdd    )(LPCTSTR szName, LPCTSTR szDesc);
typedef BOOL (VC_API *tfStHatchDelete )(int Index);
typedef int  (VC_API *tfStHatchActive )(int Index);
typedef int  (VC_API *tfStHatchCount  )();
typedef int  (VC_API *tfStHatchIndex  )(LPCTSTR szName, int ID);
typedef int  (VC_API *tfStDimAdd      )(LPCTSTR szName);
typedef BOOL (VC_API *tfStDimDelete   )(int Index);
typedef int  (VC_API *tfStDimActive   )(int Index);
typedef int  (VC_API *tfStDimCount    )();
typedef int  (VC_API *tfStDimIndex    )(LPCTSTR szName, int ID);
typedef int  (VC_API *tfStPointAdd    )(LPCTSTR szName);
typedef BOOL (VC_API *tfStPointDelete )(int Index);
typedef int  (VC_API *tfStPointActive )(int Index);
typedef int  (VC_API *tfStPointCount  )();
typedef int  (VC_API *tfStPointIndex  )(LPCTSTR szName, int ID);
typedef int  (VC_API *tfGrPointAdd    )(LPCTSTR szName);
typedef BOOL (VC_API *tfGrPointDelete )(int Index);
typedef int  (VC_API *tfGrPointActive )(int Index);
typedef int  (VC_API *tfGrPointCount  )();
typedef int  (VC_API *tfGrPointIndex  )(LPCTSTR szName, int ID);
typedef int  (VC_API *tfViewSave      )(LPCTSTR szName);
typedef BOOL (VC_API *tfViewDelete    )(int Index);
typedef int  (VC_API *tfViewRestore   )(int Index);
typedef int  (VC_API *tfViewCount     )();
typedef int  (VC_API *tfViewIndex     )(LPCTSTR szName, int ID);
typedef int  (VC_API *tfPrnRectAdd    )(double X, double Y, double W, double H, double Angle);
typedef BOOL (VC_API *tfPrnRectDelete )(int Index);
typedef int  (VC_API *tfPrnRectCount  )();
typedef BOOL (VC_API *tfPrnRectPrint  )(int Index, HDC hPrintDC, double ScaleX, double ScaleY, double OriginX, double OriginY);
typedef int  (VC_API *tfPrnRectAuto   )(double Width, double Height);
typedef BOOL (VC_API *tfBlockBegin    )();
typedef int  (VC_API *tfBlockAdd      )(LPCTSTR szName, double x, double y);
typedef int  (VC_API *tfBlockAddF     )(LPCTSTR szFileName, LPCTSTR szBlockName);
typedef BOOL (VC_API *tfBlockDelete   )(int Index);
typedef int  (VC_API *tfBlockActive   )(int Index);
typedef int  (VC_API *tfBlockCount    )();
typedef int  (VC_API *tfBlockIndex    )(LPCTSTR szName, int ID);
typedef int  (VC_API *tfAddPoint      )(double X, double Y);
typedef int  (VC_API *tfAddLine       )(double X1, double Y1, double X2, double Y2);
typedef int  (VC_API *tfAddArcEx      )(double X, double Y, double Rh, double Rv, double Ang0, double AngArc, double AngRot);
typedef int  (VC_API *tfAddCircle     )(double X, double Y, double Rad);
typedef int  (VC_API *tfAddCircle3P   )(double X1, double Y1, double X2, double Y2, double X3, double Y3);
typedef int  (VC_API *tfAddArc        )(double X, double Y, double Rad, double Ang1, double Ang2);
typedef int  (VC_API *tfAddArc3P      )(double X1, double Y1, double X2, double Y2, double X3, double Y3);
typedef int  (VC_API *tfAddEllipse    )(double X, double Y, double Rh, double Rv, double Angle);
typedef BOOL (VC_API *tfSetTextParam  )(int Mode, double Var);
typedef BOOL (VC_API *tfSetTextParams )(int Align, double Height, double Angle, double ScaleW, double Oblique, double HInter, double VInter);
typedef int  (VC_API *tfAddText       )(double X, double Y, LPCTSTR szStr);
typedef BOOL (VC_API *tfPolylineBegin )();
typedef BOOL (VC_API *tfVertex        )(double X, double Y);
typedef BOOL (VC_API *tfVertexR       )(double X, double Y, double Radius);
typedef BOOL (VC_API *tfVertexF       )(double X, double Y, BOOL bOnCurve);
typedef BOOL (VC_API *tfVertexB       )(double X, double Y, double Bulge);
typedef int  (VC_API *tfAddPolyline   )(int SmoothType, BOOL bClosed);
typedef int  (VC_API *tfAddBlockIns   )(int Index, double X, double Y, double Angle, double Xscale, double Yscale);
typedef int  (VC_API *tfAddHatch      )(int Index, double Scale, double Angle);
typedef int  (VC_API *tfAddRaster     )(LPCTSTR FileName, double X, double Y, double ResH, double ResV);
typedef int  (VC_API *tfAddRect       )(double X, double Y, double W, double H, double Ang, double Rad);
typedef int  (VC_API *tfAddDimHor     )(double X1, double Y1, double X2, double Y2, double Y);
typedef int  (VC_API *tfAddDimVer     )(double X1, double Y1, double X2, double Y2, double X);
typedef int  (VC_API *tfAddDimPar     )(double X1, double Y1, double X2, double Y2, double Off);
typedef int  (VC_API *tfAddDimAng     )(double Xcen, double Ycen, double X1, double Y1, double X2, double Y2, double Off);
typedef int  (VC_API *tfAddDimRad     )(double Xcen, double Ycen, double Xrad, double Yrad, double Off);
typedef int  (VC_API *tfAddDimDiam    )(double Xcen, double Ycen, double Xrad, double Yrad);
typedef int  (VC_API *tfAddDimOrd     )(double X, double Y, double Xtxt, double Ytxt, BOOL bYord);
typedef int  (VC_API *tfAddDwgIns     )(LPCTSTR FileName, double X, double Y, double Angle, double ScaleH, double ScaleV, int iPage);
typedef int  (VC_API *tfFileNew       )(HWND hwVec, LPCTSTR szTemplate);
typedef int  (VC_API *tfFileOpen      )(HWND hwVec, LPCTSTR szFileName);
typedef BOOL (VC_API *tfFileLoad      )(int Mode, LPCTSTR szFileName);
typedef BOOL (VC_API *tfFileSave      )(int Mode, LPCTSTR szFileName);
typedef BOOL (VC_API *tfFileList      )(HWND hwParent);
typedef BOOL (VC_API *tfFileLoadMem   )(void* pMem);
typedef int  (VC_API *tfFileSaveMem   )(void* pMem, int MaxSize);
typedef int  (VC_API *tfGetEntity      )(int Mode, int Prm1, int Prm2);
typedef int  (VC_API *tfGetBlockEntity )(int iBlock, int Counter);
typedef BOOL (VC_API *tfSelect          )(BOOL bSelect, int Index);
typedef int  (VC_API *tfSelectByPoint   )(BOOL bSelect, double X, double Y, double Delta);
typedef int  (VC_API *tfSelectByRect    )(BOOL bSelect, double Left, double Bottom, double Right, double Top, BOOL Cross);
typedef int  (VC_API *tfSelectByPolygon )(BOOL bSelect, const VLPOINT* Ver, int nver, BOOL bCross);
typedef int  (VC_API *tfSelectByPolyline)(BOOL bSelect, const VLPOINT* Ver, int nver);
typedef int  (VC_API *tfSelectByDist    )(BOOL bSelect, double X, double Y, double Dist, BOOL bCross);
typedef int  (VC_API *tfSelectByHandle  )(BOOL bSelect, int Handle);
typedef int  (VC_API *tfSelectByKey     )(BOOL bSelect, int Key);
typedef int  (VC_API *tfSelectByLayer   )(BOOL bSelect, int Index);
typedef BOOL (VC_API *tfCbCut        )();
typedef BOOL (VC_API *tfCbCopy       )();
typedef BOOL (VC_API *tfCbPaste      )(double X, double Y);
typedef int  (VC_API *tfCopy         )(int iObj, double dx, double dy);
typedef BOOL (VC_API *tfMove         )(int iObj, double dx, double dy);
typedef BOOL (VC_API *tfRotate       )(int iObj, double X, double Y, double Angle);
typedef BOOL (VC_API *tfScale        )(int iObj, double X, double Y, double Scale);
typedef BOOL (VC_API *tfMirror       )(int iObj, double X1, double Y1, double X2, double Y2);
typedef BOOL (VC_API *tfErase        )(int iObj);
typedef BOOL (VC_API *tfExplode      )(int iObj);
typedef BOOL (VC_API *tfJoin         )(double Delta);
typedef BOOL (VC_API *tfUndo         )();
typedef BOOL (VC_API *tfRedo         )();
typedef BOOL (VC_API *tfPolyVerInsert)(int iEnt, int iVer);
typedef BOOL (VC_API *tfPolyVerDelete)(int iEnt, int iVer);
typedef BOOL (VC_API *tfPolyVerGet   )(int iEnt, int iVer, double* pX, double* pY, double* pPrm);
typedef BOOL (VC_API *tfPolyVerSet   )(int iEnt, int iVer, double X, double Y, double Prm);
typedef BOOL (VC_API *tfGripGet      )(int iObj, int iGrip, double* pX, double* pY);
typedef BOOL (VC_API *tfGripSet      )(int iObj, int iGrip, double X, double Y);
typedef BOOL (VC_API *tfGripMove     )(int iObj, int iGrip, double dx, double dy);
typedef int  (VC_API *tfPropGet       )(int PropID, int iObj, void* pData);
typedef int  (VC_API *tfPropGetInt    )(int PropID, int iObj);
typedef double (VC_API *tfPropGetDbl  )(int PropID, int iObj);
typedef int  (VC_API *tfPropPut       )(int PropID, int iObj, const void* pData);
typedef int  (VC_API *tfPropPutInt    )(int PropID, int iObj, int Value);
typedef int  (VC_API *tfPropPutDbl    )(int PropID, int iObj, double Value);
typedef BOOL (VC_API *tfZoom          )(double Scale);
typedef BOOL (VC_API *tfZoomRect      )(double Left, double Bottom, double Right, double Top);
typedef BOOL (VC_API *tfZoomPan       )(double dx, double dy);
typedef BOOL (VC_API *tfCoordWinToDwg )(int Xwin, int Ywin, double* Xdwg, double* Ydwg);
typedef BOOL (VC_API *tfCoordDwgToWin )(double Xdwg, double Ydwg, int* pXwin, int* pYwin);
typedef BOOL (VC_API *tfLenWinToDwg   )(int Lwin, double* pLdwg);
typedef BOOL (VC_API *tfLenDwgToWin   )(double Ldwg, int* pLwin);
typedef BOOL (VC_API *tfSetDrawPen    )(double Width, COLORREF Color);
typedef BOOL (VC_API *tfDrawPoint     )(double X, double Y, int Type, int Size);
typedef BOOL (VC_API *tfDrawLine      )(double X1, double Y1, double X2, double Y2);
typedef BOOL (VC_API *tfDrawPolyline  )(const VLPOINT* Ver, int n_ver, BOOL bClosed);
typedef BOOL (VC_API *tfDrawPolygon   )(const VLPOINT* Ver, int n_ver, BOOL bFill, BOOL bBorder, COLORREF FillColor);
typedef BOOL (VC_API *tfDrawCircle    )(double X, double Y, double Rad);
typedef BOOL (VC_API *tfDrawArc       )(double X, double Y, double Rad, double Angle1, double Angle2);
typedef BOOL (VC_API *tfDrawEllipse   )(double X, double Y, double Rh, double Rv, double Angle);
typedef BOOL (VC_API *tfDrawBitmap    )(HBITMAP hbm, int W, int H, double X, double Y, double ResX, double ResY);
typedef BOOL (VC_API *tfDrawText      )(double X, double Y, LPCTSTR szText);
typedef BOOL (VC_API *tfDrawEntity    )(int Index, double Xbase, double Ybase, double Xins, double Yins, double Angle, double ScaleX, double ScaleY);
typedef BOOL (VC_API *tfExecute       )(int IdCmd);   // VL_CM_...
typedef BOOL (VC_API *tfSetAccKey     )(int IdCmd, int VirtKey, int Flags);
typedef BOOL (VC_API *tfClear         )(BOOL bSetDefLayout);
typedef BOOL (VC_API *tfSetFocus      )();
typedef BOOL (VC_API *tfUpdate        )();
typedef BOOL (VC_API *tfRedraw        )();
typedef BOOL (VC_API *tfReset         )();
typedef BOOL (VC_API *tfPrintSetup    )(HWND hParent);
typedef BOOL (VC_API *tfPrint         )(HDC hPrintDC, double Left, double Bottom, double Right, double Top, double ScaleX, double ScaleY, double OriginX, double OriginY);
typedef BOOL (VC_API *tfDoRaster      )(LPCTSTR szFileName, double Left, double Bottom, double Right, double Top, double Res);
typedef BOOL (VC_API *tfGetWinSize    )(HWND hWnd, int* pW, int* pH);
typedef BOOL (VC_API *tfSetTimer      )(int ID, int Elapse);
typedef BOOL (VC_API *tfKillTimer     )(int ID);
typedef double (VC_API *tfGetArea     )(double X, double Y);
typedef HWND (VC_API *tfNavCreate     )(HWND hWndParent, HWND hVecWnd, int wstyle, int X, int Y, int W, int H);
typedef BOOL (VC_API *tfNavResize     )(int X, int Y, int W, int H);
typedef BOOL (VC_API *tfNavUpdate     )();
typedef BOOL (VC_API *tfNavGetProp    )(VLNAVIGATOR* pProp);
typedef BOOL (VC_API *tfNavPutProp    )(const VLNAVIGATOR* pProp);
typedef HWND (VC_API *tfLayWinCreate  )(HWND hWndParent, int wstyle, int X, int Y, int W, int H);
typedef BOOL (VC_API *tfLayWinResize  )(int X, int Y, int W, int H);
typedef BOOL (VC_API *tfLayWinGetProp )(VLLAYWIN* pProp);
typedef BOOL (VC_API *tfLayWinPutProp )(const VLLAYWIN* pProp);
typedef BOOL (VC_API *tfEntSwap       )(int iEnt1, int iEnt2);
typedef BOOL (VC_API *tfEntToTop      )(int iEnt);
typedef BOOL (VC_API *tfEntToBottom   )(int iEnt);
typedef BOOL    (VC_API *tfPointRotate    )(double X, double Y, double Xc, double Yc, double Angle, double* pXnew, double* pYnew);
typedef LPCTSTR (VC_API *tfGetAppDir      )(LPCTSTR szFileName);
typedef LPCTSTR (VC_API *tfGetFileExt     )(LPCTSTR szFileName, LPTSTR szExt);
typedef LPCTSTR (VC_API *tfGetFileDir     )(LPCTSTR szFileName);
typedef LPCTSTR (VC_API *tfGetFileName    )(LPCTSTR szFileName);
typedef BOOL    (VC_API *tfGetSaveFileName)(HWND hParent, LPCTSTR szFilter, LPCTSTR szDefExt, LPCTSTR szDir, LPTSTR szFileName);
typedef BOOL    (VC_API *tfGetOpenFileName)(HWND hParent, LPCTSTR szFilter, LPCTSTR szDefExt, LPCTSTR szDir, LPTSTR szFileName);
typedef int     (VC_API *tfSearchFile     )(LPCTSTR szFileName, LPTSTR szFindName);

//*******************************************************************
// alloc pointers to functions
//*******************************************************************
tfGetVersion     pfGetVersion;
tfRegistration   pfRegistration;
tfSetMsgHandler  pfSetMsgHandler;
tfWndCreate      pfWndCreate;
tfWndResize      pfWndResize;
tfWndSetTitle    pfWndSetTitle;
tfWndSetMaxRect  pfWndSetMaxRect;
tfWndSetCursor   pfWndSetCursor;
tfToolBarCreate  pfToolBarCreate;
tfToolBarButton  pfToolBarButton;
tfStatBarCreate  pfStatBarCreate;
tfStatBarResize  pfStatBarResize;
tfStatBarSetText pfStatBarSetText;
tfIndicCreate    pfIndicCreate;
tfIndicDestroy   pfIndicDestroy;
tfIndicSetRange  pfIndicSetRange;
tfIndicSetPos    pfIndicSetPos;
tfIndicSetText   pfIndicSetText;
tfIndicStep      pfIndicStep;
tfDocCreate      pfDocCreate;
tfDocDelete      pfDocDelete;
tfDocSetActive   pfDocSetActive;
tfDocGetActive   pfDocGetActive;
tfDocCopy        pfDocCopy;
tfPageAdd        pfPageAdd;
tfPageDelete     pfPageDelete;
tfPageActive     pfPageActive;
tfPageCount      pfPageCount;
tfPageIndex      pfPageIndex;
tfLayerAdd       pfLayerAdd;
tfLayerDelete    pfLayerDelete;
tfLayerActive    pfLayerActive;
tfLayerCount     pfLayerCount;
tfLayerIndex     pfLayerIndex;
tfStLineAdd      pfStLineAdd;
tfStLineDelete   pfStLineDelete;
tfStLineActive   pfStLineActive;
tfStLineCount    pfStLineCount;
tfStLineIndex    pfStLineIndex;
tfStTextAdd      pfStTextAdd;
tfStTextDelete   pfStTextDelete;
tfStTextActive   pfStTextActive;
tfStTextCount    pfStTextCount;
tfStTextIndex    pfStTextIndex;
tfStTextReload   pfStTextReload;
tfStHatchAdd     pfStHatchAdd;
tfStHatchDelete  pfStHatchDelete;
tfStHatchActive  pfStHatchActive;
tfStHatchCount   pfStHatchCount;
tfStHatchIndex   pfStHatchIndex;
tfStDimAdd       pfStDimAdd;
tfStDimDelete    pfStDimDelete;
tfStDimActive    pfStDimActive;
tfStDimCount     pfStDimCount;
tfStDimIndex     pfStDimIndex;
tfStPointAdd     pfStPointAdd;
tfStPointDelete  pfStPointDelete;
tfStPointActive  pfStPointActive;
tfStPointCount   pfStPointCount;
tfStPointIndex   pfStPointIndex;
tfGrPointAdd     pfGrPointAdd;
tfGrPointDelete  pfGrPointDelete;
tfGrPointActive  pfGrPointActive;
tfGrPointCount   pfGrPointCount;
tfGrPointIndex   pfGrPointIndex;
tfViewSave       pfViewSave;
tfViewDelete     pfViewDelete;
tfViewRestore    pfViewRestore;
tfViewCount      pfViewCount;
tfViewIndex      pfViewIndex;
tfPrnRectAdd     pfPrnRectAdd;
tfPrnRectDelete  pfPrnRectDelete;
tfPrnRectCount   pfPrnRectCount;
tfPrnRectPrint   pfPrnRectPrint;
tfPrnRectAuto    pfPrnRectAuto;
tfBlockBegin     pfBlockBegin;
tfBlockAdd       pfBlockAdd;
tfBlockAddF      pfBlockAddF;
tfBlockDelete    pfBlockDelete;
tfBlockActive    pfBlockActive;
tfBlockCount     pfBlockCount;
tfBlockIndex     pfBlockIndex;
tfAddPoint       pfAddPoint;
tfAddLine        pfAddLine;
tfAddArcEx       pfAddArcEx;
tfAddCircle      pfAddCircle;
tfAddCircle3P    pfAddCircle3P;
tfAddArc         pfAddArc;
tfAddArc3P       pfAddArc3P;
tfAddEllipse     pfAddEllipse;
tfSetTextParam   pfSetTextParam;
tfSetTextParams  pfSetTextParams;
tfAddText        pfAddText;
tfPolylineBegin  pfPolylineBegin;
tfVertex         pfVertex;
tfVertexR        pfVertexR;
tfVertexF        pfVertexF;
tfVertexB        pfVertexB;
tfAddPolyline    pfAddPolyline;
tfAddBlockIns    pfAddBlockIns;
tfAddHatch       pfAddHatch;
tfAddRaster      pfAddRaster;
tfAddRect        pfAddRect;
tfAddDimHor      pfAddDimHor;
tfAddDimVer      pfAddDimVer;
tfAddDimPar      pfAddDimPar;
tfAddDimAng      pfAddDimAng;
tfAddDimRad      pfAddDimRad;
tfAddDimDiam     pfAddDimDiam;
tfAddDimOrd      pfAddDimOrd;
tfAddDwgIns      pfAddDwgIns;
tfFileNew        pfFileNew;
tfFileOpen       pfFileOpen;
tfFileLoad       pfFileLoad;
tfFileSave       pfFileSave;
tfFileList       pfFileList;
tfFileLoadMem    pfFileLoadMem;
tfFileSaveMem    pfFileSaveMem;
tfGetEntity        pfGetEntity;
tfGetBlockEntity   pfGetBlockEntity;
tfSelect           pfSelect;
tfSelectByPoint    pfSelectByPoint;
tfSelectByRect     pfSelectByRect;
tfSelectByPolygon  pfSelectByPolygon;
tfSelectByPolyline pfSelectByPolyline;
tfSelectByDist     pfSelectByDist;
tfSelectByHandle   pfSelectByHandle;
tfSelectByKey      pfSelectByKey;
tfSelectByLayer    pfSelectByLayer;
tfCbCut          pfCbCut;
tfCbCopy         pfCbCopy;
tfCbPaste        pfCbPaste;
tfCopy           pfCopy;
tfMove           pfMove;
tfRotate         pfRotate;
tfScale          pfScale;
tfMirror         pfMirror;
tfErase          pfErase;
tfExplode        pfExplode;
tfJoin           pfJoin;
tfUndo           pfUndo;
tfRedo           pfRedo;
tfPolyVerInsert  pfPolyVerInsert;
tfPolyVerDelete  pfPolyVerDelete;
tfPolyVerGet     pfPolyVerGet;
tfPolyVerSet     pfPolyVerSet;
tfGripGet        pfGripGet;
tfGripSet        pfGripSet;
tfGripMove       pfGripMove;
tfPropGet        pfPropGet;
tfPropGetInt     pfPropGetInt;
tfPropGetDbl     pfPropGetDbl;
tfPropPut        pfPropPut;
tfPropPutInt     pfPropPutInt;
tfPropPutDbl     pfPropPutDbl;
tfZoom           pfZoom;
tfZoomRect       pfZoomRect;
tfZoomPan        pfZoomPan;
tfCoordWinToDwg  pfCoordWinToDwg;
tfCoordDwgToWin  pfCoordDwgToWin;
tfLenWinToDwg    pfLenWinToDwg;
tfLenDwgToWin    pfLenDwgToWin;
tfSetDrawPen     pfSetDrawPen;
tfDrawPoint      pfDrawPoint;
tfDrawLine       pfDrawLine;
tfDrawPolyline   pfDrawPolyline;
tfDrawPolygon    pfDrawPolygon;
tfDrawCircle     pfDrawCircle;
tfDrawArc        pfDrawArc;
tfDrawEllipse    pfDrawEllipse;
tfDrawText       pfDrawText;
tfDrawBitmap     pfDrawBitmap;
tfDrawEntity     pfDrawEntity;
tfExecute        pfExecute;
tfSetAccKey      pfSetAccKey;
tfClear          pfClear;
tfSetFocus       pfSetFocus;
tfUpdate         pfUpdate;
tfRedraw         pfRedraw;
tfReset          pfReset;
tfPrintSetup     pfPrintSetup;
tfPrint          pfPrint;
tfDoRaster       pfDoRaster;
tfGetWinSize     pfGetWinSize;
tfSetTimer       pfSetTimer;     
tfKillTimer      pfKillTimer;
tfGetArea        pfGetArea;
tfNavCreate      pfNavCreate;
tfNavResize      pfNavResize;
tfNavUpdate      pfNavUpdate;
tfNavGetProp     pfNavGetProp;
tfNavPutProp     pfNavPutProp;
tfLayWinCreate   pfLayWinCreate;
tfLayWinResize   pfLayWinResize;
tfLayWinGetProp  pfLayWinGetProp;
tfLayWinPutProp  pfLayWinPutProp;
tfEntSwap        pfEntSwap;
tfEntToTop       pfEntToTop;
tfEntToBottom    pfEntToBottom;
tfPointRotate      pfPointRotate;
tfGetAppDir        pfGetAppDir;
tfGetFileExt       pfGetFileExt;
tfGetFileDir       pfGetFileDir;
tfGetFileName      pfGetFileName;
tfGetSaveFileName  pfGetSaveFileName;
tfGetOpenFileName  pfGetOpenFileName;
tfSearchFile       pfSearchFile;

static HINSTANCE ghVecLibInst=0;    // handle to library instance

//*******************************************************************
//  Get addresses of vecad.dll functions
//  This function must be called before call any VeCAD function
//*******************************************************************
BOOL vlStartup ()
{
  ghVecLibInst = LoadLibrary( "vecad52.dll" );
  if (ghVecLibInst==NULL){
    return FALSE;
  }
  pfGetVersion = (tfGetVersion) GetProcAddress( ghVecLibInst, "vlGetVersion" );
  pfRegistration = (tfRegistration) GetProcAddress( ghVecLibInst, "vlRegistration" );
  pfSetMsgHandler = (tfSetMsgHandler) GetProcAddress( ghVecLibInst, "vlSetMsgHandler" );
  pfWndCreate = (tfWndCreate) GetProcAddress( ghVecLibInst, "vlWndCreate" );
  pfWndResize = (tfWndResize) GetProcAddress( ghVecLibInst, "vlWndResize" );
  pfWndSetTitle = (tfWndSetTitle) GetProcAddress( ghVecLibInst, "vlWndSetTitle" );
  pfWndSetMaxRect = (tfWndSetMaxRect) GetProcAddress( ghVecLibInst, "vlWndSetMaxRect" );
  pfWndSetCursor = (tfWndSetCursor) GetProcAddress( ghVecLibInst, "vlWndSetCursor" );
  pfToolBarCreate = (tfToolBarCreate) GetProcAddress( ghVecLibInst, "vlToolBarCreate" );
  pfToolBarButton = (tfToolBarButton) GetProcAddress( ghVecLibInst, "vlToolBarButton" );
  pfStatBarCreate = (tfStatBarCreate) GetProcAddress( ghVecLibInst, "vlStatBarCreate" );
  pfStatBarResize = (tfStatBarResize) GetProcAddress( ghVecLibInst, "vlStatBarResize" );
  pfStatBarSetText = (tfStatBarSetText) GetProcAddress( ghVecLibInst, "vlStatBarSetText" );
  pfIndicCreate = (tfIndicCreate) GetProcAddress( ghVecLibInst, "vlIndicCreate" );
  pfIndicDestroy = (tfIndicDestroy) GetProcAddress( ghVecLibInst, "vlIndicDestroy" );
  pfIndicSetRange = (tfIndicSetRange) GetProcAddress( ghVecLibInst, "vlIndicSetRange" );
  pfIndicSetPos = (tfIndicSetPos) GetProcAddress( ghVecLibInst, "vlIndicSetPos" );
  pfIndicSetText = (tfIndicSetText) GetProcAddress( ghVecLibInst, "vlIndicSetText" );
  pfIndicStep = (tfIndicStep) GetProcAddress( ghVecLibInst, "vlIndicStep" );
  pfDocCreate = (tfDocCreate) GetProcAddress( ghVecLibInst, "vlDocCreate" );
  pfDocDelete = (tfDocDelete) GetProcAddress( ghVecLibInst, "vlDocDelete" );
  pfDocSetActive = (tfDocSetActive) GetProcAddress( ghVecLibInst, "vlDocSetActive" );
  pfDocGetActive = (tfDocGetActive) GetProcAddress( ghVecLibInst, "vlDocGetActive" );
  pfDocCopy = (tfDocCopy) GetProcAddress( ghVecLibInst, "vlDocCopy" );
  pfPageAdd = (tfPageAdd) GetProcAddress( ghVecLibInst, "vlPageAdd" );
  pfPageDelete = (tfPageDelete) GetProcAddress( ghVecLibInst, "vlPageDelete" );
  pfPageActive = (tfPageActive) GetProcAddress( ghVecLibInst, "vlPageActive" );
  pfPageCount = (tfPageCount) GetProcAddress( ghVecLibInst, "vlPageCount" );
  pfPageIndex = (tfPageIndex) GetProcAddress( ghVecLibInst, "vlPageIndex" );
  pfLayerAdd = (tfLayerAdd) GetProcAddress( ghVecLibInst, "vlLayerAdd" );
  pfLayerDelete = (tfLayerDelete) GetProcAddress( ghVecLibInst, "vlLayerDelete" );
  pfLayerActive = (tfLayerActive) GetProcAddress( ghVecLibInst, "vlLayerActive" );
  pfLayerCount = (tfLayerCount) GetProcAddress( ghVecLibInst, "vlLayerCount" );
  pfLayerIndex = (tfLayerIndex) GetProcAddress( ghVecLibInst, "vlLayerIndex" );
  pfStLineAdd = (tfStLineAdd) GetProcAddress( ghVecLibInst, "vlStLineAdd" );
  pfStLineDelete = (tfStLineDelete) GetProcAddress( ghVecLibInst, "vlStLineDelete" );
  pfStLineActive = (tfStLineActive) GetProcAddress( ghVecLibInst, "vlStLineActive" );
  pfStLineCount = (tfStLineCount) GetProcAddress( ghVecLibInst, "vlStLineCount" );
  pfStLineIndex = (tfStLineIndex) GetProcAddress( ghVecLibInst, "vlStLineIndex" );
  pfStTextAdd = (tfStTextAdd) GetProcAddress( ghVecLibInst, "vlStTextAdd" );
  pfStTextDelete = (tfStTextDelete) GetProcAddress( ghVecLibInst, "vlStTextDelete" );
  pfStTextActive = (tfStTextActive) GetProcAddress( ghVecLibInst, "vlStTextActive" );
  pfStTextCount = (tfStTextCount) GetProcAddress( ghVecLibInst, "vlStTextCount" );
  pfStTextIndex = (tfStTextIndex) GetProcAddress( ghVecLibInst, "vlStTextIndex" );
  pfStTextReload = (tfStTextReload) GetProcAddress( ghVecLibInst, "vlStTextReload" );
  pfStHatchAdd = (tfStHatchAdd) GetProcAddress( ghVecLibInst, "vlStHatchAdd" );
  pfStHatchDelete = (tfStHatchDelete) GetProcAddress( ghVecLibInst, "vlStHatchDelete" );
  pfStHatchActive = (tfStHatchActive) GetProcAddress( ghVecLibInst, "vlStHatchActive" );
  pfStHatchCount = (tfStHatchCount) GetProcAddress( ghVecLibInst, "vlStHatchCount" );
  pfStHatchIndex = (tfStHatchIndex) GetProcAddress( ghVecLibInst, "vlStHatchIndex" );
  pfStDimAdd = (tfStDimAdd) GetProcAddress( ghVecLibInst, "vlStDimAdd" );
  pfStDimDelete = (tfStDimDelete) GetProcAddress( ghVecLibInst, "vlStDimDelete" );
  pfStDimActive = (tfStDimActive) GetProcAddress( ghVecLibInst, "vlStDimActive" );
  pfStDimCount = (tfStDimCount) GetProcAddress( ghVecLibInst, "vlStDimCount" );
  pfStDimIndex = (tfStDimIndex) GetProcAddress( ghVecLibInst, "vlStDimIndex" );
  pfStPointAdd = (tfStPointAdd) GetProcAddress( ghVecLibInst, "vlStPointAdd" );
  pfStPointDelete = (tfStPointDelete) GetProcAddress( ghVecLibInst, "vlStPointDelete" );
  pfStPointActive = (tfStPointActive) GetProcAddress( ghVecLibInst, "vlStPointActive" );
  pfStPointCount = (tfStPointCount) GetProcAddress( ghVecLibInst, "vlStPointCount" );
  pfStPointIndex = (tfStPointIndex) GetProcAddress( ghVecLibInst, "vlStPointIndex" );
  pfGrPointAdd = (tfGrPointAdd) GetProcAddress( ghVecLibInst, "vlGrPointAdd" );
  pfGrPointDelete = (tfGrPointDelete) GetProcAddress( ghVecLibInst, "vlGrPointDelete" );
  pfGrPointActive = (tfGrPointActive) GetProcAddress( ghVecLibInst, "vlGrPointActive" );
  pfGrPointCount = (tfGrPointCount) GetProcAddress( ghVecLibInst, "vlGrPointCount" );
  pfGrPointIndex = (tfGrPointIndex) GetProcAddress( ghVecLibInst, "vlGrPointIndex" );
  pfViewSave = (tfViewSave) GetProcAddress( ghVecLibInst, "vlViewSave" );
  pfViewDelete = (tfViewDelete) GetProcAddress( ghVecLibInst, "vlViewDelete" );
  pfViewRestore = (tfViewRestore) GetProcAddress( ghVecLibInst, "vlViewRestore" );
  pfViewCount = (tfViewCount) GetProcAddress( ghVecLibInst, "vlViewCount" );
  pfViewIndex = (tfViewIndex) GetProcAddress( ghVecLibInst, "vlViewIndex" );
  pfPrnRectAdd = (tfPrnRectAdd) GetProcAddress( ghVecLibInst, "vlPrnRectAdd" );
  pfPrnRectDelete = (tfPrnRectDelete) GetProcAddress( ghVecLibInst, "vlPrnRectDelete" );
  pfPrnRectCount = (tfPrnRectCount) GetProcAddress( ghVecLibInst, "vlPrnRectCount" );
  pfPrnRectPrint = (tfPrnRectPrint) GetProcAddress( ghVecLibInst, "vlPrnRectPrint" );
  pfPrnRectAuto = (tfPrnRectAuto) GetProcAddress( ghVecLibInst, "vlPrnRectAuto" );
  pfBlockBegin = (tfBlockBegin) GetProcAddress( ghVecLibInst, "vlBlockBegin" );
  pfBlockAdd = (tfBlockAdd) GetProcAddress( ghVecLibInst, "vlBlockAdd" );
  pfBlockAddF = (tfBlockAddF) GetProcAddress( ghVecLibInst, "vlBlockAddF" );
  pfBlockDelete = (tfBlockDelete) GetProcAddress( ghVecLibInst, "vlBlockDelete" );
  pfBlockActive = (tfBlockActive) GetProcAddress( ghVecLibInst, "vlBlockActive" );
  pfBlockCount = (tfBlockCount) GetProcAddress( ghVecLibInst, "vlBlockCount" );
  pfBlockIndex = (tfBlockIndex) GetProcAddress( ghVecLibInst, "vlBlockIndex" );
  pfAddPoint = (tfAddPoint) GetProcAddress( ghVecLibInst, "vlAddPoint" );
  pfAddLine = (tfAddLine) GetProcAddress( ghVecLibInst, "vlAddLine" );
  pfAddArcEx = (tfAddArcEx) GetProcAddress( ghVecLibInst, "vlAddArcEx" );
  pfAddCircle = (tfAddCircle) GetProcAddress( ghVecLibInst, "vlAddCircle" );
  pfAddCircle3P = (tfAddCircle3P) GetProcAddress( ghVecLibInst, "vlAddCircle3P" );
  pfAddArc = (tfAddArc) GetProcAddress( ghVecLibInst, "vlAddArc" );
  pfAddArc3P = (tfAddArc3P) GetProcAddress( ghVecLibInst, "vlAddArc3P" );
  pfAddEllipse = (tfAddEllipse) GetProcAddress( ghVecLibInst, "vlAddEllipse" );
  pfSetTextParam = (tfSetTextParam) GetProcAddress( ghVecLibInst, "vlSetTextParam" );
  pfSetTextParams = (tfSetTextParams) GetProcAddress( ghVecLibInst, "vlSetTextParams" );
  pfAddText = (tfAddText) GetProcAddress( ghVecLibInst, "vlAddText" );
  pfPolylineBegin = (tfPolylineBegin) GetProcAddress( ghVecLibInst, "vlPolylineBegin" );
  pfVertex = (tfVertex) GetProcAddress( ghVecLibInst, "vlVertex" );
  pfVertexR = (tfVertexR) GetProcAddress( ghVecLibInst, "vlVertexR" );
  pfVertexF = (tfVertexF) GetProcAddress( ghVecLibInst, "vlVertexF" );
  pfVertexB = (tfVertexB) GetProcAddress( ghVecLibInst, "vlVertexB" );
  pfAddPolyline = (tfAddPolyline) GetProcAddress( ghVecLibInst, "vlAddPolyline" );
  pfAddBlockIns = (tfAddBlockIns) GetProcAddress( ghVecLibInst, "vlAddBlockIns" );
  pfAddHatch = (tfAddHatch) GetProcAddress( ghVecLibInst, "vlAddHatch" );
  pfAddRaster = (tfAddRaster) GetProcAddress( ghVecLibInst, "vlAddRaster" );
  pfAddRect = (tfAddRect) GetProcAddress( ghVecLibInst, "vlAddRect" );
  pfAddDimHor = (tfAddDimHor) GetProcAddress( ghVecLibInst, "vlAddDimHor" );
  pfAddDimVer = (tfAddDimVer) GetProcAddress( ghVecLibInst, "vlAddDimVer" );
  pfAddDimPar = (tfAddDimPar) GetProcAddress( ghVecLibInst, "vlAddDimPar" );
  pfAddDimAng = (tfAddDimAng) GetProcAddress( ghVecLibInst, "vlAddDimAng" );
  pfAddDimRad = (tfAddDimRad) GetProcAddress( ghVecLibInst, "vlAddDimRad" );
  pfAddDimDiam = (tfAddDimDiam) GetProcAddress( ghVecLibInst, "vlAddDimDiam" );
  pfAddDimOrd = (tfAddDimOrd) GetProcAddress( ghVecLibInst, "vlAddDimOrd" );
  pfAddDwgIns =  (tfAddDwgIns) GetProcAddress( ghVecLibInst, "vlAddDwgIns" );
  pfFileNew = (tfFileNew) GetProcAddress( ghVecLibInst, "vlFileNew" );
  pfFileOpen = (tfFileOpen) GetProcAddress( ghVecLibInst, "vlFileOpen" );
  pfFileLoad = (tfFileLoad) GetProcAddress( ghVecLibInst, "vlFileLoad" );
  pfFileList = (tfFileList) GetProcAddress( ghVecLibInst, "vlFileList" );
  pfFileSave = (tfFileSave) GetProcAddress( ghVecLibInst, "vlFileSave" );
  pfFileLoadMem = (tfFileLoadMem) GetProcAddress( ghVecLibInst, "vlFileLoadMem" );
  pfFileSaveMem = (tfFileSaveMem) GetProcAddress( ghVecLibInst, "vlFileSaveMem" );
  pfGetEntity = (tfGetEntity) GetProcAddress( ghVecLibInst, "vlGetEntity" );
  pfGetBlockEntity = (tfGetBlockEntity) GetProcAddress( ghVecLibInst, "vlGetBlockEntity" );
  pfSelect = (tfSelect) GetProcAddress( ghVecLibInst, "vlSelect" );
  pfSelectByPoint = (tfSelectByPoint) GetProcAddress( ghVecLibInst, "vlSelectByPoint" );
  pfSelectByRect = (tfSelectByRect) GetProcAddress( ghVecLibInst, "vlSelectByRect" );
  pfSelectByPolygon = (tfSelectByPolygon) GetProcAddress( ghVecLibInst, "vlSelectByPolygon" );
  pfSelectByPolyline = (tfSelectByPolyline) GetProcAddress( ghVecLibInst, "vlSelectByPolyline" );
  pfSelectByDist = (tfSelectByDist) GetProcAddress( ghVecLibInst, "vlSelectByDist" );
  pfSelectByHandle = (tfSelectByHandle) GetProcAddress( ghVecLibInst, "vlSelectByHandle" );
  pfSelectByKey = (tfSelectByKey) GetProcAddress( ghVecLibInst, "vlSelectByKey" );
  pfSelectByLayer = (tfSelectByLayer) GetProcAddress( ghVecLibInst, "vlSelectByLayer" );
  pfCbCut = (tfCbCut) GetProcAddress( ghVecLibInst, "vlCbCut" );
  pfCbCopy = (tfCbCopy) GetProcAddress( ghVecLibInst, "vlCbCopy" );
  pfCbPaste = (tfCbPaste) GetProcAddress( ghVecLibInst, "vlCbPaste" );
  pfCopy = (tfCopy) GetProcAddress( ghVecLibInst, "vlCopy" );
  pfMove = (tfMove) GetProcAddress( ghVecLibInst, "vlMove" );
  pfRotate = (tfRotate) GetProcAddress( ghVecLibInst, "vlRotate" );
  pfScale = (tfScale) GetProcAddress( ghVecLibInst, "vlScale" );
  pfMirror = (tfMirror) GetProcAddress( ghVecLibInst, "vlMirror" );
  pfErase = (tfErase) GetProcAddress( ghVecLibInst, "vlErase" );
  pfExplode = (tfExplode) GetProcAddress( ghVecLibInst, "vlExplode" );
  pfJoin = (tfJoin) GetProcAddress( ghVecLibInst, "vlJoin" );
  pfUndo = (tfUndo) GetProcAddress( ghVecLibInst, "vlUndo" );
  pfRedo = (tfRedo) GetProcAddress( ghVecLibInst, "vlRedo" );
  pfPolyVerInsert = (tfPolyVerInsert) GetProcAddress( ghVecLibInst, "vlPolyVerInsert" );
  pfPolyVerDelete = (tfPolyVerDelete) GetProcAddress( ghVecLibInst, "vlPolyVerDelete" );
  pfPolyVerGet = (tfPolyVerGet) GetProcAddress( ghVecLibInst, "vlPolyVerGet" );
  pfPolyVerSet = (tfPolyVerSet) GetProcAddress( ghVecLibInst, "vlPolyVerSet" );
  pfGripGet = (tfGripGet) GetProcAddress( ghVecLibInst, "vlGripGet" );
  pfGripSet = (tfGripSet) GetProcAddress( ghVecLibInst, "vlGripSet" );
  pfGripMove = (tfGripMove) GetProcAddress( ghVecLibInst, "vlGripMove" );
  pfPropGet = (tfPropGet) GetProcAddress( ghVecLibInst, "vlPropGet" );
  pfPropGetInt = (tfPropGetInt) GetProcAddress( ghVecLibInst, "vlPropGetInt" );
  pfPropGetDbl = (tfPropGetDbl) GetProcAddress( ghVecLibInst, "vlPropGetDbl" );
  pfPropPut = (tfPropPut) GetProcAddress( ghVecLibInst, "vlPropPut" );
  pfPropPutInt = (tfPropPutInt) GetProcAddress( ghVecLibInst, "vlPropPutInt" );
  pfPropPutDbl = (tfPropPutDbl) GetProcAddress( ghVecLibInst, "vlPropPutDbl" );
  pfZoom = (tfZoom) GetProcAddress( ghVecLibInst, "vlZoom" );
  pfZoomRect = (tfZoomRect) GetProcAddress( ghVecLibInst, "vlZoomRect" );
  pfZoomPan = (tfZoomPan) GetProcAddress( ghVecLibInst, "vlZoomPan" );
  pfCoordWinToDwg = (tfCoordWinToDwg) GetProcAddress( ghVecLibInst, "vlCoordWinToDwg" );
  pfCoordDwgToWin = (tfCoordDwgToWin) GetProcAddress( ghVecLibInst, "vlCoordDwgToWin" );
  pfLenWinToDwg = (tfLenWinToDwg) GetProcAddress( ghVecLibInst, "vlLenWinToDwg" );
  pfLenDwgToWin = (tfLenDwgToWin) GetProcAddress( ghVecLibInst, "vlLenDwgToWin" );
  pfSetDrawPen = (tfSetDrawPen) GetProcAddress( ghVecLibInst, "vlSetDrawPen" );
  pfDrawPoint = (tfDrawPoint) GetProcAddress( ghVecLibInst, "vlDrawPoint" );
  pfDrawLine = (tfDrawLine) GetProcAddress( ghVecLibInst, "vlDrawLine" );
  pfDrawPolyline = (tfDrawPolyline) GetProcAddress( ghVecLibInst, "vlDrawPolyline" );
  pfDrawPolygon = (tfDrawPolygon) GetProcAddress( ghVecLibInst, "vlDrawPolygon" );
  pfDrawCircle = (tfDrawCircle) GetProcAddress( ghVecLibInst, "vlDrawCircle" );
  pfDrawArc = (tfDrawArc) GetProcAddress( ghVecLibInst, "vlDrawArc" );
  pfDrawEllipse = (tfDrawEllipse) GetProcAddress( ghVecLibInst, "vlDrawEllipse" );
  pfDrawText = (tfDrawText) GetProcAddress( ghVecLibInst, "vlDrawText" );
  pfDrawBitmap = (tfDrawBitmap ) GetProcAddress( ghVecLibInst, "vlDrawBitmap" );
  pfDrawEntity = (tfDrawEntity) GetProcAddress( ghVecLibInst, "vlDrawEntity" );
  pfExecute = (tfExecute) GetProcAddress( ghVecLibInst, "vlExecute" );
  pfSetAccKey = (tfSetAccKey) GetProcAddress( ghVecLibInst, "vlSetAccKey" );
  pfClear = (tfClear) GetProcAddress( ghVecLibInst, "vlClear" );
  pfSetFocus = (tfSetFocus) GetProcAddress( ghVecLibInst, "vlSetFocus" );
  pfUpdate = (tfUpdate) GetProcAddress( ghVecLibInst, "vlUpdate" );
  pfRedraw = (tfRedraw) GetProcAddress( ghVecLibInst, "vlRedraw" );
  pfReset = (tfReset) GetProcAddress( ghVecLibInst, "vlReset" );
  pfPrintSetup = (tfPrintSetup) GetProcAddress( ghVecLibInst, "vlPrintSetup" );
  pfPrint = (tfPrint) GetProcAddress( ghVecLibInst, "vlPrint" );
  pfDoRaster = (tfDoRaster) GetProcAddress( ghVecLibInst, "vlDoRaster" );
  pfGetWinSize = (tfGetWinSize) GetProcAddress( ghVecLibInst, "vlGetWinSize" );
  pfSetTimer = (tfSetTimer) GetProcAddress( ghVecLibInst, "vlSetTimer" );
  pfKillTimer = (tfKillTimer) GetProcAddress( ghVecLibInst, "vlKillTimer" );
  pfGetArea = (tfGetArea) GetProcAddress( ghVecLibInst, "vlGetArea" );
  pfNavCreate = (tfNavCreate) GetProcAddress( ghVecLibInst, "vlNavCreate" );
  pfNavResize = (tfNavResize) GetProcAddress( ghVecLibInst, "vlNavResize" );
  pfNavUpdate = (tfNavUpdate) GetProcAddress( ghVecLibInst, "vlNavUpdate" );
  pfNavGetProp = (tfNavGetProp) GetProcAddress( ghVecLibInst, "vlNavGetProp" );
  pfNavPutProp = (tfNavPutProp) GetProcAddress( ghVecLibInst, "vlNavPutProp" );
  pfLayWinCreate = (tfLayWinCreate) GetProcAddress( ghVecLibInst, "vlLayWinCreate" );
  pfLayWinResize = (tfLayWinResize) GetProcAddress( ghVecLibInst, "vlLayWinResize" );
  pfLayWinGetProp = (tfLayWinGetProp) GetProcAddress( ghVecLibInst, "vlLayWinGetProp" );
  pfLayWinPutProp = (tfLayWinPutProp) GetProcAddress( ghVecLibInst, "vlLayWinPutProp" );
  pfEntSwap = (tfEntSwap) GetProcAddress( ghVecLibInst, "vlEntSwap" );
  pfEntToTop = (tfEntToTop) GetProcAddress( ghVecLibInst, "vlEntToTop" );
  pfEntToBottom = (tfEntToBottom) GetProcAddress( ghVecLibInst, "vlEntToBottom" );
  pfPointRotate = (tfPointRotate) GetProcAddress( ghVecLibInst, "gmPointRotate" );
  pfGetAppDir = (tfGetAppDir) GetProcAddress( ghVecLibInst, "vuGetAppDir" );
  pfGetFileExt = (tfGetFileExt) GetProcAddress( ghVecLibInst, "vuGetFileExt" );
  pfGetFileDir = (tfGetFileDir) GetProcAddress( ghVecLibInst, "vuGetFileDir" );
  pfGetFileName = (tfGetFileName) GetProcAddress( ghVecLibInst, "vuGetFileName" );
  pfGetSaveFileName = (tfGetSaveFileName) GetProcAddress( ghVecLibInst, "vuGetSaveFileName" );
  pfGetOpenFileName = (tfGetOpenFileName) GetProcAddress( ghVecLibInst, "vuGetOpenFileName" );
  pfSearchFile  = (tfSearchFile) GetProcAddress( ghVecLibInst, "vuSearchFile" );
  return TRUE;
}


//*******************************************************************
//  Free the library vecad.dll
//  Must be called before quit from application
//*******************************************************************
VOID vlCleanup ()
{
	if(!ghVecLibInst)	return;
  	FreeLibrary( ghVecLibInst );
  	ghVecLibInst = 0;
}


//*******************************************************************
// Realization of VeCAD functions
//*******************************************************************

//-----------------------------------------------
int VC_API vlGetVersion ()
{
  return (*pfGetVersion)();
}

//-----------------------------------------------
BOOL VC_API vlRegistration (int code)
{
  return (*pfRegistration) (code);
}

//-----------------------------------------------
BOOL VC_API vlSetMsgHandler (DWGPROC pfDwgProc)
{
  return (*pfSetMsgHandler)( pfDwgProc );
}

//-----------------------------------------------
HWND VC_API vlWndCreate (HWND hParent, int Style, int X, int Y, int W, int H)
{
  return (*pfWndCreate)( hParent, Style, X, Y, W, H );
}

//-----------------------------------------------
BOOL VC_API vlWndResize (HWND hVecWnd, int X, int Y, int W, int H)
{
  return (*pfWndResize)( hVecWnd, X, Y, W, H );
}

//-----------------------------------------------
BOOL VC_API vlWndSetTitle (HWND hVecWnd, LPCTSTR pTitle)
{
  return (*pfWndSetTitle)( hVecWnd, pTitle );
}

//-----------------------------------------------
BOOL VC_API vlWndSetMaxRect (HWND hVecWnd, const RECT* pRect)
{
  return (*pfWndSetMaxRect)( hVecWnd, pRect );
}

//-----------------------------------------------
BOOL VC_API vlWndSetCursor (HWND hVecWnd, HCURSOR hCursor)
{
  return (*pfWndSetCursor)( hVecWnd, hCursor );
}

//-----------------------------------------------
HWND VC_API vlToolBarCreate (HWND hwParent, int Id, int X, int Y, int W, int H, int* pW, int* pH)
{
  return (*pfToolBarCreate)( hwParent, Id, X, Y, W, H, pW, pH );
}

//-----------------------------------------------
BOOL VC_API vlToolBarButton (int Id)
{
  return (*pfToolBarButton)( Id );
}

//-----------------------------------------------
HWND VC_API vlStatBarCreate (HWND hwParent, int* pH)
{
  return (*pfStatBarCreate)( hwParent, pH );
}

//-----------------------------------------------
BOOL VC_API vlStatBarResize ()
{
  return (*pfStatBarResize)();
}

//-----------------------------------------------
BOOL VC_API vlStatBarSetText (int iPart, LPCTSTR szText)
{
  return (*pfStatBarSetText)( iPart, szText );
}

//-----------------------------------------------
BOOL VC_API vlIndicCreate (HWND Parent, LPCTSTR szTitle)
{
  return (*pfIndicCreate)( Parent, szTitle );
}

//-----------------------------------------------
BOOL VC_API vlIndicDestroy ()
{
  return (*pfIndicDestroy)();
}

//-----------------------------------------------
BOOL VC_API vlIndicSetRange (int nFrom,int nTo)
{
  return (*pfIndicSetRange)( nFrom, nTo );
}

//-----------------------------------------------
BOOL VC_API vlIndicSetPos (int iPos)
{
  return (*pfIndicSetPos)( iPos );
}

//-----------------------------------------------
BOOL VC_API vlIndicSetText (LPCTSTR szText)
{
  return (*pfIndicSetText)( szText );
}

//-----------------------------------------------
BOOL VC_API vlIndicStep ()
{
  return (*pfIndicStep)();
}

//-----------------------------------------------
int VC_API vlDocCreate (HWND hwVec)
{
  return (*pfDocCreate)( hwVec );
}

//-----------------------------------------------
BOOL VC_API vlDocDelete (int iDwg)
{
  return (*pfDocDelete)( iDwg );
}

//-----------------------------------------------
int VC_API vlDocSetActive (int iDwg)
{
  return (*pfDocSetActive )( iDwg );
}

//-----------------------------------------------
int VC_API vlDocGetActive ()
{
  return (*pfDocGetActive )();
}

//-----------------------------------------------
BOOL VC_API vlDocCopy (int iDwgSrc,int iDwgDest,int Mode)
{
  return (*pfDocCopy)( iDwgSrc, iDwgDest, Mode );
}

//-----------------------------------------------
int VC_API vlPageAdd (LPCTSTR szName, int Size, int Orient, int W, int H)
{
  return (*pfPageAdd)( szName, Size, Orient, W, H );
}

//-----------------------------------------------
BOOL VC_API vlPageDelete (int Index)
{
  return (*pfPageDelete)( Index );
}

//-----------------------------------------------
int VC_API vlPageActive (int Mode, int Index)
{
  return (*pfPageActive)( Mode, Index );
}

//-----------------------------------------------
int VC_API vlPageCount ()
{
  return (*pfPageCount)();
}

//-----------------------------------------------
int VC_API vlPageIndex (LPCTSTR szName, int ID)
{
  return (*pfPageIndex)( szName, ID );
}

//-----------------------------------------------
int VC_API vlLayerAdd (LPCTSTR szName, double LineWidth, COLORREF LineColor, COLORREF FillColor)
{
  return (*pfLayerAdd)( szName, LineWidth, LineColor, FillColor );
}

//-----------------------------------------------
BOOL VC_API vlLayerDelete (int Index)
{
  return (*pfLayerDelete)( Index );
}

//-----------------------------------------------
int VC_API vlLayerActive (int Index)
{
  return (*pfLayerActive)( Index );
}

//-----------------------------------------------
int VC_API vlLayerCount ()
{
  return (*pfLayerCount)();
}

//-----------------------------------------------
int VC_API vlLayerIndex (LPCTSTR szName, int ID)
{
  return (*pfLayerIndex)( szName, ID );
}

//-----------------------------------------------
int VC_API vlStLineAdd (LPCTSTR szName, LPCTSTR szDesc)
{
  return (*pfStLineAdd)( szName, szDesc );
}

//-----------------------------------------------
BOOL VC_API vlStLineDelete (int Index)
{
  return (*pfStLineDelete)( Index );
}

//-----------------------------------------------
int VC_API vlStLineActive (int Index)
{
  return (*pfStLineActive)( Index );
}

//-----------------------------------------------
int VC_API vlStLineCount ()
{
  return (*pfStLineCount)();
}

//-----------------------------------------------
int VC_API vlStLineIndex (LPCTSTR szName, int ID)
{
  return (*pfStLineIndex)( szName, ID );
}

//-----------------------------------------------
int VC_API vlStTextAdd (LPCTSTR szName, LPCTSTR szFont, double Width, double Oblique, int Prec, BOOL Filled, BOOL Bold)
{
  return (*pfStTextAdd)( szName, szFont, Width, Oblique, Prec, Filled, Bold );
}

//-----------------------------------------------
BOOL VC_API vlStTextDelete (int Index)
{
  return (*pfStTextDelete)( Index );
}

//-----------------------------------------------
int VC_API vlStTextActive (int Index)
{
  return (*pfStTextActive)( Index );
}

//-----------------------------------------------
int VC_API vlStTextCount ()
{
  return (*pfStTextCount)();
}

//-----------------------------------------------
int VC_API vlStTextIndex (LPCTSTR szName, int ID)
{
  return (*pfStTextIndex)( szName, ID );
}

//-----------------------------------------------
BOOL VC_API vlStTextReload ()
{
  return (*pfStTextReload)();
}

//-----------------------------------------------
int VC_API vlStHatchAdd (LPCTSTR szName, LPCTSTR szDesc)
{
  return (*pfStHatchAdd)( szName, szDesc );
}

//-----------------------------------------------
BOOL VC_API vlStHatchDelete (int Index)
{
  return (*pfStHatchDelete)( Index );
}

//-----------------------------------------------
int VC_API vlStHatchActive (int Index)
{
  return (*pfStHatchActive)( Index );
}

//-----------------------------------------------
int VC_API vlStHatchCount ()
{
  return (*pfStHatchCount)();
}

//-----------------------------------------------
int VC_API vlStHatchIndex (LPCTSTR szName, int ID)
{
  return (*pfStHatchIndex)( szName, ID );
}

//-----------------------------------------------
int VC_API vlStDimAdd (LPCTSTR szName)
{
  return (*pfStDimAdd)( szName );
}

//-----------------------------------------------
BOOL VC_API vlStDimDelete (int Index)
{
  return (*pfStDimDelete)( Index );
}

//-----------------------------------------------
int VC_API vlStDimActive (int Index)
{
  return (*pfStDimActive)( Index );
}

//-----------------------------------------------
int VC_API vlStDimCount ()
{
  return (*pfStDimCount)();
}

//-----------------------------------------------
int VC_API vlStDimIndex (LPCTSTR szName, int ID)
{
  return (*pfStDimIndex)( szName, ID );
}

//-----------------------------------------------
int VC_API vlStPointAdd (LPCTSTR szName)
{
  return (*pfStPointAdd)( szName );
}

//-----------------------------------------------
BOOL VC_API vlStPointDelete (int Index)
{
  return (*pfStPointDelete)( Index );
}

//-----------------------------------------------
int VC_API vlStPointActive (int Index)
{
  return (*pfStPointActive)( Index );
}

//-----------------------------------------------
int VC_API vlStPointCount ()
{
  return (*pfStPointCount)();
}

//-----------------------------------------------
int VC_API vlStPointIndex (LPCTSTR szName, int ID)
{
  return (*pfStPointIndex)( szName, ID );
}

//-----------------------------------------------
int VC_API vlGrPointAdd (LPCTSTR szName)
{
  return (*pfGrPointAdd)( szName );
}

//-----------------------------------------------
BOOL VC_API vlGrPointDelete (int Index)
{
  return (*pfGrPointDelete)( Index );
}

//-----------------------------------------------
int VC_API vlGrPointActive (int Index)
{
  return (*pfGrPointActive)( Index );
}

//-----------------------------------------------
int VC_API vlGrPointCount ()
{
  return (*pfGrPointCount)();
}

//-----------------------------------------------
int VC_API vlGrPointIndex (LPCTSTR szName, int ID)
{
  return (*pfGrPointIndex)( szName, ID );
}

//-----------------------------------------------
int VC_API vlViewSave (LPCTSTR szName)
{
  return (*pfViewSave)( szName );
}

//-----------------------------------------------
BOOL VC_API vlViewDelete (int Index)
{
  return (*pfViewDelete)( Index );
}

//-----------------------------------------------
int VC_API vlViewRestore (int Index)
{
  return (*pfViewRestore)( Index );
}

//-----------------------------------------------
int VC_API vlViewCount ()
{
  return (*pfViewCount)();
}

//-----------------------------------------------
int VC_API vlViewIndex (LPCTSTR szName, int ID)
{
  return (*pfViewIndex)( szName, ID );
}

//-----------------------------------------------
int VC_API vlPrnRectAdd (double X, double Y, double W, double H, double Angle)
{
  return (*pfPrnRectAdd)( X, Y, W, H, Angle );
}

//-----------------------------------------------
BOOL VC_API vlPrnRectDelete (int Index)
{
  return (*pfPrnRectDelete)( Index );
}

//-----------------------------------------------
int VC_API vlPrnRectCount ()
{
  return (*pfPrnRectCount)();
}

//-----------------------------------------------
BOOL VC_API vlPrnRectPrint (int Index, HDC hPrintDC, double ScaleX, double ScaleY, double OriginX, double OriginY)
{
  return (*pfPrnRectPrint)( Index, hPrintDC, ScaleX, ScaleY, OriginX, OriginY );
}

//-----------------------------------------------
int VC_API vlPrnRectAuto (double Width, double Height)
{
  return (*pfPrnRectAuto)( Width, Height );
}

//-----------------------------------------------
BOOL VC_API vlBlockBegin ()
{
  return (*pfBlockBegin)();
}

//-----------------------------------------------
int VC_API vlBlockAdd (LPCTSTR szName, double x, double y)
{
  return (*pfBlockAdd)( szName, x, y );
}

//-----------------------------------------------
int VC_API vlBlockAddF (LPCTSTR szFileName, LPCTSTR szBlockName)
{
  return (*pfBlockAddF)( szFileName, szBlockName );
}

//-----------------------------------------------
BOOL VC_API vlBlockDelete (int Index)
{
  return (*pfBlockDelete)( Index );
}

//-----------------------------------------------
int VC_API vlBlockActive (int Index)
{
  return (*pfBlockActive)( Index );
}

//-----------------------------------------------
int VC_API vlBlockCount ()
{
  return (*pfBlockCount)();
}

//-----------------------------------------------
int VC_API vlBlockIndex (LPCTSTR szName, int ID)
{
  return (*pfBlockIndex)( szName, ID );
}

//-----------------------------------------------
int VC_API vlAddPoint (double X, double Y)
{
  return (*pfAddPoint)( X, Y );
}

//-----------------------------------------------
int VC_API vlAddLine (double X1, double Y1, double X2, double Y2)
{
  return (*pfAddLine)( X1, Y1, X2, Y2 );
}

//-----------------------------------------------
int VC_API vlAddArcEx (double X, double Y, double Rh, double Rv, double Ang0, double AngArc, double AngRot)
{
  return (*pfAddArcEx)( X, Y, Rh, Rv, Ang0, AngArc, AngRot );
}

//-----------------------------------------------
int VC_API vlAddCircle (double X, double Y, double Rad)
{
  return (*pfAddCircle)( X, Y, Rad );
}

//-----------------------------------------------
int VC_API vlAddCircle3P (double X1, double Y1, double X2, double Y2, double X3, double Y3)
{
  return (*pfAddCircle3P)( X1, Y1, X2, Y2, X3, Y3 );
}

//-----------------------------------------------
int VC_API vlAddArc (double X, double Y, double Rad, double Ang1, double Ang2)
{
  return (*pfAddArc)( X, Y, Rad, Ang1, Ang2 );
}

//-----------------------------------------------
int VC_API vlAddArc3P (double X1, double Y1, double X2, double Y2, double X3, double Y3)
{
  return (*pfAddArc3P)( X1, Y1, X2, Y2, X3, Y3 );
}

//-----------------------------------------------
int VC_API vlAddEllipse (double X, double Y, double Rh, double Rv, double Angle)
{
  return (*pfAddEllipse)( X, Y, Rh, Rv, Angle );
}

//-----------------------------------------------
BOOL VC_API vlSetTextParam (int Mode, double Var)
{
  return (*pfSetTextParam)( Mode, Var );
}

//-----------------------------------------------
BOOL VC_API vlSetTextParams (int Align, double Height, double Angle, double ScaleW, double Oblique, double HInter, double VInter)
{
  return (*pfSetTextParams)( Align, Height, Angle, ScaleW, Oblique, HInter, VInter);
}

//-----------------------------------------------
int VC_API vlAddText (double X, double Y, LPCTSTR szStr)
{
  return (*pfAddText)( X, Y, szStr );
}

//-----------------------------------------------
BOOL VC_API vlPolylineBegin ()
{
  return (*pfPolylineBegin)();
}

//-----------------------------------------------
BOOL VC_API vlVertex (double X, double Y)
{
  return (*pfVertex)( X, Y );
}

//-----------------------------------------------
BOOL VC_API vlVertexR (double X, double Y, double Radius)
{
  return (*pfVertexR)( X, Y, Radius );
}

//-----------------------------------------------
BOOL VC_API vlVertexF (double X, double Y, BOOL bOnCurve)
{
  return (*pfVertexF)( X, Y, bOnCurve );
}

//-----------------------------------------------
BOOL VC_API vlVertexB (double X, double Y, double Bulge)
{
  return (*pfVertexB)( X, Y, Bulge);
}

//-----------------------------------------------
int VC_API vlAddPolyline (int SmoothType, BOOL bClosed)
{
  return (*pfAddPolyline)( SmoothType, bClosed);
}

//-----------------------------------------------
int VC_API vlAddBlockIns (int Index, double X, double Y, double Angle, double Xscale, double Yscale)
{
  return (*pfAddBlockIns)( Index, X, Y, Angle, Xscale, Yscale );
}

//-----------------------------------------------
int VC_API vlAddHatch (int Index, double Scale, double Angle)
{
  return (*pfAddHatch)( Index, Scale, Angle);
}

//-----------------------------------------------
int VC_API vlAddRaster (LPCTSTR FileName, double X, double Y, double ResH, double ResV)
{
  return (*pfAddRaster)( FileName, X, Y, ResH, ResV );
}

//-----------------------------------------------
int VC_API vlAddRect (double X, double Y, double W, double H, double Ang, double Rad)
{
  return (*pfAddRect)( X, Y, W, H, Ang, Rad);
}

//-----------------------------------------------
int VC_API vlAddDimHor (double X1, double Y1, double X2, double Y2, double Y)
{
  return (*pfAddDimHor)( X1, Y1, X2, Y2, Y);
}

//-----------------------------------------------
int VC_API vlAddDimVer (double X1, double Y1, double X2, double Y2, double X)
{
  return (*pfAddDimVer)( X1, Y1, X2, Y2, X);
}

//-----------------------------------------------
int VC_API vlAddDimPar (double X1, double Y1, double X2, double Y2, double Off)
{
  return (*pfAddDimPar)( X1, Y1, X2, Y2, Off);
}

//-----------------------------------------------
int VC_API vlAddDimAng (double Xcen, double Ycen, double X1, double Y1, double X2, double Y2, double Off)
{
  return (*pfAddDimAng)( Xcen, Ycen, X1, Y1, X2, Y2, Off);
}

//-----------------------------------------------
int VC_API vlAddDimRad (double Xcen, double Ycen, double Xrad, double Yrad, double Off)
{
  return (*pfAddDimRad)( Xcen, Ycen, Xrad, Yrad, Off);
}

//-----------------------------------------------
int VC_API vlAddDimDiam (double Xcen, double Ycen, double Xrad, double Yrad)
{
  return (*pfAddDimDiam)( Xcen, Ycen, Xrad, Yrad);
}

//-----------------------------------------------
int VC_API vlAddDimOrd (double X, double Y, double Xtxt, double Ytxt, BOOL bYord)
{
  return (*pfAddDimOrd)( X, Y, Xtxt, Ytxt, bYord);
}

//-----------------------------------------------
int VC_API vlAddDwgIns (LPCTSTR FileName, double X, double Y, double Angle, double ScaleH, double ScaleV, int iPage)
{
  return (*pfAddDwgIns)( FileName, X, Y, Angle, ScaleH, ScaleV, iPage );
}

//-----------------------------------------------
int VC_API vlFileNew (HWND hwVec, LPCTSTR szTemplate)
{
  return (*pfFileNew)( hwVec, szTemplate);
}

//-----------------------------------------------
int VC_API vlFileOpen (HWND hwVec, LPCTSTR szFileName)
{
  return (*pfFileOpen)( hwVec, szFileName);
}

//-----------------------------------------------
BOOL VC_API vlFileLoad (int Mode, LPCTSTR szFileName)
{
  return (*pfFileLoad)( Mode, szFileName);
}

//-----------------------------------------------
BOOL VC_API vlFileSave (int Mode, LPCTSTR szFileName)
{
  return (*pfFileSave)( Mode, szFileName);
}

//-----------------------------------------------
BOOL VC_API vlFileList (HWND hwParent)
{
  return (*pfFileList)( hwParent );
}

//-----------------------------------------------
BOOL VC_API vlFileLoadMem (void* pMem)
{
  return (*pfFileLoadMem)( pMem );
}

//-----------------------------------------------
int VC_API vlFileSaveMem (void* pMem, int MaxSize)
{
  return (*pfFileSaveMem)( pMem, MaxSize);
}

//-----------------------------------------------
int VC_API vlGetEntity (int Mode, int Prm1, int Prm2)
{
  return (*pfGetEntity)( Mode, Prm1, Prm2);
}

//-----------------------------------------------
int VC_API vlGetBlockEntity (int iBlock, int Counter)
{
  return (*pfGetBlockEntity)( iBlock, Counter );
}

//-----------------------------------------------
BOOL VC_API vlSelect (BOOL bSelect, int Index)
{
  return (*pfSelect)( bSelect, Index);
}

//-----------------------------------------------
int VC_API vlSelectByPoint (BOOL bSelect, double X, double Y, double Delta)
{
  return (*pfSelectByPoint)( bSelect, X, Y, Delta );
}

//-----------------------------------------------
int VC_API vlSelectByRect (BOOL bSelect, double Left, double Bottom, double Right, double Top, BOOL Cross)
{
  return (*pfSelectByRect)( bSelect, Left, Bottom, Right, Top, Cross);
}

//-----------------------------------------------
int VC_API vlSelectByPolygon (BOOL bSelect, const VLPOINT* Ver, int nver, BOOL bCross)
{
  return (*pfSelectByPolygon)( bSelect, Ver, nver, bCross );
}

//-----------------------------------------------
int VC_API vlSelectByPolyline (BOOL bSelect, const VLPOINT* Ver, int nver)
{
  return (*pfSelectByPolyline)( bSelect, Ver, nver );
}

//-----------------------------------------------
int VC_API vlSelectByDist (BOOL bSelect, double X, double Y, double Dist, BOOL bCross)
{
  return (*pfSelectByDist)( bSelect, X, Y, Dist, bCross );
}

//-----------------------------------------------
int VC_API vlSelectByHandle (BOOL bSelect, int Handle)
{
  return (*pfSelectByHandle)( bSelect, Handle );
}

//-----------------------------------------------
int VC_API vlSelectByKey (BOOL bSelect, int Key)
{
  return (*pfSelectByKey)( bSelect, Key );
}

//-----------------------------------------------
int VC_API vlSelectByLayer (BOOL bSelect, int Index)
{
  return (*pfSelectByLayer)( bSelect, Index );
}

//-----------------------------------------------
BOOL VC_API vlCbCut ()
{
  return (*pfCbCut)();
}

//-----------------------------------------------
BOOL VC_API vlCbCopy ()
{
  return (*pfCbCopy)();
}

//-----------------------------------------------
BOOL VC_API vlCbPaste (double X, double Y)
{
  return (*pfCbPaste)( X, Y);
}

//-----------------------------------------------
int VC_API vlCopy (int iObj, double dx, double dy)
{
  return (*pfCopy)( iObj, dx, dy);
}

//-----------------------------------------------
BOOL VC_API vlMove (int iObj, double dx, double dy)
{
  return (*pfMove)( iObj, dx, dy);
}

//-----------------------------------------------
BOOL VC_API vlRotate (int iObj, double X, double Y, double Angle)
{
  return (*pfRotate)( iObj, X, Y, Angle);
}

//-----------------------------------------------
BOOL VC_API vlScale (int iObj, double X, double Y, double Scale)
{
  return (*pfScale)( iObj, X, Y, Scale);
}

//-----------------------------------------------
BOOL VC_API vlMirror (int iObj, double X1, double Y1, double X2, double Y2)
{
  return (*pfMirror)( iObj, X1, Y1, X2, Y2);
}

//-----------------------------------------------
BOOL VC_API vlErase (int iObj)
{
  return (*pfErase)( iObj );
}

//-----------------------------------------------
BOOL VC_API vlExplode (int iObj)
{
  return (*pfExplode)( iObj );
}

//-----------------------------------------------
BOOL VC_API vlJoin (double Delta)
{
  return (*pfJoin)( Delta );
}

//-----------------------------------------------
BOOL VC_API vlUndo ()
{
  return (*pfUndo)();
}

//-----------------------------------------------
BOOL VC_API vlRedo ()
{
  return (*pfRedo)();
}

//-----------------------------------------------
BOOL VC_API vlPolyVerInsert (int iEnt, int iVer)
{
  return (*pfPolyVerInsert)( iEnt, iVer );
}

//-----------------------------------------------
BOOL VC_API vlPolyVerDelete (int iEnt, int iVer)
{
  return (*pfPolyVerDelete)( iEnt, iVer );
}

//-----------------------------------------------
BOOL VC_API vlPolyVerGet (int iEnt, int iVer, double* pX, double* pY, double* pPrm)
{
  return (*pfPolyVerGet)( iEnt, iVer, pX, pY, pPrm );
}

//-----------------------------------------------
BOOL VC_API vlPolyVerSet (int iEnt, int iVer, double X, double Y, double Prm)
{
  return (*pfPolyVerSet)( iEnt, iVer, X, Y, Prm );
}

//-----------------------------------------------
BOOL VC_API vlGripGet (int iObj, int iGrip, double* pX, double* pY)
{
  return (*pfGripGet)( iObj, iGrip, pX, pY );
}

//-----------------------------------------------
BOOL VC_API vlGripSet (int iObj, int iGrip, double X, double Y)
{
  return (*pfGripSet)( iObj, iGrip, X, Y );
}

//-----------------------------------------------
BOOL VC_API vlGripMove (int iObj, int iGrip, double dx, double dy)
{
  return (*pfGripMove)( iObj, iGrip, dx, dy );
}

//-----------------------------------------------
int VC_API vlPropGet (int PropID, int iObj, void* pData)
{
  return (*pfPropGet)( PropID, iObj, pData );
}

//-----------------------------------------------
int VC_API vlPropGetInt (int PropID, int iObj)
{
  return (*pfPropGetInt)( PropID, iObj );
}

//-----------------------------------------------
double VC_API vlPropGetDbl (int PropID, int iObj)
{
  return (*pfPropGetDbl)( PropID, iObj );
}

//-----------------------------------------------
int VC_API vlPropPut (int PropID, int iObj, void* pData)
{
  return (*pfPropPut)( PropID, iObj, pData );
}

//-----------------------------------------------
int VC_API vlPropPutInt (int PropID, int iObj, int Value)
{
  return (*pfPropPutInt)( PropID, iObj, Value );
}

//-----------------------------------------------
int VC_API vlPropPutDbl (int PropID, int iObj, double Value)
{
  return (*pfPropPutDbl)( PropID, iObj, Value );
}

//-----------------------------------------------
BOOL VC_API vlZoom (double Scale)
{
  return (*pfZoom)( Scale );
}

//-----------------------------------------------
BOOL VC_API vlZoomRect (double Left, double Bottom, double Right, double Top)
{
  return (*pfZoomRect)( Left, Bottom, Right, Top );
}

//-----------------------------------------------
BOOL VC_API vlZoomPan (double dx, double dy)
{
  return (*pfZoomPan)( dx, dy );
}

//-----------------------------------------------
BOOL VC_API vlCoordWinToDwg (int Xwin, int Ywin, double* pXdwg, double* pYdwg)
{
  return (*pfCoordWinToDwg)( Xwin, Ywin, pXdwg, pYdwg );
}

//-----------------------------------------------
BOOL VC_API vlCoordDwgToWin (double Xdwg, double Ydwg, int* pXwin, int* pYwin)
{
  return (*pfCoordDwgToWin)( Xdwg, Ydwg, pXwin, pYwin );
}

//-----------------------------------------------
BOOL VC_API vlLenWinToDwg (int Lwin, double* pLdwg)
{
  return (*pfLenWinToDwg)( Lwin, pLdwg );
}

//-----------------------------------------------
BOOL VC_API vlLenDwgToWin (double Ldwg, int* pLwin)
{
  return (*pfLenDwgToWin)( Ldwg, pLwin );
}

//-----------------------------------------------
BOOL VC_API vlSetDrawPen (double Width, COLORREF Color)
{
  return (*pfSetDrawPen)(Width, Color);
}

//-----------------------------------------------
BOOL VC_API vlDrawPoint (double X, double Y, int Type, int Size)
{
  return (*pfDrawPoint)( X, Y, Type, Size);
}

//-----------------------------------------------
BOOL VC_API vlDrawLine (double X1, double Y1, double X2, double Y2)
{
  return (*pfDrawLine)( X1, Y1, X2, Y2 );
}

//-----------------------------------------------
BOOL VC_API vlDrawPolyline (const VLPOINT* Ver, int n_ver, BOOL bClosed)
{
  return (*pfDrawPolyline)( Ver, n_ver, bClosed );
}

//-----------------------------------------------
BOOL VC_API vlDrawPolygon (const VLPOINT* Ver, int n_ver, BOOL bFill, BOOL bBorder, COLORREF FillColor)
{
  return (*pfDrawPolygon)( Ver, n_ver, bFill, bBorder, FillColor);
}

//-----------------------------------------------
BOOL VC_API vlDrawCircle (double X, double Y, double Rad)
{
  return (*pfDrawCircle)( X, Y, Rad );
}

//-----------------------------------------------
BOOL VC_API vlDrawArc (double X, double Y, double Rad, double Angle1, double Angle2)
{
  return (*pfDrawArc)( X, Y, Rad, Angle1, Angle2 );
}

//-----------------------------------------------
BOOL VC_API vlDrawEllipse (double X, double Y, double Rh, double Rv, double Angle)
{
  return (*pfDrawEllipse)( X, Y, Rh, Rv, Angle );
}

//-----------------------------------------------
BOOL VC_API vlDrawText (double X, double Y, LPCTSTR szText)
{
  return (*pfDrawText)( X, Y, szText );
}

//-----------------------------------------------
BOOL VC_API vlDrawBitmap (HBITMAP hbm, int W, int H, double X, double Y, double ResX, double ResY)
{
  return (*pfDrawBitmap)(hbm,W,H,X,Y,ResX,ResY);
}

//-----------------------------------------------
BOOL VC_API vlDrawEntity (int Index, double Xbase, double Ybase, double Xins, double Yins, double Angle, double ScaleX, double ScaleY)
{
  return (*pfDrawEntity)( Index, Xbase, Ybase, Xins, Yins, Angle, ScaleX, ScaleY );
}

//-----------------------------------------------
BOOL VC_API vlExecute (int IdCmd)
{
  return (*pfExecute)( IdCmd );
}

//-----------------------------------------------
BOOL VC_API vlSetAccKey (int IdCmd, int VirtKey, int Flags)
{
  return (*pfSetAccKey)( IdCmd, VirtKey, Flags );
}

//-----------------------------------------------
BOOL VC_API vlClear (BOOL bSetDefLayout)
{
  return (*pfClear)( bSetDefLayout );
}

//-----------------------------------------------
BOOL VC_API vlSetFocus ()
{
  return (*pfSetFocus)();
}

//-----------------------------------------------
BOOL VC_API vlUpdate ()
{
  return (*pfUpdate)();
}

//-----------------------------------------------
BOOL VC_API vlRedraw ()
{
  return (*pfRedraw)();
}

//-----------------------------------------------
BOOL VC_API vlReset ()
{
  return (*pfReset)();
}

//-----------------------------------------------
BOOL VC_API vlPrintSetup (HWND hParent)
{
  return (*pfPrintSetup)( hParent );
}

//-----------------------------------------------
BOOL VC_API vlPrint (HDC hPrintDC, double Left, double Bottom, double Right, double Top, double ScaleX, double ScaleY, double OriginX, double OriginY)
{
  return (*pfPrint)( hPrintDC, Left, Bottom, Right, Top, ScaleX, ScaleY, OriginX, OriginY );
}

//-----------------------------------------------
BOOL VC_API vlDoRaster (LPCTSTR szFileName, double Left, double Bottom, double Right, double Top, double Res)
{
  return (*pfDoRaster)(szFileName,Left,Bottom,Right,Top,Res);
}

//-----------------------------------------------
BOOL VC_API vlGetWinSize (HWND hWnd, int* pW, int* pH)
{
  return (*pfGetWinSize)( hWnd, pW, pH);
}

//-----------------------------------------------
BOOL VC_API vlSetTimer (int ID, int Elapse)
{
  return (*pfSetTimer)( ID, Elapse );
}

//-----------------------------------------------
BOOL VC_API vlKillTimer (int ID)
{
  return (*pfKillTimer)( ID );
}

//-----------------------------------------------
double VC_API vlGetArea (double X, double Y)
{
  return (*pfGetArea)( X, Y );
}

//-----------------------------------------------
HWND VC_API vlNavCreate (HWND hWndParent, HWND hVecWnd, int Style, int X, int Y, int W, int H)
{
  return (*pfNavCreate)( hWndParent, hVecWnd, Style, X, Y, W, H );
}

//-----------------------------------------------
BOOL VC_API vlNavResize (int X, int Y, int W, int H)
{
  return (*pfNavResize)( X, Y, W, H );
}

//-----------------------------------------------
BOOL VC_API vlNavUpdate ()
{
  return (*pfNavUpdate)();
}


//-----------------------------------------------
BOOL VC_API vlNavGetProp  (VLNAVIGATOR* pProp)
{
  return (*pfNavGetProp)( pProp );
}

//-----------------------------------------------
BOOL VC_API vlNavPutProp  (const VLNAVIGATOR* pProp)
{
  return (*pfNavPutProp)( pProp );
}

//-----------------------------------------------
HWND VC_API vlLayWinCreate (HWND hWndParent, int Style, int X, int Y, int W, int H)
{
  return (*pfLayWinCreate)( hWndParent, Style, X, Y, W, H );
}

//-----------------------------------------------
BOOL VC_API vlLayWinResize (int X, int Y, int W, int H)
{
  return (*pfLayWinResize)( X, Y, W, H );
}

//-----------------------------------------------
BOOL VC_API vlLayWinGetProp  (VLLAYWIN* pProp)
{
  return (*pfLayWinGetProp)( pProp );
}

//-----------------------------------------------
BOOL VC_API vlLayWinPutProp  (const VLLAYWIN* pProp)
{
  return (*pfLayWinPutProp)( pProp );
}

//-----------------------------------------------
BOOL VC_API vlEntSwap (int iEnt1, int iEnt2)
{
  return (*pfEntSwap)( iEnt1, iEnt2 );
}
//-----------------------------------------------
BOOL VC_API vlEntToTop (int iEnt)
{
  return (*pfEntToTop)( iEnt );
}
//-----------------------------------------------
BOOL VC_API vlEntToBottom (int iEnt)
{
  return (*pfEntToBottom)( iEnt );
}

//-----------------------------------------------
BOOL VC_API gmPointRotate (double X, double Y, double Xc, double Yc, double Angle, double* pXnew, double* pYnew)
{
  return (*pfPointRotate)( X, Y, Xc, Yc, Angle, pXnew, pYnew );
}

//-----------------------------------------------
LPCTSTR VC_API vuGetAppDir (LPCTSTR szFileName)
{
  return (*pfGetAppDir)( szFileName );
}

//-----------------------------------------------
LPCTSTR VC_API vuGetFileExt (LPCTSTR szFileName, LPTSTR szExt)
{
  return (*pfGetFileExt)( szFileName, szExt );
}

//-----------------------------------------------
LPCTSTR VC_API vuGetFileDir (LPCTSTR szFileName)
{
  return (*pfGetFileDir)( szFileName );
}

//-----------------------------------------------
LPCTSTR VC_API vuGetFileName (LPCTSTR szFileName)
{
  return (*pfGetFileName)( szFileName );
}

//-----------------------------------------------
BOOL VC_API vuGetSaveFileName (HWND hParent, LPCTSTR szFilter, LPCTSTR szDefExt, LPCTSTR szDir, LPTSTR szFileName)
{
  return (*pfGetSaveFileName)( hParent, szFilter, szDefExt, szDir, szFileName );
}

//-----------------------------------------------
BOOL VC_API vuGetOpenFileName (HWND hParent, LPCTSTR szFilter, LPCTSTR szDefExt, LPCTSTR szDir, LPTSTR szFileName)
{
  return (*pfGetOpenFileName)( hParent, szFilter, szDefExt, szDir, szFileName );
}

//-----------------------------------------------
int VC_API vuSearchFile (LPCTSTR szFileName, LPTSTR szFindName)
{
  return (*pfSearchFile)( szFileName, szFindName );
}

