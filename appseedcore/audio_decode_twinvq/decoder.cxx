/* (c)Copyright 1996-2000 NTT Cyber Space Laboratories */
/*                Released on 2000.09.06 by N. Iwakami */
/*                Modified on 2000.09.22 by N. Iwakami */

#include "StdAfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

#include "twinvq.h"
#include "tvqdec.h"
#include "bfile.h"
#include "bstream.h"
#include "HeaderManager.h"

/*----------------------------------------------------------------------------*/
/* static variables                                                           */
/*----------------------------------------------------------------------------*/
static int FF_DEMO  = 0;  // switch for FF demonstration (overrides REW_DEMO)
static int REW_DEMO = 0;  // switch for REW demonstration
static const int WAVE_DATA_OFFSET = 44;

// ファイルタイプ関連の定義
static enum {
	fileTypeWav = 0,
	fileTypeRaw,
} fileTypeNumber;

static char *fileTypeName[] = {	// ファイルタイプ名、fileType フラグと連動している。
	"wav",
	"raw",
	NULL
};

/*----------------------------------------------------------------------------*/
/* definitions                                                                */
/*----------------------------------------------------------------------------*/
#define INIT_ERR_DISP_MBOX 1
#define DISPLAY_PROGRESS 0
#define strOnOff(x) ((x)==0 ? "OFF" : "ON")
#define TEST_PROGRAM_VERSION "2.3.0.02 (open version), API-C, HD2.0"
#define COPYRIGHT            "Copyright (C) 1996-2000 NTT Cyber Space Laboratories."

/***************************************/
/* STATIC FUNCTIONS FOR INITIALIZATION */
/***************************************/
/*----------------------------------------------------------------------------*/
/* Name:        NegociateAndGetFileNames()                                    */
/* Description: negociate with user and get input and output file names       */
/* Return:      (int) return 1 errors or returns 0                            */
/* Access:      static                                                        */
/*----------------------------------------------------------------------------*/
static
int NegociateAndGetFileNames( char *namein, char *nameout )
{
	printf("\n");
	printf("Bitstream file name?\t");
	scanf("%s", namein);
	printf("Audio data file name?\t");
	scanf("%s", nameout);

	return 0;
}

static
void usage( char *comname )
{
	fprintf( stderr, "Usage: %s [--version] [-t <wav|raw>] <cwfile> <outfile> [ff/rew]\n", comname );
}

/*----------------------------------------------------------------------------*/
/* Name:        ReceiveArguments()                                            */
/* Description: receive arguments and get file names and FF/REW request       */
/* Return:      (int) returns 1 when errors or returns 0                      */
/* Access:      static                                                        */
/*----------------------------------------------------------------------------*/
static int check_iarg( int iarg, int argc, char *comname )
{
	if ( iarg >= argc ) {
		if ( comname ) {
			usage( comname );
		}
		return 1;
	}
	return 0;
}

static
int ReceiveArguments(int  argc,
					 char *argv[],
					 char *namein,
					 char *nameout,
					 int  *ff_demo,
					 int  *rew_demo,
					 int  *fileType)
{
	
	*fileType = fileTypeWav;
	
	// check number of arguments
	if ( argc > 1 && strstr( argv[1], "--version" ) ){
		char moduleVersion[256];
		TvqGetModuleVersion( moduleVersion );
		printf( "TwinVQ test decoder version %s,\nusing TwinVQ decoder module version %s\n", TEST_PROGRAM_VERSION, moduleVersion );
		printf("\n%s\n", COPYRIGHT );
		return 1;
	}
	
	if (argc < 2){
		usage( argv[0] );
		return 1;
	}

	// get options
	int iarg = 0;
	while ( ++iarg < argc && argv[iarg][0]=='-' ) {
		switch ( argv[iarg][1] ) {
		case 't':
			{
				if ( check_iarg( ++iarg, argc, argv[0] ) ) return 1;
				int ifile=0;
				while ( fileTypeName[ifile] ) {
					if ( strcmp ( argv[iarg], fileTypeName[ifile] ) == 0 ) {
						*fileType = ifile;
						break;
					}
					++ifile;
				}
				if ( fileTypeName[ifile] == NULL ) {
					usage( argv[0] );
					return 1;
				}
			}
			break;
		default:
			usage( argv[0] );
			return 1;
		}
	}
	
	// get input and output filename
	sprintf( namein, "%s", argv[iarg] );  // input bitstream file name
	if ( check_iarg ( ++iarg, argc, argv[0] ) ) return 1;
	sprintf( nameout, "%s", argv[iarg] ); // output audio data file name

	// get file extention, if there's not, create one.
	char* extention = strpbrk( nameout, "." );
	if ( extention == NULL ) {
		sprintf( nameout, "%s.%s", argv[iarg], fileTypeName[*fileType] );
		extention = strpbrk( nameout, "." );
	}

	// get file type
	if ( strcmp(extention, ".wav")==0 || strcmp(extention, ".WAV")==0 ) {
		*fileType = fileTypeWav;
	}
	else{
		*fileType = fileTypeRaw;
	}

	// FF and REW demo mode
	if ( check_iarg ( ++iarg, argc, NULL ) ) return 0;
	if (strcmp(argv[iarg], "ff") == 0){
		*ff_demo = 1;
	}
	else if (strcmp(argv[iarg], "rew") == 0){
		*rew_demo = 1;
	}

	return 0;
}

