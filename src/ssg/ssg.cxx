
#include "ssgLocal.h"

sgMat4 _ssgOpenGLAxisSwapMatrix =
{
  {  1.0f,  0.0f,  0.0f,  0.0f },
  {  0.0f,  0.0f, -1.0f,  0.0f },
  {  0.0f,  1.0f,  0.0f,  0.0f },
  {  0.0f,  0.0f,  0.0f,  1.0f }
} ;

sgVec3 _tfVertex000   = { 0.0f, 0.0f, 0.0f } ;
sgVec4 _tfColourWhite = { 1.0f, 1.0f, 1.0f, 1.0f } ;
sgVec3 _tfNormalUp    = { 0.0f, 0.0f, 1.0f } ;
sgVec2 _tfTexCoord00  = { 0.0f, 0.0f } ;

sgFrustum *_ssgCurrentFrustum  = NULL ;
sgMat4     _ssgCurrentCameraMatrix ;
int        _ssgCurrentCullFace = TRUE ;
int        _ssgOverrideTexture = FALSE ;
int        _ssgIsHotTest       = FALSE ;

ssgLight   _ssgLights [ 8 ] ;

int         _ssgFrameCounter = 0 ;

int ssgGetFrameCounter () { return _ssgFrameCounter ; }
void ssgSetFrameCounter ( int fc ) { _ssgFrameCounter = fc ; }

char *ssgGetVersion ()
{
#ifdef VERSION
  return VERSION ;
#else
  return "Unknown" ;
#endif
}

void ssgDelete ( ssgBranch *br )
{
  if ( br == NULL )
    return ;

  br -> removeAllKids () ;
  delete br ;
}

ssgLight *ssgGetLight ( int i )
{
  return &_ssgLights [ i ] ;
}

void ssgGetCameraPosition ( sgVec3 pos )
{
  sgCopyVec3 ( pos, _ssgCurrentCameraMatrix [ 3 ] ) ;
}

void ssgOverrideTexture ( int on_off )
{
  _ssgOverrideTexture = on_off ;
}

void ssgInit ()
{
  ssgTexturePath ( "." ) ;
  ssgModelPath   ( "." ) ;

  _ssgCurrentFrustum = new sgFrustum ;
  _ssgCurrentFrustum -> setNearFar ( 1.0, 10000.0 ) ;
  _ssgCurrentFrustum -> setFOV     ( 60.0, 45.0 ) ;

  sgMakeIdentMat4 ( _ssgCurrentCameraMatrix ) ;

  _ssgLights [ 0 ] . setID ( 0 ) ;
  _ssgLights [ 0 ] . on    () ;

  for ( int i = 1 ; i < 8 ; i++ )
  {
    _ssgLights [ i ] . setID ( i ) ;
    _ssgLights [ i ] . off   () ;
  }

  _ssgCurrentCullFace = TRUE ;
  glEnable ( GL_CULL_FACE ) ;
  
  _ssgInitState () ;
}


void ssgSetNearFar ( float n, float f )
{
  _ssgCurrentFrustum -> setNearFar ( n, f ) ;
}


void ssgSetFOV ( float w, float h )
{
  _ssgCurrentFrustum -> setFOV ( w, h ) ;
}


void ssgSetCamera ( sgMat4 mat )
{
  sgMat4 viewmat ;


  sgTransposeNegateMat4 ( viewmat, mat ) ;

  sgCopyMat4      ( _ssgCurrentCameraMatrix, _ssgOpenGLAxisSwapMatrix ) ;
  sgPreMultMat4   ( _ssgCurrentCameraMatrix, viewmat ) ;
}


void ssgSetCamera ( sgCoord *coord )
{
  sgMat4 viewmat, mat ;

  sgMakeCoordMat4 ( mat, coord ) ;
  sgTransposeNegateMat4 ( viewmat, mat ) ;

  sgCopyMat4      ( _ssgCurrentCameraMatrix, _ssgOpenGLAxisSwapMatrix ) ;
  sgPreMultMat4   ( _ssgCurrentCameraMatrix, viewmat ) ;
}


