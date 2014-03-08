#ifndef _TIFF_H_
#define _TIFF_H_
#include "Command.h"
#include <fstream>
#include <vector>
#include "AppContext.h"
#include <fstream>

#define TIFF_VERSION_CLASSIC 42

#define TIFF_BIG_ENDIAN 0
#define TIFF_LITTLE_ENDIAN 1

typedef struct
{
    short tiff_endian;      /* magic number (defines byte order) */
    short tiff_magic;    /* TIFF version number */
    int tiff_diroff;     /* byte offset to first directory */
} TIFFHeaderClassic;


enum DataType
{
    TIFF_NOTYPE = 0,      /* placeholder */
    TIFF_BYTE = 1,        /* 8-bit unsigned integer */
    TIFF_ASCII = 2,       /* 8-bit bytes w/ last byte null */
    TIFF_SHORT = 3,       /* 16-bit unsigned integer */
    TIFF_LONG = 4,        /* 32-bit unsigned integer */
    TIFF_RATIONAL = 5,    /* 64-bit unsigned fraction */
    TIFF_SBYTE = 6,       /* !8-bit signed integer */
    TIFF_UNDEFINED = 7,   /* !8-bit untyped data */
    TIFF_SSHORT = 8,      /* !16-bit signed integer */
    TIFF_SLONG = 9,       /* !32-bit signed integer */
    TIFF_SRATIONAL = 10,  /* !64-bit signed fraction */
    TIFF_FLOAT = 11,      /* !32-bit IEEE floating point */
    TIFF_DOUBLE = 12,     /* !64-bit IEEE floating point */
};
enum TAGS
{
    NewSubfileType = 254,
    SubfileType = 255,
    ImageWidth = 256,
    ImageLength = 257,
    BitsPerSample = 258,
    Compression = 259,
    PhotometricInterpretation = 262,
    Threshholding = 263,
    CellWidth = 264,
    CellLength = 265,
    FillOrder = 266,
    DocumentName = 269,
    ImageDescription = 270,
    Make = 271,
    Model = 272,
    StripOffsets = 273,
    Orientation = 274,
    SamplesPerPixel = 277,
    RowsPerStrip = 278,
    StripByteCounts = 279,
    MinSampleValue = 280,
    MaxSampleValue = 281,
    XResolution = 282,
    YResolution = 283,
    PlanarConfiguration = 284,
    PageName = 285,
    XPosition = 286,
    YPosition = 287,
    FreeOffsets = 288,
    FreeByteCounts = 289,
    GrayResponseUnit = 290,
    GrayResponseCurve = 291,
    T4Options = 292,
    T6Options = 293,
    ResolutionUnit = 296,
    PageNumber = 297,
    TransferFunction = 301,
    Software = 305,
    DateTime = 306,
    Artist = 315,
    HostComputer = 316,
    Predictor = 317,
    WhitePoint = 318,
    PrimaryChromaticities = 319,
    ColorMap = 320,
    HalftoneHints = 321,
    TileWidth = 322,
    TileLength = 323,
    TileOffsets = 324,
    TileByteCounts = 325,
    InkSet = 332,
    InkNames = 333,
    NumberOfInks = 334,
    DotRange = 336,
    TargetPrinter = 337,
    ExtraSamples = 338,
    SampleFormat = 339,
    SMinSampleValue = 340,
    SMaxSampleValue = 341,
    TransferRange = 342,
    JPEGProc = 512,
    JPEGInterchangeFormat = 513,
    JPEGInterchangeFormatLngth = 514,
    JPEGRestartInterval = 515,
    PEGLosslessPredictors = 517,
    JPEGPointTransforms = 518,
    JPEGQTables = 519,
    JPEGDCTables = 520,
    JPEGACTables = 521,
    YCbCrCoefficients = 529,
    YCbCrSubSampling = 530,
    YCbCrPositioning = 531,
    ReferenceBlackWhite = 532,
    Copyright = 33432
};

class Tiff
{
public:

    TIFFHeaderClassic header;
    int mImageWidth;
    int mImageLength;

    int mBitsPerSample;
    int mCompressed;
    int mPhotoMetric;
    vector<int> mStripOffset;
    int mRowsPerStrip;
    vector<int> mStripByteCounts;
    long long mXResolution;
    long long mYResolution;
    int mResolutionUnit;

    int mPictureType;
    int mSamplePerPixel;

    GLubyte mImageData[1024][1024][3];

    bool mEndian_Convert;
    short count_entry; //number of directory entry

};


class TiffHelper
{
public:

    int IsLittleEndian();

    template <class T>
    void endianswap(T *objp);

    void reverser_str(char *str);
    void reset(Tiff *ptr);
    string getTagName(int tag);
    string getTypeName(int type);
    void printTAG(short Tag, short fType, int count_value, int value_offset);
};

class TiffRead:public Command, public TiffHelper
{
public:
    TiffRead(string filename);
    ~TiffRead();
    void execute();


private:
    string filename; // read filename
    bool mConvert;
    ifstream mFile;

    ifstream mFile2;

    short mTmpS;
    int mTmpI;
    long mTmpL;

};

class TiffWrite:public Command, public TiffHelper
{
public:
    TiffWrite(string filename, int x, int y, int xx, int yy);
    ~TiffWrite();
    void execute();
    template <class T>
    void write(T obj);
private:
    string filename; //output filename
    ofstream mFile;
    int x,y,xx,yy;
};

class TiffStat:public Command, public TiffHelper
{
public:
    TiffStat();
    TiffStat(string filename);
    ~TiffStat();
    void execute();



private:
    string filename; // read filename
    ifstream mFile;
    ifstream mFile2;
};



#endif // _TIFF_H_