/*----------------------------------------------------------------------------*/
/* Name:        OpenFiles()                                                   */
/* Description: opens input and output files                                  */
/* Return:      (int) returns 1 when errors or returns 0                      */
/* Access:      static                                                        */
/*----------------------------------------------------------------------------*/
static
int OpenFiles( char *namein, BFILE **bfp_cw, char *nameout, FILE **fp_o, char *command_name )
{
	// open input bitstream file
//	if ( (*bfp_cw=bopen(namein,"rb")) == NULL ){
//		fprintf(stderr, "%s: %s: File not found.\n", command_name, namein );
//		return 1;
//	}

	// open output audio data file
	if ( (*fp_o=fopen(nameout,"wb")) == NULL ){
		fprintf(stderr, "%s: %s: File open error\n", command_name, nameout );
		return 1;
	}

	return 0;
}

/*----------------------------------------------------------------------------*/
/* Name:        GetTextInfo()                                                 */
/* Description: ヘッダマネージャから標準文字列チャンク情報を取得する          */
/* Return:      (int) 取得に成功すれば 0 失敗したら 1                         */
/* Access:      static                                                        */
/*----------------------------------------------------------------------------*/
static
int GetTextInfo( char *data, std::string ID, CHeaderManager *theManager )
{
	try {
		CStringChunk stringChunk = theManager->GetPrimaryChunk( ID );
		sprintf( data, "%s", stringChunk.GetString().c_str() );
	}

	catch (CHeaderManager::err_FailGetChunk) { // チャンクがなかった場合
		sprintf( data, "" );
		return 1;
	}

	return 0;
}

/*--------------------------------------------------------------------------------------*/
/* Name:        TvqGetStandardChunkINfo()                                               */
/* Description: theManager から標準チャンクの情報を取得し、setupInfo のメンバに格納する */
/* Return:      (int) 取得に成功すれば 0 失敗したら 1                                   */
/* Access:      static                                                                  */
/*--------------------------------------------------------------------------------------*/
static
int TvqGetStandardChunkInfo ( CHeaderManager* theManager, headerInfo* setupInfo )
{
	// TwinVQ ID を取得する。
	sprintf( setupInfo->ID, "%s", theManager->GetID().c_str() );

	// COMM チャンクの情報を取得する
	try {
		CCommChunk commChunk( theManager->GetPrimaryChunk("COMM") );
		setupInfo->channelMode = commChunk.GetChannelMode();
		setupInfo->bitRate = commChunk.GetBitRate();
		setupInfo->samplingRate = commChunk.GetSamplingRate();
		setupInfo->securityLevel = commChunk.GetSecurityLevel();
	}
	catch (CHeaderManager::err_FailGetChunk) {
		std::cerr << "no COMM chunk" << std::endl;
		return 1;
	}

	// 標準文字列チャンクの情報を取得する
	GetTextInfo( setupInfo->Name, "NAME", theManager );
	GetTextInfo( setupInfo->Auth, "AUTH", theManager );
	GetTextInfo( setupInfo->Comt, "COMT", theManager );
	GetTextInfo( setupInfo->Cpyr, "(c) ", theManager );
	GetTextInfo( setupInfo->File, "FILE", theManager );

	// DSIZチャンクの情報を得る
	try {
		CDsizChunk dsizChunk( theManager->GetPrimaryChunk("DSIZ") );
		setupInfo->Dsiz = dsizChunk.GetInt();
	}
	catch (CHeaderManager::err_FailGetChunk) {
		setupInfo->Dsiz = 0;
	}


	return 0;
}