void _ssgLoadProjectionMatrix ( sgFrustum *f )
{
  glLoadIdentity () ;
  glFrustum ( f -> getLeft() , f -> getRight(),
              f -> getBot () , f -> getTop  (),
              f -> getNear() , f -> getFar  () ) ;
}


void _ssgLoadModelViewMatrix ( sgMat4 mat )
{
  glLoadMatrixf ( (float *) mat ) ;
}


void ssgCullAndDraw ( ssgRoot *r )
{
  if ( _ssgCurrentFrustum == NULL )
  {
    fprintf ( stderr, "You forgot to call ssgInit()!\n" ) ;
    exit ( 1 ) ;
  }

  _ssgFrameCounter++ ;

  ssgForceBasicState () ;

  glMatrixMode ( GL_PROJECTION ) ;
  _ssgLoadProjectionMatrix ( _ssgCurrentFrustum ) ;

  glMatrixMode ( GL_MODELVIEW ) ;
  glLoadIdentity () ;

  int i ;

  for ( i = 0 ; i < 8 ; i++ )
    if ( _ssgLights [ i ] . isHeadlight () )
      _ssgLights [ i ] . setup () ;

  _ssgLoadModelViewMatrix  ( _ssgCurrentCameraMatrix ) ;

  for ( i = 0 ; i < 8 ; i++ )
    if ( ! _ssgLights [ i ] . isHeadlight () )
      _ssgLights [ i ] . setup () ;

  r -> cull ( _ssgCurrentFrustum, _ssgCurrentCameraMatrix, TRUE ) ;

  _ssgDrawDList () ;

  glMatrixMode ( GL_MODELVIEW ) ;
  glLoadIdentity () ;
}

char *_ssgModelPath = NULL ;
char *_ssgTexturePath = NULL ;

void ssgModelPath ( char *s )
{
  delete _ssgModelPath ;
  _ssgModelPath = new char [ strlen ( s ) + 1 ] ;
  strcpy ( _ssgModelPath, s ) ;
}

void ssgTexturePath ( char *s )
{
  delete _ssgTexturePath ;
  _ssgTexturePath = new char [ strlen ( s ) + 1 ] ;
  strcpy ( _ssgTexturePath, s ) ;
}


char *ssgBase         ::getTypeName (void) { return "ssgBase"          ; }
char *ssgTexture      ::getTypeName (void) { return "ssgTexture"       ; }
char *ssgState        ::getTypeName (void) { return "ssgState"         ; }
char *ssgSimpleState  ::getTypeName (void) { return "ssgSimpleState"   ; }
char *ssgStateSelector::getTypeName (void) { return "ssgStateSelector" ; }
char *ssgEntity       ::getTypeName (void) { return "ssgEntity"        ; }
char *ssgLeaf         ::getTypeName (void) { return "ssgLeaf"          ; }
char *ssgVTable       ::getTypeName (void) { return "ssgVTable"        ; }
char *ssgBranch       ::getTypeName (void) { return "ssgBranch"        ; }
char *ssgSelector     ::getTypeName (void) { return "ssgSelector"      ; }
char *ssgRangeSelector::getTypeName (void) { return "ssgRangeSelector" ; }
char *ssgTimedSelector::getTypeName (void) { return "ssgTimedSelector" ; }
char *ssgBaseTransform::getTypeName (void) { return "ssgBaseTransform" ; }
char *ssgTransform    ::getTypeName (void) { return "ssgTransform"     ; }
char *ssgTexTrans     ::getTypeName (void) { return "ssgTexTrans"      ; }
char *ssgCutout       ::getTypeName (void) { return "ssgCutout"        ; }
char *ssgRoot         ::getTypeName (void) { return "ssgRoot"          ; }