/*----------------------------------------------------------------------------*/
/* Name:        DisplayExtendedHeaderInfo()                                   */
/* Description: 拡張チャンクの情報を取得する。実装は一例。                    */
/* Return:      エラーがあれば１、なければ０                                  */
/* Access:      static                                                        */
/*----------------------------------------------------------------------------*/
static
int DisplayExtendedHeaderInfo( CHeaderManager* theHeaderManager )
{
	// サブチャンクの取得。これらは一例。別のチャンクも同じ要領で取得できる。

	// YEAR チャンク
	try {
		CYearChunk yearChunk = theHeaderManager->GetPrimaryChunk( "YEAR" );
		printf( "** YEAR\n" );
		printf( "%d / %d\n", yearChunk.GetYear(), yearChunk.GetMonth() );
	}
	catch (CHeaderManager::err_FailGetChunk) { } // 見つからなければ何もしない

	// ENCD チャンク
	try {
		CEncdChunk encd = theHeaderManager->GetPrimaryChunk( "ENCD" );
		printf( "** ENCD\n" );
		printf( "%d年%d月%d日%d時%d分、タイムゾーン：%d\n",
			encd.GetYear(), encd.GetMonth(), encd.GetDay(), encd.GetHour(), encd.GetMinute(), encd.GetTimeZone() );
	}
	catch (CHeaderManager::err_FailGetChunk) { } // 見つからなければ何もしない

	// TRAC チャンク
	try {
		CTracChunk trac( theHeaderManager->GetPrimaryChunk("TRAC") );
		printf( "** TRAC\n" );
		printf( "%d\n", trac.GetInt() );
	}
	catch (CHeaderManager::err_FailGetChunk) { } // 見つからなければ何もしない

	// 統合文字列情報の取得。これらは一例。別の情報も同じ要領で取得できる。
	// NAME チャンク
	try {
		CUniStringInfo albm( "ALBM", *theHeaderManager );
		printf( "**ALBM\n" );
		std::cout << albm.GetPrimaryInfo() << " / " << albm.GetSecondaryInfo() << std::endl;
	}
	catch (CUniStringInfo::err_FailConstruction) { } // 見つからなければ何もしない

	return 0;
}

/*----------------------------------------------------------------------------*/
/* Name:        InitializeDecoder()                                           */
/* Description: initializes TwinVQ decoder                                    */
/*              Note: Do not change initialization order.                     */
/*                    It may cause of process corruption.                     */
/* Return:      (int) returns 1 when errors or returns 0                      */
/* Access:      static                                                        */
/*----------------------------------------------------------------------------*/

int InitializeDecoder(headerInfo *setupInfo,  // Output: setup parameters
					  int *frameSize,         // Output: frame size
					  int *numChannels,       // Output: number of channels
					  INDEX *index,           // Output: code information interface
					  float **out,            // Output: decoder output data array
					  short **bufout,         // Output: data buffer used for file output
					  BFILE *bfp_cw,          // Input:  the bitstream file pointer
					  int   fileType,
					  FILE  *fp_o,
					  char  *namein,          // Input:  input file name (used only for displaying)
					  char  *nameout)         // Input:  output file name (used only for displaying)
{
	/*--- read bitstream header and create "TWIN" chunk data ---*/

	// 初期化ステップ１：ビットストリームヘッダを読み込み、ヘッダデータ構造体を得る
	CChunkChunk* twinChunk;
	if ( (twinChunk=TvqGetBsHeaderInfo( bfp_cw)) == NULL ) {
		fprintf( stderr, "Program is stopped due to an error in parsing header.\n" );
		return 1;
	}

	// 初期化ステップ２：ヘッダデータ構造体を使ってヘッダマネージャを作成する。
	CHeaderManager *theHeaderManager = CHeaderManager::Create( *twinChunk );
	if ( theHeaderManager == NULL) {
		fprintf( stderr, "Failed to read header. Check the bitstream file.\n" );
		return 1;
	}
	delete twinChunk;

	// 初期化ステップ３：標準チャンクの情報を取得し、setupInfo に格納する
	if ( TvqGetStandardChunkInfo ( theHeaderManager, setupInfo ) ) {
		return 1;
	}

	// 初期化ステップ４：TwinVQ デコーダモジュールを初期化する
	if ( TvqInitialize( setupInfo, index, INIT_ERR_DISP_MBOX ) ){
		fprintf( stderr, "Program is stopped due to an initialization error.\n" );
		return 1;
	}

	// 初期化ステップ５：ビットストリーム読み込みモジュールを初期化する
	if ( TvqInitBsReader( setupInfo ) ) {
		fprintf( stderr, "Program is stopped due to an error in bitstream reader initialization.\n" );
		return 1;
	}

	// 初期化ステップ６：オーディオデータ出力インタフェースを初期化する
	/*--- inquire the TwinVQ decoder DLL about frame setup information ---*/
	*frameSize =   TvqGetFrameSize();     // frame size
	*numChannels = TvqGetNumChannels();   // number of channels
	/*--- allocate memory to data arrays ---*/
	*out    = new float[ *frameSize * *numChannels ]; // memory alocation: decoder output array
	*bufout = new short[ *frameSize * *numChannels ]; // memory allocation: audio data buffer
	/*--- jump to top of the audio data ---*/
//	if(fileType == fileTypeWav){
//		fseek(fp_o, WAVE_DATA_OFFSET, SEEK_SET);
//	}


	// 初期化終了後、ヘッダ情報を表示することができる
	TRACE(										// 符号化条件を表示する
		"\n<<< SETUP INFORMATION >>>\n"
		"Version = %s\n"
		"Input bitstream file = %s\n"
//		"Output audio data file = %s\n"
		"Output audio data file type = %s\n\n"
		"Title = %s\n"
		"Author = %s\n\n"
		"Number of channels = %d\n"
		"Bit Rate = %d kbit/s\n"
		"Sampling Rate = %d kHz\n"
		"FF  demonstration = %s\n"
		"REW demonstration = %s\n\n",
		setupInfo->ID,
		namein, 
//      nameout,
		fileTypeName[fileType],
		setupInfo->Name, setupInfo->Auth,
		*numChannels, setupInfo->bitRate, setupInfo->samplingRate,
		strOnOff(FF_DEMO),
		strOnOff(REW_DEMO)
		);

	if ( DisplayExtendedHeaderInfo( theHeaderManager ) ) {	// 拡張チャンクの情報を取得し、表示する（実装の例としてチャンクの一部のみを取得している）
		return 1;
	}

	delete theHeaderManager;

	return 0;
}

/*****************************************/
/* STATIC FUNCTIONS FOR DECODING PROCESS */
/*****************************************/
/*----------------------------------------------------------------------------*/
/* Name:        frtobuf()                                                     */
/* Description: copy frame data to output buffer                              */
/* Return:      none                                                          */
/* Access:      static                                                        */
/*----------------------------------------------------------------------------*/

void frtobuf(float out[],       /* Input  --- input data frame */
			 short  bufout[],    /* Output --- output data buffer array */
			 int    frameSize,   /* Input  --- frame size */
			 int    numChannels) /* Input  --- number of channels */
{
	/*--- Variables ---*/
	int	ismp, ich, uflag, lflag;
	float *ptr;
	register float dtmp;
	
	uflag = lflag = 0;
	
	for ( ich=0; ich<numChannels; ich++ ){
		ptr = out+ich*frameSize;
		for ( ismp=0; ismp<frameSize; ismp++ ){
			dtmp = ptr[ismp];
			if ( dtmp >= 0. ){
				if ( dtmp > 32700. ){
					dtmp = 32700.;
					uflag = 1;
				}
				bufout[ismp*numChannels+ich] = (short)(dtmp+0.5);
			}
			else{
				if ( dtmp < -32700. ){
					dtmp = -32700.;
					lflag = 1;
				}
				bufout[ismp*numChannels+ich] = (short)(dtmp-0.5);
			}
		}
	}
	//    if ( uflag ) fprintf( stderr, "U" );
	//    if ( lflag ) fprintf( stderr, "L" );
}

/*----------------------------------------------------------------------------*/
/* Name:        mark()                                                        */
/* Description: print decoding progress                                       */
/* Return:      none                                                          */
/* Access:      static                                                        */
/*----------------------------------------------------------------------------*/
#define NFR_PNT 32
#define NPNT   40
#define NLN    (NPNT*NFR_PNT)

static
void mark(int ndata, int flgFF, int flgREW)
{
#if 1
	const char *strMode[3] = {
		">  normal",
		">> FF    ",
		"<< REW   "
	};
	int id = 0;
	if (flgFF == 1){
		id = 1;
	}
	else if (flgREW == 1){
		id = 2;
	}
	fprintf(stderr, "\r%6d\t%s", ndata, strMode[id]);
#else
	if( ndata % NFR_PNT == 0 ) {
		if( ndata % NLN == 0 )
			fprintf( stderr, "\n Frame%6d\t", ndata );
		putc( '.', stderr );
		fflush( stderr );
	}
#endif
}

/*----------------------------------------------------------------------------*/
/* Name:        DecodingProcess()                                             */
/* Description: does decoding                                                 */
/* Return:      (int) returns 1 when errors or returns 0                      */
/* Access:      static                                                        */
/*----------------------------------------------------------------------------*/
static
int DecodingProcess(int   frameSize,    // Input:   frame size
					int   numChannels,  // Input:   number of channels
					INDEX *index,       // Pointer: code information interface
					float *out,         // Pointer: output data array
					short *bufout,      // Pointer: file output buffer
					BFILE *bfp_cw,      // Input:   input bitstream file pointer
					FILE  *fp_o)        // Input:   output file pointer
{

	fprintf( stderr, " Start decoding process..." );
#if DISPLAY_PROGRESS
	fprintf( stderr, "\n" );
#endif

	/*--- set and initialize decoding status parameters ---*/
	int wout_flag = 2;             // Decoder wave output flag
	int flgRewind = 0, flgFF = 0;  // FF and REW status
	int play_count = 0;            // skip control parameters when FF and REW mode

	/*--- the decoding process loop ---*/
	while ( TvqReadBsFrame(index, bfp_cw) != 0 ){ // read 1-frame bitstream data

		/* decode frame */
		TvqDecodeFrame(index, out);

		/* transform decoder output data to audio PCM data */
		frtobuf(out, bufout, frameSize, numChannels);

		// write PCM data to the output audio data file
		if ( wout_flag == 0 ){  // two frames are canceled after starting the decoding
			fwrite(bufout, sizeof(*bufout), frameSize*numChannels, fp_o);
		}
		wout_flag = wout_flag - 1 > 0 ? wout_flag - 1 : 0;

		/* display decoding progress */
#if DISPLAY_PROGRESS
		mark(TvqGetBsFramePoint() -1, flgFF, flgRewind); // mark decoding progression
#endif
		
		/*** FF control ***/
		if (FF_DEMO == 1){
			if (TvqGetBsFramePoint() > 150 && flgFF != -1) flgFF = 1; // set FF start point
			if (flgFF == 1){
				if (++play_count == 5){ // frame is skipped by every 5-frame decoding
					play_count = 0;          // reset the decoding counter
					wout_flag = 2;           // reset the wave output flag
					TvqSkipFrame(bfp_cw, 1); // skip one frames (then (1+2)=3 frames are skipped playing
				}
				if (TvqGetBsFramePoint() > 400){  // set FF stop point
					flgFF = -1;
				}
			}
		}
		/*** REW control ***/
		else if (REW_DEMO == 1){
			if (TvqGetBsFramePoint() > 450 && flgRewind != -1) flgRewind = 1; // set REW start point
			if (flgRewind == 1){
				if (++play_count == 5){ // frame is skipped by every 5-frame decoding
					play_count = 0;     // reset the decoding counter
					wout_flag = 2;      // reset the wave output flag
					TvqSkipFrame(bfp_cw, -11);  // skip backward 11 frames
				}
				if (TvqGetBsFramePoint() < 200){ // set REW stop point
					flgRewind = -1;
				}
			}
		}
	}

#if DISPLAY_PROGRESS
	fprintf( stderr, "\n" );
#endif
	fprintf( stderr, "done.\n" );

	return 0;
}

/************************************/
/* STATIC FUNCTIONS FOR TERMINATION */
/************************************/
/*----------------------------------------------------------------------------*/
/* Name:        trans_sampling_rate()                                         */
/* Description: translate sampling rate from TwinVQ format to WAVE format     */
/* Return:      WAVE format sampling rate                                     */
/* Access:      static                                                        */
/*----------------------------------------------------------------------------*/
static int trans_samplingRate( int in )
{
	switch(in){
	case 44:
		return 44100;
	case 22:
		return 22050;
	case 11:
		return 11025;
	default:
		return in*1000;
	}
}
		
/*----------------------------------------------------------------------------*/
/* Name:        WriteWaveHeader()                                             */
/* Description: write header of "WAVE" audio file format.                     */
/* Return:      (int) number of bytes written in the header.                  */
/* Access:      static                                                        */
/*----------------------------------------------------------------------------*/
static
int WriteWaveHeader(FILE *fp_o,
					int samplingRate,
					 int numChannels,
					 int dataSize,
					 char waveHeader[])
{
	int usedByte=0;

	int         size_RiffChunk   = dataSize + 36;
	const int   size_FmtChunk    = 16;
	const short dataType         = 1;	// PCM
	short       blockSize        = numChannels * sizeof(short);
	int         byteRate         = samplingRate * blockSize;
	const short numBitsPerSample = 8 * sizeof(short);

	const int   size_ChunkID = 4 * sizeof(char);

	/* create wave header */
	usedByte += fwrite( "RIFF",            1, size_ChunkID,  fp_o );	// RIFF chunk ID
	usedByte += fwrite( &size_RiffChunk,   1, sizeof(int),   fp_o );	// RIFF chunk size

	usedByte += fwrite( "WAVE",            1, size_ChunkID,  fp_o );	// WAVE chunk ID

	usedByte += fwrite( "fmt ",            1, size_ChunkID,  fp_o );	// fmt  chunk ID
	usedByte += fwrite( &size_FmtChunk,    1, sizeof(int),   fp_o );	// fmt  chunk size
	usedByte += fwrite( &dataType,         1, sizeof(short), fp_o );	// data type
	usedByte += fwrite( &numChannels,      1, sizeof(short), fp_o );	// number of channels
	usedByte += fwrite( &samplingRate,     1, sizeof(int),   fp_o );	// sampling rate
	usedByte += fwrite( &byteRate,         1, sizeof(int),   fp_o );	// number of bytes per second
	usedByte += fwrite( &blockSize,        1, sizeof(short), fp_o );	// block size
	usedByte += fwrite( &numBitsPerSample, 1, sizeof(short), fp_o );	// number of bits per sample

	usedByte += fwrite( "data",            1, size_ChunkID,  fp_o );	// data chunk ID
	usedByte += fwrite( &dataSize,         1, sizeof(int),   fp_o );	// data chunk size

	return usedByte;
}
		
/*----------------------------------------------------------------------------*/
/* Name:        WriteAudioFileHeader()                                        */
/* Description: Write audio file header.                                      */
/* Return:      (int) returns 1 when errors or returns 0                      */
/* Access:      static                                                        */
/*----------------------------------------------------------------------------*/
static
int WriteAudioFileHeader( int fileType, FILE *fp_o, int samplingRate_tvq, int numChannels )
{

	if(fileType == fileTypeWav){
		int samplingRate_wav; /* Hz */
		int dataSize;
		char waveHeader[WAVE_DATA_OFFSET];

		/* set parameters */
		samplingRate_wav = trans_samplingRate( samplingRate_tvq );		/* sampling rate */
		dataSize = ftell(fp_o) - WAVE_DATA_OFFSET;						/* data size */
		
		/* write header into wave file */
		fseek(fp_o, 0, SEEK_SET);
		if ( WriteWaveHeader(fp_o, samplingRate_wav, numChannels, dataSize, waveHeader) != WAVE_DATA_OFFSET ) return 1;
		fseek(fp_o, 0, SEEK_END);
		
	} /* if(fileType==0) */

	return 0;
}

/*----------------------------------------------------------------------------*/
/* Name:        TerminateDecoder()                                            */
/* Description: terminates the decoder                                        */
/* Return:      (int) return 1 when error or returns 0                        */
/* Access:      static                                                        */
/*----------------------------------------------------------------------------*/
static
int TerminateDecoder(
#if V2PLUS_SUPPORT
					 headerInfo *setupInfo,  // Input: setup information
#endif
					 INDEX      *index,      // Input: code information interface
					 float      *out,        // Input: output data array
					 short      *bufout,     // Input: file data buffer
					 BFILE      *bfp_cw,     // Input: bitstream file pointer
					 FILE       *fp_o)       // Input: audio data file pointer
{
	/* Terminate the TwinVQ decoder DLL */
	TvqTerminate( index );
	
	/* close files */
	bclose(bfp_cw);  // close the bitstream file
	fclose(fp_o);    // close the audio data file
	
	/* free memory of the data arrays */
	delete[] out;
	delete[] bufout;
	
	return 0;
}

/******************************************************************************/
/******************************************************************************/
/* Name:        main()                                                        */
/* Description: the main program()                                            */
/* Return:      (int) returns 1 when errors are found                         */
/* Access:      the main program                                              */
/******************************************************************************/
/******************************************************************************/
#define MULTIPLE 0

int main(int argc, char *argv[])
{

	int fileType = 0;

#if MULTIPLE==1  // This is a mode to decode files one another.
	while ( 1 ){
		/*-----------------------------------------------------------------*/
		/* NEGOCIATE WITH USER AND GET FILE NAMES                          */
		/*-----------------------------------------------------------------*/
		char namein[256], nameout[256];
		if ( NegociateAndGetFileNames(namein, nameout) ){
			return 1;
		}

#else // This is a mode to decode one file.
		/*-----------------------------------------------------------------*/
		/* RECEIVE ARGUMENTS                                               */
		/*-----------------------------------------------------------------*/
		char namein[BUFSIZ], nameout[BUFSIZ];
		if ( ReceiveArguments(argc, argv, namein, nameout, &FF_DEMO, &REW_DEMO, &fileType) ){
			return 1;
		}

#endif // MULTIPLE == 1
		/*-----------------------------------------------------------------*/
		/* OPEN INPUT BITSTREAM FILE AND OUTPUT AUDIO DATA FILE            */
		/*-----------------------------------------------------------------*/
		BFILE	*bfp_cw; // input bitstream file pointer
		FILE	*fp_o;   // output audio data file pointer
		if ( OpenFiles(namein, &bfp_cw, nameout, &fp_o, argv[0]) ){
			return 1;
		}

		/*-----------------------------------------------------------------*/
		/* INITIALIZE TwinVQ decoder                                       */
		/*-----------------------------------------------------------------*/
		headerInfo setupInfo;               // setup information
		INDEX index;                        // quantization indexes
		int        frameSize, numChannels;  // frame configuration parameters
		float      *out;                    // decoder output data array
		short      *bufout;                 // file output buffer
		if ( InitializeDecoder( &setupInfo, &frameSize, &numChannels, &index, &out, &bufout, bfp_cw, fileType, fp_o, namein, nameout ) ){
			return 1;
		}

		/*-----------------------------------------------------------------*/
		/* DECODING PROCESS                                                */
		/*-----------------------------------------------------------------*/
		if ( DecodingProcess( frameSize, numChannels, &index, out, bufout, bfp_cw, fp_o ) ){
			return 1;
		}

		/*-----------------------------------------------------------------*/
		/* TERMINATE THE DECODER                                           */
		/*-----------------------------------------------------------------*/
		WriteAudioFileHeader( fileType, fp_o, setupInfo.samplingRate, numChannels );

#ifndef V2PLUS_SUPPORT
		TerminateDecoder( &index, out, bufout, bfp_cw, fp_o );
#else
		TerminateDecoder( &setupInfo, &index, out, bufout, bfp_cw, fp_o );
#endif

#if MULTIPLE==1
	}
#endif
	return 0;
}

